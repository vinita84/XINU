
/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  * xsh_hello - obtain and print the string with hello message
 *   *------------------------------------------------------------------------
 *    */
shellcmd xsh_hello(int nargs, char *args[]) {

	//char	retval;			/* return value			*/
	//uint32	now;			/* current local time		*/
	//char	datestr[64];		/* printable date in ascii	*/


	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
	}
	if (nargs < 2) {
                fprintf(stderr, "%s: too few arguments\n", args[0]);
        }
	if (nargs == 2) {
		printf("Hello %s, Welcome to the world of Xinu!!\n", args[1]);
	}
	printf("entering loop..");
	while(1)
	{
	}
	return 0;
}
