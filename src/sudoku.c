#include "sudoku.h"

#define POS(i, j) ((i) * 9 + (j))

static void eliminate(cell * table, unsigned i, unsigned j)
{
    unsigned ii, jj, n = table[POS(i, j)].num - 1;
    unsigned bi = i / 3 * 3, bj = j / 3 * 3;

    for (ii = 0; ii < 9; ++ii) table[POS(ii, j)].choice[n] = 0;
    for (jj = 0; jj < 9; ++jj) table[POS(i, jj)].choice[n] = 0;

    for (ii = bi; ii < bi + 3; ++ii)
        for (jj = bj; jj < bj + 3; ++jj)
            table[POS(ii, jj)].choice[n] = 0;
}

static void initialize(cell * table)
{
    unsigned i, j;

    for (i = 0; i < 9*9; ++i)
        if (table[i].num == 0)
            for (j = 0; j < 9; ++j)
                table[i].choice[j] = 1;

    for (i = 0; i < 9; ++i)
        for (j = 0; j < 9; ++j)
            if (table[POS(i, j)].num != 0)
                eliminate(table, i, j);
}

typedef struct
{
    _Bool row[9], column[9], block[3][3];
} choice_backup;

static void backup(const cell * table, unsigned i, unsigned j, choice_backup * data)
{
    unsigned n = table[POS(i, j)].num - 1, ii, jj;
    unsigned bi = i / 3 * 3, bj = j / 3 * 3;

    for (ii = 0; ii < 9; ++ii) data->column[ii] = table[POS(ii, j)].choice[n];
    for (jj = 0; jj < 9; ++jj) data->row[jj] = table[POS(i, jj)].choice[n];

    for (ii = 0; ii < 3; ++ii)
        for (jj = 0; jj < 3; ++jj)
            data->block[ii][jj] = table[POS(ii + bi, jj + bj)].choice[n];
}

static void restore(cell * table, unsigned i, unsigned j, const choice_backup * data)
{
    unsigned n = table[POS(i, j)].num - 1, ii, jj;
    unsigned bi = i / 3 * 3, bj = j / 3 * 3;

    for (ii = 0; ii < 9; ++ii) table[POS(ii, j)].choice[n] = data->column[ii];
    for (jj = 0; jj < 9; ++jj) table[POS(i, jj)].choice[n] = data->row[jj];

    for (ii = 0; ii < 3; ++ii)
        for (jj = 0; jj < 3; ++jj)
            table[POS(ii + bi, jj + bj)].choice[n] = data->block[ii][jj];
}

static _Bool guess(cell * table, unsigned i)
{
    unsigned j, ii, jj;
    choice_backup data;

    while (i < 9*9 && table[i].num != 0) ++i;
    if (i == 9*9) return 1;

    ii = i / 9, jj = i % 9;

    for (j = 0; j < 9; ++j)
        if (table[i].choice[j])
        {
            table[i].num = j + 1;
            backup(table, ii, jj, &data);
            eliminate(table, ii, jj);
            if (guess(table, i + 1)) return 1;
            restore(table, ii, jj, &data);
        }

    table[i].num = 0;
    return 0;
}

_Bool solve(cell * table)
{
    initialize(table);
    return guess(table, 0);
}

static _Bool check9(unsigned * temp)
{
    _Bool appeared[9];
    unsigned i;

    for (i = 0; i < 9; ++i) appeared[i] = 0;

    for (i = 0; i < 9; ++i)
    {
        if (appeared[temp[i] - 1]) return 0;
        appeared[temp[i] - 1] = 1;
    }

    return 1;
}

_Bool check(cell * table)
{
    unsigned i, j, bi, bj, temp[9];

    for (i = 0; i < 9; ++i)
    {
        for (j = 0; j < 9; ++j)
            temp[j] = table[POS(i, j)].num;
        if (!check9(temp)) return 0;
    }

    for (j = 0; j < 9; ++j)
    {
        for (i = 0; i < 9; ++i)
            temp[i] = table[POS(i, j)].num;
        if (!check9(temp)) return 0;
    }

    for (bi = 0; bi < 3; ++bi)
        for (bj = 0; bj < 3; ++bj)
        {
            for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                    temp[3*i+j] = table[POS(3*bi + i, 3*bj + j)].num;
            if (!check9(temp)) return 0;
        }

    return 1;
}
