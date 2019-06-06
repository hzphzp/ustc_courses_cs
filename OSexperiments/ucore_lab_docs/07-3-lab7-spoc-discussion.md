2.（扩展练习）请在lab7-answer中分析

- cvp->count含义是什么？cvp->count是否可能<0, 是否可能>1？请举例或说明原因。

  count表示等在这个条件变量上的睡眠进程的个数。不可能<0，可能>1。
  不可能<0，因为++和--成对出现，总能保证不小于0.
  可能>1，因为当多个进程因为条件变量而等待时count就会大于1.
  
- cvp->owner->next_count含义是什么？cvp->owner->next_count是否可能<0, 是否可能>1？请举例或说明原因。

  next_count表示了由于发出singal_cv而睡眠的进程个数。不可能<0，不可能>1。
  不可能<0，因为++和--成对出现。 
  不可能>1，因为同一时刻仅有一个进程能够进入到++后的代码执行，保证其最大为1。

- 目前的lab7-answer中管程的实现是Hansen管程类型还是Hoare管程类型？请在lab7-answer中实现另外一种类型的管程。

修改monitor.c如下：

```C
// Unlock one of threads waiting on the condition variable.
void cond_signal(condvar_t *cvp) {
    cprintf(
        "cond_signal begin: cvp %x, cvp->count %d, cvp->owner->next_count %d\n",
        cvp, cvp->count, cvp->owner->next_count);
    if (cvp->count > 0) {
        //Simply give signal without doing anything else (Hasen Style)
        up(&(cvp->sem));
    }
    cprintf(
        "cond_signal end: cvp %x, cvp->count %d, cvp->owner->next_count %d\n",
        cvp, cvp->count, cvp->owner->next_count);
}

// Suspend calling thread on a condition variable waiting for condition
// Atomically unlocks
// mutex and suspends calling thread on conditional variable after waking up
// locks mutex. Notice: mp is mutex semaphore for monitor's procedures
void cond_wait(condvar_t *cvp) {
    cprintf(
        "cond_wait begin:  cvp %x, cvp->count %d, cvp->owner->next_count %d\n",
        cvp, cvp->count, cvp->owner->next_count);
    cvp->count++;
    up(&(cvp->owner->mutex));
    down(&(cvp->sem));
    down(&(cvp->owner->mutex));
    cvp->count--;
    cprintf(
        "cond_wait end:  cvp %x, cvp->count %d, cvp->owner->next_count %d\n",
        cvp, cvp->count, cvp->owner->next_count);
}

```
