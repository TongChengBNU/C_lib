/* Processed by ecpg (11.5) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "source.pgc"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* exec sql whenever sql_warning  sqlprint ; */
#line 6 "source.pgc"

    /* exec sql whenever sqlerror  sqlprint ; */
#line 7 "source.pgc"


    { ECPGconnect(__LINE__, 0, "tmp@127.0.0.1:5432" , "postgres" , "980126" , NULL, 1); 
#line 9 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 9 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 9 "source.pgc"

    
    /* exec sql begin declare section */
         
         
         
         
         
    
#line 12 "source.pgc"
 int id ;
 
#line 13 "source.pgc"
 char name [ 20 ] ;
 
#line 14 "source.pgc"
 char sex [ 20 ] ;
 
#line 15 "source.pgc"
 int age ;
 
#line 16 "source.pgc"
 char dep [ 20 ] ;
/* exec sql end declare section */
#line 17 "source.pgc"


    /* declare query_cursor scroll cursor with hold for select * from doctor */
#line 20 "source.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare query_cursor scroll cursor with hold for select * from doctor", ECPGt_EOIT, ECPGt_EORT);
#line 21 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 21 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 21 "source.pgc"

    printf("Select all queries:\n");
    do{
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from query_cursor", ECPGt_EOIT, 
	ECPGt_int,&(id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(sex),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(age),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(dep),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 25 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 25 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 25 "source.pgc"

        
        printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    } while (strcmp(SQLSTATE, "02000"));
    // exec sql close query_cursor;

    // exec sql open query_cursor;
    printf("\n");
    printf("Select 1st query:");
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch first from query_cursor", ECPGt_EOIT, 
	ECPGt_int,&(id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(sex),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(age),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(dep),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 35 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 35 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 35 "source.pgc"

    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    printf("\n");
    printf("Select next query:");
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch relative + 1 from query_cursor", ECPGt_EOIT, 
	ECPGt_int,&(id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(sex),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(age),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(dep),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 41 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 41 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 41 "source.pgc"

    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    printf("\n");
    printf("Select last query:");
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch last from query_cursor", ECPGt_EOIT, 
	ECPGt_int,&(id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(sex),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(age),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(dep),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 47 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 47 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 47 "source.pgc"

    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    printf("\n");
    printf("Select prior query:");
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch prior from query_cursor", ECPGt_EOIT, 
	ECPGt_int,&(id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(sex),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(age),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(dep),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 53 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 53 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 53 "source.pgc"

    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close query_cursor", ECPGt_EOIT, ECPGt_EORT);
#line 56 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 56 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 56 "source.pgc"

    { ECPGdisconnect(__LINE__, "CURRENT");
#line 57 "source.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 57 "source.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 57 "source.pgc"

    

    return 0;

    // exec sql create table doctor (
    //     doc_id int, 
    //     doc_name varchar(20),
    //     doc_sex varchar(20),
    //     doc_age int,
    //     doc_dep varchar(20),
    //     primary key (doc_id)
    // );


    // exec sql insert into doctor values 
    // (1,'aa','male',35,'aaaa'),
    // (2,'bb','female',32,'bbbb'),
    // (3,'cc','male',42,'cccc'),
    // (4,'dd','female',42,'dddd');


    // exec sql begin declare section;
    //     int id;
    //     char name[20];
    //     char sex[20];
    //     int age;
    //     char dep[20];
    // exec sql end declare section;
    // exec sql select * 
    //     into :id, :name, :sex, :age, :dep
    //     from doctor
    //     where doc_id=2;
    // exec sql disconnect;
    // printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep);


    // exec sql declare query_cursor CURSOR with hold for
    //     select * 
    //     from doctor;
    // exec sql open query_cursor; 
    // do{
    //     exec sql fetch from query_cursor
    //         into :id, :name, :sex, :age, :dep;
    //     printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep);
    //     id = 0;
    //     name[0] = '\0';
    //     sex[0] = '\0';
    //     age = 0;
    //     dep[0] = '\0';
    // } while (strcmp(SQLSTATE, "02000"));
    
    // exec sql close query_cursor;
    // exec sql disconnect;

    // exec sql update doctor 
    //     set doc_dep = 'xxxx'
    //     where doc_id = 3;
    // exec sql disconnect;

    // exec sql begin declare section;
    //     int m;
    // exec sql end declare section;
    // scanf("%d", &m);
    
    // exec sql update doctor 
    //     set doc_age = :m + (
    //         select doc_age from doctor
    //         where doc_id = 4
    //     )
    //     where doc_id = 4;
    // exec sql disconnect;
}

