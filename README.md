# CProfiler

## Overview
MyProject is a C++ program that demonstrates the usage of a custom profiling class Timer to measure the execution time of functions. The profiler logs start and end times, durations, and can optionally log this information to a file. The project includes nested function calls, class methods, loops, and various calculations to showcase the profiling capabilities.

## Directory Structure
```
MyProject/
├── CMakeLists.txt
├── include/
│   └── Timer.h
└── src/
    └── main.cpp
```

## Building the Project

### Step 1: Create a Build Directory

Create a build directory and navigate into it:
```bash
mkdir build
cd build
```

### Step 2: Generate the Build Files Using CMake

Run the following command to generate the build files:
Generate the build files using CMake:
```bash
cmake ..
```

### Step 3: Build the Project

Build the project using the following command:
Build the project:
```bash
cmake --build .
```

### Running the Executable
After building the project, run the executable:
Run the executable:
```bash
./MyExecutable
```

## Using the Timer Class
### Profiling Functions

To profile a function and log the information to the console, use the PROFILE_FUNCTION() macro at the beginning of the function:
```cpp
void myFunction() {
    PROFILE_FUNCTION(); // Profiles the execution time of this function
    // Function implementation
}
```

### Logging to a File
To log profiling information to a file instead of the console, use the PROFILE_FUNCTION_TO_FILE() macro:

```cpp
void myFunction() {
    PROFILE_FUNCTION_TO_FILE(); // Profiles the execution time of this function and logs to a file
    // Function implementation
}
```

## Conclusion
This project demonstrates how to use a custom profiling class to measure and log the execution time of functions in a C++ program. The Timer class provides detailed profiling information, which can be invaluable for performance analysis and optimization.