#include "bfs.h"
#include <string.h>
static void build_path(SearchResult *o,const int *parent,int s,int g){
    int rev[MAX_CELLS],n=0,p=g;
    while(p!=-1&&n<MAX_CELLS){rev[n++]=p;if(p==s)break;p=parent[p];}
    if(!n||rev[n-1]!=s)return;
    o->found=1;o->path_length=n;
    for(int i=0;i<n;i++)o->path[i]=rev[n-1-i];
}
SearchResult run_bfs(const int grid[ROWS][COLS],int sr,int sc,int er,int ec){
    SearchResult o;memset(&o,0,sizeof(o));
    if(!is_valid_cell(sr,sc)||!is_valid_cell(er,ec)||grid[sr][sc]||grid[er][ec])return o;
    int q[MAX_CELLS],front=0,rear=0,parent[MAX_CELLS],visited[MAX_CELLS]={0};
    for(int i=0;i<MAX_CELLS;i++)parent[i]=-1;
    int s=cell_id(sr,sc),g=cell_id(er,ec);q[rear++]=s;visited[s]=1;
    const int dr[4]={-1,0,1,0},dc[4]={0,1,0,-1};
    while(front<rear){
        int cur=q[front++];o.visited_order[o.visited_count++]=cur;
        if(cur==g){build_path(&o,parent,s,g);break;}
        int r=row_of(cur),c=col_of(cur);
        for(int k=0;k<4;k++){
            int nr=r+dr[k],nc=c+dc[k];
            if(!is_valid_cell(nr,nc)||grid[nr][nc])continue;
            int nxt=cell_id(nr,nc);
            if(!visited[nxt]){visited[nxt]=1;parent[nxt]=cur;q[rear++]=nxt;}
        }
    }
    return o;
}
