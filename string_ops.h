#pragma once
#ifndef STRING_OPS_H_INCLUDED
#define STRING_OPS_H_INCLUDED

#include<string.h>
#include "str_types.h"

boolean_t startsWith(string_t *input, string_t search_word); 
boolean_t endsWith(string_t *input, string_t search_word);    
boolean_t containsChar(string_t *input, char search);         
boolean_t string_IsANum(string_t input);                      
string_t trim(string_t *input, string_t word_pattern, boolean_t use_asPattern);
string_t trimStart(string_t *input, char trim_char, boolean_t keep_input);       

LONGLONG_t tryParse_ll(string_t *input);
double tryParse_double(string_t *input);

String StringCreate(string_t input, StringType type_);                      
StringArray StringCreateArray(size_t num_of_elements, StringType type_);   
STATUS_t StringDeleteArray(StringArray *string_arrObj);                    
STATUS_t StringCopyArray(StringArray *dst_, StringArray *src_, boolean_t keep_src);
STATUS_t StringInsertIntoArray(StringArray *string_arrObj, String *string_Obj, INDEX_t index);
STATUS_t StringRemoveAt(StringArray *string_arrObj, INDEX_t index);           
STATUS_t StringClearArray(StringArray *string_arrObj);                        
StringArray StringShrinkArray(StringArray *string_arrObj, boolean_t keep_old);
STATUS_t StringChange(String *string_Obj, StringType type_, string_t input);  
STATUS_t StringDelete(String *string_Obj);                                    

extern string_t StrNums;
extern size_t   StrNumsLngth;

#endif // STRING_OPS_H_INCLUDED