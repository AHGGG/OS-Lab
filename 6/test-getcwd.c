#define _SVID_SOURCE
/* print files in current directory in reverse order */
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int
main(void)
{
    struct dirent **namelist;
    int n;
    printf("getcwd = %s\n", getcwd(NULL, 0));

}