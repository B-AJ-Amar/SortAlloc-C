#ifndef CSV_H
#define CSV_H

#include <stdlib.h>
#include <stdio.h>
#include "str.h" 

// ? =============================================================================
// ? CSV data types
// ? =============================================================================
typedef struct Record {
    int id;
    str firstName;
    str lastName;
    int group;
} Record;

typedef struct RecordArray {
    int length;
    Record* data;
} RecordArray;

typedef struct RecordNode {
    Record data;
    struct RecordNode* next;
} RecordNode;

typedef struct RecordLinkedList {
    RecordNode* head;
    RecordNode* tail;
    int length;
} RecordLinkedList;

typedef struct RecordBinaryTree {
    Record data;
    struct RecordBinaryTree* left;
    struct RecordBinaryTree* right;
} RecordBinaryTree;






// * Record --------------------------------------------------------------------

int getLinesNum(FILE *fp);
/*
// Record RecordInit()

// void SetRecord(Record *record, int id, str firstName, str lastName, int group);

// Record getCSVLine(FILE *fp)

// void PrintRecord(Record record);
*/
// * RecordArray --------------------------------------------------------------

// RecordArray* createRecordArray() 
void printRecordArray(RecordArray* array);
// void PrintRecordArray(RecordArray arr)

// void RecordArraySet(RecordArray* s, int index, Record record);


// * RecordLinkedList ----------------------------------------------------------
RecordNode* createRecordNode(const Record* record);

RecordLinkedList* createRecordLinkedList();

void insertRecordLinkedList(RecordLinkedList* list, const Record* record);

void printLinkedList(const RecordLinkedList* list);

void freeLinkedList(RecordLinkedList* list);
// * RecordBinaryTree ----------------------------------------------------------

RecordBinaryTree* createTreeNode(const Record* record);

RecordBinaryTree* insertRecordBinaryTree(RecordBinaryTree* root, const Record* record);

void printBinaryTreeInc(RecordBinaryTree* root);
void printBinaryTreeDec(RecordBinaryTree* root);

void printBinaryTree(RecordBinaryTree* root, int order);

void freeBinaryTree(RecordBinaryTree* root);

// * Hash Table ---------------------------------------------------------------
// liniar hash table
int hash(int key, int size);

// double hash table
int hash2(int key);

RecordArray HashTable(RecordArray* array,int algorithm);

void insertRecordLinear(RecordArray* table,Record* record);

RecordArray linearHashArrayToTable(RecordArray* array);

void insertRecordDouble(RecordArray* table,Record* record);

RecordArray doubleHashArrayToTable(RecordArray* array);

// +++++++++++++++++++++++++++

RecordArray HashTableLL(RecordLinkedList* array,int algorithm);

RecordArray linearHashLinkedListToTable(RecordLinkedList* list);




// ? storing CSV data =========================================================
// RecordArray* ArrStoreCSV(FILE *fp);
void CSVToArrayRecords(FILE* file, RecordArray* array);
// void CSVToArrayRecords(const char* filename, RecordArray* array);
void CSVToBinaryTree(FILE* file, RecordBinaryTree** root); 

void CSVToLinkedList(FILE* file, RecordLinkedList* list);

#endif