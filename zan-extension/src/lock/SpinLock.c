/*
  +----------------------------------------------------------------------+
  | Zan                                                                  |
  +----------------------------------------------------------------------+
  | Copyright (c) 2012-2016 Swoole Team <http://github.com/swoole>       |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | license@swoole.com so we can mail you a copy immediately.            |
  +----------------------------------------------------------------------+
  | Author: Tianfeng Han  <mikan.tenny@gmail.com>                        |
  +----------------------------------------------------------------------+
*/

#include "swLock.h"

#ifdef HAVE_SPINLOCK
static int swSpinLock_lock(swLock *lock);
static int swSpinLock_unlock(swLock *lock);
static int swSpinLock_trylock(swLock *lock);
static int swSpinLock_free(swLock *lock);


int swSpinLock_create(swLock *lock, int use_in_process)
{
    if (!lock){
        return SW_ERR;
    }

    bzero(lock, sizeof(swLock));
    if (pthread_spin_init(&lock->object.spinlock.lock_t, use_in_process) < 0)
    {
        return SW_ERR;
    }

    lock->type = SW_SPINLOCK;
    lock->lock = swSpinLock_lock;
    lock->unlock = swSpinLock_unlock;
    lock->trylock = swSpinLock_trylock;
    lock->free = swSpinLock_free;
    return SW_OK;
}

static int swSpinLock_lock(swLock *lock)
{
    return pthread_spin_lock(&lock->object.spinlock.lock_t);
}

static int swSpinLock_unlock(swLock *lock)
{
    return pthread_spin_unlock(&lock->object.spinlock.lock_t);
}

static int swSpinLock_trylock(swLock *lock)
{
    return pthread_spin_trylock(&lock->object.spinlock.lock_t);
}

static int swSpinLock_free(swLock *lock)
{
    return pthread_spin_destroy(&lock->object.spinlock.lock_t);
}

#endif
