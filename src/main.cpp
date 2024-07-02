#include <thread> // Includes the library for std::this_thread::sleep_for
#include <chrono> // Includes the library for std::chrono::milliseconds
#include <vector> // Includes the library for std::vector
#include <iostream>

class Calculator {
public:
    Calculator() = default;

    /**
     * @brief Computes the sum of a vector of integers.
     * 
     * @param numbers A vector of integers.
     * @return int The sum of the integers.
     */
    int computeSum(const std::vector<int>& numbers) 
    
    {
        int sum = 0;
        for (int number : numbers) {
            sum += number;
        }
        return sum;
    }

    /**
     * @brief Computes the product of a vector of integers.
     * 
     * @param numbers A vector of integers.
     * @return int The product of the integers.
     */
    int computeProduct(const std::vector<int>& numbers) {
        int product = 1;
        for (int number : numbers) {
            product *= number;
        }
        return product;
    }
};

/**
 * @brief Puts the current thread to sleep for a specified duration.
 * 
 * This function pauses the execution of the current thread for 100 milliseconds
 * using std::this_thread::sleep_for and std::chrono::milliseconds.
 */
void testFunction()             {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Puts the current thread to sleep for 100 milliseconds
}

/**
 * @brief Fills a vector with integers from 1 to n.
 * 
 * @param n The number of elements to generate.
 * @return std::vector<int> A vector filled with integers from 1 to n.
 */
std::vector<int> generateNumbers(int n) 
{
    std::vector<int> numbers;
    for (int i = 1; i <= n; ++i) {
        numbers.push_back(i);
    }
    return numbers;
}

int main() {

    // Test the sleep function
    testFunction();

    // Generate a vector of numbers
    std::vector<int> numbers = generateNumbers(1000);

    // Create a Calculator object
    Calculator calc;

    // Compute the sum of the numbers
    int sum = calc.computeSum(numbers);
    std::cout << "Sum of numbers: " << sum << std::endl;

    // Compute the product of the numbers
    int product = calc.computeProduct(numbers);
    std::cout << "Product of numbers: " << product << std::endl;

    // More complex calculations
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate some workload
        sum += calc.computeSum(numbers);
        product *= calc.computeProduct(numbers);
    }

    std::cout << "Final sum: " << sum << std::endl;
    std::cout << "Final product: " << product << std::endl;

    return 0; // Returns 0 to indicate that the program terminated successfully
}
