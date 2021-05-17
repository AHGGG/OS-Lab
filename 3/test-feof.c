#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * @brief 输入多于4个,少于13个字符,并且以连按两次ctrl+d为结束(不要按回车)，可以看出
 * ,每当满足(_IO_read_end < (_IO_buf_base-_IO_buf_end)) && (_IO_read_ptr == _IO_read_end)时
 * ,标准I/O则认为已经到达文件末尾,feof(stdin)才会被设置其中_IO_buf_base-_IO_buf_end是缓冲区的长度。
 * 也就是说,标准I/O是通过它的缓冲区来判断流是否要结束了的.
 * 这就解释了为什么即使是一个空文件,标准I/O也需要读一次,才能使用feof判断释放为空。
 * 
 * @return int 
 */
int main(void)
{
  char buf[5];
  char buf2[10];

  fgets(buf, sizeof(buf), stdin);//输入要多于4个,少于13个字符才能看出效果
  puts(buf);

  //交替注释下面两行
  stdin->_IO_read_end = stdin->_IO_read_ptr+1;

//   stdin->_IO_read_end = stdin->_IO_read_ptr + sizeof(buf2)-1;
   
  fgets(buf2, sizeof(buf2), stdin);
  puts(buf2);
  if (feof(stdin)) printf("input end\n");
  return 0;
}