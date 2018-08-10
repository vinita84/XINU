/* getitem.c - getfirst, getlast, getitem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid32	getfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;

	if (isempty(q)) {
		return EMPTY;
	}

	head = queuehead(q);
	//print("\n %d",head)
	return getitem(queuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  getlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid32	getlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;

	if (isempty(q)) {
		return EMPTY;
	}

	tail = queuetail(q);
	//print("\n %d",tail)
	return getitem(queuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32	getitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	pid32	prev, next;
	
	//test starts
	//pid32 tail;
	//pid32 head;
	//static qid16	nextqid=NPROC;
	//qid16		q;		/* ID of allocated queue 	*/
	//q = nextqid;
	//tail = queuetail(q);
	//head = queuehead(q);
	//printf("\n head:%d, tail:%d",head,tail);
	//test ends
	
	//next = *(queuetab+pid)->qnext;	/* Following node in list	*/
	//prev = *(queuetab+pid)->qprev;	/* Previous node in list	*/
	//(queuetab+prev)->qnext = next;
	//(queuetab+next)->qprev = prev;
	next = queuetab[pid].qnext;	/* Following node in list	*/
	prev = queuetab[pid].qprev;	/* Previous node in list	*/
	queuetab[prev].qnext = next;
	queuetab[next].qprev = prev;

	//test starts
	//printf("\n next:%d, prev:%d",next,prev);
	//test ends
	return pid;
}
