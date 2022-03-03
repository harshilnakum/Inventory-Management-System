#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// This Project is executed with the help of Linked Lists and Basics of File Handling in C language.
typedef struct llNode
{
    // The core linked list will contain Data - Admission Number, First Name, Last Name, Gender
    // And a pointer to the next node in the linked list.
    
    //Linked List is chosen over array of structures because of easier Insertion Deletion operations.
    char adm_no[10];
    char fname[20];
    char lname[20];
    char gender;
    struct llNode *next;
} llNode;
llNode *head;
char file_name[8] = "stu.txt"; // File to store all the data given by the user.

// Insert(append) node in linked list
void ll_insert(char adm_no[], char fname[], char lname[], char gender)
{
    // First we traverse through the List and point towards the last List, then we allocate a new node and append it to the list.
    if (!head)
    {
        head = (llNode *)malloc(sizeof(llNode));
        strcpy(head->adm_no, adm_no);
        strcpy(head->fname, fname);
        strcpy(head->lname, lname);
        head->gender = gender;
        head->next = NULL;
    }
    else
    {
        llNode *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = (llNode *)malloc(sizeof(llNode));
        strcpy(temp->next->adm_no, adm_no);
        strcpy(temp->next->fname, fname);
        strcpy(temp->next->lname, lname);
        temp->next->gender = gender;
        temp->next->next = NULL;
    }
}
// Delete node from specified position
void ll_delete(int pos)
{
    // We traverse through the linked list to the position which is to be deleted, we name that node temp and the immediate previous node as 'prev'. Then we link the Previous node to the node next to temporary.
    int i = 0;
    llNode *temp = head, *prev = NULL;
    while (i < pos - 1 && temp)
    {
        prev = temp;
        temp = temp->next;
        i++;
    }
    if (i == 0)
    {
        head = head->next;
        free(temp);
    }
    else
    {
        prev->next = temp->next;
        free(temp);
    }
}
// Modify node at specified position
void ll_modify(int pos)
{
    // Fetching new details...
    int i = 0;
    char adm_no[10], fname[20], lname[20], gender;
    printf("Enter new admission number: ");
    scanf("%s", adm_no);
    printf("Enter new first name: ");
    scanf("%s", fname);
    printf("Enter new last name: ");
    scanf("%s", lname);
    printf("Enter new gender (M for male, F for female): ");
    scanf(" %c", &gender);
    // Traversing through the list and pointing to the last node.
    llNode *temp = head;
    while (i < pos - 1 && temp)
    {
        temp = temp->next;
        i++;
    }
    strcpy(temp->adm_no, adm_no);
    strcpy(temp->fname, fname);
    strcpy(temp->lname, lname);
    temp->gender = gender;
}

// Read the content of the files in the linked list
void get_list()
{
    //This code inserts the data of the file into a linked list using insert function above.
    head = NULL;
    char adm_no[10], fname[20], lname[20], gender;
    FILE *fptr = fopen(file_name, "r");
    while (fscanf(fptr, "%s %s %s %c", adm_no, fname, lname, &gender) != -1)
    {
        ll_insert(adm_no, fname, lname, gender);
    }
    fclose(fptr);
}
// Dump the content of the files in the linked list
void put_list()
{
    // We dump all the data of the Linked List into the file by use of fprintf function.
    FILE *fptr = fopen(file_name, "w");
    llNode *temp = head;
    // Traverse and insert.
    while (temp)
    {
        fprintf(fptr, "%-10s %-20s %-20s %c\n", temp->adm_no, temp->fname,
                temp->lname, temp->gender);
        temp = temp->next;
    }
    fclose(fptr);
}
int get_count()
{
    //Basic Linked list traversal with help of a counter variable.
    get_list();
    int i = 0;
    llNode *temp = head;
    while (temp)
    {
        temp = temp->next;
        i++;
    }
    return i;
}
// Append new record to file directly
void add_record()
{
    //Directly fetches and adds the data to the file.
    char adm_no[10], fname[20], lname[20], gender;
    printf("Enter admission number: ");
    scanf("%s", adm_no);
    printf("Enter first name: ");
    scanf("%s", fname);
    printf("Enter last name: ");
    scanf("%s", lname);
    printf("Enter gender (M for male, F for female): ");
    scanf(" %c", &gender);
    FILE *fptr = fopen(file_name, "a");
    fprintf(fptr, "%-10s %-20s %-20s %c\n", adm_no, fname, lname, gender);
    fclose(fptr);
}
// Delete a record from the file using linked list
void delete_record()
{

    int i = 1, idx;
    get_list(); //First we get all the file data into a Linked List.
    llNode *temp = head;
    // Then we traverse and print all the data. And query the position to delete.
    while (temp)
    {
        printf("%d %-10s %-20s %-20s %c\n", i++, temp->adm_no, temp->fname,
               temp->lname, temp->gender);
        temp = temp->next;
    }
    printf("Enter the index of record to delete: ");
    scanf("%d", &idx);
    //We then Delete that node from the Linked List.
    ll_delete(idx);
    //Finally we print the List into the file overwritting all the previous data.
    put_list();
}
// Modify a record from the file using linked list
void modify_record()
{
    int i = 1, idx;
    get_list(); //First we get all the file data into a Linked List.
    llNode *temp = head;
    // Then we traverse and print all the data. And query the position to modify.
    while (temp)
    {
        printf("%d %-10s %-20s %-20s %c\n", i++, temp->adm_no, temp->fname,
               temp->lname, temp->gender);
        temp = temp->next;
    }
    printf("Enter the index of record to modify: ");
    scanf("%d", &idx);
    //Modify the postion with the help of modify function we implemented above.
    ll_modify(idx);
     //Finally we print the List into the file overwritting all the previous data.
    put_list();
}
// Display all records
void show_records()
{
    //Traverse through the file using file handling using fscanf and print the data.
    printf("\nRecords: \n");
    char adm_no[10], fname[20], lname[20], gender;
    FILE *fptr = fopen(file_name, "r");
    while (fscanf(fptr, "%s %s %s %c", adm_no, fname, lname, &gender) != -1)
    {
        printf("%-10s %-20s %-20s %c\n", adm_no, fname, lname, gender);
    }
    fclose(fptr);
    printf("\n");
}
// Display count of records
void show_count()
{
    int i = get_count();
    printf("Number of records: %d\n", i);
}
// Compare function for ascending order name
int cmp_asc(const void *a, const void *b)
{
    llNode *l1 = (llNode *)a;
    llNode *l2 = (llNode *)b;
    return strcmp(l1->fname, l2->fname);
}
// Sort first names in ascending order
void sort_asc_fname()
{
    int n = get_count();
    llNode arr[n];
    llNode *temp = head;
    for (int i = 0; i < n; i++)
    {
        arr[i] = *temp;
        temp = temp->next;
    }
    qsort(arr, n, sizeof(llNode), cmp_asc);
    for (int i = 0; i < n; i++)
    {
        printf("%-10s %-20s %-20s %c\n", arr[i].adm_no, arr[i].fname,
               arr[i].lname, arr[i].gender);
    }
}
// Compare function for descending order name
int cmp_dsc(const void *a, const void *b)
{
    llNode *l1 = (llNode *)a;
    llNode *l2 = (llNode *)b;
    return strcmp(l2->lname, l1->lname);
}
// Sort last names in descending order
void sort_dsc_lname()
{
    int n = get_count();
    llNode arr[n];
    llNode *temp = head;
    for (int i = 0; i < n; i++)
    {
        arr[i] = *temp;
        temp = temp->next;
    }
    qsort(arr, n, sizeof(llNode), cmp_dsc);
    for (int i = 0; i < n; i++)
    {
        printf("%-10s %-20s %-20s %c\n", arr[i].adm_no, arr[i].fname,
               arr[i].lname, arr[i].gender);
    }
}
// Put girls and boys entries in separate files
void girls_boys_sep()
{
    get_list();
    FILE *g = fopen("girls.txt", "w"), *b = fopen("boys.txt", "w");
    llNode *temp = head;
    while (temp)
    {
        if (temp->gender == 'F')
        {
            fprintf(g, "%-10s %-20s %-20s %c\n", temp->adm_no, temp->fname,
                    temp->lname, temp->gender);
        }
        else
        {
            fprintf(b, "%-10s %-20s %-20s %c\n", temp->adm_no, temp->fname,
                    temp->lname, temp->gender);
        }
        temp = temp->next;
    }
    fclose(g);
    fclose(b);
}
// Sub menu for option 5
void summaries()
{
    char choice;
    do
    {
        printf("Summaries menu: \n");
        printf("a) Get total Count of students. \n");
        printf("b) Display data in Ascending order of first name. \n");
        printf("c) Display data in Descending order of last name. \n");
        printf("d) Sort the Girls and boys in separate file. \n");
        printf("z) Exit. \n");
        printf("> ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'a':
            show_count();
            break;
        case 'b':
            sort_asc_fname();
            break;
        case 'c':
            sort_dsc_lname();
            break;
        case 'd':
            girls_boys_sep();
            break;
        default:
            break;
        }
    } while (choice != 'z');
}
// Driver Code running the choice loop in Main function:
int main()
{
    head = NULL;
    int choice = 0;
    do
    {
        printf("Welcome to the system User... Please select the choice from Menu: \n");
        printf("1) Add a record into the file. \n");
        printf("2) Delete a record from the file. \n");
        printf("3) Modify a record from the file. \n");
        printf("4) Show all the records from the file. \n");
        printf("5) Show Record summaries menu. \n");
        printf("-1) Exit. \n");
        printf("> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_record();
            break;
        case 2:
            delete_record();
            break;
        case 3:
            modify_record();
            break;
        case 4:
            show_records();
            break;
        case 5:
            summaries();
            break;
        default:
            break;
        }
    } while (choice != -1);
}
