#include <iostream>
#include "file.h"

int main(void)
{
    Write writer;
    Read reader;
    std::string file_path = "./sample_text.txt";

    writer.AddFile("Hello,World");
    writer.AddFile("Hello,World!");
    writer.AddFile("Hello,World!!");
    writer.WriteFile(file_path);

    reader.ReadFile(file_path);
    std::cout << reader.GetLine(0) << std::endl;
    std::cout << reader.GetLine(2) << std::endl;
    std::cout << reader.GetLine(1) << std::endl;
}
