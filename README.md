# ShortestPathEngine 

A high-performance, modular C++ routing engine designed for efficient pathfinding in complex network topologies. This project focuses on algorithmic optimization, resource-efficient data structures, and real-time performance benchmarking.

## Key Features

* **Algorithmic Depth:** Implements Dijkstra’s algorithm using a Min-Priority Queue for $O(E \log V)$ time complexity.
* **Systems Architecture:** Utilizes memory-efficient adjacency lists for graph storage, enabling the handling of large-scale topologies (up to 100,000+ nodes).
* **High-Precision Benchmarking:** Integrated latency monitoring using `<chrono>` to provide real-time performance metrics during execution.
* **Robust I/O:** Supports dynamic graph loading from external text files and includes an automated stress-test generator for performance validation.
* **Path Reconstruction:** Full parent-pointer tracking for precise route visualization.

## Performance Metrics

The engine has been stress-tested across varying graph densities to ensure production-grade latency.

| Nodes | Edges | Execution Time (Avg) |
| --- | --- | --- |
| 100 | 500 | ~0.29 ms |
| 10,000 | 50,000 | ~39.58 ms |
| 100,000 | 500,000 | ~122.70 ms |

*(Benchmark results obtained on a standard development environment using high-resolution timers.)*

## Technical Stack

* **Language:** C++17
* **Core Logic:** Dijkstra's Algorithm, Priority Queues (STL), Adjacency List Representation.
* **Instrumentation:** `<chrono>` library for microsecond-precision latency tracking.
* **I/O:** `<fstream>` for efficient file-based data ingestion.

## Getting Started

1. **Clone the repository:** `git clone [your-repo-link]`
2. **Compile:** Use any C++ compiler (G++ recommended): `g++ -O3 main.cpp -o ShortestPathEngine`
3. **Run:** Execute the binary to view the automated benchmark suite: `./ShortestPathEngine`
4. **Custom Data:** To use your own data, place an edge list (format: `u v weight`) in a `.txt` file and update the `loadFromFile` path in `main.cpp`.

## License

This project is open-source and intended for educational use.