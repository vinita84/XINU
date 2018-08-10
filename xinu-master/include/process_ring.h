/*This file will declare function prototypes and variables used.*/

#ifndef _PROCESS_RING_H_
#define _PROCESS_RING_H_
extern shellcmd xsh_process_ring   (int32, char *[]);
process polling(int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);
process sem_producer(sid32 *process_sems[], int32 *curr_val, sid32 done_sem, int32 *rounds_p, int32 *rings_p, int32 ring_id, int32 *curr_round );

#endif
