#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include<string.h> 
#include <time.h> 

//int sig_int_flag;
int termCount = 0;
int sigCount = 0;
char* argSigs[31] = {"0", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT OR SIGIOT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT","SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH"};

void regSigs(char* sigs[]);
void handleSig(int sig);

int main(int argc, char* argv[]) {
    int count = 1;
    int Tcount = 0;

    printf("Start Time: %ld \n", time(NULL));

	printf("PPID: %d, PID: %d \n", getppid(), getpid());
    //printf("%s", argv[1]);

    regSigs(argv);

    //kill(getpid(), SIGVTALRM);
    //kill(getpid(), SIGUSR1);

    while(termCount < 3) {
        //kill(getpid(), SIGTERM);
        pause();
        regSigs(argv);
        //printf("test");
        //while (sig_int_flag == 0) pause();
    }


    printf("Code done! Number of signals caught: %d\n", sigCount);
    return 0;
}

void regSigs(char* sigs[]) {
    int count = 1;
    
    int sigNum = 0;
    while (sigs[count]) {
        char hold[10] = "SIG";

        strncat(hold, sigs[count], 7);
        for (int i = 0; i <= 28; i++) {
            if (strcmp(hold, argSigs[i]) == 0) {
                //printf("works");
                sigNum = i;
            }
            //printf("%s %s %s \n", argSigs[15], hold, argSigs[i]);
        }

        if(signal(sigNum, handleSig) == SIG_ERR) printf("can't catch %s", hold);
        count++;
    }
}

void handleSig(int sig)
{
    printf("Signal: %s Caught at: %ld \n", argSigs[sig], time(NULL));
    //sig_int_flag = 1;         /* set flag for main loop to examine */
    if (sig == 15) termCount++;
    else termCount = 0;
    sigCount++;
}
