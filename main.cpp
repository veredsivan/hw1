#include "string.h"
#include "ip.h"
#include "port.h"
#include "generic-field.h"
#include "input.h"

int main(int argc, char* argv[]) {
    // Check if the command-line arguments are correct
    if (check_args(argc, argv) != 0) {
        return 1;
    }

    // Get the firewall rule from the command-line argument
    String firewallRule = String(argv[1]);

    char del[3] = {'=','-','\0'};
    String str;
    String** out;//check if the size is really needed
    size_t *size;
	GenericField *field;
	
    firewallRule.split(del, out, size);
    str = (*out)[0].trim();
    (*out)[0]=str;
    str = (*out)[1].trim();
    (*out)[1]=str;


   //if it's ip
    if((*out)[1].equals("ip")){
      if ((!(*out)[0].equals("src"))|| !((*out)[0].equals("dst"))){
   	delete [] (*out);
   	return false;
   }

   *field= IPField((*out)[0]);
   //parse gets ip1 as a &?? how do we connect between the generic_field and our functions?


    }


    //if it's port
    if((*out)[1].equals("port")){
      if (!((*out)[0].equals("src"))|| !((*out)[0].equals("dst"))){
   	delete [] (*out);
   	return false;
   }


   *field= PortField((*out)[0]);

    }


    parse_input(*field);

    return 0;
}