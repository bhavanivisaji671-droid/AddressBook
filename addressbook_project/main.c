#include <stdio.h>
#include "contact.h"
#include "file.h"
int main()
{
    int choice;
    AddressBook addressBook;
    //Load saved contacts when the program stars
    loadContactsFromFile(&addressBook);

    do
    {
        //Display Address book menu
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");

        //read uesr's choice
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //perform operation based on user's choice
        switch (choice)
        {
            case 1:
            //create a new contact
                createContact(&addressBook);
                break;

            case 2:
            //search for a contact
                searchContact(&addressBook);
                break;

            case 3:
            //edit an existing contact
                editContact(&addressBook);
                break;

            case 4:
            //delete an existing contact
                deleteContact(&addressBook);
                break;

            case 5:
            //Display all contacts
                listContacts(&addressBook);
                break;

            case 6:
            //save contacts before exiting
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;

            default:
            //handle invalid menu choice
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}