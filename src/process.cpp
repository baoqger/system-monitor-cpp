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

int Process::Pid() { 
    return pid;
}

float Process::CpuUtilization() { 
    return cpuUtil; 
}

string Process::Command() { 
    return command; 
}

string Process::Ram() { 
    return ram; 
}

string Process::User() { 
    return userName; 
}

long int Process::UpTime() { 
    return upTime; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
