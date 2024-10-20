#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define contactsLimit 100
#define defaultSizeLimit 100 + 1

const char tNine[10][5] = {"+", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; 

typedef struct Scontact
{
    char string[defaultSizeLimit];
    char number[defaultSizeLimit]; 
} contact;

contact contactCtor(char string[], char number[]);
int filterContacts(contact *contacts, int contactsCount, contact *filteredContacts, char *filter, bool strictFiltration);
int readContacts(contact *contacts);
bool isContactValidFormat(char string[], char number[]);
bool isWithinKey(char item, char key);
bool isMatchingFilter(char *string, char *filter, bool strictFiltration);
bool setValidInput(char input[], char consoleArgument[]);
void printfContacts(contact *contacts, int arraySize);

int main(int argc, char *argv[])
{
    contact contacts[contactsLimit];

    int contactsCount = readContacts(contacts);
    if (contactsCount == 0)
    {
        fprintf(stderr, "Reading contacts was not successful.");
        return 1;
    }

    char inputFilter[defaultSizeLimit];
    contact filteredContacts[contactsLimit];
    int filteredItemsCount = 0;

    if (argc == 2)
    {
        bool result = setValidInput(inputFilter, argv[1]);
        if (!result) return 2;

        filteredItemsCount = filterContacts(contacts, contactsCount, filteredContacts, inputFilter, (bool)true);
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-s") == 0)
        {
            bool result = setValidInput(inputFilter, argv[2]);
            if (!result) return 2;

            filteredItemsCount = filterContacts(contacts, contactsCount, filteredContacts, inputFilter, (bool)false);
        }
        else
        {
            fprintf(stderr, "Unsupported input filter tag: '%s'", argv[1]);
            return 3;
        }
    }
    else
    {
        printfContacts(contacts, contactsCount);
        return 0;
    }

    printfContacts(filteredContacts, filteredItemsCount);
        
    if (filteredItemsCount == 0)
    {
        printf("Not found\n");
    }
    
    return 0;
}

int readContacts(contact *contacts)
{
    for (int userIndex = 0; userIndex < contactsLimit; userIndex++)
    {
        char name[defaultSizeLimit], number[defaultSizeLimit];

        int scanfResult = scanf("%[^\n]\n%[^\n]\n", name, number); 
        if (scanfResult == EOF)
        {
            int contactsCount = userIndex; // no contact was added current iteration.
            return contactsCount;
        }
        
        bool isValid = isContactValidFormat(name, number);

        if (scanfResult != 2 || !isValid)
        {
            fprintf(stderr, "Invalid input format.\n");
            return 0;
        }

        contact newContact = contactCtor(name, number);
        contacts[userIndex] = newContact;
    }
    fprintf(stderr, "Unsupported contacts input lenght.");
    return 0;
}

bool isContactValidFormat(char name[], char number[])
{
    if (strlen(name) > 100 || strlen(number) > 100) return false;

    bool isNumberValid = true;
    for (int i = 0; i < (int)strlen(number); i++)
    {
        if (!isdigit((int)number[i]) || number[i] == '+')
            isNumberValid = false;
    }
    if (!isNumberValid) return false;  
    
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
        printf("%s, %s\n", contacts[i].string, contacts[i].number);
    }
}

bool isWithinKey(char item, char key)
{
    if (item == key) return true;
    
    int keyNumericValue = key - '0';

    char lower = (char)tolower(item);

    for (int i = 0; i < (int)strlen(tNine[keyNumericValue]); i++)
    {
        if (tNine[keyNumericValue][i] == lower) return true;
    }

    return false;
}

int filterContacts(contact *contacts, int contactsCount, contact *filteredContacts, char *filter, bool strictFiltration)
{
    int filteredCount = 0;

    for (int i = 0; i < contactsCount; i++)
    {
        contact c = contacts[i];

        bool stringMatch = isMatchingFilter(c.string, filter, strictFiltration);
        bool numberMatch = isMatchingFilter(c.number, filter, strictFiltration);

        if (stringMatch || numberMatch)
        {
            filteredContacts[filteredCount] = c;
            filteredCount++;
        }
    }
    
    return filteredCount;
}

bool isMatchingFilter(char *string, char *filter, bool strictFiltration)
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
            if (strictFiltration)
            {
                matchingCharacterCount = 0;
                filterIndex = 0;
                // TODO: comment functionality
                // Even though character is not 
                if (isWithinKey(string[i], filter[0]))
                {
                    matchingCharacterCount = 1;
                    filterIndex = 1;
                }
            }
        }

        if (matchingCharacterCount == filterLength) return true;
    }

    return false;
}

bool setValidInput(char input[], char consoleArgument[])
{
    for (int i = 0; i < (int)strlen(input); i++)
    {
        if (!isdigit(input[i])) 
        {
            fprintf(stderr, "Input filter was not in correct format.");
            return false;
        }
    }
    
    strcpy(input, consoleArgument);
    return true;
}