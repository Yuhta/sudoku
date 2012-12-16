#include "sudoku.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv)
{
    int i, j;
    int x;
    cell sudoku[9*9];
    FILE * ifile = NULL, * ofile = NULL;

    for(i = 1; i < argc; ++i)
        if (strcmp("-i", argv[i]) == 0)
        {
            ifile = freopen(argv[++i], "r", stdin);
            if (ifile == NULL)
            {
                fprintf(stderr, "Error reading file\n");
                return 0;
            }
        }
        else if (strcmp("-o", argv[i]) == 0)
        {
            ofile = freopen(argv[++i], "w", stdout);
            if (ofile == NULL)
            {
                fprintf(stderr, "Error writing file\n");
                return 0;
            }
        }

    for (i = 0; i < 9*9; ++i)
    {
        if (1 != scanf("%d", &x))
        {
            fprintf(stderr, "Input error\n");
            return 0;
        }
        if (x >= 1 && x <= 9) sudoku[i].num = x;
        else sudoku[i].num = 0;
    }

    if (!solve(sudoku)) fprintf(stderr, "No solution\n");
    else
    {
        for (i = 0; i < 9; ++i)
        {
            for (j = 0; j < 8; ++j)
                printf("%d ", sudoku[9 * i + j].num);
            printf("%d\n", sudoku[9 * i + j].num);
        }
    }

    if (ifile != NULL) fclose(stdin);
    if (ofile != NULL) fclose(stdout);

    return 0;
}
