#ifndef __OS_WIN_H__
#define __OS_WIN_H__
#include <Windows.h>
#include <time.h>
#include <sys/timeb.h>

#define MutexInit(lock,attr) (InitializeCriticalSection(lock),0)
#define MutexLock(lock) EnterCriticalSection(lock)
#define MutexUnlock(lock) LeaveCriticalSection(lock)
#define MutexDestory(lock) (DeleteCriticalSection(lock),0)
#define CondInit(cond,attr) (InitializeConditionVariable(cond),0)
#define CondTimedWait(cond,lock,timeout) (SleepConditionVariableCS(cond,lock,(timeout)->tv_sec*1000+(timeout)->tv_nsec/1000000)==0?GetLastError():0)
#define CondWait(cond,lock)	(SleepConditionVariableCS(cond,lock,INFINITE)==0?GetLastError():0)
#define CondSignal(cond) WakeConditionVariable(cond)
#define CondBroadcast(cond) WakeAllConditionVariable(cond)
#define CondDestory(cond) (0)

#define Mutex CRITICAL_SECTION
#define Cond CONDITION_VARIABLE
#define Thread HANDLE
#define ThreadCreate(thread,attr,func,arg) ((*thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, arg, 0, NULL))!=NULL?0:-1)
#define ThreadCancel(tid) 
#define ThreadJoin(tid,ret) do{WaitForSingleObject(tid, INFINITE);CloseHandle(tid);}while(0)

#define GetMilliseconds(ms)	do{ struct timeb t0;ftime(&t0);*ms = t0.time * 1000 + t0.millitm; }while(0)
#define GetPid	GetCurrentProcessId
//#define E_TIMEDOUT	ERROR_TIMEOUT
#endif