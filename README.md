# 🚀 ShortestPathEngine

A high-performance, modular C++17 shortest path engine built with modern software engineering practices. The project implements Dijkstra's algorithm using an efficient adjacency-list representation and priority queue while emphasizing clean architecture, scalability, and performance benchmarking.

---

## ✨ Features

* **Efficient Shortest Path Computation**

  * Implements **Dijkstra's Algorithm** using a Min Priority Queue.
  * Time Complexity: **O((V + E) log V)**.
  * Supports weighted graphs with non-negative edge weights.

* **Modular Architecture**

  * Clean separation of interface and implementation.
  * Organized into independent modules using:

    * Header files (`include/`)
    * Source files (`src/`)
    * CMake build system

* **Graph Representation**

  * Memory-efficient adjacency list.
  * Supports both **directed** and **undirected** graphs.
  * Dynamic edge insertion with input validation.

* **Path Reconstruction**

  * Stores parent information during Dijkstra's execution.
  * Reconstructs the complete shortest path from source to destination.

* **Random Graph Generator**

  * Generates large weighted graphs for benchmarking.
  * Creates connected graphs before adding random edges.

* **File-Based Input**

  * Loads graphs directly from text files.
  * Edge format:

```text
source destination weight
```

* **Performance Benchmarking**

  * Uses `std::chrono` for high-resolution timing.
  * Benchmarks multiple graph sizes automatically.

---

# 📂 Project Structure

```text
ShortestPathEngine/
│
├── build/
├── include/
│   ├── Graph.h
│   └── ...
│
├── src/
│   ├── Graph.cpp
│   └── main.cpp
│
├── tests/
│   └── graph_data.txt
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

# ⚙️ Technologies Used

* C++17
* STL

  * `vector`
  * `priority_queue`
  * `pair`
  * `random`
* CMake
* MinGW / GCC
* Chrono Library
* File Streams (`fstream`)

---

# 📈 Benchmark Results

| Nodes   | Edges   | Average Execution Time |
| ------- | ------- | ---------------------- |
| 100     | 500     | ~0.3 ms                |
| 10,000  | 50,000  | ~40 ms                 |
| 100,000 | 500,000 | ~120 ms                |

> Results may vary depending on CPU, compiler optimization level, and operating system.

---

# 🧠 Algorithm

The engine uses **Dijkstra's Algorithm** with a Min Priority Queue.

* **Time Complexity:** `O((V + E) log V)`
* **Space Complexity:** `O(V + E)`

The algorithm also maintains a parent array to reconstruct the shortest path after computing minimum distances.

---

# 🚀 Building the Project

### Configure

```bash
cmake -S . -B build
```

### Build

```bash
cmake --build build
```

### Run

```bash
./build/ShortestPathEngine
```

---

# 📌 Future Improvements

* Bellman-Ford Algorithm
* Floyd-Warshall Algorithm
* A* Search
* Bidirectional Dijkstra
* Dynamic graph updates
* Graph visualization
* Unit tests
* Benchmark suite with CSV export

---

# 📄 License

This project is open-source and intended for educational and learning purposes.
