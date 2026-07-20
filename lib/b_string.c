#include "b_core.h"
#include <stdlib.h>
#include <string.h>

b_String* conversion_fromCstring(char* in_str){
    size_t len = strlen(in_str);
    b_String tmp = {NULL, len};
    b_String* converted = malloc(sizeof(tmp));
    for (size_t i = 0; i<len; i++) {
        converted->data[i] = in_str[i];
    }
    return converted;
}

// char* conversion_toCstring(b_String in_str){
//
// }
//
// b_String slice(b_String in_str, size_t startpos, size_t endpos){
//
// }
//
// b_String string_replace_at(b_String in_str, char replace, size_t index, size_t desiredIndex){
//
// }
//
// b_String fixBufOverflow(char* in_str);
//
