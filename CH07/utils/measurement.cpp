#include "measurement.h"

std::chrono::nanoseconds measure_execution(std::function<void(void)> lambda) {
    // Record the start time
    auto start = std::chrono::high_resolution_clock::now();

    // Call the measured lambda
    lambda();
    
    // Record the end time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
}