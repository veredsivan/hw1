//#ifndef STRING_H
//#define STRING_H

//#include <stddef.h>
//#include <iostream>
#include <cstring>
#include "string.h"

#define EMPTY_STRING_LEN 1
#define END_OF_STRING '\0'
#define SPACE ' '


//constructors:
    String::String() {
        length = EMPTY_STRING_LEN;
        data = new char[this->length];
        data[0] = END_OF_STRING;
    };


    /**
     * @brief Initiates string from other string
     */
    String::String(const String &str) {
        this->length = str.length;
        this->data = new char[(this->length) + 1];
        std::strcpy(this->data, str.data);
    };


    /**
     * @brief Initiates a string from char array
     */
    String::String(const char *str) {
        this->length = std::strlen(str);
        this->data = new char[(this->length) + 1];
        std::strcpy(this->data, str);
    };

    String::~String() {
        delete[] this->data;
    };


    /**
     * @brief Changes this from String
     */
    String& String::operator=(const String &rhs){
        delete[] this->data;
        //may be replaced by constructor
        this->length = rhs.length;
        this->data = new char[(this->length) + 1];
        std::strcpy(this->data, rhs.data);
        return *this;
    };


    /**
     * @brief Changes this from char array
     */
    String& String::operator=(const char *str){
        delete[] this->data;
        //may be replaced by constructor
        this->length = std::strlen(str);
        this->data = new char[(this->length) + 1];
        std::strcpy(this->data, str);
        return *this;
    };


    /**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
    bool String::equals(const String &rhs) const{
        return !(std::strcmp(this->data, rhs.data));
    };


    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
        return !(std::strcmp(this->data, rhs));
    };




void String::split(const char* delimiters, String** output, size_t* size) const {
    if (delimiters == NULL || this->data == NULL) {
        return;
    }

    int substrings_num = 1;//Number of substrings
    int num_delimiters;//Number of delimiters
    int len = length;
    char clone[len + 1];
    strcpy(clone, data);
    num_delimiters = strlen(delimiters);

    for (int i = 0; i < len; i++) {//Count the number of substrings
        for (int j = 0; j < num_delimiters; j++) {//Count the number of delimiters
            if (clone[i] == delimiters[j]) {
                clone[i] = END_OF_STRING;//Replace the delimiter with '\0'
                if ((i > 0) && (clone[i - 1] != END_OF_STRING) && (i < (len - 1))) {
                    substrings_num++;
                }
            }
        }
    }
    //return the size even if output is NULL
    *size = substrings_num;
    if (output == NULL) {
        return;
    }
    *output = new String[substrings_num];//Allocate memory for output
    int start = 0;
    int i_substring = 0;
    for (int i = 1; i < len + 1; i++) {
        //If the current char is '\0' and the previous char is not '\0'
        if (clone[i] == END_OF_STRING && clone[i - 1] != END_OF_STRING) {
            //Copy the substring to the output
            (*output)[i_substring] = String(&clone[start]);
            i_substring++;
            start = i + 1;
        }
    }
    return;
}



    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    /**
    void String::split(const char *delimiters, String **output, size_t *size) const{
        char* token = std::strtok(this->data,delimiters);
        //int i = 0;
        int j = 0;
        int count = 1;
        //create array of Strings
        while (this->data[j] != END_OF_STRING)
        {
            int k = 0;
            while (k < std::strlen(delimiters))
            {
                if(this->data[j] == delimiters[k])
                {
                    count++;
                    break;
                }
                k++;
            }
            j++;
        }
        /**
        *size = (size_t)count; //enter size the length of arr
        *output = new String[count];
        while (token != NULL) {
            *output[i] = String(token);
            token = std::strtok(this->data,delimiters);
            i++;
        }
        **/

/**
        //return the size even if output is NULL
    int start = 0;
    int sub_count = 0;
    char clone[length + 1];
    *size =count;
    *output = new String[count];//Allocate memory for output
    for (int i = 1; i < length + 1; i++) {
        //If the current char is '\0' and the previous char is not '\0'
        if (clone[i] == END_OF_STRING && clone[i - 1] != END_OF_STRING) {
            //Copy the substring to the output
            (*output)[sub_count] = String(&clone[start]);
            sub_count++;
            start = i + 1;
        }
    }

    return;
    };
**/
    /**
     * @brief Try to convert this to an integer. We can assume that the input
     * is valid.
     */
   



    int String::to_integer() const{
        return std::atoi(this->data);
    };

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const
    {
        /**
        //remove leading spaces
        int i= 0;
        int j= this->length - 1;
        while(this->data[i] == SPACE)
            i++;

        while(this->data[j] == SPACE)
            j--;

        //str is the non-spaces string
        char* str = new char[this->length];
        str = &this->data[i];
        str[j] = END_OF_STRING;
        String copy_str = String(str);
        delete[] str;
        return copy_str;
        **/

    int start = 0;
    int end = length - 1;

    while (data[start] == SPACE) {
        start++;
    }

    while (data[end] == SPACE) {
        if (end == start) {
            return String(); // spaces string
        }
        end--;
    }
    end++;
    
    char trim_string[end-start+1];//Allocate memory for the trimmed string
    strncpy(trim_string,&data[start],end-start);//Copy the trimmed string
    trim_string[end-start]=END_OF_STRING;
    //trim_string = allocate_and_copy(&data[start],end-start);
    String new_trim_string = String(trim_string);
    return new_trim_string;

    };






//#endif
