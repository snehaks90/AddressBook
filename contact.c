#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{   
    printf("------------------------------------------------------------\n");
    printf("%-6s\t %-10s\t %-13s\t %-16s\n", "sl.no", "Name", "Phone Number", "E-mail");
    printf("------------------------------------------------------------\n");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
  printf("%-6d\t %-10s\t %-13s\t %-16s\n", i+1,  addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); 
    }
     printf("-----------------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    

    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{       

        int i = addressBook->contactCount;

        printf("Enter the name\n");
        scanf(" %[^\n]", addressBook->contacts[i].name);
        

        // to store mobile number
        char phone[20];
        int valid;
        do {
        printf("Enter the number\n");
        scanf("%s", phone);
        valid = validate_phone(addressBook, phone, -1);
        if(valid == 0)
        {
         printf("Invalid number!! Enter the mobile number again\n");
        }
        } while(valid != 1);
        strcpy(addressBook->contacts[i].phone, phone);



        // to store email id
        char email[30];
        
        do {
        printf("Enter the emailid\n");
        scanf("%s", email);
        valid = validate_emailid(addressBook, email, -1);
        if(valid == 0)
        {
           printf("Invalid mail id!! Enter valid mail id\n");
        }
        } while(valid != 1);

        strcpy(addressBook->contacts[i].email, email);
       

 addressBook->contactCount++;
	

}

int searchContact(AddressBook *addressBook, int selection) 
{        
	 char input[50];
	 int choice;
	 int index[100];
	 int matchCount = 0;
	 int flag = 0; // not found
         
           printf("1. Search by name: \n2. Search by phone number:\n3. Search by email:\n4. Exit");
           printf("\nEnter the choice(1/2/3/4):\n");
           scanf("%d",&choice);  
      
	   switch(choice)
	    {
	      case 1: printf("Enter the name:\n");
		           scanf(" %[^\n]", input);
		           for(int i = 0; i < addressBook->contactCount; i++)
		            {
			            if(strcmp(input, addressBook->contacts[i].name) == 0)  //0 ==0
		               {    
				            printf("------------------------------------------------------------\n");
				            printf("%-6d\t %-10s\t  %-13s\t %-16s\t", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
			               printf("\n------------------------------------------------------------\n"); 
			      	      flag = 1;
				            index[matchCount++]= i;
			            }
                   }
                   if (!flag)
                      printf("Contact not found\n");

                  break;

         case 2:   printf("Enter the phone number:\n");
		             scanf("%s", input);
                     for(int i = 0; i < addressBook->contactCount; i++)
                     {
                        if(strcmp(input, addressBook->contacts[i].phone) == 0)
                        {  
			                  printf("------------------------------------------------------------\n");
                           printf("%-6d\t %-10s\t  %-13s\t %-16s\t", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
			                  printf("\n------------------------------------------------------------\n");
				               flag = 1;
				               index[matchCount++]= i;
                        }
                     }
                     if (!flag)
                        printf("Contact not found\n");

		                break;
             
         case 3:   printf("Enter the email:\n");
                   scanf("%s", input);
                     for(int i = 0; i < addressBook->contactCount; i++)
                     {
                        if(strcmp(input, addressBook->contacts[i].email) == 0)
                        {  
				               printf("------------------------------------------------------------\n");
                           printf("%-6d\t %-10s\t   %-13s\t   %-16s\t",  matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	                        printf("\n------------------------------------------------------------\n");
				               flag = 1;
				               index[matchCount++]= i;
			               }
                     }	
                     if (!flag)
                     printf("Contact not found\n");

                    break;

         case 4:
                     printf("Exiting..\n");
                     return -1;

         default:  printf("Invalid choice. Please try again\n");
                          break;
                        
	    }
     
      
	    if(choice != 4)
       {

         if(matchCount > 1 && selection)
	      {
           printf("Multiple contacts found. Select contact from 1 to %d \n", matchCount);
	        int select;
	        scanf("%d", &select);
	        if(select >= 1 && select <= matchCount)
		     return index[select - 1];
	        else
	        {
	           printf("Invalid choice\n");
	            return -1;
	        }
	      } 
        
	      else if(matchCount == 1)
		     return index[matchCount - 1];
	 
      
      }
      return -1;
}
void editContact(AddressBook *addressBook)
{     
      

      int i = searchContact(addressBook, 1); 
      if(i == -1)
      {
	     // printf("Contact not found");
	      return;
      }
      
      char newname[30];
      int option;
      int valid;
      
      do 
      {     
       printf("Which field you want to edit?\n");
       printf("1. Name: \n2. Phone number:\n3. Email:\n4. Exit\n");
       printf("Enter the option(1/2/3/4):\n");
       scanf("%d",&option);
       getchar();
           switch(option)
           {
             case 1: 
		                printf("Enter the new name\n");
                     scanf(" %[^\n]", newname);
                     strcpy(addressBook->contacts[i].name, newname);
		               printf("The contact name is succsessfully updated\n");
                     break;



             case 2:  
                     do
                     {
		                  printf("Enter the new mobile number\n");
		                  scanf("%s", newname);
                   
                        valid = validate_phone(addressBook, newname, i);
                        if(valid == 0)
                        {
                          printf("Invalid number!! Enter the mobile number again\n");
                        }
                     } while(valid != 1);
                      

		               strcpy(addressBook->contacts[i].phone, newname);
		               printf("The contact number is succsessfully updated\n");
		               break;
  
	         case 3:
                      do
                      {
		                 printf("Enter the new emailid\n");
                       scanf("%s", newname);
                      
                      valid = validate_emailid(addressBook, newname, i);
                        if(valid == 0)
                        {
                           printf("Invalid mail id!! Enter valid mail id \n");
                        }
                     } while(valid != 1);
                      

                      strcpy(addressBook->contacts[i].email, newname);
		                printf("The contact email id is succsessfully updated\n");
                      break;
            case 4:
                     printf("Exiting..\n");
                     return ;    

            default:  printf("Invalid input\n");
                      return ;		      
            }
      } while( option != 4);
      
	    
	   printf("Updated contact details:\n");
            printf("%-6s\t %-10s\t %-13s\t %-16s\n", "sl.no", "Name", "Phone Number", "E-mail");                                                                        printf("------------------------------------------------------------\n");
	    printf("%-6d %-10s\t %-13s\t %-16s\t", 
	             i+1, addressBook->contacts[i].name,
	             addressBook->contacts[i].phone, 
		     addressBook->contacts[i].email);
	    printf("\n------------------------------------------------------------\n");
        
    
}

void deleteContact(AddressBook *addressBook)
{  
   int i = searchContact(addressBook, 1);
      if(i == -1)
      {
             // printf("Contact not found");
              return;
      }

      char delete;
      printf("Are you sure you want to delete this contact?(y/n)\n");
      scanf(" %c", &delete);
      if(delete == 'y' || delete =='Y')
      {
           for(int j = i; j < addressBook->contactCount - 1; j++)
            {
                strcpy( addressBook->contacts[j].name, addressBook->contacts[j+1].name);
		strcpy( addressBook->contacts[j].phone, addressBook->contacts[j+1].phone);
		strcpy( addressBook->contacts[j].email, addressBook->contacts[j+1].email);
	    }
	   addressBook->contactCount--;
	   printf("Contact deleted succsessfully\n");
      }
      else if(delete == 'n' || delete == 'N')
      {    
	     printf("Deletion cancelled\n");
	     return;
      }
      else
           {
	      printf("Invalid choice!!\n");
              return;
           }
              

}
