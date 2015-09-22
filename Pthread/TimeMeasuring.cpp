/*
 * TimeMeasuring.cpp
 *
 *  Created on: 2015/09/07
 *      Author: ttm
 */
#include <stdio.h>
#include "TimeMeasuring.h"

CTimeMeasuring::CTimeMeasuring(){
	Begin();
}

CTimeMeasuring::~CTimeMeasuring(){
	End();
}

void	CTimeMeasuring::Begin(){
	gettimeofday(&_begin, NULL);
}

void	CTimeMeasuring::End(){
	gettimeofday(&_end, NULL);
	printf("%f.\n",((_end.tv_sec - _begin.tv_sec) + (_end.tv_usec - _begin.tv_usec) / 1000000.0) );
}



