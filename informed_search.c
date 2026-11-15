#include "core.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>

void heap_push_internal(void*, int, int);
void heap_pop_internal(void*, int*, int*);
int heap_empty_internal(const void*);
unsigned long heap_storage_size(void);

static int heuristic(int a, int b) {
    int dr=row_of(a)-row_of(b), dc=col_of(a)-col_of(b);
    if (dr<0) dr=-dr; if (dc<0) dc=-dc;
    return dr+dc; /* Manhattan distance: admissible for four-way unit-cost grid. */
}
static void restore_path(SearchResult *out, const int *parent, int start, int goal) {
    int rev[MAX_CELLS], n=0, cur=goal;
    while (cur!=-1 && n<MAX_CELLS) {
        rev[n++]=cur;
        if (cur==start) break;
        cur=parent[cur];
    }
    if (!n || rev[n-1]!=start) return;
    out->found=1; out->path_length=n;
    for (int i=0;i<n;i++) out->path[i]=rev[n-1-i];
}
SearchResult run_informed(const int grid[ROWS][COLS], int sr,int sc,int er,int ec, int use_astar) {
    SearchResult out; memset(&out,0,sizeof(out));
    if (!is_valid_cell(sr,sc)||!is_valid_cell(er,ec)||grid[sr][sc]||grid[er][ec]) return out;
    int start=cell_id(sr,sc), goal=cell_id(er,ec);
    int g[MAX_CELLS], parent[MAX_CELLS], closed[MAX_CELLS]={0};
    for(int i=0;i<MAX_CELLS;i++){g[i]=INT_MAX;parent[i]=-1;}
    g[start]=0;
    unsigned char storage[sizeof(int)*MAX_CELLS*8 + 1024];
   
    void *heap=calloc(1,heap_storage_size());
    if(!heap) return out;
    heap_push_internal(heap,start,use_astar?heuristic(start,goal):0);
    const int dr[4]={-1,0,1,0}, dc[4]={0,1,0,-1};
    (void)storage;
    while(!heap_empty_internal(heap)) {
        int cur, priority; heap_pop_internal(heap,&cur,&priority); (void)priority;
        if(cur<0 || closed[cur]) continue;
        closed[cur]=1; out.visited_order[out.visited_count++]=cur;
        if(cur==goal){restore_path(&out,parent,start,goal);break;}
        int r=row_of(cur),c=col_of(cur);
        for(int k=0;k<4;k++){
            int nr=r+dr[k],nc=c+dc[k];
            if(!is_valid_cell(nr,nc)||grid[nr][nc]) continue;
            int nxt=cell_id(nr,nc);
            if(closed[nxt]||g[cur]==INT_MAX) continue;
            int tentative=g[cur]+1;
            if(tentative<g[nxt]){
                g[nxt]=tentative;parent[nxt]=cur;
                int f=tentative+(use_astar?heuristic(nxt,goal):0);
                heap_push_internal(heap,nxt,f);
            }
        }
    }
    free(heap); return out;
}
