#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ReadFile {
public:
    int Read(std::string file_path) {
        std::ifstream ifs(file_path);
        int buf_size = 100;

        char str[buf_size];
        if (ifs.fail()) {
            std::cerr << "Failed to open file." << std::endl;
            return -1;
        }
        while (ifs.getline(str, buf_size)) {
            file_data.push_back(str);
            file_data_record = file_data_record + str;
            std::cout << "#" << str << std::endl;
        }
        return 0;
    }

    int FileSize() {
        file_size = 0;
        std::cout << "[DEBUG][LOG][file.cpp] filesize : " << file_data.size() << std::endl;
        for (int i = 0; i < (int)file_data.size(); i++) {
            std::cout << "[DEBUG][LOG][file.cpp] filesize for : " << i << std::endl;
            file_size += (int)file_data[i].size();
        }
        return file_size;
    }

    std::string FileDataRecord() { return file_data_record; }
private:
    std::vector<std::string> file_data;
    std::string file_data_record = "";
    int file_size;
};

class WriteFile {

};
