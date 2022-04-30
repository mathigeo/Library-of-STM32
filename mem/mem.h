#ifndef _MEM_H
#define _MEM_H
#include "stm32f10x.h"


#ifndef NULL
#define NULL (void *)0
#endif


/*内部内存池*/
#define SRAMIN	 	0
/*外部内存池*/
#define SRAMEX   	1
/*定义支持的SRAM块数*/
#define SRAMBANK 	2	


/*mem1内存参数设定.mem1完全处于内部SRAM里面*/

/*内存块大小为32字节*/
#define MEM1_BLOCK_SIZE			32  
/*最大管理内存*/
#define MEM1_MAX_SIZE			0x00000200  
/*内存表大小,代表有多少块内存*/
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	


/*mem2内存参数设定.mem2的内存池处于外部SRAM里面*/

/*内存块大小为32字节*/
#define MEM2_BLOCK_SIZE			32  
/*最大管理内存*/
#define MEM2_MAX_SIZE			0x00000200  	
/*内存表大小,代表有多少块内存*/
#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	


/*内存管理控制器*/
struct malloc_cortol_struct
{
	/*内存池 管理SRAMBANK个区域的内存，是内存池的入口地址*/
	u8 	*membase[SRAMBANK];	
	/*内存管理状态表，内存管理表的地址*/
	u16 *memmap[SRAMBANK];	
	/*内存管理是否就绪*/
	u8  memrdy[SRAMBANK];	
};


/*用户调用函数*/
void my_mem_init(u8 memx);				
u8 my_mem_perused(u8 memx);				
void myfree(u8 memx,void *paddr);  			
void *mymalloc(u8 memx,u32 size);			
void *myrealloc(u8 memx,void *paddr,u32 size);

#endif //_MEM_H

