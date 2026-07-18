#include "b_core.h"
#include <stdlib.h>
#include <string.h>

b_String_slice* conversion_fromCstring(char* in_str){
    size_t len = strlen(in_str);
    b_String_slice tmp = {NULL, len};
    b_String_slice* converted = malloc(sizeof(tmp));
    for (size_t i = 0; i<len; i++) {
        converted->data[i] = in_str[i];
    }
    return converted;
}

// char* conversion_toCstring(b_String_slice in_str){
//
// }
//
// b_String_slice slice(b_String_slice in_str, size_t startpos, size_t endpos){
//
// }
//
// b_String_slice string_replace_at(b_String_slice in_str, char replace, size_t index, size_t desiredIndex){
//
// }
//
// b_String_slice fixBufOverflow(char* in_str);
//
