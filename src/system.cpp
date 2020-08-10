#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
    vector<int> pids = LinuxParser::Pids();
    for (auto pid : pids) {
        Process process{
            pid,
            LinuxParser::Cpu(pid),
            LinuxParser::Command(pid),
            LinuxParser::Uid(pid),
            LinuxParser::User(pid),
            LinuxParser::Ram(pid),
            LinuxParser::UpTime(pid)
        };
        processes_.emplace_back(process);
    }
    return processes_;
}

std::string System::Kernel() { 
    return LinuxParser::Kernel();
 }

float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
 }

std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
}


int System::RunningProcesses() {
    return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses();
}

long int System::UpTime() { 
    return LinuxParser::UpTime();
}