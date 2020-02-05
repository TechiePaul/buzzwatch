/***********************************************************************************
 *  @file BT_BaseTypes.h
 ***********************************************************************************
 *  ╦ ╦╔═╗╔╦╗  ┌─┐┌─┐┌┬┐┌─┐  ┌─┐┬  ┬ ┬┌┐
 *  ║║║╠═╣║║║  │  │ │ ││├┤   │  │  │ │├┴┐
 *  ╚╩╝╩ ╩╩ ╩  └─┘└─┘─┴┘└─┘  └─┘┴─┘└─┘└─┘
 ***********************************************************************************
 *  Copyright (c) 2020 WAM code club
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 ***********************************************************************************
 *  Basic Type definitions.
 ***********************************************************************************/

#ifndef __BT_BASETYPES_H__
#define __BT_BASETYPES_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef enum teFUNC_STATUS
{
	BT_SUCCESS = 1,
	BT_FAIL = 0
} teFUNC_STATUS;

typedef enum tBOOL
{
	TRUE = 1,
	FALSE = 0
} tBOOL;

typedef unsigned int tUINT32;

typedef char tCHAR;

typedef int tINT32;

typedef tINT32 tBYTES;

typedef tUINT32 tK_BYTES;

typedef tUINT32 tTIME_H;

typedef tUINT32 tTIME_MS;

typedef tUINT32 tTIME_S;

typedef tUINT32 tTIME_US;


#ifdef __cplusplus
}
#endif
#endif /* __BT_BASETYPES_H__ */

