/* Print out new values in the produce location, and acknowledge that
 *    they were received by placing them in the consume location */
#include <xinu.h>
//#include <time.h>
process polling_process(int32 *curr_val, volatile int32 *curr_round, int32 *rounds, int32 *ring_id, int32 *ring_no, int32 *max_rings){
	int32 rd = *curr_round;
	int32 rg_id = *ring_id;
	while (*curr_round <= *rounds-1)
	{
		int32 tmp = *curr_val;
    		int32 rg = *ring_no;
    		if (rg == rg_id)
		{
      			rd = *curr_round;
			printf("Ring Element %d : round %d : value : %d \n", rg, rd, tmp); //%d\n", tmp + 1);
      			*curr_val = tmp - 1;
      			if(rg < *max_rings-1)
      			{ 
				*ring_no = rg + 1; }
      			else 
			{ 	
				*ring_no = 0;
				rd = rd + 1;
				*curr_round = rd;
			}
    		}
		rd = *curr_round;
 	}
	return OK;

}

shellcmd xsh_example2(int nargs, char *args[]) {
	//struct time start, stop;
	//clock_gettime( &start);
	int32 curr_round = 0;
	int32 rounds = atoi(args[1]);
	int32 rings = atoi(args[2]); //2;
  	int32 ring_id = 0;
	int32 ring_no = 0;
  	if(nargs > 2)
 	{
  		printf("Number of processes: %d\n",rings);
  		printf("Number of rounds: %d\n",rounds);
  
 		volatile int32 curr_val = rounds * rings - 1; //11;
  		
		while( ring_id < rings)
		{
			resume(create(polling_process, 1024, 20, "producer", 6, &curr_val, &curr_round, &rounds, &ring_id, &ring_no, &rings));
			ring_id = ring_id + 1;
  		}

  		/* Polling to see if both producer and consumer are done */
  		while (ring_no < rings & curr_round < rounds)
		{ printf("");
		}
		
  		return SHELL_OK;
  	}
  	else
	{
   		printf("\nInsufficient number of arguments.");
  	}
	//clock_gettime(&stop);
	//printf("\nElapsed seconds:%d\n",stop.tv_sec - start.tv_sec);
	return SHELL_OK;
}
