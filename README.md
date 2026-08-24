# 🧭 Interactive Pathfinding Algorithm Visualizer

An interactive visualizer that demonstrates how different **pathfinding algorithms** explore a grid and find the shortest or optimal path between two points.

The project is designed as a **PBL (Project-Based Learning)** project to make Data Structures and Algorithms easier to understand through real-time visualization.

---

## 🚀 Project Overview

Pathfinding algorithms are widely used in **Google Maps, GPS navigation, robotics, games, and AI systems**.

Understanding these algorithms theoretically can be difficult. This project provides an interactive grid where users can:

* 🟢 Select a starting point
* 🔴 Select a destination
* 🧱 Create walls/obstacles
* ▶️ Run different pathfinding algorithms
* 👀 Watch the algorithm explore the grid step-by-step
* 🛣️ Visualize the final path

---

## ✨ Features

* 🖱️ Interactive grid
* 🟢 Custom Start Point
* 🔴 Custom End Point
* 🧱 Add/remove obstacles
* ⚡ Real-time algorithm visualization
* 📊 Compare different algorithms
* 🔄 Reset/Clear grid
* ⏱️ Visualization of algorithm execution
* 🎨 Easy-to-understand color-coded cells

---

## 🧠 Algorithms

The visualizer will demonstrate multiple pathfinding algorithms:

| Algorithm                | Type       | Shortest Path    | Time Complexity    |
| ------------------------ | ---------- | ---------------- | ------------------ |
| **BFS**                  | Unweighted | ✅ Yes            | `O(V + E)`         |
| **DFS**                  | Unweighted | ❌ Not Guaranteed | `O(V + E)`         |
| **Dijkstra's Algorithm** | Weighted   | ✅ Yes            | `O((V + E) log V)` |
| **A***                   | Heuristic  | ✅ Yes*           | `O(E)`*            |

> **Note:** The exact performance depends on the implementation and graph/grid configuration.

---

## 🎨 Visualization

The grid uses different colors to represent different states:

* 🟢 **Green** → Starting Point
* 🔴 **Red** → Destination
* ⬛ **Black** → Wall / Obstacle
* 🟡 **Yellow** → Visited / Explored Cell
* 🔵 **Blue** → Final Path
* ⬜ **White** → Unvisited Cell

---

## 🛠️ Technologies Used

* **C++**
* **SDL2**
* **Data Structures & Algorithms**
* **Object-Oriented Programming**
* **Graph/Grid Traversal**
* **Pathfinding Algorithms**

---

## 🏗️ Project Structure

```text
Interactive-Pathfinding-Visualizer/
│
├── src/
│   ├── main.cpp
│   ├── grid.cpp
│   ├── grid.h
│   ├── bfs.cpp
│   ├── dfs.cpp
│   ├── dijkstra.cpp
│   └── astar.cpp
│
├── include/
│
├── assets/
│
├── README.md
└── LICENSE
```

> The project structure may change as development progresses.

---

## 🎮 How It Works

### 1. Create Grid

The application generates an interactive grid consisting of rows and columns.

### 2. Set Start & End

The user selects:

```text
🟢 Start → 🔴 Destination
```

### 3. Add Obstacles

Users can click or drag over cells to create walls.

### 4. Select Algorithm

Choose an algorithm such as:

```text
BFS
DFS
Dijkstra
A*
```

### 5. Start Visualization

The selected algorithm explores the grid step-by-step.

### 6. Display Final Path

After reaching the destination, the shortest/selected path is highlighted.

---

## 📚 Concepts Used

This project demonstrates important concepts of **Data Structures and Algorithms**:

* Graphs
* 2D Arrays
* Queues
* Stacks
* Priority Queues
* Heaps
* Recursion
* BFS
* DFS
* Greedy Search
* Heuristic Search
* Time & Space Complexity
* Object-Oriented Programming

---

## 🎯 Objectives

The main objectives of this project are:

1. To understand pathfinding algorithms practically.
2. To visualize graph traversal algorithms.
3. To compare the performance of different algorithms.
4. To understand shortest-path concepts.
5. To implement Data Structures in a real-world application.
6. To develop an interactive GUI-based C++ application.

---

## 🌍 Real-World Applications

Pathfinding algorithms are used in many real-world systems:

* 🗺️ GPS & Navigation
* 🤖 Robotics
* 🎮 Game Development
* 🚗 Autonomous Vehicles
* 🧠 Artificial Intelligence
* 📦 Warehouse Automation
* 🛰️ Route Planning

---

## 👥 Team Members

| Name         | Role                     |
| ------------ | ------------------------ |
| **Member 1** | Algorithm Development    |
| **Member 2** | GUI / SDL2 Development   |
| **Member 3** | Testing & Optimization   |
| **Member 4** | Documentation & Research |

> Replace the names and roles with your actual group members.

---

## 🔮 Future Improvements

Future versions may include:

* [ ] Weighted grid cells
* [ ] More pathfinding algorithms
* [ ] Algorithm speed control
* [ ] Maze generation
* [ ] Performance comparison graphs
* [ ] Multiple heuristic functions
* [ ] Save/load grid configurations
* [ ] Better GUI
* [ ] Dark/Light themes

---

## 📸 Screenshots

Add project screenshots here after completing the visualizer.

```text
screenshots/
├── main-menu.png
├── grid.png
├── bfs.png
└── final-path.png
```

---

## ⚙️ Installation & Setup

### Prerequisites

Make sure you have:

* C++ Compiler
* CMake *(if used)*
* SDL2
* Git

### Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/Interactive-Pathfinding-Visualizer.git
```

### Navigate to Project

```bash
cd Interactive-Pathfinding-Visualizer
```

### Build & Run

Follow the build instructions according to your operating system and SDL2 configuration.

---

## 🤝 Contribution

Contributions from team members are welcome.

1. Clone the repository.
2. Create a new branch.
3. Make your changes.
4. Commit your changes.
5. Push the branch.
6. Create a Pull Request.

Example:

```bash
git checkout -b feature/bfs
git add .
git commit -m "Added BFS pathfinding algorithm"
git push origin feature/bfs
```

---

## 📄 License

This project is created for **educational and academic purposes** as part of a PBL project.

---

## ⭐ Support

If you find this project useful, consider giving the repository a ⭐.

### Made with ❤️ by the PBL Team

**Interactive Pathfinding Algorithm Visualizer**
