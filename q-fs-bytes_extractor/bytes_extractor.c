#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *in  = fopen(argv[1], "rb");
    FILE *out = fopen(argv[2], "wb");

    int start = atoi(argv[3]);
    int end   = atoi(argv[4]);
    size_t num_chars   = end - start;

    fseek(in, start, SEEK_SET);

    char buf[num_chars];                 
    fread(buf, 1, num_chars, in);        //always "1" in the 2nd arg for portability
    fwrite(buf, 1, num_chars, out);

    fclose(in);
    fclose(out);
    return 0;
}
