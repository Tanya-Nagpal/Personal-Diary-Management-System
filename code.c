#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void addRecord();
void viewRecord();
void editRecord();
void deleteRecord();
struct record
{
    char title[50];
    char date[10];
    char duration[12];
    char place[20];
    char time[8];
    char note[1000];
};
int main()
{
    int num;
    printf("*************************************************\n");
    printf("\t*Welcome To Your Personal Diary* \t\n\n");
    printf("*************************************************\n");
    while (1)
    {
        printf("\n\n\t\tMAIN MENU:\t\t");
        printf("\n\n\tAdd Diary\t[1]\n");
        printf("\tView Diary\t[2]\n");
        printf("\tEdit Diary\t[3]\n");
        printf("\tDelete record\t[4]\n");
        printf("\tEXIT\t\t[5]\n\n");
        printf("\tEnter Your Choice : ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            addRecord();
            break;
        case 2:
            viewRecord();
            break;
        case 3:
            editRecord();
            break;
        case 4:
            deleteRecord();
            break;
            exit(0);
        default:
            printf("You have entered wrong choice\n");
            printf("Press any key to try again\n");
            getch();
            break;
        }
        system("cls"); // system(“cls”) is used to make the screen/terminal clear.
    }
    return 0;
}
void addRecord()
{
    system("cls");
    FILE *fptr;
    struct record r;
    int choice;
    char another = 'Y', name[30], date[8], time[10], filename[30];
    printf("Enter your name :\n");
    scanf("%s", name);
    system("cls");
    printf("***********************************************\n");
    printf("\t\tWelcome!, %s\n\t\t\tAdd your Diary\n", name);
    printf("***********************************************\n\n");
    printf("Enter date of your record [dd-mm-yyyy] :\n");
    fflush(stdin);
    gets(filename);
    fptr = fopen(filename, "ab+");
    if (fptr == NULL)
    {
        fptr = fopen(filename, "wb+");
        if (fptr == NULL)
        {
            printf("\nSYSTEM ERROR...");
            printf("\nPRESS ANY KEY TO EXIT");
            getch();
            return;
        }
    }
    while (another == 'Y' || another == 'y')
    {
        choice = 0;
        fflush(stdin);
        printf("Enter date :\n");
        scanf("%s", date);
        rewind(fptr);
        while (fread(&r, sizeof(r), 1, fptr) == 1)
        {
            if (strcmp(r.date, date) == 0)
            {
                printf("DIARY ALREAY EXISTS...\n");
                choice = 1;
            }
        }
        if (choice == 0)
        {
            strcpy(r.date, date);
            printf("ENTER TITLE : \n");
            fflush(stdin);
            gets(r.title);
            printf("ENTER PLACE : \n");
            fflush(stdin);
            gets(r.place);
            printf("ENTER DURATION : \n");
            fflush(stdin);
            gets(r.duration);
            printf("ENTER NOTE : \n");
            fflush(stdin);
            gets(r.note);
            fwrite(&r, sizeof(r), 1, fptr);
            printf("YOUR FILE IS ADDED \n");
        }
        printf("\tADD ANOTHER RECORD...( Y/N )?\n");
        fflush(stdin);
        another = getchar();
    }
    fclose(fptr);
    printf("PRESS ANY KEY TO  EXIT.....\n\n");
    getch();
}
void viewRecord()
{
    FILE *fptr1;
    system("cls");
    struct record user;
    char time[10], choice, filename[30];
    int ch;
    printf("\t\t***************************************\n");
    printf("\t\t*HERE'S YOUR BEAUTIFUL DIARY*\n");
    printf("\t\t***************************************\n\n\n");
    do
    {
        // fflush(stdin);
        printf("\tENTER THE DATE OF RECORD TO BE VIEWED [dd-mm-yyyy] :");
        fflush(stdin);
        gets(filename);
        fptr1 = fopen(filename, "rb");
        if (fptr1 == NULL)
        {
            puts("THE RECORD DOESN'T EXIST.....\n");
            printf("PRESS ANY KEY TO EXIT...\n");
            getch();
            return;
        }
        else
        {
            system("cls");
            printf("THE WHOLE RECORD FOR %s IS :\n", filename);
            while (fread(&user, sizeof(user), 1, fptr1) == 1)
            {
                printf("\n");
                printf("\nTIME : %s\n", user.time);
                printf("\nMEETING WITH: %s", user.title);
                printf("\nMEETING AT: %s", user.place);
                printf("\nDURATION: %s", user.duration);
                printf("\nNOTE: %s", user.note);
                printf("\n");
            }
        }
        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N) ?");
        fflush(stdin);
        scanf("%c", &choice);

    } while (choice == 'Y' || choice == 'y');
    fclose(fptr1);
    return;
    fflush(stdin);
}
void editRecord()
{
    system("cls");
    FILE *fptr1;
    struct record user;
    char date[12], choice, filename[30];
    int num, count = 0;
    printf("\t***********************************************\n");
    printf("\t\t*EDIT YOUR BEAUTIFUL DIARY*\n");
    printf("\t***********************************************\n");
    do
    {
        printf("\nENTER THE DATE OF RECORD TO BE EDITED [DD-MM-YYYY] :\n");
        fflush(stdin);
        gets(filename);
        fptr1 = fopen(filename, "rb+");
        if (fptr1 == NULL)
        {
            printf("\nRECORD DOESN'T EXISTS :");
            printf("\nPRESS ANY KEY TO GO BACK");
            getch();
            return;
        }
        while (fread(&user, sizeof(user), 1, fptr1))
        {
            if (strcmp(user.date, date))
            {
                printf("\nYOUR OLD DIARY WAS AS:\n");
                printf("\nTIME : %s\n", user.time);
                printf("\nMEETING WITH: %s", user.title);
                printf("\nMEETING AT: %s", user.place);
                printf("\nDURATION: %s", user.duration);
                printf("\nNOTE: %s", user.note);
                printf("\n");
                printf("\n\tWHAT WOULD YOU LIKE TO EDIT...?\n");
                printf("1.TIME.\n");
                printf("2.Title.\n");
                printf("3.PLACE.\n");
                printf("4.DURATION.\n");
                printf("5.NOTE.\n");
                printf("6.WHOLE RECORD.\n");
                printf("7.GO BACK TO MAIN MENU.\n\n");
                do
                {
                    printf("ENTER YOUR CHOICE :\n");
                    fflush(stdin);
                    scanf("%d", &num);
                    fflush(stdin);
                    switch (num)
                    {
                    case 1:
                        printf("ENTER THE NEW DATA :\n");
                        printf("NEW TIME [HH:MM]\n");
                        gets(user.time);
                        break;
                    case 2:
                        printf("ENTER THE NEW DATA :\n");
                        printf("NEW TITLE :\n");
                        gets(user.title);
                        break;
                    case 3:
                        printf("ENTER THE NEW DATA :\n");
                        printf("NEW PLACE :\n");
                        gets(user.place);
                        break;
                    case 4:
                        printf("\nENTER THE NEW DATA:");
                        printf("\nDURATION:");
                        gets(user.duration);
                        break;
                    case 5:
                        printf("ENTER THE NEW DATA:");
                        printf("\nNOTE:");
                        gets(user.note);
                        break;
                    case 6:
                        printf("ENTER THE NEW DATA :\n");
                        printf("NEW TIME [HH:MM]\n");
                        gets(user.time);
                        printf("ENTER THE NEW DATA :\n");
                        printf("NEW tITLE :\n");
                        gets(user.title);
                        printf("ENTER THE NEW DATA :\n");
                        printf("NEW PLACE :\n");
                        gets(user.place);
                        printf("ENTER THE NEW DATA:\n");
                        printf("DURATION:\n");
                        gets(user.duration);
                        printf("ENTER THE NEW DATA:\n");
                        printf("NOTE:\n");
                        gets(user.note);
                        break;
                    case 7:
                        printf("PRESS ANY KEY TO GO BACK\n");
                        getch();
                        return;
                        break;
                    default:
                        printf("\nYOU TYPED SOMETHING ELSE...TRY AGAIN\n");
                        break;
                    }
                } while (num < 1 || num > 8);
                // fseek(FILE *stream, long int offset, int whence) sets the file position of the stream to the given offset.
                //  Parameters
                //      stream − This is the pointer to a FILE object that identifies the stream.
                //      offset − This is the number of bytes to offset from whence.
                //      whence − This is the position from where offset is added. It is specified by one of the following constants
                /*Sr.No.-------------------Constant & Description

                SEEK_SET                   Beginning of file

                SEEK_CUR                   Current position of the file pointer

                SEEK_END                   End of file*/

                fseek(fptr1, -sizeof(user), SEEK_CUR);
                fwrite(&user, sizeof(user), 1, fptr1);
                fseek(fptr1, -sizeof(user), SEEK_CUR);
                fwrite(&user, sizeof(user), 1, fptr1);
                num = 5;
                break;
            }
        }
        if (num == 5)
        {
            system("cls");
            printf("\n\t\tEDITNG COMPLETED...\n");
            printf("-----------------------\n");
            printf("THE NEW RECORD IS :\n");
            printf("-----------------------\n");
            printf("\nTIME : %s\n", user.time);
            printf("NAME :%s\n", user.title);
            printf("PLACE : %s\n", user.place);
            printf("DURATION: %s", user.duration);
            printf("NOTE : %s\n", user.note);
            fclose(fptr1);
            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD...(Y/N)?\n");
            scanf("%c", &num);
            count++;
        }
        else
        {
            printf("\nTHE RECORD DOES NOT EXIST:\n");
            printf("\nWOULD YOU LIKE TO TRY AGAIN...(Y/N)\n");
            scanf("%c", &num);
        }

    } while (num == 'Y' || num == 'y');
    fclose(fptr1);
    if (count == 1)
    {
        printf("%d FILE IS EDITED...\n", count);
    }
    else if (count > 1)
    {
        printf("%d FILES ARE EDITED...\n", count);
    }
    else
    {
        printf("\nNO FILES EDITED...\n");
    }
    printf("\tPRESS ENTER TO EXIT EDITING MENU.");
    getch();
}

void deleteRecord()
{
    system("cls");
    FILE *fptr, *fp;
    struct record delfile;
    char filename[20], another = 'Y', time[10];

    int choice, check;
    printf("\n\n\t\t******************************************\n");
    printf("\t\t*DELETE YOUR DIARY*\n");
    printf("\n\t\t****************************************\n\n");
    while (another = 'Y')
    {
        printf("\n\n#DELETE WHOLE RECORD\t\t\t\t");
        do
        {
            printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");
            fflush(stdin);
            gets(filename);
            fp = fopen(filename, "wb");
            if (fptr == NULL)
            {
                printf("\nTHIS FILE DOESN'T EXISTS");
                printf("\nPRESS ANY KEY TO GO BACK.");
                getch();
                return;
            }
            fclose(fptr);
            remove(filename);
            printf("\nDELETED SUCCESSFUL...");
        } while (1);
        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");
        fflush(stdin);
        scanf("%c", &another);
    }
    printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();
}
