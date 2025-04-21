Lockout/Tagout Scheduler
A C++ data structures exercise that models and simulates an industrial lockout/tagout procedure to safely isolate machines. Leveraging key containers (unordered_map, vector, unordered_set) and OOP, it reads JSON inputs and produces an optimal, non‑redundant schedule based on team capabilities.
🚀 Core Data Structures & Algorithms
Fast lookups via unordered_map (O(1) average) for devices & machines

Dynamic arrays (vector) to track related devices & team lists

Sets (unordered_set) to prevent duplicate lockouts

Sorting (std::sort) with custom comparator to define machine order

OOP design: clear class responsibilities, pointer-based associations

🔧 Features
JSON Parsing: Load real‑world data using nlohmann/json.

Data Structure Mastery:

Map IDs → objects (Device, Machine)

Associate machines → device pointers

Track lockouts efficiently

Scheduling Logic:

Sequential machine processing

Parallel‑capable device assignments (one per team)

Skip already‑locked devices

Detailed Reporting:

List of machines to lock

Step‑by‑step lockouts by machine

Summary lockouts by team

💡 Customization
Change machine order by editing the lambda in main.cpp.

Tweak JSON in assets/ to test robustness.

Extend with smart pointers or alternative containers (e.g., map, deque).

This project demonstrates advanced use of C++ data structures to solve a real‑world scheduling problem. 🔧📈

![Console de débogage Microsoft Visual Studio 2025-04-21 13_11_23](https://github.com/user-attachments/assets/e7349508-4a26-4888-aa3e-e602e2a7e83d)
![Console de débogage Microsoft Visual Studio 2025-04-21 13_11_34](https://github.com/user-attachments/assets/1758e4b8-2238-4cfb-b892-0e068f39c06f)



