#include <stdio.h>
#include <stdlib.h> // For exit() function
int main()
{
    char data[1000];
    FILE *fptr;

    if ((fptr = fopen("food_nutrient_db.csv", "r")) == NULL)
    {
        printf("Error opening file, please try again with the correct file.");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }

   else {
		HashList *list = createHashTable(hashListSize);
		while (fgets(readString,MAX_NAME -1, fp) != NULL) {
			addToHashList(list, readString);
		}
		fclose(fp);

    // reads text until newline 
    fscanf(fptr,"%[^\n]", c);

    printf("Data from the file:\n%s", c);
    fclose(fptr);
    
    return 0;
}