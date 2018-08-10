Answer1. The two things I learnt from this assignment are:
I learnt the concept of Semaphores and how to implement them to share resources between multiple processes. 
I learnt the concept of polling and its implementation between multiple processes. 

Answer2. I corrected the following two mistakes from this assignment:
Firstly, while creating semaphores I was creating one semaphore for each process and then creating the respective process. This was wrong. I figured out that all the semaphores need to be created first and then the processes should be created because all semaphores will be accessed by all processes.
Secondly, I was executing all process until the final printed value reaches 0. But later I decided to execute all process until the final round is reached by each process. This is because the final value will become 0 in the last process so other processes need not wait for the last process if they have executed their final round.

Answer3. If I was restarting this assignment, I would do a little more pseudocode in the beginning and draft an optimised layout before going to the actual coding. This would help me a lot of mistakes like some pointed in question 2. Also I would plan on the data structure for implementing semaphores of different processes.
