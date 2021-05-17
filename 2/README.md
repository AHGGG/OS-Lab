# 实验2

### 相关知识点

#### 2021-5-16

- Posix 信号量与System v信号量的区别:Posix信号量是基于内存的，即信号量值是放在共享内存中的，它是由可能与文件系统中的路径名对应的名字来标识的。而System v信号量测试基于内核的，它放在内核里面，相同点都是它们都可以用于进程或者线程间的同步。

[![ggQDWn.png](https://z3.ax1x.com/2021/05/16/ggQDWn.png)](https://imgtu.com/i/ggQDWn)

- man sem.h : sys/sem.h - XSI semaphore facility,这里也是POSIX标准的扩展。发现有这些函数：int semctl(int, int, int, ...);int semget(key_t, int, int);int semop(int, struct sembuf *, size_t);sem_num，sem_op，sem_flg都是这里的。

- semget - get a System V semaphore set identifier。

- man semaphore.h:也是POSIX里的。
[![gglb3n.png](https://z3.ax1x.com/2021/05/16/gglb3n.png)](https://imgtu.com/i/gglb3n)


---

#### 错误记录：
- 


#### 