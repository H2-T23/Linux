/*
 * TimeMeasuring.h
 *
 *  Created on: 2015/08/31
 *      Author: ttm
 */

#ifndef TIME_MEASURING_H_
#define TIME_MEASURING_H_

#include <sys/time.h>

class CTimeMeasuring {
private:
	struct timeval	_begin, _end;

public:
	CTimeMeasuring();
	~CTimeMeasuring();

	void	Begin();
	void	End();
};

#endif//TIME_MEASURING_H_

