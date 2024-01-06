// ? Libraries =====================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>
#include <time.h>

#include "sort.h" // my csv library
// ! this main function is just for testing, i didnt make it yet

// ? Macros ========================================================================================
#define MAX_PATH_LEN 256 // Max length of a path in windows is 256 characters
#define MAX_LINE_SIZE 1024 // Max length of a line in a CSV file
#define REPORT_FILE "report.csv"
#define clearScreen system("cls") // Clear the screen in windows (clear in linux)

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
// #define COLOR_BLUE    "\x1b[34m"
#define COLOR_BLUE    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
// ? functions =====================================================================================
// this function takes menu and return the choice of the user
int menu(char *path,int offset,int num, ...){
    int choice =0;
    char get;
    va_list args;

    while (1) {
        clearScreen;
        va_start(args, num);
        printf("[./%s]> %s\n\n",path,va_arg(args, char*));
        for (int i = 0; i < num-1; i++)
        {
            if (i == choice)printf("    %s-> %s%s\n",COLOR_BLUE,va_arg(args, char*),COLOR_RESET);

            else printf("       %s\n",va_arg(args, char*));
        }
        printf( (choice==num-1 )? "\n%s<- GoBack%s\n" : "\n   GoBack\n",COLOR_RED,COLOR_RESET);

        get = getch();
        if (get==13) return (choice==num-1 )? 0b10000000 : choice<<offset; // Enter button
        if (get==0 || get == 0xE0)  get = getch();	// arrow keys have two codes, the first is 0 or 0xE0
		if (get==72) choice -= (choice>0)? 1:0 ;    // up arrow
		else if (get==80) choice +=  (choice<num-1)? 1:0 ; // down arrow
    }  
}

/*
choice variable :

first 2 bits : alocation method
    0- array            xxxxxxx00
    1- linked list      xxxxxxx01
    2- binary tree      xxxxxxx10

3 to 5 bits : sort algorithm 
    0- bubble sort      xxxx000xx
    1- selection sort   xxxx001xx
    2- insertion sort   xxxx010xx
    3- quick sort       xxxx011xx
    4- merge sort       xxxx100xx
bit 6 : sort direction
    0- ascending        xxx0xxxxx
    1- descending       xxx1xxxxx
bit 7 : is hashed 
    0- no               xx0xxxxxx
    1- yes              xx1xxxxxx // 64 = 0b01000000

bit 8 : go back
    0- no               x0xxxxxxx
    1- yes              x1xxxxxxx // 128 = 0b10000000

bit 9 : hash algorithm
    0- linear           0xxxxxxxx
    1- double           1xxxxxxxx // 256 = 0b100000000

*/
// ? Main ==========================================================================================
int main() {
    // * Variables ------------------------------------------------------------------------------
    FILE *fp; // File pointer
    int choice = 0;
    char path[MAX_PATH_LEN] ;
    char line[MAX_LINE_SIZE] ;
    double time_taken[4]; // array to store the time taken by each algorithm
    /*
        time_taken[0] = loading time
        time_taken[1] = sorting time
        time_taken[2] = printing time
        time_taken[3] = hashing time
    */
    clock_t start_time;
    // * Part 1 : get a path from the user ------------------------------------------------------
    chooseFile:
        do
        {
            system("cls");
            printf("Enter a path: ");
            scanf("%s", path);
            fp = fopen(path, "r");
        } while (fp == NULL);
    // *Part 2 : get the number of the fields of the CSV file------------------------------------
    // ? this part is removed , because the plan changed 
    // ? check the plan-A branch for the old code
    // ? if i had time i will fix the old code because it is more efficient
    // ? the idea of the old code is no metter how many fields in the csv file
    // ? it just take the first fields as an id and put the rest in an array of strings
    // *Part 3 : choosing the alocation method ------------------------------------------------
    allocMethod:
        choice = menu(path,0,4,"Choose the alocation method:","Array","Linked List","binary tree"); // the first 3 bits
        if (choice & 0b10000000) {
            choice = 0;
            goto chooseFile;
        }
    if (choice == 0b0000010) goto sortDirection; // if he choose binary tree without hashing , we will not take a sort algorithm because it is already sorted
    IsHashed:
        choice += menu(path,6,3,"do you want to hash data (1=yes/0=no): ","no","yes");

        if ((choice & 0b10000000) ){
            choice = 0;
            goto allocMethod;
        }
        // choice +=   tmp<<6; // the 7th bit
        HashAlgorithm:
            if (choice & 0b1000000 ) {
                choice += menu(path,8,3,"choose the hash algorithm: ","linear","double");
                if (choice & 0b10000000){
                    choice = choice & 0b00000011;
                    goto IsHashed;
                }
                // choice +=   tmp<<8; // the 9th bit 1 << 8 = 256
            }
          
    // if he choose binary tree without hashing , we will not take a sort algorithm because it is already sorted 0b1000010 = 66
    sortAlgorithm:
        if (choice != 0b0000010){
            choice += menu(path,2,6,"choose the sort algorithm: ","Bubble Sort","selection Sort","insertion Sort","Quick Sort","Merge Sort"); // the 3rd to 5th bits
            if ((choice & 0b10000000)){
                choice = choice & 0b00000011;
                goto IsHashed;
            }
            // choice +=   tmp<<2;
        }
    sortDirection:
        choice += menu(path,5,3,"choose the sort direction: ","Ascending","Descending");
        if (choice & 0b10000000){
            choice = choice & 0b001000011;
            if (choice == 0b0000010) goto allocMethod;
            goto sortAlgorithm;
        }
        // choice +=   tmp<<5; // the 6th bit

    // *Part 4 : sorting the data ------------------------------------------------------------
    if ( (choice & 0b10 ) == 0b0000010) {
        // * Part 4.1 : sorting the data using binary tree 
        printf("%s>Loading File ...\n%s",COLOR_GREEN,COLOR_RESET);
        start_time = clock();
        RecordBinaryTree* root = NULL;
        FileToBinaryTree(fp, &root);
        time_taken[0] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        printf("  >Done in %f seconds\n",time_taken[0]);
        fclose(fp);

        // * Part 4.2 : printing the data 
        start_time = clock();
        printBinaryTree(root, (choice & 0b100000) >> 5);
        time_taken[2] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        printf("  >Done in %f seconds\n",time_taken[2]);
        // * Part 4.3 : free the memory 
        freeBinaryTree(root);
    }
    else if (choice & 0b1) {
        // * Part 4.1 : sorting the data using linked list 
        printf("%s>Loading File ...\n%s",COLOR_GREEN,COLOR_RESET);
        start_time = clock();
        RecordLinkedList* list = createRecordLinkedList();
        FileToLinkedList(fp, list);
        time_taken[0] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        printf("  >Done in %f seconds\n",time_taken[0]);
        fclose(fp);
        // is hashed
        if (choice & 0b1000000){
            printf("%s>Hashing ...\n%s",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            RecordArray array = HashTableLL(list, (choice & 0b100000000));
            time_taken[3] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[3]);

            printf("%s>Sorting ...\n%s",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            ArraySort(&array, (choice & 0b11100) >> 2, (choice & 0b100000) >> 5);
            time_taken[1] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[1]);

            printf("%s>Printing ...%s\n",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            printRecordArray(&array);
            time_taken[2] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[2]);
        }
        else{
            printf("%s>Sorting ...%s\n",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            LLSort(list, (choice & 0b11100) >> 2, (choice & 0b100000) >> 5);
            time_taken[1] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[1]);

            printf("%s>Printing ...%s\n",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            printLinkedList(list);
            time_taken[2] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[2]);
        }
        freeLinkedList(list);
    }
    else {
        // * Part 4.1 : sorting the data using array 
        printf("%s>Loading File ...\n%s",COLOR_GREEN,COLOR_RESET);
        start_time = clock();
        time_taken[0] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        RecordArray *array = createRecordArray();
        FileToArrayRecords(fp, array);
        fclose(fp);
        printf("  >Done in %f seconds\n",(double)(clock() - start_time) / CLOCKS_PER_SEC);
        // is hashed
        if (choice & 0b1000000){
            printf("%s>Haching ...\n%s",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            RecordArray hashedArray = HashTable(array,(choice & 0b100000000));
            time_taken[3] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[3]);

            printf("%s>Sorting ...%s",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            time_taken[1] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            ArraySort(&hashedArray, (choice & 0b11100) >> 2, (choice & 0b100000) >> 5);
            printf("\n  >Done in %f seconds\n",time_taken[1]);

            printf("%s>Printing ...%s\n",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            
            printRecordArray(&hashedArray);
            time_taken[2] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[2]);
        }
        else{
            printf("%s>Sorting ...%s\n",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            time_taken[1] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            ArraySort(array, (choice & 0b11100) >> 2, (choice & 0b100000) >> 5);
            printf("\n  >Done in %f seconds\n",time_taken[1]);

            printf("%s>Printing ...%s\n",COLOR_GREEN,COLOR_RESET);
            start_time = clock();
            printRecordArray(array);
            time_taken[2] = (double)(clock() - start_time) / CLOCKS_PER_SEC;
            printf("  >Done in %f seconds\n",time_taken[2]);
        }
    }
    if (saveReport(REPORT_FILE,path,time_taken,choice)) printf("%s>Report saved successfully%s\n",COLOR_GREEN,COLOR_RESET);
    else printf("%s>Report not saved%s\n",COLOR_RED,COLOR_RESET);

    printf("\n>Do you want to choose another file (1=yes/0=no): ");
    scanf("%d",&choice);
    if (choice) goto chooseFile;    
}
