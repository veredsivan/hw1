//#include "string.h"
#include "ip.h"
#define SLASH_SYMBOL "/"
#define DOT_SYMBOL "."
#define EQUALL_SYMBOL "="
#define FALSE 1
#define TRUE 0
#define IP_SLOTS 4
#define TARGET_PART 0
#define IP_PART 1
#define NUM_EQ_PARTS 2
#define SRCIP "src-ip"
#define DSTIP "dst-ip"
#define BYTE 8
#define NUM_PACKET_FIELDS 8
#define EIGHT_BIT_SHIFT 8


//parse command string
bool sep_command_field(String command, String **output, size_t *size)
{
    String *pre_trim;
    char *delimiter = "=";
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

/**
class GenericField {
public:
	String value;
    virtual bool match(String packet) = 0;
    virtual bool set_value(String value) = 0;
    virtual ~GenericField() {}
};
**/

//parse packet string
bool sep_packet_field(String packet, String** output, size_t *size)
{
    char* delimiters = "=,";
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

//transfer each slot of ip to int number
bool ip_to_int(String IP, int *IP_int)
{
    size_t size;
    String *ip_arr;
    char *delimiter = DOT_SYMBOL;
    String ip_con;
    IP.split(delimiter, &ip_arr, &size);
    if (size != IP_SLOTS)
    {
    	delete[] ip_arr;
        return FALSE;
    }
    for(size_t i=0; i < size - 1; i++) //w/o LSB
        *IP_int += (ip_arr[i].to_integer())<<EIGHT_BIT_SHIFT;
    *IP_int += ip_arr[size-1].to_integer(); //LSB doesnt need shift
    delete[] ip_arr;
    return TRUE;
}




/**
class IPField : public GenericField {
	public:
	int mask;
	int IP_value; //stores the ip in int
	String value;
	String target; //options are "dst-ip" or "src-ip"
    //constructors:
	IPField();
	IPField(String command)
	{
		String **command_fields;
		size_t fields_size;
		String target;
		sep_command_field(command, command_fields, &fields_size);
		//set value and target of element
		this->target = *command_fields[TARGET_PART];
		this->value = *command_fields[IP_PART];
	}
    //methods:
    bool set_value(String value);
    bool match(String packet);
};
**/

IPField::IPField(String command) 
	{
		String *command_fields;
		size_t fields_size;
		String target;
		sep_command_field(command, &command_fields, &fields_size);
		if (fields_size != NUM_EQ_PARTS)
		{
			delete[] command_fields;
			return;
		}
		//set value and target of element
		this->target = command_fields[TARGET_PART];
		this->value = command_fields[IP_PART];
		delete[] command_fields;
	}
/**
//sestructor implemntation
IPFIELD::~IPFIELD()
{

}
**/
bool IPField::set_value(String value)
	{
		String *sep_by_slash;
		String *sep_by_dot;
		size_t *size_slash;
		size_t *size_dot;
		value.split(SLASH_SYMBOL, &sep_by_slash, size_slash);
		sep_by_slash[0].split(DOT_SYMBOL, &sep_by_dot,size_dot);
		if(*size_dot!=NUM_EQ_PARTS)
		{
			delete[] sep_by_slash;
			delete[] sep_by_dot;
			return FALSE;
		}
		int ip_num;
		for (size_t i=0; i < *size_dot; i++)
		{
			ip_num = sep_by_dot[i].to_integer();
			if ((ip_num < 0) || (ip_num > 255))
			{
				delete[] sep_by_slash;
				delete[] sep_by_dot;
				return FALSE;
			}
		}
		if (!(ip_to_int(sep_by_slash[0], &(this->IP_value))))
		{
			delete[] sep_by_slash;
			delete[] sep_by_dot;
			return FALSE;
		}
		mask = sep_by_slash[1].to_integer();
		if ((mask < 0) || (mask > 32))
		{
			delete[] sep_by_slash;
			delete[] sep_by_dot;
			return FALSE;
		}
		this->mask = mask;
		delete[] sep_by_slash;
		delete[] sep_by_dot;
		return TRUE;
	}

bool IPField::match(String packet)
	{
	String* packet_fields;
	size_t num_fields;
	int packet_ip;
	int masked_packet_ip;
	//send the IP part to set value
	if (!(this->set_value(this->value)))
	{
		delete[] packet_fields;
		return FALSE;
	}

	//divide packet into arr of phrases
	sep_packet_field(packet, &packet_fields, &num_fields);
	for (size_t i=0; i < num_fields; i++)
		if((packet_fields[i].equals(this->target)))
		{
			ip_to_int(packet_fields[i+1],	&packet_ip);
			masked_packet_ip = packet_ip<<mask;
			if (masked_packet_ip == this->IP_value)
			{
				delete[] packet_fields;
				return TRUE;
			}
			delete[] packet_fields;
			return FALSE;
		}
	delete[] packet_fields;	
	return FALSE;

	}



