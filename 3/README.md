# 实验3

### 相关知识点

#### 2021-5-16

- 对全缓冲来说,buffered I/O写总是试图在缓冲区写满之后,再系统调用write)
- _IO_write_ptr始终指向缓冲区中已被用户写入的字符的下一个，flush的时候,将_IO_write_base和_IO_write_ptr之间的字符通过系统调用write写入内核
- myfile->_IO_write_ptr = myfile->_IO_write_base;//标准I/O认为没有数据写入缓冲区,所以永远不会调用write,这样aaa.txt文件得不到写入.

- fsync()：是把内核缓冲刷到磁盘上。fflush():是把C库中的缓冲调用write函数写到磁盘(其实是写到内核的缓冲区)。

- printf函数是一个行缓冲函数？？，先将内容写到缓冲区，满足一定条件后，才会将内容写入对应的文件或流中。满足的条件：1.缓冲区填满;写入的字符中有‘\n’ '\r';调用fflush或stdout手动刷新缓冲区;调用scanf等要从缓冲区中读取数据时，也会将缓冲区内的数据刷新;程序结束时.

- printf实际是向用户空间的IO缓冲写，在满足条件的情况下（条件下面会说）才会调用write系统调用，这样也就提高了内核的效率。[更多内容！！见此处]
[![gWieJK.png](https://z3.ax1x.com/2021/05/17/gWieJK.png)](https://imgtu.com/i/gWieJK)

- 空文件为什么也要读一下，才能判断feof判断是否为空？答案：见test-feof.c中的解释。[更多内容！！见此处]

[更多内容！！见此处]:https://www.cnblogs.com/orlion/p/6258691.html

- man 7 pipe : If all file descriptors referring to the write end of a pipe have been closed, then an attempt to read(2) from the pipe will see end-of-file (read(2) will return 0).  If all file  descriptors  referring  to  the  read end of a pipe have been closed, then a write(2) will cause a SIGPIPE signal to be generated for the calling process.  

---

#### 错误记录：
- 


#### 