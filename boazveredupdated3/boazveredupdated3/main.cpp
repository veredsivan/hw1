//#include "string.h"
//#include "libinput.so"
#include "generic-field.h"
//#include <iostream>
#include "ip.h"
#include "port.h"
#include "input.h"
#define PORT "port"
#define IP "ip"
#define TARGET 1
#define RULE 1
#define COMMAND_FIELDS 3







/**
//return if object is IP or port
String get_class(String command)
{
	
}
**/

int main(int argc, char **argv) 
{
	String *command_fields;
	size_t size;
	check_args(argc, argv);
	String command(argv[RULE]);
	command.trim();
	command.split("=-", &command_fields, &size);
	command_fields[TARGET].trim();
	//send command to relevant class
	if (command_fields[TARGET].equals(PORT))
	{
		PortField field(command);
		parse_input(field); 
	}
	else if (command_fields[TARGET].equals(IP))
	{
		IPField field(command);
		parse_input(field);
	}
	delete[] command_fields;
	return 0;
}


