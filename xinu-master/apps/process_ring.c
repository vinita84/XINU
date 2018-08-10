/*function that defines the ring processes*/ 
#include<xinu.h>
#include<string.h>
#include<process_ring.h>
process polling(int32 *curr_val, int32 *curr_round, int32 *rounds, int32 *ring_id, int32 *ring_no, int32 *processes){
        //printf("EXECUTING POLL\n");
	int32 rd = *curr_round;
        int32 rg_id = *ring_id;
	int32 p = *processes;
        while (rd <= *rounds-1)
        {
                int32 tmp = *curr_val;
                int32 rg = *ring_no;
                if (rg == rg_id)
                {
                        rd = *curr_round;
                        printf("Ring Element %d : round %d : value : %d \n", rg, rd, tmp); //%d\n", tmp + 1);
                        *curr_val = tmp - 1;
                        if(rg < p-1)
                        {
                                *ring_no = rg + 1; }
                        else
                        {
                                *ring_no = 0;
                                rd = *curr_round + 1;
                                *curr_round = rd;
                        }
                }
                rd = *curr_round;
        }
        return OK;
         
}         

process sem_producer(sid32 *process_sems[], int32 *curr_val, sid32 done_sem, int32 *rounds_p, int32 *rings_p, int32 ring_id, int32 *curr_round )
{       //printf("EXECUTING SYNC\n");                 
	int32 rings = *rings_p;
	int32 rounds = *rounds_p;
	int32 last = -1;
	int32 rd = *curr_round;
	sid32 curr_sem = (sid32)process_sems[ring_id];
	while (rd < rounds)
	{
		last = last + 1;
   		wait(curr_sem);
		rd = *curr_round;
		int32 val = *curr_val;
		if(rd < rounds && val >-1)
		{
		printf("Ring Element %d : Round %d : Value : %d\n", ring_id, rd, val);
		}
		*curr_val = *curr_val - 1;
    		if (ring_id == rings - 1)
		{
			*curr_round = *curr_round + 1;
			sid32 next_sem =  (sid32) process_sems[0];
			signal(next_sem);
		}
		else
		{
			sid32 next_sem =  (sid32)process_sems[ring_id+1];
			signal(next_sem);
		}
		
		rd = *curr_round;
		//IF IT IS THE LAST ROUND THIS PROCESS SHOULD EXIT AND RUN NO MORE.
		//if(rd == rounds-1)
		//	rd = rd + 1;

	}
  	signal(done_sem);
  	return OK;
}                         
/*shellcmd xsh_process_ring(int nargs, char *args[]) */
