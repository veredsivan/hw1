//#include "string.h"
#include "ip.h"
#define SLASH_SYMBOL '/'
#define DOT_SYMBOL '.'
#define EQUALL_SYMBOL '='
#define FALSE 0
#define TRUE 1
#define IP_SLOTS 4
#define TARGET_PART 0
#define IP_PART 1
#define NUM_EQ_PARTS 2
#define SRCIP "src-ip"
#define DSTIP "dst-ip"
#define BYTE 8
#define NUM_PACKET_FIELDS 8
#define EIGHT_BIT_SHIFT 8
#define MAX_MULTIPLIER 24
#define DIFF_MULT 8
#define FOUR_BYTES 32

using namespace std;

/**
//parse command string
static bool sep_command_field(String command, String **output, size_t *size)
{
    String *pre_trim;
    const char *delimiter = "=";
    command.split(delimiter, &pre_trim, size);
    command.split(delimiter, output, size);
    if (*size != NUM_EQ_PARTS)
    {
        delete[] pre_trim;
        return FALSE;
    }
    *output = new String[NUM_EQ_PARTS];
    for (size_t i = 0; i < *size; i++)
    {
    	cout << "i = " << i << endl;
    	String tmp = pre_trim[i].trim();
        *output[i] = tmp;
        output[i].trim();
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
bool sep_packet_field(String packet, String** output, size_t *size)
{
    const char* delimiters = "=,";
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
//transfer each slot of ip to int number
bool ip_to_int(String IP, size_t *IP_int)
{
	*IP_int = 0;
	int mult = MAX_MULTIPLIER;
    size_t size;
    String *ip_arr;
    char delimiter[] = ".";
    String ip_con;
    IP.split(delimiter, &ip_arr, &size);
    if (size != IP_SLOTS)
    {
    	delete[] ip_arr;
        return FALSE;
    }
    for(size_t i=0; i < IP_SLOTS; i++) {
    	size_t slot_ip_int = (size_t) ip_arr[i].trim().to_integer();
       *IP_int += (slot_ip_int << mult);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`    	
 //	cout << "sade in int ->" << *IP_int << endl;
 	//cout << "not to be added ->" << slot_ip_int << endl;
	//cout << "sade in string ->";
	//ip_arr[i].print_string();   	
	//cout<< endl;

    mult -= DIFF_MULT;
	//	*IP_int = (unsigned int)*IP_int << BYTE;
	//	*IP_int = *IP_int || ip_arr[i].to_integer();
    }

    //*IP_int += ip_arr[size-1].to_integer(); //LSB doesnt need shift
    
//    cout << "weird print ->";
//    ip_arr[0].print_string();
   // cout << "ip in int is " << *IP_int << endl;
    

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
	size_t IP_value = 0;
	size_t size;
	String target;
	String *command_fields = new String[NUM_EQ_PARTS];
	String *pre_trim ;
    const char *delimiter = "=";
    command.split(delimiter, &pre_trim, &size);
    if (size != NUM_EQ_PARTS)
    {
        delete[] pre_trim;
        delete[] command_fields;
    }
    //*output = new String[NUM_EQ_PARTS];
    for (size_t i = 0; i < size; i++)
    {
    	//cout << "i = " << i << endl;
    	command_fields[i] = pre_trim[i].trim();
         
        //*output[i].trim();
    }
    

	//set value and target of element
	this->target = command_fields[TARGET_PART];
	this->value = command_fields[IP_PART];
	//this->target(command_fields[TARGET_PART]);
	//this->value(command_fields[IP_PART]);
	delete[] command_fields;
	delete[] pre_trim; 
	}
/**
//sestructor implemntation
IPFIELD::~IPFIELD()
{

}
**/
bool IPField::set_value(String value)
	{
		//cout << "hi";
		String *sep_by_slash;
		String *sep_by_dot;
		size_t size_slash;
		size_t size_dot;
		value.split("/", &sep_by_slash, &size_slash);
		sep_by_slash[0].split(".", &sep_by_dot,&size_dot);
		//cout << "sizedot is: " << size_dot << endl;
		if(size_dot!=IP_SLOTS)
		{
					cout << "hi1";

			delete[] sep_by_slash;
			delete[] sep_by_dot;
			return FALSE;
		}
		int ip_num;
		for (size_t i=0; i < size_dot; i++)
		{
			ip_num = sep_by_dot[i].to_integer();
			if ((ip_num < 0) || (ip_num > 255))
			{
						cout << "hi2";

				delete[] sep_by_slash;
				delete[] sep_by_dot;
				return FALSE;
			}
		}
	//	cout << "now a print in set value! ->";
	//	sep_by_slash[0].print_string();
		if (!(ip_to_int(sep_by_slash[0], &(this->IP_value))))
		{
					cout << "hi3";

			delete[] sep_by_slash;
			delete[] sep_by_dot;
			return FALSE;
		}
		mask = sep_by_slash[1].to_integer();
		if ((mask < 0) || (mask > 32))
		{
					cout << "hi4";

			delete[] sep_by_slash;
			delete[] sep_by_dot;
			return FALSE;
		}
		this->mask = mask;
	//	cout << "mask is:" << mask << endl;
		delete[] sep_by_slash;
		delete[] sep_by_dot;
		return TRUE;
	}

bool IPField::match(String packet)
	{
	//	cout << "pakcet is : "  << endl;
//		packet.print_string();
	String *packet_fields = new String[NUM_PACKET_FIELDS];
	String *pre_trim ;
	
	size_t packet_ip = 0;
	size_t masked_packet_ip = 0;
	size_t masked_rule_ip = 0;

	size_t size;
	const char* delimiters = "=,";
    
    
	//send the IP part to set value
	if (!(this->set_value(this->value)))
	{	
		cout << "hi1" << endl;
		delete[] packet_fields;
		return FALSE;
	}

	//divide packet into arr of phrases
	//sep_packet_field(packet, &packet_fields, &num_fields);

	packet.split(delimiters, &pre_trim, &size);
	//cout << "size is: " << size << endl;
    if (size != NUM_PACKET_FIELDS) //check for valid packet struct
    {
    	//cout << "hi2" << endl;
		delete[] packet_fields;
    	delete[] pre_trim;
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

			ip_to_int(packet_fields[i+1], &packet_ip);
			masked_packet_ip = packet_ip>> (FOUR_BYTES - mask);
		masked_rule_ip = (this->IP_value) >> (FOUR_BYTES - mask);
	//		cout << "packet after mask is:" << masked_rule_ip << endl;
	//		cout << "IP_value is: " << masked_rule_ip << endl;

		//	cout << "IP_value (rule) is:" << (this->IP_value) << endl;
		//	cout << "masked_packet is:" << masked_ << endl;
			if (masked_packet_ip == masked_rule_ip)
			{
				delete[] packet_fields;
				delete[] pre_trim;
				return TRUE;
			}
		//	cout << "hi3" << endl;
			delete[] packet_fields;
			delete[] pre_trim;
			return FALSE;
		}
		cout << "hi4" << endl;
	}
delete[] packet_fields;	
delete[] pre_trim;
return FALSE;

}



IPField::IPField() : mask(0),  IP_value(0) {}