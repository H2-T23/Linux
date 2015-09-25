/*
 * DebugHelper.cpp
 *
 *  Created on: 2015/09/25
 *      Author: ttm
 */

#include <stdio.h>


namespace DebugHelper
{
	void	dump(unsigned char* buf, size_t siz){
		for(int i=0;i<int(siz);i++){
			if( (i%16) == 0 ){
				printf("%08X ",(unsigned int)(&buf[i]-buf));
			}
			printf("%02X ",buf[i]);
			if( ((i+1)%16) == 0 ){
				printf("\n");
			}else if( ((i+1)%8) == 0 ){
				printf(" ");
			}
		}
		printf("\n");
	}
}


