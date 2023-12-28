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

// ? getFieldsNum : get the number of fields in a CSV file

// fix stupid CODE   

// ? Main ==========================================================================================
int main() {
    // * Variables ------------------------------------------------------------------------------
    FILE *fp; // File pointer
    char path[MAX_PATH_LEN] ;

    // * Part 1 : get a path from the user ------------------------------------------------------
    do
    {
        clearScreen;
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
        printf("> Storing csv in Array ===============================\n");
        RecordArray* newArray = (RecordArray*)malloc(sizeof(RecordArray));
        newArray->length = 0;
        newArray->data = NULL;
        CSVToArrayRecords(fp, newArray);
        printRecordArray(newArray);
        printf("> Sorting csv in Array ===============================\n");
        ArraySort(newArray, 0, 4);
        printRecordArray(newArray);
        printf("> hash csv in Array ===============================\n");
        RecordArray hashArray = HashTable(newArray,1);
        printRecordArray(&hashArray);
        // RecordArray csv = ArrStoreCSV(fp);
        // PrintRecordArray(*csv);


    }
    else if (choice == 2)
    {
        printf("Linked List\n");
    }
    else
    {
        printf("binary tree\n");
    }
    
    // using strtoc


    printf("End ...\n");
    return 0;
}
