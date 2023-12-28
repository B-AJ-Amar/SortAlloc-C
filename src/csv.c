#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_LINE_SIZE 1024 // Max length of a line in a CSV file


// ? ========================================================================
// ? Record data types manupulation
// ? ========================================================================


int getLinesNum(FILE *fp){
    int linesNum = 0;
    char *line = (char *)malloc(MAX_LINE_SIZE * sizeof(char));
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        linesNum++;
    }
    rewind(fp); // return the pointer to the begining of the file
    return linesNum;
}






// ? recorde array ========================================================================
// ! there is some error i dont know why 
// RecordArray* createRecordArray() {
//     RecordArray* newArray = (RecordArray*)malloc(sizeof(RecordArray));
//     newArray->length = 0;
//     newArray->data = NULL;
//     return newArray;
// }


// Function to initialize a new RecordArray structure
RecordArray* createRecordArray() {
    RecordArray* newArray = (RecordArray*)malloc(sizeof(RecordArray));
    newArray->length = 0;
    newArray->data = NULL;
    return newArray;
}

void printRecordArray(RecordArray* array) {

    printf("+---------+------------------------------+-------------------------------------+\n");
    printf("|id       |first name                    |last name                     |group |\n");
    printf("+---------+------------------------------+-------------------------------------+\n");
    for (int i = 0; i < array->length; i++) {
        printf("|%d ", array->data[i].id);
        printf("|%s", array->data[i].firstName.data);
        for (int j = 0; j < 30 - array->data[i].firstName.length; j++)printf(" ");
        printf("|%s", array->data[i].lastName.data);
        for (int j = 0; j < 30 - array->data[i].lastName.length; j++)printf(" ");
        printf("|%d     |\n", array->data[i].group);
    }
  
    printf("+---------+------------------------------+-------------------------------------+\n");
}

// ? Binary tree ========================================================================

// Function to create a new RecordBinaryTree node
RecordBinaryTree* createTreeNode(const Record* record) {
    RecordBinaryTree* newNode = (RecordBinaryTree*)malloc(sizeof(RecordBinaryTree));
    newNode->data = *record;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a record into the binary search tree
RecordBinaryTree* insertRecordBinaryTree(RecordBinaryTree* root, const Record* record) {
    if (root == NULL) {
        return createTreeNode(record);
    }

    // Compare IDs to decide whether to insert left or right
    if (record->id < root->data.id) {
        root->left = insertRecordBinaryTree(root->left, record);
    } else if (record->id > root->data.id) {
        root->right = insertRecordBinaryTree(root->right, record);
    }

    return root;
}

// print records in increasing order of their IDs
void printBinaryTreeInc(RecordBinaryTree* root) {
    if (root != NULL) {
        printBinaryTreeInc(root->left);

            printf("|%d ", root->data.id);
            printf("|%s", root->data.firstName.data);
            for (int j = 0; j < 30 - root->data.firstName.length; j++)printf(" ");
            printf("|%s", root->data.lastName.data);
            for (int j = 0; j < 30 - root->data.lastName.length; j++)printf(" ");
            printf("|%d     |\n", root->data.group);
    
        printBinaryTreeInc(root->right);
    }    
}

void printBinaryTreeDec(RecordBinaryTree* root) {
    if (root != NULL) {
        printBinaryTreeDec(root->right);
            
            printf("|%d ", root->data.id);
            printf("|%s", root->data.firstName.data);
            for (int j = 0; j < 30 - root->data.firstName.length; j++)printf(" ");
            printf("|%s", root->data.lastName.data);
            for (int j = 0; j < 30 - root->data.lastName.length; j++)printf(" ");
            printf("|%d     |\n", root->data.group);
        
        printBinaryTreeDec(root->left);
    }
    else printf("empty tree\n");
}

void printBinaryTree(RecordBinaryTree* root, int order) {
    printf("+---------+------------------------------+-------------------------------------+\n");
    printf("|id       |first name                    |last name                     |group |\n");
    printf("+---------+------------------------------+-------------------------------------+\n");
    if (order == 0) printBinaryTreeInc(root);
    else printBinaryTreeDec(root);
    
    printf("+---------+------------------------------+-------------------------------------+\n");
}

void freeBinaryTree(RecordBinaryTree* root) {
    if (root != NULL) {
        freeBinaryTree(root->left);
        freeBinaryTree(root->right);
        free(root);
    }
}


// ? hash table ========================================================================

// the general hash function
RecordArray HashTable(RecordArray* array,int algorithm){
    if (algorithm==0) return linearHashArrayToTable(array);
    return doubleHashArrayToTable(array);
}

// * Liniar Hashing ----------------------------------------------------------
int hash(int key, int size) {
    return key % size;
}

// Function to insert a record into the hash table using linear probing
void insertRecordLinear(RecordArray* table,Record* record) {
    int key = record->id;
    int index = hash(key, table->length);

    // Linear probing to handle collisions
    while (table->data[index].id != -1) {
        index = (index + 1) % table->length;
    }

    // Insert the record at the found index
    table->data[index] = *record;
}

RecordArray linearHashArrayToTable(RecordArray* array) {
    RecordArray newTable = {array->length, (Record*)malloc(array->length * sizeof(Record))};

    for (int i = 0; i < array->length; i++) {
        // Initialize the new table with empty records
        newTable.data[i].id = -1;
    }

    for (int i = 0; i < array->length; i++) {
        insertRecordLinear(&newTable, &array->data[i]); // Using a step size of 1 for linear probing
    }

    return newTable;
}
// * Double Hashing ----------------------------------------------------------

// Second hash function for double hashing (using prime number)
int hash2(int key) {
    return 13 - (key % 13);
}

// Function to insert a record into the hash table using double hashing
void insertRecordDouble(RecordArray* table,Record* record) {
    int key = record->id;
    int index = hash(key, table->length);
    int stepSize = hash2(key);

    // Double hashing to handle collisions
    while (table->data[index].id != -1) {
        index = (index + stepSize ) % table->length;
    }

    // Insert the record at the found index
    table->data[index] = *record;
}

RecordArray doubleHashArrayToTable(RecordArray* array) {
    RecordArray newTable = {array->length, (Record*)malloc(array->length * sizeof(Record))};

    for (int i = 0; i < array->length; i++) {
        // Initialize the new table with empty records
        newTable.data[i].id = -1;
    }

    for (int i = 0; i < array->length; i++) {
        insertRecordDouble(&newTable, &array->data[i]); // Using a step size of 1 for double hashing
    }

    return newTable;
}

// ? ========================================================================
// ? CSV store data
// ? ========================================================================


//* I- Array ================================================================
/*
? there is to ways to store the csv file in array:
    ? 1- count the number of lines in the file and create an array of records with the same length:
        - the time comlexity is O(n){create the array}+O(n){count the lines} = O(2n) and the space complexity is O(n)
    ? 2- realoc the array each time we read a line from the file:
        - the time comlexity is O(n^2) and the space complexity is O(n)

? we will use the first method because it's faster and it's not a big deal to waste some space
*/

void CSVToArrayRecords(FILE* file, RecordArray* array) {
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int linesNum = getLinesNum(file);

    array->length = linesNum;
    array->data = (Record*)malloc(linesNum * sizeof(Record));

    char line[MAX_LINE_SIZE];
    for (int i = 0; i < linesNum; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            break;  // End of file or error
        }

        Record* record = &array->data[i];

        char* token = strtok(line, ",");
        record->id = atoi(token);

        token = strtok(NULL, ",");
        record->firstName = strCreate(token);

        token = strtok(NULL, ",");
        record->lastName = strCreate(token);

        token = strtok(NULL, ",");
        record->group = atoi(token);
    }

}


//* II- BinaryTree ================================================================
void CSVToBinaryTree(FILE* file, RecordBinaryTree** root) {
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_SIZE];
   
    while( fgets ( line, sizeof line, file ) != NULL ){ 

        Record* record= (Record*)malloc(sizeof(Record));

        char* token = strtok(line, ",");
        record->id = atoi(token);

        token = strtok(NULL, ",");
        record->firstName = strCreate(token);

        token = strtok(NULL, ",");
        record->lastName = strCreate(token);

        token = strtok(NULL, ",");
        record->group = atoi(token);

        *root = insertRecordBinaryTree(*root, record);
    }

}


