/*
 * DebugHelper.cpp
 *
 *  Created on: 2015/09/25
 *      Author: ttm
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

namespace DebugHelper
{
	FILE*	out = stderr;	// stdout;

	void	trace(const char* fmt,...){
		va_list	args;

		int		cnt = 0;
		int		siz = 128;
		char*	buf = (char*)malloc(siz);

		while( 1 )
		{
			va_start(args,fmt);
			cnt = vsnprintf(buf, siz, fmt, args);
			va_end(args);

			if( cnt < 0 ){
				free(buf);
				return;
			}

			if( cnt < siz ){
				break;
			}

			siz = cnt + 1;

			char* ptr = (char*)realloc(buf, siz);
			if( ptr == NULL ){
				free(ptr);
				return;
			}else{
				buf = ptr;
			}
		}
		fprintf(out,"%s\n",buf);
		free(buf);
	}

	void	dumpEx(const unsigned char* buf, const size_t ofs, const size_t siz){
		for(size_t i=ofs; i<(ofs+siz); i++){
			if( (i%16) == 0 ){
				fprintf(out,"%08X ",(unsigned int)(&buf[i]-buf));
			}
			fprintf(out,"%02X ",buf[i]);
			if( ((i+1)%16) == 0 ){
				fprintf(out,"\n");
			}else if( ((i+1)%8) == 0 ){
				fprintf(out," ");
			}
		}
		fprintf(out,"\n");
	}

	void	dump(const unsigned char* buf, const size_t siz){
		dumpEx(buf,0,siz);
	}
}


