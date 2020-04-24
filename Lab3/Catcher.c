#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include<string.h> 
#include <time.h> 

#define HUP SIGHUP   
#define INT SIGINT    
#define QUIT SIGQUIT    
#define ILL SIGILL    
#define TRAP SIGTRAP    
#define ABRT SIGABRT   
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

/**/#define SIGHUP  1    
#define SIGINT  2   
#define SIGQUIT 3   
#define SIGILL  4   
#define SIGTRAP 5   
#define SIGABRT 6  
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



int sig_int_flag;
int sigCount = 0;
//char* argSigs[];
//strcpy(argSigs, argv);

void regSigs(char* sigs[]);
void handleSig(int sig);

int main(int argc, char* argv[]) {
    int count = 1;
    int Tcount = 0;
    char sig[4];

    printf("Start: %ld \n", time(NULL));

	printf("PPID: %d, PID: %d \n", getppid(), getpid());
    //printf("%s", argv[1]);

    regSigs(argv);

    signal(SIGUSR1, handleSig);

    for(int i=0;i<3;i++) {
        //strcpy(sig, argv[count]);

        regSigs(argv);
        while (sig_int_flag == 0) pause();

        printf("%s", argv[count]);
        printf("\n");
        count++;
    }
    
    /*if (signal(SIGUSR1, handleSig) == SIG_ERR)
        err_sys("can't catch SIGUSR1");
    if (signal(SIGUSR2, handleSig) == SIG_ERR)
        err_sys("can't catch SIGUSR2");
    for (; ; )
        pause();*/

    //pause();

    printf("Code done! Number of signals caught: %d\n", sigCount);
    return 0;
}

void regSigs(char* sigs[]) {
    int count = 1;
    while (sigs[count]) {
        if(signal(sigs[count], handleSig) == SIG_ERR) printf("can't catch SIG %s", sigs[count]);
        count++;
    }
}

void handleSig(int sig)
{
    printf("Signal: %d Time: %ld \n", sig, time(NULL));
    //regSigs[argv];
    sig_int_flag = 1;         /* set flag for main loop to examine */

    sigCount++;
    /*if (sig == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (sig == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        err_dump("received signal %d\n", sig);/**/
}
