/*
 * Thread.h
 *
 *  Created on: 2015/09/02
 *      Author: ttm
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

//-----------------------------------------------
/*
 *
 */
class IRunnable {
public:
	virtual ~IRunnable(void){}
	virtual void	run(void) = 0;
};
//-----------------------------------------------
/*
 *
 */
class CThread : public IRunnable {
private:
	static void*	EntryPoint(void*);
protected:
	pthread_t		thread;
	IRunnable*		pRunnable;
public:
	CThread(void);
	CThread(IRunnable* runable);
	virtual ~CThread(void);
public:
	bool	Create();
	void	Join();
protected:
	virtual void run(void);
};


#endif /* THREAD_H_ */
