/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file heap.h
 * @author chenjiansen(com@baidu.com)
 * @date 2014/05/13 21:12:41
 * @brief 
 *  
 **/




#ifndef  __MIN_HEAP_H_
#define  __MIN_HEAP_H_

typedef struct _min_heap_t
{
    int size;
    int capacity;
    int update_total;
    int buf[0];
}min_heap_t;

min_heap_t* heap_create(int capacity);
void heap_destroy(min_heap_t* heap);
int heap_insert(min_heap_t* heap, int value);
int heap_remove(min_heap_t* heap, int& value);
int heap_top(int& value);
void heap_dump(min_heap_t* heap);





#endif  //__HEAP_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
