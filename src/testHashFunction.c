/**
 * @file testHashFunction.c
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing implementation of unit testing of hash function
 */

#include "HashTableAPI.h"
#include <string.h>

int hashFunction(size_t tableSize, char* key);
void destroyData(void *data);
void printData(void *toBePrinted);
void displayTable(HTable *newHTable);
char *strMalloc(char *str);

int main(int argc, char **argv)
{
    HTable *newHTable;

    printf("*******************Start Testing Section*******************\n\n");

    newHTable = createTable(100, hashFunction, destroyData, printData);

    insertData(newHTable, strMalloc("January"), strMalloc("1"));
    insertData(newHTable, strMalloc("February"),strMalloc("2"));
    insertData(newHTable, strMalloc("March"),strMalloc("3"));
    insertData(newHTable, strMalloc("April"),strMalloc("4"));
    insertData(newHTable, strMalloc("May"),strMalloc("5"));
    insertData(newHTable, strMalloc("June"), strMalloc("6"));
    insertData(newHTable, strMalloc("July"),strMalloc("7"));
    insertData(newHTable, strMalloc("August"),strMalloc("8"));
    insertData(newHTable, strMalloc("September"),strMalloc("9"));
    insertData(newHTable, strMalloc("October"), strMalloc("10"));
    insertData(newHTable, strMalloc("November"),strMalloc("11"));
    insertData(newHTable, strMalloc("December"), strMalloc("12"));

    displayTable(newHTable);
    destroyTable(newHTable);

    return 0;
}

void destroyData(void *data)
{
    free(data);
}

int hashFunction(size_t tableSize, char *key)
{
    int i = 0, sum = 0;

    for (i=0; key[i]!='\0'; i++)
    {
        sum += key[i];
    }
    return sum % tableSize;
}

void printData(void *toBePrinted)
{
    printf("%d ", *((int*)toBePrinted));
}

void displayTable(HTable *hashTable)
{
    int i;

    printf("---Display the Hash Table---\n");

    for (i=0; i<hashTable->size; i++)
    {
        if(hashTable->table[i] != NULL)
        {
            Node *tempNode = hashTable->table[i];

            while(tempNode)
            {
                printf("Table[%d]\tKey: %s\tData: %s\n",i,tempNode->key,(char*)(tempNode->data));
                tempNode = tempNode->next;
            }
        }
    }
}

char *strMalloc(char *str)
{
    char *newStr;
    newStr = malloc(sizeof(char)*(strlen(str)+1));
    strcpy(newStr,str);
    return newStr;
}
