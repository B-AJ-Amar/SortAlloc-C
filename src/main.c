// ? Libraries =====================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h" // my csv library


// ? Macros ========================================================================================
#define MAX_PATH_LEN 256 // Max length of a path in windows is 256 characters
#define MAX_LINE_SIZE 1024 // Max length of a line in a CSV file
#define clearScreen system("cls") // Clear the screen in windows (clear in linux)


// ? functions =====================================================================================


// ? Main ==========================================================================================
int main() {
    // * Variables ------------------------------------------------------------------------------
    FILE *fp; // File pointer
    char path[MAX_PATH_LEN] ;

    // * Part 1 : get a path from the user ------------------------------------------------------
    do
    {
        system("cls");
        printf("Enter a path: ");
        scanf("%s", path);
        printf("path: %s\n", path);
        fp = fopen(path, "r");
    } while (fp == NULL);
    // *Part 2 : get the number of the fields of the CSV file------------------------------------
    // ? this part is removed , because the plan changed 
    // ? check the plan-A branch for the old code
    // ? if i had time i will fix the old code because it is more efficient
    // ? the idea of the old code is no metter how many fields in the csv file
    // ? it just take the first fields as an id and put the rest in an array of strings

    char line[MAX_LINE_SIZE] ;
    

    // *Part 3 : choosing the alocation method ------------------------------------------------
    int choice;
    printf("Choose the alocation method:\n");
    printf("    1- Array\n");
    printf("    2- Linked List\n");
    printf("    3- binary tree\n");
    do
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
    } while (choice < 1 || choice > 3);


    if (choice == 1)
    {
        int sortAlgorithm,sortDirection,isHashed;
        RecordArray* hashArray = NULL;
        printf("> Storing csv in Array ===============================\n");
        RecordArray* newArray = (RecordArray*)malloc(sizeof(RecordArray));
        newArray->length = 0;
        newArray->data = NULL;
        CSVToArrayRecords(fp, newArray);
        do
        {
            printf("do you want to hash data (1=yes/0=no): ");
            scanf("%d", &isHashed);
            fflush(stdin);
        } while (isHashed!=0 && isHashed != 1);
        
        if (isHashed == 1)
        {
            printf("> hashing csv in Array ===============================\n");
            hashArray = (RecordArray*)malloc(sizeof(RecordArray));
            *hashArray = HashTable(newArray, 0);
            printf("donn\n");
        }

            printf("choose the sort algorithm: \n");
            printf("    1- Bubble Sort\n");
            printf("    2- selection Sort\n");
            printf("    3- insertion Sort\n");
            printf("    4- Quick Sort\n");
            printf("    5- Merge Sort\n");
        do
        {
            printf("> ");
            scanf("%d", &sortAlgorithm);
            fflush(stdin);
        } while (sortAlgorithm<1 || sortAlgorithm > 5);
        
            printf("choose the sort direction: \n");
            printf("    1- Ascending\n");
            printf("    2- Descending\n");
        do
        {
            printf("> ");
            scanf("%d",&sortDirection);
            fflush(stdin);
        } while (sortDirection!=2 && sortDirection != 1);

            printf("> Sorting csv in Array ===============================\n");
        if(isHashed)
        {
            ArraySort(hashArray, sortDirection-1, sortAlgorithm-1);
            printRecordArray(hashArray);
        }    
        else{
            ArraySort(newArray, sortDirection-1, sortAlgorithm-1);
            printRecordArray(newArray);

        } 
        

        


    }
    else if (choice == 2)
    {
        RecordLinkedList* newLList = createRecordLinkedList();
        CSVToLinkedList(fp, newLList);
        printLinkedList(newLList);
        printf("Linked List\n");
    }
    else
    {
        RecordBinaryTree* root = NULL;
        CSVToBinaryTree(fp, &root);
        printBinaryTree(root, 0 );
        printf("binary tree\n");
    }
    
    // using strtoc


    printf("End ...\n");
    return 0;
}
