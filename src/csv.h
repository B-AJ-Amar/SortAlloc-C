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

// typedef struct RecordNode {
//     Record data;
//     struct RecordNode* next;
// } RecordNode;

// typedef struct RecordLinkedList {
//     RecordNode* head;
//     RecordNode* tail;
//     int length;
// } RecordLinkedList;

// typedef struct RecordBinaryTree {
//     Record data;
//     struct RecordBinaryTree* left;
//     struct RecordBinaryTree* right;
// } RecordBinaryTree;






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

// void PrintRecordArray(RecordArray arr)

// void RecordArraySet(RecordArray* s, int index, Record record);
// * Hash Table ---------------------------------------------------------------
RecordArray HashTable(RecordArray* array,int algorithm);

// liniar hash table
int hash(int key, int size);

void insertRecordLinear(RecordArray* table,Record* record);

RecordArray linearHashArrayToTable(RecordArray* array);

// double hash table
int hash2(int key);

void insertRecordDouble(RecordArray* table,Record* record);

RecordArray doubleHashArrayToTable(RecordArray* array);

// ? storing CSV data =========================================================
// RecordArray* ArrStoreCSV(FILE *fp);
void CSVToArrayRecords(FILE* file, RecordArray* array);
// void CSVToArrayRecords(const char* filename, RecordArray* array);
void printRecordArray(RecordArray* array);

#endif