#pragma once


#include <stdlib.h>

typedef struct b_String_slice{
    char* data;
    size_t length;
}b_String_slice;

b_String_slice conversion_fromCstring(char* in_str);
char* conversion_toCstring(b_String_slice in_str);
b_String_slice slice(b_String_slice in_str, size_t startpos, size_t endpos);
b_String_slice string_replace_at(b_String_slice in_str, char replace, size_t index, size_t desiredIndex);
b_String_slice fixBufOverflow(char* in_str);

