/*
 * SyncObject.cpp
 *
 *  Created on: 2015/08/31
 *      Author: ttm
 */

#include "SyncObject.h"

//-----------------------------------------------
/*
 *
 */
CSyncObject::CSyncObject(void)
	: handle(NULL) {
}
CSyncObject::CSyncObject(void* ptr)
	: handle(ptr){
}
CSyncObject::~CSyncObject(){
}
bool	CSyncObject::Create(){
	return false;
}
void	CSyncObject::Close(){
}
bool	CSyncObject::TryLock(){
	return false;
}
bool	CSyncObject::Lock(){
	return false;
}
void	CSyncObject::Unlock(){
}

//-----------------------------------------------
/*
 *
 */
CMutex::CMutex() : CSyncObject(&mutx) {
	Create();
}
CMutex::~CMutex() {
	Close();
}
bool	CMutex::Create(){
	return(pthread_mutex_init(&mutx, NULL)==0);
}
void	CMutex::Close(){
	pthread_mutex_destroy(&mutx);
}
bool	CMutex::TryLock(){
	return(pthread_mutex_trylock(&mutx)==0);
}
bool	CMutex::Lock(){
	return(pthread_mutex_lock(&mutx)==0);
}
void	CMutex::Unlock(){
	pthread_mutex_unlock(&mutx);
}

//-----------------------------------------------
/*
 *
 */
CEvent::CEvent(bool signal/*= false*/,bool reset/*= false*/)
	: signaled(signal)
	, auto_reset(reset)
{
	Create();
}
CEvent::~CEvent(){
	Close();
}
bool	CEvent::Create(){
	return(pthread_cond_init(&cond, NULL)==0);
}
void	CEvent::Close(){
	pthread_cond_destroy(&cond);
}
void	CEvent::Wait(int millisecTimeout/*= 0*/){
#ifndef NANO_PER_SEC
#define NANO_PER_SEC		(1000000000)
#endif
	if( Lock() ){
		if( !signaled )
		{
			if( millisecTimeout > 0 ){
				struct timespec timeout;
				clock_gettime(CLOCK_REALTIME, &timeout);
				timeout.tv_sec	+= (millisecTimeout / 1000);
				timeout.tv_nsec	+= (millisecTimeout % 1000) * 1000000;
				while( timeout.tv_nsec >= NANO_PER_SEC ){
					timeout.tv_sec++;
					timeout.tv_nsec -= NANO_PER_SEC;
				}
				pthread_cond_timedwait(&cond, (CMutex::HANDLE)mutx.handle, &timeout);
			}else{
				while( !signaled ){
					pthread_cond_wait(&cond, (CMutex::HANDLE)mutx.handle);
				}
			}

			if( auto_reset ){
				signaled = false;
			}
		}
		Unlock();
	}
}
void	CEvent::Signal(){
	if( Lock() ){
		signaled = true;
		Unlock();
	}
	pthread_cond_signal(&cond);
}
void	CEvent::Reset(){
	if( Lock() ){
		signaled = false;
		Unlock();
	}
}
bool	CEvent::TryLock(){
	return mutx.TryLock();
}
bool	CEvent::Lock(){
	return mutx.Lock();
}
void	CEvent::Unlock(){
	mutx.Unlock();
}
