#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define contactsLimit 100
#define defaultSizeLimit 100 + 1

const char tNine[10][5] = {"+", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; 

typedef struct contact
{
    char string[defaultSizeLimit];
    char number[defaultSizeLimit]; 
} contact;

int readContacts(contact *contacts);
void printfContacts(contact *contacts, int arraySize);
contact contactCtor(char string[], char number[]);
bool isContactValidFormat(char string[], char number[]);
bool isWithinKey(char item, char key);
int filterContacts(contact *contacts, int contactsCount, contact *filteredContacts, char *filter);
bool isMatchingStrictOrder(char string[], char *filter);

int main(int argc, char *argv[])
{
    contact contacts[contactsLimit];

    int contactsCount = readContacts(contacts);
    if (contactsCount == 0)
    {
        printf("Reading contacts was not successful.");
        return 1; // TODO: code
    }

    if (argc == 2)
    {
        char input[defaultSizeLimit];
        strcpy(input, argv[1]); // TODO: format

        contact filtered[contactsLimit];

        int filteredItemsCount = filterContacts(contacts, contactsCount, filtered, input);
        printfContacts(filtered, filteredItemsCount);
        
        if (filteredItemsCount == 0)
        {
            printf("Not found");
        }

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
        char string[defaultSizeLimit], number[defaultSizeLimit];

        int scanfResult = scanf("%100[^\n]\n%100[^\n]\n", string, number);
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

        bool isValid = isContactValidFormat(string, number);
        if (!isValid) // TODO is contact input invalid or whole inpuit is invalid?
        {
            continue;
        }

        contact newContact = contactCtor(string, number);

        contacts[userIndex] = newContact;
    }
    printf("Unsupported contacts input lenght.");
    return 0;
}

bool isContactValidFormat(char string[], char number[])
{
    if (strlen(string) > 100 || strlen(number) > 100) // TODO: strlen is never > 100
    {
        return false;
    }

    bool isNumberNumeric = true;
    for (int i = 0; i < (int)strlen(number); i++)
    {
        if (!isdigit((int)number[i]))
        {
            isNumberNumeric = false;
        }
    }
    if (!isNumberNumeric) 
    {
        return false;  
    }
    
    return true;
}

contact contactCtor(char string[], char number[])
{
    contact newContact;
    strcpy(newContact.string, string);
    strcpy(newContact.number, number);

    return newContact;
}

void printfContacts(contact *contacts, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        printf("%s, %s\n", contacts[i].string, contacts[i].number); // TODO: \n na konci?
    }
}

bool isWithinKey(char item, char key)
{
    if (item == key)
    {
        return true;
    }

    char stringKey[] = { key };
    int keyNumericValue = atoi(stringKey);

    for (int i = 0; i < (int)strlen(tNine[keyNumericValue]); i++)
    {
        if (tNine[keyNumericValue][i] == item)
        {
            return true;
        }
    }

    return false;
}

int filterContacts(contact *contacts, int contactsCount, contact *filteredContacts, char *filter)
{
    int filteredCount = 0;

    for (int i = 0; i < contactsCount; i++)
    {
        contact c = contacts[i];

        bool stringMatch = isMatchingStrictOrder(c.string, filter);
        bool numberMatch = isMatchingStrictOrder(c.number, filter);

        if (stringMatch || numberMatch)
        {
            filteredContacts[filteredCount] = c;
            filteredCount++;
        }
    }
    
    return filteredCount;
}

bool isMatchingStrictOrder(char *string, char *filter) // TODO: naming
{
    int filterLength = strlen(filter);
    int stringLength = strlen(string);

    int filterIndex = 0;
    int matchingCharacterCount = 0;
    
    for (int i = 0; i < stringLength; i++)
    {
        if (isWithinKey(string[i], filter[filterIndex]))
        {
            matchingCharacterCount++;
            filterIndex++;
        }
        else
        {
            matchingCharacterCount = 0;
            filterIndex = 0;
            // TODO: comment functionality
            if (isWithinKey(string[i], filter[0]))
            {
                matchingCharacterCount = 1;
                filterIndex = 1;
            }
        }

        if (matchingCharacterCount == filterLength)
        {
            return true;
        }        
    }

    return false;
}

bool isContactInArray(contact c, contact *contacts, int contactsSize)
{
    for (int i = 0; i < contactsSize; i++)
    {
        if (c.string == contacts[i].string && c.number == contacts[i].number)
        {
            return true;
        }
    }

    return false;
}
