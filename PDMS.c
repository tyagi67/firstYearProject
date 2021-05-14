//Personal Diary Management System (PASSWORD PROTECTED, pass - hello)
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

void add_record();
void view_record();
void delete_record();

struct record
{
    char time[6];
    char name[30];
    char place[25];
    char note[100];
};

int main()

{

	char pass[6]="hello",enter_pass[6];                //default password - hello

	int z,ch;

	printf("\nPlease Enter password To access the SOFTWARE:: ");         //password checker
	gets(enter_pass);
	z = strcmp(pass,enter_pass);

	if(z==0)
	{
		printf("\nACCESS GRANTED !\n");

    while(1)
    {
		printf("\n\t    | PERSONAL DIARY |\n");                         //main menu
    	printf("\t--------------------------\n");
        printf("\n\tMAIN MENU:\n");
        printf("\n\t1. ADD RECORD\t");
        printf("\n\t2. VIEW RECORD\t");
        printf("\n\t3. DELETE RECORD\t");
        printf("\n\t4. EXIT\t\t");
        printf("\n\n\tENTER YOUR CHOICE: ");
        scanf("%d",&ch);

        switch(ch)
        {

        case 1:

            add_record();                        //function call to add record
            break;

        case 2:

            view_record();                      //function call to view record
            break;

        case 3:

            delete_record();                    //function call to delete record
            break;

        case 4:

            printf("\n\n\tThanks for using ! ");

            getch();

            exit(0);

        default:

            printf("\nYOU ENTERED WRONG CHOICE..");

            printf("\nPRESS ANY KEY TO TRY AGAIN");

            getch();

            break;

        }

        system("cls");

    }

	}

	else
	{
		printf("\nACCESS DENIED\n\nExiting.............\n");
		getch();
	}

    return 0;

}

void add_record()
{

	system("cls");

	FILE *fp;

	struct record e;
	char filename[15] , time[6] , another = 'Y';
	int choice;

	printf("Welcome to add menu.\n\n");
	printf("\tEnter Date [dd-mm-yyyy]:    ");

	fflush(stdin);

	gets(filename);

	fp = fopen (filename, "ab+" ) ;

	if ( fp == NULL )

    {

        fp=fopen(filename,"wb+");

        if(fp==NULL)

        {

            printf("\nError OCCOURED..   \n Press any key to exit.");

            getch();

            return ;

        }

    }

    while ( another == 'Y' || another=='y' )

    {

        choice=0;

        fflush(stdin);

        printf ( "\tEnter Time [hh:mm]:         ");
        scanf("%s",time);

        rewind(fp);

        while(fread(&e,sizeof(e),1,fp)==1)

        {

            if(strcmp(e.time,time)==0)

            {

                printf("\n\tTHE RECORD ALREADY EXISTS.\n");

                choice=1;

            }

        }

        if(choice==0)

        {

            strcpy(e.time,time);

            printf("\tEnter Name:                 ");

            fflush(stdin);

			gets(e.name);

			fflush(stdin);

            printf("\tEnter Place:                ");

			gets(e.place);

			fflush(stdin);

            printf("\tNote:                       ");
            gets(e.note);

            fwrite(&e,sizeof(e),1,fp);

            printf("\nRecord Added..\n");

        }

        printf ( "\n\tAdd Another Record...(Y/N) " ) ;

        fflush(stdin);

        another = getchar( ) ;

    }

    fclose(fp);

    printf("\n\n\tPress any key to exit..");

    getch();

}

void view_record()
{
	FILE *fpve ;

    system("cls");

    struct record customer ;
    char time[6] , choice , filename[14];
    int ch;

    printf(" HERE IS THE VIEWING MENU \n");

    do
    {

        printf("\n\tEnter date of record to be viewed [dd-mm-yyyy]: ");

        fflush(stdin);

        gets(filename);

        fpve = fopen ( filename, "rb" ) ;

        if ( fpve == NULL )

        {

            puts ( "\n\n\tRecord does not exist..   Press any key to exit.." ) ;

            getch();

            return ;

        }

        system("cls");

        printf("\n\tHOW WOULD YOU LIKE TO VIEW:\n");

        printf("\n\t1. Whole record of the day ?");

        printf("\n\t2. Record of fixed time ?");

        printf("\n\n\tEnter choice: ");

        scanf("%d",&ch);

        switch(ch)

        {

        case 1:

            printf("\nThe whole record for %s is.. ",filename);

            while(fread(&customer,sizeof(customer),1,fpve)==1)

            {

                printf("\n");

                printf("\nTime:     %s",customer.time);

                printf("\nName:     %s",customer.name);

                printf("\nAt:       %s",customer.place);

                printf("\nNote:     %s",customer.note);

                printf("\n");

            }

            break;

        case 2:

        	fflush(stdin);

            printf("\nEnter time [hh:mm]: ");
            gets(time);

            while(fread(&customer,sizeof(customer),1,fpve)==1)

            {

                if(strcmp(customer.time,time)==0)

                {

                    printf("\nYour record is.. \n");

                    printf("\nTime:     %s",customer.time);

                    printf("\nName:     %s",customer.name);

                    printf("\nAt:       %s",customer.place);

                    printf("\nNote:     %s",customer.note);

                }

            }

            break;

        default:
            printf("\nYou typed someting else..\n");

            break;

        }

        printf("\n\nContinue viewing ? (Y/N): ");

        fflush(stdin);

        scanf("%c",&choice);

    }
    while(choice=='Y' || choice=='y');

    fclose(fpve);

    return;

}

void delete_record()
{
	system("cls");

    FILE *fp,*fptr;

    struct record file;
    char filename[15],another = 'Y' ,time[10];
    int choice;

    printf("WELCOME TO DELETE MENU ");

    while ( another == 'Y'||another == 'y' )

    {

        printf("\n\n\tHow would you like to delete.\n");

        printf("\n\t1. Delete whole Record ?");

        printf("\n\t2. Delete a particular record by time ?\t");

            printf("\n\n\tEnter choice: ");
            scanf("%d",&choice);

            switch(choice)

            {

            case 1:

                printf("\n\tEnter date of record to be deleted [dd-mm-yyyy]: ");

                fflush(stdin);

                gets(filename);

                fp=fopen(filename,"wb");

                if ( fp == NULL )

                {

                    printf("\nFile does not EXIST..   Press any key to go back..");

                    getch();

                    return ;

                }

                fclose(fp);

                remove(filename);

                printf("\nDELETED SUCCESFULLY...");

                break;

            case 2:

                printf("\n\tEnter date of record [dd-mm-yyyy]: ");

                fflush(stdin);

                gets(filename);

                fp = fopen (filename, "rb" ) ;

                if ( fp == NULL )

                {

                    printf("\nFile does not exist..   Press any key to go back !");

                    getch();

                    return ;

                }

                fptr=fopen("temp","wb");

                if(fptr==NULL)

                {

                    printf("\nSystem ERROR..     Press any key to go back ! ");

                    getch();

                    return ;

                }

                printf("\n\tEnter the time of the record to be deleted [hh:mm]: ");

                fflush(stdin);

                gets(time);

                while(fread(&file,sizeof(file),1,fp)==1)

                {

                    if(strcmp(file.time,time)!=0)

                        fwrite(&file,sizeof(file),1,fptr);

                }

                fclose(fp);

                fclose(fptr);

                remove(filename);

                rename("temp",filename);

                printf("\nSuccessfully Deleted..");

                break;

            default:

                printf("\n\tWrong choice entered.");

                break;

            }

        printf("\n\tDo you want to delete more records ? (Y/N): ");

        fflush(stdin);

        scanf("%c",&another);

    }

    printf("\n\n\tPRESS ANY KEY TO EXIT...");

    getch();

}

