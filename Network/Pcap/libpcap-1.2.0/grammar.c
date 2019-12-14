/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammar.y" /* yacc.c:339  */

/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef lint
static const char rcsid[] _U_ =
    "@(#) $Header: /tcpdump/master/libpcap/grammar.y,v 1.101 2007-11-18 02:03:52 guy Exp $ (LBL)";
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32
#include <pcap-stdinc.h>
#else /* WIN32 */
#include <sys/types.h>
#include <sys/socket.h>
#endif /* WIN32 */

#include <stdlib.h>

#ifndef WIN32
#if __STDC__
struct mbuf;
struct rtentry;
#endif

#include <netinet/in.h>
#include <arpa/inet.h>
#endif /* WIN32 */

#include <stdio.h>

#include "pcap-int.h"

#include "gencode.h"
#ifdef HAVE_NET_PFVAR_H
#include <net/if.h>
#include <net/pfvar.h>
#include <net/if_pflog.h>
#endif
#include "ieee80211.h"
#include <pcap/namedb.h>

#ifdef HAVE_OS_PROTO_H
#include "os-proto.h"
#endif

#define QSET(q, p, d, a) (q).proto = (p),\
			 (q).dir = (d),\
			 (q).addr = (a)

struct tok {
	int v;			/* value */
	const char *s;		/* string */
};

static const struct tok ieee80211_types[] = {
	{ IEEE80211_FC0_TYPE_DATA, "data" },
	{ IEEE80211_FC0_TYPE_MGT, "mgt" },
	{ IEEE80211_FC0_TYPE_MGT, "management" },
	{ IEEE80211_FC0_TYPE_CTL, "ctl" },
	{ IEEE80211_FC0_TYPE_CTL, "control" },
	{ 0, NULL }
};
static const struct tok ieee80211_mgt_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assocreq" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assoc-req" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assocresp" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassocreq" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassoc-req" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassocresp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probereq" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probe-req" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "proberesp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "probe-resp" },
	{ IEEE80211_FC0_SUBTYPE_BEACON, "beacon" },
	{ IEEE80211_FC0_SUBTYPE_ATIM, "atim" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassoc" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassociation" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "auth" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "authentication" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauth" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauthentication" },
	{ 0, NULL }
};
static const struct tok ieee80211_ctl_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_PS_POLL, "ps-poll" },
	{ IEEE80211_FC0_SUBTYPE_RTS, "rts" },
	{ IEEE80211_FC0_SUBTYPE_CTS, "cts" },
	{ IEEE80211_FC0_SUBTYPE_ACK, "ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_END, "cf-end" },
	{ IEEE80211_FC0_SUBTYPE_CF_END_ACK, "cf-end-ack" },
	{ 0, NULL }
};
static const struct tok ieee80211_data_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_DATA, "data" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACK, "data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_POLL, "data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACPL, "data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_NODATA, "null" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACK, "cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "cf-poll"  },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_DATA, "qos-data" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACK, "qos-data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_POLL, "qos-data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACPL, "qos-data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA, "qos" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "qos-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "qos-cf-ack-poll" },
	{ 0, NULL }
};
struct type2tok {
	int type;
	const struct tok *tok;
};
static const struct type2tok ieee80211_type_subtypes[] = {
	{ IEEE80211_FC0_TYPE_MGT, ieee80211_mgt_subtypes },
	{ IEEE80211_FC0_TYPE_CTL, ieee80211_ctl_subtypes },
	{ IEEE80211_FC0_TYPE_DATA, ieee80211_data_subtypes },
	{ 0, NULL }
};

static int
str2tok(const char *str, const struct tok *toks)
{
	int i;

	for (i = 0; toks[i].s != NULL; i++) {
		if (pcap_strcasecmp(toks[i].s, str) == 0)
			return (toks[i].v);
	}
	return (-1);
}

int n_errors = 0;

static struct qual qerr = { Q_UNDEF, Q_UNDEF, Q_UNDEF, Q_UNDEF };

static void
yyerror(const char *msg)
{
	++n_errors;
	bpf_error("%s", msg);
	/* NOTREACHED */
}

#ifndef YYBISON
int yyparse(void);

int
pcap_parse()
{
	return (yyparse());
}
#endif

#ifdef HAVE_NET_PFVAR_H
static int
pfreason_to_num(const char *reason)
{
	const char *reasons[] = PFRES_NAMES;
	int i;

	for (i = 0; reasons[i]; i++) {
		if (pcap_strcasecmp(reason, reasons[i]) == 0)
			return (i);
	}
	bpf_error("unknown PF reason");
	/*NOTREACHED*/
}

static int
pfaction_to_num(const char *action)
{
	if (pcap_strcasecmp(action, "pass") == 0 ||
	    pcap_strcasecmp(action, "accept") == 0)
		return (PF_PASS);
	else if (pcap_strcasecmp(action, "drop") == 0 ||
		pcap_strcasecmp(action, "block") == 0)
		return (PF_DROP);
#if HAVE_PF_NAT_THROUGH_PF_NORDR
	else if (pcap_strcasecmp(action, "rdr") == 0)
		return (PF_RDR);
	else if (pcap_strcasecmp(action, "nat") == 0)
		return (PF_NAT);
	else if (pcap_strcasecmp(action, "binat") == 0)
		return (PF_BINAT);
	else if (pcap_strcasecmp(action, "nordr") == 0)
		return (PF_NORDR);
#endif
	else {
		bpf_error("unknown PF action");
		/*NOTREACHED*/
	}
}
#else /* !HAVE_NET_PFVAR_H */
static int
pfreason_to_num(const char *reason)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}

static int
pfaction_to_num(const char *action)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}
#endif /* HAVE_NET_PFVAR_H */

#line 307 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    DST = 258,
    SRC = 259,
    HOST = 260,
    GATEWAY = 261,
    NET = 262,
    NETMASK = 263,
    PORT = 264,
    PORTRANGE = 265,
    LESS = 266,
    GREATER = 267,
    PROTO = 268,
    PROTOCHAIN = 269,
    CBYTE = 270,
    ARP = 271,
    RARP = 272,
    IP = 273,
    SCTP = 274,
    TCP = 275,
    UDP = 276,
    ICMP = 277,
    IGMP = 278,
    IGRP = 279,
    PIM = 280,
    VRRP = 281,
    ATALK = 282,
    AARP = 283,
    DECNET = 284,
    LAT = 285,
    SCA = 286,
    MOPRC = 287,
    MOPDL = 288,
    TK_BROADCAST = 289,
    TK_MULTICAST = 290,
    NUM = 291,
    INBOUND = 292,
    OUTBOUND = 293,
    PF_IFNAME = 294,
    PF_RSET = 295,
    PF_RNR = 296,
    PF_SRNR = 297,
    PF_REASON = 298,
    PF_ACTION = 299,
    TYPE = 300,
    SUBTYPE = 301,
    DIR = 302,
    ADDR1 = 303,
    ADDR2 = 304,
    ADDR3 = 305,
    ADDR4 = 306,
    RA = 307,
    TA = 308,
    LINK = 309,
    GEQ = 310,
    LEQ = 311,
    NEQ = 312,
    ID = 313,
    EID = 314,
    HID = 315,
    HID6 = 316,
    AID = 317,
    LSH = 318,
    RSH = 319,
    LEN = 320,
    IPV6 = 321,
    ICMPV6 = 322,
    AH = 323,
    ESP = 324,
    VLAN = 325,
    MPLS = 326,
    PPPOED = 327,
    PPPOES = 328,
    ISO = 329,
    ESIS = 330,
    CLNP = 331,
    ISIS = 332,
    L1 = 333,
    L2 = 334,
    IIH = 335,
    LSP = 336,
    SNP = 337,
    CSNP = 338,
    PSNP = 339,
    STP = 340,
    IPX = 341,
    NETBEUI = 342,
    LANE = 343,
    LLC = 344,
    METAC = 345,
    BCC = 346,
    SC = 347,
    ILMIC = 348,
    OAMF4EC = 349,
    OAMF4SC = 350,
    OAM = 351,
    OAMF4 = 352,
    CONNECTMSG = 353,
    METACONNECT = 354,
    VPI = 355,
    VCI = 356,
    RADIO = 357,
    FISU = 358,
    LSSU = 359,
    MSU = 360,
    SIO = 361,
    OPC = 362,
    DPC = 363,
    SLS = 364,
    OR = 365,
    AND = 366,
    UMINUS = 367
  };
#endif
/* Tokens.  */
#define DST 258
#define SRC 259
#define HOST 260
#define GATEWAY 261
#define NET 262
#define NETMASK 263
#define PORT 264
#define PORTRANGE 265
#define LESS 266
#define GREATER 267
#define PROTO 268
#define PROTOCHAIN 269
#define CBYTE 270
#define ARP 271
#define RARP 272
#define IP 273
#define SCTP 274
#define TCP 275
#define UDP 276
#define ICMP 277
#define IGMP 278
#define IGRP 279
#define PIM 280
#define VRRP 281
#define ATALK 282
#define AARP 283
#define DECNET 284
#define LAT 285
#define SCA 286
#define MOPRC 287
#define MOPDL 288
#define TK_BROADCAST 289
#define TK_MULTICAST 290
#define NUM 291
#define INBOUND 292
#define OUTBOUND 293
#define PF_IFNAME 294
#define PF_RSET 295
#define PF_RNR 296
#define PF_SRNR 297
#define PF_REASON 298
#define PF_ACTION 299
#define TYPE 300
#define SUBTYPE 301
#define DIR 302
#define ADDR1 303
#define ADDR2 304
#define ADDR3 305
#define ADDR4 306
#define RA 307
#define TA 308
#define LINK 309
#define GEQ 310
#define LEQ 311
#define NEQ 312
#define ID 313
#define EID 314
#define HID 315
#define HID6 316
#define AID 317
#define LSH 318
#define RSH 319
#define LEN 320
#define IPV6 321
#define ICMPV6 322
#define AH 323
#define ESP 324
#define VLAN 325
#define MPLS 326
#define PPPOED 327
#define PPPOES 328
#define ISO 329
#define ESIS 330
#define CLNP 331
#define ISIS 332
#define L1 333
#define L2 334
#define IIH 335
#define LSP 336
#define SNP 337
#define CSNP 338
#define PSNP 339
#define STP 340
#define IPX 341
#define NETBEUI 342
#define LANE 343
#define LLC 344
#define METAC 345
#define BCC 346
#define SC 347
#define ILMIC 348
#define OAMF4EC 349
#define OAMF4SC 350
#define OAM 351
#define OAMF4 352
#define CONNECTMSG 353
#define METACONNECT 354
#define VPI 355
#define VCI 356
#define RADIO 357
#define FISU 358
#define LSSU 359
#define MSU 360
#define SIO 361
#define OPC 362
#define DPC 363
#define SLS 364
#define OR 365
#define AND 366
#define UMINUS 367

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 242 "grammar.y" /* yacc.c:355  */

	int i;
	bpf_u_int32 h;
	u_char *e;
	char *s;
	struct stmt *stmt;
	struct arth *a;
	struct {
		struct qual q;
		int atmfieldtype;
		int mtp3fieldtype;
		struct block *b;
	} blk;
	struct block *rblk;

#line 587 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 604 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   695

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  204
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  276

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   367

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   112,     2,     2,     2,     2,   114,     2,
     121,   120,   117,   115,     2,   116,     2,   118,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   127,     2,
     124,   123,   122,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   125,     2,   126,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   113,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   119
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   315,   315,   319,   321,   323,   324,   325,   326,   327,
     329,   331,   333,   334,   336,   338,   339,   341,   343,   356,
     365,   374,   383,   392,   394,   396,   398,   399,   400,   402,
     404,   406,   407,   409,   410,   411,   412,   413,   414,   416,
     417,   418,   419,   421,   423,   424,   425,   426,   427,   428,
     431,   432,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   449,   450,   451,   452,   455,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   513,   514,   515,   516,   517,   518,   521,   526,
     529,   533,   536,   537,   543,   544,   564,   580,   581,   594,
     595,   598,   601,   602,   603,   605,   606,   607,   609,   610,
     612,   613,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   626,   627,   628,   629,   630,   632,   633,
     635,   636,   637,   638,   639,   640,   641,   642,   644,   645,
     646,   647,   650,   651,   653,   654,   655,   656,   658,   665,
     666,   669,   670,   671,   674,   675,   676,   677,   679,   680,
     681,   682,   684,   693,   694
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DST", "SRC", "HOST", "GATEWAY", "NET",
  "NETMASK", "PORT", "PORTRANGE", "LESS", "GREATER", "PROTO", "PROTOCHAIN",
  "CBYTE", "ARP", "RARP", "IP", "SCTP", "TCP", "UDP", "ICMP", "IGMP",
  "IGRP", "PIM", "VRRP", "ATALK", "AARP", "DECNET", "LAT", "SCA", "MOPRC",
  "MOPDL", "TK_BROADCAST", "TK_MULTICAST", "NUM", "INBOUND", "OUTBOUND",
  "PF_IFNAME", "PF_RSET", "PF_RNR", "PF_SRNR", "PF_REASON", "PF_ACTION",
  "TYPE", "SUBTYPE", "DIR", "ADDR1", "ADDR2", "ADDR3", "ADDR4", "RA", "TA",
  "LINK", "GEQ", "LEQ", "NEQ", "ID", "EID", "HID", "HID6", "AID", "LSH",
  "RSH", "LEN", "IPV6", "ICMPV6", "AH", "ESP", "VLAN", "MPLS", "PPPOED",
  "PPPOES", "ISO", "ESIS", "CLNP", "ISIS", "L1", "L2", "IIH", "LSP", "SNP",
  "CSNP", "PSNP", "STP", "IPX", "NETBEUI", "LANE", "LLC", "METAC", "BCC",
  "SC", "ILMIC", "OAMF4EC", "OAMF4SC", "OAM", "OAMF4", "CONNECTMSG",
  "METACONNECT", "VPI", "VCI", "RADIO", "FISU", "LSSU", "MSU", "SIO",
  "OPC", "DPC", "SLS", "OR", "AND", "'!'", "'|'", "'&'", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "')'", "'('", "'>'", "'='", "'<'", "'['", "']'",
  "':'", "$accept", "prog", "null", "expr", "and", "or", "id", "nid",
  "not", "paren", "pid", "qid", "term", "head", "rterm", "pqual", "dqual",
  "aqual", "ndaqual", "pname", "other", "pfvar", "p80211", "type",
  "subtype", "type_subtype", "dir", "reason", "action", "relop", "irelop",
  "arth", "narth", "byteop", "pnum", "atmtype", "atmmultitype", "atmfield",
  "atmvalue", "atmfieldvalue", "atmlistvalue", "mtp2type", "mtp3field",
  "mtp3value", "mtp3fieldvalue", "mtp3listvalue", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,    33,   124,    38,    43,    45,    42,    47,   367,
      41,    40,    62,    61,    60,    91,    93,    58
};
# endif

#define YYPACT_NINF -197

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-197)))

#define YYTABLE_NINF -42

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -197,    14,   218,  -197,   -17,   -11,    23,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,     4,    13,
      48,    52,   -21,    37,  -197,  -197,  -197,  -197,  -197,  -197,
     -24,   -24,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,   538,  -197,   -67,   432,   432,  -197,   152,  -197,   642,
      11,  -197,  -197,   520,  -197,  -197,  -197,  -197,   -15,  -197,
     101,  -197,  -197,   -59,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,   -24,  -197,  -197,   538,   -10,  -197,  -197,
    -197,   325,   325,  -197,   -54,    -8,    -4,  -197,  -197,     0,
       6,  -197,  -197,  -197,   152,   152,  -197,   -43,   -31,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,   -12,    72,
      -7,  -197,  -197,  -197,  -197,  -197,  -197,   165,  -197,  -197,
    -197,   538,  -197,  -197,  -197,   538,   538,   538,   538,   538,
     538,   538,   538,  -197,  -197,  -197,   538,   538,  -197,    74,
     105,   114,  -197,  -197,  -197,   115,   116,   119,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,   123,    -4,   -41,  -197,   325,
     325,  -197,     3,  -197,  -197,  -197,  -197,  -197,   100,   125,
     126,  -197,  -197,    43,   -67,    -4,   162,   167,   164,   170,
    -197,  -197,   130,  -197,  -197,  -197,  -197,  -197,  -197,    76,
     -13,   -13,   153,   163,    17,    17,  -197,  -197,   -41,   -41,
    -197,   -93,  -197,  -197,  -197,   -90,  -197,  -197,  -197,   -50,
    -197,  -197,  -197,  -197,   152,   152,  -197,  -197,  -197,  -197,
      -5,  -197,   141,  -197,    74,  -197,   115,  -197,  -197,  -197,
    -197,  -197,    53,  -197,  -197,  -197
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    51,     1,     0,     0,     0,    71,    72,    70,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    87,    86,   168,   112,   113,     0,     0,
       0,     0,     0,     0,    69,   162,    88,    89,    90,    91,
     115,   117,   118,   119,    92,    93,   102,    94,    95,    96,
      97,    98,    99,   101,   100,   103,   104,   105,   170,   171,
     172,   173,   176,   177,   174,   175,   178,   179,   180,   181,
     182,   183,   106,   191,   192,   193,   194,   195,   196,   197,
      24,     0,    25,     2,    51,    51,     5,     0,    31,     0,
      50,    44,   120,     0,   149,   148,    45,    46,     0,    48,
       0,   109,   110,     0,   122,   123,   124,   125,   139,   140,
     126,   141,   127,     0,   114,   116,     0,     0,   160,    11,
      10,    51,    51,    32,     0,   149,   148,    15,    21,    18,
      20,    22,    39,    12,     0,     0,    13,    53,    52,    64,
      68,    65,    66,    67,    36,    37,   107,   108,     0,     0,
       0,    58,    59,    60,    61,    62,    63,    34,    35,    38,
     121,     0,   143,   145,   147,     0,     0,     0,     0,     0,
       0,     0,     0,   142,   144,   146,     0,     0,   188,     0,
       0,     0,    47,   184,   202,     0,     0,     0,    49,   198,
     164,   163,   166,   167,   165,     0,     0,     0,     7,    51,
      51,     6,   148,     9,     8,    40,   161,   169,     0,     0,
       0,    23,    26,    30,     0,    29,     0,     0,     0,     0,
     132,   133,   129,   136,   130,   137,   138,   131,    33,     0,
     158,   159,   157,   156,   152,   153,   154,   155,    42,    43,
     189,     0,   185,   186,   203,     0,   199,   200,   111,   148,
      17,    16,    19,    14,     0,     0,    55,    57,    54,    56,
       0,   150,     0,   187,     0,   201,     0,    27,    28,   134,
     135,   128,     0,   190,   204,   151
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -197,  -197,  -197,   176,   -34,  -196,   -86,  -131,     5,    -2,
    -197,  -197,   -74,  -197,  -197,  -197,  -197,    24,  -197,     7,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,   -72,
     -66,   -23,   -83,  -197,   -35,  -197,  -197,  -197,  -197,  -163,
    -197,  -197,  -197,  -197,  -172,  -197
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   124,   121,   122,   211,   133,   134,   116,
     213,   214,    86,    87,    88,    89,   157,   158,   159,   117,
      91,    92,   160,   222,   271,   224,   227,   110,   112,   176,
     177,    93,    94,   195,    95,    96,    97,    98,   182,   183,
     241,    99,   100,   188,   189,   245
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      85,   132,   125,   -13,   212,   114,   115,    84,   208,    90,
     123,   -41,    25,   244,     3,   108,   240,   119,   255,   101,
     119,   178,   165,   166,   220,   102,   180,   263,   186,   225,
     265,   269,   181,   125,   187,   198,   203,   109,   113,   113,
     162,   163,   164,   119,   120,   264,   221,   201,   204,   266,
     126,   226,   136,   270,   190,   191,   119,   120,   118,   103,
     -29,   -29,   104,   192,   193,   194,   205,   216,   217,   212,
     207,   105,   167,   168,   169,   170,   171,   172,   196,   218,
     219,   126,    85,    85,   106,   135,   202,   202,   107,    84,
      84,    90,    90,   197,   274,   111,   179,    82,   185,   136,
     215,   273,   169,   170,   171,   172,    82,   173,   174,   175,
     178,   113,   206,   -13,   -13,   161,   207,   125,   209,   200,
     200,   -41,   -41,   -13,   210,   123,   199,   199,    90,    90,
     223,   -41,   135,   113,   171,   172,   161,   184,   229,   165,
     166,   242,   230,   231,   232,   233,   234,   235,   236,   237,
     243,   184,   246,   238,   239,   247,   162,   163,   164,   248,
     250,   251,   252,   253,   202,   249,   256,   258,   267,   268,
     139,   257,   141,   259,   142,   143,   260,   272,    83,   275,
     254,   228,     0,     0,     0,     0,     0,     0,    25,   167,
     168,   169,   170,   171,   172,     0,     0,   200,    85,     0,
       0,     0,   261,   262,   199,   199,    90,    90,     0,     0,
     127,   128,   129,   130,   131,     0,   165,   166,    -3,   136,
     136,     0,    82,   173,   174,   175,   165,   166,     0,     4,
       5,     0,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,   135,   135,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,    80,     0,     0,   168,   169,   170,
     171,   172,    34,    82,     0,     0,     0,     0,   169,   170,
     171,   172,     0,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,     0,     0,
      80,     0,     0,     0,    81,     0,     4,     5,     0,    82,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
       0,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,     0,   127,   128,   129,   130,   131,     0,     0,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,     0,     0,    80,     0,     0,
       0,    81,     0,     4,     5,     0,    82,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,     0,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,     0,     0,    80,     0,     0,     0,    81,     0,
       0,     0,     0,    82,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,     0,    25,   162,   163,   164,     0,     0,
       0,     0,     0,   165,   166,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    36,    37,    38,    39,     0,     0,
       0,     0,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,   167,   168,   169,   170,   171,   172,     0,
      72,     0,   173,   174,   175,   137,   138,   139,   140,   141,
       0,   142,   143,     0,    81,   144,   145,     0,     0,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   146,   147,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156
};

static const yytype_int16 yycheck[] =
{
       2,    87,    85,     0,   135,    40,    41,     2,     8,     2,
      84,     0,    36,   185,     0,    36,   179,   110,   214,    36,
     110,    36,    63,    64,    36,    36,    98,   120,   100,    36,
     120,    36,    98,   116,   100,   121,   122,    58,    40,    41,
      55,    56,    57,   110,   111,   241,    58,   121,   122,   245,
      85,    58,    87,    58,   113,   114,   110,   111,    81,    36,
     110,   111,    58,   122,   123,   124,   120,   110,   111,   200,
     120,    58,   113,   114,   115,   116,   117,   118,   113,   110,
     111,   116,    84,    85,    36,    87,   121,   122,    36,    84,
      85,    84,    85,   116,   266,    58,    98,   121,   100,   134,
     135,   264,   115,   116,   117,   118,   121,   122,   123,   124,
      36,   113,   120,   110,   111,   125,   120,   200,   118,   121,
     122,   110,   111,   120,   118,   199,   121,   122,   121,   122,
      58,   120,   134,   135,   117,   118,   125,    36,   161,    63,
      64,    36,   165,   166,   167,   168,   169,   170,   171,   172,
      36,    36,    36,   176,   177,    36,    55,    56,    57,    36,
      60,    36,    36,   120,   199,   200,     4,     3,   254,   255,
       5,     4,     7,     3,     9,    10,    46,    36,     2,   126,
     214,   157,    -1,    -1,    -1,    -1,    -1,    -1,    36,   113,
     114,   115,   116,   117,   118,    -1,    -1,   199,   200,    -1,
      -1,    -1,   126,   127,   199,   200,   199,   200,    -1,    -1,
      58,    59,    60,    61,    62,    -1,    63,    64,     0,   254,
     255,    -1,   121,   122,   123,   124,    63,    64,    -1,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   254,   255,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,   112,    -1,    -1,   114,   115,   116,
     117,   118,    54,   121,    -1,    -1,    -1,    -1,   115,   116,
     117,   118,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    -1,    -1,
     112,    -1,    -1,    -1,   116,    -1,    11,    12,    -1,   121,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,   112,    -1,    -1,
      -1,   116,    -1,    11,    12,    -1,   121,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    -1,    -1,   112,    -1,    -1,    -1,   116,    -1,
      -1,    -1,    -1,   121,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    -1,    -1,    36,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,    -1,
     102,    -1,   122,   123,   124,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,   116,    13,    14,    -1,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   129,   130,     0,    11,    12,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    54,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     112,   116,   121,   131,   136,   137,   140,   141,   142,   143,
     147,   148,   149,   159,   160,   162,   163,   164,   165,   169,
     170,    36,    36,    36,    58,    58,    36,    36,    36,    58,
     155,    58,   156,   137,   162,   162,   137,   147,   159,   110,
     111,   132,   133,   140,   131,   160,   162,    58,    59,    60,
      61,    62,   134,   135,   136,   137,   162,     3,     4,     5,
       6,     7,     9,    10,    13,    14,    34,    35,    45,    46,
      47,    48,    49,    50,    51,    52,    53,   144,   145,   146,
     150,   125,    55,    56,    57,    63,    64,   113,   114,   115,
     116,   117,   118,   122,   123,   124,   157,   158,    36,   137,
     157,   158,   166,   167,    36,   137,   157,   158,   171,   172,
     113,   114,   122,   123,   124,   161,   162,   159,   134,   136,
     137,   140,   162,   134,   140,   120,   120,   120,     8,   118,
     118,   134,   135,   138,   139,   162,   110,   111,   110,   111,
      36,    58,   151,    58,   153,    36,    58,   154,   145,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     167,   168,    36,    36,   172,   173,    36,    36,    36,   162,
      60,    36,    36,   120,   132,   133,     4,     4,     3,     3,
      46,   126,   127,   120,   133,   120,   133,   134,   134,    36,
      58,   152,    36,   167,   172,   126
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   128,   129,   129,   130,   131,   131,   131,   131,   131,
     132,   133,   134,   134,   134,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   136,   137,   138,   138,   138,   139,
     139,   140,   140,   141,   141,   141,   141,   141,   141,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     143,   143,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   145,   145,   145,   145,   146,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   149,   149,   149,   149,   149,   149,   150,   150,
     150,   150,   151,   151,   152,   152,   153,   154,   154,   155,
     155,   156,   157,   157,   157,   158,   158,   158,   159,   159,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   161,   161,   161,   161,   161,   162,   162,
     163,   163,   163,   163,   163,   163,   163,   163,   164,   164,
     164,   164,   165,   165,   166,   166,   166,   166,   167,   168,
     168,   169,   169,   169,   170,   170,   170,   170,   171,   171,
     171,   171,   172,   173,   173
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     1,     3,     3,     1,     3,
       1,     1,     1,     2,     1,     1,     1,     3,     3,     1,
       1,     1,     2,     3,     2,     2,     2,     2,     2,     2,
       3,     1,     3,     3,     1,     1,     1,     2,     1,     2,
       1,     0,     1,     1,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     4,     1,     1,     2,     1,     2,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     4,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     6,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 316 "grammar.y" /* yacc.c:1646  */
    {
	finish_parse((yyvsp[0].blk).b);
}
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 321 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).q = qerr; }
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 324 "grammar.y" /* yacc.c:1646  */
    { gen_and((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 325 "grammar.y" /* yacc.c:1646  */
    { gen_and((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 326 "grammar.y" /* yacc.c:1646  */
    { gen_or((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 327 "grammar.y" /* yacc.c:1646  */
    { gen_or((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 329 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk) = (yyvsp[-1].blk); }
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 331 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk) = (yyvsp[-1].blk); }
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 334 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_ncode(NULL, (bpf_u_int32)(yyvsp[0].i),
						   (yyval.blk).q = (yyvsp[-1].blk).q); }
#line 2050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 336 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk) = (yyvsp[-1].blk); }
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 338 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_scode((yyvsp[0].s), (yyval.blk).q = (yyvsp[-1].blk).q); }
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 339 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_mcode((yyvsp[-2].s), NULL, (yyvsp[0].i),
				    (yyval.blk).q = (yyvsp[-3].blk).q); }
#line 2069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 341 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_mcode((yyvsp[-2].s), (yyvsp[0].s), 0,
				    (yyval.blk).q = (yyvsp[-3].blk).q); }
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 343 "grammar.y" /* yacc.c:1646  */
    {
				  /* Decide how to parse HID based on proto */
				  (yyval.blk).q = (yyvsp[-1].blk).q;
				  if ((yyval.blk).q.addr == Q_PORT)
				  	bpf_error("'port' modifier applied to ip host");
				  else if ((yyval.blk).q.addr == Q_PORTRANGE)
				  	bpf_error("'portrange' modifier applied to ip host");
				  else if ((yyval.blk).q.addr == Q_PROTO)
				  	bpf_error("'proto' modifier applied to ip host");
				  else if ((yyval.blk).q.addr == Q_PROTOCHAIN)
				  	bpf_error("'protochain' modifier applied to ip host");
				  (yyval.blk).b = gen_ncode((yyvsp[0].s), 0, (yyval.blk).q);
				}
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 356 "grammar.y" /* yacc.c:1646  */
    {
#ifdef INET6
				  (yyval.blk).b = gen_mcode6((yyvsp[-2].s), NULL, (yyvsp[0].i),
				    (yyval.blk).q = (yyvsp[-3].blk).q);
#else
				  bpf_error("'ip6addr/prefixlen' not supported "
					"in this configuration");
#endif /*INET6*/
				}
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 365 "grammar.y" /* yacc.c:1646  */
    {
#ifdef INET6
				  (yyval.blk).b = gen_mcode6((yyvsp[0].s), 0, 128,
				    (yyval.blk).q = (yyvsp[-1].blk).q);
#else
				  bpf_error("'ip6addr' not supported "
					"in this configuration");
#endif /*INET6*/
				}
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 374 "grammar.y" /* yacc.c:1646  */
    { 
				  (yyval.blk).b = gen_ecode((yyvsp[0].e), (yyval.blk).q = (yyvsp[-1].blk).q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free((yyvsp[0].e));
				}
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 383 "grammar.y" /* yacc.c:1646  */
    {
				  (yyval.blk).b = gen_acode((yyvsp[0].e), (yyval.blk).q = (yyvsp[-1].blk).q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free((yyvsp[0].e));
				}
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 392 "grammar.y" /* yacc.c:1646  */
    { gen_not((yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 394 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk) = (yyvsp[-1].blk); }
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 396 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk) = (yyvsp[-1].blk); }
#line 2168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 399 "grammar.y" /* yacc.c:1646  */
    { gen_and((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2174 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 400 "grammar.y" /* yacc.c:1646  */
    { gen_or((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 402 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_ncode(NULL, (bpf_u_int32)(yyvsp[0].i),
						   (yyval.blk).q = (yyvsp[-1].blk).q); }
#line 2187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 407 "grammar.y" /* yacc.c:1646  */
    { gen_not((yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 2193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 409 "grammar.y" /* yacc.c:1646  */
    { QSET((yyval.blk).q, (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i)); }
#line 2199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 410 "grammar.y" /* yacc.c:1646  */
    { QSET((yyval.blk).q, (yyvsp[-1].i), (yyvsp[0].i), Q_DEFAULT); }
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 411 "grammar.y" /* yacc.c:1646  */
    { QSET((yyval.blk).q, (yyvsp[-1].i), Q_DEFAULT, (yyvsp[0].i)); }
#line 2211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 412 "grammar.y" /* yacc.c:1646  */
    { QSET((yyval.blk).q, (yyvsp[-1].i), Q_DEFAULT, Q_PROTO); }
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 413 "grammar.y" /* yacc.c:1646  */
    { QSET((yyval.blk).q, (yyvsp[-1].i), Q_DEFAULT, Q_PROTOCHAIN); }
#line 2223 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 414 "grammar.y" /* yacc.c:1646  */
    { QSET((yyval.blk).q, (yyvsp[-1].i), Q_DEFAULT, (yyvsp[0].i)); }
#line 2229 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 416 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk) = (yyvsp[0].blk); }
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 417 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = (yyvsp[-1].blk).b; (yyval.blk).q = (yyvsp[-2].blk).q; }
#line 2241 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 418 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_proto_abbrev((yyvsp[0].i)); (yyval.blk).q = qerr; }
#line 2247 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 419 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_relation((yyvsp[-1].i), (yyvsp[-2].a), (yyvsp[0].a), 0);
				  (yyval.blk).q = qerr; }
#line 2254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 421 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_relation((yyvsp[-1].i), (yyvsp[-2].a), (yyvsp[0].a), 1);
				  (yyval.blk).q = qerr; }
#line 2261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 423 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = (yyvsp[0].rblk); (yyval.blk).q = qerr; }
#line 2267 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 424 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_atmtype_abbrev((yyvsp[0].i)); (yyval.blk).q = qerr; }
#line 2273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 425 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_atmmulti_abbrev((yyvsp[0].i)); (yyval.blk).q = qerr; }
#line 2279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 426 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = (yyvsp[0].blk).b; (yyval.blk).q = qerr; }
#line 2285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 427 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_mtp2type_abbrev((yyvsp[0].i)); (yyval.blk).q = qerr; }
#line 2291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 428 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = (yyvsp[0].blk).b; (yyval.blk).q = qerr; }
#line 2297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 432 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_DEFAULT; }
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 435 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_SRC; }
#line 2309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 436 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_DST; }
#line 2315 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 437 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_OR; }
#line 2321 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 438 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_OR; }
#line 2327 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 439 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_AND; }
#line 2333 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 440 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_AND; }
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 441 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ADDR1; }
#line 2345 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 442 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ADDR2; }
#line 2351 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 443 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ADDR3; }
#line 2357 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 444 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ADDR4; }
#line 2363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 445 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_RA; }
#line 2369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 446 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_TA; }
#line 2375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 449 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_HOST; }
#line 2381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 450 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_NET; }
#line 2387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 451 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_PORT; }
#line 2393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 452 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_PORTRANGE; }
#line 2399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 455 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_GATEWAY; }
#line 2405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 457 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_LINK; }
#line 2411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 458 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_IP; }
#line 2417 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 459 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ARP; }
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 460 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_RARP; }
#line 2429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 461 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_SCTP; }
#line 2435 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 462 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_TCP; }
#line 2441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 463 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_UDP; }
#line 2447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 464 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ICMP; }
#line 2453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 465 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_IGMP; }
#line 2459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 466 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_IGRP; }
#line 2465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 467 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_PIM; }
#line 2471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 468 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_VRRP; }
#line 2477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 469 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ATALK; }
#line 2483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 470 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_AARP; }
#line 2489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 471 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_DECNET; }
#line 2495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 472 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_LAT; }
#line 2501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 473 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_SCA; }
#line 2507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 474 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_MOPDL; }
#line 2513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 475 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_MOPRC; }
#line 2519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 476 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_IPV6; }
#line 2525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 477 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ICMPV6; }
#line 2531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 478 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_AH; }
#line 2537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 479 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ESP; }
#line 2543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 480 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISO; }
#line 2549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 481 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ESIS; }
#line 2555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 482 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS; }
#line 2561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 483 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS_L1; }
#line 2567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 484 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS_L2; }
#line 2573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 485 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS_IIH; }
#line 2579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 486 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS_LSP; }
#line 2585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 487 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS_SNP; }
#line 2591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 488 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS_PSNP; }
#line 2597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 489 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_ISIS_CSNP; }
#line 2603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 490 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_CLNP; }
#line 2609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 491 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_STP; }
#line 2615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 492 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_IPX; }
#line 2621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 493 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_NETBEUI; }
#line 2627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 494 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = Q_RADIO; }
#line 2633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 496 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_broadcast((yyvsp[-1].i)); }
#line 2639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 497 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_multicast((yyvsp[-1].i)); }
#line 2645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 498 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_less((yyvsp[0].i)); }
#line 2651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 499 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_greater((yyvsp[0].i)); }
#line 2657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 500 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_byteop((yyvsp[-1].i), (yyvsp[-2].i), (yyvsp[0].i)); }
#line 2663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 501 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_inbound(0); }
#line 2669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 502 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_inbound(1); }
#line 2675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 503 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_vlan((yyvsp[0].i)); }
#line 2681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 504 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_vlan(-1); }
#line 2687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 505 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_mpls((yyvsp[0].i)); }
#line 2693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 506 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_mpls(-1); }
#line 2699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 507 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pppoed(); }
#line 2705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 508 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pppoes(); }
#line 2711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 509 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = (yyvsp[0].rblk); }
#line 2717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 510 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = (yyvsp[0].rblk); }
#line 2723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 513 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pf_ifname((yyvsp[0].s)); }
#line 2729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 514 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pf_ruleset((yyvsp[0].s)); }
#line 2735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 515 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pf_rnr((yyvsp[0].i)); }
#line 2741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 516 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pf_srnr((yyvsp[0].i)); }
#line 2747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 517 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pf_reason((yyvsp[0].i)); }
#line 2753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 518 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_pf_action((yyvsp[0].i)); }
#line 2759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 522 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_p80211_type((yyvsp[-2].i) | (yyvsp[0].i),
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				}
#line 2768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 526 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_p80211_type((yyvsp[0].i),
					IEEE80211_FC0_TYPE_MASK);
				}
#line 2776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 529 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_p80211_type((yyvsp[0].i),
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				}
#line 2785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 533 "grammar.y" /* yacc.c:1646  */
    { (yyval.rblk) = gen_p80211_fcdir((yyvsp[0].i)); }
#line 2791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 537 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = str2tok((yyvsp[0].s), ieee80211_types);
				  if ((yyval.i) == -1)
				  	bpf_error("unknown 802.11 type name");
				}
#line 2800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 544 "grammar.y" /* yacc.c:1646  */
    { const struct tok *types = NULL;
				  int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type");
						break;
					}
					if ((yyvsp[(-1) - (1)].i) == ieee80211_type_subtypes[i].type) {
						types = ieee80211_type_subtypes[i].tok;
						break;
					}
				  }

				  (yyval.i) = str2tok((yyvsp[0].s), types);
				  if ((yyval.i) == -1)
					bpf_error("unknown 802.11 subtype name");
				}
#line 2823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 564 "grammar.y" /* yacc.c:1646  */
    { int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type name");
						break;
					}
					(yyval.i) = str2tok((yyvsp[0].s), ieee80211_type_subtypes[i].tok);
					if ((yyval.i) != -1) {
						(yyval.i) |= ieee80211_type_subtypes[i].type;
						break;
					}
				  }
				}
#line 2842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 581 "grammar.y" /* yacc.c:1646  */
    { if (pcap_strcasecmp((yyvsp[0].s), "nods") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_NODS;
				  else if (pcap_strcasecmp((yyvsp[0].s), "tods") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_TODS;
				  else if (pcap_strcasecmp((yyvsp[0].s), "fromds") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_FROMDS;
				  else if (pcap_strcasecmp((yyvsp[0].s), "dstods") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_DSTODS;
				  else
					bpf_error("unknown 802.11 direction");
				}
#line 2858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 594 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = (yyvsp[0].i); }
#line 2864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 595 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = pfreason_to_num((yyvsp[0].s)); }
#line 2870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 598 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = pfaction_to_num((yyvsp[0].s)); }
#line 2876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 601 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = BPF_JGT; }
#line 2882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 602 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = BPF_JGE; }
#line 2888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 603 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = BPF_JEQ; }
#line 2894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 605 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = BPF_JGT; }
#line 2900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 606 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = BPF_JGE; }
#line 2906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 607 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = BPF_JEQ; }
#line 2912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 609 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_loadi((yyvsp[0].i)); }
#line 2918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 612 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_load((yyvsp[-3].i), (yyvsp[-1].a), 1); }
#line 2924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 613 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_load((yyvsp[-5].i), (yyvsp[-3].a), (yyvsp[-1].i)); }
#line 2930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 614 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_ADD, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 615 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_SUB, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 616 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_MUL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 617 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_DIV, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 618 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_AND, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 619 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_OR, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 620 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_LSH, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 621 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_arth(BPF_RSH, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2978 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 622 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_neg((yyvsp[0].a)); }
#line 2984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 623 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = (yyvsp[-1].a); }
#line 2990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 624 "grammar.y" /* yacc.c:1646  */
    { (yyval.a) = gen_loadlen(); }
#line 2996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 626 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = '&'; }
#line 3002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 627 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = '|'; }
#line 3008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 628 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = '<'; }
#line 3014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 629 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = '>'; }
#line 3020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 630 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = '='; }
#line 3026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 633 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = (yyvsp[-1].i); }
#line 3032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 635 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_LANE; }
#line 3038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 636 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_LLC; }
#line 3044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 637 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_METAC;	}
#line 3050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 638 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_BCC; }
#line 3056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 639 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_OAMF4EC; }
#line 3062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 640 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_OAMF4SC; }
#line 3068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 641 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_SC; }
#line 3074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 642 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_ILMIC; }
#line 3080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 644 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_OAM; }
#line 3086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 645 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_OAMF4; }
#line 3092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 646 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_CONNECTMSG; }
#line 3098 "y.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 647 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = A_METACONNECT; }
#line 3104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 650 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).atmfieldtype = A_VPI; }
#line 3110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 651 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).atmfieldtype = A_VCI; }
#line 3116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 654 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_atmfield_code((yyvsp[-2].blk).atmfieldtype, (bpf_int32)(yyvsp[0].i), (bpf_u_int32)(yyvsp[-1].i), 0); }
#line 3122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 655 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_atmfield_code((yyvsp[-2].blk).atmfieldtype, (bpf_int32)(yyvsp[0].i), (bpf_u_int32)(yyvsp[-1].i), 1); }
#line 3128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 656 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = (yyvsp[-1].blk).b; (yyval.blk).q = qerr; }
#line 3134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 658 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.blk).atmfieldtype = (yyvsp[-1].blk).atmfieldtype;
	if ((yyval.blk).atmfieldtype == A_VPI ||
	    (yyval.blk).atmfieldtype == A_VCI)
		(yyval.blk).b = gen_atmfield_code((yyval.blk).atmfieldtype, (bpf_int32) (yyvsp[0].i), BPF_JEQ, 0);
	}
#line 3145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 666 "grammar.y" /* yacc.c:1646  */
    { gen_or((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 3151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 669 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = M_FISU; }
#line 3157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 670 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = M_LSSU; }
#line 3163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 671 "grammar.y" /* yacc.c:1646  */
    { (yyval.i) = M_MSU; }
#line 3169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 674 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).mtp3fieldtype = M_SIO; }
#line 3175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 675 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).mtp3fieldtype = M_OPC; }
#line 3181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 676 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).mtp3fieldtype = M_DPC; }
#line 3187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 677 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).mtp3fieldtype = M_SLS; }
#line 3193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 680 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_mtp3field_code((yyvsp[-2].blk).mtp3fieldtype, (u_int)(yyvsp[0].i), (u_int)(yyvsp[-1].i), 0); }
#line 3199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 681 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = gen_mtp3field_code((yyvsp[-2].blk).mtp3fieldtype, (u_int)(yyvsp[0].i), (u_int)(yyvsp[-1].i), 1); }
#line 3205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 682 "grammar.y" /* yacc.c:1646  */
    { (yyval.blk).b = (yyvsp[-1].blk).b; (yyval.blk).q = qerr; }
#line 3211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 684 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.blk).mtp3fieldtype = (yyvsp[-1].blk).mtp3fieldtype;
	if ((yyval.blk).mtp3fieldtype == M_SIO ||
	    (yyval.blk).mtp3fieldtype == M_OPC ||
	    (yyval.blk).mtp3fieldtype == M_DPC ||
	    (yyval.blk).mtp3fieldtype == M_SLS )
		(yyval.blk).b = gen_mtp3field_code((yyval.blk).mtp3fieldtype, (u_int) (yyvsp[0].i), BPF_JEQ, 0);
	}
#line 3224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 694 "grammar.y" /* yacc.c:1646  */
    { gen_or((yyvsp[-2].blk).b, (yyvsp[0].blk).b); (yyval.blk) = (yyvsp[0].blk); }
#line 3230 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3234 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
      yyerror (YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 696 "grammar.y" /* yacc.c:1906  */

