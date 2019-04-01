// to print 
int c;
FILE *file;
file = fopen("test.txt", "r");
if (file) {
    while ((c = getc(file)) != EOF)
        putchar(c);
    fclose(file);
}