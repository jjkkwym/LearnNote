# basic

memcpy 内存地址重叠问题。
memmove 拷贝到临时内存，再拷贝回来。

IIC时序

# point

free(void *)自动置NULL

自动置NULL并不能解决问题，指针在free后就不应该被引用，如果被重复引用代码逻辑是否存在问题？ 
传参为指针值，并不上指针变量地址，无法对指针进行修改