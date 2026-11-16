
#include <iostream>
using namespace std;

class Node {
private:
    int row;
    int col;
    bool blocked;

public:
    Node(int r, int c, bool isBlocked = false) {
        row = r;
        col = c;
        blocked = isBlocked;
    }

    void setBlocked(bool value) {
        blocked = value;
    }

    void display() const {
        cout << "Node position: (" << row << ", " << col << ")\n";
        cout << "Blocked: " << (blocked ? "Yes" : "No") << '\n';
    }
};

int main() {
    Node startNode(0, 0);
    Node wallNode(2, 3, true);

    cout << "Start node:\n";
    startNode.display();

    cout << "\nWall node:\n";
    wallNode.display();

    return 0;
}
