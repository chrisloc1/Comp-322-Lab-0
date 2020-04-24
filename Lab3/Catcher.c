#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
//typedef void (*sighandler_t)(int);
//sighandler_t signal(int signum, sighandler_t handler);

#define SIGHUP  1   /* Hangup the process */ 
#define SIGINT  2   /* Interrupt the process */ 
#define SIGQUIT 3   /* Quit the process */ 
#define SIGILL  4   /* Illegal instruction. */ 
#define SIGTRAP 5   /* Trace trap. */ 
#define SIGABRT 6   /* Abort. */
#define SIGEMT 7
#define SIGFPE 8
#define SIGKILL 9
#define SIGBUS 10
#define SIGSEGV 11
#define SIGSYS 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGURG 16
#define SIGSTOP 17
#define SIGTSTP 18
#define SIGCONT 19
#define SIGCHLD 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGIO 23
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGINFO 29
#define SIGUSR1 30
#define SIGUSR2 31

#define HUP SIGHUP   /* Hangup the process */ 
#define INT SIGINT    /* Interrupt the process */ 
#define QUIT SIGQUIT    /* Quit the process */ 
#define ILL SIGILL    /* Illegal instruction. */ 
#define TRAP SIGTRAP    /* Trace trap. */ 
#define ABRT SIGABRT    /* Abort. */
#define EMT SIGEMT 
#define FPE SIGFPE 
#define KILL SIGKILL 
#define BUS SIGBUS 
#define SEGV SIGSEGV 
#define SYS SIGSYS 
#define PIPE SIGPIPE 
#define GALRM SIGALRM 
#define TERM SIGTERM 
#define URG SIGURG 
#define STOP SIGSTOP 
#define TSTP SIGTSTP 
#define CONT SIGCONT 
#define CHLD SIGCHLD 
#define TTIN SIGTTIN 
#define TTOU SIGTTOU 
#define IO SIGIO 
#define XCPU SIGXCPU 
#define XFSZ SIGXFSZ 
#define VTALRM SIGVTALRM 
#define PROF SIGPROF 
#define WINCH SIGWINCH 
#define INFO SIGINFO 
#define USR1 SIGUSR1 
#define USR2 SIGUSR2 

void handleSig(int sig);

int main(int argc, char* argv[]) {
    printf("Start: %ld \n", time(NULL));

	printf("PPID: %d, PID: %d \n", getppid(), getpid());

	signal(SIGINT, handleSig);
    pause();
    /*while (1)
    {
        printf("hello world\n");
        sleep(1);
    }*/
    return 0;
}

void handleSig(int sig)
{
    printf("Signal: %d Time: %ld \n", sig, time(NULL));
}
