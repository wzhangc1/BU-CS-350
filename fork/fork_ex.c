#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int idata = 111; 

int main()
{
	pid_t pid;

	pid = fork();
	
	//printf("-----PID=%s %d \n", (pid == 0) ? "(child) " : "(parent)", (int) getpid());
 
	if (pid == -1) { 
		fprintf(stderr, "fork failed\n"); 
		exit(1); 
	} 

	if (pid == 0) {
		printf("This is the child%d\n",getpid()); 
		
		exit(0); 
	} 

	if (pid > 0) { 
		pid = wait(NULL);
		printf("This is parent. The child is %d\n", pid); 
		
		exit(0); 
	}
	
	return 0;
}

