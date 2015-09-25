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
	CPipe(void);
	~CPipe(void);

public:
	bool	Create();
	void	Close();
	bool	Send(const char* buf, size_t siz);
	bool	Recv(char* buf, size_t siz);
	
public:
	int		FD(CPipe::TYPE type) const;
};

#endif//PIPE_H_

