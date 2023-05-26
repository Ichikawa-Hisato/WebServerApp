#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Read {
public:
    int ReadFile(std::string file_path) {
        std::ifstream ifs(file_path);
        std::string str;

        if (ifs.fail()) {
            std::cerr << "Failed to open file." << std::endl;
            return -1;
        }
        while (getline(ifs, str)) {
            file_data.push_back(str);
        }
        return 0;
    }

    int LineSize() { return file_data.size(); }
    std::string GetLine(int line) { return file_data[line]; }
private:
    std::vector<std::string> file_data;
};

class Write {
public:
    void WriteFile(std::string file_path) {
        std::ofstream ofs(file_path);
        for (int i = 0; i < file_data.size(); i++) {
            ofs << file_data[i] << std::endl;
        }
    }
    void AddFile(std::string data) { return file_data.push_back(data); }
private:
    std::vector<std::string> file_data;
};
