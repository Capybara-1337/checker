#include <iostream>
#include <fstream>
int main() {
    std::string path_to_input, path_to_output, path_to_executeables;
    std::cout << "Set path to folder with input files:\n"; std::cin >> path_to_input;
    std::cout << "Set path to folder with output files:\n"; std::cin >> path_to_output;
    std::cout << "Set path to folder with executable files:\n"; std::cin >> path_to_executeables;
    if(path_to_input.back() != '/') path_to_input += '/';
    if(path_to_output.back() != '/') path_to_output += '/';
    if(path_to_executeables.back() != '/') path_to_executeables += '/';
    std::ofstream configure_file("config.txt");
    configure_file << path_to_input << '\n' << path_to_output << '\n' << path_to_executeables;
    configure_file.close();
}