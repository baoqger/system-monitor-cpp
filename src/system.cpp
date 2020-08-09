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

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    vector<int> pids = LinuxParser::Pids();
    for (auto pid : pids) {
        Process process{
            pid,
            0.0,
            LinuxParser::Command(pid),
            LinuxParser::Uid(pid),
            LinuxParser::User(pid),
            LinuxParser::Ram(pid),
            LinuxParser::UpTime(pid)
        };
        processes_.emplace_back(process);
    }
    // for (auto p : processes_) {
    //     std::cout << "pid: " << p.Pid() << std::endl;
    //     std::cout << "cpu: " << p.CpuUtilization() << std::endl;
    //     std::cout << "ram: " << p.Ram() << std::endl;
    //     std::cout << "user: " << p.User() << std::endl;
    //     std::cout << "command: " << p.Command() << std::endl;
    // }
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel();
 }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
 }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime();
}