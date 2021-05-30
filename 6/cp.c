#define _SVID_SOURCE//放在第一行, alphasort才行？
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>//for malloc
#include <fcntl.h>

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

void read_recur(char *d_entry, char *cp_des,int is_recur){
    if(1 == is_recur) printf("\t\t========== %s =================\n", d_entry);
    else printf("========== %s =================\n", d_entry);
    struct dirent *currentdp;
    struct stat buffer;
    int status;
    char path[1024] = "/root/Desktop/OS-Lab";
    strcpy(path, d_entry);
    char *des = malloc(sizeof(path));

    // printf("sizeof(path):%d, des after cpy : %s\n",sizeof(path), des);
    
    DIR *dir = opendir(path);

    while ((currentdp = readdir(dir)) != NULL){
        strcpy(des, path);
        strcat(des, "/");
        char *newpath = strcat(des,currentdp->d_name);

        status = stat(newpath, &buffer);

        char *filetype;

        switch ((buffer.st_mode & S_IFMT))
        {
            case S_IFDIR:
                /* 目录文件 */
                filetype = "目录";
                break;
            case S_IFCHR:
                /* 字符设备*/
                filetype = "字符设备";
                break;
            case S_IFBLK:
                /* 块设备 */
                filetype = "块设备";
                break;
            case S_IFREG:
                /* 普通文件 */
                filetype = "普通文件";
                break;
            case S_IFIFO:
                /* FIFO */
                filetype = "FIFO";
                break;
            case S_IFLNK:
                /* 符号链接 */
                filetype = "符号链接";
                break;
            case S_IFSOCK:
                /* 套接字 */
                filetype = "套接字";
                break;
            default:
                filetype = "default";
                break;
        }
        
        if(1 == is_recur) printf("\t\t%-84s st_mode : %06o\tst_size : %6d\tfiletype:%s\n", newpath, buffer.st_mode, buffer.st_size, filetype);
        else printf("%-84s st_mode : %06o\tst_size : %6d\tfiletype:%s\n", newpath, buffer.st_mode, buffer.st_size, filetype);
        
        if((buffer.st_mode & S_IFMT) == S_IFDIR){
            //是目录, 且是. 和 .. 
            if(0 == strcmp(currentdp->d_name, ".") || 0 == strcmp(currentdp->d_name, "..")){
                //啥也不做, printf("currentdp->d_name:%s, 识别到当前目录\n", currentdp->d_name);
            }else{
                //是目录, 但不是. 或 .. ,就再次调用
                printf(">>>>>>>>>>>>>>>%s是目录, 但是不是. 和 .., 下面进行递归调用=================\n", newpath);
                read_recur(newpath, cp_des, 1); 
            }
        }else if((buffer.st_mode & S_IFMT) == S_IFREG){
            //如果是普通文件 则复制到 target
            // cp_once(newpath, cp_des);
        }

        
    }
    
    closedir(dir);
    if(1 == is_recur) printf("\t\t========== %s =================\n\n", d_entry);
    else printf("========== %s =================\n\n", d_entry);
}

int main(int argc, char **argv)
{

    if(argc != 3){
        printf("请传入复制的source 和 des\n");
        exit(0);
    }
    read_recur(argv[1], argv[2], 0);
    
}