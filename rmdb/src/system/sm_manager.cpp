/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "sm_manager.h"

#include <sys/stat.h>
#include <unistd.h>

#include <fstream>

#include "index/ix.h"
#include "record/rm.h"
#include "record_printer.h"
#include "common/type/attr_type.h"
#include "common/rc.h"

using namespace std;

/**
 * @description: 创建数据库，所有的数据库相关文件都放在数据库同名文件夹下
 * @param {string&} db_name 数据库名称
 */
RC SmManager::create_db(const std::string& db_name) {
    RC rc = RC::SUCCESS;
    if (disk_manager_->is_dir(db_name)) {
        return RC::DB_EXISTS;
    }
    //为数据库创建一个子目录
    std::string cmd = "mkdir " + db_name;
    if (system(cmd.c_str()) < 0) {  // 创建一个名为db_name的目录
        return RC::UNIX_ERROR;
    }
    if (chdir(db_name.c_str()) < 0) {  // 进入名为db_name的目录
        return RC::UNIX_ERROR;
    }
    //创建系统目录
    DbMeta *new_db = new DbMeta();
    new_db->name_ = db_name;

    // 注意，此处ofstream会在当前目录创建(如果没有此文件先创建)和打开一个名为DB_META_NAME的文件
    std::ofstream ofs(DB_META_NAME);

    // 将new_db中的信息写入到ofs打开的DB_META_NAME文件中
    rc = new_db->serialize(ofs);
    delete new_db;
    if(RM_FAIL(rc)) return rc;

    // 创建日志文件
    if(RM_FAIL(rc = disk_manager_->create_file(LOG_FILE_NAME))) return rc;

    // 回到根目录
    if (chdir("..") < 0) {
        return RC::UNIX_ERROR;
    }
    return RC::SUCCESS;
}

/**
 * @description: 删除数据库，同时需要清空相关文件以及数据库同名文件夹
 * @param {string&} db_name 数据库名称，与文件夹同名
 */
RC SmManager::drop_db(const std::string& db_name) {
    if (!disk_manager_->is_dir(db_name)) {
        RC::DB_NOT_EXISTS;
    }
    std::string cmd = "rm -r " + db_name;
    if (system(cmd.c_str()) < 0) {
        return RC::UNIX_ERROR;
    }
    return RC::SUCCESS;
}

/**
 * @description: 打开数据库，找到数据库对应的文件夹，并加载数据库元数据和相关文件
 * @param {string&} db_name 数据库名称，与文件夹同名
 */
RC SmManager::open_db(const std::string& db_name) {
    std::ifstream is(db_name + '/' + DB_META_NAME);
    RC rc = db_.deserialize(is);
    if(RM_FAIL(rc)) return rc;
    // 初始化fhs_
    for(auto pair : db_.tabs_) {
        string tab_path = db_name + '/' + pair.first;
        std::unique_ptr<RmFileHandle> rm_file_handle;
        if(RM_FAIL(rc = rm_manager_->open_file(tab_path, rm_file_handle))) return rc;
        fhs_.emplace(pair.first, std::move(rm_file_handle));
    }
    // TODO: 初始化ihs_

    return RC::SUCCESS;
}

/**
 * @description: 把数据库相关的元数据刷入磁盘中
 */
RC SmManager::flush_meta() {
    // 默认清空文件
    std::ofstream ofs(db_.name_ + '/' + DB_META_NAME);
    return db_.serialize(ofs);
}

/**
 * @description: 关闭数据库并把数据落盘
 */
RC SmManager::close_db() {
    RC rc = RC::SUCCESS;

    if(RM_FAIL(rc = flush_meta())) return rc;

    // 将table落盘
    for(auto table : db_.tabs_) {
        rc = rm_manager_->close_file(fhs_[table.first].get());
        if(RM_FAIL(rc)) return rc;
    }

    //TODO: 将index落盘

    return RC::SUCCESS;
}

/**
 * @description: 显示所有的表,通过测试需要将其结果写入到output.txt,详情看题目文档
 * @param {Context*} context 
 */
void SmManager::show_tables(Context* context) {
    std::fstream outfile;
    outfile.open("output.txt", std::ios::out | std::ios::app);
    outfile << "| Tables |\n";
    RecordPrinter printer(1);
    printer.print_separator(context);
    printer.print_record({"Tables"}, context);
    printer.print_separator(context);
    for (auto &entry : db_.tabs_) {
        auto &tab = entry.second;
        printer.print_record({tab.name}, context);
        outfile << "| " << tab.name << " |\n";
    }
    printer.print_separator(context);
    outfile.close();
}

/**
 * @description: 显示表的元数据
 * @param {string&} tab_name 表名称
 * @param {Context*} context 
 */
void SmManager::desc_table(const std::string& tab_name, Context* context) {
    // TabMeta &tab = db_.get_table(tab_name);

    // std::vector<std::string> captions = {"Field", "Type", "Index"};
    // RecordPrinter printer(captions.size());
    // // Print header
    // printer.print_separator(context);
    // printer.print_record(captions, context);
    // printer.print_separator(context);
    // // Print fields
    // for (auto &col : tab.cols) {
    //     std::vector<std::string> field_info = {col.name, attr_type_to_string(col.type), col.index ? "YES" : "NO"};
    //     printer.print_record(field_info, context);
    // }
    // // Print footer
    // printer.print_separator(context);
}

/**
 * @description: 创建表
 * @param {string&} tab_name 表的名称
 * @param {vector<ColDef>&} col_defs 表的字段
 * @param {Context*} context 
 */
RC SmManager::create_table(const std::string& tab_name, const std::vector<ColDef>& col_defs, Context* context) {
    RC rc = RC::SUCCESS;
    if (db_.is_table(tab_name)) {
        return RC::SCHEMA_TABLE_EXIST;
    }
    // Create table meta
    int curr_offset = 0;
    TabMeta tab;
    tab.name = tab_name;
    int id = 0;
    for (auto &col_def : col_defs) {
        ColMeta col(col_def.name,
                    col_def.type,
                    col_def.len,
                    curr_offset,
                    id,
                    false
        );
        curr_offset += col_def.len;
        id++;
        tab.cols.push_back(col);
    }
    // Create & open record file
    int record_size = curr_offset;  // record_size就是col meta所占的大小（表的元数据也是以记录的形式进行存储的）
    string tab_path = db_.name_ + '/' + tab_name;
    if(RM_FAIL(rc = rm_manager_->create_file(tab_path, record_size))) return rc;
    db_.tabs_[tab_name] = tab;
    // fhs_[tab_name] = rm_manager_->open_file(tab_name);
    std::unique_ptr<RmFileHandle> rm_file_handle;
    if(RM_FAIL(rc = rm_manager_->open_file(tab_path, rm_file_handle))) return rc;
    fhs_.emplace(tab_name, std::move(rm_file_handle));

    if(RM_FAIL(rc = flush_meta())) return rc;

    return RC::SUCCESS;
}

/**
 * @description: 删除表
 * @param {string&} tab_name 表的名称
 * @param {Context*} context
 */
RC SmManager::drop_table(const std::string& tab_name, Context* context) {
    RC rc;
    if(!db_.is_table(tab_name)) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    string tab_path = db_.name_ + '/' + tab_name;

    if(RM_FAIL(rc = rm_manager_->close_file(fhs_.at(tab_name).get()))) return rc;
    if(RM_FAIL(rc = rm_manager_->destroy_file(tab_path))) return rc;

    // TODO: 还要删除与table相关的所有索引

    fhs_.erase(tab_name);
    db_.tabs_.erase(tab_name);

    if(RM_FAIL(rc = flush_meta())) return rc;

    return RC::SUCCESS;
}

/**
 * @description: 创建索引
 * @param {string&} tab_name 表的名称
 * @param {vector<string>&} col_names 索引包含的字段名称
 * @param {Context*} context
 */
RC SmManager::create_index( TabMeta& tab_meta, const std::vector<ColMeta>& col_metas, Context* context) {
    RC rc = RC::SUCCESS;
    std::string tab_name = tab_meta.name;

    // 生成索引文件名

    std::string index_file_name = db_.name_ +'/' + tab_name;
    std::string index_name = ix_manager_->get_index_name(index_file_name, col_metas);
    // 创建索引文件
    if (RM_FAIL(rc = ix_manager_->create_index(index_name, col_metas))) {
        return rc;
    }
    // 打开索引文件
    std::unique_ptr<IxIndexHandle> index_handle;
    if (RM_FAIL(rc = ix_manager_->open_index(index_name,index_handle))) {
        return rc;
    }

    IndexMeta index_meta;
    index_meta.name = index_name;
    index_meta.cols = col_metas;
    tab_meta.indexes.emplace_back(index_meta);

    // 将索引句柄添加到 ihs_ 中
    ihs_.emplace(index_name, std::move(index_handle));

    // 刷写元数据到磁盘
    if (RM_FAIL(rc = flush_meta())) {
        return rc;
    }

    // 插入表中已有的记录到索引中
    RmFileHandle* file_handle = fhs_.at(tab_name).get();
    RecScan scan( file_handle, nullptr);
    if(RM_FAIL(rc = scan.open(context))){
        return rc;
    };
    while (RM_SUCC(rc = scan.next())) {
        vector<char> key;
        if(RM_FAIL( rc = ix_manager_->make_key(scan.record(),col_metas,key))){
            return rc;
        }
        index_handle->insert_entry(key.data(), scan.record()->rid , context->txn_);
        
    }
    return RC::SUCCESS;
}

/**
 * @description: 删除索引
 * @param {string&} tab_name 表名称
 * @param {vector<string>&} col_names 索引包含的字段名称
 * @param {Context*} context
 */
RC SmManager::drop_index(const std::string& tab_name, const std::vector<std::string>& col_names, Context* context) {
    return RC::UNIMPLEMENTED;
}

/**
 * @description: 删除索引
 * @param {string&} tab_name 表名称
 * @param {vector<ColMeta>&} 索引包含的字段元数据
 * @param {Context*} context
 */
RC SmManager::drop_index(const std::string& tab_name, const std::vector<ColMeta>& cols, Context* context) {
    return RC::UNIMPLEMENTED;
}