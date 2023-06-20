#include <cstring>
#include "string.h"
static const char SLASH0 = '\0';

/**
    * @brief Initiates an empty string
    */

String::String()
{
    data = new char[1];
    data[0] = '\0';
    length=0;
}


/**
 * @brief Initiates string from other string
 */

String::String(const String& str)
{
	length=str.length;
	data=new char[length+ 1];
    strcpy(data, str.data);
}
/**
 * @brief Initiates a string from char array
 */

String::String(const char* str)
{
	length= strlen(str);
	data= new char[length + 1];
    strcpy(data, str);
}

String::~String()
{
    delete[] data;
}

/**
 * @brief Changes this from String
 */
String& String::operator=(const String& rhs)
{
    if (this != &rhs)
    {
        delete[] data;
        length = rhs.length;
        data = new char[length + 1];
        strcpy(data, rhs.data);
    }

    return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char* str)
{
    if (data != str)
    {
        delete[] data;
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String& rhs) const
{
    if (strcmp(data, rhs.data) == 0) {
        return true;
    }
    return false;
}

/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char* rhs) const
{
    if (strcmp(data, rhs) == 0) {
        return true;
    }
    return false;
}

/*the function finds the first appearence of any delimiter in the string
* while searching from placeToStart */
int find_pos(const char* delimiters, int placeToStart, size_t length, const char* data) 
{
    size_t numD = strlen(delimiters);
    for (size_t i = placeToStart; i < length; i++) 
    {
        for (size_t j = 0; j < numD; j++) {
            if (data[i] == delimiters[j]) {
                return (int)i;
            }
        }
    }
    return -1;
}

//the function makes a new substring of data, from the pointer start until end
char* make_sub(int start, int end, const char* data) 
{
    char* sub = new char[end - start + 1];
    int i;
    for (i = 0; i < end-start; i++) 
    {
        sub[i] = data[i+start];
    }
    sub[i] = '\0';
    return sub;
}

/**
 * @brief Splits the string into several sub-strings according to delimiters.
 * Allocates memory for "output" that the user must delete (using delete[]).
 * @note Does not affect the original string.
 * @note If "output" is set to nullptr, only compute "size" without allocating memory.
 */
void String::split(const char* delimiters, String** output, size_t* size) const 
{
    size_t count = 0;
    int firstPos = 0;
    int lastPos = find_pos(delimiters, firstPos, length, data);

    while (lastPos != -1) 
    {
        count++;
        firstPos = lastPos + 1;
        lastPos = find_pos(delimiters, firstPos, length, data);
    }
    count++;
    *size =count;

    if (output == nullptr) 
    {
        return;
    }

    *output = new String[count];
    int i = 0;
    firstPos = 0;
    lastPos = find_pos(delimiters, firstPos, length, data);

    while (lastPos != -1) 
    {
        char* curSub = make_sub(firstPos, lastPos, data);
        (*output)[i] = curSub;
        delete[] curSub;
        firstPos = lastPos + 1;
        lastPos = find_pos(delimiters, firstPos, length, data);
        i++;
    }

    char* curSub = make_sub(firstPos, length, data);
    (*output)[i] = curSub;
    delete[] curSub;
}

int String::to_integer() const
{
    return atoi(data);
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const
{
	if(length==0)
	{
		return String("");
	}
    size_t startIndex = 0, endIndex = length-1;

    while (data[startIndex] == ' ' && startIndex < length)
    {
        startIndex++;
    }
    while (data[endIndex] == ' ' && endIndex > startIndex)
    {
        endIndex--;
    }
    if(startIndex== length-1 || endIndex == 0)
    {
    	return String("");
    }
    char* newData = new char[endIndex - startIndex + 2];

    for (size_t i = 0; i <= endIndex - startIndex; i++)
    {
        newData[i] = data[i + startIndex];
    }
   
    newData[endIndex - startIndex +1 ] = '\0';
    String str(newData);
    delete[] newData;
    return str;   
}
