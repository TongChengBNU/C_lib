/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 242 "grammar.y" /* yacc.c:1909  */

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

#line 294 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
