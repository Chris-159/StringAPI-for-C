#include<stdio.h>
#include<math.h>

#include "string_ops.h"
#include "str_macros.h"

string_t StrNums = "0123456789";
size_t StrNumsLngth = 10;

/// @brief Decides if the {input} word STARTS with {search_word}
/// @param input string_t*
/// @param search_word string_t
/// @return false -> the {input} is NULL or the {input} does not starts with {search_word}
/// @return true -> the {input} starts with {search_word}
boolean_t startsWith(string_t *input, string_t search_word) {
    if (input == STRING_EMPTY)
        return false;

    boolean_t it_was_null = false, output = false;
    if (search_word == STRING_EMPTY) {    // if the search word is NULL then search for empty space
        search_word = (string_t)malloc(sizeof(char) * 2);

        if (search_word == STRING_EMPTY)
            return false;

        //strcpy_s(search_word, 2, " \0");
        strcpy(search_word, " \0");
        it_was_null = true;
    }
    
    size_t search_word_lngth = strlen(search_word);
    size_t whole_lngth = strlen(*input);
    int matches = 0;
    if (search_word_lngth > 1) // [1] if the search word is a string
    {
        for (size_t i = 0, index = 0; i < whole_lngth; i++)
        {
            if ((*input)[i] == search_word[index]) {  // [1.2] if the current character matches
                if (index < search_word_lngth) // [1.2.1] if the seatch word index is within range
                    index++;
                else {                         // [1.2.2] else we went through the string and found no missmatch
                    output = true;
                    break;
                }

                matches++;
            } else {                                  // [1.2] else we found a missmatch
                if (matches < search_word_lngth)  // [1.2.1] if the input strings index length is < the search word length
                    output = false;
                else                              // [1.2.2] else we analysed all the characters and no missmatch
                    output = true;

                break;
            }
        }        
    } else                   // [1] else the search word is a character
        if ((*input)[0] == search_word[0]) // [1.2] if the character is a match            
            output = true;

    if (it_was_null) { _STR_FREE(search_word); } // [2] if the search word was empty
    return output;
}

/// @brief Decides if the {input} word ENDS with {search_word}
/// @param input string_t*
/// @param search_word string_t
/// @return [false] -> the {input} is NULL or the {input} does not ends with {search_word};
/// @return [true] -> the {input} ends with {search_word}
boolean_t endsWith(string_t *input, string_t search_word) {
    if (input == STRING_EMPTY)
        return false;

    boolean_t it_was_null = false, output = false;
    if (search_word == STRING_EMPTY) {    // if the search word is NULL then search for empty space
        search_word = (string_t)malloc(sizeof(char) * 2);

        if (search_word == STRING_EMPTY)
            return false;
        
        strcpy(search_word, " \0");
        it_was_null = true;
    }
    
    size_t search_word_lngth = strlen(search_word);
    size_t input_index = strlen(*input) - 1;
    if (search_word_lngth > 1)    // if the search word is a string_t
    {
        int matches = 0;
        for (size_t i = input_index, index = (search_word_lngth - 1); i >= 0; i--)
        {
            if ((*input)[i] == search_word[index]) {
                if (index > search_word_lngth)
                    index--;
                else {
                    output = true;
                    break;
                }
                
                matches++;
            } else {
                if (matches < search_word_lngth)
                    output = false;
                else
                    output = true;

                break;
            }
        }        
    } else                     // else the search word is a character
        if ((*input)[input_index] == search_word[0])            
            output = true;

    if (it_was_null) { _STR_FREE(search_word); }
    return output;
}

/// @brief Trims the character or characters from the given pattern.
/// @brief The character which is meant to be trimmed will only be used as a pattern, when {use_asPattern} is set to -true-.
/// @brief If it is -false- only the first character of {word_pattern} will be trimmed from the {input}
/// @param input string_t*
/// @param word_pattern string_t
/// @param use_asPattern boolean_t
/// @return [STRING_EMPTY] -> the {input} is either NULL, or the allocation for the output has failed;
/// @return [string_t] -> the trim is successful, created a new string which is without the trimmed characters
string_t trim(string_t *input, string_t word_pattern, boolean_t use_asPattern) {
    if (input == STRING_EMPTY)
        return STRING_EMPTY;

    if (word_pattern == STRING_EMPTY) {    // if the search word is NULL then search for empty space
        word_pattern = (string_t)malloc(sizeof(char) * 2);

        if (word_pattern == STRING_EMPTY)
            return STRING_EMPTY;
        
        strcpy(word_pattern, " \0");
    }

    size_t whole_lngth = strlen(*input), pattern_lngth = strlen(word_pattern);
    string_t temp_buffer = malloc(whole_lngth + 1);

    if (temp_buffer == STRING_EMPTY)
        return STRING_EMPTY;
    
    int matches = 0;
    if (use_asPattern) { // if I want to delete more character at a time
        for (size_t i = 0, j = 0; i < whole_lngth; i++)
        {
            boolean_t match_found = false;
            // go through the pattern
            for (j = 0; j < pattern_lngth; j++)
            {
                // if the current character matches with one of the characters from the pattern
                if ((*input)[i] == word_pattern[j]) {
                    match_found = true;
                    break;
                }
            }

            // if the current check is not resulted a match
            if (!match_found) {
                temp_buffer[matches] = (*input)[i];
                matches++;
            }
        }
    } else { // only one character deletion
        for (size_t i = 0, index = 0; i < whole_lngth; i++)
        {
            // if the current check is not resulted a match
            if ((*input)[i] != word_pattern[0]) {
                matches++;
                temp_buffer[index] = (*input)[i];
                index++;
            }
        }
    }

    // if the whole length is bigger, than the matches count 
    if (whole_lngth > matches) {
        temp_buffer = realloc(temp_buffer, matches + 1);
    }
    
    temp_buffer[matches] = '\0';
    return temp_buffer;
}

// ----
// RETURNS STRING_EMPTY: 
// RETURNS [trimmed_word]: 


/// @brief Trims {trim_char} from the start of the {input}.
/// @brief If {keep_input} is set to false the input will be freed
/// @param input string_t*
/// @param trim_char char
/// @param keep_input boolean_t
/// @return [STRING_EMPTY] -> the {input} is NULL;
/// @return [string_t] -> the {input} but without the {trim_char}
string_t trimStart(string_t *input, char trim_char, boolean_t keep_input) {
    if ((*input) == STRING_EMPTY)
        return STRING_EMPTY;

    size_t whole_lngth = strlen((*input)), i = 0, index = 0;
    size_t calculated_lngth = 0;
    
    // increment the indexer while the searched character is represented
    while((*input)[i] == trim_char && i < (whole_lngth - 1))
        i++;

    calculated_lngth = ((whole_lngth - i) + 1); // +1 is for null terminator

    if (calculated_lngth < 2)
        calculated_lngth = 2;   

    // after leaving the trimmed chars behind, we can calculate the size
    string_t temp_buffer = malloc(sizeof(char) * calculated_lngth);

    if (temp_buffer == STRING_EMPTY)
        return STRING_EMPTY;    

    // Start from the location where the searched char is not present
    // and copy all the values into the temp buffer
    for(; i < whole_lngth; i++, index++)
        temp_buffer[index] = (*input)[i];

    temp_buffer[index] = '\0'; //place string terminator
    if (!keep_input) {
        _STR_FREE((*input))
    }
    
    return temp_buffer;
}
 
/// @brief Decides if the {input} contains the character {search}
/// @param input string_t*
/// @param search char
/// @return [false] -> does not contains | the {input} is NULL;
/// @return [true] -> contains
boolean_t containsChar(string_t *input, char search) {
    if (input == STRING_EMPTY)
        return false;
    
    size_t whole_lngth = strlen(*input);
    for (size_t i = 0; i < whole_lngth; i++)
        if ((*input)[i] == search)
            return true;

    return false;
}

/// @brief Decides if the {input} string is a number or not
/// @param input string_t
/// @return [false] -> not a number | the {input} is NULL;
/// @return [true] -> it's a number
boolean_t string_IsANum(string_t input) {
    if(input == STRING_EMPTY)
        return false;

    size_t input_lngth = strlen(input);
    if (input_lngth < 1)
        return false;

    for (size_t i = 0; i < input_lngth; i++)
        if (input[i] > '9' || input[i] < '0')
            return false;

    return true;
}

// ----
// RETURNS false:
// RETURNS true: the conversion is successful\

/// @brief Converts the string {input} to the equivalent |long long| number
/// @param input string_t*
/// @return [-1] -> {input} is NULL;
/// @return [-2] -> the {input} contains a non-numerical character;
/// @return [-3] -> if the trimmed string is NULL;
/// @return [0] -> if the input is 0 | if the length of the trimmed string is 0 
///             | at the conversion one of the character from {input} is non-numerical 
///             | if one of the character in {input} is not found in the |StrNums| array;
/// @return [converted value (LONGLONG_t)] -> the |long long| representation of the {input}
LONGLONG_t tryParse_ll(string_t *input) {
    if ((*input) == STRING_EMPTY)   // if the input is NULL
        return -1;

    if (!string_IsANum((*input)))   // if it's not a number
        return -2;

    double doubl_value = 0, current_power = 0;
    size_t whole_lngth, i = 0;
    LONGLONG_t output = 0;
    int col_index = -1;

    if (strcmp((*input), "0") == 0) // if it is only 0
        return output;

    // in the case when the input is starting with zeroes (trim 0 from the beggining)
    // or the values are all zeroes
    string_t str_trimmed = trimStart(input, "0", true); // trim zeroes from the start of the input

    if (str_trimmed == STRING_EMPTY)
        return -3;

    whole_lngth = strlen(str_trimmed);
    if (whole_lngth < 1) {
        _STR_FREE(str_trimmed)        
        return output;
    }

    for (size_t index = 0; i < whole_lngth; i++) {

        /* If it IS a number */
        if (str_trimmed[i] >= '0' && str_trimmed[i] <= '9')
        {
            // find the index in the nums array
            _STR_FIND_CHAR_INDEX(StrNums, StrNumsLngth, str_trimmed[i], col_index)
            current_power = pow(10, ((whole_lngth - i) - 1));
            if(col_index > -1) {
                if (current_power > 0)  // if the power value is greater than 0, then use the equation
                    doubl_value += col_index * current_power; // the equation which computes the character to number
                else                    // else just add the col_index to the result
                    doubl_value += col_index;

            } else {
                doubl_value = 0;
                break;
            }
        } else {  /* Else the current character in the input is NOT a number */
            doubl_value = 0;
            break;
        }
    }

    if (str_trimmed != STRING_EMPTY) {
        _STR_FREE(str_trimmed)
    }
    
    output = (LONGLONG_t)doubl_value;
    return output;
}

/// @brief Converts the string {input} to the equivalent |double| number
/// @param input string_t*
/// @return [-1] -> {input} is NULL;
///         [-2] -> the input contains none of the partial indicator characters: ' . ' ' , ';
///         [0] -> if the {input} contains only the partial indicator characters
///              | the {input} contains more than 1 partial indicator
///              | at the conversion one of the character from {input} is non-numerical 
///             | if one of the character in {input} is not found in the |StrNums| array;
/// [converted value (double)] -> the |double| representation of the {input} 
double tryParse_double(string_t *input) {
    if (input == STRING_EMPTY)
        return -1;    

    double output = 0, current_power = 0;
    // col_count = how many columns | col_index = the index of the column | num_index = the index inside the helper array 
    int col_count = 0, col_index = -1, num_index = -1;
    boolean_t switch_mode = false;         // the indicator when to calculate the partial part
    size_t whole_lngth = strlen((*input)); // get the input size

    // if the input does not contain ' . ' or ' , '
    if(!containsChar(input, '.') && !containsChar(input, ','))
        return -2;

    // if the ' , ' or ' . ' is at the start or at the end
    boolean_t it_StartsWithCol = (startsWith(input, ".") || startsWith(input, ","));
    boolean_t it_EndsWithCol = (endsWith(input, ".") || endsWith(input, ","));
    if (it_StartsWithCol && it_EndsWithCol) // if it starts and ends with a column
        return 0;
    else if (it_StartsWithCol)           // if it starts with a column, then set switch_mode to true
        switch_mode = true;

    // find the location of the ' . ' or the ' , '
    _STR_FIND_CHAR_INDEX((*input), whole_lngth, '.', col_index)
    if (col_index < 0)
        _STR_FIND_CHAR_INDEX((*input), whole_lngth, ',', col_index)

    for (size_t partial_offset = 1, i = 0, power_num; i < whole_lngth; i++) {
        if (col_count >= 2)   // if the input contains multiple columns
            return 0;
        
        // if it's a number (ascii table representation 48 - 57)
        if ((*input)[i] >= '0' && (*input)[i] <= '9')
        {
            //find the index in the nums array
            _STR_FIND_CHAR_INDEX(StrNums, StrNumsLngth, (*input)[i], num_index)
            if(col_index > -1) {
                if (!switch_mode) {     // if we are NOT after the ' , ' or ' . '
                    power_num = (col_index - 1) - i; // (((whole_lngth - i) - (whole_lngth - col_index)) - 1)
                    current_power = pow(10, (int)power_num);
                    output += num_index * current_power; // the equation which computes the character to whole number
                }
                else if(switch_mode) {  // else if we are after the ' , ' or ' . '
                    current_power = pow(10, partial_offset);  // calculate the current power index
                    partial_offset++;                         // increment the offset
                    output += num_index / current_power; // the equation which computes the character to partial number
                }
            } 
            else 
                return 0;
        // else if it's ' . ' or ' , ' ,then: count it, set switch_mode to true
        } else if ((*input)[i] == '.' || (*input)[i] == ',') {
            if (it_EndsWithCol) // if it ends with a column
                break;
            
            col_count++;        // count the column
            if (!switch_mode)   // if switch_mode is false, then set to true
                switch_mode = true;
        } else
            return 0;
    }

    return output;
}


/* Handle String objects */

/// @brief Creates a String object with the specified type {type_}, which stores the {input} string.
///        If the {input} is NULL the String will be empty (created, buffer contains no characters).
/// @param input string_t, a string type (char*)
/// @param type_ StringType, the type of the String object (e.g. STRING_4, ...)
/// @return [STRING_EMPTY] -> the allocation for the String struct failed;
///         [String]       -> created the String object
String StringCreate(string_t input, StringType type_) {
    size_t buffer_size = type_;

    String string_Obj = malloc(sizeof(STRING) + (buffer_size - 1));
    if (string_Obj == STRING_EMPTY)
        return STRING_EMPTY;

    _STR_CLEAR_ARRAY(string_Obj->buffer, buffer_size)
    if (input == STRING_EMPTY) {
        string_Obj->length = 0;
        string_Obj->empty = true;
    } else {
        string_Obj->length = strlen(strncpy(string_Obj->buffer, input, buffer_size - 1));
        string_Obj->buffer[string_Obj->length + 1] = '\0';
        string_Obj->empty = false;
    }

    string_Obj->type_ = type_;

    return string_Obj;
}

/// @brief Redefine the {string_Obj} to the specified type {type_}.
///        The new object will store the {input}. If the {input} is empty the String object will be empty.
/// @param string_Obj String*, the String to change
/// @param type_ StringType, the type of the String object (e.g. STRING_4, ...)
/// @param input string_t, a string type (char*)
/// @return [-1] -> {string_Obj} is NULL;
///         [-2] -> new String object allocation failed;
///         [0] -> the changes were applied
STATUS_t StringChange(String *string_Obj, StringType type_, string_t input) {
    if ((*string_Obj) == STRING_EMPTY)
        return -1;
    
    size_t current_size = (*string_Obj)->length;
    if ((*string_Obj)->type_ == type_)
    {
        _STR_CLEAR_ARRAY((*string_Obj)->buffer, current_size)
        if (input == STRING_EMPTY)
        {
            (*string_Obj)->length = 0;
            (*string_Obj)->empty = true;
        } else {
            (*string_Obj)->length = strlen(strncpy((*string_Obj)->buffer, input, ((*string_Obj)->type_) - 1));
            (*string_Obj)->buffer[((*string_Obj)->type_) - 1] = '\0';
            (*string_Obj)->empty = false;
        }
    } else { 
        String new_string = StringCreate(input, type_);
        StringDelete(string_Obj);
        
        if (new_string == STRING_EMPTY)
            return -2;

        *string_Obj = new_string;
    }
    
    return 0;
}

/// @brief Creates an array of a specific String type {type_} object, with the specified length {num_of_elements}
/// @param num_of_elements size_t, the number of String objects which will be created inside the array
/// @param type_ StringType, the type of the String objects inside the array (e.g. STRING_4, ...)
/// @return [STRING_EMPTY] -> the allocation for the StringArray failed;
///         [StringArray] -> the allocation and the setup went successful
StringArray StringCreateArray(size_t num_of_elements, StringType type_) {
    StringArray array_obj = (StringArray)malloc(sizeof(STRING_ARRAY));

    if (array_obj == STRING_EMPTY || num_of_elements < 1)
        return STRING_EMPTY;

    size_t buffer_size = type_;

    array_obj->size = num_of_elements;
    array_obj->type_ = type_;
    array_obj->string_obj = (String*)malloc((sizeof(String) + (buffer_size - 1)) * num_of_elements);
    
    if (array_obj->string_obj == STRING_EMPTY) {
        _STR_FREE(array_obj);
        return STRING_EMPTY;
    }

    for (size_t i = 0; i < array_obj->size; i++)
        array_obj->string_obj[i] = StringCreate(STRING_EMPTY, type_);
    
    return array_obj;
}

/// @brief Deletes the String array {string_arrObj}
/// @param string_arrObj StringArray*, the pointer to the array, which will be deleted
/// @return [-1] -> the {string_arrObj} is NULL;
///         [0] -> {string_arrObj} is deleted
STATUS_t StringDeleteArray(StringArray *string_arrObj) {
    if ((*string_arrObj) == STRING_EMPTY)
        return -1;
    
    for (size_t i = 0; i < (*string_arrObj)->size; i++)
        if ((*string_arrObj)->string_obj[i] != STRING_EMPTY)
            StringDelete(&((*string_arrObj)->string_obj[i]));

    _STR_FREE((*string_arrObj)->string_obj)

    (*string_arrObj)->size = 0;
    _STR_FREE((*string_arrObj))
    return 0; 
}

/// @brief Copies StringArray {src_} elements to the destination array {dst_}.
///        If the {keep_src} is set to false the {src_} will be deleted.
///        Only the right amount of elements will be copied if the {dst_} is smaller than the {src_}.
/// @param dst_ StringArray*, the destination array where the strings will be copied
/// @param src_ StringArray*, the source array
/// @param keep_src boolean_t
/// @return [-1] -> {dst_} or {src_} is NULL
///         [-2] -> if {dst_} has no free spots
///         [0] -> the elements were copied
STATUS_t StringCopyArray(StringArray *dst_, StringArray *src_, boolean_t keep_src) {
    if ((*dst_) == STRING_EMPTY || (*src_) == STRING_EMPTY)
        return -1;

    size_t insert_index = 0;
    // find the first free spot in the destination array
    for (size_t i = 0; i < (*dst_)->size; i++) {
        if ((*dst_)->string_obj[insert_index] != STRING_EMPTY)
            if (!((*dst_)->string_obj[insert_index]->empty))
                insert_index++;
    }
    
    // if the destination array has no free spot
    if (insert_index > ((*dst_)->size) - 1)
        return -2;

    size_t i = 0;
    while ((i < (*src_)->size) && ((*dst_)->size - insert_index) > 0)
    {
        // if the current element in the destination is not empty
        if ((*dst_)->string_obj[insert_index] != STRING_EMPTY) {
            if (!((*dst_)->string_obj[insert_index]->empty)) {
                insert_index++;
                continue;
            }
        }
        
        // if the current element in the source is not empty
        if ((*src_)->string_obj[i] != STRING_EMPTY) {
            if (!((*src_)->string_obj[i]->empty)) {
                // copy the source to the destination
                StringInsertIntoArray(dst_, &((*src_)->string_obj[i]), insert_index);
                insert_index++;
            }
        }
        
        i++;
    }

    if (!keep_src)
        StringDeleteArray(src_);

    return 0;   
}

/// @brief Inserts the specified String object {string_Obj} into the specified StringArray {string_arrObj}.
///        If the element at the current {index} is NULL, the function will create a new String object at that position.
///        (WARNING!!! If the String type does not match, the String will lose some characters if it is too big)
/// @param string_arrObj StringArray*, the array where the String should be inserted
/// @param string_Obj String*, the String object which will be inserted
/// @param index INDEX_t, the index in the array where the element will be inserted
/// @return [-1] -> {string_arrObj} or {string_Obj} is NULL;
///         [-2] -> {index} > size of {string_arrObj} | {index} < 0;
///         [-3] -> the new String object allocation failed;
///         [0] -> insertion successful
STATUS_t StringInsertIntoArray(StringArray *string_arrObj, String *string_Obj, INDEX_t index) {
    if ((*string_arrObj) == STRING_EMPTY || (*string_Obj) == STRING_EMPTY)
        return -1;

    if (index > ((*string_arrObj)->size) - 1 || index < 0)
        return -2;
    
    StringType current_type = (*string_arrObj)->type_;
    String current_arrStrObj = (*string_arrObj)->string_obj[index];

    // insert into the String object to the specified position
    if (current_arrStrObj == STRING_EMPTY) {  // if the current slot in the array is NULL
        (*string_arrObj)->string_obj[index] = StringCreate((*string_Obj)->buffer, current_type);
        if (current_arrStrObj == STRING_EMPTY)  // check if the allocation failed or not
            return -3;
    } else                                    // else the current slot in the array is not NULL
        StringChange(&current_arrStrObj, current_type, (*string_Obj)->buffer);

    return 0;
}

/// @brief Resets (makes it empty) the String object in the {string_arrObj} at the specified index {index}
/// @param string_arrObj StringArray*, the array where the element will be removed
/// @param index INDEX_t, the index in the array {string_arrObj}
/// @return [-1] -> {string_arrObj} is NULL;
///         [-2] -> {index} > array size | {index} < 0;
///         [0] -> no errors
STATUS_t StringRemoveAt(StringArray *string_arrObj, INDEX_t index) {
    if ((*string_arrObj) == STRING_EMPTY)
        return -1;
    
    if ((index > ((*string_arrObj)->size - 1)) || index < 0)
        return -2;
    
    StringChange(&((*string_arrObj)->string_obj[index]), (*string_arrObj)->type_, STRING_EMPTY);
    return 0; 
}

/// @brief Resets (makes them empty) all the String objects in {string_arrObj}
/// @param string_arrObj StringArray*, the array where the elements will be reset
/// @return [-1] -> {string_arrObj} is NULL;
///         [0] -> no errors
STATUS_t StringClearArray(StringArray *string_arrObj) {
    if ((*string_arrObj) == STRING_EMPTY)
        return -1;   

    StringType current_type = (*string_arrObj)->type_;
    String current_obj = STRING_EMPTY;
    for (size_t i = 0; i < (*string_arrObj)->size; i++) {
        current_obj = (*string_arrObj)->string_obj[i];
        StringChange(&current_obj, current_type, STRING_EMPTY);
    }
    
    return 0;
}

/// @brief Shrinks an array {string_arrObj} (eliminates all NULL or empty String objects).
/// @brief If {keep_old} is set to false {string_arrObj} will be deleted
/// @param string_arrObj StringArray*
/// @param keep_old boolean_t
/// @return STRING_EMPTY -> {string_arrObj} is NULL | new array allocation failed
/// @return {new StrinArray} -> if array shrink went successful
StringArray StringShrinkArray(StringArray *string_arrObj, boolean_t keep_old) {
    if ((*string_arrObj) == STRING_EMPTY)
        return STRING_EMPTY;

    int non_empty_count = 0;
    size_t input_size = (*string_arrObj)->size;
    String current_word = STRING_EMPTY;

    // go through the array to find out the new size (count the non-empty literals)
    for (size_t i = 0; i < input_size; i++) {
        current_word = (*string_arrObj)->string_obj[i];
        if (current_word == STRING_EMPTY) // if the current String object is NULL
            continue;
        
        if (!(current_word->empty)) // if the current String object is not empty
            non_empty_count++;
    }
    
    // create a new array with the size of non empty count
    StringArray new_arr = StringCreateArray(non_empty_count, (*string_arrObj)->type_);
    if (new_arr == STRING_EMPTY)
        return STRING_EMPTY;

    // copy the array elements without the empty literals to the new array
    StringCopyArray(&new_arr, string_arrObj, keep_old);

    return new_arr;
}

/// @brief Deletes the String object {string_Obj}
/// @param string_Obj String* 
/// @return -1 -> {string_Obj} is NULL
/// @return ; 0 -> {string_Obj} is deleted
STATUS_t StringDelete(String *string_Obj) {
    if ((*string_Obj) == STRING_EMPTY)
        return -1;

    _STR_FREE((*string_Obj));
    return 0;
}
