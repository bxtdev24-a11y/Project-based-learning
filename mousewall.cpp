//adding mouse wall in grid using sdl2 libary
// Mouse click
if (event.type == SDL_MOUSEBUTTONDOWN) 
{

    int x, y;

    // Mouse ki position lo
    SDL_GetMouseState(&x, &y);

    // Mouse position ko grid ke row/column mein convert karo
    int col = x / CELL_SIZE;
    int row = y / CELL_SIZE;

    // Boundary check
    if (row >= 0 && row < ROWS &&
        col >= 0 && col < COLS) {

        // Empty cell ko Wall banao
        if (grid[row][col] == EMPTY) {
            grid[row][col] = WALL;
        }

        // Wall ko dobara click karne par Empty banao
        else if (grid[row][col] == WALL) {
            grid[row][col] = EMPTY;
        }
    }
}
