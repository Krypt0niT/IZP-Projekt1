#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define contactsLimit 50

typedef struct contact
{
    char name[100 + 1];
    char number[100 + 1]; 
} contact;

bool tryReadContacts(contact *contacts);

int main(int argc, char *argv[])
{
    contact contacts[contactsLimit];

    bool success = tryReadContacts(contacts);
    if (!success)
    {
        printf("Reading contacts was not successful.");
    }
    
    return 0;
}

bool tryReadContacts(contact *contacts)
{
    for (int userIndex = 0; userIndex < contactsLimit - 1; userIndex++) // TODO: test size
    {
        char name[101], number[101];

        int scanfResult = scanf("%100[^\n]\n%100[^\n]\n", name, number);
        if (scanfResult == EOF)
        {
            break;
        }
        if (scanfResult != 2)
        {
            printf("Invalid input format.\n");
            return false;
        }

        contact newContact;
        strcpy(newContact.name, name);
        strcpy(newContact.number, number);

        contacts[userIndex] = newContact;
        printf("%s, %s\n", contacts[userIndex].name, contacts[userIndex].number);
    }
    return true;
}