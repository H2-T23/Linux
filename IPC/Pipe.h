/*
 * Pipe.h
 *
 *  Created on: 2015/08/31
 *      Author: ttm
 */

#ifndef PIPE_H_
#define PIPE_H_


class CPipe {
public:
	static const int INVALID;
	
	enum TYPE {
		READ=0, WRITE, NUM,
	};
private:
	int		fds[NUM];
	
public:
	CPipe();
	~CPipe();

public:
	bool	Create();
	void	Close();
	void	Send(const char* buf, size_t siz);
	void	Recv(char* buf, size_t siz);
	
public:
	int		FD(TYPE type);
};

#endif//PIPE_H_

