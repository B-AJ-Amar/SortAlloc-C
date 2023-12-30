// ? Libraries ====================================================================
#include <stdlib.h>
#include <string.h>
#include "sort.h" // my sort library

/*
? in this functions (sort functions ) i could make them shorter by using condition in the loops
? insead of reapeating the code twice 
? but this inhance the time complexity of the code
? because the condition will be checked every time the loop run 
*/

// ! i didn't make sort algorithms for binary tree because its already sorted


// ! there is a problem in quicksort Linked lists i will ix it later

void ArraySort(RecordArray* array, int direction, int sortAlgorithm) {
    int sortTypes = 5;
    if (sortAlgorithm % sortTypes == 0) ArrayBubbleSortById(array, direction);
    else if (sortAlgorithm % sortTypes == 1) ArraySelectionSortById(array, direction);
    else if (sortAlgorithm % sortTypes == 2) ArrayInsertionSortById(array, direction);
    else if (sortAlgorithm % sortTypes == 3) ArrayQuickSort(array, 0, array->length - 1); //TODO: add direction
    else if (sortAlgorithm % sortTypes == 4) ArrayMergeSort(array, 0, array->length - 1,direction);

}

void LLSort(RecordLinkedList* list, int direction, int sortAlgorithm) {
    int sortTypes = 5;
    if (sortAlgorithm % sortTypes == 0) bubbleSortLinkedList(list, direction);
    else if (sortAlgorithm % sortTypes == 1) selectionSortLinkedList(list, direction);
    else if (sortAlgorithm % sortTypes == 2) insertionSortLinkedList(list, direction);
    else if (sortAlgorithm % sortTypes == 3) quickSortUtil(list->head, list->tail);
    else if (sortAlgorithm % sortTypes == 4) mergeSortLinkedList(&(list->head),direction);
}
// ? =============================================================================
// ? Array
// ? =============================================================================



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
// ? =============================================================================
// ? Linked List
// ? =============================================================================




void swapRecordsLL(Record* a, Record* b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

void swapRecords(RecordNode* a, RecordNode* b) {
    Record temp = a->data;
    a->data = b->data;
    b->data = temp;
}
// * bubble sort ==============================================================
void bubbleSortLinkedList(RecordLinkedList* list,int direction) {
    int swapped;
    RecordNode* ptr1;
    RecordNode* lptr = NULL;

    if (list->head == NULL) return;
    // dec order
    if (!direction){
        do {
            swapped = 0;
            ptr1 = list->head;

            while (ptr1->next != lptr) {
                // Compare adjacent records and swap if necessary
                if (ptr1->data.id > ptr1->next->data.id) {
                    swapRecordsLL(&(ptr1->data), &(ptr1->next->data));
                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
        return;
    }
    // inc order
    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) {
            // Compare adjacent records and swap if necessary
            if (ptr1->data.id < ptr1->next->data.id) {
                swapRecordsLL(&(ptr1->data), &(ptr1->next->data));
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// * selection sort ===========================================================

void swapRecordNodesLL(RecordNode* a, RecordNode* b) {
    Record temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void selectionSortLinkedList(RecordLinkedList* list,int direction) {
    RecordNode* current;
    RecordNode* index;
    RecordNode* min;


    if(list->head == NULL) return;
    // increasing order
    if (direction){
        for (current = list->head; current->next != NULL; current = current->next) {
            min = current;

            for (index = current->next; index != NULL; index = index->next) {
                if (index->data.id < min->data.id) {
                    min = index;
                }
            }
            swapRecordNodesLL(current, min);
        }
        return;
    }
    // decreasing order
    for (current = list->head; current != NULL; current = current->next) {
        min = current; // this var should be the max but because min is already declared i will use it

        for (index = current->next; index != NULL; index = index->next) {
            if (index->data.id > min->data.id) {
                min = index;
            }
        }
        swapRecordNodesLL(current, min);
    }
}

// * insertion sort ===========================================================

void insertionSortLinkedList(RecordLinkedList* list,int direction) {
    RecordNode* current = list->head;
    RecordNode* sorted = NULL;
    if (list->head == NULL) return;

    // increasing order
    if(direction){
        while (current != NULL) {
            RecordNode* next = current->next;

            // Move the current node to the sorted part of the list
            if (sorted == NULL || sorted->data.id > current->data.id) {
                current->next = sorted;
                sorted = current;
            } else {
                // Search for the correct position in the sorted part
                RecordNode* temp = sorted;
                while (temp->next != NULL && temp->next->data.id < current->data.id) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next;
        }

        list->head = sorted;
        return;
    }
    // decreasing order
    while (current != NULL) {
        RecordNode* next = current->next;

        // Move the current node to the sorted part of the list
        if (sorted == NULL || sorted->data.id < current->data.id) {
            current->next = sorted;
            sorted = current;
        } else {
            // Search for the correct position in the sorted part
            RecordNode* temp = sorted;
            while (temp->next != NULL && temp->next->data.id > current->data.id) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    list->head = sorted;
}


// * quick sort ================================================================


// Function to partition the linked list and return the pivot node
// patitionLLQS = partition linked list quick sort
RecordNode* getTail(RecordNode* current) {
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    return current;
}

// Function to partition the linked list and return the pivot node
RecordNode* partitionLL(RecordNode* head, RecordNode* end, RecordNode** newHead, RecordNode** newEnd) {
    RecordNode* pivot = end;
    RecordNode* prev = NULL, *current = head, *tail = pivot;

    while (current != pivot) {
        if (current->data.id <= pivot->data.id) {
            if (*newHead == NULL)
                *newHead = current;

            prev = current;
            current = current->next;
        } else {
            if (prev)
                prev->next = current->next;
            RecordNode* temp = current->next;
            current->next = NULL;
            tail->next = current;
            tail = current;
            current = temp;
        }
    }

    if (*newHead == NULL)
        *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

// Recursive function to implement quicksort for a linked list
RecordNode* quickSortUtil(RecordNode* head, RecordNode* end) {
    if (!head || head == end)
        return head;

    RecordNode* newHead = NULL, *newEnd = NULL;

    RecordNode* pivot = partitionLL(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        RecordNode* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;

        newHead = quickSortUtil(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortUtil(pivot->next, newEnd);

    return newHead;
}

// Function to sort a linked list using quicksort
void quickSort(RecordLinkedList* list) {
    list->head = quickSortUtil(list->head, getTail(list->head));
}

// * merge sort ================================================================
RecordNode* IMergeLinkedList(RecordNode* left, RecordNode* right) {
    RecordNode* result = NULL;

    if (left == NULL)
        return right;
    if (right == NULL)
        return left;

    if (left->data.id <= right->data.id) {
        result = left;
        result->next = IMergeLinkedList(left->next, right);
    } else {
        result = right;
        result->next = IMergeLinkedList(left, right->next);
    }

    return result;
}

RecordNode* DMergeLinkedList(RecordNode* left, RecordNode* right) {
    RecordNode* result = NULL;

    if (left == NULL)
        return right;
    if (right == NULL)
        return left;

    if (left->data.id >= right->data.id) {
        result = left;
        result->next = DMergeLinkedList(left->next, right);
    } else {
        result = right;
        result->next = DMergeLinkedList(left, right->next);
    }

    return result;
}

// Function to split the linked list into two halves
void splitList(RecordNode* head, RecordNode** left, RecordNode** right) {
    if (head == NULL || head->next == NULL) {
        *left = head;
        *right = NULL;
        return;
    }

    RecordNode* slow = head;
    RecordNode* fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

// Function to perform merge sort on a linked list
void mergeSortLinkedList(RecordNode** head,int direction) {
    RecordNode* h = *head;
    RecordNode* left;
    RecordNode* right;

    if (h == NULL || h->next == NULL)
        return;

    splitList(h, &left, &right);

    if (!direction){

        mergeSortLinkedList(&left,0);  // Recursively sort the left half
        mergeSortLinkedList(&right,0); // Recursively sort the right half

        *head = IMergeLinkedList(left, right);  // Merge the sorted halves
    }
    else {
        mergeSortLinkedList(&left,1);  // Recursively sort the left half
        mergeSortLinkedList(&right,1); // Recursively sort the right half

        *head = DMergeLinkedList(left, right);  // Merge the sorted halves
    }
}
