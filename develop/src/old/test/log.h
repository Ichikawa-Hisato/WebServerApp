#pragma once

#include <iostream>
#include <string>

#include <chrono>
#include <cstdio> 
#include <ctime>

class Logger {
public:
    void INFO(std::string message) { std::cout << CurrentTime() << " [LOG][INFO]" << message << std::endl; }
    void ERROR(std::string message) { std::cout << CurrentTime() << " [LOG][ERROR]" << message << std::endl; }
private:
    std::string CurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        auto millisec = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        auto decimal = millisec - seconds*1000000;

        //std::cout << "millisec : " << millisec << std::endl;
        //std::cout << "seconds : " << seconds << std::endl;
        //std::cout << "decimal : " << millisec - seconds*1000000 << std::endl;

        // ローカル日時を変数に格納する
        struct tm *local = localtime(&now_time);
        char buf[128];
        strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", local);
        sprintf(buf, "%s.%03ld", buf, decimal);

        return (std::string)buf;
    }
};
