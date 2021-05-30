#define _SVID_SOURCE
/* print files in current directory in reverse order */
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>

int
main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while (n--) {
            printf("d_ino:%d, d_type:%c, d_name:%s\n", namelist[n]->d_ino, namelist[n]->d_type, namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }
}