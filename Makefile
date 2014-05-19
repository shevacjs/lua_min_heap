

all : lua_min_heap.cpp minheap.c
	g++ -g -fPIC -shared -rdynamic  -o libmin_heap.so lua_min_heap.cpp minheap.c
