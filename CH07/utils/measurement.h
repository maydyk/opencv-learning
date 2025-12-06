#pragma once

#include <chrono>
#include <functional>

std::chrono::nanoseconds measure_execution(std::function<void(void)>);