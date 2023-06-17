#include "string.h"
#include "libinput.so"
#include "generic-field.h"
//#include <iostream>
#include "ip.h"
#include "port.h"
#include "input.h"
#define PORT "port"
#define IP "ip"
#define TARGET 1
#define RULE 1








//return if object is IP or port
String get_class(String command)
{
	String** tmp;
	//String class;
	size_t size;
	command.split("=-", tmp, &size);
	return (tmp[TARGET]->trim());																											
}


int main(int argc, char **argv) 
{
	check_args(argc, argv);
	String command(argv[RULE]);
	//send command to relevant class
	String direction = get_class(command);
	if (direction.equals(PORT))
	{
		PortField field(command);
		parse_input(field); 
	}
	else if (direction.equals(IP))
	{
		IPField field(command);
		parse_input(field);
	}
	
	
	return 0;
}


