#include "core.h"
int cell_id(int row, int col) { return row * COLS + col; }
int row_of(int id) { return id / COLS; }
int col_of(int id) { return id % COLS; }
int is_valid_cell(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
