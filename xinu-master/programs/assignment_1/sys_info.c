#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <queue.h>
int main(int argc, char *argv[])
{
	int fd[2];
	pid_t cpid;
	char buf;
	//char msg; 
	//msg = "hello world";
	if(argc !=2 )
	{
		printf("error");
	}
	if(pipe(fd) == -1)
	{
		printf("error in pipe");
		perror("pipe");
	}
	cpid = fork();
	if (cpid == -1) 
	{
        	printf("error in fork");
		perror("fork");
        	exit(EXIT_FAILURE);
   	 }
	if(cpid == 0)
	{
		printf("\nCHILD PID = %d",getpid());
		close(fd[1]);
		if (read(fd[0], &buf, strlen(argv[1])) > 0)
		{
			printf("\n the buffer is:%s",&buf);
		}
		if(strcmp(argv[1],"/bin/echo") == 0)
			execl(&buf,"echo","hello world!",NULL);
		else
			execl(&buf,"date", NULL);
		close(fd[0]);
        	_exit(EXIT_SUCCESS);
	}
	else{
		printf("\nPARENT PID = %d\n",getpid());
		close(fd[0]);
		write(fd[1], argv[1], strlen(argv[1]));
		close(fd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	pid32   prev, next;
        pid32 tail;
        pid32 head;
        static qid16    nextqid=NPROC;
        qid16           q;              /* ID of allocated queue        */
        q = nextqid;
        tail = queuetail(q);
        head = queuehead(q);
        printf("\n head:%d, tail:%d",head,tail);
        next = queuetab[pid].qnext;     /* Following node in list       */
        prev = queuetab[pid].qprev;     /* Previous node in list        */
        queuetab[prev].qnext = next;
        queuetab[next].qprev = prev;
        printf("\n next:%d, prev:%d",next,prev);

}
