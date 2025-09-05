// recurse-sample.c (minimal; no error checking)
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void permstr(mode_t m, char p[11]) {
    p[0] = S_ISDIR(m)    ? 'd' : '-';
    p[1] = (m & S_IRUSR) ? 'r' : '-';
    p[2] = (m & S_IWUSR) ? 'w' : '-';
    p[3] = (m & S_IXUSR) ? 'x' : '-';

    p[4] = (m & S_IRGRP) ? 'r' : '-';
    p[5] = (m & S_IWGRP) ? 'w' : '-';
    p[6] = (m & S_IXGRP) ? 'x' : '-';

    p[7] = (m & S_IROTH) ? 'r' : '-';
    p[8] = (m & S_IWOTH) ? 'w' : '-';
    p[9] = (m & S_IXOTH) ? 'x' : '-';

    p[10] = '\0';
}

void recurse(char *dir) {
    DIR *d = opendir(dir);
    struct dirent *e;
    // list current directory (part 2)
    while ((e = readdir(d))) {
        // filter . and ..
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;

        char path[4096];
        // compile new path 
        int n = snprintf(path, sizeof(path), "%s/%s", dir, e->d_name);

        struct stat st;
        stat(path, &st);
        // recurse (part 3)
        if (S_ISDIR(st.st_mode)) {
            recurse(path);
        }

        // filter and print (part 4)
        if (strstr(e->d_name, "hello")) {
            //get and print permstring
            char p[11];
            permstr(st.st_mode, p);
            printf("%s %s\n", p, path);
        }


    }
    closedir(d);
}

int main(int argc, char **argv) {
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);      // Part 0: print current working directory
    recurse(argv[1]);            // start directory (e.g., ".")
    return 0;
}
