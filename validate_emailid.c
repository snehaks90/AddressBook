#include<stdio.h>
#include"contact.h"
#include<ctype.h>
#include<string.h>

int validate_emailid(AddressBook *addressBook, char *email, int skipIndex)
{
	char* at = strchr(email , '@');

        // check @ is present or not
	if(!at)
	  return 0;

	char *str = ".com";
        char *ptr = strstr(email, str);

	if(ptr== NULL || strcmp(ptr, str) != 0)
		return 0;	
        
	// check if upper case is present
	for(int i = 0; i < strlen(email); i++)
	{
	if(isupper(email[i]))
	    return 0;
	}
        

	// check before @ and after @ there is a chara
	if(email[0] == '@'  || at[1] == '.')
	    return 0;
      for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (j == skipIndex)
            continue;

        if (strcmp(addressBook->contacts[j].email, email) == 0)
        {
            printf("This email already exists. Try with a new email.\n");
            return 2;
        }
    }  
    

       

	return 1; // if all conditions passed

	}

