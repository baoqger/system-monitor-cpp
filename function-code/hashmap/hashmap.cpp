#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>

float MemoUtil() {
    const std::string kProcDirectory{"/proc/"};
    const std::string kMeminfoFilename{"/meminfo"};
    
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

int main() {
    float memUtils = MemoUtil();
    std::cout << memUtils << std::endl;
    return 0;
}