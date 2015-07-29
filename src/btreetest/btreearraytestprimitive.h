/************************************************************
**
** file:	btreearraytestprimitive.h
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains primitive code for the b-tree framework's
** test bench to support array data class testing.
**
************************************************************/

#ifndef	BTREEARRAYTESTPRIMITIVE_H
#define	BTREEARRAYTESTPRIMITIVE_H

#include <stdint.h>

#include <iostream>

#include "btreetestcommon.h"
#include "btreetestarray.h"

typedef enum
{
	BTREETEST_ARRAY_PRIMITIVE_SEEK_BEGIN, 
	BTREETEST_ARRAY_PRIMITIVE_SEEK_END, 
	BTREETEST_ARRAY_PRIMITIVE_SEEK_RANDOM
} btreetest_array_primitive_seek_e;

void arrayPrim_add (CBTreeArrayDataIf<arrayEntry_t> *pClArray, uint32_t nEntries, uint32_t &nDebug, btreetest_array_primitive_seek_e eWhere);
void arrayPrim_remove (CBTreeArrayDataIf<arrayEntry_t> *pClArray, uint32_t nEntries, btreetest_array_primitive_seek_e eWhere);
void arrayPrim_replace (CBTreeArrayDataIf<arrayEntry_t> *pClArray, uint32_t nEntries, uint32_t &nDebug, btreetest_array_primitive_seek_e eWhere);
bool arrayPrim_compare (CBTreeArrayDataIf<arrayEntry_t> *pClArray0, CBTreeArrayDataIf<arrayEntry_t> *pClArray1);

#endif // BTREEARRAYTESTPRIMITIVE_H
