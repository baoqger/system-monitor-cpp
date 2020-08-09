#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    std::string h = std::to_string(seconds/3600);
    seconds = seconds%3600;
    std::string m = std::to_string(seconds/60);
    std::string s = std::to_string(seconds%60);
    std::string symbol{":"};    
    return (h + symbol + m + symbol + s);
}