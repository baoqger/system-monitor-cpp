#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

void streamInterator() {
    std::string fileName{"./test.txt"};
    std::ifstream stream{fileName};
    if (!stream.is_open()) {
        std::cout << "failed to open test.txt file" << std::endl;
    }
    std::string line;
    std::getline(stream, line);
    // std::cout << "file content" << line << std::endl;

    std::istringstream streamline{line};
    std::istream_iterator<std::string> beg(streamline);
    std::istream_iterator<std::string> end; 
    std::vector<std::string> values{beg, end};
}


int main() {
    streamInterator();
    int time{5800};
    int h = time/3600;
    time = time%3600;
    int m = time/60;
    int s = time%60;
    std::cout << h << std::endl;
    std::cout << m << std::endl;
    std::cout << s << std::endl;
    return 0;
}