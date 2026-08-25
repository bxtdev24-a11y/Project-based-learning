#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

// Window size
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;

// Grid
const int ROWS = 25;
const int COLS = 40;
const int CELL_SIZE = 32;

// Cell states
enum CellState
{
    EMPTY = 0,
    WALL = 1,
    START = 2,
    END = 3,
    VISITED = 4,
    PATH = 5
};

// Grid array
CellState grid[ROWS][COLS] = {};

// Start and End position
int startRow = 5;
int startCol = 5;

int endRow = 20;
int endCol = 35;


// Function to draw grid
void drawGrid(SDL_Renderer* renderer)
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            SDL_Rect cell =
            {
                c * CELL_SIZE,
                r * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };

            // Choose color according to cell state
            switch (grid[r][c])
            {
                case EMPTY:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    break;

                case WALL:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    break;

                case START:
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    break;

                case END:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    break;

                case VISITED:
                    SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
                    break;

                case PATH:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                    break;
            }

            // Draw cell
            SDL_RenderFillRect(renderer, &cell);

            // Grid lines
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}


int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL failed: "
             << SDL_GetError() << endl;

        return 1;
    }


    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Pathfinder Visualizer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );


    if (window == nullptr)
    {
        cout << "Window creation failed: "
             << SDL_GetError() << endl;

        SDL_Quit();
        return 1;
    }


    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );


    if (renderer == nullptr)
    {
        cout << "Renderer creation failed: "
             << SDL_GetError() << endl;

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }


    // Set Start and End cells
    grid[startRow][startCol] = START;
    grid[endRow][endCol] = END;


    bool running = true;
    SDL_Event event;


    // Main Loop
    while (running)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }


        // Clear screen
        SDL_SetRenderDrawColor(
            renderer,
            30, 30, 30, 255
        );

        SDL_RenderClear(renderer);


        // Draw grid
        drawGrid(renderer);


        // Show everything
        SDL_RenderPresent(renderer);
    }


    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
