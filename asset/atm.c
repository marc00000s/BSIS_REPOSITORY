#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define DATAFILE "D:\\data.txt"
#define PINDIR "D:\\"
#define DELIMITER "|"

typedef struct User
{
    char acc_number[50];
    char name[50];
    char bday[50];
    char contact[50];
    double balance; // min of 5000 for new account
    char pin[8];
} Record;

typedef struct List
{
    Record person[MAX];
    int last;
} List;

List L;

Record user;
Record user2;

char pin[8];
char acc_number[50];

void login()
{
    memset(pin, 0, sizeof(pin));
    system("cls");
    printf("\n\n\t\t ENTER YOUR ACCOUNT NUMBER: ");
    scanf("%s", &acc_number);
    printf("\t\t ENTER YOUR PINCODE: ");
    int index = 0;
    char ch;
    while ((ch = getch()) != 13 && index < 5)
    {
        if (index < 0)
        {
            index = 0;
        }

        if (ch == 8)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }

        if (isdigit(ch))
        {
            pin[index++] = ch;
            putch('*');
        }
    }
    pin[index++] = '\0';
    printf("\n");

    // get the index of the account number
    index = -1;
    for (int i = 0; i <= L.last; i++)
    {
        if (strcmp(L.person[i].acc_number, acc_number) == 0)
        {
            index = i;
            break;
        }
    }

    // if account number is not found
    if (index == -1)
    {
        printf("\n\n\t\t INCORRECT ACCOUNT NUMBER.\n\n");
        system("pause");
        return;
    }

    // check if pin is correct
    if (strcmp(L.person[index].pin, pin) != 0)
    {
        printf("\n\n\t\tINCORRECT PIN. \n\n");
        return;
    }

    user = L.person[index];
    system("pause");
}

void encrypt()
{
    int i = 0;
    while (pin[i] != '\0')
    {
        pin[i] = pin[i] + 77;
        i++;
    }
}

void decrypt()
{
    int i = 0;
    while (pin[i] != '\0')
    {
        pin[i] = pin[i] - 77;
        i++;
    }
}

void insertcard()
{
    FILE *fp;
    do
    {
        system("cls");
        printf("\n\n\t\t PLEASE INSERT CARD...");
        fp = fopen(DATAFILE, "r");
        usleep(500);
    } while (fp == NULL);
    fclose(fp);
    login();
}

void removecard()
{
    FILE *fp;
    do
    {
        system("cls");
        printf("\n\n\t\tPLEASE REMOVE CARD...");
        fp = fopen("D:atm.txt", "r");
    } while (fp != NULL);
    fclose(fp);
    printf("\n\n\t\t THANKYOU FOR BANKING WITH US \n\n");
}

void makenull()
{
    L.last = -1;
}

int isEmpty()
{
    return (L.last == -1);
}

int isFull()
{
    return (L.last == MAX - 1);
}

void add(Record r)
{
    if (isFull())
    {
        printf("\n\n\t\t LIST IS FULL.\n");
        system("pause");
    }
    else
    {
        L.last++;
        L.person[L.last] = r;
    }
}

void retrieve()
{
    // reset the list
    makenull();

    // open file
    FILE *fp = fopen(DATAFILE, "r");

    // if file exists, read and store data
    if (fp != NULL)
    {
        // read data from file line by line and use delimiter to separate data
        char line[1024];
        while (fgets(line, 1024, fp))
        {
            // create a new record
            Record newRecord;

            // get the first token
            char *token = strtok(line, DELIMITER);

            // walk through other tokens
            int i = 0;
            while (token != NULL)
            {
                switch (i)
                {
                case 0:
                    strcpy(newRecord.acc_number, token);
                    break;
                case 1:
                    strcpy(newRecord.name, token);
                    break;
                case 2:
                    strcpy(newRecord.bday, token);
                    break;
                case 3:
                    strcpy(newRecord.contact, token);
                    break;
                case 4:
                    newRecord.balance = atof(token);
                    break;
                case 5:
                    strcpy(pin, token);
                    decrypt();
                    strcpy(newRecord.pin, pin);
                    break;
                }

                token = strtok(NULL, DELIMITER);
                i++;
            }

            // add the new record to the list
            add(newRecord);
        }
    }

    // empty pin
    strcpy(pin, "");
}

void save()
{
    // open file, create, overwrite
    FILE *fp = fopen(DATAFILE, "w");
    Record r;
    for (int i = 0; i <= L.last; i++)
    {
        r = L.person[i];
        strcpy(pin, r.pin);
        encrypt();
        strcpy(r.pin, pin);
        fprintf(fp, "%s|%s|%s|%s|%.2f|%s|\n", r.acc_number, r.name, r.bday, r.contact, r.balance, r.pin);
    }
    fclose(fp);
}

void balanceInquiry()
{
    system("cls");
    printf("\n\n\t\t HI! [ %s ] YOUR CURRENTLY BALANCE IS [ %.2fphp ]\n\n",user.name ,user.balance);
    system("pause");
}

void withdraw()
{
    system("cls");
    double amount;
    printf("\n\n\t\t ENTER AMOUNT TO WITHDAW: ");
    scanf("%lf", &amount);
    if (amount > user.balance)
    {
        printf("\n\n\t\t INSUFFICIENT BALANCE. PLEASE TRY AGAIN.\n\n");
        system("pause");
    }
    else
    {
        user.balance -= amount;
        for (int i = 0; i <= L.last; i++)
        {
            if (strcmp(L.person[i].acc_number, user.acc_number) == 0)
            {
                L.person[i] = user;
                break;
            }
        }
        save();

        printf("\n\n\t\t HI [ %s ] YOUR WITHRAW OF [ %.2lfphp ] IS SUCCESSFUL!\n\n",user.name ,amount);
        system("pause");
    }
}

void deposit()
{
    system("cls");
    double amount;
    printf("\n\n\t\tENTER AMOUNT TO DEPOSIT: ");
    scanf("%lf", &amount);
    user.balance += amount;
    for (int i = 0; i <= L.last; i++)
    {
        if (strcmp(L.person[i].acc_number, user.acc_number) == 0)
        {
            L.person[i] = user;
            break;
        }
    }
    save();

    printf("\n\n\t\t HI [ %s ] YOUR DEPOSIT OF [ %.2lfphp ] IS SUCCESSFUL!\n\n",user.name ,amount);
    system("pause");
}

void fundTransfer()
{
    system("cls");
    char acc_number[20];
    double amount;
    printf("\n\n\t\t ENTER ACCOUNT NUMBER TO TRANSFER: ");
    scanf("%s", &acc_number);
    printf("\t\t ENTER AMOUNT TO TRANSFER: ");
    scanf("%lf", &amount);
    if (amount > user.balance)
    {
        printf("\n\n\t\t INSUFFICIENT BALANCE. PLEASE TRY AGAIN.\n\n");
        system("pause");
    }
    else
    {
        int index = -1;
        for (int i = 0; i <= L.last; i++)
        {
            if (strcmp(L.person[i].acc_number, acc_number) == 0 && strcmp(L.person[i].acc_number, user.acc_number) != 0)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            printf("\n\n\t\tACCOUNT NUMBER DOESNT EXIST. PLEASE TRY AGAIN.\n");
            system("pause");
        }
        else
        {
            user.balance -= amount;
            L.person[index].balance += amount;
            for (int i = 0; i <= L.last; i++)
            {
                if (strcmp(L.person[i].acc_number, user.acc_number) == 0)
                {
                    L.person[i] = user;
                    break;
                }
            }
            save();

            printf("\n\n\t\t HI [ %s ] YOUR TRANSFER OF [ %.2lfphp ] FUNDS TO [ %s ] IS SUCCESSFUL!\n\n",user.name ,amount ,acc_number);
            system("pause");
        }
    }
}



void registration()
{
    system("cls");
    Record newRecord;
    printf("\n\n\t\tREGISTER ACCOUNT NUMBER: ");
    scanf("%s", &newRecord.acc_number);
    printf("\t\tENTER NAME: ");
    // fix issue with scanf can input with space
    fflush(stdin);
    gets(newRecord.name);
    printf("\t\tENTER BITHDAY: ");
    scanf("%s", &newRecord.bday);
    printf("\t\tENTER CONTACT NUMBER: ");
    scanf("%s", &newRecord.contact);
    printf("\t\tENTER INITIAL BALANCE: ");
    scanf("%lf", &newRecord.balance);
    printf("\t\tENTER PINCODE: ");
    scanf("%s", &newRecord.pin);
    if (newRecord.balance < 5000)
    {
        printf("\n\n\t[ MINIMUM BALANCE SHOUDL BE 5000php. PLEASE TRY AGAIN. ]\n");
        system("pause");
        registration();
    }
    else
    {
        add(newRecord);
        save();

        // create pin file acc_num + pin .code in PINDIR
        char pinfile[50];
        strcpy(pinfile, PINDIR);
        strcat(pinfile, newRecord.acc_number);
        strcat(pinfile, newRecord.pin);
        strcat(pinfile, ".code");
        FILE *fp = fopen(pinfile, "w");
        fclose(fp);

        printf("\n\n\t\t [ ACCOUNT IS NOW REGISTERED! ]\n\n");
        system("pause");
    }
}

void changePin()
{
    system("cls");
    char newpin[10];
    char pinfile[50];
    strcpy(pinfile, PINDIR);
    strcat(pinfile, user.acc_number);
    strcat(pinfile, user.pin);
    strcat(pinfile, ".code");

    printf("\n\n\t\t CREATE NEW PINCODE: ");
    scanf("%s", &newpin);
    strcpy(user.pin, newpin);
    for (int i = 0; i <= L.last; i++)
    {
        if (strcmp(L.person[i].acc_number, user.acc_number) == 0)
        {
            L.person[i] = user;
            break;
        }
    }
    save();

    // delete old pin file
    remove(pinfile);

    // save pin file acc_num + pin .code in PINDIR
    strcpy(pinfile, PINDIR);
    strcat(pinfile, user.acc_number);
    strcat(pinfile, user.pin);
    strcat(pinfile, ".code");
    FILE *fp = fopen(pinfile, "w");
    fclose(fp);

    printf("\t\t PINCODE CHANGE SUCCESSFULLY!\n");
    system("pause");
}

void transaction()
{
    insertcard();

    // if has no user, return
    if (user.acc_number[0] == '\0')
    {
        return;
    }

    system("cls");
    int choice;
    // choices: balance inquiry, withdraw, deposit, Fund transfer, change pin, exit
    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");

        printf("\n\t\t\t\t\t WELCOME TO OUR BANK  [ %s! ]             \n", user.name);

        printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");

        printf("\n\n\t\t1. BALANCE INQUIRY\n");
        printf("\t\t2. WITHRAW\n");
        printf("\t\t3. DEPOSIT\n");
        printf("\t\t4. FUND TRANSFER\n");
        printf("\t\t5. CHANGE PINCODE\n");
        printf("\t\t6. EXIT\n");
        printf("\t\t   SELECT YOUR CHOICE: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            balanceInquiry();
            break;
        case 2:
            withdraw();
            break;
        case 3:
            deposit();
            break;
        case 4:
            fundTransfer();
            break;
        case 5:
            changePin();
            break;
        case 6:
            printf("\n\n\t\t THANKYOU FOR BANKING WITH US! \n\n");
            break;
        default:
            printf("\n\n\t\t INVALID CHOICE. PLEASE TRY AGAIN.\n\n");
            system("pause");
        }
    } while (choice != 6);
}

int main()
{
    retrieve();
    int choice;

    // choices: registration, transaction, exit
    system("cls");
    printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    printf("\n\t\t\t\t\t\xdb\xdb                            \xdb\xdb");
    printf("\n\t\t\t\t\t\xdb\xdb    WELCOME TO OUR BANK!    \xdb\xdb");
    printf("\n\t\t\t\t\t\xdb\xdb                            \xdb\xdb");
     printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    printf("\n\n\t\t 1. REGISTRATION");
    printf("\n\t\t 2. TRANSACTION");
    printf("\n\t\t 3. EXIT");
    printf("\n\t\t    SELECT YOUR CHOICE: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        registration();
        break;
    case 2:
        transaction();
        break;
    case 3:
        printf("\n\n\t\t THANKYOU FOR BANKING WITH US! \n\n");
        break;
    default:
        printf("\n\n\t\t INVALID CHOICE. PLEASE TRY AGAIN.\n\n");
    }
}
