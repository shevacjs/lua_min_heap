
require "libmin_heap"

test_min = min_heap.new();

test_min:create(5);

test_min:insert(2);
test_min:insert(3);
test_min:insert(1);
test_min:insert(5);
test_min:insert(5);
test_min:insert(7);

print( test_min );

local info = test_min:serialize();

print (info);



heap2 = min_heap.new();
heap2:attach(info);
print (heap2);

heap2:insert(4);
heap2:insert(6);

print (heap2);

print (test_min);

