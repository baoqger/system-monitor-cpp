
#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    int totalCPUTime {0};
    float cpu_percentage {1.4f};    
    std::vector<std::string> cpu_utils = LinuxParser::CpuUtilization();
    for(auto each : cpu_utils) {
        totalCPUTime += std::stoi(each);
    }
    cpu_percentage = std::stoi(cpu_utils[3])/static_cast<double>(totalCPUTime);
    return 1 - cpu_percentage;     
}