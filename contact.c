#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"

void initialize(AddressBook *address_book) 
{
	FILE* fptr = fopen("contacts.csv", "r");
	fscanf(fptr, "#%d", &address_book->contactCount);
	for(int i=0; i<address_book->contactCount; i++)
		fscanf(fptr, "%[^,],%[^,],%[^\n]\n", address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
	fclose(fptr);
}

void saveContactsToFile(AddressBook *address_book)
{
	FILE* ptr = fopen("contacts.csv", "w");
    fprintf(ptr, "#%d", address_book->contactCount);
    for(int i=0; i<address_book->contactCount; i++)
    {
        //printf("Entered\n");
        fprintf(ptr, "%s,%s,%s\n", address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
    }
    fclose(ptr);
    return;
}

void listContacts(AddressBook *address_book, int sort_criteria) 
{
   Contact temp;
    // Sort contacts based on the chosen criteria
    printf("\nNames\t\tphone no\t\temail id\n");
    if(sort_criteria == 1)
    {
        for(int i=0; i<address_book->contactCount-1; i++)
        {
            for(int j=0; j<address_book->contactCount-1-i; j++)
            {
                if(strcmp(address_book->contacts[j].name, address_book->contacts[j+1].name)>0)
                {
                    temp = address_book->contacts[j];
                    address_book->contacts[j] = address_book->contacts[j+1];
                    address_book->contacts[j+1] = temp;
                }
            }
        }
    }
    else if (sort_criteria == 2)
    {
        for(int i=0; i<address_book->contactCount-1; i++)
        {
            for(int j=0; j<address_book->contactCount-1-i; j++)
            {
                if(strcmp(address_book->contacts[j].phone, address_book->contacts[j+1].phone)>0)
                {
                    temp = address_book->contacts[j];
                    address_book->contacts[j] = address_book->contacts[j+1];
                    address_book->contacts[j+1] = temp;
                }
            }
        }
    }
    else
    {
        for(int i=0; i<address_book->contactCount-1; i++)
        {
            for(int j=0; j<address_book->contactCount-1-i; j++)
            {
                if(strcmp(address_book->contacts[j].email, address_book->contacts[j+1].email)>0)
                {
                    temp = address_book->contacts[j];
                    address_book->contacts[j] = address_book->contacts[j+1];
                    address_book->contacts[j+1] = temp;
                }
            }
        }
        
    }
        for(int i=0; i<=address_book->contactCount; i++)
            printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);

        
    
    
}

void createContact(AddressBook *address_book)
{


 // create contact
    char temp_validate[100];
    int valid;
    do{
        // reading the name
        printf("Enter the name: ");
        scanf(" %[^\n]", address_book->contacts[address_book->contactCount].name);

        //////////////////////////// reding the phone number ////////////////////////////
        do
        {
            printf("Enter the phone number: ");
            scanf(" %s", temp_validate);
    
            // validating the number 
            valid = validate_number( temp_validate,address_book);
            
            if(valid == 0)// number is valid
                strcpy(address_book->contacts[address_book->contactCount].phone, temp_validate);
            else if(valid == 1)
                continue;
            else
                return;
            break;
        }while(1);
        if(valid == 2)
            return;
        //////////////////////////// Reading the mail ///////////////////
        do
        {
            printf("Enter the mail id: ");
            scanf(" %s", temp_validate);
            valid = validate_mail(temp_validate);
            
            if(valid == 0)// number is valid
                strcpy(address_book->contacts[address_book->contactCount].email, temp_validate);
            else if(valid == 1)
                continue;
            else
                return;
            break;
        }while(1);
        if(valid == 2)
            return;
        printf("\n\nconatact created successfully\n");
        address_book->contactCount++;
        return;
    }while(address_book->contactCount<=MAX_CONTACTS); 
}

void searchContact(AddressBook *address_book) 
{
    char temp_validate[30], index = 0;
    /* Define the logic for search */
    printf("Search: ");
    scanf(" %s", temp_validate);
    
    if(temp_validate[0] >= '0' && temp_validate[0]<= '9')
    {
        if(temp_validate[1] >= '0' && temp_validate[1]<= '9') // Assuming search by number
            for(int i=0; i<=address_book->contactCount; i++)
                if(strstr(address_book->contacts[i].phone, temp_validate))
				{
                    printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
					index = 1;
				}
    }
    else if(strstr(temp_validate, ".com") || strchr(temp_validate, '@'))
    {
        // assuming search by email
        for(int i=0; i<=address_book->contactCount; i++)
            if(strstr(address_book->contacts[i].email, temp_validate))
			{
                printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
				index = 1;
			}
    }
    else
    {
        // assuming search by name
        for(int i=0; i<address_book->contactCount; i++)
            if(strstr(address_book->contacts[i].name, temp_validate))
			{
                printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
				index = 1;
			}
	}
	if(index)
		return;
	else
    printf("\ncontact not found!\n");
}

void editContact(AddressBook *address_book)
{ 

	int found, count, valid;
    char temp_validate[30];
	/* Define the logic for Editcontact */
	do 
	{
	    count = 0;
        printf("Search contact to edit: ");
        scanf(" %s", temp_validate);
        printf("\n");
        if(temp_validate[0] >= '0' && temp_validate[0]<= '9')
        {
            if(temp_validate[1] >= '0' && temp_validate[1]<= '9') // Assuming search by number
                for(int i=0; i<=address_book->contactCount; i++)
                    if(strstr(address_book->contacts[i].phone, temp_validate))
                    {
                        printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
                        count ++;
                        found = i;
                    }

    }
    else if(strstr(temp_validate, ".com") || strchr(temp_validate, '@'))
    {
        // assuming search by email
        for(int i=0; i<=address_book->contactCount; i++)
            if(strstr(address_book->contacts[i].email, temp_validate))
            {
                printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
                count++;
                found = i;
            }
    }
    else
    {
        // assuming search by name
        for(int i=0; i<address_book->contactCount; i++)
            if(strstr(address_book->contacts[i].name, temp_validate))
            {
                printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
                count++;
                found = i;
            }
    }
    if(count > 1)
    {
        printf("\nToo many conatcts Found provide more info!\n\n");
        printf("Select option below:\n1.continue\n2.back\n");
        scanf("%d", &count);
        if(count == 1)
            continue;
        else
            return;
    }
    else if(count != 1)
    {
        printf("\ncontact not found!\n\n");
        printf("Select option below:\n1.continue\n2.back\n");
        scanf("%d", &count);
        if(count == 1)
            continue;
        else
            return;
    }
    printf("\nSelect option for edit\n");
    printf("1.Name\n2.number\n3.email id\n");
    scanf("%d", &count);
    switch(count)
    {
        case 1:
            count = 0;
            printf("Enter the new name: ");
            scanf(" %[^\n]", address_book->contacts[found].name);
            printf("\nName updated successfully\n\n");
            return;
        case 2:
            do
            {
                count = 0;
                printf("Enter the new number: ");
                scanf(" %s", temp_validate);
                // number lenght must be 10
                if(strlen(temp_validate) != 10)
                {
                    printf("\nInvalid number!\n1.\ncontinue\n2.back\n");
                    scanf("%d", &count);
                    if(count == 1)
                        continue;
                    else
                        break;
                }
                // checking numbers must be between 0 and 9
                for(int i=0; temp_validate[i]; i++)
                {
                    if(temp_validate[i]>'9' || temp_validate[i]<'0')
                    {
                        printf("\nInvalid number!\n1.\ncontinue\n2.back\n");
                        scanf("%d", &count);
                        if(count == 1)
                            continue;
                        else
                            break;
                    }
                }
                break;
            }while(1);
            
            if(count == 2)
                return;
            strcpy(address_book->contacts[found].phone, temp_validate);
            printf("\nNumber updated successfully!\n");
            return;
        case 3:
        do
        {
            count = 0;
            printf("\nEnter the new email\n");
            scanf(" %s", temp_validate);
            count = validate_mail(temp_validate);
            if(count != 1)
                break;
            else
                continue;
            break;
            
        }while(1);
        if(count == 2)
            return;
        strcpy(address_book->contacts[found].email, temp_validate);
        printf("\nMail updated successfully!\n");
        return;
    }
	}while(1);
}

void deleteContact(AddressBook *address_book)
{

	int index, count=0;
	char temp_validate[30];
	do
	{
	    count = 0;
        /* Define the logic for deletecontact */
        printf("\nEnter the contact details to delet: ");
        scanf(" %[^\n]", temp_validate);
        if(temp_validate[0] >= '0' && temp_validate[0]<= '9')
        {
        if(temp_validate[1] >= '0' && temp_validate[1]<= '9') // Assuming search by number
            for(int i=0; i<=address_book->contactCount; i++)
                if(strstr(address_book->contacts[i].phone, temp_validate))
                {
                    printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
                    index = i;
                    count++;
                }

        }
        else if(strstr(temp_validate, ".com") || strchr(temp_validate, '@'))
        {
        // assuming search by email
            for(int i=0; i<=address_book->contactCount; i++)
                if(strstr(address_book->contacts[i].email, temp_validate))
                {
                    printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
                    index = i;
                    count++;
                }
        }
        else
        {
            // assuming search by name
            for(int i=0; i<address_book->contactCount; i++)
                if(strstr(address_book->contacts[i].name, temp_validate))
                {
                    printf("%s\t%s\t%s\n",address_book->contacts[i].name, address_book->contacts[i].phone, address_book->contacts[i].email);
                    index = i;
                    count++;
                }
        }
    if(count>1)
    {
        printf("\nToo many contacts please provide more information!\n");
        printf("\nselect option\n1.continue\n2.back\n");
        scanf("%d", &count);
        if(count == 1)
            continue;
        else 
            return;
    }
    else if(count == 0)
    {
        printf("\nContact not found!\n");
        printf("\nselect option\n1.continue\n2.back\n");
        scanf("%d", &count);
        if(count == 1)
            continue;
        else 
            return;
    }
    printf("\nDeleting Contact!\n1.delete\n2.back\n");
    scanf("%d", &count);
    if(count == 2)
        return;
    for(int i=index; i<address_book->contactCount-1; i++)
    {
        address_book->contacts[i] = address_book->contacts[i+1];
    }
    printf("\n\nContact deleted successfully!\n\n");
	address_book->contactCount--;
    return;
   
	}while(1);
}


/////// function to validate the number //////////
int validate_number(char* temp_validate, AddressBook *address_book)
{
    int found;
    // number lenght must be 10
        if(strlen(temp_validate) != 10)
        {
            printf("Invalid number!\n1.continue\n2.back\n");
            scanf("%d", &found);
            if(found == 1)
                return 1;
            else
                return 2;
        }
        found = 0;
        
        // checking the number is present or not
        for(int i=0; i<address_book->contactCount; i++)
        {
            if(strstr(address_book->contacts[i].phone, temp_validate) != NULL) 
            {
                found = 1;
                break;
            }
        }
        if(found)
        {
            printf("Number exists!\n");
            printf("1.continue\n2.Back\n");
            scanf("%d", &found);
            if(found == 1)
                return 1;
            else
                return 2;
        }

        // checking numbers must be between 0 and 9
        for(int i=0; temp_validate[i]; i++)
        {
            if(temp_validate[i]>'9' || temp_validate[i]<'0')
            {
                printf("Invalid number!\n1.continue\n2.back\n");
                scanf("%d", &found);
                if(found == 1)
                    return 1;
                else
                    return 2;
            }
        }
            
    return 0;
}

int validate_mail(char* temp_validate)
{
		int found, count_at = 0, count_dot=0;
    
    // validating the mail id
        char* address1 = strchr(temp_validate, '@');
        if(address1 == NULL)
        {
            printf("Invalid mail id!\n1.\ncontinue\n2.back");
                scanf("%d", &found);
                if(found == 1)
                    return 1;
                else
                    return 2;
        }
        char*address2 = strchr(temp_validate, '.');
        if(address2 == NULL || address1+1 == address2)
        {
            printf("Invalid mail id!\n1.\ncontinue\n2.back");
                scanf("%d", &found);
                if(found == 1)
                    return 1;
                else
                    return 2;
        }
        // chrcking is lower and starting name must not be digit
        for(int i=0; temp_validate[i]; i++)
        {
            if(temp_validate[i] <'a' || temp_validate[i] >'z')
            {
                if(temp_validate[i] == '@' || temp_validate[i] == '.' || temp_validate[i]>='0' && temp_validate[i]<='9')
				{
					if(temp_validate[i] == '@')
						count_at++;
					if(temp_validate[i]=='.')
						count_dot++;
					if(count_at>1||count_dot>1)
						break;
					continue;
				}
                else
                {
                    printf("Invalid mail id!\n1.\ncontinue\n2.back");
                    scanf("%d", &found);
                    if(found == 1)
                        return 1;
                    else
                        return 2;
                }
                    
            }
        }
		if(count_at>1||count_dot>1)
		{
			 printf("Invalid mail id!\n1.\ncontinue\n2.back");
             scanf("%d", &found);
             if(found == 1)
                 return 1;
             else
                 return 2;
		}

    return 0;
}

