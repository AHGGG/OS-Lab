# 实验2

### 相关知识点

#### 2021-5-16

- Posix 信号量与System v信号量的区别:Posix信号量是基于内存的，即信号量值是放在共享内存中的，它是由可能与文件系统中的路径名对应的名字来标识的。而System v信号量测试基于内核的，它放在内核里面，相同点都是它们都可以用于进程或者线程间的同步。

[![ggQDWn.png](https://z3.ax1x.com/2021/05/16/ggQDWn.png)](https://imgtu.com/i/ggQDWn)

- man sem.h : sys/sem.h - XSI semaphore facility,这里也是POSIX标准的扩展。发现有这些函数：int semctl(int, int, int, ...);int semget(key_t, int, int);int semop(int, struct sembuf *, size_t);sem_num，sem_op，sem_flg都是这里的。

- semget - get a System V semaphore set identifier。

- man semaphore.h:也是POSIX里的。
[![gglb3n.png](https://z3.ax1x.com/2021/05/16/gglb3n.png)](https://imgtu.com/i/gglb3n)

- C语言读写文件：
- 字符读写函数  ：fgetc和fputc
- 字符串读写函数：fgets和fputs;fgets(字符数组名,n,文件指针);fputs(字符串,文件指针);
- 数据块读写函数：freed和fwrite;fread(buffer,size,count,fp);fwrite(buffer,size,count,fp);
- 格式化读写函数：fscanf和fprinf;fscanf(文件指针,格式字符串,输入表列);fprintf(文件指针,格式字符串,输出表列);

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

#### 错误记录：
- 


#### 