#include<stdio.h>
#include"contact.h"
#include<ctype.h>
#include<string.h>

int validate_phone(AddressBook *addressBook, char *phone, int skipIndex)
{
       
	   int len = strlen(phone);

	if(len != 10)
	{
		return 0;
	}
        
	
	for(int i = 0; i < 10; i++)
	{
		if(!(isdigit(phone[i])))
		{
		return 0;
		}
	}
for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (j == skipIndex)
		{
            continue;
		}

        if (strcmp(phone, addressBook->contacts[j].phone) == 0)
        {
            printf("This mobile number already exists. Try with another number.\n");
            return 2;
        }
    }
    

	return 1;
}
                
        
      

