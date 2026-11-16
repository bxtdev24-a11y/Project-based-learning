#ifndef SUPPORT_H
#define SUPPORT_H
#include "core.h"
void generate_random_walls(int grid[ROWS][COLS],unsigned int seed,int percent,
                           int sr,int sc,int er,int ec);
double elapsed_milliseconds(long long start_counter,long long end_counter,
                            long long frequency);
#endif
