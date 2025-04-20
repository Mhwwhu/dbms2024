/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"

#include "ast.h"
#include "yacc.tab.h"
#include "lex.h"
#include "expression/expression.h"
#include "expression/value_expr.h"
#include "expression/unbound_field_expr.h"
#include "expression/comparison_expr.h"
#include "expression/conjunction_expr.h"
#include "expression/star_expr.h"
#include <iostream>
#include <memory>


std::string token_name(const char *sql_string, YYLTYPE *llocp)
{
    return std::string(sql_string + llocp->first_column - 1, llocp->last_column - llocp->first_column);
}

int yyerror(YYLTYPE *locp, const char* s, std::shared_ptr<ast::TreeNode>& sql_result, yyscan_t scanner, const char* msg) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
    auto error_node = std::make_shared<ast::ErrorNode>();
    error_node->error_msg = msg;
    error_node->line = locp->first_line;
    error_node->col = locp->first_column;
    sql_result = std::move(error_node);
    return 0;
}

using namespace ast;

#line 102 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_HOME_XIRRO_DBMS2024_RMDB_SRC_PARSER_YACC_TAB_H_INCLUDED
# define YY_YY_HOME_XIRRO_DBMS2024_RMDB_SRC_PARSER_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SHOW = 258,
    TABLES = 259,
    CREATE = 260,
    TABLE = 261,
    DROP = 262,
    DESC = 263,
    INSERT = 264,
    INTO = 265,
    VALUES = 266,
    DELETE = 267,
    FROM = 268,
    ASC = 269,
    ORDER = 270,
    BY = 271,
    ON = 272,
    WHERE = 273,
    UPDATE = 274,
    SET = 275,
    SELECT = 276,
    INT = 277,
    CHAR = 278,
    FLOAT = 279,
    INDEX = 280,
    AND = 281,
    OR = 282,
    JOIN = 283,
    EXIT = 284,
    HELP = 285,
    TXN_BEGIN = 286,
    TXN_COMMIT = 287,
    TXN_ABORT = 288,
    TXN_ROLLBACK = 289,
    ORDER_BY = 290,
    ENABLE_NESTLOOP = 291,
    ENABLE_SORTMERGE = 292,
    LEQ = 293,
    NEQ = 294,
    GEQ = 295,
    T_EOF = 296,
    IDENTIFIER = 297,
    VALUE_STRING = 298,
    VALUE_INT = 299,
    VALUE_FLOAT = 300,
    VALUE_BOOL = 301
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner);

#endif /* !YY_YY_HOME_XIRRO_DBMS2024_RMDB_SRC_PARSER_YACC_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   136

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

#define YYUNDEFTOK  2
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    49,    55,     2,    50,     2,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    47,
      53,    52,    54,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    89,    89,    97,    98,    99,   100,   105,   109,   113,
     117,   124,   138,   142,   146,   150,   154,   161,   164,   167,
     170,   176,   182,   188,   194,   200,   201,   207,   213,   216,
     219,   222,   228,   234,   241,   244,   247,   248,   254,   257,
     260,   261,   268,   271,   279,   283,   290,   294,   301,   308,
     312,   316,   334,   338,   342,   346,   401,   402,   403,   404,
     405,   406,   410,   413,   420,   423,   427,   431,   435,   442,
     447,   450,   455,   460,   463,   466,   471,   474,   480,   484,
     491,   546,   548
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SHOW", "TABLES", "CREATE", "TABLE",
  "DROP", "DESC", "INSERT", "INTO", "VALUES", "DELETE", "FROM", "ASC",
  "ORDER", "BY", "ON", "WHERE", "UPDATE", "SET", "SELECT", "INT", "CHAR",
  "FLOAT", "INDEX", "AND", "OR", "JOIN", "EXIT", "HELP", "TXN_BEGIN",
  "TXN_COMMIT", "TXN_ABORT", "TXN_ROLLBACK", "ORDER_BY", "ENABLE_NESTLOOP",
  "ENABLE_SORTMERGE", "LEQ", "NEQ", "GEQ", "T_EOF", "IDENTIFIER",
  "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL", "';'", "'('",
  "')'", "','", "'.'", "'='", "'<'", "'>'", "'*'", "$accept", "start",
  "stmt", "txnStmt", "dbStmt", "ddl", "dml", "insert", "select", "delete",
  "update", "optFromClause", "virtualTable", "joinTree", "join_type",
  "onClause", "optGroupbyClause", "optHavingClause", "optWhereClause",
  "optOrderbyClause", "optLimitClause", "optColumnClause", "insertList",
  "fieldList", "colNameList", "field", "type", "value", "compOp",
  "exprList", "expr", "valueExpr", "unboundFieldExpr", "compExpr",
  "conjunctionExpr", "starExpr", "setClauses", "setClause", "tbName",
  "colName", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    59,    40,    41,
      44,    46,    61,    60,    62,    42
};
# endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-82)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      58,     6,     0,    10,   -30,    37,     1,   -30,    75,   -75,
     -75,   -75,   -75,    54,    11,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -30,   -30,   -30,   -30,   -75,   -75,
     -30,   -30,    40,    13,   -75,   -75,   -75,   -75,    75,   -75,
     -75,   -12,    62,   -75,   -75,   -75,   -75,    18,   -75,   -75,
     -75,    28,    74,   -75,    76,    77,    93,    51,    56,   -31,
      75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    75,     4,
      51,    51,    51,    51,   115,    75,   -75,   -75,    -5,   -75,
      79,   -75,   -31,   -75,   -21,   -75,    62,   -75,    62,   -75,
     -75,     3,   -75,    27,     7,   -75,    25,    31,    80,    82,
      45,   -75,    51,   -75,    75,   -19,   -75,   -31,   -31,    93,
     -75,    51,   -75,    81,   -75,   -75,   -75,    51,   -75,   -75,
      75,    85,    75,    75,   -75,    62,   -75,   -21,   -13,   -75,
     -75,    83,   -75,    57,    75,    62,    62,   -75,   -75,   -75,
      86,   -75,    63,   -75,   -75,   -75
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     9,    10,     0,     0,     6,     3,     4,     5,    20,
      19,    18,    17,    11,     0,     0,     0,     0,    81,    14,
       0,     0,     0,    82,    54,    52,    53,    55,     0,    76,
      69,    25,    62,    65,    66,    67,    68,     0,    71,     1,
       2,     0,     0,    13,     0,    40,    36,     0,     0,     0,
       0,    34,    60,    59,    61,    56,    57,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    82,    36,    78,
       0,    64,     0,    28,    26,    27,    63,    35,    72,    77,
      70,     0,    44,     0,     0,    46,     0,     0,     0,    21,
      73,    37,     0,    24,     0,     0,    32,     0,     0,    36,
      12,     0,    49,     0,    51,    48,    15,     0,    16,    41,
       0,     0,     0,     0,    79,    80,    31,    30,     0,    38,
      45,     0,    47,     0,     0,    74,    75,    33,    29,    39,
       0,    42,     0,    22,    50,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -74,   -75,   -75,   -75,   -75,   -73,   -75,
     -75,   -75,   -75,   -75,   -54,    23,   -75,   -75,   -75,   -72,
     -36,   -75,   -75,   -75,   -75,   -75,   -75,    34,    -4,   -29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    61,    83,    84,   108,   138,    87,   109,    76,   139,
     143,    74,    99,    91,    94,    92,   115,    40,    68,    41,
      42,    43,    44,    45,   101,    46,    78,    79,    47,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    59,    58,    32,   137,   103,    24,   106,   105,   106,
      23,    28,    28,    75,    31,   106,    26,    82,    96,    97,
      51,    52,    53,    54,    86,    25,    55,    56,    80,   107,
     126,   107,    88,   127,   128,    27,   129,   107,    60,   100,
      90,    93,    95,    95,    95,   102,    77,    30,   133,   112,
     113,   114,   110,   111,    49,    85,   116,   117,    50,    89,
      57,     1,   142,     2,   -81,     3,     4,     5,   125,    69,
       6,   122,   123,    80,   118,   117,    70,     7,    85,     8,
     119,   117,    93,    62,    63,    64,   135,   136,   132,     9,
      10,    11,    12,    77,    62,    63,    64,    65,    66,    67,
      62,    63,    64,    85,    85,    81,   141,    60,    65,    66,
      67,    75,   145,    60,    65,    66,    67,    33,    34,    35,
      36,    37,    71,    38,    72,    73,    98,   140,   120,   131,
      39,   104,   121,   134,   130,   144,   124
};

static const yytype_uint8 yycheck[] =
{
       4,    13,    38,     7,    17,    78,     6,    28,    82,    28,
       4,    42,    42,    18,    13,    28,     6,    48,    72,    73,
      24,    25,    26,    27,    60,    25,    30,    31,    57,    50,
      49,    50,    68,   107,   108,    25,   109,    50,    50,    75,
      69,    70,    71,    72,    73,    50,    42,    10,   120,    22,
      23,    24,    49,    50,     0,    59,    49,    50,    47,    55,
      20,     3,   134,     5,    51,     7,     8,     9,   104,    51,
      12,    26,    27,   102,    49,    50,    48,    19,    82,    21,
      49,    50,   111,    38,    39,    40,   122,   123,   117,    31,
      32,    33,    34,    42,    38,    39,    40,    52,    53,    54,
      38,    39,    40,   107,   108,    49,    49,    50,    52,    53,
      54,    18,    49,    50,    52,    53,    54,    42,    43,    44,
      45,    46,    48,    48,    48,    48,    11,    44,    48,    48,
      55,    52,    50,    48,   111,    49,   102
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    19,    21,    31,
      32,    33,    34,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     4,     6,    25,     6,    25,    42,    94,
      10,    13,    94,    42,    43,    44,    45,    46,    48,    55,
      83,    85,    86,    87,    88,    89,    91,    94,    95,     0,
      47,    94,    94,    94,    94,    94,    94,    20,    86,    13,
      50,    67,    38,    39,    40,    52,    53,    54,    84,    51,
      48,    48,    48,    48,    77,    18,    74,    42,    92,    93,
      95,    49,    48,    68,    69,    94,    86,    72,    86,    55,
      95,    79,    81,    95,    80,    95,    80,    80,    11,    78,
      86,    90,    50,    74,    52,    69,    28,    50,    70,    73,
      49,    50,    22,    23,    24,    82,    49,    50,    49,    49,
      48,    50,    26,    27,    93,    86,    49,    69,    69,    74,
      81,    48,    95,    85,    48,    86,    86,    17,    71,    75,
      44,    49,    85,    76,    49,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    58,    58,    59,    59,    59,
      59,    60,    61,    61,    61,    61,    61,    62,    62,    62,
      62,    63,    64,    65,    66,    67,    67,    68,    69,    69,
      69,    69,    70,    71,    72,    73,    74,    74,    75,    76,
      77,    77,    78,    78,    79,    79,    80,    80,    81,    82,
      82,    82,    83,    83,    83,    83,    84,    84,    84,    84,
      84,    84,    85,    85,    86,    86,    86,    86,    86,    87,
      88,    88,    89,    90,    90,    90,    91,    91,    92,    92,
      93,    94,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     6,     3,     2,     6,     6,     1,     1,     1,
       1,     5,     8,     4,     5,     0,     2,     1,     1,     4,
       3,     3,     1,     1,     0,     0,     0,     2,     0,     0,
       0,     3,     4,     5,     1,     3,     1,     3,     2,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     1,     3,
       3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 90 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        sql_result = std::move((yyvsp[-1].sv_node));
        YYACCEPT;
    }
#line 1601 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 7:
#line 106 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1609 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 8:
#line 110 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1617 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 9:
#line 114 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1625 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 10:
#line 118 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1633 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 11:
#line 125 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1641 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 12:
#line 139 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1649 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 13:
#line 143 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1657 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 14:
#line 147 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1665 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 15:
#line 151 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1673 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 16:
#line 155 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1681 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 17:
#line 161 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
           {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1689 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 18:
#line 164 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
             {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1697 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 19:
#line 167 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
             {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1705 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 20:
#line 170 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
             {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1713 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 21:
#line 176 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                                                  {
        (yyval.sv_node) = std::make_shared<InsertNode>((yyvsp[-2].sv_str), (yyvsp[-1].sv_strs), (yyvsp[0].sv_expr_chunk));
    }
#line 1721 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 22:
#line 182 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                                                                                                                  {
        (yyval.sv_node) = std::make_shared<SelectNode>((yyvsp[-6].sv_exprs), (yyvsp[-5].sv_join), (yyvsp[-4].sv_exprs), (yyvsp[-3].sv_expr), (yyvsp[-2].sv_expr), (yyvsp[-1].sv_orderby), (yyvsp[0].sv_int));
    }
#line 1729 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 23:
#line 188 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                                      {
        (yyval.sv_node) = std::make_shared<DeleteNode>((yyvsp[-1].sv_str), (yyvsp[0].sv_expr));
    }
#line 1737 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 24:
#line 194 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                                                {
        (yyval.sv_node) = std::make_shared<UpdateNode>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_expr));
    }
#line 1745 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 25:
#line 200 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_join) = nullptr; }
#line 1751 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 26:
#line 201 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                    {
        (yyval.sv_join) = std::move((yyvsp[0].sv_join));
    }
#line 1759 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 27:
#line 207 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
           {
        (yyval.sv_vtable) = std::make_shared<VirtualTableNode>((yyvsp[0].sv_str), (yyvsp[0].sv_str));
    }
#line 1767 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 28:
#line 213 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                 {
        (yyval.sv_join) = std::make_shared<JoinNode>(std::move((yyvsp[0].sv_vtable)));
    }
#line 1775 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 29:
#line 216 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                                           {
        (yyval.sv_join) = std::make_shared<JoinNode>(std::move((yyvsp[-3].sv_join)), std::move((yyvsp[-1].sv_join)), std::move((yyvsp[0].sv_expr)), (yyvsp[-2].sv_join_type));
    }
#line 1783 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 30:
#line 219 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                            {
        (yyval.sv_join) = std::make_shared<JoinNode>(std::move((yyvsp[-2].sv_join)), std::move((yyvsp[0].sv_join)), nullptr, common::JoinType::CARTESIAN_PRODUCT);
    }
#line 1791 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 31:
#line 222 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                       {
        (yyval.sv_join) = std::move((yyvsp[-1].sv_join));
    }
#line 1799 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 32:
#line 228 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
         {
        (yyval.sv_join_type) = common::JoinType::INNER_JOIN;
    }
#line 1807 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 33:
#line 234 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
        {
        (yyval.sv_expr) = nullptr;
    }
#line 1815 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 34:
#line 241 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_exprs) = std::vector<std::shared_ptr<Expression>>(); }
#line 1821 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 35:
#line 244 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_expr) = nullptr; }
#line 1827 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 36:
#line 247 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_expr) = nullptr; }
#line 1833 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 37:
#line 248 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                            {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
    }
#line 1841 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 38:
#line 254 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_orderby) = nullptr; }
#line 1847 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 39:
#line 257 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_int) = -1; }
#line 1853 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 40:
#line 260 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_strs) = std::vector<std::string>(); }
#line 1859 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 41:
#line 261 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                         {
        (yyval.sv_strs) = std::vector<std::string>();
        std::move((yyvsp[-1].sv_strs).begin(), (yyvsp[-1].sv_strs).end(), std::back_inserter((yyval.sv_strs)));
    }
#line 1868 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 42:
#line 268 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                             {
        (yyval.sv_expr_chunk) = std::vector<std::vector<std::shared_ptr<Expression>>>();
        (yyval.sv_expr_chunk).push_back(std::move((yyvsp[-1].sv_exprs)));
    }
#line 1877 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 43:
#line 271 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                                        {
        (yyval.sv_expr_chunk) = std::vector<std::vector<std::shared_ptr<Expression>>>();
        std::move((yyvsp[-4].sv_expr_chunk).begin(), (yyvsp[-4].sv_expr_chunk).end(), std::back_inserter((yyval.sv_expr_chunk)));
        (yyval.sv_expr_chunk).push_back(std::move((yyvsp[-1].sv_exprs)));
    }
#line 1887 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 44:
#line 280 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 1895 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 45:
#line 284 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1903 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 46:
#line 291 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1911 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 47:
#line 295 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1919 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 48:
#line 302 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<Field>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 1927 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 49:
#line 309 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(AttrType::INTS, sizeof(int));
    }
#line 1935 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 50:
#line 313 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(AttrType::CHARS, (yyvsp[-1].sv_int));
    }
#line 1943 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 51:
#line 317 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(AttrType::FLOATS, sizeof(float));
    }
#line 1951 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 52:
#line 335 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_int));
    }
#line 1959 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 53:
#line 339 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_float));
    }
#line 1967 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 54:
#line 343 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_str).c_str());
    }
#line 1975 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 55:
#line 347 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_bool));
    }
#line 1983 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 56:
#line 401 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
        { (yyval.sv_comp_op) = common::CompOp::EQ; }
#line 1989 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 57:
#line 402 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::LT; }
#line 1995 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 58:
#line 403 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::GT; }
#line 2001 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 59:
#line 404 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::NE; }
#line 2007 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 60:
#line 405 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::LE; }
#line 2013 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 61:
#line 406 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::GE; }
#line 2019 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 62:
#line 410 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
         {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expression>>();
        (yyval.sv_exprs).push_back(std::move((yyvsp[0].sv_expr)));
    }
#line 2028 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 63:
#line 413 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                          {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expression>>();
        std::move((yyvsp[-2].sv_exprs).begin(), (yyvsp[-2].sv_exprs).end(), std::back_inserter((yyval.sv_exprs)));
        (yyval.sv_exprs).push_back(std::move((yyvsp[0].sv_expr)));
    }
#line 2038 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 64:
#line 420 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                 {
        (yyval.sv_expr) = std::move((yyvsp[-1].sv_expr));
    }
#line 2046 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 65:
#line 423 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
        (yyval.sv_expr)->set_name(token_name(sql_string, &(yylsp[0])));
    }
#line 2055 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 66:
#line 427 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                       {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
        (yyval.sv_expr)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2064 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 67:
#line 431 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
               {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
        (yyval.sv_expr)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2073 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 68:
#line 435 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
               {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
        (yyval.sv_expr)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2082 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 69:
#line 442 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
          {
        (yyval.sv_expr) = std::make_shared<ValueExpr>(*(yyvsp[0].sv_val));
    }
#line 2090 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 70:
#line 447 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                       {
        (yyval.sv_expr) = std::make_shared<UnboundFieldExpr>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2098 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 71:
#line 450 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
              {
        (yyval.sv_expr) = std::make_shared<UnboundFieldExpr>("", (yyvsp[0].sv_str));
    }
#line 2106 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 72:
#line 455 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                     {
        (yyval.sv_expr) = std::make_shared<ComparisonExpr>(std::move((yyvsp[-2].sv_expr)), std::move((yyvsp[0].sv_expr)), (yyvsp[-1].sv_comp_op));
    }
#line 2114 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 73:
#line 460 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
         {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
    }
#line 2122 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 74:
#line 463 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                    {
        (yyval.sv_expr) = std::make_shared<ConjunctionExpr>(std::move((yyvsp[-2].sv_expr)), std::move((yyvsp[0].sv_expr)), common::ConjunctionType::AND);
    }
#line 2130 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 75:
#line 466 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                   {
        (yyval.sv_expr) = std::make_shared<ConjunctionExpr>(std::move((yyvsp[-2].sv_expr)), std::move((yyvsp[0].sv_expr)), common::ConjunctionType::OR);
    }
#line 2138 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 76:
#line 471 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
        {
        (yyval.sv_expr) = std::make_shared<StarExpr>();
    }
#line 2146 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 77:
#line 474 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
                     {
        (yyval.sv_expr) = std::make_shared<StarExpr>((yyvsp[-2].sv_str));
    }
#line 2154 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 78:
#line 481 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2162 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 79:
#line 485 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2170 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 80:
#line 492 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_expr));
    }
#line 2178 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"
    break;


#line 2182 "/home/xirro/dbms2024/rmdb/src/parser/yacc.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 549 "/home/xirro/dbms2024/rmdb/src/parser/yacc.y"


extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, std::shared_ptr<ast::TreeNode>& sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
