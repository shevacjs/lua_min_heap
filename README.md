
## 最小堆的lua扩展实现 ##

### 特点说明 ###

* 支持序列化/反序列化的lua min heap
* 支持in place update string，避免内存浪费，提升性能


### 接口 ###

	int insert ( int  value ) : 插入一个值
	int create ( int heap_size) : 创建一个最小堆，heap_size为堆大小
	int attach ( string info ) : 管理到一个lua string，改string对象为之前序列化的信息，用于反序列化
	string serialize () : 序列化该 min heap对象到string
	


### demo ###

请见 test.lua
