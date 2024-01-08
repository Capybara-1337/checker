#include <iostream>
#include <fstream>
#include <string>
int main() {
    int tests; bool is_equal;
    std::string exe_name, command, expected_line, out_line, in_path, out_path, executables_path;
    std::ifstream expected_out_file, out_file, configure_file("config.txt");
    std::ofstream result_file;
    std::cout << "Amount of tests (an integer): ";
    std::cin >> tests;
    std::cout << "Name of the executable and tests: ";
    std::cin >> exe_name;
    result_file.open(exe_name + "_results.txt");
    if (!result_file) {
      std::cerr << "Failed to open " << exe_name + "_results.txt" << "\n";
      return 1;
    }
    if(!configure_file) {
        std::cerr << "Couldn't access the configuration file!\n";
        return 1;
    }
    getline(configure_file, in_path); getline(configure_file, out_path); getline(configure_file, executables_path);
    // std::cout << in_path << out_path << executables_path;
    for(int i = 1; i <= tests; i++) {
        std::cout << "Attempting to open: " << out_path << exe_name << std::to_string(i) << ".out\n";
        expected_out_file.open(out_path + exe_name + std::to_string(i) + ".out");
        if(!expected_out_file)  {
            std::cerr << "Error opening expected output file!\n"; 
            std::cout << "Writing to result_file: Test " << i << ": Error (missing file)\n";
            result_file << "Test " << i << ": Error (missing file)\n";
            continue;
        }
        command = executables_path + exe_name + " < " + in_path + exe_name + std::to_string(i) + ".in > " + exe_name + std::to_string(i) + "_temp.out";
        system(command.c_str());
        std::cout << "Attempting to open: " << exe_name << std::to_string(i) << "_temp.out\n";
        out_file.open(exe_name + std::to_string(i) + "_temp.out");
        if(!out_file) {
            std::cerr << "Error opening output file!\n";
            std::cout << "Writing to result_file: Test " << i << ": Error (missing file)\n";
            result_file << "Test " << i << ": Error (missing file)\n";
            continue;
        }
        if(std::remove((exe_name + std::to_string(i) + "_temp.out").c_str()) == 0) {
            std::cout << "Deleted temp file!\n";
        } else {
            std::cout << "Unable to delete temp file!\n";
        }
        is_equal = 1;
        while(getline(expected_out_file, expected_line) && getline(out_file, out_line)) {
            std::cout << "Expected line: " << expected_line << "\n";
            std::cout << "Actual line: " << out_line << "\n";
            if(expected_line != out_line) {
                std::cout << i << " DID NOT PASS -> actual line:\n\t" << out_line << "\nand expected line:\n\t" << expected_line << '\n';
                std::cout << "Writing to result_file: Test " << i << ": Didn't pass\n";
                result_file << "Test " << i << ": Didn't pass\n";
                result_file.flush();
                is_equal = 0;
                break;
            }
        }
        if(is_equal) {
            std::cout << "Writing to result_file: Test " << i << ": Passed\n";
            result_file << "Test " << i << ": Passed\n";
            result_file.flush();
        }
        out_file.close();
        expected_out_file.close();
    }
    result_file.close();
}