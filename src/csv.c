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
    for (int i = 0; i < array->length; i++) {
        printf("%d, %s, %s, %d\n", array->data[i].id, array->data[i].firstName.data, array->data[i].lastName.data, array->data[i].group);
    }
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