#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <iomanip>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return version;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
    std::ifstream stream{kProcDirectory + kMeminfoFilename};

    if (!stream.is_open()) {
        std::cout << "failed to open /proc/meminfo file" << std::endl;
    }

    std::map<std::string, int> memoUsage;
    std::string line;
    std::string key;
    int value;
    while (std::getline(stream, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream streamline{line};
        streamline >> key >> value;
        memoUsage.emplace(key, value);
    }
    int  totalMemo = memoUsage["MemTotal"];
    int  freeMemo = memoUsage["MemFree"];
    return (totalMemo - freeMemo) / static_cast<float>(totalMemo);  
}

// TODO: Read and return the system uptime
long int LinuxParser::UpTime() {
  std::ifstream stream{kProcDirectory + kUptimeFilename};
  if(!stream.is_open()) {
    std::cout << "failed to open proc/uptime file" << std::endl;
  }
  std::string line;
  std::getline(stream, line);
  std::istringstream streamline{line};

  std::istream_iterator<string> beg{streamline}, end;
  std::vector<string> values{beg, end};
  return std::stoi(values[0]);
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
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

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream stream{kProcDirectory + std::to_string(pid) + kCmdlineFilename};
  std::getline(stream, line);
  return line;
}


string LinuxParser::Ram(int pid) { 
  std::string line;
  std::string name{"VmData"};
  std::string value;
  float result;
  std::stringstream resultStream;
  std::ifstream stream{kProcDirectory + std::to_string(pid) + kStatusFilename};
  while(std::getline(stream, line)) {
    if(line.compare(0, name.size(), name) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<string> beg(buf), end;
      std::vector<string> values(beg, end);
      result = (stof(values[1])/float(1024));
      break;
    }
  };
  resultStream << std::fixed << std::setprecision(2) << result;
  return resultStream.str();
}

string LinuxParser::Uid(int pid) { 
  std::string line;
  std::string name{"uid"};
  std::string result;
  std::ifstream stream{kProcDirectory + std::to_string(pid) + kStatusFilename};
  while(std::getline(stream, line)) {
    if(line.compare(0, name.size(), name) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      result = values[1];
      break;
    }
  }
  return result;
}

string LinuxParser::User(int pid) {
  std::ifstream stream{kPasswordPath};
  std::string name{"x:" + Uid(pid)};
  std::string result;
  std::string line;
  while(std::getline(stream, line)) {
    if(line.find(name) != std::string::npos) {
      result = line.substr(0, line.find(":"));
      break;
    }
  }
  return result;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { return 0; }