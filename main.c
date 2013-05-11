#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
#define NUMBER_MIN 0
#define NUMBER_MAX 99

int int_input(char *information);
int file_filling(FILE *file, char *which);
void file_output(char *file_name, char *info);
void numbers_remove(int bin_num, int text_num);
void new_text_file(int *text_array);

int main(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt", "(manual)");
        return 0;
    }
    FILE *text_file, *bin_file;
    int text_num = 0, bin_num = 0;
    text_file = fopen("text", "w+");
    bin_file = fopen("bin", "w");
    text_num = file_filling(text_file, "text");
    bin_num = file_filling(bin_file, "bin");
    fclose(bin_file);
    fclose(text_file);   
    file_output("text", "");
    file_output("bin", "");
    numbers_remove(bin_num, text_num);
    file_output("text", "(after del.)");
    return 0;
}

int file_filling(FILE *file, char *which)
{
    int element = 0, i = 0, j = 0;
    printf ("\n%s file filling:", which);
    printf ("\nIf you will put number > %d or < %d input will break.\n"
                                               , NUMBER_MAX, NUMBER_MIN);
    while(1) {
        element = int_input("number:");
        if (element > NUMBER_MAX || element < NUMBER_MIN) {
            break;
        }
        if (!strcmp(which, "text")) {
            fprintf(file, "%d ", element);
            i++;
        }
        else {
            fwrite(&element, sizeof(int), 1, file); 
            j++;
        } 
    }
    if (!strcmp(which, "text")) {
        return i;
    }
    return j;
}

void file_output(char *file_name, char *info)
{   
    char input_buffer[STR_MAX]; 
    FILE *file;
    int num;
    printf ("\n%s%s file output:", file_name, info);
    if (!strcmp(file_name, "text") || !strcmp(file_name, "README.txt")) {
        file = fopen(file_name, "rt");
        puts("\n");
        while (fgets(input_buffer, sizeof(input_buffer), file)) {
            printf ("%s", input_buffer);
        }
    }
    else {
        file = fopen(file_name, "rb");
        puts("\n");
        rewind(file);
        while (fread(&num, sizeof(int), 1, file)) {
            printf("%d ", num);
        }
    }
    fclose(file);
    puts("\n");
}

void numbers_remove(int bin_num, int text_num)
{
    FILE *text_file, *bin_file;
    int i, j, k, number, bin_array[bin_num], text_array[text_num + 1];
    text_file = fopen("text", "r");
    bin_file = fopen("bin", "rb");
    for (i = 0; fscanf(text_file, "%d ", &number) != EOF; i++) {
        text_array[i] = number;
    } 
    text_array[i] = -1;
    for (i = 0; fread(&number, sizeof(int), 1, bin_file); i++) {
        bin_array[i] = number;
    } 
    for (j = 0; j < bin_num; j++) {
        for (i = 0; i < text_num; i++) {
            if (text_array[i] == bin_array[j]) {
                for (k = i; k < text_num; k++)
                    text_array[k] = text_array[k + 1];
                i --;
            }
        }
    }
    fclose(text_file);
    fclose(bin_file);
    new_text_file(text_array);
}

void new_text_file(int *text_array)
{
    int i ;
    FILE *text_file;
    text_file = fopen("text", "wt");
    for (i = 0 ; text_array[i] != -1; i++) {
        fprintf(text_file, "%d ", text_array[i]);
    }
    fclose(text_file);
}

int int_input(char *information)
{
    int input_text;
    char input_buffer[STR_MAX];
    printf("%s ", information);
    while (1) {
        fgets(input_buffer, STR_MAX, stdin);
        input_buffer[strlen(input_buffer)-1]='\0';
        if (!(input_text = atoi(input_buffer))) {
            if (!strcmp(input_buffer, "0")) {
                input_text = 0;
                return input_text;
        }
            puts("Invalid input, try again.");
        }
        else {
            break;
        }
    }
    return input_text;
}