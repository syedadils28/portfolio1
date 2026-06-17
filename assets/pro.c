#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct person
{
    char name[35];
    char address[50];
    char father_name[35];
    char mother_name[30];
    char mble_no[15]; // changed to string
    char sex[8];
    char mail[100];
    char citizen_no[20];
};

void menu();
void get_input(char *buffer, int size);
void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();
int is_valid_phone(char *phone);
int is_valid_email(char *email);

int main()
{
    menu();
    return 0;
}

void menu()
{
    int choice;

    while (1)
    {
        printf("\n********** WELCOME TO PHONEBOOK *************\n");
        printf("1. Add New\n");
        printf("2. List\n");
        printf("3. Exit\n");
        printf("4. Modify\n");
        printf("5. Search\n");
        printf("6. Delete\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        getchar();

        switch (choice)
        {
        case 1:
            addrecord();
            break;
        case 2:
            listrecord();
            break;
        case 3:
            exit(0);
        case 4:
            modifyrecord();
            break;
        case 5:
            searchrecord();
            break;
        case 6:
            deleterecord();
            break;
        default:
            printf("Invalid choice!\n");
        }
    }
}

int is_valid_phone(char *phone)
{
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(phone[i]))
            return 0;
    }
    return 1;
}

int is_valid_email(char *email)
{
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');

    if (at && dot && at < dot)
        return 1;
    return 0;
}

void addrecord()
{
    FILE *f;
    struct person p;

    f = fopen("project.dat", "ab+");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name: ");
    get_input(p.name, sizeof(p.name));

    printf("Enter address: ");
    get_input(p.address, sizeof(p.address));

    printf("Enter father name: ");
    get_input(p.father_name, sizeof(p.father_name));

    printf("Enter mother name: ");
    get_input(p.mother_name, sizeof(p.mother_name));

    do
    {
        printf("Enter phone no. (10 digits): ");
        get_input(p.mble_no, sizeof(p.mble_no));

        if (!is_valid_phone(p.mble_no))
            printf("Error: Phone must be exactly 10 digits.\n");

    } while (!is_valid_phone(p.mble_no));

    printf("Enter sex: ");
    get_input(p.sex, sizeof(p.sex));

    do
    {
        printf("Enter e-mail: ");
        get_input(p.mail, sizeof(p.mail));

        if (!is_valid_email(p.mail))
            printf("Error: Invalid email format.\n");

    } while (!is_valid_email(p.mail));

    printf("Enter citizen no: ");
    get_input(p.citizen_no, sizeof(p.citizen_no));

    fwrite(&p, sizeof(p), 1, f);
    fclose(f);

    printf("\nRecord saved successfully.\n");
}

void listrecord()
{
    struct person p;
    FILE *f;
    int count = 0;

    f = fopen("project.dat", "rb");
    if (f == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        count++;
        printf("\n--- Record #%d ---\n", count);
        printf("Name        : %s\n", p.name);
        printf("Address     : %s\n", p.address);
        printf("Father Name : %s\n", p.father_name);
        printf("Mother Name : %s\n", p.mother_name);
        printf("Mobile      : %s\n", p.mble_no);
        printf("Sex         : %s\n", p.sex);
        printf("Email       : %s\n", p.mail);
        printf("Citizen No  : %s\n", p.citizen_no);
    }

    if (count == 0)
        printf("\nNo records found.\n");

    fclose(f);
}

void searchrecord()
{
    struct person p;
    FILE *f;
    char name[35];
    int found = 0;

    f = fopen("project.dat", "rb");
    if (f == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter name to search: ");
    get_input(name, sizeof(name));

    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        if (strcmp(p.name, name) == 0)
        {
            printf("\nRecord Found:\n");
            printf("Name   : %s\n", p.name);
            printf("Mobile : %s\n", p.mble_no);
            printf("Email  : %s\n", p.mail);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");

    fclose(f);
}

void deleterecord()
{
    struct person p;
    FILE *f, *ft;
    char name[35];
    int found = 0;

    f = fopen("project.dat", "rb");
    if (f == NULL)
    {
        printf("No records found.\n");
        return;
    }

    ft = fopen("temp.dat", "wb");

    printf("Enter name to delete: ");
    get_input(name, sizeof(name));

    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        if (strcmp(p.name, name) != 0)
        {
            fwrite(&p, sizeof(p), 1, ft);
        }
        else
        {
            found = 1;
        }
    }

    fclose(f);
    fclose(ft);

    if (found)
    {
        remove("project.dat");
        rename("temp.dat", "project.dat");
        printf("Record deleted successfully.\n");
    }
    else
    {
        remove("temp.dat");
        printf("Record not found.\n");
    }
}

void modifyrecord()
{
    struct person p;
    FILE *f;
    char name[35];
    int found = 0;

    f = fopen("project.dat", "rb+");
    if (f == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter name to modify: ");
    get_input(name, sizeof(name));

    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        if (strcmp(p.name, name) == 0)
        {

            printf("Enter new address: ");
            get_input(p.address, sizeof(p.address));

            do
            {
                printf("Enter new phone (10 digits): ");
                get_input(p.mble_no, sizeof(p.mble_no));

            } while (!is_valid_phone(p.mble_no));

            do
            {
                printf("Enter new email: ");
                get_input(p.mail, sizeof(p.mail));

            } while (!is_valid_email(p.mail));

            fseek(f, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, f);

            printf("Record updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");

    fclose(f);
}

void get_input(char *buffer, int size)
{
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}