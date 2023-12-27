#ifndef CSV_H
#define CSV_H

#include <stdlib.h>
#include <stdio.h>
#include "str.h" // WTF 

// ? =============================================================================
// ? CSV data types
// ? =============================================================================
typedef struct Record {
    int id;
    strArray* fields; 
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
int getFieldsNum(FILE *fp);

int getLinesNum(FILE *fp);

Record* RecordCreate(int FieldsNum);

void SetRecord(Record *record, int id, strArray* fields);

void PrintRecord(Record record);

// * RecordArray --------------------------------------------------------------

RecordArray *RecordArrayCreate(int length,int fieldsNum);

void PrintRecordArray(RecordArray arr);

// void RecordArraySet(RecordArray* s, int index, Record record);


RecordArray* ArrStoreCSV(FILE *fp);

#endif