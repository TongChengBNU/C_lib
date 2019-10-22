/* Processed by ecpg (11.5) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "test_pgSQL.pgc"
// ----------------------------------------------------------------------
// Step 1:
// ./ecpg -t -c -I <pg include dir path> -o <.c output> <.pgc source> 
// Step 2:
// gcc -I <pg include dir path> -Wall -g <.c source> -L <pg lib dir path> -lecpg -lpq -lpgtypes -o <output exec>
// 
// ----------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

int main()
{   
    /* exec sql whenever sql_warning  sqlprint ; */
#line 15 "test_pgSQL.pgc"

    /* exec sql whenever sqlerror  sqlprint ; */
#line 16 "test_pgSQL.pgc"


    // connect to DB server
    { ECPGconnect(__LINE__, 0, "tmp@127.0.0.1:5432" , "postgres" , "980126" , NULL, 1); 
#line 19 "test_pgSQL.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 19 "test_pgSQL.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 19 "test_pgSQL.pgc"
 

    // execute DML 
    // exec sql insert into examinee (eeid) values ('555');



    // shared variables 
    /* exec sql begin declare section */
          
         
            
    
#line 28 "test_pgSQL.pgc"
 char id [ 30 ] = "218811011013" ;
 
#line 29 "test_pgSQL.pgc"
 char name [ 20 ] ;
 
#line 30 "test_pgSQL.pgc"
 int eeage ;
/* exec sql end declare section */
#line 31 "test_pgSQL.pgc"


    // query from table
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select eename , eeage from examinee where eeid = $1 ", 
	ECPGt_char,(id),(long)30,(long)1,(30)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(name),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(eeage),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 37 "test_pgSQL.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 37 "test_pgSQL.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 37 "test_pgSQL.pgc"

    { ECPGdisconnect(__LINE__, "CURRENT");
#line 38 "test_pgSQL.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 38 "test_pgSQL.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 38 "test_pgSQL.pgc"


    printf("id=%s, name=%s, grade=%d\n", id, name, eeage);



    // cursor
    // exec sql declare query_cursor cursor with hold for 
    //    select eeid, eename, grade
    //    from 

    // exec sql fetch from query_cursor    
    //    into 
    

    // scroll cursor
    // exec sql declare query_cursor scroll cursor with hold for

    // exec sql fetch last from query_cursor

    // exec sql fetch relative-1 from query_cursor

    return 0;
}