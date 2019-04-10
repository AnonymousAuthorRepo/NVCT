#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_include.h"
//#include <linux/mm.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt",on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif

#define DOUBLE "double"
#define INT "int"
#define FLOAT "float"

#define LINESIZE        64
#define LINEBITS        6
#define spanlines(start, end) \
        (((end - (start & ~(LINESIZE - 1))) >> LINEBITS) + 1)

void flush_dcache_range(unsigned long start, unsigned long end)
{
        unsigned long lines = spanlines(start, end-1);
        //printf("start = %lu end = %lu\n",start,end);
        //printf("lines = %lu\n",lines);
        unsigned long i, flags;

        start &= ~(LINESIZE - 1);

        //local_irq_save(flags);

        for (i = 0; i < lines; i++) {
                _mm_clflushopt(start);
                //_mm_clflush(start);
                //_mm_clwb(start);
                start += LINESIZE;
        }
        //local_irq_restore(flags);
}


void consistent_data(void* addr, char type[], int size)
{
    //printf("The address is %x, the type is %s, the size is %d\n", addr, type, size);
}

void crucial_data(void* addr, char type[], int size)
{
    printf("The address is %x, the type is %s, the size is %d\n", addr, type, size);
}

void readonly_data(void* addr, char type[], int size)
{
    //printf("The address is %x, the type is %s, the size is %d\n", addr, type, size);
}

void flush_whole_cache()
{
	printf("Flush the whole cache\n");
}

void start_crash()
{
	printf("crash could happen!\n");
}

void end_crash()
{
	printf("crash wouldn't happen anymore!\n");
}

void clflush(void* addr)
{
	_mm_clflushopt(addr);
}

void clwb(void* addr)
{
	_mm_clwb(addr);
}

void mfence()
{
	_mm_mfence();
}

void clflushopt( void* addr)
{

}
