#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *address_book);
void searchContact(AddressBook *address_book);
void editContact(AddressBook *address_book);
void deleteContact(AddressBook *address_book);
void listContacts(AddressBook *address_book, int);
void initialize(AddressBook *address_book);
void saveContactsToFile(AddressBook *address_book);
void populateAddressBook(AddressBook* address_book);
int validate_number(char*, AddressBook *address_book);
int validate_mail(char*);

#endif
