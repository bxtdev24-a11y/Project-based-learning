#ifndef CORE_H
#define CORE_H
#ifdef __cplusplus
extern "C" {
#endif
#define ROWS 25
#define COLS 40
#define MAX_CELLS (ROWS * COLS)
typedef enum { ALG_BFS=1, ALG_DFS=2, ALG_DIJKSTRA=3, ALG_ASTAR=4 } Algorithm;
typedef struct {
    int found;
    int visited_count;
    int path_length;
    int visited_order[MAX_CELLS];
    int path[MAX_CELLS];
} SearchResult;
int cell_id(int row, int col);
int row_of(int id);
int col_of(int id);
int is_valid_cell(int row, int col);
#ifdef __cplusplus
}
#endif
#endif
