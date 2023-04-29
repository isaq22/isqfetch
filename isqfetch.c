#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main () {
    struct utsname sys_info;

    if (uname(&sys_info) != 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    char cmd[128];
    sprintf(cmd, "figlet %s", sys_info.nodename);

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    char buf[128];
    while (fgets(buf, 128, fp) != NULL) {
        printf("%s", buf);
    }
    printf ("\nos: %s", sys_info.sysname);
    printf ("\nkernel: %s", sys_info.release);
    printf ("\narch: %s", sys_info.machine);
    system("printf 'pacman pkgs: ' && pacman -Q | wc -l");
    pclose(fp);
    return 0;
}
