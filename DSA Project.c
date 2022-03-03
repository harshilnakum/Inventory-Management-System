#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
int fill = -1; //Maintains the count of data that is filled
struct inventory
{

    int computerID;
    int DOP;
    int DOM;
    int warrantyperiod;
    int processor;
    int ROD;
};
struct inventory s[100];
void insert();
void delete ();
void display();
void bsortDesc();
void isEmpty();
void isFull();
void updateProcessor();
void search_and_display();
void number_of_comps();
void longestROD();
struct Date
{
    int d, m, y;
};

// To store number of days in
// all months from January to Dec.
const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

// This function counts number of
// leap years before the given date
int countLeapYears(struct Date d)
{
    int years = d.y;

    // Check if the current year needs to be
    //  considered for the count of leap years
    // or not
    if (d.m <= 2)
        years--;

    // An year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
    // multiple of 100.
    return years / 4 - years / 100 + years / 400;
}

// This function returns number of
// days between two given dates
int getDifference(struct Date dt1, struct Date dt2)
{
    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1'

    // initialize count using years and day
    long int n1 = dt1.y * 365 + dt1.d;

    // Add days for months in given date
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1);

    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2'

    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    // return difference between two counts
    return abs(n2 - n1);
}

int main()
{
    while (1)
    {
        system("cls");
        printf("Enter the operation number that you want to conduct:\n");
        printf("1) insert or update\n2) delete\n3) search and display specific\n4) number of comps\n5) update processor\n6) display\n7) isEmpty\n8) isFull\n9) logest return off period\n10) exit \n\n");
        int ch;
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            insert();
            break;
        case 2:
            delete ();
            break;
        case 3:
            search_and_display();
            break;

        case 4:
            number_of_comps();
            break;
        case 5:
            updateProcessor();
            break;
        case 6:
            display();
            break;
        case 7:
            isEmpty();
            break;
        case 8:
            isFull();
            break;
        case 9:
            longestROD();
            break;
        case 10:
            exit(0);
        default:
            printf("Please select the correct choice.\n");
            break;
        }
    }
    return 0;
}
void insert()
{
    if (fill == 99)
    {
        printf("The list is full, no other entry is possible!!!\n");
    }
    else
    {
        int id, index = -1;
        int flag = 0;
        printf("Enter the computer id : \n");
        scanf("%d", &id);
        for (int i = 0; i <= fill; ++i)
        {
            if (id == s[i].computerID)
            {
                flag = 1;
                index = i;
                break;
            }
        }
        if (flag == 1)
        {
            printf("Such a computer code already exists. Now updating that entry.\n");
            printf("Enter the date of purchase (DDMMYYYY):\n");
            scanf("%d", &s[index].DOP);
            printf("Enter the date of manufacture (DDMMYYYY):\n");
            scanf("%d", &s[index].DOM);
            printf("Enter the date of return (DDMMYYYY):\n");
            scanf("%d", &s[index].ROD);
            printf("Enter the warranty period in years:\n");
            scanf("%d", &s[index].warrantyperiod);
            printf("Enter the processor generation(13 or 15 or 17):\n");
            scanf("%d", &s[index].processor);
        }
        else
        {
            printf("Creating new entry...\n");
            s[fill + 1].computerID = id;
            printf("Enter the date of purchase (DDMMYYYY):\n");
            scanf("%d", &s[fill + 1].DOP);
            printf("Enter the date of manufacture (DDMMYYYY):\n");
            scanf("%d", &s[fill + 1].DOM);
            printf("Enter the date of return (DDMMYYYY):\n");
            scanf("%d", &s[fill + 1].ROD);
            printf("Enter the warranty period in years:\n");
            scanf("%d", &s[fill + 1].warrantyperiod);
            printf("Enter the processor generation(13 or 15 or 17):\n");
            scanf("%d", &s[fill + 1].processor);
            ++fill;
        }
        printf("Update/Insertion successfull.\n");
    }
    bsortDesc();
    printf("Press any key to continue.\n");
    getch();
}
void delete ()
{
    int id, index = -1;
    printf("Enter the computer id to be deleted : \n");
    scanf("%d", &id);
    for (int i = 0; i <= fill; ++i)
    {
        if (id == s[i].computerID)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Such a computer entry doesn't exist! Operation failed...\n");
    }
    else
    {
        for (int i = index; i <= fill - 1; ++i)
        {
            s[i] = s[i + 1];
        }
        --fill;
        printf("Operation Successfull!\n");
    }
    bsortDesc();
    printf("Press any key to continue...\n");
    getch();
}

void display()
{
    int i;
    printf("The size of inventory is: %d", fill + 1);
    printf("\n");
    for (i = 0; i <= fill; i++)
    {
        printf("------------------------------------------\n");
        printf("Computer ID: %d\n", s[i].computerID);
        printf("Date of Purchace: %d\n", s[i].DOP);
        printf("Date of Manufacture: %d\n", s[i].DOM);
        printf("Warranty Period: %d\n", s[i].warrantyperiod);
        printf("Processor: %d\n", s[i].processor);
        printf("Return off date: %d\n", s[i].ROD);
    }
    printf("Press any key to continue.\n");
    getch();
}

void bsortDesc()
{
    int i, j;
    int se = fill + 1;
    struct inventory temp;
    for (i = 0; i < se - 1; i++)
    {
        for (j = 0; j < (se - 1 - i); j++)
        {
            if (s[j].computerID > s[j + 1].computerID)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

void isEmpty()
{
    if (fill == -1)
    {
        printf("The inventory is Empty!!!\n");
    }
    else
    {
        printf("The inventory is NOT Empty!!!\n");
    }
    printf("Press any key to continue.\n");
    getch();
}

void isFull()
{
    if (fill == 99)
    {
        printf("The inventory is Full!!!\n");
    }
    else
    {
        printf("The inventory is NOT Full!!!\n");
    }
    printf("Press any key to continue.\n");
    getch();
}

void updateProcessor()
{
    int id, index = -1;
    int flag = 0;
    printf("Enter the computer id whose processor needs to be updated: \n");
    scanf("%d", &id);
    for (int i = 0; i <= fill; ++i)
    {
        if (id == s[i].computerID)
        {
            flag = 1;
            index = i;
            break;
        }
    }
    if (flag == 1)
    {
        int de;
        printf("Enter new the processor generation(13 or 15 or 17):\n");
        scanf("%d", &de);
        s[index].processor = de;
        printf("Processor updation successfull.\n");
    }
    else
    {
        printf("No computer with given ID exists in the inventory!!!\n");
    }

    bsortDesc();
    printf("Press any key to continue.\n");
    getch();
}

void search_and_display()
{
    int id, index = -1;
    int flag = 0;
    printf("Enter the computer id you need to search: \n");
    scanf("%d", &id);
    for (int i = 0; i <= fill; ++i)
    {
        if (id == s[i].computerID)
        {
            flag = 1;
            index = i;
            break;
        }
    }
    if (flag == 1)
    {
        printf("The computer is present !!!\n");
        printf("------------------------------------------\n");
        printf("Computer ID: %d\n", s[index].computerID);
        printf("Date of Purchace: %d\n", s[index].DOP);
        printf("Date of Manufacture: %d\n", s[index].DOM);
        printf("Warranty Period: %d\n", s[index].warrantyperiod);
        printf("Processor: %d\n", s[index].processor);
        printf("Return off date: %d\n", s[index].ROD);
    }
    else
    {
        printf("No computer with given ID exists in the inventory!!!\n");
    }

    bsortDesc();
    printf("Press any key to continue.\n");
    getch();
}

void number_of_comps()
{
    int fil1;
    int fil2;
    int fil3;
    int fil4;
    int fil5;
    printf("If you do not want the asked filter, enter -1: \n");

    printf("Date of Purchace: \n");
    scanf("%d", &fil1);
    printf("Date of Manufacture:\n");
    scanf("%d", &fil2);
    printf("Warranty Period: \n");
    scanf("%d", &fil3);
    printf("Processor: \n");
    scanf("%d", &fil4);
    printf("Return off date: \n");
    scanf("%d", &fil5);
    int correct = 0;
    if (fil1 != -1)
    {
        correct++;
    }
    if (fil2 != -1)
    {
        correct++;
    }
    if (fil3 != -1)
    {
        correct++;
    }
    if (fil4 != -1)
    {
        correct++;
    }
    if (fil5 != -1)
    {
        correct++;
    }
    int i, j;
    int se = fill + 1;
    int ans = 0;
    for (i = 0; i < se; i++)
    {
        int subcor = 0;
        if (fil1 != -1 && s[i].DOP == fil1)
        {
            subcor++;
        }
        if (fil2 != -1 && s[i].DOM == fil2)
        {
            subcor++;
        }
        if (fil3 != -1 && s[i].warrantyperiod == fil3)
        {
            subcor++;
        }
        if (fil4 != -1 && s[i].processor == fil4)
        {
            subcor++;
        }
        if (fil5 != -1 && s[i].ROD == fil5)
        {
            subcor++;
        }
        if (subcor == correct)
        {
            ans++;
        }
    }
    printf("The number of computers with given filters are %d\n", ans);
    printf("Press any key to continue.\n");
    getch();
}

void longestROD()
{

    int ans = -99999999;
    int index;
    for (int i = 0; i <= fill; i++)
    {
        int subans;
        int dd1 = 0, mm1 = 0, yyyy1 = 0;
        int dd2 = 0, mm2 = 0, yyyy2 = 0;
        int temp1 = s[i].DOP;
        int temp2 = s[i].ROD;
        yyyy1 = s[i].DOP % 100000;
        yyyy2 = s[i].ROD % 100000;
        temp1 /= 10000;
        temp2 /= 10000;
        mm1 = temp1 % 1000;
        mm2 = temp2 % 1000;
        temp1 /= 100;
        temp2 /= 100;
        dd1 = temp1 % 1000;
        dd2 = temp2 % 1000;
        struct Date dt2 = {dd2, mm2, yyyy2};
        struct Date dt1 = {dd1, mm1, yyyy1};

        subans = getDifference(dt1, dt2);
        if (subans >= ans)
        {
            ans = subans;
            index = i;
        }
    }
    printf("The computer with max ROD is: \n");
    printf("------------------------------------------\n");
    printf("Computer ID: %d\n", s[index].computerID);
    printf("Date of Purchace: %d\n", s[index].DOP);
    printf("Date of Manufacture: %d\n", s[index].DOM);
    printf("Warranty Period: %d\n", s[index].warrantyperiod);
    printf("Processor: %d\n", s[index].processor);
    printf("Return off date: %d\n", s[index].ROD);
    printf("Press any key to continue.\n");
    getch();
}