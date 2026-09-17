#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

/* Validate Name */
// Validate name using alphabets, spaces and dots
int validate_name(char *str)
{
    int i;

    // Check minimum length of name
    if (strlen(str) < 4)
        return 0;

        // Check every character of the name
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ' && str[i] != '.')
            return 0;
    }

    return 1;
}

/* Validate Phone */
// Validate phone number
int validate_phone(char *str)
{
    int i;

// Validate phone number length
    if (strlen(str) != 10)
        return 0;

// Check first digit is between 6 and 9
    if (str[0] < '6' || str[0] > '9')
        return 0;

// Check every character is a digit
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }

    return 1;
}

/* Validate Email */
// Validate email address
int validate_email(char *str)
{
    int i;
    int at = -1;
    int dot = -1;
    int atCount = 0;
    int len = strlen(str);

    // Find the @ symbol in the email
    for (i = 0; i < len; i++)
    {
        if (str[i] == '@')
        {
            at = i;
            atCount++;
        }
    }

    // Check that email contains only one @
    if (atCount != 1)
        return 0;

    // Check @ is not at the beginning or end
    if (at == 0 || at == len - 1)
        return 0;

    // Validate characters before @
    for (i = 0; i < at; i++)
    {
        if (!isalnum(str[i]) && str[i] != '.')
            return 0;
    }

    // Find dot after @
    for (i = at + 1; i < len; i++)
    {
        if (str[i] == '.')
        {
            dot = i;
            break;
        }
    }

    // Check dot position
    if (dot == -1 || dot == at + 1 || dot == len - 1)
        return 0;

        // Validate characters after @
    for (i = at + 1; i < len; i++)
    {
        if (!isalnum(str[i]) && str[i] != '.')
            return 0;
    }

    // Check that two dots are not together
    if (str[dot + 1] == '.')
        return 0;

        // Check that email extension contains only alphabets
    for (i = len - 1; i > dot; i--)
    {
        if (!isalpha(str[i]))
            return 0;
    }

    return 1;
}


/* Create Contact */
// Create a new contact
void createContact(AddressBook *addressBook)
{
    char str1[50];
    char str2[20];
    char str3[50];

    /* Name */
    do
    {
        // Read and validate name
        printf("Enter the name: ");
        scanf(" %[^\n]", str1);

        if (!validate_name(str1))
            printf("Invalid name. Enter only alphabets, spaces and dots.\n");

    } while (!validate_name(str1));


    /* Phone */
    // Read and validate phone number
    do
    {
        printf("Enter the phone number: ");
        scanf("%19s", str2);

        if (!validate_phone(str2))
            printf("Invalid phone number. Enter 10 digits starting from 6-9.\n");

    } while (!validate_phone(str2));


    /* Email */
    // Read and validate email
    do
    {
        printf("Enter the email: ");
        scanf("%49s", str3);

        if (!validate_email(str3))
            printf("Invalid email.\n");

    } while (!validate_email(str3));


    /* Store contact */
    // Store the contact details
    strcpy(addressBook->contacts[addressBook->contactCount].name, str1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str2);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str3);

    // Increase contact count
    addressBook->contactCount++;

    printf("Contact created successfully!\n");
}


/* List Contacts */
// Display all contacts
void listContacts(AddressBook *addressBook)
{
    int i;

    // Check whether contacts are available
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }

    printf("\n-------------------------------------------------------------\n");
    printf("S.No  Name                 Phone          Email\n");
    printf("-------------------------------------------------------------\n");
//Display each contact
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-14s %s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("-------------------------------------------------------------\n");
}


/* Search Contact */
// Search for a contact
void searchContact(AddressBook *addressBook)
{
    int choice;
    char search[50];
    int i;
    int found = 0;

    // Display search options
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Search contact by name
    if (choice == 1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", search);

        // Compare entered name with stored names
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, search) == 0)
            {
                printf("%s, %s, %s\n",
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    }
    // Search contact by phone
    else if (choice == 2)
    {
        printf("Enter phone: ");
        scanf("%s", search);

    // Compare entered phone with stored phone numbers
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                printf("%s, %s, %s\n",
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    }
    // Handle invalid search choice
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    // Display message when contact is not found
    if (!found)
        printf("Contact not found.\n");
}


/* Edit Contact */
// Edit an existing contact
void editContact(AddressBook *addressBook)
{
    int choice;
    int i;
    int found = -1;
    char search[50];
    char newName[50];
    char newPhone[20];
    char newEmail[50];

    // Display edit options
    printf("1. Edit by name\n");
    printf("2. Edit by phone\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    //Find contact by name
    if (choice == 1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", search);

        // Compare entered name with stored names
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, search) == 0)
            {
                found = i;
                break;
            }
        }
    }
    // Find contact by phone
    else if (choice == 2)
    {
        printf("Enter phone: ");
        scanf("%s", search);

    // Compare entered phone with stored phone numbers
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                found = i;
                break;
            }
        }
    }
    // Handle invalid edit choice
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    // Check whether contact was found
    if (found == -1)
    {
        printf("Contact not found.\n");
        return;
    }

    // Read and validate new name
    printf("Enter new name: ");
    scanf(" %[^\n]", newName);

    while (!validate_name(newName))
    {
        printf("Invalid name. Enter again: ");
        scanf(" %[^\n]", newName);
    }

    // Read and validate new phone
    printf("Enter new phone: ");
    scanf("%19s", newPhone);

    while (!validate_phone(newPhone))
    {
        printf("Invalid phone. Enter again: ");
        scanf("%19s", newPhone);
    }

    // Read and validate new email
    printf("Enter new email: ");
    scanf("%49s", newEmail);

    while (!validate_email(newEmail))
    {
        printf("Invalid email. Enter again: ");
        scanf("%49s", newEmail);
    }

    // Update contact details
    strcpy(addressBook->contacts[found].name, newName);
    strcpy(addressBook->contacts[found].phone, newPhone);
    strcpy(addressBook->contacts[found].email, newEmail);

    printf("Contact updated successfully!\n");
}


/* Delete Contact */
// Delete an existing contact
void deleteContact(AddressBook *addressBook)
{
    int choice;
    int i;
    int found = -1;
    char search[50];

    // Display delete options
    printf("1. Delete by name\n");
    printf("2. Delete by phone\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Find contact by name
    if (choice == 1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", search);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, search) == 0)
            {
                found = i;
                break;
            }
        }
    }
    // Find contact by phone
    else if (choice == 2)
    {
        printf("Enter phone: ");
        scanf("%s", search);

        // Compare entered phone with stored phone numbers
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                found = i;
                break;
            }
        }
    }
    // Handle invalid delete choice
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    // Check whether contact was found
    if (found == -1)
    {
        printf("Contact not found.\n");
        return;
    }

    // Shift contacts after deleting one contact
    for (i = found; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    // Decrease contact count
    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}