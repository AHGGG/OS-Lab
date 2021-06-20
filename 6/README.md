# 实验6

### 相关知识点

#### 2021-5-19

- ln : 创建硬链接，可以用不同的文件名访问同样的内容；对文件内容进行修改，会影响到所有文件名；但是，删除一个文件名，不影响另一个文件名的访问。

- ls -li : 能看到文件的链接数

- readdir(DIR *drip) : 返回drip指向的目录中的 下一个目录入口的指针，如果到达目录的尾部或者遇到问题返回NULL。

- ulimit -a:看看core file多大, 如果是0的话，ulimit -c 1024 来指定要生成的core文件的大小

- gdb core-file core.9266：来查看发生错误的原因

- gdb -c core:看是在哪一行 发生错误的，进去后输入where，就可以看到是哪个函数发生错误

- grep显示关键词所在行的内容： | grep -2 关键词，显示关键词前后两行的内容！

- int open(const char * pathname, int flags) : 
- int open(const char * pathname, int flags, mode_t mode) : flags---> 文件的读写权限(r、w、rw) | O_CREAT\O_APPEND等, mode是创建文件时候要赋予文件什么样的权限。

- ssize_t  write( int filedes,  const void *buf, size_t  nbytes) 函数：write() writes up to count bytes from the buffer pointed buf to the file referred to by the file descriptor fd.

- lseek获取当前读取的位置：Upon  successful  completion, lseek() returns the resulting offset location as measured in bytes from the beginning of the file.  On error, the value (off_t) -1 is returned and errno is set to indicate the error.

- 内存泄露是指程序运行过程中的，所以malloc后要记得free，不然随着程序的运行堆内存只会越来越少。
- C语言并没有Java一类的垃圾回收机制, 所有动态申请的内存都需要自行释放, 打开的设备，管道，套接字等等必须自己关闭，不然就一直存在不会自动释放的，在进程结束后系统回收，不过这个不是c语言的，而是操作系统的。进程结束后，进程的所有内存都将被释放，包括堆上的内存泄露的内存。原因是，当进程结束时，GDT、LDT和页目录都被操作系统更改，逻辑内存全部消失，可能物理内存的内容还在但是逻辑内存已经从LDT和GDT删除，页目录表全部销毁，所以内存会被全部收回。

- 


---

#### 记录：
- 


#### 