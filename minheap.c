/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file /home/users/chenjiansen/dev/minheap/minheap.c
 * @author chenjiansen(com@baidu.com)
 * @date 2014/05/17 19:14:25
 * @brief 
 *  
 **/

#include "minheap.h"

#include <stdio.h>
#include <stdlib.h>

#define _CJS_DEBUG_

#ifdef _CJS_DEBUG_

#define cjs_log(fmt, ...) fprintf(stdout,"%s %d: "fmt"\n", __FILE__, __LINE__, ## __VA_ARGS__)
#define cjs_log_err(fmt, ...) fprintf(stderr,"%s %d: "fmt"\n", __FILE__, __LINE__, ## __VA_ARGS__)

#else

#define cjs_log(fmt, ...) 
#define cjs_log_err(fmt, ...)

#endif

static void filterup(min_heap_t* heap, int start)
{
	int j=start,i=(j-1)/2;
    int temp = heap->buf[j];
	while( j > 0)
	{
		if( heap->buf[i] <= temp)
		{
			break;
		}
		else
		{
			heap->buf[j] = heap->buf[i];
			j = i;
			i=(i-1)/2;
		}
	}

	heap->buf[j] = temp;
}

static void filterdown(min_heap_t* heap, int start, int end)
{
	int i=start,j=2*i+1;
    int temp = heap->buf[i];
	while(j <= end)
	{
		if( j < end && heap->buf[j] > heap->buf[j+1] )
		{
			j++;
		}

		if(temp <= heap->buf[j])
		{
			break;
		}
		else
		{
			heap->buf[i] = heap->buf[j];
			i = j;
			j = 2*i+1;
		}
	}

    heap->buf[i] = temp;

}

min_heap_t* heap_create(int capacity)
{
    int buf_size = sizeof(min_heap_t) + sizeof(int) * capacity;
    min_heap_t* heap = (min_heap_t*)malloc(buf_size);
    heap->size = 0;
    heap->update_total = 0;
    heap->capacity = capacity;

    return heap;
}

void heap_destroy(min_heap_t* heap)
{
    free(heap);
}


int heap_insert(min_heap_t* heap, int value)
{
    ++ heap->update_total;
    if(heap->capacity == heap->size)
    {
        cjs_log("is full!");
        int temp;
        //基于最小堆的特性，去掉最小的
        if(value > heap->buf[0])
        {
            heap->buf[0] = value;
            filterdown(heap, 0, heap->size - 1);
            /*
             *heap->buf[ heap->size -1 ] = value;
             *filterup(heap, heap->size);
             */
            return 0;
        }
        else
        {
            cjs_log("heap is full, and new value[%d] is bigger than all, skip insert!", value);
        }

        return -1;
    }

    heap->buf[ heap->size ] = value;
    filterup(heap, heap->size);
    heap->size ++;

    return 0;

}

int heap_remove(min_heap_t* heap, int& value)
{
    if( 0 == heap->size)
        return -1;

	value = heap->buf[0];
	heap->buf[0] = heap->buf[heap->size - 1];
    heap->size --;
	filterdown(heap, 0, heap->size - 1);
	return 0;
}

void heap_dump(min_heap_t* heap)
{
    int i;
    for(i = 0; i < heap->size; ++i )
    {
        printf("%d, ", heap->buf[i]);
    }

    printf("\n");
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
