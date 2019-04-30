/**
 * @file main.c
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing the implementation of the password Vault
 */

 #include "HashTableAPI.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #define MASTERPASS "MASTER&~\n"
 #define MAX 200

 int hashFunction(size_t tableSize, char *key);
 void destroyData(void *data);
 void printData(void *toBePrinted);
 void creatMasterPass(HTable *hashTable);
 void managePasswords();
 void displayTable(HTable *hashTable);
 void removeNewLine(char *input);
 int isBlank(char *input);

 int main(int arg, char**argv)
 {
     FILE *fin, *fout;
     char menu[MAX],fileName[MAX],*sysDescriptor,*password,checkMaster[MAX],*r;
     HTable *writeToHTable, *readFromHTable;

     do
     {
         printf("\n---Welcome to iPassword Vault---\n");
         printf("\n\t***Main Menu***\n");
         printf("->Enter 'new' to creat a new file\n");
         printf("->Enter 'find' to open an exist file\n");
         printf("->Enter 'q' to quit the program\n");
         printf("->Enter:");
         fgets(menu,MAX,stdin);
         removeNewLine(menu);
         printf("\n");

         if(strcmp(menu, "new") == 0)
         {
             printf("* *Creat a new file* *\n");
             do
             {
                 do
                 {
                     do
                     {
                         printf("->Enter the path for the new file:");
                         fgets(fileName,MAX,stdin);
                     } while(isBlank(fileName) == 1);

                     fout = fopen(fileName,"rb");
                     if(fout)
                     {
                         printf("---File already exists---\n");
                         fclose(fout);
                     }
                     } while(fout);

                     fout = fopen(fileName, "wb+");

                     if(!fout)
                     {
                         printf("\n---Unable open the file---\n");
                     }
                } while(!fout);

             writeToHTable = createTable(100, hashFunction, destroyData, printData);
             creatMasterPass(writeToHTable);
             managePasswords(writeToHTable, fout);

             fclose(fout);
             destroyTable(writeToHTable);
         }
         else if(strcmp(menu, "find") == 0)
         {
              printf("* *Find an existing file* *\n");
              do
              {
                  printf("->Enter the existing file name:");
                  fgets(fileName,MAX,stdin);

                  fin = fopen(fileName, "rb");
                  if(!fin)
                  {
                      printf("---Unable open the file---\n");
                  }
              } while(!fin);

              readFromHTable = createTable(100, hashFunction, destroyData, printData);

              sysDescriptor = malloc(sizeof(char)*MAX);
              r = fgets(sysDescriptor,MAX,fin);

              password = malloc(sizeof(char)*MAX);
              fgets(password,MAX,fin);

              insertData(readFromHTable,sysDescriptor,password);
              do
              {
                  do
                  {
                  printf("\n->Enter the master password of the file:");
                  fgets(checkMaster,MAX,stdin);
                  } while(isBlank(checkMaster) == 1);

                  if(strcmp(checkMaster,password) != 0)
                  {
                      do
                      {
                      printf("\n---Incorrect password---\n\n");
                      printf("->Enter 'back' go back to the main menu\n");
                      printf("->Any other key to try again\n");
                      printf("->Enter:");
                      fgets(menu,MAX,stdin);
                      removeNewLine(menu);
                      } while(isBlank(menu) == 1);
                  }
                  else
                  {
                      printf("\n---Correct password---\n\n");
                      while(1)
                      {
                        sysDescriptor = malloc(sizeof(char)*MAX);
                        r = fgets(sysDescriptor,MAX,fin);
                        if(r == NULL)
                        {
                            free(sysDescriptor);
                            break;
                        }
                        password = malloc(sizeof(char)*MAX);
                        fgets(password,MAX,fin);
                        insertData(readFromHTable,sysDescriptor,password);
                      }
                      fclose(fin);

                      fout = fopen(fileName,"wb");
                      if(!fout)
                      {
                          printf("\n---Unable open the file---\n\n");
                          break;
                      }
                      managePasswords(readFromHTable,fout);
                      destroyTable(readFromHTable);
                      fclose(fout);
                      break;
                  }

              } while(strcmp(menu,"back") != 0);

              if(strcmp(menu,"back") == 0)
              {
                  destroyTable(readFromHTable);
                  fclose(fin);
              }
         }
         else if(strcmp(menu,"q") == 0)
         {
              printf("\n---BYE BYE---\n");
         }
         else
         {
              printf("\nInvaild Input. Please try again!\n");
         }
       printf("\n");
   } while(strcmp(menu, "q") != 0);

     return 0;
 }

 void destroyData(void *data)
 {
     free(data);
 }

 int hashFunction(size_t tableSize, char *key)
 {
     int i = 0, sum = 0;

     if(strcmp(key, MASTERPASS) == 0)
         return 0;

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

 void creatMasterPass(HTable *hashTable)
 {
     char *sysDescriptor, *password;

     do
     {
         sysDescriptor = malloc(sizeof(char)*MAX);
         strcpy(sysDescriptor,MASTERPASS);
         printf("->Enter the master password to secure your file:");
         password = malloc(sizeof(char)*MAX);
         fgets(password, MAX, stdin);
     } while(isBlank(password) == 1);

     insertData(hashTable,sysDescriptor,password);
 }

 void managePasswords(HTable *hashTable, FILE *fp)
 {
     char choice[MAX], toBeRemoved[MAX], toBeRet[MAX], *sysDescriptor,*password,*temp,retTemp[MAX];
     int i;

     do
     {
         printf("\n->Enter 'add' to add a new system and password\n");
         printf("->Enter 'ret' to retrieve password\n");
         printf("->Enter 'rm' to remove an entire system\n");
         printf("->Enter 'main' go back to the main menu\n");
         printf("->Enter:");
         fgets(choice,MAX,stdin);
         removeNewLine(choice);
         printf("\n");

         if(strcmp(choice, "add") == 0)
         {
             printf("* *To add a new password* *\n");
             do
             {
             printf("-> Enter the name:");
             sysDescriptor = malloc(sizeof (char)*MAX);
             fgets(sysDescriptor,MAX,stdin);
             } while(isBlank(sysDescriptor) == 1);

             do
             {
             printf("-> Enter the password:");
             password = malloc(sizeof(char)*MAX);
             fgets(password,MAX,stdin);
             } while(isBlank(password) == 1);

             insertData(hashTable, sysDescriptor, password);
             temp = lookupData(hashTable, sysDescriptor);
             if(strcmp(password,temp) == 0)
             {
                 printf("---Add password successfully---\n\n");
             }
             else
             {
                 printf("---Add password failed---\n\n");
             }
         }
         else if(strcmp(choice, "ret") == 0)
         {
             do
             {
             printf("* *To retrieve password* *\n");
             printf("-> Enter the name:");
             fgets(toBeRet,MAX,stdin);
           } while(isBlank(toBeRet) == 1);

             password = lookupData(hashTable, toBeRet);

             if(password == NULL)
             {
                 printf("\n---The password not exit. Try again!---\n\n");

             }
             else
             {
                 strcpy(retTemp,toBeRet);
                 removeNewLine(retTemp);
                 printf("Name: %s, Password: %s\n", retTemp, password);
             }
         }
         else if(strcmp(choice, "rm") == 0)
         {
             do {
             printf("* *To remove a password* *\n");
             printf("->Enter the name:");
             fgets(toBeRemoved,MAX,stdin);
           } while(isBlank(toBeRemoved) == 1);

             if(lookupData(hashTable, toBeRemoved) == NULL)
             {
                 printf("\n---The password is not exist---\n\n");
             }
             else if(strcmp(toBeRemoved,MASTERPASS) == 0)
             {
                 printf("\n---Invalid Input---\n\n");
             }
             else
             {
                 removeData(hashTable, toBeRemoved);

                 if(lookupData(hashTable, toBeRemoved) == NULL)
                 {
                     printf("\n---Remove data successfully---\n\n");
                 }
                 else
                 {
                     printf("\n---Remove data failed---\n\n");
                 }
             }
         }
         else if(strcmp(choice, "main") == 0)
         {
             printf("\n---Back to the main menu--->>>\n");
         }
         else
         {
             printf("\n---Invaild Input---\n");
         }
     } while(strcmp(choice, "main") != 0);

     for (i=0; i<hashTable->size; i++)
     {
       if(hashTable->table[i] != NULL)
       {
           Node *tempNode = hashTable->table[i];

           while(tempNode)
           {
              fwrite(tempNode->key,sizeof(char),strlen(tempNode->key),fp);
              fwrite(tempNode->data,sizeof(char),strlen(tempNode->data),fp);
              tempNode = tempNode->next;
           }
        }
     }

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
                 printf("Name: %s password: %s\n", tempNode->key,(char*)(tempNode->data));
                 tempNode = tempNode->next;
             }
         }
     }
 }

 void removeNewLine(char *input)
 {
     int length;

     length = strlen(input);

     if(input[length-1] == '\n')
     {
         input[length-1] = '\0';
     }
 }

 int isBlank(char *input)
 {
     int i;

     for (i=0; i<strlen(input);i++)
     {
         if(isblank(input[i]) == 0 && input[i] != '\n')
         {
             return 0;
         }
     }
     printf("---Blank is invalid---\n");
     return 1;
 }
