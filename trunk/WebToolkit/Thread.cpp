#include "Common.h"
#include "Thread.h"

#ifndef WIN32
#include <signal.h>
#endif

struct ThreadArgs
{
	ThreadProc threadProc;
	void* arg;
};

#ifdef WIN32
DWORD WINAPI
#else
void*
#endif
thread_func(void* d)
{
#ifndef WIN32
	signal(SIGPIPE,SIG_IGN);
#endif
	srand(static_cast<unsigned int>(time(NULL)));
	ThreadArgs* args=reinterpret_cast<ThreadArgs*>(d);
	(*args->threadProc)(args->arg);
	delete args;
	return 0;
}

void Thread::StartThread(ThreadProc threadProc,void* arg)
{
	ThreadArgs* args=new ThreadArgs();
	args->threadProc=threadProc;
	args->arg=arg;
#ifdef WIN32
	HANDLE thread;
	CreateThread(NULL,0,thread_func,args,0,(LPDWORD)&thread);
#else
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&thread,&attr,thread_func,args);
	pthread_attr_destroy(&attr);
#endif
}

unsigned long Thread::GetCurrentThreadId() {
#ifdef WIN32
	return (unsigned long) ::GetCurrentThreadId();
#else
    return (unsigned long) pthread_self();
#endif
}

Mutex::Mutex()
{
#ifdef WIN32
	mutex=CreateMutex(NULL,FALSE,NULL);
#else
	pthread_mutex_init(&mutex,NULL);
#endif
}

Mutex::~Mutex()
{
#ifdef WIN32
	CloseHandle(mutex);
#else
	pthread_mutex_destroy(&mutex);
#endif
}

void Mutex::Lock()
{
#ifdef WIN32
	WaitForSingleObject(mutex,INFINITE);
#else
	pthread_mutex_lock(&mutex);
#endif
}

void Mutex::Unlock()
{
#ifdef WIN32
	ReleaseMutex(mutex);
#else
	pthread_mutex_unlock(&mutex);
#endif
}

CondVar::CondVar()
{
#ifdef WIN32
	condVarEvent=CreateEvent(NULL,FALSE,FALSE,NULL);
#else
	pthread_cond_init(&condVar,NULL);
#endif
}

CondVar::~CondVar()
{
#ifdef WIN32
	CloseHandle(condVarEvent);
#else
	pthread_cond_destroy(&condVar);
#endif
}

void CondVar::Wait(Mutex& externalMutex)
{
#ifdef WIN32
	SignalObjectAndWait(externalMutex.mutex,condVarEvent,INFINITE,FALSE);
	externalMutex.Lock();
#else
	pthread_cond_wait(&condVar,&externalMutex.mutex);
#endif
}

void CondVar::Signal()
{
#ifdef WIN32
	PulseEvent(condVarEvent);
#else
	pthread_cond_signal(&condVar);
#endif
}
