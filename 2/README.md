# 实验2

### 相关知识点

#### 2021-5-16

- Posix 信号量与System v信号量的区别:Posix信号量是基于内存的，即信号量值是放在共享内存中的，它是由可能与文件系统中的路径名对应的名字来标识的。而System v信号量测试基于内核的，它放在内核里面，相同点都是它们都可以用于进程或者线程间的同步。

[![ggQDWn.png](https://z3.ax1x.com/2021/05/16/ggQDWn.png)](https://imgtu.com/i/ggQDWn)

----

- man sem.h : sys/sem.h - XSI semaphore facility,这里也是POSIX标准的扩展。发现有这些函数：
- int semget(key_t, int, int);创建一个新的信号量或获取一个已经存在的信号量的键值。成功返回信号量的标识码ID。失败返回-1；
- int semctl(int, int, int, ...);控制信号量的信息。成功返回0，失败返回-1；
- int semop(int, struct sembuf *, size_t);用户改变信号量的值。也就是使用资源还是释放资源使用权。成功返回0，失败返回-1；
```C
struct   sembuf{

     unsigned short  sem_num;//第几个信号量，第一个信号量为0；

     short  sem_op;//对该信号量的操作。

     short _semflg;//IPC_NOWAIT :对信号的操作不能满足时，semop()不会阻塞，并立即返回，同时设定错误信息。IPC_UNDO :程序结束时(不论正常或不正常)，保证信号值会被重设为semop()调用前的值。这样做的目的在于避免程序在异常情况下结束时未将锁定的资源解锁，造成该资源永远锁定。

};
```
- sem_num，sem_op，sem_flg都是这里的。

- semget创建的信号量，可以通过ipcs –s来查看，ipcsm –s semid来删除

- semget - get a System V semaphore set identifier

---

- man semaphore.h:也是POSIX里的。
[![gglb3n.png](https://z3.ax1x.com/2021/05/16/gglb3n.png)](https://imgtu.com/i/gglb3n)

#### 2021-5-30

- C语言读写文件：
- 字符读写函数  ：fgetc和fputc
- 字符串读写函数：fgets和fputs;fgets(字符数组名,n,文件指针);fputs(字符串,文件指针);
- 数据块读写函数：fread和fwrite;fread(buffer,size,count,fp);fwrite(buffer,size,count,fp);
- 格式化读写函数：fscanf和fprinf;fscanf(文件指针,格式字符串,输入表列);fprintf(文件指针,格式字符串,输出表列);

----

- 读写文件的格式：
- r
- r+:写入和读取，文件必须存在。在r的基础上增加“可写”
- rb:二进制模式打开，其他同r
- rb+:二进制模式打开，其他同r+
- w:为写入操作打开一个空文件。若文件不存在，则创建一个文件；若给定的文件已经存在，那么它的内容将被清空
- w+:新建一个文件，先向该文件中写人数据，然后可从该文件中读取数据
- a:追加 如果不存在就创建
- a+:在a的基础上增加可读功能
- wb wb+ ab ab+，同上的rb rb+

---

- 线程间内存共享：sys/shm.h
1. int shmget(key_t key, size_t size, int shmflg);
> key:，非0整数，它有效地为共享内存段命名，成功时返回一个与key相关的共享内存标识符（非负整数），用于后续的共享内存函数。调用失败返回-1.

> size:以字节为单位指定需要共享的内存容量

> shmflg:权限标志, 共享内存的权限标志与文件的读写权限一样, 如果要想在key标识的共享内存不存在时，创建它的话，可以与IPC_CREAT做或操作

2. void *shmat(int shm_id, const void *shm_addr, int shmflg);
> 第一次创建完共享内存时，它还不能被任何进程访问，shmat()函数的作用就是用来启动对该共享内存的访问，并把共享内存连接到当前进程的地址空间

> shm_id是由shmget()函数返回的共享内存标识。

> shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。

> shm_flg是一组标志位，通常为0。

3. int shmdt(const void *shmaddr);
> 共享内存分离并不是删除它，只是使该共享内存对当前进程不再可用

> shmaddr是shmat()函数返回的地址指针，调用成功时返回0，失败时返回-1.

4. int shmctl(int shm_id, int command, struct shmid_ds *buf);
> shm_id是shmget()函数返回的共享内存标识符。

> command是要采取的操作，它可以取下面的三个值 ：
IPC_STAT：把shmid_ds结构中的数据设置为共享内存的当前关联值，即用共享内存的当前关联值覆盖shmid_ds的值;;
IPC_SET：如果进程有足够的权限，就把共享内存的当前关联值设置为shmid_ds结构中给出的值;;
IPC_RMID：删除共享内存段

> buf是一个结构指针，它指向共享内存模式和访问权限的结构。

```C
struct shmid_ds
{
    uid_t shm_perm.uid;
    uid_t shm_perm.gid;
    mode_t shm_perm.mode;
};
```






---

#### 错误记录：
- 


#### 