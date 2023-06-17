//#ifndef PORT_H
//#define PORT_H

#include "string.h"
#include "generic-field.h"

class PortField : public GenericField
{	
	size_t min_port;
	size_t max_port;
	String value;
	String target; //options are "dst-ip" or "src-ip" 
	public:
		//constructors:
		PortField();
		PortField(String command);
		//destructor:
		//~PortField();
		//methods:
	    bool set_value(String value);
	    bool match(String packet);
};

//#endif
