#include "httplib.h"
#include <iostream>

class FileReader {
public:
    int Read(std::string file_path) {
        std::ifstream ifs(file_path);
        std::string str = "";
        record_data = "";

        if (ifs.fail()) {
            std::cerr << "Failed to open file." << std::endl;
            return -1;
        }
        while (getline(ifs, str)) {
            record_data += str;
        }
        return 0;
    }
    std::string GetRecord() { return record_data; }
private:
    std::string record_data;
};

int main(void)
{
    using namespace httplib;
    Server svr;
    FileReader reader;

    std::cout << "start Server" << std::endl;

    std::string file_path = "../html";

    svr.Get("/", [&](const Request& req, Response& res) {
        reader.Read(file_path + "/index.html");
        std::string html = reader.GetRecord();
        res.set_content(html, "text/html");
    });

    svr.Get(R"(/(.+))", [&](const Request& req, Response& res) {
        reader.Read(file_path + req.target);
        std::string html = reader.GetRecord();
        res.set_content(html, "text/html");
    });

    svr.listen("127.0.0.1", 8080);
}
