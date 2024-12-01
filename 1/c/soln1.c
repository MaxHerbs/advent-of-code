#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int getNumberOfLines(FILE *file);
int parse_data(FILE *file, int *col1, int *col2, int num_lines);
int compare(const void *a, const void *b);

int main()
{
    FILE *data = fopen("data.txt", "r");
    if (data == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int lines = getNumberOfLines(data);

    int diff = 0;
    printf("Number of lines: %d\n", lines);

    // Arrays to store the data values, and keep track of visited locations
    int *col_1 = malloc(sizeof(int) * lines);
    int *col_1_visited = malloc(sizeof(int) * lines);

    int *col_2 = malloc(sizeof(int) * lines);
    int *col_2_visited = malloc(sizeof(int) * lines);

    int parse_status = parse_data(data, col_1, col_2, lines);
    if (parse_status)
    {
        printf("Something went wrong parsing the data.");
        return 1;
    }

    qsort(col_1, lines, sizeof(int), compare);
    qsort(col_2, lines, sizeof(int), compare);

    for (int i = 0; i < lines; i++)
    {
      diff += abs(col_1[i] - col_2[i]);
    }

    printf("Total Diff: %d\n", diff);
    free(col_1);
    free(col_1_visited);
    free(col_2);
    free(col_2_visited);
}

int getNumberOfLines(FILE *file)
{
    int count = 0;
    char c;
    char prevC;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            count++;
        }
        prevC = c;
    }
    if (prevC != '\n' && prevC != '\0')
    {
        count++;
    }
    fseek(file, 0, SEEK_SET);
    return count;
}

int parse_data(FILE *file, int *col1, int *col2, int num_lines)
{
    int counter = 0;
    while (fscanf(file, "%d %d", &col1[counter], &col2[counter]) == 2)
    {
        counter++;
        if (counter > num_lines)
        {
            fprintf(stderr, "Reached maximum line limit of %d\n", num_lines);
            return 1;
        }
    }
    return 0;
}

int compare(const void *a, const void *b)
{
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}