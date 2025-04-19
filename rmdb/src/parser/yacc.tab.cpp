/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"

#include "ast.h"
#include "yacc.tab.h"
#include "lex.h"
#include "expression/expression.h"
#include "expression/value_expr.h"
#include "expression/unbound_field_expr.h"
#include "expression/comparison_expr.h"
#include "expression/conjunction_expr.h"
#include <iostream>
#include <memory>


std::string token_name(const char *sql_string, YYLTYPE *llocp)
{
    return std::string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
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

#line 102 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"

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

#include "yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SHOW = 3,                       /* SHOW  */
  YYSYMBOL_TABLES = 4,                     /* TABLES  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_DROP = 7,                       /* DROP  */
  YYSYMBOL_DESC = 8,                       /* DESC  */
  YYSYMBOL_INSERT = 9,                     /* INSERT  */
  YYSYMBOL_INTO = 10,                      /* INTO  */
  YYSYMBOL_VALUES = 11,                    /* VALUES  */
  YYSYMBOL_DELETE = 12,                    /* DELETE  */
  YYSYMBOL_FROM = 13,                      /* FROM  */
  YYSYMBOL_ASC = 14,                       /* ASC  */
  YYSYMBOL_ORDER = 15,                     /* ORDER  */
  YYSYMBOL_BY = 16,                        /* BY  */
  YYSYMBOL_ON = 17,                        /* ON  */
  YYSYMBOL_WHERE = 18,                     /* WHERE  */
  YYSYMBOL_UPDATE = 19,                    /* UPDATE  */
  YYSYMBOL_SET = 20,                       /* SET  */
  YYSYMBOL_SELECT = 21,                    /* SELECT  */
  YYSYMBOL_INT = 22,                       /* INT  */
  YYSYMBOL_CHAR = 23,                      /* CHAR  */
  YYSYMBOL_FLOAT = 24,                     /* FLOAT  */
  YYSYMBOL_INDEX = 25,                     /* INDEX  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_JOIN = 28,                      /* JOIN  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_HELP = 30,                      /* HELP  */
  YYSYMBOL_TXN_BEGIN = 31,                 /* TXN_BEGIN  */
  YYSYMBOL_TXN_COMMIT = 32,                /* TXN_COMMIT  */
  YYSYMBOL_TXN_ABORT = 33,                 /* TXN_ABORT  */
  YYSYMBOL_TXN_ROLLBACK = 34,              /* TXN_ROLLBACK  */
  YYSYMBOL_ORDER_BY = 35,                  /* ORDER_BY  */
  YYSYMBOL_ENABLE_NESTLOOP = 36,           /* ENABLE_NESTLOOP  */
  YYSYMBOL_ENABLE_SORTMERGE = 37,          /* ENABLE_SORTMERGE  */
  YYSYMBOL_LEQ = 38,                       /* LEQ  */
  YYSYMBOL_NEQ = 39,                       /* NEQ  */
  YYSYMBOL_GEQ = 40,                       /* GEQ  */
  YYSYMBOL_T_EOF = 41,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 42,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 43,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 44,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 45,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 46,                /* VALUE_BOOL  */
  YYSYMBOL_47_ = 47,                       /* ';'  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* ')'  */
  YYSYMBOL_50_ = 50,                       /* ','  */
  YYSYMBOL_51_ = 51,                       /* '.'  */
  YYSYMBOL_52_ = 52,                       /* '='  */
  YYSYMBOL_53_ = 53,                       /* '<'  */
  YYSYMBOL_54_ = 54,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_start = 56,                     /* start  */
  YYSYMBOL_stmt = 57,                      /* stmt  */
  YYSYMBOL_txnStmt = 58,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 59,                    /* dbStmt  */
  YYSYMBOL_ddl = 60,                       /* ddl  */
  YYSYMBOL_dml = 61,                       /* dml  */
  YYSYMBOL_insert = 62,                    /* insert  */
  YYSYMBOL_select = 63,                    /* select  */
  YYSYMBOL_delete = 64,                    /* delete  */
  YYSYMBOL_update = 65,                    /* update  */
  YYSYMBOL_optFromClause = 66,             /* optFromClause  */
  YYSYMBOL_virtualTable = 67,              /* virtualTable  */
  YYSYMBOL_joinTree = 68,                  /* joinTree  */
  YYSYMBOL_join_type = 69,                 /* join_type  */
  YYSYMBOL_onClause = 70,                  /* onClause  */
  YYSYMBOL_optGroupbyClause = 71,          /* optGroupbyClause  */
  YYSYMBOL_optHavingClause = 72,           /* optHavingClause  */
  YYSYMBOL_optWhereClause = 73,            /* optWhereClause  */
  YYSYMBOL_optOrderbyClause = 74,          /* optOrderbyClause  */
  YYSYMBOL_optLimitClause = 75,            /* optLimitClause  */
  YYSYMBOL_optColumnClause = 76,           /* optColumnClause  */
  YYSYMBOL_insertList = 77,                /* insertList  */
  YYSYMBOL_fieldList = 78,                 /* fieldList  */
  YYSYMBOL_colNameList = 79,               /* colNameList  */
  YYSYMBOL_field = 80,                     /* field  */
  YYSYMBOL_type = 81,                      /* type  */
  YYSYMBOL_value = 82,                     /* value  */
  YYSYMBOL_compOp = 83,                    /* compOp  */
  YYSYMBOL_exprList = 84,                  /* exprList  */
  YYSYMBOL_expr = 85,                      /* expr  */
  YYSYMBOL_valueExpr = 86,                 /* valueExpr  */
  YYSYMBOL_unboundFieldExpr = 87,          /* unboundFieldExpr  */
  YYSYMBOL_compExpr = 88,                  /* compExpr  */
  YYSYMBOL_conjunctionExpr = 89,           /* conjunctionExpr  */
  YYSYMBOL_setClauses = 90,                /* setClauses  */
  YYSYMBOL_setClause = 91,                 /* setClause  */
  YYSYMBOL_tbName = 92,                    /* tbName  */
  YYSYMBOL_colName = 93                    /* colName  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   119

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    49,     2,     2,    50,     2,    51,     2,     2,     2,
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
       0,    87,    87,    95,    96,    97,    98,   103,   107,   111,
     115,   122,   136,   140,   144,   159,   162,   165,   168,   174,
     180,   186,   192,   198,   199,   205,   211,   214,   217,   220,
     226,   232,   239,   242,   245,   246,   252,   255,   258,   259,
     266,   269,   277,   281,   288,   292,   299,   306,   310,   314,
     332,   336,   340,   344,   399,   400,   401,   402,   403,   404,
     408,   411,   418,   421,   424,   427,   432,   437,   440,   445,
     450,   453,   456,   461,   465,   472,   527,   529
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SHOW", "TABLES",
  "CREATE", "TABLE", "DROP", "DESC", "INSERT", "INTO", "VALUES", "DELETE",
  "FROM", "ASC", "ORDER", "BY", "ON", "WHERE", "UPDATE", "SET", "SELECT",
  "INT", "CHAR", "FLOAT", "INDEX", "AND", "OR", "JOIN", "EXIT", "HELP",
  "TXN_BEGIN", "TXN_COMMIT", "TXN_ABORT", "TXN_ROLLBACK", "ORDER_BY",
  "ENABLE_NESTLOOP", "ENABLE_SORTMERGE", "LEQ", "NEQ", "GEQ", "T_EOF",
  "IDENTIFIER", "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL",
  "';'", "'('", "')'", "','", "'.'", "'='", "'<'", "'>'", "$accept",
  "start", "stmt", "txnStmt", "dbStmt", "ddl", "dml", "insert", "select",
  "delete", "update", "optFromClause", "virtualTable", "joinTree",
  "join_type", "onClause", "optGroupbyClause", "optHavingClause",
  "optWhereClause", "optOrderbyClause", "optLimitClause",
  "optColumnClause", "insertList", "fieldList", "colNameList", "field",
  "type", "value", "compOp", "exprList", "expr", "valueExpr",
  "unboundFieldExpr", "compExpr", "conjunctionExpr", "setClauses",
  "setClause", "tbName", "colName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-96)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-77)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      47,     9,    12,    17,   -14,    23,    25,   -14,    52,   -96,
     -96,   -96,   -96,    40,    -2,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -14,   -14,   -96,   -96,   -14,   -14,
      71,     2,   -96,   -96,   -96,   -96,    52,   -96,    -9,    50,
     -96,   -96,   -96,    16,   -96,   -96,   -96,    51,   -96,    53,
      90,    67,    33,    21,    52,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,    52,    67,    67,    67,    99,    52,   -96,   -96,
     -13,   -96,    59,   -96,    21,   -96,   -19,   -96,    50,   -96,
      50,   -96,   -39,   -96,    83,    15,   -96,    64,    63,     8,
     -96,    67,   -96,    52,    -6,   -96,    21,    21,    90,   -96,
      67,   -96,    66,   -96,   -96,   -96,    67,    52,    68,    52,
      52,   -96,    50,   -96,   -19,   -11,   -96,   -96,    73,   -96,
      27,    52,    50,    50,   -96,   -96,   -96,    69,   -96,    34,
     -96,   -96,   -96
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     9,    10,     0,     0,     6,     3,     4,     5,    18,
      17,    16,    15,    11,     0,     0,    76,    14,     0,     0,
       0,    77,    52,    50,    51,    53,     0,    66,    23,    60,
      63,    64,    65,     0,    68,     1,     2,     0,    13,    38,
      34,     0,     0,     0,     0,    32,    58,    57,    59,    54,
      55,    56,     0,     0,     0,     0,     0,     0,    21,    77,
      34,    73,     0,    62,     0,    26,    24,    25,    61,    33,
      69,    67,     0,    42,     0,     0,    44,     0,    19,    70,
      35,     0,    22,     0,     0,    30,     0,     0,    34,    12,
       0,    47,     0,    49,    46,    39,     0,     0,     0,     0,
       0,    74,    75,    29,    28,     0,    36,    43,     0,    45,
       0,     0,    71,    72,    31,    27,    37,     0,    40,     0,
      20,    48,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -67,   -96,   -96,   -96,   -96,   -62,   -96,
     -96,   -96,   -96,   -96,   -96,    19,   -96,   -96,   -96,   -95,
     -35,   -96,   -96,   -96,   -96,   -96,    24,    -4,   -49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    55,    75,    76,    97,   125,    79,    98,    68,   126,
     130,    66,    88,    82,    85,    83,   104,    37,    62,    38,
      39,    40,    41,    42,    90,    70,    71,    43,    44
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    52,    72,    30,    53,    67,   124,    94,    92,    95,
      99,   100,   120,    23,    81,    84,    86,    95,    24,    78,
      47,    48,    95,    25,    49,    50,   129,    80,    26,   114,
     115,    96,    89,    28,   109,   110,   116,    91,    29,    96,
      45,    54,    72,   113,    96,    46,    56,    57,    58,    77,
       1,    84,     2,   -76,     3,     4,     5,   119,   112,     6,
      59,    60,    61,    26,   105,   106,     7,    63,     8,    74,
      77,    56,    57,    58,   122,   123,   128,    54,     9,    10,
      11,    12,    73,   132,    54,    59,    60,    61,    56,    57,
      58,    51,    77,    77,    31,    32,    33,    34,    35,    64,
      36,    65,    59,    60,    61,   101,   102,   103,    67,    69,
      87,    93,   107,   108,   118,   111,   121,   127,   131,   117
};

static const yytype_int8 yycheck[] =
{
       4,    36,    51,     7,    13,    18,    17,    74,    70,    28,
      49,    50,   107,     4,    63,    64,    65,    28,     6,    54,
      24,    25,    28,     6,    28,    29,   121,    62,    42,    96,
      97,    50,    67,    10,    26,    27,    98,    50,    13,    50,
       0,    50,    91,    49,    50,    47,    38,    39,    40,    53,
       3,   100,     5,    51,     7,     8,     9,   106,    93,    12,
      52,    53,    54,    42,    49,    50,    19,    51,    21,    48,
      74,    38,    39,    40,   109,   110,    49,    50,    31,    32,
      33,    34,    49,    49,    50,    52,    53,    54,    38,    39,
      40,    20,    96,    97,    42,    43,    44,    45,    46,    48,
      48,    48,    52,    53,    54,    22,    23,    24,    18,    42,
      11,    52,    48,    50,    48,    91,    48,    44,    49,   100
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    19,    21,    31,
      32,    33,    34,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     4,     6,     6,    42,    92,    10,    13,
      92,    42,    43,    44,    45,    46,    48,    82,    84,    85,
      86,    87,    88,    92,    93,     0,    47,    92,    92,    92,
      92,    20,    85,    13,    50,    66,    38,    39,    40,    52,
      53,    54,    83,    51,    48,    48,    76,    18,    73,    42,
      90,    91,    93,    49,    48,    67,    68,    92,    85,    71,
      85,    93,    78,    80,    93,    79,    93,    11,    77,    85,
      89,    50,    73,    52,    68,    28,    50,    69,    72,    49,
      50,    22,    23,    24,    81,    49,    50,    48,    50,    26,
      27,    91,    85,    49,    68,    68,    73,    80,    48,    93,
      84,    48,    85,    85,    17,    70,    74,    44,    49,    84,
      75,    49,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    57,    58,    58,    58,
      58,    59,    60,    60,    60,    61,    61,    61,    61,    62,
      63,    64,    65,    66,    66,    67,    68,    68,    68,    68,
      69,    70,    71,    72,    73,    73,    74,    75,    76,    76,
      77,    77,    78,    78,    79,    79,    80,    81,    81,    81,
      82,    82,    82,    82,    83,    83,    83,    83,    83,    83,
      84,    84,    85,    85,    85,    85,    86,    87,    87,    88,
      89,    89,    89,    90,    90,    91,    92,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     6,     3,     2,     1,     1,     1,     1,     5,
       8,     4,     5,     0,     2,     1,     1,     4,     3,     3,
       1,     1,     0,     0,     0,     2,     0,     0,     0,     3,
       4,     5,     1,     3,     1,     3,     2,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, std::shared_ptr<ast::TreeNode>& sql_result, void * scanner)
{
/* Lookahead token kind.  */
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
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  case 2: /* start: stmt ';'  */
#line 88 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        sql_result = std::move((yyvsp[-1].sv_node));
        YYACCEPT;
    }
#line 1679 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 7: /* txnStmt: TXN_BEGIN  */
#line 104 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1687 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 8: /* txnStmt: TXN_COMMIT  */
#line 108 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1695 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 9: /* txnStmt: TXN_ABORT  */
#line 112 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1703 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 10: /* txnStmt: TXN_ROLLBACK  */
#line 116 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1711 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 11: /* dbStmt: SHOW TABLES  */
#line 123 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1719 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 12: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 137 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1727 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 13: /* ddl: DROP TABLE tbName  */
#line 141 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1735 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 14: /* ddl: DESC tbName  */
#line 145 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1743 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 15: /* dml: update  */
#line 159 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
           {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1751 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 16: /* dml: delete  */
#line 162 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
             {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1759 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 17: /* dml: select  */
#line 165 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
             {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1767 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 18: /* dml: insert  */
#line 168 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
             {
        (yyval.sv_node) = std::move((yyvsp[0].sv_node));
    }
#line 1775 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 19: /* insert: INSERT INTO tbName optColumnClause insertList  */
#line 174 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                                                  {
        (yyval.sv_node) = std::make_shared<InsertNode>((yyvsp[-2].sv_str), (yyvsp[-1].sv_strs), (yyvsp[0].sv_expr_chunk));
    }
#line 1783 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 20: /* select: SELECT exprList optFromClause optGroupbyClause optHavingClause optWhereClause optOrderbyClause optLimitClause  */
#line 180 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                                                                                                                  {
        (yyval.sv_node) = std::make_shared<SelectNode>((yyvsp[-6].sv_exprs), (yyvsp[-5].sv_join), (yyvsp[-4].sv_exprs), (yyvsp[-3].sv_expr), (yyvsp[-2].sv_expr), (yyvsp[-1].sv_orderby), (yyvsp[0].sv_int));
    }
#line 1791 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 21: /* delete: DELETE FROM tbName optWhereClause  */
#line 186 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                                      {
        (yyval.sv_node) = std::make_shared<DeleteNode>((yyvsp[-1].sv_str), (yyvsp[0].sv_expr));
    }
#line 1799 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 22: /* update: UPDATE tbName SET setClauses optWhereClause  */
#line 192 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                                                {
        (yyval.sv_node) = std::make_shared<UpdateNode>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_expr));
    }
#line 1807 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 23: /* optFromClause: %empty  */
#line 198 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_join) = nullptr; }
#line 1813 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 24: /* optFromClause: FROM joinTree  */
#line 199 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                    {
        (yyval.sv_join) = std::move((yyvsp[0].sv_join));
    }
#line 1821 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 25: /* virtualTable: tbName  */
#line 205 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
           {
        (yyval.sv_vtable) = std::make_shared<VirtualTableNode>((yyvsp[0].sv_str), (yyvsp[0].sv_str));
    }
#line 1829 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 26: /* joinTree: virtualTable  */
#line 211 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                 {
        (yyval.sv_join) = std::make_shared<JoinNode>(std::move((yyvsp[0].sv_vtable)));
    }
#line 1837 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 27: /* joinTree: joinTree join_type joinTree onClause  */
#line 214 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                                           {
        (yyval.sv_join) = std::make_shared<JoinNode>(std::move((yyvsp[-3].sv_join)), std::move((yyvsp[-1].sv_join)), std::move((yyvsp[0].sv_expr)), (yyvsp[-2].sv_join_type));
    }
#line 1845 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 28: /* joinTree: joinTree ',' joinTree  */
#line 217 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                            {
        (yyval.sv_join) = std::make_shared<JoinNode>(std::move((yyvsp[-2].sv_join)), std::move((yyvsp[0].sv_join)), nullptr, common::JoinType::CARTESIAN_PRODUCT);
    }
#line 1853 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 29: /* joinTree: '(' joinTree ')'  */
#line 220 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                       {
        (yyval.sv_join) = std::move((yyvsp[-1].sv_join));
    }
#line 1861 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 30: /* join_type: JOIN  */
#line 226 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
         {
        (yyval.sv_join_type) = common::JoinType::INNER_JOIN;
    }
#line 1869 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 31: /* onClause: ON  */
#line 232 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
        {
        (yyval.sv_expr) = nullptr;
    }
#line 1877 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 32: /* optGroupbyClause: %empty  */
#line 239 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_exprs) = std::vector<std::shared_ptr<Expression>>(); }
#line 1883 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 33: /* optHavingClause: %empty  */
#line 242 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_expr) = nullptr; }
#line 1889 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 34: /* optWhereClause: %empty  */
#line 245 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_expr) = nullptr; }
#line 1895 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 35: /* optWhereClause: WHERE conjunctionExpr  */
#line 246 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                            {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
    }
#line 1903 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 36: /* optOrderbyClause: %empty  */
#line 252 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_orderby) = nullptr; }
#line 1909 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 37: /* optLimitClause: %empty  */
#line 255 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_int) = -1; }
#line 1915 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 38: /* optColumnClause: %empty  */
#line 258 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    { (yyval.sv_strs) = std::vector<std::string>(); }
#line 1921 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 39: /* optColumnClause: '(' colNameList ')'  */
#line 259 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                         {
        (yyval.sv_strs) = std::vector<std::string>();
        std::move((yyvsp[-1].sv_strs).begin(), (yyvsp[-1].sv_strs).end(), std::back_inserter((yyval.sv_strs)));
    }
#line 1930 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 40: /* insertList: VALUES '(' exprList ')'  */
#line 266 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                             {
        (yyval.sv_expr_chunk) = std::vector<std::vector<std::shared_ptr<Expression>>>();
        (yyval.sv_expr_chunk).push_back(std::move((yyvsp[-1].sv_exprs)));
    }
#line 1939 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 41: /* insertList: insertList ',' '(' exprList ')'  */
#line 269 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                                        {
        (yyval.sv_expr_chunk) = std::vector<std::vector<std::shared_ptr<Expression>>>();
        std::move((yyvsp[-4].sv_expr_chunk).begin(), (yyvsp[-4].sv_expr_chunk).end(), std::back_inserter((yyval.sv_expr_chunk)));
        (yyval.sv_expr_chunk).push_back(std::move((yyvsp[-1].sv_exprs)));
    }
#line 1949 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 42: /* fieldList: field  */
#line 278 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 1957 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 43: /* fieldList: fieldList ',' field  */
#line 282 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1965 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 44: /* colNameList: colName  */
#line 289 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1973 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 45: /* colNameList: colNameList ',' colName  */
#line 293 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1981 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 46: /* field: colName type  */
#line 300 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<Field>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 1989 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 47: /* type: INT  */
#line 307 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(AttrType::INTS, sizeof(int));
    }
#line 1997 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 48: /* type: CHAR '(' VALUE_INT ')'  */
#line 311 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(AttrType::CHARS, (yyvsp[-1].sv_int));
    }
#line 2005 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 49: /* type: FLOAT  */
#line 315 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(AttrType::FLOATS, sizeof(float));
    }
#line 2013 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 50: /* value: VALUE_INT  */
#line 333 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_int));
    }
#line 2021 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 51: /* value: VALUE_FLOAT  */
#line 337 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_float));
    }
#line 2029 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 52: /* value: VALUE_STRING  */
#line 341 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_str).c_str());
    }
#line 2037 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 53: /* value: VALUE_BOOL  */
#line 345 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<Value>((yyvsp[0].sv_bool));
    }
#line 2045 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 54: /* compOp: '='  */
#line 399 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
        { (yyval.sv_comp_op) = common::CompOp::EQ; }
#line 2051 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 55: /* compOp: '<'  */
#line 400 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::LT; }
#line 2057 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 56: /* compOp: '>'  */
#line 401 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::GT; }
#line 2063 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 57: /* compOp: NEQ  */
#line 402 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::NE; }
#line 2069 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 58: /* compOp: LEQ  */
#line 403 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::LE; }
#line 2075 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 59: /* compOp: GEQ  */
#line 404 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
          { (yyval.sv_comp_op) = common::CompOp::GE; }
#line 2081 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 60: /* exprList: expr  */
#line 408 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
         {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expression>>();
        (yyval.sv_exprs).push_back(std::move((yyvsp[0].sv_expr)));
    }
#line 2090 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 61: /* exprList: exprList ',' expr  */
#line 411 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                          {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expression>>();
        std::move((yyvsp[-2].sv_exprs).begin(), (yyvsp[-2].sv_exprs).end(), std::back_inserter((yyval.sv_exprs)));
        (yyval.sv_exprs).push_back(std::move((yyvsp[0].sv_expr)));
    }
#line 2100 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 62: /* expr: '(' expr ')'  */
#line 418 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                 {
        (yyval.sv_expr) = std::move((yyvsp[-1].sv_expr));
    }
#line 2108 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 63: /* expr: valueExpr  */
#line 421 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
    }
#line 2116 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 64: /* expr: unboundFieldExpr  */
#line 424 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                       {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
    }
#line 2124 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 65: /* expr: compExpr  */
#line 427 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
               {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
    }
#line 2132 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 66: /* valueExpr: value  */
#line 432 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
          {
        (yyval.sv_expr) = std::make_shared<ValueExpr>(*(yyvsp[0].sv_val));
    }
#line 2140 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 67: /* unboundFieldExpr: tbName '.' colName  */
#line 437 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                       {
        (yyval.sv_expr) = std::make_shared<UnboundFieldExpr>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2148 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 68: /* unboundFieldExpr: colName  */
#line 440 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
              {
        (yyval.sv_expr) = std::make_shared<UnboundFieldExpr>("", (yyvsp[0].sv_str));
    }
#line 2156 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 69: /* compExpr: expr compOp expr  */
#line 445 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                     {
        (yyval.sv_expr) = std::make_shared<ComparisonExpr>(std::move((yyvsp[-2].sv_expr)), std::move((yyvsp[0].sv_expr)), (yyvsp[-1].sv_comp_op));
    }
#line 2164 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 70: /* conjunctionExpr: expr  */
#line 450 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
         {
        (yyval.sv_expr) = std::move((yyvsp[0].sv_expr));
    }
#line 2172 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 71: /* conjunctionExpr: expr AND expr  */
#line 453 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                    {
        (yyval.sv_expr) = std::make_shared<ConjunctionExpr>(std::move((yyvsp[-2].sv_expr)), std::move((yyvsp[0].sv_expr)), common::ConjunctionType::AND);
    }
#line 2180 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 72: /* conjunctionExpr: expr OR expr  */
#line 456 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
                   {
        (yyval.sv_expr) = std::make_shared<ConjunctionExpr>(std::move((yyvsp[-2].sv_expr)), std::move((yyvsp[0].sv_expr)), common::ConjunctionType::OR);
    }
#line 2188 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 73: /* setClauses: setClause  */
#line 462 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2196 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 74: /* setClauses: setClauses ',' setClause  */
#line 466 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2204 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 75: /* setClause: colName '=' expr  */
#line 473 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_expr));
    }
#line 2212 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"
    break;


#line 2216 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 530 "/home/mhwwhu/db2024/rmdb/src/parser/yacc.y"


extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, std::shared_ptr<ast::TreeNode>& sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
