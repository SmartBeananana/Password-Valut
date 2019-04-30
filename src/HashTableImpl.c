/**
 * @file HashTableImpl.c
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing implementation of hash table
 */

 #include <string.h>
 #include "HashTableAPI.h"

 HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char *key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
 {
     HTable *newHTable;
     int i;

     newHTable = malloc(sizeof (HTable));

     if(newHTable == NULL)
         return NULL;

     newHTable->table = malloc(size * sizeof(Node *));

     if(newHTable->table == NULL)
         return NULL;

     for(i=0; i<size; i++)
     {
         newHTable->table[i] = NULL;
     }

     newHTable->destroyData = destroyData;
     newHTable->hashFunction = hashFunction;
     newHTable->printData = printData;
     newHTable->size = size;

     return newHTable;
 }

 Node *createNode(char *key, void *data)
 {
     Node *newNode;

     newNode = malloc(sizeof (Node) );

     if(newNode == NULL)
         return NULL;

     newNode->next = NULL;
     newNode->key = key;
     newNode->data = data;

     return newNode;
 }

 void destroyTable(HTable *hashTable)
 {
     int i;
     if(hashTable == NULL)
         return;

     if(hashTable->table == NULL)
     {
         free(hashTable);
         return;
     }

     for(i=0; i<(hashTable->size); i++)
     {
         Node *tempNode = hashTable->table[i];

         while(tempNode)
         {
             Node *tempDeleteNode = tempNode;
             tempNode = tempNode->next;
             hashTable->destroyData(tempDeleteNode->data);
             free(tempDeleteNode->key);
             free(tempDeleteNode);
         }
     }
     free(hashTable->table);
     free(hashTable);
 }

 void insertData(HTable *hashTable, char *key, void *data)
 {
     size_t index;
     Node *newNode;

     if(hashTable != NULL)
     {
         index = hashTable->hashFunction(hashTable->size, key);

         if(hashTable->table[index] != NULL)
         {

             Node **temp = &(hashTable->table[index]);
             while(*temp)
             {
                 if(strcmp((*temp)->key, key) == 0)
                 {
                     hashTable->destroyData((*temp)->data);
                     (*temp)->data = data;
                     return;
                 }
                 temp = &((*temp)->next);
             }
             newNode = createNode(key, data);
             *temp = newNode;
         }
         else
         {
             hashTable->table[index] = createNode(key, data);
         }
     }
 }

 void removeData(HTable *hashTable, char *key)
 {
     size_t index;

     if(hashTable != NULL)
     {
          index = hashTable->hashFunction(hashTable->size, key);

          if(hashTable->table[index] != NULL)
          {
              Node **tempNode = &(hashTable->table[index]);

              while(*tempNode)
              {
                  if(strcmp((*tempNode)->key, key) == 0)
                  {
                      Node *tempDeleteNode = *tempNode;
                      *tempNode = (*tempNode)->next;
                      hashTable->destroyData(tempDeleteNode->data);
                      free(tempDeleteNode->key);
                      free(tempDeleteNode);
                      return;
                  }
                  tempNode = &((*tempNode)->next);
              }
          }
     }
 }

 void *lookupData(HTable *hashTable, char *key)
 {
    size_t index;
    if(hashTable != NULL)
    {
        index = hashTable->hashFunction(hashTable->size, key);

        if(hashTable->table[index] == NULL)
            return NULL;

        Node *tempNode = hashTable->table[index];
        while(tempNode)
        {
            if(strcmp(tempNode->key, key) == 0)
            {
                return tempNode->data;
            }
            tempNode = tempNode->next;
        }
    }
    return NULL;
 }
