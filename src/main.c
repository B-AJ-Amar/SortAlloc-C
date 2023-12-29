// ? Libraries =====================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>
#include "sort.h" // my csv library
// ! this main function is just for testing, i didnt make it yet

// ? Macros ========================================================================================
#define MAX_PATH_LEN 256 // Max length of a path in windows is 256 characters
#define MAX_LINE_SIZE 1024 // Max length of a line in a CSV file
#define clearScreen system("cls") // Clear the screen in windows (clear in linux)

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"
// ? functions =====================================================================================
// this function takes menu and return the choice of the user
int menu(int num, ...){
    int choice =0;
    char get;
    va_list args;

    while (1) {
        clearScreen;
        va_start(args, num);
        printf("%s\n",va_arg(args, char*));
        for (int i = 0; i < num-1; i++)
        {
            if (i == choice)
            {
                printf("    %s-> %s%s\n",COLOR_BLUE,va_arg(args, char*),COLOR_RESET);
            }
            else
            {
                printf("       %s\n",va_arg(args, char*));
            }
        }
        get = getch();
        if (get==13){
            return choice;
        }
        if (get==0 || get == 0xE0) 
        {
            get = getch();
        }	
		if (get==72) choice -= (choice>0)? 1:0 ;
			// printf("UP");
		else if (get==80) choice +=  (choice<num-2)? 1:0 ;
			// printf("DOWN");
        
    }
    
}

/*
choice variable :

first 2 bits : alocation method
    0- array            xxxxx00
    1- linked list      xxxxx01
    2- binary tree      xxxxx10

3 to 5 bits : sort algorithm 
    0- bubble sort      xx000xx
    1- selection sort   xx001xx
    2- insertion sort   xx010xx
    3- quick sort       xx011xx
    4- merge sort       xx100xx
bit 6 : sort direction
    0- ascending        x0xxxxx
    1- descending       x1xxxxx
bit 7 : is hashed 
    0- no               0xxxxxx
    1- yes              1xxxxxx

*/

// ? Main ==========================================================================================
int main() {
    // * Variables ------------------------------------------------------------------------------
    FILE *fp; // File pointer
    char path[MAX_PATH_LEN] ;
    int choice = 0,tmpp;
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
    choice = menu(4,"Choose the alocation method:","Array","Linked List","binary tree"); // the first 3 bits
    printf("choice %d",choice);
    scanf("%d", &tmpp);
    choice += menu(3,"do you want to hash data (1=yes/0=no): ","no","yes")<<6; // the 7th bit
    printf("choice %d",choice);
    scanf("%d", &tmpp);
    // if he choose binary tree without hashing , we will not take a sort algorithm because it is already sorted
    if (choice != 2) choice += menu(5,"choose the sort algorithm: ","Bubble Sort","selection Sort","insertion Sort","Quick Sort","Merge Sort")<<2; // the 3rd to 5th bits
    choice += menu(3,"choose the sort direction: ","Ascending","Descending")<<5; // the 6th bit
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
        // LLSort(newLList, 0, 3);
        // printLinkedList(newLList);
        printf("hashing\n");
        RecordArray hashedLL = HashTableLL(newLList, 1);
        printf("printing\n");
        ArraySort(&hashedLL, 0, 3);
        printRecordArray(&hashedLL);
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
