# bug

freertos 事件组下面链表出现内存指向非法地址导致hardware fault督促我,原因为时间组下链表指向了一个非法地址，
review了代码并没有发现内存问题，对比freertos代码和rtos的配置，没有问题
发现另一个同事写的函数嵌套了很多层，导致堆栈数据上去，造成栈溢出问题,


## github push commit fail

fatal: unable to access 'https://github.com/jjkkwym/code.git/': GnuTLS recv error (-110): The TLS connection was non-properly terminated.

取消git本身的https代理，使用自己本机的代理
git config --global --unset http.proxy
git config --global --unset https.proxy