# Concurrent Programming

## Process vs Threads
### 1. Multiprocessing
Each process has only one thread running, and all the processes communicate to each other
through the regular 'Interprocess Communication channel' such as files, pipes, message queues.

### 2. Multithreading
One process contains two ore more threads, and all the threads communicates each other through
shared memory.

---
## Advantage & Disadvantage of this two model above.
### 1. Pros & Cons - Multithreading
Pros
* Fast to start
  * In case of the multiprocessing is slow & complicated to start a process because the operating
    system need to devote a bunch of internal resources to **manage the resources**.
* Low overhead
  * In case of the multiprocessing has more overhead, the operating system need to provide a lot of
    protection so that the one process will not accidently step into another process.
  * Communicating through shared memory is a lot faster than communicating through interprocess communication channel

Cons
* Difficult to implement
* Can't run on distributed system
  * This can be estabilished with multiprocessing

## Resource
[Youtube](https://www.youtube.com/watch?v=LL8wkskDlbs)
