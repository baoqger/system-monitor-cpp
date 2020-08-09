#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// constructor
Process::Process(int pid, float cpuUtil, std::string command, std::string userId, std::string userName, std::string ram, long upTime) {
    this->pid = pid;
    this->cpuUtil = cpuUtil;
    this->command = command;
    this->userId = userId;
    this->userName = userName;
    this->ram = ram;
    this->upTime = upTime;
}

// TODO: Return this process's ID
int Process::Pid() { 
    return pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return cpuUtil; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return command; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return ram; 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return userName; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return upTime; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
