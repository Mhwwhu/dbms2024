/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "errors.h"
#include "sm_defs.h"
#include "common/rc.h"
#include "deps/jsoncpp/json/json.h"
#include "common/type/attr_type.h"
#include "common/common.h"

static const Json::StaticString FIELD_COL_NAME("name");
static const Json::StaticString FIELD_COL_TYPE("type");
static const Json::StaticString FIELD_COL_LEN("length");
static const Json::StaticString FIELD_COL_OFFSET("offset");
static const Json::StaticString FIELD_COL_ID("id");
static const Json::StaticString FIELD_COL_NULLABLE("nullable");

static const Json::StaticString FIELD_TAB_NAME("name");
static const Json::StaticString FIELD_TAB_ID("id");
static const Json::StaticString FIELD_TAB_COLUMNS("columns");
static const Json::StaticString FIELD_TAB_INDEXES("indexes");

static const Json::StaticString FIELD_INDEX_NAME("name");
static const Json::StaticString FIELD_INDEX_COLS("columns");
static const Json::StaticString FIELD_INDEX_UNIQUE("unique");

static const Json::StaticString FIELD_DB_NAME("name");
static const Json::StaticString FIELD_DB_TABLES("tables");

struct VirtualFieldMeta {
    std::string alias_name;
    AttrType attr_type;
    int len;
    common::VirtualFieldType type;

    VirtualFieldMeta() = default;
    VirtualFieldMeta(const std::string& name_, AttrType attr_type_, int len_, common::VirtualFieldType type_)
    : alias_name(name_), attr_type(attr_type_), len(len_), type(type_) {}

    virtual ~VirtualFieldMeta() = default;
};

/* 字段元数据 */
struct ColMeta : public VirtualFieldMeta{
    std::string name;       // 字段名称
    AttrType type;           // 字段类型
    int len;                // 字段长度
    int offset;             // 字段位于记录中的偏移量
    int id;
    bool nullable;

    ColMeta() = default;
    ColMeta(const std::string& name_, AttrType type_, int len_, int offset_, int id_, bool nullable_)
    : VirtualFieldMeta(name_, type_, len_, common::VirtualFieldType::TABLE_COL),
     name(name_), type(type_), len(len_), offset(offset_), id(id_), nullable(nullable_) {}

    Json::Value to_json() 
    {
        Json::Value col_value;
        col_value[FIELD_COL_NAME] = name;
        col_value[FIELD_COL_TYPE] = attr_type_to_string(type);
        col_value[FIELD_COL_LEN] = len;
        col_value[FIELD_COL_OFFSET] = offset;
        col_value[FIELD_COL_ID] = id;
        col_value[FIELD_COL_NULLABLE] = nullable;
        return col_value;
    }

    RC from_json(const Json::Value& json_value)
    {
        RC rc = RC::SUCCESS;

        if(!json_value.isObject()) return RC::INTERNAL;

        const Json::Value& name_value = json_value[FIELD_COL_NAME.c_str()];
        const Json::Value& type_value = json_value[FIELD_COL_TYPE.c_str()];
        const Json::Value& offset_value = json_value[FIELD_COL_OFFSET.c_str()];
        const Json::Value& len_value = json_value[FIELD_COL_LEN.c_str()];
        const Json::Value& col_id_value = json_value[FIELD_COL_ID.c_str()];
        const Json::Value& nullable_value = json_value[FIELD_COL_NULLABLE.c_str()];
    
        if (!name_value.isString()) {
            return RC::JSON_PARSE_FAILED;
        }
        if (!type_value.isString()) {
            return RC::JSON_PARSE_FAILED;
        }
        if (!offset_value.isInt()) {
            return RC::JSON_PARSE_FAILED;
        }
        if (!len_value.isInt()) {
            return RC::JSON_PARSE_FAILED;
        }
        if (!col_id_value.isInt()) {
            return RC::JSON_PARSE_FAILED;
        }
        if (!nullable_value.isBool()) {
            return RC::JSON_PARSE_FAILED;
        }
        type = attr_type_from_string(type_value.asCString());
        if (AttrType::UNDEFINED == type) {
            return RC::INTERNAL;
        }
    
        name = name_value.asCString();
        offset = offset_value.asInt();
        len = len_value.asInt();
        id = col_id_value.asInt();
        nullable = nullable_value.asBool();

        VirtualFieldMeta::alias_name = name;
        VirtualFieldMeta::attr_type = type;
        VirtualFieldMeta::type = common::VirtualFieldType::TABLE_COL;
        VirtualFieldMeta::len = len;

        return RC::SUCCESS;
    }
};

/* 索引元数据 */
struct IndexMeta {
    std::string name;           // 索引名称
    std::vector<ColMeta> cols;      // 索引包含的字段
    bool unique;

    Json::Value to_json()
    {
        Json::Value idx_value;
        idx_value[FIELD_INDEX_NAME] = name;
        idx_value[FIELD_INDEX_UNIQUE] = unique;

        Json::Value cols_value;
        for(ColMeta& col : cols) {
            cols_value.append(std::move(col.to_json()));
        }
        idx_value[FIELD_INDEX_COLS] = cols_value;

        return idx_value;
    }

    RC from_json(const Json::Value& json_value)
    {
        Json::Value name_value = json_value[FIELD_INDEX_NAME.c_str()];
        Json::Value unique_value = json_value[FIELD_INDEX_UNIQUE.c_str()];
        Json::Value cols_value = json_value[FIELD_INDEX_COLS.c_str()];

        if(!name_value.isString()) return RC::JSON_PARSE_FAILED;
        if(!unique_value.isBool()) return RC::JSON_PARSE_FAILED;
        if(!cols_value.isArray()) return RC::JSON_PARSE_FAILED;

        name = name_value.asCString();
        unique = unique_value.asBool();

        for(auto col_value : cols_value) {
            ColMeta col;
            if(RM_FAIL(col.from_json(col_value))) return RC::JSON_PARSE_FAILED;
            cols.push_back(col);
        }

        return RC::SUCCESS;
    }
};

struct VirtualTabMeta {
    std::string alias_name;
    std::vector<std::shared_ptr<VirtualFieldMeta>> vcols;
    common::VirtualTabType type;

    VirtualTabMeta(std::string alias, common::VirtualTabType type): alias_name(alias), type(type) {}
    VirtualTabMeta() = default;
    virtual ~VirtualTabMeta() = default;

    std::shared_ptr<VirtualFieldMeta> get_vfield(const std::string& name) 
    {
        for(auto vcol : vcols) {
            if(vcol->alias_name == name) return vcol;
        }
        return nullptr;
    }
};

/* 表元数据 */
struct TabMeta : public VirtualTabMeta{
    std::string name;                   // 表名称
    std::vector<ColMeta> cols;          // 表包含的字段
    std::vector<IndexMeta> indexes;     // 表上建立的索引

    TabMeta(): VirtualTabMeta() {}

    /* 判断当前表中是否存在名为col_name的字段 */
    bool is_col(const std::string &col_name) const {
        auto pos = std::find_if(cols.begin(), cols.end(), [&](const ColMeta &col) { return col.name == col_name; });
        return pos != cols.end();
    }

    /* 判断当前表上是否建有指定索引，索引包含的字段为col_names */
    // bool is_index(const std::vector<std::string>& col_names) const {
    //     for(auto& index: indexes) {
    //         if(index.col_num == col_names.size()) {
    //             size_t i = 0;
    //             for(; i < index.col_num; ++i) {
    //                 if(index.cols[i].name.compare(col_names[i]) != 0)
    //                     break;
    //             }
    //             if(i == index.col_num) return true;
    //         }
    //     }

    //     return false;
    // }

    /* 根据字段名称集合获取索引元数据 */
    // std::vector<IndexMeta>::iterator get_index_meta(const std::vector<std::string>& col_names) {
    //     for(auto index = indexes.begin(); index != indexes.end(); ++index) {
    //         if((*index).col_num != col_names.size()) continue;
    //         auto& index_cols = (*index).cols;
    //         size_t i = 0;
    //         for(; i < col_names.size(); ++i) {
    //             if(index_cols[i].name.compare(col_names[i]) != 0) 
    //                 break;
    //         }
    //         if(i == col_names.size()) return index;
    //     }
    //     throw IndexNotFoundError(name, col_names);
    // }

    /* 根据字段名称获取字段元数据 */
    RC get_col(const std::string &col_name, ColMeta& col) const {
        auto pos = std::find_if(cols.begin(), cols.end(), [&](const ColMeta &col) { return col.name == col_name; });
        if (pos == cols.end()) {
            return RC::SCHEMA_FIELD_NOT_EXIST;
        }
        col = *pos;
        return RC::SUCCESS;
    }

    Json::Value to_json() {
        Json::Value table_value;

        table_value[FIELD_TAB_NAME] = name;

        Json::Value cols_value;
        for(ColMeta& col : cols) {
            cols_value.append(std::move(col.to_json()));
        }
        table_value[FIELD_TAB_COLUMNS] = std::move(cols_value);

        Json::Value indexes_value;
        for(IndexMeta& idx : indexes) {
            indexes_value.append(std::move(idx.to_json()));
        }
        table_value[FIELD_TAB_INDEXES] = std::move(indexes_value);

        return table_value;
    }

    RC from_json(const Json::Value json_value)
    {
        Json::Value name_value = json_value[FIELD_TAB_NAME.c_str()];
        Json::Value cols_value = json_value[FIELD_TAB_COLUMNS.c_str()];
        Json::Value idxs_value = json_value[FIELD_TAB_INDEXES.c_str()];

        if(!name_value.isString()) return RC::JSON_PARSE_FAILED;
        if(!cols_value.isArray()) return RC::JSON_PARSE_FAILED;
        if(!idxs_value.isArray() && !idxs_value.isNull()) return RC::JSON_PARSE_FAILED;

        for(auto col_value : cols_value) {
            ColMeta col;
            if(RM_FAIL(col.from_json(col_value))) return RC::JSON_PARSE_FAILED;
            cols.push_back(col);
        }
        // 要对cols的id进行排序
        std::sort(cols.begin(), cols.end(), [](ColMeta& left, ColMeta& right) { return left.id < right.id; });

        if(!idxs_value.isNull()) {
            for(auto idx_value : idxs_value) {
                IndexMeta idx;
                if(RM_FAIL(idx.from_json(idx_value))) return RC::JSON_PARSE_FAILED;
                indexes.push_back(idx);
            }
        }

        name = name_value.asCString();
        VirtualTabMeta::alias_name = name;
        for(auto col : cols) {
            VirtualTabMeta::vcols.push_back(std::make_shared<ColMeta>(col));
        }

        return RC::SUCCESS;
    }
};

// 注意重载了操作符 << 和 >>，这需要更底层同样重载TabMeta、ColMeta的操作符 << 和 >>
/* 数据库元数据 */
class DbMeta {
    friend class SmManager;

   private:
    std::string name_;                      // 数据库名称
    std::map<std::string, TabMeta> tabs_;   // 数据库中包含的表

   public:
    // DbMeta(std::string name) : name_(name) {}

    /* 判断数据库中是否存在指定名称的表 */
    bool is_table(const std::string &tab_name) const { return tabs_.find(tab_name) != tabs_.end(); }

    void SetTabMeta(const std::string &tab_name, const TabMeta &meta) {
        tabs_[tab_name] = meta;
    }

    /* 获取指定名称表的元数据 */
    RC get_table(const std::string &tab_name, TabMeta& tab_meta) {
        auto pos = tabs_.find(tab_name);
        if (pos == tabs_.end()) {
            return RC::SCHEMA_TABLE_NOT_EXIST;
        }

        tab_meta = pos->second;
        return RC::SUCCESS;
    }

    Json::Value to_json()
    {
        Json::Value db_value;

        db_value[FIELD_DB_NAME] = name_;
        
        Json::Value tabs_value;
        for(auto pair : tabs_) {
            tabs_value.append(std::move(pair.second.to_json()));
        }
        db_value[FIELD_DB_TABLES] = tabs_value;

        return db_value;
    }

    RC from_json(const Json::Value& json_value)
    {
        Json::Value name_value = json_value[FIELD_DB_NAME.c_str()];
        Json::Value tabs_value = json_value[FIELD_DB_TABLES.c_str()];

        if(!name_value.isString()) return RC::JSON_PARSE_FAILED;
        if(!tabs_value.isArray() && !tabs_value.isNull()) return RC::JSON_PARSE_FAILED;
        
        if(!tabs_value.isNull()) {
            for(auto tab_value : tabs_value) {
                TabMeta tab;
                if(RM_FAIL(tab.from_json(tab_value))) return RC::JSON_PARSE_FAILED;
                tabs_[tab.name] = tab;
            }
        }

        name_ = name_value.asCString();

        return RC::SUCCESS;
    }

    RC serialize(std::ostream& os)
    {
        Json::StreamWriterBuilder builder;

        std::streampos old_pos = os.tellp();
        auto jsonString = Json::writeString(builder, to_json());
        os << jsonString << std::endl;
        std::streampos new_pos = os.tellp();
        if(new_pos - old_pos <= 0) return RC::IOERR_WRITE;

        return RC::SUCCESS;
    }

    RC deserialize(std::istream& is)
    {
        Json::Value             db_value;
        Json::CharReaderBuilder builder;
        std::string             errors;

        std::streampos old_pos = is.tellg();
        if (!Json::parseFromStream(builder, is, &db_value, &errors)) {
            return RC::JSON_PARSE_FAILED;
	    }

        return from_json(db_value);
    }
};
