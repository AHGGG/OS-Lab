# 实验1

### 相关知识点

#### 2021-5-14

- POSIX：表示可移植操作系统接口（Portable Operating System Interface ）。电气和电子工程师协会（Institute of Electrical and Electronics Engineers，IEEE）最初开发 POSIX 标准，是为了提高 UNIX 环境下应用程序的可移植性。然而，POSIX 并不局限于 UNIX。许多其它的操作系统，例如 DEC OpenVMS 和 Microsoft Windows NT，都支持 POSIX 标准，尤其是 IEEE Std. 1003.1-1990（1995 年修订）或 POSIX.1，POSIX.1 提供了源代码级别的 C 语言应用编程接口（API）给操作系统的服务程序，例如读写文件。POSIX.1 已经被国际标准化组织（International Standards Organization，ISO）所接受，被命名为 ISO/IEC 9945-1:1990 标准。
- Single UNIX Specification：POSIX.1标准的超集，定义了一些附加的接口，这些接口扩展了基本的POSIX.1规范的功能。相应的系统接口全集被称为X/Open系统接口（**XSI**，X/Open System Interface） ， XSI还定义了实现必须支持的POSIX.1的哪些可选部分才能认为是遵循XSI的。它们包括文件同步，存储映射文件，存储保护及线程接口。只有遵循XSI的实现才能称为UNIX操作系统。

- pthread_create和fork clone 的区别：fork调clone, clone调do_fork(do_fork是内核函数, 不是系统调用). 当然fork也可以直接调do_fork, 具体怎么做的, 请参看内核代码sys_fork的实现.pthread_create是调的clone.简单的说clone就是fork的"泛化"版. 通过clone创建一个新进程时可以指定很多参数, 比如是否共享内存空间等等. Linux内核并没有对线程的实现, 一切都是进程, 线程简单地说不过是共享内存空间的进程而已(当然可能还有点别的细节, 比如是否共享信号处理, 文件描述符之类的).内核中一个task_struct对象代表一个进程/task/调度对象.[原文链接]


- 对Linux系统来说, 创建一个新线程和创建一个新进程开销是基本一样的(简单的说内核的眼里只有进程, 或者只有任务). 线程切换的开销和进程切换的开销, 主要是切换时是否刷新页表(MMU TLB), 也就是是否切换虚拟内存空间所对应的物理内存页. 别的几乎一致. 嗯, 线程切换是要快一些.[原文链接]

#### 2021-5-15

- 信号量(semapthore)和互斥量(mutex)的区别：mutex是服务于共享资源的互斥访问；而semaphore是服务于多个线程间的执行的逻辑顺序的。

#### 2021-5-16

- 有名、无名信号量的区别：无名信号量，由于其没有名字，所以适用范围要小于有名信号量。只有将无名信号量放在多个进程或线程都共同可见的内存区域时才有意义，否则协作的进程无法操作信号量，达不到同步或互斥的目的。有名信号量，多个不相干的进程可以通过名字来打开同一个信号量，从而完成同步。[区别]

[区别]:https://blog.csdn.net/qq_38813056/article/details/85706006

- void pthread_exit( void * value_ptr ) : pthread_exit函数唯一的参数value_ptr是函数的返回代码，只要pthread_join中的第二个参数value_ptr不是NULL，这个值将被传递给value_ptr。

- 互斥锁的静态初始化和动态初始化有什么区别:动态初始化在堆中创建，不用了需要删除以释放内存；静态初始化在静态存储区，初始化之后直接用就可以，不用了也不需要删除。

- restrict关键字：只用于限制指针，告诉编译器，所有修改该指针指向内存中内容的操作，只能通过本指针完成。不能通过除本指针以外的其他变量或指针修改。

- sem_init第二个参数表示线程间共享(1代表可进程间共享), 第三个参数代表初始值


---

{ { 0, 0, 0, 0, 0, __PTHREAD_SPINS, { 0, 0 } } }
```C
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
#ifdef __x86_64__
    unsigned int __nusers;
#endif
    /* KIND must stay at this position in the structure to maintain
       binary compatibility.  */
    int __kind;
#ifdef __x86_64__
    short __spins;
    short __elision;
    __pthread_list_t __list;
# define __PTHREAD_MUTEX_HAVE_PREV	1
/* Mutex __spins initializer used by PTHREAD_MUTEX_INITIALIZER.  */
# define __PTHREAD_SPINS             0, 0
#else
    unsigned int __nusers;
    __extension__ union
    {
      struct
      {
	short __espins;
	short __elision;
# define __spins __elision_data.__espins
# define __elision __elision_data.__elision
# define __PTHREAD_SPINS         { 0, 0 }
      } __elision_data;
      __pthread_slist_t __list;
    };
#endif
  } __data;
  char __size[__SIZEOF_PTHREAD_MUTEX_T];
  long int __align;
} pthread_mutex_t;
```


[原文链接]:http://bbs.chinaunix.net/forum.php?mod=viewthread&tid=3766087&highlight=&page=1

#### 错误记录：
- 如果直接gcc 1.c -o 1：会出现错误undefined reference to 'pthread_create'、undefined reference to `pthread_join', 解决办法：用gcc后面加上-lpthread（具体为什么见笔记），或者用makefile

- stray ‘\302’ in program: 解决：命令行输入od -c 文件名，找到前面数字对应的地方，删去就好了。刚刚我啥也没改反复make了几次就好了？？？可能是注释中哪儿有问题，刚刚是删了又加上make的。
#### 