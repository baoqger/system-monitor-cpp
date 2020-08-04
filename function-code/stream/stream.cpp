#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>


std::string Kernel() {
    const std::string kProcDirectory{"/proc/"};
    const std::string kVersionFilename{"/version"};    
    std::string os, kernel;
    std::string line;

    std::ifstream stream{kProcDirectory + kVersionFilename};

    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> kernel;
    }

    return kernel;
}

void MemoInfo() {
    const std::string kProcDirectory{"/proc/"};
    const std::string kMeminfoFilename{"/meminfo"};

    std::ifstream stream{kProcDirectory + kMeminfoFilename};

    if (!stream.is_open()) {
        std::cout << "failed to open memoinfo file" << std::endl;
        return;
    }
    std::string line;
    std::string key, value;
    while(std::getline(stream, line)) {
        // std::cout << line << std::endl;
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        linestream >> key >> value;
        std::cout << "key: " << key << " value: " << value << std::endl;
    }
}

std::vector<std::string> CPU_Util() {
    const std::string kProcDirectory{"/proc/"};
    const std::string kStatFilename{"/stat"};

    std::vector<std::string> cpu_utils; 

    std::ifstream stream{kProcDirectory + kStatFilename};

    if(!stream.is_open()) {
        std::cout << "fail to open proc/stat file" << std::endl;
    }
    std::string line;
    std::getline(stream, line); // read the first line of proc/stat
    // std::cout << "first line of proc/stat" <<  line << std::endl; 

    std::istringstream linestream{line};
    std::string cpu_time;
    int count {0};
    while (linestream >> cpu_time) {
        // std::cout << "each cpu time: " << cpu_time << std::endl;
        if (count > 0) {
            cpu_utils.push_back(cpu_time);
        }
        count++;
    }

    return cpu_utils;
}

int main() {

    std::cout << Kernel() << std::endl;
    MemoInfo();
    int totalCPUTime {0};
    float cpu_percentage {1.4f};
    std::vector<std::string> cpu_utils = CPU_Util();
    for(auto each : cpu_utils) {
        std::cout << "cpu time: " << each << std::endl;
        totalCPUTime += std::stoi(each);
        std::cout << "total cpu time: " << totalCPUTime << std::endl;
    } 
    std::cout << "idel time: " << cpu_utils[3] << std::endl;
    cpu_percentage = std::stoi(cpu_utils[3])/static_cast<double>(totalCPUTime);
    std::cout << "Total CPU time: " << totalCPUTime << std::endl;
    std::cout << "CPU percentage: " << 100* (1 - cpu_percentage) << std::endl;
    return 0;

}