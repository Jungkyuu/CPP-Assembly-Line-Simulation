# Assembly Line Simulation System

## Overview
This project is a C++ based simulation of an assembly line that processes customer orders across multiple workstations. It accurately models the flow of inventory and orders, reading initial states from text files and managing the lifecycle of each item until the order is completely filled. 

This system was developed to practice and demonstrate core software engineering principles, with a strong emphasis on memory safety, resource management, and modular architecture.

## Key Technical Skills Highlighted
* **Memory Management & Move Semantics:** Implemented custom destructors, move constructors, and move assignment operators (Rule of 5) to prevent memory leaks and optimize resource transfers when handling dynamically allocated item arrays.
* **Robust Data Parsing:** Built a custom string parsing utility (`Utilities.cpp`) to safely extract and validate tokens from delimited text files, handling edge cases and input validation.
* **Object-Oriented Design:** Structured the system into decoupled modules (`Station`, `CustomerOrder`, `Workstation`, `LineManager`) to ensure maintainability and scalability.
* **STL Containers & Algorithms:** Extensively utilized C++ Standard Template Library (STL) including `std::vector`, iterators, and lambda functions for efficient data manipulation and search operations.

## Architecture & Modules
* `Station`: Manages inventory and serial numbers for specific items on the assembly line.
* `CustomerOrder`: Handles dynamically allocated arrays of items requested by customers, utilizing move semantics for efficient data transfer.
* `Workstation`: Inherits from `Station` and manages the queue of pending orders, moving them down the line once filled.
* `LineManager`: Parses assembly line configuration files to establish the sequence of workstations and orchestrates the overall simulation loop.
