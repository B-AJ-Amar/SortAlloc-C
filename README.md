# SortAlloc-C

This C language project focuses on analyzing and comparing various file allocation methods and sorting algorithms. The aim is to provide students with an opportunity to explore the advantages and disadvantages of different file allocation strategies and sorting algorithms while enhancing their programming skills in C.

## Getting Started
### Prerequisites

- Ensure you have a C compiler installed (e.g., GCC).
### Installation
0. **note:** if you have the `makefile` you can skip to step 3
1. Clone the repository:

    ```bash
     git clone https://github.com/B-AJ-Amar/SortAlloc-C.git
    ```

2. create makefile :
    - for linux || mac :
      ```bash
      Scripts/Setup-Linux.sh
      ```
    - for windows
      ```bash
        Scripts\Setup-Windows.bat
      ```
3. make :
    ```bash
      make
      ```
      **Note:** if you get an error whene you `make`, go to `./App.make` and add to it `CC=gcc`

4. Run the program:

    ```bash
    ./bin/debug/App.exe
    ```
## Usage
- Follow the instructions displayed on the console or terminal interface.
- Input data and observe the program's output.
## Project Requirements

### Made By 
| Modules                             | Professor                |
| ----------------------------------- | ------------------------ |
| File Structure and Data Structure   | Dr. Hannousse Abdelhakim |
| Algorithms and Complexity           | Dr. Chohra Chemseddine   |

### Objective
Development of a program in C language aimed at analyzing and comparing the different methods of
allocating files in central memory as well as the different sorting algorithms. This mini project will allow
students to explore and understand the advantages and disadvantages of various file allocation methods and
sorting algorithms, while developing their C language programming skills.

### Description 
The program must present an interactive main menu offering the user the following options:
1. Selection of a structured file (set of records).
2. Choosing a memory file allocation method:
     - Array
     - Linked List
     - Binary Tree
4. Indication of the use (or not) of a hash function for loading. For this step, the use of the open
  addressing technique (linear or double hashing) will be proposed, accompanied by an adapted
  hashing function.
5. Specifying the sorting method to apply to the file data: 
     - Bubble sort.
     - selection sort
     - insertion sort
     - Merge sort
     - Quick sort.
6. Generating an execution report - the program will record the execution times for each loading and
  sorting operation. These results will be recorded in a CSV file, detailing for each line the file
  allocation method, the use or not of a hashing method and the sorting method used, as well as the
  execution times corresponding to each operation. .
