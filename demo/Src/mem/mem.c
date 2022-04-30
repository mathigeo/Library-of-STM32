#include "mem.h"

/*内存池(32字节对齐)
内部SRAM内存池，数组个数40K，类型U8*/
__align(32) u8 mem1base[MEM1_MAX_SIZE];	

/*使用的FSMC的bank1,区域3,
外部SRAM内存池,绝对位置定位;*/
__align(32) u8 mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000)));					

/*内存管理表
内部SRAM内存池MAP，数组数量为内存块个数，类型U16*/
u16 mem1mapbase[MEM1_ALLOC_TABLE_SIZE];	

/*外部SRAM内存池MAP，在开辟的内存后，开辟内存块个数个u16类型*/
u16 mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000+MEM2_MAX_SIZE)));	

/*内存表大小*/
const u32 memtblsize[SRAMBANK]={MEM1_ALLOC_TABLE_SIZE,MEM2_ALLOC_TABLE_SIZE};
/*内存分块大小*/
const u32 memblksize[SRAMBANK]={MEM1_BLOCK_SIZE,MEM2_BLOCK_SIZE};		
/*内存总大小*/
const u32 memsize[SRAMBANK]={MEM1_MAX_SIZE,MEM2_MAX_SIZE};							


/*内存管理控制器*/
struct malloc_cortol_struct malloc_cortol=
{
	mem1base,mem2base,		/*内存池，把内存池的地址赋值给.membase*/
	mem1mapbase,mem2mapbase,/*内存管理状态表,把状态表地址赋值给.memmap*/
	0,0,  		 			/*内存管理未就绪*/
};



/**
 * @brief 复制内存
 * @param des 目的地址
 * @param src 源地址
 * @param len 需要复制的内存长度(字节为单位)
 * @retval None
 */
void my_mem_cpy(void *des,void *src,u32 len)  
{  
    u8 *xdes=des;
	u8 *xsrc=src; 
    while(len--)*xdes++=*xsrc++;  
}  




/**
 * @brief 设置内存
 * @param s 内存首地址
 * @param c 要设置的值
 * @param num 需要设置的内存大小(字节为单位) 
 * @retval None
 */
void my_mem_set(void *s,u8 c,u32 num)  
{  
    u8 *xs = s;  
    while(num--)*xs++=c;  
}	   



/**
 * @brief 内存管理初始化  
 * @param memx 所属内存块
 *	memx取值为SRAMIN(0),或SRAMEX(1)，
 *	表示对内部或外部SRAM初始化
 * @retval None
 */
void my_mem_init(u8 memx)  
{  	
	/*内存表基地址设置的值			
	这里为什么要*2：内存表是u16类型的数组，
	而my_mem_set中xs是u8类型，每次擦除一位，
	擦除完状态表需要擦两次*/
	
	/*内存状态表数据清零*/ 
	my_mem_set(malloc_cortol.memmap[memx], 0,memtblsize[memx]*2);
	/*内存池所有数据清零*/  
	my_mem_set(malloc_cortol.membase[memx], 0,memsize[memx]);	
	/*内存管理初始化OK*/
	malloc_cortol.memrdy[memx]=1;								  
}



/**
 * @brief 获取内存使用率
 * @param memx 所属内存块
 * @retval 使用率(0~100)
 */
u8 my_mem_perused(u8 memx)  
{  
    u32 used=0;  
    u32 i;  
    for(i=0;i<memtblsize[memx];i++)  
    {  
		/*memmap[memx]是内存表数组*/
        if(malloc_cortol.memmap[memx][i])used++; 
    } 
    return (used*100)/(memtblsize[memx]);  
}



/**
 * @brief 内存分配(内部调用)
 * @param memx 所属内存块
 * @param size 要分配的内存大小(字节)
 * @retval 0XFFFFFFFF,代表错误;其他,内存偏移地址
 */
u32 my_mem_malloc(u8 memx,u32 size)  
{  
    signed long offset=0; 
	/*需要的内存块数*/  
    u32 xmemb;	
	/*连续空内存块数*/
	u32 kmemb=0;
    u32 i;  
    if(!malloc_cortol.memrdy[memx])
	{
		/*未初始化,先执行初始化*/
		my_mem_init(memx);
	}
    if(size==0)
	{
		//不需要分配
		return 0XFFFFFFFF;
	}
	/*获取需要分配的连续内存块数*/
    xmemb=size/memblksize[memx];  
	/*如果所需内存不够一块，则取一块*/
    if(size%memblksize[memx])
	{
		xmemb++;  	
	}
	/*搜索整个内存控制区*/
    for(offset=memtblsize[memx]-1;offset>=0;offset--)  
    {   /*连续空内存块数增加*/
		if(!malloc_cortol.memmap[memx][offset])
		{
			kmemb++;
		}
		else 
		{
			/*连续内存块清零*/
			kmemb=0;								
		}
		/*找到了连续nmemb个空内存块*/
		if(kmemb==xmemb)							
		{
			/*标注内存块非空*/
            for(i=0;i<xmemb;i++)  					 
            {  
                malloc_cortol.memmap[memx][offset+i]=xmemb;  
            }  
			/*返回偏移地址*/
            return (offset*memblksize[memx]);  
		}
    }  
	/*未找到符合分配条件的内存块*/
    return 0XFFFFFFFF;
}  



/**
 * @brief 释放内存(内部调用) 
 * @param memx 所属内存块
 * @param offset 内存地址偏移
 * @retval 0,释放成功;1,释放失败
 */
u8 my_mem_free(u8 memx,u32 offset)  
{  
    int i;  
	/*未初始化,先执行初始化*/
    if(!malloc_cortol.memrdy[memx])
	{
		my_mem_init(memx);    
		/*未初始化*/
        return 1;
    }  
	/*偏移在内存池内*/
    if(offset<memsize[memx])
    {  
		/*偏移所在内存块号码*/
        int index=offset/memblksize[memx];	
		/*内存块数量*/
        int nmemb=malloc_cortol.memmap[memx][index];	
		/*内存块清零*/
        for(i=0;i<nmemb;i++)  						
        {  
            malloc_cortol.memmap[memx][index+i]=0;  
        }  
        return 0;  
		
    }
	else 
	{
		/*偏移超区了*/  
		return 2;
	}
}  



/**
 * @brief 释放内存(外部调用) 
 * @param memx 所属内存块
 * @param ptr 内存首地址 
 * @retval None
 */
void myfree(u8 memx,void *paddr)  
{  
	u32 offset;  
	/*地址为0*/
	if(paddr==NULL)return; 
 	offset=(u32)paddr-(u32)malloc_cortol.membase[memx]; 
	/*释放内存*/
    my_mem_free(memx,offset);	      
}  



/**
 * @brief 分配内存(外部调用) 
 * @param memx 所属内存块
 * @param size:内存大小(字节)
 * @retval 分配到的内存首地址.
 */
void *mymalloc(u8 memx,u32 size)  	
{  
    u32 offset;   
	offset=my_mem_malloc(memx,size);  	   	 	   
    if(offset==0XFFFFFFFF)return NULL;  
    else 
	{
		/*基地址+偏移地址*/
		return (void*)((u32)malloc_cortol.membase[memx]+offset); 
	}		
}  													
	



/**
 * @brief 重新分配内存(外部调用)
 * @param memx 所属内存块
 * @param ptr 旧内存首地址
 * @param size 要分配的内存大小(字节)
 * @retval 新分配到的内存首地址
 */
void *myrealloc(u8 memx,void *paddr,u32 size)  
{  
    u32 offset;    
    offset=my_mem_malloc(memx,size);   	
    if(offset==0XFFFFFFFF)
	{
		return NULL;     
	}
    else  
    {  									   
		/*拷贝旧内存内容到新内存*/
	    my_mem_cpy((void*)((u32)malloc_cortol.membase[memx]+offset),paddr,size);  
		/*释放旧内存*/
        myfree(memx,paddr);  
		/*返回新内存首地址*/		
        return (void*)((u32)malloc_cortol.membase[memx]+offset);			
    }  
}
