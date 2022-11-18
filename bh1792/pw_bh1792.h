/////////////////////////////////////////////////////////////////////////////////
// pw_bh1792.h
// 
// Copyright (c) 2016 ROHM Co.,Ltd.
// Copyright (C) 2019 HERBIO Co., Ltd.
// Copyright (c) 2019 Yoshihiro Nakagawa a.k.a. takurx, JJT1BC
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
/////////////////////////////////////////////////////////////////////////////////

#ifndef _PW_BH1792_H_
#define _PW_BH1792_H_

#include <type_def.h>


//===============================================================================
//  Constants
//===============================================================================


//===============================================================================
//  Type Definition
//===============================================================================
typedef struct {
    uint32_t msr       : 3;
    uint32_t reserved1 : 1;
    uint32_t sel_adc   : 1;
    uint32_t reserved2 : 2;
    uint32_t rdy       : 1;
} MEAS_CTRL1;

typedef struct {
    uint32_t cur      : 6;
    uint32_t en1      : 2;
} MEAS_CTRL2;

typedef struct {
    uint32_t cur      : 6;
    uint32_t reserved : 1;
    uint32_t en2      : 1;
} MEAS_CTRL3;

typedef struct {
    uint32_t th_ir_low  : 8;
} MEAS_CTRL4_LOW;

typedef struct {
    uint32_t th_ir_high : 8;
} MEAS_CTRL4_HIGH;

typedef struct {
    uint32_t int_sel  : 2;
    uint32_t reserved : 6;
} MEAS_CTRL5;

typedef struct {
    uint32_t st       : 1;
    uint32_t reserved : 7;
} MEAS_START;


//===============================================================================
//  Extern Global Variables
//===============================================================================


//===============================================================================
//  Public Function Prototypes
//===============================================================================
uint16_t pw_Init(void);
uint16_t pw_StartMeasure(void);
uint16_t pw_OneMoreStartMeasure(void);
uint16_t pw_StopMeasure(void);
uint16_t pw_GetMeasureData(u16_pair_t *data);
uint16_t pw_SetParam(uint8_t type, uint8_t value);
uint16_t pw_GetParam(uint8_t type, uint8_t *value);



//===============================================================================
//  Macro
//===============================================================================



#endif  // _PW_BH1792_H_
