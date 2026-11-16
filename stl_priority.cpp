
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

int main() {
  
    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(40);
    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(5);
    minHeap.push(20);

    cout << "Elements removed in ascending order:\n";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << '\n';

    return 0;
}
