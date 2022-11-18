/////////////////////////////////////////////////////////////////////////////////
// sysDef.h
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

#ifndef SYS_DEF_H
#define SYS_DEF_H


//===============================================================================
//  Constants
//===============================================================================
// Error Code: Common
#define ERROR_NONE                      (0x0000U)   // No error

// Error Code: BH1792
#define ERROR_PW_EXIST_SENSOR           (0x1000U)   // No PW Sensor exists
#define ERROR_PW_I2C                    (0x1001U)   // I2C error with PW Sensor
#define ERROR_PW_MEASURING              (0x1100U)   // Must stop the measurement
#define ERROR_PW_NOT_MEASURE            (0x1101U)   // Must start the measurement
#define ERROR_PW_UNKNOWN                (0x1fffU)   // Unknown error

//#define ERROR_BH1792_PRM_CTRL1_FREQ     (0x1200U)   // LED emitting frequency
//#define ERROR_BH1792_PRM_CTRL1_RCYCLE   (0x1201U)   // RCYCLE
#define ERROR_BH1792_PRM_CTRL1_MSR       (0x1201U)    // MSR
//#define ERROR_BH1792_PRM_CTRL2_EN       (0x1202U)   // LED en
//#define ERROR_BH1792_PRM_CTRL2_ONTIME   (0x1203U)   // LED emitting time
#define ERROR_BH1792_PRM_CTRL2_EN1       (0x1202U)    // LED1 en1
#define ERROR_BH1792_PRM_CTRL2_CUR_LED1  (0x1203U)    // LED1 driver current
#define ERROR_BH1792_PRM_CTRL3_EN2       (0x1204U)    // LED2 en2
#define ERROR_BH1792_PRM_CTRL3_CUR_LED2  (0x1205U)    // LED2 driver current
#define ERROR_BH1792_PRM_TYPE            (0x1206U)    // Undefined Parameter

// Error Code: Heart Rate
#define ERROR_HR_MA_PARAM               (0x3000U)   // Moving Average
#define ERROR_HR_IS_WEARING             (0x3001U)   // is_wearing Parameter
// Error Code: Pulse Wave Calculation
#define ERROR_PWCALC_MA_PARAM           (0x3100U)   // Moving Average


//===============================================================================
//  Type Definition
//===============================================================================


//===============================================================================
//  Extern Global Variables
//===============================================================================


//===============================================================================
//  Public Function Prototypes
//===============================================================================


//===============================================================================
//  Macro
//===============================================================================



#endif  // SYS_DEF_H
