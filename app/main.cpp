#include "../include/eventsprocessing.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    // Открываем файл
    std::string path = argv[1];
    (void)argc;
    std::vector<std::string> lines; // Строки, прочтённые из файла
    std::string line;
    std::ifstream inputFile(path);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();
    } else {
        std::cout << "Unable to open file";
        return 1;
    }

    // Парсим данные через класс ParseData,
    // затем обрабатываем через класс EventProcessor
    ParseData pd(lines);
    EventProcessor ep(pd);
    ep.processing();
    ep.ServiceClosed(); // Завершающее событие

}