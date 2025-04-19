#include<stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook address_book;
    initialize(&address_book); // Initialize the address_book

    do {
        
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. Display contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
              createContact(&address_book);
                break;
            case 2:
              searchContact(&address_book);
                break;
            case 3:
                editContact(&address_book); 
                break;
            case 4:
                deleteContact(&address_book); 
                break;
            case 5: 
            int sort_criteria;
            printf("Select criteria\n1.By name\n2.By phone number\n3.By mail id\n");
            scanf("%d", &sort_criteria);
               listContacts(&address_book, sort_criteria);
                break;
            case 6:
                printf("Saving and Exiting...\n");
				saveContactsToFile(&address_book);
				printf("Contacts saved!\n");
				choice = 7;
                break;
            case 7:

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}

