#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    char name[20];
    char phone[20];
    char email[20];
} Contact;

typedef struct {
    Contact *contacts;
    int size;
    int capacity;
} ContactList;

void listContacts(const ContactList *list);

void addContact(ContactList *list, Contact contact);

void deleteContact(ContactList *list, Contact contact);

int main() {
    ContactList list;
    list.size = 0;
    list.capacity = 10;
    list.contacts = malloc(list.size*sizeof(Contact));

    Contact newContact = {.id =  1,.name = "omer",.phone = "05123123",.email = "onal@asd.com"};
    addContact(&list, newContact);
    deleteContact(&list, newContact);

    listContacts(&list);
    return 0;
}

void addContact(ContactList *list, Contact contact) {
    if (list->size == list->capacity) {
        
        int newCapacity = list->capacity * 2;
        Contact *newContacts = (Contact *)realloc(list->contacts, newCapacity * sizeof(Contact));
        if (newContacts == NULL) {
            fprintf(stderr, "Unable to allocate more memory.\n");
            return;
        }
        list->contacts = newContacts;
        list->capacity = newCapacity;
    }

    list->contacts[list->size] = contact;
    list->size++;
}

void deleteContact(ContactList *list, Contact contact){
    int i;
    for(i = 0; i < list->size; i++){
        if(list->contacts[i].id == contact.id){
            break;
        }
    }
    if(i == list->size){
        return;
    }
    for(; i < list->size - 1; i++){
        list->contacts[i] = list->contacts[i + 1];
    }
    list->size--;
}

void listContacts(const ContactList *list) {
    printf("%-5s %-20s %-20s %-30s\n", "ID", "Name", "Phone", "Email");
    for (int i = 0; i < list->size; ++i) {
        printf("%-5d %-20s %-20s %-30s\n",
               list->contacts[i].id,
               list->contacts[i].name,
               list->contacts[i].phone,
               list->contacts[i].email);
    }
}