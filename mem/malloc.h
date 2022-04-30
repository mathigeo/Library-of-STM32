#ifndef __MEMORY_H
#define __MEMORY_H

#include "mem.h"


#define mem_init()          my_mem_init(SRAMIN)
#define mem_perused()       my_mem_perused(SRAMIN)
#define	malloc(size)        mymalloc(SRAMIN,size)
#define realloc(p,size)     realloc(SRAMIN,p,size)
#define free(p)             myfree(SRAMIN,p)


#endif //__MEMORY_H


