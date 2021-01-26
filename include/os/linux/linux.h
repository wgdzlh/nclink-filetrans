#ifndef __OS_LNX_H__
#define __OS_LNX_H__
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <errno.h>

#define MutexInit pthread_mutex_init
#define MutexLock pthread_mutex_lock
#define MutexUnlock pthread_mutex_unlock
#define MutexDestory pthread_mutex_destroy
#define CondInit pthread_cond_init
#define CondWait	pthread_cond_wait
#define CondSignal pthread_cond_signal
#define CondBroadcast pthread_cond_broadcast
#define CondDestory pthread_cond_destroy

#define Mutex pthread_mutex_t
#define Cond pthread_cond_t
#define Thread pthread_t
#define ThreadCreate pthread_create
#define ThreadCancel pthread_cancel 
#define ThreadJoin pthread_join

#define GetPid	getpid

#define E_TIMEDOUT    ETIMEDOUT
///按毫秒数休眠
#define Sleep(n) usleep(n*1000)
///退出线程
#define StopThread(tid) do{ThreadCancel(tid);ThreadJoin(tid,NULL);}while(0)
///获取当前时间毫秒数
#define GetMilliseconds(ms)    do{ struct timeval t0;gettimeofday(&t0, NULL);*ms = ((long long)(t0.tv_sec)) * 1000 + t0.tv_usec / 1000; }while(0)

///改写的条件变量超时等待函数，修改时间参数，为相对时间
static inline int CondTimedWait(Cond* cond, Mutex* lock, struct timespec* timeout)
{
    long long ms;
    GetMilliseconds(&ms);
    (timeout)->tv_sec = (timeout)->tv_sec + ms / 1000;
    (timeout)->tv_nsec = (timeout)->tv_nsec + (ms % 1000) * 1000000;
    return pthread_cond_timedwait(cond, lock, timeout);
}
#endif
