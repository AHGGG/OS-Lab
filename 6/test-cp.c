#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>//for read()
#include <stdlib.h>//for malloc

#include <regex.h>
#include <string.h>
//已实现 cp 文件 文件
//未实现 cp 文件 目录
//未实现 cp 目录 目录
//未实现 cp -r 目录 目录(子目录也一起复制)
void cp_once(char *dir, char *des){
    char buf[2];

    //open
    int res_open = open(dir, O_RDONLY);
    int des_open = open(des, O_WRONLY|O_CREAT, S_IRWXU);

    //read //write
    while (read(res_open, &buf, 1) > 0)
    {
        write(des_open, buf, 1);
    }

    //close
    close(res_open);
    close(des_open);
}

//定义的时候和形参都要为 src[] 才行 char *src就不行 why？？？
char *get_file_name(char src[]){
    char *ptr = strtok(src, "/");
    char *filename = malloc(1024);
    
	while (ptr != NULL) {
		// printf("ptr=%s\n", ptr);
        strcpy(filename, ptr);
		ptr = strtok(NULL, "/");
	}

    return filename;
}


int main(int argc, char **argv){
    char src[] = "/root/Desktop/OS-Lab/6/test-cp.c";
    char *filename = get_file_name(src);
    printf("filename=%s\n", filename);

    // if(argc < 2){
    //     printf("please input cp from where to where\n");
    // }

    // cp_once(argv[1], argv[2]);


    return 0;
}