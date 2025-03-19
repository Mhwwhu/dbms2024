# Parser模块
## lex/yacc 语法解析部分

语法解析部分负责将输入的String转化为一个个Token,用于构成语法分析树。

输出`shared_ptr<TreeNode> parse_tree` 作为根节点,其下包含了各种类型的子节点,各个节点的值信息存储类型在`SemValue`(YYSTYPE)定义。`TreeNode`作为基类,层层封装子句信息;

` lex.h` 可以考虑优化一下匹配规则

` yacc.h` 可以优化一下分析树结构

## analyse 语义分析部分 
### analyser类
关键函数`do_analyze`主要功能是将 SQL 语句的解析树`TreeNode`转换为一个 `Query` 对象，同时对查询中的表、列、条件等进行校验和处理。以`TreeNode`作为输入，输出`Query`。

`do_analyze`对到来的`TreeNode`做一个轮询,判断TreeNode顶层语句类型(DML,DDL,其他),然后执行对应的操作。

`check_column` 用于检查列名是否存在，以及存在不指定表明的字段时**推断**表名

`get_clause` 函数将 SQL 中的WHERE子句解析为 `Condition` 对象。对每个条件表达式（sv_conds），将其左操作数和右操作数提取出来，并存储在` Condition` 对象中。如果右操作数是列，调用 `check_column` 来确保列名的正确性。返回解析后的条件列表（conds）。

`check_clause` 函数用于校验 SQL 条件表达式的类型兼容性。首先,调用 get_all_cols 获取所有表的列元数据。对每个条件，检查左右操作数的类型是否一致。

### Query类

`Query`封装了SQL语句的元信息,并且仍包含原始的`TreeNode`,下一步作为optimizer的参数。*感觉有点冗余，但是为了简单可以浪费点空间*。
