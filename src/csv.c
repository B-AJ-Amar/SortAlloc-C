#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_LINE_SIZE 1024 // Max length of a line in a CSV file


// ? ========================================================================
// ? Record data types manupulation
// ? ========================================================================

int getFieldsNum(FILE *fp){
    int fieldsNum = 0;
    printf("getFieldsNum\n");
    char *line = (char *)malloc(MAX_LINE_SIZE * sizeof(char));
    fgets(line, MAX_LINE_SIZE, fp);
    char *token = strtok(line, ",");

    while (token != NULL) {
        fieldsNum++;
        printf("token: %s , fields %d \n", token,fieldsNum);
        token = strtok(NULL, ",");
    }
    rewind(fp); // return the pointer to the begining of the file
    return fieldsNum;
}

int getLinesNum(FILE *fp){
    int linesNum = 0;
    char *line = (char *)malloc(MAX_LINE_SIZE * sizeof(char));
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        linesNum++;
    }
    rewind(fp); // return the pointer to the begining of the file
    return linesNum;
}



// create recorde 

Record* RecordCreate(int FieldsNum){
    strArray* fields;
    *fields = strArrayCreate(FieldsNum-1);
    Record* record = (Record*)malloc(sizeof(Record));  
    record->fields = fields;
    printf("> creating Rec =========================\n");
    PrintRecord(*record);
    return record;
}

void SetRecord(Record *record, int id, strArray* fields){
    record->id = id;
    record->fields = fields;
}



void PrintRecord(Record record){
    printf("{\n");
    printf("    id: %d\n", record.id);
    printf("    fields: ");
    strArrayPrint(*(record.fields));
    printf("\n}");
}

// * RecordArray --------------------------------------------------------------

RecordArray *RecordArrayCreate(int length,int fieldsNum){
    RecordArray* arr = (RecordArray*)malloc(sizeof(RecordArray));
    arr->length = length;
    arr->data = RecordCreate(fieldsNum);
    return arr;
}

void PrintRecordArray(RecordArray arr){
    printf("[");
    for (int i = 0; i < arr.length; i++) {
        PrintRecord(arr.data[i]);
        printf(",\n");
    }
    printf("]");
}
// ? ========================================================================
// ? CSV store data
// ? ========================================================================

// ! akhir 7aja wsaltlha hiya masal7ach nkhdm bla Record , lavm ndir record w n7otto f RecordArray
RecordArray* ArrStoreCSV(FILE *fp){
    printf("@ArrStoreCSV######################################\n");
    int fieldsNum = getFieldsNum(fp);
    int linesNum = getLinesNum(fp);
    int tempID = 0;
    RecordArray* arr = RecordArrayCreate(linesNum, fieldsNum);
    arr->length = linesNum;
    arr->data = RecordCreate(fieldsNum);
    char *line = NULL;
    char *token = strtok(line, ",");
    int recLine=0, recField=0;

    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        recField = 0;
        strArray tempArray = strArrayCreate(fieldsNum-1);
        tempID = atoi(strtok(line, ","));
        arr->data[recLine].id = tempID;
        token = strtok(line, ",");
        while (token != NULL) {

            printf("token: %s , fields %d \n", token,recField);
            // strArraySet(&arr.data[recLine].fields, recField, token);
            strArraySet(&tempArray, recField, token);
            recField++;
            token = strtok(NULL, ",");
        }
        printf("> end record %d :\n", recLine);
        strArrayCopy(arr->data[recLine].fields, tempArray);
        printf("result record :\n");
        PrintRecord(arr->data[recLine]);
        recLine++;
    }
    PrintRecordArray(*arr);
    printf("ArrStoreCSV passed######################################\n");
    return arr;
}



// RecordLinkedList StoreCSVList(FILE *fl){
//     RecordLinkedList list;
//     list.head = NULL;
//     list.tail = NULL;
//     list.length = 0;
//     char *line = (char *)malloc(MAX_LINE_SIZE * sizeof(char));
//     char *token = strtok(line, ",");
//     int i = 0;
//     while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
//         RecordNode *node = (RecordNode *)malloc(sizeof(RecordNode));
//         node->data.id = i;
//         node->data.fields = strArrayCreate(fieldsNum);
//         token = strtok(line, ",");
//         while (token != NULL) {
//             strArrayPush(&node->data.fields, token);
//             token = strtok(NULL, ",");
//         }
//         node->next = NULL;
//         if (list.head == NULL) {
//             list.head = node;
//             list.tail = node;
//         } else {
//             list.tail->next = node;
//             list.tail = node;
//         }
//         list.length++;
//         i++;
//     }
//     return list;
// }



// ! el mechkl fi strArray lazm nl9alha 7all
