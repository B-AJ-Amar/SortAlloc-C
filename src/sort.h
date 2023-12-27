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

#endif