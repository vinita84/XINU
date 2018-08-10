#include<xinu.h>
#include<string.h>
#include<process_ring.h>
#include <stdlib.h>
shellcmd xsh_process_ring(int nargs, char *args[]) 
{
	uint32 *t_start = 0;
	uint32 *t_end = 0;
	gettime(t_start);
	int32 processes = 2; //default number of processes.
	int32 rounds = 3; //default number of rounds.
	char *implement = "poll"; //default implementation set to polling
	char *sync = "sync";
	/* Parsing all arguments*/
	char *endp = "";
	int32 i;
  	for(i = 1; i < nargs; i++){
    		if(strncmp(args[1], "--help", 7) == 0) 
		{
	                printf("Usage: %s\n\n", args[0]);
        	        printf("Description:\n");
                	printf("\tCoordinates processes to count from some number down to zero\n");
                	printf("Options (two per invocation):\n");
                	printf("\t-p\tNumber of processes to be run\n");
                	printf("\t-r\tNumber of rounds\n");
                	printf("\t-i\tType of implementation, either synchronisation or polling\n");
                	printf("\t--help\tdisplay this help and exit\n");
                	return 0;
        	}

		else if (0 == strncmp("-p", args[i], 3)){
      			/* parse numeric argument to -p */
      			if (! (i + 1 < nargs)) {
        			/* No argument after flag */
        			//print_usage();
       	 			printf("-p flag expected an argument\n");
        			return SHELL_ERROR;
      			}
      			processes = atoi(args[i + 1]);
      			if (endp == args[i + 1]) {
        			/* The end pointer hasn't advanced, No number was parsed.*/
        			//print_usage();
        			printf("-p flag expected an integer\n");
        			return SHELL_ERROR;
      			} 
			/*else if (*endp != '\0'){
       				 There was trailing garbage in the string that wasn't converted to an integer. 
        			//print_usage();
        			printf("-p recieved invalid integer\n");
        			return SHELL_ERROR;
      			} */
			else if (!(0 <= processes && processes <= 64)) {
        			/* The number is out of range */
        			//print_usage();
        			printf("-p flag expected a number between 0 - 64\n");
        			return SHELL_ERROR;
      			}
      			/* Skip pass the numeric argument, that was successfully parsed */
      			i += 1; 
    		}
		/*else if (0 <= atoi(args[i]) <= 64)
		{
			if (i == 1)
				processes = atoi(args[i]);
			else
				rounds = atoi(args[i]);
		} */
		else if (0 == strncmp("-r", args[i], 3)){
                        /* parse numeric argument to -r */
                        if (! (i + 1 < nargs)) {
                                /* No argument after flag */
                                //print_usage();
                                printf("-r flag expected an argument\n");
                                return SHELL_ERROR;
                        }
                        rounds = atoi(args[i + 1]);
                        if (endp == args[i + 1]) {
                                /* The end pointer hasn't advanced, No number was parsed.*/
                                //print_usage();
                                printf("-r flag expected an integer\n");
                                return SHELL_ERROR;
                        } 
                        /*else if (*endp != '\0'){
                                // There was trailing garbage in the string that wasn't converted to an integer. 
                                //print_usage();
                                printf("-r recieved invalid integer\n");
                                return SHELL_ERROR;
                        } */
                        else if (!(0 <= processes && processes <= 64)) {
                                /* The number is out of range */
                                //print_usage();
                                printf("-r flag expected a number between 0 - 64\n");
                                return SHELL_ERROR;
                        }
                        /* Skip pass the numeric argument, that was successfully parsed */
                        i += 1;
      		}
		else if (0 == strncmp("-i", args[i], 5)){
                        /* parse string argument to -i */
                        if (! (i + 1 < nargs)) {
                                /* No argument after flag */
                                //print_usage();
                                printf("-i flag expected an argument\n");
                                return SHELL_ERROR;
                        }
                        implement = args[i + 1];
                        if (endp == args[i + 1]) {
                                /* The end pointer hasn't advanced, No number was parsed.*/
                                //print_usage();
                                printf("-i flag expected an integer\n");
                                return SHELL_ERROR;
                        }
                        /* else if (*endp != '\0'){
                                // There was trailing garbage in the string that wasn't converted to an integer. 
                                print_usage();
                                printf("-p recieved invalid integer\n");
                                return SHELL_ERROR;
                        }*/
                        else if (!(strncmp("poll", args[i], 5)) | !(strncmp("sync", args[i], 5))) {
                                /* The string is an invalid option */
                                //print_usage();
                                printf("-i flag allowed implementation types are 'poll' or 'sync'\n");
                                return SHELL_ERROR;
                        }
                        /* Skip pass the numeric argument, that was successfully parsed */
                        i += 1;                
                }

      	}
        printf("arguments  are %d, %d, %s\n", processes,rounds, implement );
      	          
               
	/*if(nargs >= 2)
	{
  		rounds = atoi(args[2]);
		processes = atoi(args[1]);
	}*/
	printf("Number of Rings: %d\n",processes);
	//rounds = atoi(args[2]);
	printf("Number of Rounds: %d\n",rounds);
		
	if(0 == strncmp(sync, implement,5))
	{
		int32 curr_val = (processes * rounds) -1;
		sid32 done_sem = semcreate(0);
		int32 ring_id = 1;
		int32 curr_round = 0;
		sid32 process_sems[processes];
		process_sems[0] = semcreate(1);
		while(ring_id < processes)
		{
			process_sems[ring_id] = semcreate(0);
			ring_id = ring_id + 1;
		}
		ring_id = 0;
		while(ring_id < processes)
		{
			resume(create(sem_producer, 1024, 20, "producer", 7, &process_sems, &curr_val, done_sem, &rounds, &processes, ring_id, &curr_round));
			ring_id = ring_id + 1;
		}
  		wait(done_sem);
  		wait(done_sem);
  		ring_id = 0;
		while(ring_id < processes)
                {
                        //process_sems[ring_id] = semcreate(0);
                        semdelete(process_sems[ring_id]);
			ring_id = ring_id + 1;
                }
		//semdelete(produce_sem);
  		//semdelete(consume_sem);
  		semdelete(done_sem);
	}
	else
	{
		int32 curr_round = 0;
        	//int32 rounds = atoi(args[1]);
        	//int32 processes = atoi(args[2]); 
        	int32 ring_id = 0;
        	int32 ring_no = 0;
        
                int32 curr_val = rounds * processes - 1;
                
                while( ring_id < processes)
                {
                        resume(create(polling, 1024, 20, "producer", 6, &curr_val, &curr_round, &rounds, &ring_id, &ring_no, &processes));
                        ring_id = ring_id + 1;
                }

                
                while ((ring_no < processes) & (curr_round < rounds))
                { printf("");
                }

               
        	//clock_gettime(&stop);
        	//printf("\nElapsed seconds:%d\n",stop.tv_sec - start.tv_sec);
                //return SHELL_OK;

	}
	/*else
	{
		printf("Insufficient arguments");
		
	}*/
	gettime(t_end);
	int time_diff = *t_end - *t_start;
	printf("\nElapsed seconds:%d\n", time_diff);
	pid32 pid = getpid();
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
  	return SHELL_OK;
}
