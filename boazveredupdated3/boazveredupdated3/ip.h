#ifndef IP_H
#define IP_H

//#include "string.h"
#include "generic-field.h"

class IPField : public GenericField {
	public: 
	  	int mask;
		size_t IP_value; //stores the ip in int
		String value;
		String target; //options are "dst-ip" or "src-ip" 
		//constructors:
		IPField();
		IPField(String command);
		//destructor:
		//~IPField();
	//methods:
	    bool set_value(String value);
	    bool match(String packet);

};

#endif
