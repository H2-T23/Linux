/*
 * Pipe.cpp
 *
 *  Created on: 2015/09/07
 *      Author: ttm
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Pipe.h"

const int	CPipe::INVALID = -1;

CPipe::CPipe(void){
	fds[READ]=INVALID;
	fds[WRITE]=INVALID;
}

CPipe::~CPipe(void){
}

bool	CPipe::Create(){
	if( pipe(fds) < 0 ){
		return false;
	}
	//printf("%u\n",fcntl(fds[READ], F_GETPIPE_SZ));
	//printf("%u\n",fcntl(fds[WRITE], F_GETPIPE_SZ));
	return true;
}

void	CPipe::Close(){
	close( fds[WRITE] );
	close( fds[READ] );
}

bool	CPipe::Send(const char* buf, size_t siz){
	int ret = write(fds[WRITE], buf, siz);
	if( ret == int(siz) ){
		return true;
	}
	return false;
}

bool	CPipe::Recv(char* buf, size_t siz){
	int ret = read(fds[READ], buf, siz);
	if( ret == int(siz) ){
		return true;
	}
	return false;
}

int		CPipe::FD(CPipe::TYPE type) const {
	return(fds[type]);
}

