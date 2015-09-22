/*
 * SyncObject.h
 *
 *  Created on: 2015/08/31
 *      Author: ttm
 */

#ifndef SYNCOBJECT_H_
#define SYNCOBJECT_H_

#include <pthread.h>

//-----------------------------------------------
/*
 *
 */
class ISyncObject {
public:
	virtual ~ISyncObject(void){}
	virtual bool	Lock()		= 0;
	virtual void	Unlock()	= 0;
};
//-----------------------------------------------
/*
 *
 */
class CSyncObject : public ISyncObject {
	CSyncObject(CSyncObject&);
	CSyncObject&	operator=(CSyncObject&);
protected:
	CSyncObject(void);
	CSyncObject(void* ptr);
public:
	void* handle;
	virtual ~CSyncObject();
protected:
	virtual bool	Create();
	virtual void	Close();
public:
	virtual bool	TryLock();
	virtual bool	Lock();
	virtual void	Unlock();
};
//-----------------------------------------------
/*
 *
 */
class CMutex : public CSyncObject {
protected:
	pthread_mutex_t 	mutx;
public:
	typedef pthread_mutex_t*	HANDLE;
	CMutex();
	virtual ~CMutex();
protected:
	bool	Create();
	void	Close();
public:
	bool	TryLock();
	bool	Lock();
	void	Unlock();
};
//-----------------------------------------------
/*
 *
 */
class CEvent : public CSyncObject {
protected:
	CMutex					mutx;
	pthread_cond_t		cond;
	bool					signaled;
	bool					auto_reset;
public:
	CEvent(bool signal=false,bool reset=false);
	virtual ~CEvent();
protected:
	bool	Create();
	void	Close();
public:
	void	Wait(int millisectimeout=0);
	void	Signal();
	void	Reset();
	bool	TryLock();
	bool	Lock();
	void	Unlock();
};

#endif /* SYNCOBJECT_H_ */
