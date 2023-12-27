// ? Libraries ====================================================================
#include <stdlib.h>
#include <string.h>
#include "sort.h" // my sort library

// ? =============================================================================
// ? Array
// ? =============================================================================

void ArraySort(RecordArray* array, int direction, int sortAlgorithm) {
    int sortTypes = 5;
    if (sortAlgorithm % sortTypes == 0) ArrayBubbleSortById(array, direction);
    else if (sortAlgorithm % sortTypes == 1) ArraySelectionSortById(array, direction);
    else if (sortAlgorithm % sortTypes == 2) ArrayInsertionSortById(array, direction);
    else if (sortAlgorithm % sortTypes == 3) ArrayQuickSort(array, 0, array->length - 1); //TODO: add direction
    else if (sortAlgorithm % sortTypes == 4) ArrayMergeSort(array, 0, array->length - 1,direction);

}

/*
? in this functions i could make them shorter by using condition in the for loop
? insead of reapeating the code twice 
? but this inhance the time complexity of the code
? because the condition will be checked every time the loop run 
*/

// * Bubble sort ==============================================================
void ArrayBubbleSortById(RecordArray* array, int direction) {
    if (direction == 0) { // Ascending order
        for (int i = 0; i < array->length - 1; i++) {
            for (int j = 0; j < array->length - i - 1; j++) {
                if (array->data[j].id > array->data[j + 1].id) {
                    // Swap records
                    Record temp = array->data[j];
                    array->data[j] = array->data[j + 1];
                    array->data[j + 1] = temp;
                }
            }
        }
    return;
    }
    // decreasing order
    for (int i = 0; i < array->length - 1; i++) {
        for (int j = 0; j < array->length - i - 1; j++) {
            if (array->data[j].id < array->data[j + 1].id) {
                // Swap records
                Record temp = array->data[j];
                array->data[j] = array->data[j + 1];
                array->data[j + 1] = temp;
            }
        }
    }  
}

// * Selection sort ===========================================================
void ArraySelectionSortById(RecordArray* array,int direction) {
    if (direction== 0){
        for (int i = 0; i < array->length - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < array->length; j++) {
                if (array->data[j].id < array->data[minIndex].id) {
                    minIndex = j;
                }
            }

            // Swap records
            Record temp = array->data[i];
            array->data[i] = array->data[minIndex];
            array->data[minIndex] = temp;
        }
    return;
    }
    // decreasing order
    for (int i = 0; i < array->length - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < array->length; j++) {
            if (array->data[j].id > array->data[minIndex].id) {
                minIndex = j;
            }
        }

        // Swap records
        Record temp = array->data[i];
        array->data[i] = array->data[minIndex];
        array->data[minIndex] = temp;
    }
}

// * Insertion sort ===========================================================
void ArrayInsertionSortById(RecordArray* array,int direction) {
    int i, j;
    Record key;
    if (direction== 0){
        for (i = 1; i < array->length; i++) {
            key = array->data[i];
            j = i - 1;

            while (j >= 0 && array->data[j].id > key.id) {
                array->data[j + 1] = array->data[j];
                j = j - 1;
            }

            array->data[j + 1] = key;
        }
        return;
    }
    // decreasing order
    for (i = 1; i < array->length; i++) {
        key = array->data[i];
        j = i - 1;

        while (j >= 0 && array->data[j].id < key.id) {
            array->data[j + 1] = array->data[j];
            j = j - 1;
        }

        array->data[j + 1] = key;
    }
}
//* quick sort ================================================================
// 
int partition(RecordArray* array, int low, int high) {
    int pivot = array->data[high].id;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array->data[j].id <= pivot) {
            i++;
            // Swap records
            Record temp = array->data[i];
            array->data[i] = array->data[j];
            array->data[j] = temp;
        }
    }

    // Swap the pivot element with the element at (i + 1)
    Record temp = array->data[i + 1];
    array->data[i + 1] = array->data[high];
    array->data[high] = temp;

    return i + 1;
}

// Function to perform quicksort on RecordArray based on id
void ArrayQuickSort(RecordArray* array, int low, int high) {
    if (low < high) {
        // Find the pivot index
        int pivotIndex = partition(array, low, high);

        // Recursively sort the subarrays
        ArrayQuickSort(array, low, pivotIndex - 1);
        ArrayQuickSort(array, pivotIndex + 1, high);
    }
}
//* merge sort ================================================================

/*
? i think that there is a better solution for this function
? but i don't want to think about it now

? i had to make two functions for increasing and decreasing order to avoid using if condition in the merge function
? this inhance the time complexity of the code and make it easier to read
*/
// Increasing order
void IMerge(RecordArray* array, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    
    Record* leftArray = (Record*)malloc(n1 * sizeof(Record));
    Record* rightArray = (Record*)malloc(n2 * sizeof(Record));

    // ? Copy data to temp arrays 
    for (i = 0; i < n1; i++)
        leftArray[i] = array->data[left + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = array->data[middle + 1 + j];

    // ? Merge the temporary arrays back into array[left...right]
    i = 0; // Initial index of leftArray
    j = 0; // Initial index of rightArray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (leftArray[i].id <= rightArray[j].id) {
            array->data[k] = leftArray[i];
            i++;
        } else {
            array->data[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array->data[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        array->data[k] = rightArray[j];
        j++;
        k++;
    }

    free(leftArray);
    free(rightArray);
}

// Deacreasing order
void DMerge(RecordArray* array, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    
    Record* leftArray = (Record*)malloc(n1 * sizeof(Record));
    Record* rightArray = (Record*)malloc(n2 * sizeof(Record));

    // ? Copy data to temp arrays 
    for (i = 0; i < n1; i++)
        leftArray[i] = array->data[left + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = array->data[middle + 1 + j];

    // ? Merge the temporary arrays back into array[left...right]
    i = 0; // Initial index of leftArray
    j = 0; // Initial index of rightArray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (leftArray[i].id >= rightArray[j].id) {
            array->data[k] = leftArray[i];
            i++;
        } else {
            array->data[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array->data[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        array->data[k] = rightArray[j];
        j++;
        k++;
    }

    free(leftArray);
    free(rightArray);
}


void ArrayMergeSort(RecordArray* array, int left, int right, int direction) {
    if (direction == 0) {
        if (left < right) {
            int middle = left + (right - left) / 2;

            ArrayMergeSort(array, left, middle, direction);
            ArrayMergeSort(array, middle + 1, right, direction);

            IMerge(array, left, middle, right);
        }
        return;
    }
    // decreasing order
    if (left < right) {
        int middle = left + (right - left) / 2;

        ArrayMergeSort(array, left, middle, direction);
        ArrayMergeSort(array, middle + 1, right, direction);

        DMerge(array, left, middle, right);
    }
}
