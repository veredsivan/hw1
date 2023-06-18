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
        this->length = std::strlen(rhs.data);
        this->data = new char[(this->length) + 1];
        std::strcpy(this->data, rhs.data);
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
    };


    /**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
    bool String::equals(const String &rhs) const{
        return std::strcmp(this->data, rhs.data);
    };


    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
        return std::strcmp(this->data, rhs);
    };


    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    void String::split(const char *delimiters, String **output, size_t *size) const{
        char* token = std::strtok(this->data,delimiters);
        int i = 0;
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
        *size = (size_t)count; //enter size the length of arr
        *output = new String[count];
        while (token != NULL) {
            *output[i] = String(token);
            token = std::strtok(this->data,delimiters);
            i++;
        }
    };

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

        return String(str);
    };



//#endif
