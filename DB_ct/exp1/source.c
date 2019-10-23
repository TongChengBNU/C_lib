#include <stdio.h>
#include <stdlib.h>

int main()
{
    exec sql whenever sqlwarning sqlprint;
    exec sql whenever sqlerror sqlprint;

    exec sql connect to "tmp@127.0.0.1:5432" user "postgres" using "980126";
    
    exec sql begin declare section;
        int id;
        char name[20];
        char sex[20];
        int age;
        char dep[20];
    exec sql end declare section;

    exec sql declare query_cursor scroll cursor with hold for 
        select * from doctor;
    exec sql open query_cursor;
    printf("Select all queries:\n");
    do{
        exec sql fetch from query_cursor
            into :id, :name, :sex, :age, :dep;
        
        printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    } while (strcmp(SQLSTATE, "02000"));
    // exec sql close query_cursor;

    // exec sql open query_cursor;
    printf("\n");
    printf("Select 1st query:");
    exec sql fetch first from query_cursor
        into :id, :name, :sex, :age, :dep;
    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    printf("\n");
    printf("Select next query:");
    exec sql fetch relative+1 from query_cursor
        into :id, :name, :sex, :age, :dep;
    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    printf("\n");
    printf("Select last query:");
    exec sql fetch last from query_cursor
        into :id, :name, :sex, :age, :dep;
    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    printf("\n");
    printf("Select prior query:");
    exec sql fetch prior from query_cursor
        into :id, :name, :sex, :age, :dep;
    printf("doc_id=%d, doc_name=%s, doc_sex=%s, doc_age=%d, doc_dep=%s\n", id, name, sex, age, dep); 
    
    exec sql close query_cursor;
    exec sql disconnect;
    

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

