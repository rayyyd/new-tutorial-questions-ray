#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *in  = fopen(argv[1], "rb");
    if (in == NULL) {
        perror(argv[1]);
        exit(1);
    }
    FILE *out = fopen(argv[2], "wb");
    if (out == NULL) {
        perror(argv[1]);
        exit(1);
    }

    int start = atoi(argv[3]);
    int end   = atoi(argv[4]);
    size_t num_chars   = end - start;

    if(fseek(in, start, SEEK_SET) == -1) {
        fprintf(stderr, "seeking failed\n");
        exit(1);
    };
    

    char buf[num_chars];                 
    if (fread(buf, 1, num_chars, in) != num_chars) {
        fprintf(stderr, "not enough bytes to read\n");
        exit(1);
    };        //always "1" in the 2nd arg for portability
    if (fwrite(buf, 1, num_chars, out) != num_chars) {
        fprintf(stderr, "error writing to file\n");
        exit(1);
    };

    fclose(in);
    fclose(out); 
    return 0;
}
