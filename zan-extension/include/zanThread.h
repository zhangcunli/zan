/*
  +----------------------------------------------------------------------+
  | Zan                                                                  |
  +----------------------------------------------------------------------+
  | Copyright (c) 2016-2017 Zan Group <https://github.com/youzan/zan>    |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | zan@zanphp.io so we can mail you a copy immediately.                 |
  +----------------------------------------------------------------------+
  | Author: Zan Group   <zan@zanphp.io>                                  |
  +----------------------------------------------------------------------+
*/
#ifndef _ZAN_THREAD_H_
#define _ZAN_THREAD_H_

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

///TODO:::要怎么封装
///pthread 本身就是跨平台线程库

//TODO:::不同平台的这几个宏，在哪里定义输出?
#if (LINUX)
    typedef pid_t          zan_tid_t;
    #define ZAN_TID_T_FMT  "%P"
#elif (FREEBSD)
    typedef uint32_t       zan_tid_t;
    #define ZAN_TID_T_FMT  "%uD"
#elif (DARWIN)
    typedef uint64_t       zan_tid_t;
    #define ZAN_TID_T_FMT  "%uA"
#else
    typedef uint64_t       zan_tid_t;
    #define ZAN_TID_T_FMT  "%uA"
#endif

zan_tid_t zan_get_thread_tid(void);

#endif  //_ZAN_THREAD_H_
