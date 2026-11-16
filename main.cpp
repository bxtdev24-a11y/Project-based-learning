#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "core.h"
#include "bfs.h"
#include "dfs.h"
#include "informed.h"
#include "support.h"

static constexpr int CELL=24, TOP=70, WIN_W=COLS*CELL, WIN_H=ROWS*CELL+TOP;
static int grid[ROWS][COLS]={};
static int sr=5,sc=5,er=19,ec=33;
static Algorithm selected=ALG_BFS;
static SearchResult result={};
static bool has_result=false;

static void rect(SDL_Renderer *ren,int x,int y,int w,int h,Uint8 r,Uint8 g,Uint8 b){
    SDL_SetRenderDrawColor(ren,r,g,b,255);SDL_Rect q{x,y,w,h};SDL_RenderFillRect(ren,&q);
}
static const char* algo_name(){
    switch(selected){case ALG_BFS:return "BFS";case ALG_DFS:return "DFS";
    case ALG_DIJKSTRA:return "Dijkstra";case ALG_ASTAR:return "A*";default:return "BFS";}
}
static void run_selected(){
    Uint64 t0=SDL_GetPerformanceCounter();
    if(selected==ALG_BFS)result=run_bfs(grid,sr,sc,er,ec);
    else if(selected==ALG_DFS)result=run_dfs(grid,sr,sc,er,ec);
    else result=run_informed(grid,sr,sc,er,ec,selected==ALG_ASTAR);
    Uint64 t1=SDL_GetPerformanceCounter();has_result=true;
    double ms=elapsed_milliseconds((long long)t0,(long long)t1,(long long)SDL_GetPerformanceFrequency());
    std::printf("%s | %s | Visited nodes: %d | Path cells: %d | Time: %.3f ms\n",
        algo_name(),result.found?"Path found":"No path",result.visited_count,result.path_length,ms);
}
static void draw(SDL_Renderer *ren){
    rect(ren,0,0,WIN_W,TOP,25,31,45);
    rect(ren,12,15,15,15,46,204,113);rect(ren,34,15,15,15,231,76,60);
    rect(ren,56,15,15,15,70,130,210);rect(ren,78,15,15,15,245,196,66);
    rect(ren,100,15,15,15,45,52,65);
    bool visited[MAX_CELLS]={},path[MAX_CELLS]={};
    if(has_result){
        for(int i=0;i<result.visited_count;i++)visited[result.visited_order[i]]=true;
        for(int i=0;i<result.path_length;i++)path[result.path[i]]=true;
    }
    for(int r=0;r<ROWS;r++)for(int c=0;c<COLS;c++){
        Uint8 cr=235,cg=239,cb=244;int id=cell_id(r,c);
        if(grid[r][c]){cr=45;cg=52;cb=65;}
        if(has_result&&visited[id]&&!grid[r][c]){cr=70;cg=130;cb=210;}
        if(has_result&&path[id]){cr=245;cg=196;cb=66;}
        if(r==sr&&c==sc){cr=46;cg=204;cb=113;}
        if(r==er&&c==ec){cr=231;cg=76;cb=60;}
        rect(ren,c*CELL+1,TOP+r*CELL+1,CELL-2,CELL-2,cr,cg,cb);
    }
    SDL_RenderPresent(ren);
}
int main(int,char**){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){std::printf("SDL error: %s\n",SDL_GetError());return 1;}
    SDL_Window *win=SDL_CreateWindow("Team Apex - Pathfinding Visualizer",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_W,WIN_H,SDL_WINDOW_SHOWN);
    if(!win){std::printf("Window error: %s\n",SDL_GetError());SDL_Quit();return 1;}
    SDL_Renderer *ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    if(!ren)ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_SOFTWARE);
    if(!ren){std::printf("Renderer error: %s\n",SDL_GetError());SDL_DestroyWindow(win);SDL_Quit();return 1;}
    std::puts("Team Apex Pathfinding Visualizer");
    std::puts("1 BFS | 2 DFS | 3 Dijkstra | 4 A* | SPACE Run | C Clear | R Random walls");
    std::puts("Left click wall | Right click move destination | Middle click move start | ESC exit");
    bool running=true;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_QUIT)running=false;
            if(e.type==SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                case SDLK_ESCAPE:running=false;break;
                case SDLK_1:selected=ALG_BFS;has_result=false;break;
                case SDLK_2:selected=ALG_DFS;has_result=false;break;
                case SDLK_3:selected=ALG_DIJKSTRA;has_result=false;break;
                case SDLK_4:selected=ALG_ASTAR;has_result=false;break;
                case SDLK_SPACE:run_selected();break;
                case SDLK_c:
                    for(int r=0;r<ROWS;r++)for(int c=0;c<COLS;c++)grid[r][c]=0;
                    has_result=false;break;
                case SDLK_r:
                    generate_random_walls(grid,(unsigned int)std::time(nullptr),22,sr,sc,er,ec);
                    has_result=false;break;
                }
            }
            if(e.type==SDL_MOUSEBUTTONDOWN){
                int c=e.button.x/CELL,r=(e.button.y-TOP)/CELL;
                if(e.button.y>=TOP&&is_valid_cell(r,c)){
                    if(e.button.button==SDL_BUTTON_LEFT&&!(r==sr&&c==sc)&&!(r==er&&c==ec))grid[r][c]=!grid[r][c];
                    else if(e.button.button==SDL_BUTTON_RIGHT&&!grid[r][c]){er=r;ec=c;}
                    else if(e.button.button==SDL_BUTTON_MIDDLE&&!grid[r][c]){sr=r;sc=c;}
                    has_result=false;
                }
            }
        }
        draw(ren);SDL_Delay(16);
    }
    SDL_DestroyRenderer(ren);SDL_DestroyWindow(win);SDL_Quit();return 0;
}
