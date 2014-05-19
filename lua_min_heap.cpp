/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file lua_heap.cpp
 * @author chenjiansen(com@baidu.com)
 * @date 2014/05/13 23:33:57
 * @brief 
 *  
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern "C"
{
#include "lua.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

}

#include "minheap.h"

static const char* const TIEBA_MIN_HEAP = "shevacjs.heap";

typedef struct _lua_min_heap_t
{
    min_heap_t* heap;
}lua_min_heap_t;

static int min_heap_new(lua_State* L);
static int min_heap_insert(lua_State* L);
static int min_heap_string(lua_State* L);
static int min_heap_create(lua_State* L);
static int min_heap_attach(lua_State* L);
static int min_heap_serialize(lua_State* L);
static int min_heap_unserialize(lua_State* L);

static const struct luaL_Reg min_heap_lib_f[] = 
{
    {"new", min_heap_new},
    {NULL, NULL}

};


static const struct luaL_Reg min_heap_lib_m[] = 
{
    {"insert", min_heap_insert},
    {"create", min_heap_create},
    {"attach", min_heap_attach},
    {"serialize", min_heap_serialize},
    {"unserialize", min_heap_unserialize},
    {"__tostring", min_heap_string},
    {NULL,NULL},
};

static inline lua_min_heap_t* check_min_heap(lua_State* L)
{
    return (lua_min_heap_t*) luaL_checkudata(L,1, TIEBA_MIN_HEAP);
}

int min_heap_new(lua_State* L)
{
    lua_min_heap_t* lua_heap = (lua_min_heap_t*) lua_newuserdata(L, sizeof(lua_min_heap_t));

    luaL_getmetatable(L, TIEBA_MIN_HEAP);
    lua_setmetatable(L, -2);

    lua_heap->heap = NULL;

    return 1;
}

int min_heap_create(lua_State* L)
{
    lua_min_heap_t* lua_heap = check_min_heap(L);
    int capacity = luaL_checknumber(L,2);
    int buf_size = sizeof(min_heap_t) + sizeof(int) * capacity;
    min_heap_t* heap = (min_heap_t*) lua_newuserdata(L, sizeof(unsigned char) * buf_size);
    //min_heap_t* heap = (min_heap_t*) malloc(buf_size);
    heap->size = 0;
    heap->update_total = 0;
    heap->capacity = capacity;

    lua_heap->heap = heap;


    return 1;
}

int min_heap_insert(lua_State* L)
{
    lua_min_heap_t* lua_heap = check_min_heap(L);
    int value = luaL_checknumber(L,2);

    if(NULL == lua_heap->heap)
        return 0;

    heap_insert(lua_heap->heap, value);
    return 0;

}

int min_heap_attach(lua_State* L)
{
    lua_min_heap_t* lua_heap = check_min_heap(L);
    const char* buf = luaL_checkstring(L,2);

    lua_heap->heap = (min_heap_t*) buf;


    heap_dump(lua_heap->heap);

    return 0;

}

int min_heap_serialize(lua_State* L)
{
    lua_min_heap_t* lua_heap = check_min_heap(L);
    int buf_size = sizeof(min_heap_t) + sizeof(int) * lua_heap->heap->capacity;

    lua_pushlstring(L, (char*)lua_heap->heap, buf_size);

    return 1;
}


int min_heap_unserialize(lua_State* L)
{
    lua_min_heap_t* lua_heap = check_min_heap(L);

    return 0;
}

int min_heap_string(lua_State* L)
{
    lua_min_heap_t* lua_heap = check_min_heap(L);
    char info[1024];
    int offset = 0;

    if(NULL == lua_heap->heap)
        return 0;

    min_heap_t* heap = lua_heap->heap;

    offset += snprintf(info + offset, sizeof(info)  - offset, "[min_heap](size:%d,capacity:%d,update_total:%d):",
            heap->size, heap->capacity, heap->update_total);
    
    for(int i = 0; i < heap->size; ++i)
    {
        offset += snprintf(info + offset , sizeof(info) - offset, "%d, ", heap->buf[i]);
    }

    lua_pushstring(L,info);

    return 1;
}


// to implement a OO style opertator, always do:
// pseudo code:
//  local meta_object = getmetatable(object.new()) --> raw metable
//  meta_object.__index = meta_object -->  new meta table
//  meta_object.method1 = xxx1
//  meta_object.method2 = xxx2   ---> object:method1 would run as xxx2

extern "C" int luaopen_libmin_heap(lua_State* L)
{
    luaL_newmetatable(L, TIEBA_MIN_HEAP);
    lua_pushvalue(L,-1);
    lua_setfield(L,-2, "__index");
    luaL_register(L, NULL, min_heap_lib_m);

    luaL_register(L, "min_heap", min_heap_lib_f);

    return 1;

}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
