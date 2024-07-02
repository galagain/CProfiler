#include <thread> // Includes the library for std::this_thread::sleep_for
#include <chrono> // Includes the library for std::chrono::milliseconds

/**
 * @brief Puts the current thread to sleep for a specified duration.
 * 
 * This function pauses the execution of the current thread for 100 milliseconds
 * using std::this_thread::sleep_for and std::chrono::milliseconds.
 */
void testFunction() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Puts the current thread to sleep for 100 milliseconds
}

/**
 * @brief Main function of the program.
 * 
 * This is the entry point of the program. It calls the testFunction and returns 0 to indicate
 * successful completion of the program.
 * 
 * @return int Returns 0 to indicate successful completion of the program.
 */
int main() {
    testFunction(); // Calls the testFunction
    return 0; // Returns 0 to indicate that the program terminated successfully
}
