#  The Dining Philosophers
The basic setup for the problem is this: assume there are five “philosophers” sitting around a table. Between each
pair of philosophers is a single fork (and thus, five total). The philosophers each have times where they think, and don’t need any forks, and
times where they eat. In order to eat, a philosopher needs two forks, both
the one on their left and the one on their right. The contention for these
forks, and the synchronization problems that ensue, are what makes this
a problem we study in concurrent programming.

The key challenge, then, is to write the routines get forks() and put forks() such that there is no deadlock, no philosopher starves and never gets to eat, and concurrency is high (i.e., as many philosophers can 
eat at the same time as possible).

![Alt text](./img.png?raw=true "Table Distribution")
