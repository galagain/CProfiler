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

### Automating the Build and Run Process
Here's the simplified shell script to automate the process of generating the build files, building the project, and running the executable.

1. Create the script file:
```bash
touch build_and_run.sh
```

2. Edit the script file:
```bash
nano build_and_run.sh
```

3. Paste the script into the file and save it.
```sh
#!/bin/bash

# Step 2: Generate the Build Files Using CMake
cmake ..

# Step 3: Build the Project
cmake --build .

# Running the Executable
./MyExecutable
```

4. Make the script executable:
```bash
chmod +x build_and_run.sh
```

5. Run the script:
```bash
./build_and_run.sh
```

This script will perform the required steps to build and run your project automatically. Ensure that you run this script inside the build directory of your project.

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