#include <stdio.h>
#include "file.h"

//save all contacts to the file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    int i;

    //open the contacts files for writing
    fp = fopen("contacts.txt", "w");

    //check whether the filr was opened successfully
    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    //save the total number of contacts
    fprintf(fp, "%d\n", addressBook->contactCount);

    //save each contact's details
    for (i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s\n", addressBook->contacts[i].name);
        fprintf(fp, "%s\n", addressBook->contacts[i].phone);
        fprintf(fp, "%s\n", addressBook->contacts[i].email);
    }

    //close the file after saving
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;
    int i;

    // Open the contacts file for reading
    fp = fopen("contacts.txt", "r");

    // If the file does not exist, start with an empty address book
    if (fp == NULL)
    {
        addressBook->contactCount = 0;
        return;
    }

    // Read the total number of contacts
    fscanf(fp, "%d\n", &addressBook->contactCount);

    // Read each contact's details
    for (i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, " %[^\n]", addressBook->contacts[i].name);
        fscanf(fp, "%s", addressBook->contacts[i].phone);
        fscanf(fp, "%s", addressBook->contacts[i].email);
    }

     // Close the file after loading
    fclose(fp);
}