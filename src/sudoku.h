#ifndef _SUDOKU_H
#define _SUDOKU_H

typedef struct
{
    unsigned num; /* 0 means undetermined */
    _Bool choice[9];
} cell;

/* return 1 if find a solution; otherwise return 0 */
_Bool solve(cell * table);

/* return 1 if table is eligible; otherwise return 0 */
_Bool check(cell * table);

#endif
