/*
 * Pipe.cpp
 *
 *  Created on: 2015/09/07
 *      Author: ttm
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
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
	return true;
}

void	CPipe::Close(){
	close( fds[WRITE] );
	close( fds[READ] );
}

void	CPipe::Send(const char* buf, size_t siz){
	write(fds[WRITE], buf, siz);
}

void	CPipe::Recv(char* buf, size_t siz){
	read(fds[READ], buf, siz);
}

int		CPipe::FD(CPipe::TYPE type) const {
	return(fds[type]);
}

