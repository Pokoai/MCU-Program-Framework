#ifndef __MAIN_H__
#define __MAIN_H__

/*
 * module：main
 * function: 项目所用外设头文件声明以及类型别名定义
 * author：Guyue
 * 
 */


/*--------------------------- 头文件声明 ----------------------*/

// 系统头文件
#include <reg52.h>     
#include <intrins.h>
#include <string.h>

// 外设配置及端口分配头文件
#include "51config.h"  

// 外设头文件


/*------------------------- 头文件声明 end ----------------------*/




/*---------------------------- 类型定义 -----------------------*/

// 整型
typedef  unsigned char  uchar;  
typedef  unsigned int   uint;
typedef  unsigned long  ulong;

typedef  uchar    u8;
typedef  uint     u16;
typedef  ulong    u32;
typedef  char     int8;
typedef  int      int16;
typedef  long     int32;

// 布尔类型
typedef  char      bool;        
#define  true       1
#define  false      0

/*-------------------------- 类型定义 end -----------------------*/


#endif