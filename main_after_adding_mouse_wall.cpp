#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;


// Window Size

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;
// number of  row nad coloumn
const int ROWS = 25;
const int COLS = 40;
const int CELL_SIZE = 32;



// Cell States

enum CellState
{
    EMPTY = 0,      // White
    WALL = 1,       // Black
    START = 2,      // Green
    END = 3,        // Red
    VISITED = 4,    // Blue
    PATH = 5        // Yellow
};



// Grid Array

CellState grid[ROWS][COLS] = {};



// Start Position

int startRow = 5;
int startCol = 5;


// End Position

int endRow = 20;
int endCol = 35;



// Draw Grid Function

void drawGrid(SDL_Renderer* renderer)
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            // Create cell rectangle
            SDL_Rect cell =
            {
                c * CELL_SIZE,
                r * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };


            
            // Choose Color According to State
            
            switch (grid[r][c])
            {
                case EMPTY:
                    SDL_SetRenderDrawColor(
                        renderer, 255, 255, 255, 255
                    );
                    break;

                case WALL:
                    SDL_SetRenderDrawColor(
                        renderer, 0, 0, 0, 255
                    );
                    break;

                case START:
                    SDL_SetRenderDrawColor(
                        renderer, 0, 255, 0, 255
                    );
                    break;

                case END:
                    SDL_SetRenderDrawColor(
                        renderer, 255, 0, 0, 255
                    );
                    break;

                case VISITED:
                    SDL_SetRenderDrawColor(
                        renderer, 0, 100, 255, 255
                    );
                    break;

                case PATH:
                    SDL_SetRenderDrawColor(
                        renderer, 255, 255, 0, 255
                    );
                    break;
            }


            // Draw filled cell
            SDL_RenderFillRect(renderer, &cell);


          
            // Draw Grid Lines
           
            SDL_SetRenderDrawColor(
                renderer, 200, 200, 200, 255
            );

            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}



// Main Function

int main(int argc, char* argv[])
{
    
    // Initialize SDL
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL failed: "
             << SDL_GetError() << endl;

        return 1;
    }


   
    // Create Window
  
    SDL_Window* window = SDL_CreateWindow(
        "Pathfinder Visualizer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );


    // Check Window
    if (window == nullptr)
    {
        cout << "Window creation failed: "
             << SDL_GetError() << endl;

        SDL_Quit();

        return 1;
    }


    
    // Create Renderer
    
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );


    // Check Renderer
    if (renderer == nullptr)
    {
        cout << "Renderer creation failed: "
             << SDL_GetError() << endl;

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }


    
    // Set Start and End Cells
    
    grid[startRow][startCol] = START;
    grid[endRow][endCol] = END;


  
    // Main Loop
    
    bool running = true;

    SDL_Event event;


    while (running)
    {
        
        // Handle Events
        
        while (SDL_PollEvent(&event))
        {
            // Close Window
            if (event.type == SDL_QUIT)
            {
                running = false;
            }


           
            // Mouse Click
            
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;

                // Get mouse position
                SDL_GetMouseState(&x, &y);


                // Convert mouse position
                // into grid row and column
                int col = x / CELL_SIZE;
                int row = y / CELL_SIZE;


               
                // Boundary Check
                
                if (row >= 0 && row < ROWS &&
                    col >= 0 && col < COLS)
                {
                    // Empty → Wall
                    if (grid[row][col] == EMPTY)
                    {
                        grid[row][col] = WALL;
                    }

                    // Wall → Empty
                    else if (grid[row][col] == WALL)
                    {
                        grid[row][col] = EMPTY;
                    }

                    // START and END remain unchanged
                }
            }
        }


        
        // Clear Screen
        
        SDL_SetRenderDrawColor(
            renderer,
            30, 30, 30, 255
        );

        SDL_RenderClear(renderer);


       
        // Draw Grid
      
        drawGrid(renderer);


       
        // Display Everything
        
        SDL_RenderPresent(renderer);
    }


    
    // Cleanup
   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();


    return 0;
}
