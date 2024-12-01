#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int getSmallestUnvisited(int *col, int *visited, int len, int num_visited);
int isVisited(int curr_indx, int* visited, int num_visited);
int getNumberOfLines(FILE *file);
int parse_data(FILE *file, int *col1, int *col2, int num_lines);

int main()
{
    FILE *data = fopen("data.txt", "r");
    if (data == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int lines = getNumberOfLines(data);

    long long diff = 0;
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

    for (int i = 0; i < lines; i++)
    {
        int col1Indx = getSmallestUnvisited(col_1, col_1_visited, lines, i);
        int col2Indx = getSmallestUnvisited(col_2, col_2_visited, lines, i);
        diff += abs(col_1[col1Indx] - col_2[col2Indx]);

        // printf("Visiting: %d, %d\n\n", col_1[col1Indx], col_2[col2Indx]);
        col_1_visited[i] = col1Indx;
        col_2_visited[i] = col2Indx;
    }

    printf("Total Diff: %lld\n", diff);
    free(col_1);
    free(col_1_visited);
    free(col_2);
    free(col_2_visited);
    
}

int getSmallestUnvisited(int *col, int *visited, int len, int num_visited)
{
    /**
     * Returns the index of the smallest value that hasnt been visited
     * @param col: The collumn of values
     * @return The index of the smallest
     */

    int indx = -1;
    int val = 999999999;
    if (num_visited == len)
    {
        printf("All locations visited");
        return -1;
    }

    for (int i = 0; i < len; i++)
    {
        if (isVisited(i, visited, num_visited)){
            continue;
        }
        if (col[i] < val)
        {
            val = col[i];
            indx = i;
        }
    }
    return indx;
}

int isVisited(int curr_indx, int* visited, int num_visited)
{
    for (int j = 0; j < num_visited; j++)
    {
        if (curr_indx == visited[j])
        {
            return 1;
        }
    }
    return 0;
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