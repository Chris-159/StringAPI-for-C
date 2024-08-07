#pragma once
#ifndef STR_MACROS_H_INCLUDED
#define STR_MACROS_H_INCLUDED

#include<stdlib.h>

//    ***Macro to find the first sighting of a character {char__} in array {arr_Name__}***
#define _STR_FIND_CHAR_INDEX(arr_Name__, size__, char__, index_temp__)  \
    index_temp__ = -1;                                                  \
    for (size_t i__ = 0; i__ < size__; i__++)                           \
        if(arr_Name__[i__] == char__) {                                 \
            index_temp__ = i__;                                         \
            break;                                                      \
        }                                                            

//    ***Macro to set the {word__} string to lowercase***
#define _STR_TO_LOWERCASE(word__, word_length__)          \
    for (size_t i__ = 0; i__ < word_length__; i__++)      \
        if (word__[i__] > 64 && word__[i__] < 91)         \
            word__[i__] += 32;                                    

//    ***Macro to set all array elements to zero***
#define _STR_CLEAR_ARRAY(arr_Name__, size__)    \
    for (size_t i__ = 0; i__ < size__; i__++)   \
            arr_Name__[i__] = 0;

//    ***Macro to get String object from a specified StringArray at the specified index***
#define _STRING_AT_P(arrP_objName__, index__) arrP_objName__->string_obj[(index__)]

//    ***Macro to get a string_t (character array) from a String object***
#define _STRING_GET_P(strP_objName__) strP_objName__->buffer

//    ***Macro to deallocate simple pointer***
#define _STR_FREE(ptr__)            \
    free(ptr__); ptr__ = NULL; 

#endif // STR_MACROS_H_INCLUDED