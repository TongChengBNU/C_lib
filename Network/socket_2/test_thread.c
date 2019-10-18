#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

void *thread(void *arg);
int num = 0;

int main()
{
    pthread_t thread_id;    
    int ret;

    fprintf(stderr, "Main thread with ID: %ld\n", pthread_self());
    //if ( pthread_create(&thread_id, NULL, (void *)(&thread), NULL) != 0 )
    //{
    //    fprintf(stderr, "Thread creation failed.\n");
    //    exit(1);
    //}
    //ret = pthread_create(&thread_id, NULL, (void *)(&thread), NULL); 
    ret = pthread_create(&thread_id, NULL, &thread, NULL); 
    fprintf(stderr, "%d\n", ret);
    //sleep(5);
    printf("%d\n", num);
    return 0;
}

void *thread(void *arg)
{
    int retval;
    pthread_t new_thread_id;
    new_thread_id = pthread_self();
    fprintf(stdout, "New thread with ID: %ld\n", new_thread_id);
    // printf("New thread with ID: %ld\n", new_thread_id);
    num++;
    pthread_exit(&retval);
}
