# 实验6

### 相关知识点

#### 2021-5-19

- ln : 创建硬链接，可以用不同的文件名访问同样的内容；对文件内容进行修改，会影响到所有文件名；但是，删除一个文件名，不影响另一个文件名的访问。

- ln -s file soft_flie_name: 创建软链接

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

- getcwd(NULL, 0):这样不传入buf指针和buf的size，可以根据具体的情况帮你分配。从而拿到返回的工作目录绝对路径。

- readdir()函数：返回一个指向dirent结构体的指针，这个指针代表 目录指针 指向的 目录流 中的下一个 目录入口。returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred。

- 硬链接：与普通文件没有什么不同，inode都指向同一个文件在硬盘中的区块。删去原文件，通过刚才的硬链接还是能够访问到文件。
- 软连接：保存了其代表的文件的绝对路径，是另一种文件，在硬盘上有独立的区块，访问时替换自身路径。（如果删去软链接指向的文件，再echo xxx >> soft中去，发现文件又在了，写的时候又访问到了软连接代表的绝对路径了，）

- man 2 stat:看到数据接口，blocksize是I/O文件系统块的大小，block是该文件所在哪个块上。

- stat.h中的关于文件的宏定义：
[![RF3v3q.png](https://z3.ax1x.com/2021/06/20/RF3v3q.png)](https://imgtu.com/i/RF3v3q)
- 可以看到倒数第4位，也就是10-12这三个bit位，一个是执行的时候设置user id，作用是比如子用户要修改自己的密码，但是passwd的权限是root，所以root把这个程序标记为setuid，所以子用户在执行的时候能够短暂的获得root权限。
- chmod u+x myfile：set the file to be user-executable with the permission u+x, the setuid permission comes into effect。

- ANCI属于用户态，对应的也要操作内核，即open，close，read，write，符合POSIX标准。注意ANSI与POSI的区别在于：一个用户层，一个内核；ANSI提供一个缓冲区机制，POSIX不提供，值得注意的是POSIX有个内核缓冲区，区别于ANSI的缓冲区机制，标准C设置的缓冲区在用户空间，这个在内核空间


---

#### 记录：
- 


#### 