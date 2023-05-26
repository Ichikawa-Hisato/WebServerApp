#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ReadFile {
public:
    int Read(std::string file_path) {
        std::ifstream ifs(file_path);
        std::string str;

        if (ifs.fail()) {
            std::cerr << "Failed to open file." << std::endl;
            return -1;
        }
        while (getline(ifs, str)) {
            file_data.push_back(str);
            file_data_record = file_data_record + str;
        }
        return 0;
    }

    int FileSize() { return file_data_record.size(); }
    int FileLine() { return file_data.size(); }
    std::string FileData(int line) { return file_data[line]; }
    std::string FileDataRecord() { return file_data_record; }
private:
    std::vector<std::string> file_data;
    std::string file_data_record = "";
    int file_size;
};

class WriteFile {
public:
    void Write(std::string file_path) {
        std::ofstream ofs(file_path);
        for (int i = 0; i < file_data.size(); i++) {
            ofs << file_data[i] << std::endl;
        }
    }
    void AddFileData(std::string data) { return file_data.push_back(data); }
private:
    std::vector<std::string> file_data;
};
