#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include<string.h> 
#include <time.h> 

int sig_int_flag;
int termCount = 0;
int sigCount = 0;
char* argSigs[31] = {"0", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT OR SIGIOT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT","SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH"};
//strcpy(argSigs, argv);

void regSigs(char* sigs[]);
void handleSig(int sig);

int main(int argc, char* argv[]) {
    int count = 1;
    int Tcount = 0;

    //printf("TEST SIG%s", argv[1]);

    printf("Start: %ld \n", time(NULL));

	printf("PPID: %d, PID: %d \n", getppid(), getpid());
    //printf("%s", argv[1]);



    regSigs(argv);



    signal(10, handleSig);
    signal(SIGUSR2, handleSig);
    signal(SIGTERM, handleSig);

    kill(getpid(), SIGUSR1);
    kill(getpid(), SIGUSR1);

    while(termCount < 3) {
        //strcpy(sig, argv[count]);
        kill(getpid(), SIGTERM);
        regSigs(argv);
        printf("test");
        //while (sig_int_flag == 0) pause();
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
        char hold[7] = "SIG";
        strncat(hold, sigs[count], 4);
        if(signal(hold, handleSig) == SIG_ERR) printf("can't catch %s", hold);
        count++;
    }
}

void handleSig(int sig)
{
    printf("Signal: %s Caught at: %ld \n", argSigs[sig], time(NULL));
    //regSigs[argv];
    sig_int_flag = 1;         /* set flag for main loop to examine */
    if (sig == 15) termCount++;
    else termCount = 0;
    sigCount++;
}
