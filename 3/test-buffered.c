#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * @brief 实验read/write/buf buffer，发现buf buffer大小1024B，会先读1024的进缓冲区，避免经常进内核空间
 * 
 * @return int 
 */
int main(void)
{
  char buf[5];
  FILE *myfile =stdin;
  printf("before reading\n");
  printf("read buffer base %p\n", myfile->_IO_read_base);
  printf("read buffer length %d\n", myfile->_IO_read_end - myfile->_IO_read_base);
  printf("write buffer base %p\n", myfile->_IO_write_base);
  printf("write buffer length %d\n", myfile->_IO_write_end - myfile->_IO_write_base);
  printf("buf buffer base %p\n", myfile->_IO_buf_base);
  printf("buf buffer length %d\n", myfile->_IO_buf_end - myfile->_IO_buf_base);
  printf("\n");
  fgets(buf, 5, myfile);
  fputs(buf, myfile);
  printf("\n");
  printf("after reading\n");
  printf("read buffer base %p\n", myfile->_IO_read_base);
  printf("read buffer length %d\n", myfile->_IO_read_end - myfile->_IO_read_base);
  printf("write buffer base %p\n", myfile->_IO_write_base);
  printf("write buffer length %d\n", myfile->_IO_write_end - myfile->_IO_write_base);
  printf("buf buffer base %p\n", myfile->_IO_buf_base);
  printf("buf buffer length %d\n", myfile->_IO_buf_end - myfile->_IO_buf_base);

  return 0;
}