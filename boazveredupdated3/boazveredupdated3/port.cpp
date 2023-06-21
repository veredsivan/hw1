//
// Created by boaz3 on 6/14/2023.
//
//#include "string.h"
#include "port.h"

#define HYPHEN_SYMBOL "-"
#define FALSE 0
#define TRUE 1
#define IP_SLOTS 4
#define TARGET_PART 0
#define PORT_PART 1
#define NUM_EQ_PARTS 2
#define NUM_PACKET_FIELDS 8
#define EIGHT_BIT_SHIFT 8
#define PORT_FIELDS 2
#define MIN_PORT_LIMITER 0
#define MAX_PORT_LIMITER 1

using namespace std;
/**
//parse command string
bool sep_command_field_port(String command, String **output, size_t *size)
{
    String *pre_trim;
    char delimiter[] = "=";
    command.split(delimiter, &pre_trim, size);
    if (*size != NUM_EQ_PARTS)
    {
        delete[] pre_trim;
        return FALSE;
    }
    for (size_t i=0; i < *size; i++)
    {
        *output[i] = pre_trim[i].trim();
    }
    delete[] pre_trim;
    return TRUE;

}
**/
/**
class GenericField {
public:
    String value;
    virtual bool match(String packet) = 0;
    virtual bool set_value(String value) = 0;
    virtual ~GenericField() {}
};
**/
/**
//parse packet string
bool sep_packet_field_port(String packet, String** output, size_t *size)
{
    char delimiters[] = "=,";
    String *pre_trim;
    packet.split(delimiters, &pre_trim, size);
    if (*size != NUM_PACKET_FIELDS) //check for valid packet struct
        {
        delete[] pre_trim;
        return FALSE;
        }

    for (size_t i=0; i < *size; i++) //remove spaces from each field
    {
        *output[i] = pre_trim[i].trim();
    }
    delete[] pre_trim;
    return TRUE;
}
**/
/**
class PortField : public GenericField {
public:
    size_t min_port; //min of range
    size_t max_port; //max of range
    String value;
    String target; //options are "dst-port" or "src-port"
    //constructors:
    PortField();
    PortField(String command)
    {
        String **command_fields;
        size_t fields_size;
        String target;
        sep_command_field_port(command, command_fields, &fields_size);
        //set value and target of element
        this->target = *command_fields[TARGET_PART];
        this->value = *command_fields[PORT_PART];
    }
    //methods:
    bool set_value(String value);
    bool match(String packet);
};
**/

//constructor:
PortField::PortField() : min_port(), max_port() {}


PortField::PortField(String command)
{
    String *command_fields = new String[NUM_PACKET_FIELDS];
    size_t size;
    String target;
    String *pre_trim;
    const char delimiter[] = "=";
    command.split(delimiter, &pre_trim, &size);
    if (size != NUM_EQ_PARTS)
    {
        delete[] pre_trim;
        delete[] command_fields;
    }
    for (size_t i=0; i < size; i++)
    {
        command_fields[i] = pre_trim[i].trim();
    }


    //set value and target of element
    this->target = command_fields[TARGET_PART];
    this->value = command_fields[PORT_PART];
    delete[] command_fields;
    delete[] pre_trim;
}


bool PortField::set_value(String value)
{
    String *sep_by_hyphen;
    size_t size_hyphen;
    int port_limiter;
    value.split("-", &sep_by_hyphen, &size_hyphen);
    if(size_hyphen != PORT_FIELDS)
    {
        delete[] sep_by_hyphen;
        return FALSE;
    }
    for (size_t i=0; i < size_hyphen; i++)
    {
        port_limiter = sep_by_hyphen[i].to_integer();
        if ((port_limiter < 0) || (port_limiter > 65535))
        {
            delete[] sep_by_hyphen;
            return FALSE;
        }
    }
    this->min_port = (size_t)sep_by_hyphen[MIN_PORT_LIMITER].to_integer();
    this->max_port = (size_t)sep_by_hyphen[MAX_PORT_LIMITER].to_integer();
    delete[] sep_by_hyphen;
    return TRUE;
}

bool PortField::match(String packet)
{

    String* packet_fields = new String[NUM_PACKET_FIELDS];
    size_t packet_port;
    char delimiters[] = "=,";
    String *pre_trim;
    size_t size;

    //send value to set value
    if (!(this->set_value(this->value)))
    {
        delete[] packet_fields;
        return FALSE;
    }
    //divide packet into arr of phrases

    packet.split(delimiters, &pre_trim, &size);
    if (size != NUM_PACKET_FIELDS) //check for valid packet struct
        {
        delete[] pre_trim;
        delete[] packet_fields;
        return FALSE;
        }

    for (size_t i=0; i < size; i++) //remove spaces from each field
    {
        packet_fields[i] = pre_trim[i].trim();
    }
    for (size_t i=0; i < size; i++)
    {

        if((packet_fields[i].equals(this->target)))
        {
            packet_port = packet_fields[i+1].to_integer();
            

         //   packet_fields[i+1].print_string();
         //   cout << "port in int is:" << packet_port << endl;

            if ( (packet_port <= this->max_port)
                && (packet_port >= this->min_port))
            
            {
        //  cout << "port passed and is:" << packet_port << endl;
        //  cout << "min:" << min_port << endl;
       //     cout << "max:" << max_port << endl;   
                delete[] packet_fields;
                delete[] pre_trim;
                return TRUE;
            }
       //     cout << "failed" <<endl;
            delete[] pre_trim;
            delete[] packet_fields;
            return FALSE;
        }
    }
    delete[] pre_trim;
    delete[] packet_fields; 
    return FALSE;

}



 