// print_metadata.c (minimal; no error checking, uses ternaries + bitwise masks)
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
    struct stat st;
    // Use lstat so symlinks show 'l' like `ls -l`
    stat(argv[1], &st);

    char p[11];
    // file type
    mode_t perms = st.st_mode;
    p[0] = S_ISDIR(perms) ? 'd' : '-';

    // user
    p[1] = (perms & S_IRUSR) ? 'r' : '-';
    p[2] = (perms & S_IWUSR) ? 'w' : '-';
    p[3] = (perms & S_IXUSR) ? 'x' : '-';

    // group
    p[4] = (perms & S_IRGRP) ? 'r' : '-';
    p[5] = (perms & S_IWGRP) ? 'w' : '-';
    p[6] = (perms & S_IXGRP) ? 'x' : '-';

    // others
    p[7] = (perms & S_IROTH) ? 'r' : '-';
    p[8] = (perms & S_IWOTH) ? 'w' : '-';
    p[9] = (perms & S_IXOTH) ? 'x' : '-';

    p[10] = '\0';

    printf("size: %lld\n", (long long)st.st_size);
    printf("perms: %s\n", p);
    return 0;
}
