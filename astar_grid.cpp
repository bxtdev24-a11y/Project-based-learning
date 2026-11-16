
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Cell {
    int row, col;
    int g, h;
    int parentRow, parentCol;

    int f() const { return g + h; }
};

struct CompareCell {
    bool operator()(const Cell& a, const Cell& b) const {
        return a.f() > b.f(); // smallest f-value has highest priority
    }
};

int heuristic(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2); // Manhattan distance
}

int main() {
    const int ROWS = 6, COLS = 8;
    const int INF = numeric_limits<int>::max();

    int grid[ROWS][COLS] = {
        {0,0,0,0,0,0,0,0},
        {0,1,1,1,0,1,1,0},
        {0,0,0,1,0,0,0,0},
        {1,1,0,1,1,1,0,1},
        {0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,0}
    };

    const int sr = 0, sc = 0;
    const int gr = 5, gc = 7;

    int gScore[ROWS][COLS];
    bool closed[ROWS][COLS] = {};
    int parentR[ROWS][COLS], parentC[ROWS][COLS];

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            gScore[r][c] = INF;
            parentR[r][c] = parentC[r][c] = -1;
        }
    }

    priority_queue<Cell, vector<Cell>, CompareCell> open;
    gScore[sr][sc] = 0;
    open.push({sr, sc, 0, heuristic(sr, sc, gr, gc), -1, -1});

    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    while (!open.empty()) {
        Cell current = open.top();
        open.pop();

        int r = current.row, c = current.col;
        if (closed[r][c] || current.g != gScore[r][c])
            continue;

        closed[r][c] = true;

        if (r == gr && c == gc)
            break;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];

            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS)
                continue;
            if (grid[nr][nc] == 1 || closed[nr][nc])
                continue;

            int tentativeG = gScore[r][c] + 1;
            if (tentativeG < gScore[nr][nc]) {
                gScore[nr][nc] = tentativeG;
                parentR[nr][nc] = r;
                parentC[nr][nc] = c;
                open.push({nr, nc, tentativeG,
                           heuristic(nr, nc, gr, gc), r, c});
            }
        }
    }

    if (gScore[gr][gc] == INF) {
        cout << "No path found.\n";
        return 0;
    }

    vector<pair<int,int>> path;
    int r = gr, c = gc;
    while (!(r == sr && c == sc)) {
        path.push_back({r, c});
        int pr = parentR[r][c], pc = parentC[r][c];
        if (pr == -1 || pc == -1) {
            cout << "Path reconstruction failed.\n";
            return 1;
        }
        r = pr;
        c = pc;
    }
    path.push_back({sr, sc});
    reverse(path.begin(), path.end());

    cout << "A* path (S=start, G=goal, #=wall, *=path):\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            bool onPath = find(path.begin(), path.end(), make_pair(i,j)) != path.end();
            if (i == sr && j == sc) cout << "S ";
            else if (i == gr && j == gc) cout << "G ";
            else if (grid[i][j] == 1) cout << "# ";
            else if (onPath) cout << "* ";
            else cout << ". ";
        }
        cout << '\n';
    }
    cout << "Path length (moves): " << gScore[gr][gc] << '\n';
    return 0;
}
