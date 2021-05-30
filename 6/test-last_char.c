#include <stdio.h>
#include <string.h>


void test_strcmp_des(char des[]){
    if(0 == strcmp((des + strlen(des) - 1 ), "/")){
        printf("给出的des路径中 最后一位有/号\n");
    }
}

int main(int argc, char **argv){
    printf("argv[2]:%s, strlen(argv[2]):%d, 最后一位：%c\n", argv[2], strlen(argv[2]), *(argv[2] + strlen(argv[2]) - 1 ));
    
    test_strcmp_des(argv[2]);

}