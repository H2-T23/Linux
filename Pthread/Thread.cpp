/*
 * Thread.cpp
 *
 *  Created on: 2015/09/02
 *      Author: ttm
 */

#include <iostream>
#include "Thread.h"


using namespace std;

//-----------------------------------------------
/*
 *
 */
CThread::CThread(void)
	: thread(0)
	, pRunnable(NULL){
}
CThread::CThread(IRunnable* runable)
	: thread(0)
	, pRunnable(runable){
}
CThread::~CThread(void){
	if(pRunnable){
		delete pRunnable;
	}
}
bool	CThread::Create(){
	return(pthread_create(&thread, NULL, EntryPoint, (void*)(pRunnable?pRunnable:this))==0);
}
void	CThread::Join(){
	pthread_join(thread, NULL);
}
void*	CThread::EntryPoint(void* lpParam){
	IRunnable* pRun = (IRunnable*)lpParam;
	if( pRun ){
		pRun->run();
	}
	return NULL;
}
void CThread::run(void){
	cout<<"CThread::run()."<<endl;
}
