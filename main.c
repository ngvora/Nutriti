//Nutrition Diary Log System - Nehal Vora CS201
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // For exit() function
#include <string.h>
#include "string.h"
#include "UNORDEREDMAP.h"
#include "ROW.h"
#include "dynarr.h"

void keywordSplit(STRING* name, ROW* row, UNORDEREDMAP* index);
bool insert(ROW* row);

int main()
{
    FILE* fp = fopen("food_nutrient_db.csv", "r");

    DA* rowList = newDA(freeROW);

    UNORDEREDMAP* nameIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, freeDA);
    UNORDEREDMAP* vendorIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, freeDA);
    UNORDEREDMAP* keywordIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, freeDA);

    UNORDEREDMAP* diaryNameIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, freeDA);
    UNORDEREDMAP* vendorIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, freeDA);
    UNORDEREDMAP* keywordIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, freeDA);

    size_t next = 0;

    while (!feof(fp))
    {
        ROW* row = readROW(fp);

        if (getROWid(row) > next)
            next = getROWid(row);

        //printf("%zu %s %s\n", getROWid(row), getSTRING(getROWname(row)), getSTRING(getROWvendor(row)));
        insertDAback(rowList, row);

        void* nameResult = searchUNORDEREDMAP(nameIndex, getROWname(row), NULL);

        if (nameResult == NULL)
        {
            DA* matches = newDA(NULL);
            insertDAback(matches, row);
            insertUNORDEREDMAP(nameIndex, getROWname(row), matches, NULL);
        }

        else
        {
            DA* matches = (DA*)nameResult;
            insertDAback(matches, row);
        }
        
        void* vendorResult = searchUNORDEREDMAP(vendorIndex, getROWvendor(row), NULL);

        if (vendorResult == NULL)
        {
            DA* matches = newDA(NULL);
            insertDAback(matches, row);
            insertUNORDEREDMAP(vendorIndex, getROWvendor(row), matches, NULL);
        }

        else
        {
            DA* matches = (DA*)vendorResult;
            insertDAback(matches, row);
        }

        keywordSplit(getROWname(row), row, keywordIndex);
    }

    fclose(fp);

    char ch;
    scanf("%c", &ch);

    while (ch != 'q')
    {
        STRING* str = readSTRING(stdin, " ~\n", NULL);

        while (sizeSTRING(str) == 0)
        {
            freeSTRING(str);
            str = readSTRING(stdin, " ~\n", NULL);
        }

        UNORDEREDMAP* index;

        switch (ch)
        {
        case 'v':
            index = vendorIndex;
            break;
        case 'n':
            index = nameIndex;
            break;
        case 'k':
            index = keywordIndex;

            for (size_t i = 0; i < sizeSTRING(str); i++)
            {
                setSTRINGchar(str, i, toupper(getSTRINGchar(str, i)));
            }

            printf("Query: {%s}\n", getSTRING(str));

            break;
        default:
            printf(":-(\n");
            scanf("%c", &ch);
            continue;
        }

        DA* results = searchUNORDEREDMAP(index, str, NULL);

        if (results == NULL)
        {
            printf("No results\n");
        }

        else
        {
            for (size_t i = 0; i < sizeDA(results); i++)
            {
                ROW* row = getDA(results, i);

                printf("%zu %s %s\n", getROWid(row), getSTRING(getROWname(row)), getSTRING(getROWvendor(row)));
            }
        }
        

        scanf("%c", &ch);
    }

    FILE *fptrread;
    FILE *fwriter;
    FILE *freadr;
    //make sure hashtable has a row of number beside it

    if ((fptrread = fopen("food_nutrient_db.csv", "r")) == NULL)
    {
        printf("Error opening file, please try again with the correct file.\n");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }

int choice, choice1, choice2;
char *diaryname;
char *searchval;
char *searchmanu;
while(1)
{
printf("\nEnter 1 to create a new user diary.\n");
printf("Enter 2 to update an existing user diary.\n");
printf("Enter 3 to delete an existing user diary.\n");
printf("Enter 4 to Exit.\n");
printf("Your choice?\n");

if (scanf("%d",&choice) != 1) {
    printf("Invalid input >:-(\n");
    continue;
}
switch(choice)
{
case 1:
printf("What would you like your new user diary to be named?\n");
scanf("%s",diaryname);
printf("\nCreating User Diary %s\n",diaryname);
printf("\n");
/*creating file*/
    fwriter=fopen(diaryname,"w");
    /*check file created or not*/
    if(fwriter==NULL)
    {
        printf("File not created, please try again");
        break;
    }
 
    printf("File created successfully \n");
    break;
    /*writting into file
    int x = 0;
    while(x!=1){
    printf("Enter 1 to add an item to the log\n Enter 2 to delete an item from the log\n Enter 3 to go back to the Menu");
    printf("\nYour choice?\n");
    scanf("%d",&choice1);
    switch(choice1){
        case 1:
        printf("\nPlease enter the name of the item you would like to add.\n");
        scanf("%s",searchval);
        //searchfunction
        //display search array on the screen with a number beside it
       /* printf("Enter 1 to filter your search for a specific manufacturer, or 0 to skip");
        scanf("%d",choice2);
        switch (choice2)
        {
            case 0:
                break;
            case 1:
            printf(\n"Please enter the name of the manufacturer."\n);
            scanf("%s",searchmanu);
            //search function for manufacturer
            //display search results
            default:
                printf("Incorrect Choice");
                break;
        }

        int i;
        printf("\nPlease enter the number that matches your selection:\n");
        scanf("%d",&i);
        // insert the value from the search results that matches the value i to diaryname file line by line
        break;

        case 2:
         fwriter = fopen(diaryname,"r");
        // Read contents from file 
        printf("\nDisplaying the contents of the file for deletion. \n");
        //display contents of file line by line with number beside it
         char c = fgetc(fwriter); 
        while (c != EOF) 
           { 
        printf ("%c", c); 
        c = fgetc(fwriter); 
             } 
        int j;
        printf("\nPlease enter the number that matches the item you want to delete in the file:\n");
        scanf("%d",&j);
        // delete the value from the search results that matches the number j in diaryname file
        break;
        case 3:
        x = 1;
        break;
        default:
        printf("Invalid Choice");
        break;
        */
case 2:
printf("\n Please enter the name of the User Diary you need to update: \n");
scanf("%s",diaryname);
if (diaryname)
freadr=fopen(diaryname,"r");
    /*check if file is created or not*/
    if(freadr==NULL)
    {
        printf("File does not exist, please try again\n");
        break;
    }
    fclose(freadr);
    printf("\nUser diary found, opening log:\n");
    /*writing into file*/
    freadr=fopen(diaryname,"w");
   /*writting into file
    int x = 0;
    while(x!=1){
    printf("Enter 1 to add an item to the log\n Enter 2 to delete an item from the log\n Enter 3 to go back to the Menu");
    printf("\nYour choice?\n");
    scanf("%d",&choice1);
    switch(choice1){
        case 1:
        printf("\nPlease enter the name of the item you would like to add.\n");
        scanf("%s",searchval);
        //searchfunction
        //display search array on the screen with a number beside it
       /* printf("Enter 1 to filter your search for a specific manufacturer, or 0 to skip");
        scanf("%d",choice2);
        switch (choice2)
        {
            case 0:
                break;
            case 1:
            printf(\n"Please enter the name of the manufacturer."\n);
            scanf("%s",searchmanu);
            //search function for manufacturer
            //display search results
            default:
                printf("Incorrect Choice")
                break;
        }

        int i;
        printf("\nPlease enter the number that matches your selection:\n");
        scanf("%d",&i);
        // insert the value from the search results that matches the value i to diaryname file line by line
        break;

        case 2:
         fwriter = fopen(diaryname,"r");
        // Read contents from file 
        printf("\nDisplaying the contents of the file for deletion. \n");
        //display contents of file line by line with number beside it
         char c = fgetc(fwriter); 
        while (c != EOF) 
           { 
        printf ("%c", c); 
        c = fgetc(fwriter); 
             } 
        int j;
        printf("\nPlease enter the number that matches the item you want to delete in the file:\n");
        scanf("%d",&j);
        // delete the value from the search results that matches the number j in diaryname file
        break;
        case 3:
        x = 1;
        break;
        default:
        printf("Invalid Choice");
        break;
        */
break; //Takes control out of switch
case 3:
printf("\n Please enter the name of the User Diary you need to delete: \n");
scanf("%s",diaryname);
freadr=fopen(diaryname,"r");
    /*check file exists or not*/
    if(freadr==NULL)
    {
        printf("\nFile does not exist, please try again\n");
        break;
    }
  int status=1;
  status = remove(diaryname);
 
  if (status == 0)
  {
    printf("\n%s file deleted successfully.\n", diaryname);
  }
  else
  {
    printf("\nUnable to delete the file\n"); 
  }

break; //Takes control out of switch
default:
printf("Incorrect choice input, please try again!");
exit(1);
}
}
    return 0;
}

void keywordSplit(STRING* name, ROW* row, UNORDEREDMAP* index)
{
    STRING* temp = cloneSTRING(name);
    char* data = getSTRING(temp);
    data = strtok(data, " ");

    while ((data = strtok(NULL, " ")) != NULL)
    {
        STRING* keyword = newSTRING(data);

        DA* array = searchUNORDEREDMAP(index, keyword, NULL);

        if (array == NULL)
        {
            array = newDA(freeSTRING);
            insertDAback(array, row);
            insertUNORDEREDMAP(index, keyword, array, NULL);
        }

        else
        {
            insertDAback(array, row);
            freeSTRING(keyword);
        }
    }

    freeSTRING(temp);
}
