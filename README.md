# Lock algorithms
This repository contains an implementation of a trivial thread-locking algorithms with ```pthreads``` in C.
Additionally, the algorithm is analyzed with respect to three fundamental properties that a good Lock algorithm should satisfy:
<ul>
    <li><b>Mutual Exclusion</b>: Critical sections of different threads do not overlap.</li>
    <li><b>Deadlock Freedom</b>:
    If some thread attempts to acquire a lock, some thread will eventually acquire the lock. <br>
    If thread <b><i>A</i></b> calls <i>lock()</i> but never acquires the lock, then other threads must be completing an 
    infinite number of critical sections.
    </li>
    <li><b>Starvation Freedom</b>: Evey thread that attempts to acquire the lock eventually succeeds. 
    Therefore, each call to <i>lock()</i> eventually returns. 
    </li>
</ul>

## LockOne algorithm
Implementation can be found [here](LockOne.c).
This algorithm is usable with just two threads, <b><i>A</i></b> and <b><i>B</i></b>. 
Each thread has a unique integral identifier - either 0 or 1.  
Let's suppose the algorithm does not satisfy mutual exclusion. That means that  <b><i>A</i></b> and  <b><i>B</i></b> 
both enter the critical section concurrently. Let's consider each thread's last execution of the  <i>lock()</i> function:

 <b><i>A</i></b> sets ```flag[A]=true```, then  <b><i>A</i></b> also reads 
```flag[B]=false``` and therefore  <b><i>A</i></b> enters the critical section. 

<b><i>B</i></b> sets ```flag[B]=true```, then <b><i>B</i></b> reads that ```flag[A]=false``` and enters the critical section.

When <b><i>B</i></b> is set to true, it remains true. This means that <b><i>A</i></b> must read that 
```flag[B]=false``` before <b><i>B</i></b> sets ```flag[B]=true```. Otherwise, the mutual exclusion property would 
not apply. 

Thus, we can form the following sequence: 
* <b><i>A</i></b> sets ```flag[A]=true```
* <b><i>A</i></b> reads ```flag[B]=false```
* <b><i>B</i></b> sets ```flag[B]=true```
* <b><i>B</i></b> reads ```flag[A]=false```

Therefore, when <b><i>A</i></b> sets ```flag[A]=true```, then <b><i>B</i></b> reads ```flag[A]=false```.
This does meet the mutual exclusion property.
However, if both <b><i>A</i></b> and <b><i>B</i></b> enter the <i>lock()</i> at the same time, both will deadlock, because 
both will attempt to set their respective flags to true, before reading the other thread's flag.

 

