#pragma once
#ifndef STR_TYPES_H_INCLUDED
#define STR_TYPES_H_INCLUDED

#include "types.h"

#define STRING_EMPTY NULL

typedef char*       string_t;   // string type

/* The types of the String objects, it represents the size of a String */
typedef enum str_type {
    STRING_4 = 4,           //    3 characters
    STRING_8 = 8,           //    7 characters
    STRING_16 = 16,         //   15 characters
    STRING_32 = 32,         //   31 characters
    STRING_64 = 64,         //   63 characters
    STRING_128 = 128,       //  127 characters
    STRING_256 = 256,       //  255 characters
} StringType;

/* The String object and it's attributes */
typedef struct str_obj {
    size_t length;             // how many characters the String contains
    StringType type_;          // the type of the String
    boolean_t empty;           // indicator if it contains any characters
    char buffer[1];            // the storage of the characters
} *String, STRING;

/* The String array object, 
   which contains multiple Strings and their attributes */
typedef struct str_objArr {    
    size_t size;           // how many Strings contains the array
    StringType type_;      // the type of each String
    String *string_obj;   // the storage of the Strings
} *StringArray, STRING_ARRAY;

#endif // STR_TYPES_H_INCLUDED