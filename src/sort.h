#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdio.h>
#include "csv.h"


// ? Array ========================================================================

void ArrayBubbleSortById(RecordArray* array, int direction);

void ArraySelectionSortById(RecordArray* array,int direction);

void ArrayInsertionSortById(RecordArray* array,int direction);

void ArrayQuickSort(RecordArray* array, int low, int high);

void ArrayMergeSort(RecordArray* array, int left, int right, int direction);

void ArraySort(RecordArray* array, int direction, int sortType);


// ? Linked List ==================================================================

void bubbleSortLinkedList(RecordLinkedList* list,int direction) ;

void swapRecordNodesLL(RecordNode* a, RecordNode* b);

void selectionSortLinkedList(RecordLinkedList* list,int direction) ;

void insertionSortLinkedList(RecordLinkedList* list,int direction);

// void swapNodesLL(RecordNode* a, RecordNode* b);


// RecordNode* partitionLLQS(RecordNode* low, RecordNode* high);

void quickSortLinkedList(RecordNode* low, RecordNode* high);

// void splitList(RecordNode* head, RecordNode** left, RecordNode** right);

// RecordNode* mergeLinkedList(RecordNode* left, RecordNode* right);

void mergeSortLinkedList(RecordNode** head,int direction);

// RecordNode* IMergeLL(RecordNode* left, RecordNode* right);

// RecordNode* DMergeLL(RecordNode* left, RecordNode* right);

// void mergeSortLinkedList(RecordLinkedList* list,int direction) ;

void LLSort(RecordLinkedList* list, int direction, int sortAlgorithm);
#endif