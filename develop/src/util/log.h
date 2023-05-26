#pragma once

#include <iostream>
#include <string>

#include <chrono>
#include <cstdio> 
#include <ctime>

#define SIZE (100*1024)

class Logger {
public:
    void INFO(std::string message) { std::cout << CurrentTime() << " [LOG][INFO]" << message << std::endl; }
    void ERROR(std::string message) { std::cout << CurrentTime() << " [LOG][ERROR]" << message << std::endl; }
private:
    std::string CurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        auto microsec = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
        //auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        auto decimal = microsec - seconds*1000000;

        // ローカル日時を変数に格納する
        struct tm *local = localtime(&now_time);
        char buf[SIZE];
        strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S.", local);
        std::string current_time = (std::string)buf + std::to_string(decimal);

        return current_time;
    }
};
