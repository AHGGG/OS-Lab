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

//已实现 cp 文件 文件
//已实现 cp 文件 目录 自动拼接文件名(存在问题：如果目录是不存在的 xx.c ----> /x/不存在的路径/xx.c, 会有问题)
//未实现 cp 目录 目录--->全可以分解成 文件到目录
//未实现 cp -r 目录 目录(子目录也一起复制)
void cp_once(char *dir, char *des){
    char buf[2];
    struct stat buffer;
    int status;

    //open
    int res_open = open(dir, O_RDONLY);
    if(res_open == -1){
        printf("open %s error\n", dir);
    }
    int des_open;

    status = stat(des, &buffer);

    //判断如果des是一个目录的话
    if((buffer.st_mode & S_IFMT) == S_IFDIR){
        char *filename = get_file_name(dir);//拿到source 的文件名
        printf("目的地 %s 是目录, 拿到source的文件名:%s\n", des,  filename);
        
        //将source的名字当做des的名字
        //注意：*(des + strlen(des) - 1 ) 是char类型的, 要去掉*号，才是char *类型的
        if(0 == strcmp((des + strlen(des) - 1 ), "/")){
            //如果最后一个是/，dse就直接加名字就好
            char *newdes = malloc(sizeof(des) + sizeof(filename) + 1);
            strcpy(newdes, des);
            strcat(newdes, filename);
            des_open = open(newdes, O_RDWR|O_CREAT, S_IRWXU);
            if(des_open == -1){
                printf("open %s error\n", des);
                exit(0);
            }
            printf("newdes:%s, des_open:%d\n", newdes, des_open);
        }else{
            //des后面 加上/ 号 和文件名字
            char *newdes = malloc(sizeof(des) + sizeof(filename) + 2);
            strcpy(newdes, des);
            strcat(newdes, "/");
            strcat(newdes, filename);
            des_open =  open(newdes, O_RDWR|O_CREAT, S_IRWXU);
            if(des_open == -1){
                printf("open %s error\n", des);
                exit(0);
            }
            printf("newdes:%s, des_open:%d\n", newdes, des_open);
        }
    }else{
        //否则
        printf("目的地 %s 不是目录, 或者是不存在的目录例如：/root/Desktop/5/(open一个不存在的目录也会返回-1), 建议先手动创建目的地目录\n", des);
        des_open =  open(des, O_RDWR|O_CREAT, S_IRWXU);
        if(des_open == -1){
            printf("open %s error\n", des);
            exit(0);
        }
    }

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
    
    strcpy(path, d_entry);//这里的d_entry是文件夹的路径, 如果传入文件的路径就会出错, 所以下面增加判断是否是普通文件

    status = stat(d_entry, &buffer);
    
    //如果传入的argv[1]是目录, 表明要复制的是这个目录里的东西
    if((buffer.st_mode & S_IFMT) == S_IFDIR){
        char *des = malloc(sizeof(path));

        // printf("sizeof(path):%d, des after cpy : %s\n",sizeof(path), des);
        
        DIR *dir = opendir(path);//只能open文件夹 不能传入文件的路径

        while ((currentdp = readdir(dir)) != NULL){
            strcpy(des, path);
            strcat(des, "/");
            char *newpath = strcat(des, currentdp->d_name);

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
                cp_once(newpath, cp_des);
            }
        }
        
        closedir(dir);
        if(1 == is_recur) printf("\t\t========== %s =================\n\n", d_entry);
        else printf("========== %s =================\n\n", d_entry);
    }else if((buffer.st_mode & S_IFMT) == S_IFREG){
        //如果传入的argv[2]是普通文件
        cp_once(d_entry, cp_des);
    }


}

int main(int argc, char **argv)
{

    if(argc != 3){
        printf("请传入复制的source 和 des\n");
        exit(0);
    }
        
    read_recur(argv[1], argv[2], 0);
    // cp_once(argv[1], argv[2]);
    
}