#ifndef STATIC_FUNCTIONS_H_
#define STATIC_FUNCTIONS_H_
#include <chrono>
#include <iostream>

#define debug(x) std::cerr << #x << ": " << x << std::endl;
uint64_t getTimeMs();

#endif /* STATIC_FUNCTIONS_H_ */