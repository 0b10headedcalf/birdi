#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "b_core.h"
#include "b_string.c"

char* loadShader(const char* file){
    FILE* fp;
    b_String buf;

    fp = fopen(file,"rb");
    if(fp == NULL){
        fprintf(stderr,"Unable to open %s!",file);
    }
    fseek(fp,0L,SEEK_END);
    buf.length = ftell(fp);
    fclose(fp);

    //TODO: implement loading contents into memory
    //
    return buf.data;
}


//debug
// int main(int argc, char *argv[])
// {
//     printf("%s", loadShader(argv[1]));
//     return EXIT_SUCCESS;
// }
