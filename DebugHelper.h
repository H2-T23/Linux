/*
 * DebugHelper.h
 *
 *  Created on: 2015/09/25
 *      Author: ttm
 */

#ifndef DEBUGHELPER_H_
#define DEBUGHELPER_H_


namespace DebugHelper
{
	void	trace(const char* fmt, ...);
	void	dumpEx(const unsigned char* buf, const size_t ofs, const size_t siz);
	void	dump(const unsigned char*, const size_t siz);
}


#endif /* DEBUGHELPER_H_ */
