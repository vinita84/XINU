#include <xinu.h>

process enqueue_func(pid32 qid )
{       //printf("EXECUTING SYNC\n");                 
        //qid16 qid1;
	//qid1 = qid;
		
	pid32 pid=0;
        //pid32 pid_new = 0;
	//enqueue(*pid, qid);
	pid = getpid();      
        enqueue(pid, qid);
	printf("pid : %d, qid: %d",pid, qid);
	return OK;
}
              
shellcmd xsh_test_harness(int nargs, char *args[])
{
	qid16 qid;
	qid = newqueue();
	//pid32 pid=0;
	//pid32 pid_new = 0;
	printf("QID IS: %d",qid);	
	resume(create(enqueue_func, 1024, 20, "producer", 1, qid));
	//enqueue(*pid, qid);
	//resume(create(enqueue_func, 1024, 20, "producer", 1, &qid));
	//enqueue(pid, qid);
	//resume(create(enqueue_func, 1024, 20, "producer", 1, &qid));
	//enqueue(pid, qid);
	//resume(create(enqueue_func, 1024, 20, "producer", 1, &qid));
	//enqueue(pid, qid);
	//pid_new = getfirst(
	return SHELL_OK;
}
