#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>  /* contain function: int lockf(int fd, int cmd, off_t len) */
#include <wait.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

int main()
{
    pid_t fpid_p, fpid_p2;

    /* test 2 */
    /* printf("In parent process and before fork:"); */

    /* test 2-1 */
    /* printf("In parent process and before fork:\n");   */
    
    /* OR */

    /* printf("In parent process and before fork:"); */
    /* fflush(stdout) */


    /* test 3 */
    /* lockf(1, 0, 0) : add lock on stdout; */


    fpid_p = fork();
    /* If a child process is created successfully, fpid_p >= 0; */
    /* Then in parent process, fpid_p > 0 and equals the pid of child process; */
    /* But in child process, fpid_p = 0 means this process is a child and has no child process; */

    if (fpid_p < 0)
    {
        /* error */
        printf("Error while creating 1st process;");
        return 0;
    }
    else if (fpid_p > 0)
    {
        /* In parent process */
        fpid_p2 = fork();
        if (fpid_p2 < 0)
        {
            /* error */
            printf("Error while creating 1st process;");
            return 0;
        }
        else if (fpid_p2 > 0)
        {
            /* In parent process */
            printf("Parent Process: a;\nPID: %d\nPPID: %d\n\n", getpid(), getppid() );
        }
        else
        {
            lockf(1, 1, 0);
            for (int i=0; i<5; i++)
            {
                /* lockf(1, 1, 0); */
                /* In child 2 process */
                printf("Child 2 Process: c;\nPID: %d\nPPID: %d\n\n", getpid(), getppid() );
                /* lockf(1, 0, 0); */
                sleep(3);
            }
            lockf(1, 0, 0);
        }
    }
    else
    {
        lockf(1, 1, 0);
        for (int i=0; i<3; i++)
        {
            /* lockf(1, 1, 0); */
            /* In child 1 process */
            printf("Child 1 Process: b;\nPID: %d\nPPID: %d\n\n", getpid(), getppid() );
            /* lockf(1, 0, 0); */
            sleep(3);
        }
        lockf(1, 0, 0);

    }

    return 0;

}



