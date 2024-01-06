#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 1024 // Max length of a line in a CSV file
/*
the main aim of this file is to read data from a csv , but the plan changed , after i get the new form of the data i will change the code
*/
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
        printf("|%8d ", array->data[i].id);
        printf("|%s", array->data[i].firstName.data);
        for (int j = 0; j < 30 - array->data[i].firstName.length; j++)printf(" ");
        printf("|%s", array->data[i].lastName.data);
        for (int j = 0; j < 30 - array->data[i].lastName.length; j++)printf(" ");
        printf("|%d     |\n", array->data[i].group);
    }
  
    printf("+---------+------------------------------+-------------------------------------+\n");
}

// ? Binary tree ========================================================================

RecordBinaryTree* createTreeNode(const Record* record) {
    RecordBinaryTree* newNode = (RecordBinaryTree*)malloc(sizeof(RecordBinaryTree));
    newNode->data = *record;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

RecordBinaryTree* insertRecordBinaryTree(RecordBinaryTree* root, const Record* record) {
    if (root == NULL) {
        return createTreeNode(record);
    }

    if (record->id < root->data.id) {
        root->left = insertRecordBinaryTree(root->left, record);
    } else {
        root->right = insertRecordBinaryTree(root->right, record);
    }

    return root;
}

void printBinaryTreeInc(RecordBinaryTree* root) {
    if (root != NULL) {
        printBinaryTreeInc(root->left);

            printf("|%8d ", root->data.id);
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
            
            printf("|%8d ", root->data.id);
            printf("|%s", root->data.firstName.data);
            for (int j = 0; j < 30 - root->data.firstName.length; j++)printf(" ");
            printf("|%s", root->data.lastName.data);
            for (int j = 0; j < 30 - root->data.lastName.length; j++)printf(" ");
            printf("|%d     |\n", root->data.group);
        
        printBinaryTreeDec(root->left);
    }
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

// ? Linked Lists ========================================================================
RecordNode* createRecordNode(const Record* record) {
    RecordNode* newNode = (RecordNode*)malloc(sizeof(RecordNode));
    newNode->data = *record;
    newNode->next = NULL;
    return newNode;
}

RecordLinkedList* createRecordLinkedList() {
    RecordLinkedList* newList = (RecordLinkedList*)malloc(sizeof(RecordLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->length = 0;
    return newList;
}

void insertRecordLinkedList(RecordLinkedList* list, const Record* record) {
    RecordNode* newNode = createRecordNode(record);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->length++;
}

void printLinkedList(const RecordLinkedList* list) {
    RecordNode* current = list->head;

    printf("+---------+------------------------------+-------------------------------------+\n");
    printf("|id       |first name                    |last name                     |group |\n");
    printf("+---------+------------------------------+-------------------------------------+\n");

    while (current != NULL) {
        printf("|%8d ", current->data.id);
        printf("|%s", current->data.firstName.data);
        for (int j = 0; j < 30 - current->data.firstName.length; j++) printf(" ");
        printf("|%s", current->data.lastName.data);
        for (int j = 0; j < 30 - current->data.lastName.length; j++) printf(" ");
        printf("|%d     |\n", current->data.group);

        current = current->next;
    }
    printf("+---------+------------------------------+-------------------------------------+\n");
}

void freeLinkedList(RecordLinkedList* list) {
    RecordNode* current = list->head;
    RecordNode* next;

    while (current != NULL) {
        next = current->next;
        strFree(&current->data.firstName);
        strFree(&current->data.lastName);
        free(current);
        current = next;
    }

    free(list);
}

// ? ========================================================================
// ? hash table 
// ? ========================================================================
int hash(int key, int size) {
    return key % size;
}

int hash2(int key) {
    return 5 - (key % 5);
}
void insertRecordLinear(RecordArray* table,Record* record) {
    int key = record->id;
    int index = hash(key, table->length);

    while (table->data[index].id != -1) {
        index = (index + 1) % table->length;
    }

    table->data[index] = *record;
}
void insertRecordDouble(RecordArray* table,Record* record) {
    int key = record->id;
    int index = hash(key, table->length);
    int stepSize = hash2(key);

    while (table->data[index].id != -1) {
        index = (index + stepSize ) % table->length;
    }

    table->data[index] = *record;
}
// @ Arrays  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// the general hash function
RecordArray HashTable(RecordArray* array,int algorithm){
    if (algorithm==0) return linearHashArray(array);
    return doubleHashArray(array);
}

// * Liniar Hashing ----------------------------------------------------------
RecordArray linearHashArray(RecordArray* array) {
    RecordArray newTable = {array->length, (Record*)malloc(array->length * sizeof(Record))};

    for (int i = 0; i < array->length; i++) {
        newTable.data[i].id = -1;
    }

    for (int i = 0; i < array->length; i++) {
        insertRecordLinear(&newTable, &array->data[i]); 
    }

    return newTable;
}
// * Double Hashing ----------------------------------------------------------
RecordArray doubleHashArray(RecordArray* array) {
    RecordArray newTable = {array->length, (Record*)malloc(array->length * sizeof(Record))};

    for (int i = 0; i < array->length; i++) {
        newTable.data[i].id = -1;  // -1 ==> empty
    }

    for (int i = 0; i < array->length; i++) {
        insertRecordDouble(&newTable, &array->data[i]); // Using a step size of 1 for double hashing
    }
    return newTable;
}
// @ Linked Lists +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RecordArray HashTableLL(RecordLinkedList* array,int algorithm){
    if (algorithm==0) return linearHashLinkedList(array);
    return doubleHashLinkedList(array);
}
// * Liniar Hashing ----------------------------------------------------------

RecordArray linearHashLinkedList(RecordLinkedList* list) {
    int tableSize = list->length;
    RecordArray newTable = {tableSize, malloc(tableSize * sizeof(Record))};

    for (int i = 0; i < tableSize; i++) {
        newTable.data[i].id = -1; // -1 ==> empty
    }

    RecordNode* current = list->head;
    do{
        insertRecordLinear(&newTable, &current->data);
        current = current->next;
    }
    while (current != NULL) ;

    return newTable;
}
// * Double Hash ------------------------------------------------------------

RecordArray doubleHashLinkedList(RecordLinkedList* list) {
    int tableSize = list->length;
    RecordArray newTable = {tableSize, malloc(tableSize * sizeof(Record))};

    for (int i = 0; i < tableSize; i++) {
        newTable.data[i].id = -1; // -1 ==> empty
    }

    RecordNode* current = list->head;
    do{
        insertRecordDouble(&newTable, &current->data);
        current = current->next;
    }
    while (current != NULL) ;

    return newTable;
}
// ? ========================================================================
// ? CSV store data
// ? ========================================================================
// ! the main aim of this file is to read data from a csv , but the plan changed , after i get the new form of the data i will change the code
// ! the new form of the data is : "Matricule: 12345678 Nom: JHONE Prénom: DOE Groupe: 1"

// ? the old function ============================
// void saveCSVLine(char* line,Record* record){
//     char* token = strtok(line, ",");
//     record->id = atoi(token);

//     token = strtok(NULL, ",");
//     record->firstName = strCreate(token);

//     token = strtok(NULL, ",");
//     record->lastName = strCreate(token);

//     token = strtok(NULL, ",");
//     record->group = atoi(token);
// }
//? =========================================
void saveTxtLine(char* line,Record* record){
        char* token = strtok(line, ":");
        record->id = atoi(token);
        token = strtok(NULL, ":");
        record->firstName = strSub(strCreate(token),0 ,-8); // to remove the last 8 charachters ' Prénom: '

        token = strtok(NULL, ":");
        record->lastName = strSub(strCreate(token),0 , -7); // to remove the last 7 charachters ' Groupe: '

        token = strtok(NULL, ",");
        record->group = atoi(token);
}
//* I- Array ================================================================
/*
? there is to ways to store the csv file in array:
    ? 1- count the number of lines in the file and create an array of records with the same length:
        - the time comlexity is O(n){create the array}+O(n){count the lines} = O(2n) and the space complexity is O(n)
    ? 2- realoc the array each time we read a line from the file:
        - the time comlexity is O(n^2) and the space complexity is O(n)

? we will use the first method because it's faster and it's not a big deal to waste some space
*/

void FileToArrayRecords(FILE* file, RecordArray* array) {

    int linesNum = getLinesNum(file);

    array->length = linesNum;
    array->data = (Record*)malloc(linesNum * sizeof(Record));

    char line[MAX_LINE_SIZE];
    for (int i = 0; i < linesNum; i++) {
        fgets(line, sizeof(line), file);
        Record* record = &array->data[i];
        saveTxtLine(line+11,record); // line+11 to skip the first 11 charachters 'Matricule: '
    }

}

//* II- BinaryTree ================================================================
void FileToBinaryTree(FILE* file, RecordBinaryTree** root) {

    char line[MAX_LINE_SIZE];
   
    while( fgets ( line, sizeof line, file ) != NULL ){ 
        Record* record= (Record*)malloc(sizeof(Record));
        saveTxtLine(line+11,record);
        *root = insertRecordBinaryTree(*root, record);
    }
}

// * III- Linked List ================================================================
void FileToLinkedList(FILE* file, RecordLinkedList* list) {
   
    char line[MAX_LINE_SIZE];

    while (fgets(line, sizeof line, file) != NULL) {
        Record* record = (Record*)malloc(sizeof(Record));
        saveTxtLine(line+11,record);
        insertRecordLinkedList(list, record);
    }
}

// ? =======================================================================
// ? save the report to scv file
// ? =======================================================================
bool saveReport(char* file,char* fileName,double* time,int data){
    // file structure : fileName,emethod,loadingTime,sortingTime,IsHashed,HashingMethod,HashingTime
    bool DS = (data && 0b11)?1:0;
    bool isHashed = (data && 0b1000000)?1:0;
    bool hashingMethod = (data && 0b100000000)?1:0;
    bool sortingMethod = (data && 0b11100)>>2;
    bool sortingDirection = (data && 0b100000)?1:0;
    FILE* fp = fopen(file,"a+");
    if (fp==NULL) return false;
    fprintf(fp,"%s,%d,%f,%d,%s,%f,%s,%s,%f\n",
    fileName,DS,time[0],sortingMethod,(sortingDirection)?"Dec":"Inc", time[1], (isHashed)?"True":"False" ,(isHashed)?((hashingMethod)?"double":"liniare"):"None",time[3] );
    fclose(fp);

    return true;
}

