****************************************************
Your name		    Xiangyuan Lian
The class name		Password Vault password vault/Assignment 2
The date			lianx@uoguelph.ca
****************************************************


************************
Program Description
**************************
 This program stores passwords by using hash table with linked list. User can
 creat new file for storing, editing and removing passwords. For existing file,
 user can access and edit the file content by entering the right master password.

************
Compilation
************
 To compile this code:
 run: make test

 To compile the testing program:
 run: make testHash

  Detailed Make options:

  make cppcheck runs the cppcheck option
  make test compiles the program with the library
  make doxy creates the doxygen documentation in the docs subdirectory
  make clean removes executable files

****************************
Known Limitations, Issues and Errors
****************************

 make cppcheck error: "memory leak: newHTable".
 make valgrind -v: no error reported

 Hash Table Time Complexity:
 creatTable     O(n): malloc for new tables and initialize to null and sets the function pointer.
 creatNode      O(1): malloc a new node and sets the function pointer. constant time.
 destoryTable   O(n): delete the table by using destroyData() and go through the whole list node by node.
 insertData     O(1): insert one node to the table each time.
 removeData     O(1): remove one node from the list.
 lookupData     O(1): look for the data by traversing the linked list.
 hashFunction   O(n): loop through the string and evenly distributes the data on the hash table. 
