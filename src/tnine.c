#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define contactsLimit 100
#define defaultSizeLimit 100 + 1


typedef struct contact
{
    char name[defaultSizeLimit];
    char number[defaultSizeLimit]; 
} contact;

int readContacts(contact *contacts);
void printfContacts(contact *contacts, int arraySize);
contact contactCtor(char name[], char number[]);
bool isContactValidFormat(char name[], char number[]);

int main(int argc, char *argv[])
{
    contact contacts[contactsLimit];

    int contactsCount = readContacts(contacts);
    if (contactsCount == 0)
    {
        printf("Reading contacts was not successful.");
    }

    if (argc == 2)
    {
        char input[defaultSizeLimit];
        strcpy(input, argv[1]);

        printfContacts(contacts, contactsCount);
        // do
        
    }
    else if (argc == 1)
    {
        printfContacts(contacts, contactsCount);
    }
    
    return 0;
}

int readContacts(contact *contacts)
{
    for (int userIndex = 0; userIndex < contactsLimit - 1; userIndex++) // TODO: test size
    {
        char name[defaultSizeLimit], number[defaultSizeLimit];

        int scanfResult = scanf("%100[^\n]\n%100[^\n]\n", name, number);
        if (scanfResult == EOF)
        {
            int contactsCount = userIndex; // no contact was added current iteration.
            return contactsCount;
        }
        if (scanfResult != 2)
        {
            printf("Invalid input format.\n");
            return 0;
        }

        bool isValid = isContactValidFormat(name, number);

        if (!isValid) // TODO is contact input invalid or whole inpuit is invalid?
        {
            continue;
        }

        contact newContact = contactCtor(name, number);

        contacts[userIndex] = newContact;
    }
    printf("Unsupported contacts input lenght.");
    return 0;
}

bool isContactValidFormat(char name[], char number[])
{
    if (strlen(name) > 100 || strlen(number) > 100) // TODO: strlen is never > 100
    {
        return false;
    }

    bool isNumberNumeric = true;
    for (int i = 0; i < strlen(number); i++)
    {
        if (!isdigit((int)number[i]))
        {
            isNumberNumeric = false;
        }
    }
    if (!isNumberNumeric) 
        return false;  
    
    return true;
}


contact contactCtor(char name[], char number[])
{
    contact newContact;
    strcpy(newContact.name, name);
    strcpy(newContact.number, number);

    return newContact;
}

void printfContacts(contact *contacts, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        printf("%s, %s\n", contacts[i].name, contacts[i].number); // TODO: \n na konci?
    }
}