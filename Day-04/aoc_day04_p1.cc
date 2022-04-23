/*
 * @file aoc_day04_p1.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 04 Part 01.
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 *
 * @date originally created: 23 April 2022
 *
 * @details Advent of Code (AOC) 2020 Puzzle solution. See:
 * https://adventofcode.com/2020/
 */

//
// Build with:
// clang++ -std=c++20 -Wall -o aoc_day04_p1 aoc_day04_p1.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day04_p1 aoc_day04_p1.cc
//

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>


///////////////////////////////////////////////////////////////////////////////
//                         MAIN ENTRY POINT                                  //
///////////////////////////////////////////////////////////////////////////////

int main()
{
    // puzzle input file stream
    std::ifstream input_file{};

    // vector of strings to hold puzzle input map for route calculation
    std::vector<std::string> tree_map{};

    // start timer for overall execution
    auto t1 = std::chrono::high_resolution_clock::now();

    // Switch comments for 'test'  vs  'final' data file
     input_file.open("./data/TEST-puzzle-input.txt", std::ios::in);
    // input_file.open("./data/puzzle-input.txt", std::ios::in);

    if (not input_file.is_open()) {
        std::cerr << "Error opening puzzle date input file. Aborted." << std::endl;
        std::exit(1);
    }

    // variables to hold input data
    std::string line{};
    int line_number{0};
    int answer{0};

    // read puzzle input each line delimited by '\n' into 'line' from the file
    while (std::getline(input_file, line)) {
        line_number++;
    }


    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_slow = duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Answer: " << answer << std::endl;
    std::cout << "--> Time taken by function: " << duration_slow.count() << " microseconds" << std::endl;

    std::cout << std::endl << "Advent Of Code 2020 :  Day 04 Part 01" << '\n' << '\n';
    std::cout << "  » Number of grid line entries analysed : '" << line_number << "'" << '\n';
    std::cout << "  » PUZZLE ANSWER: the number of valid passports is : " << answer
              << '\n'
              << std::endl;

    input_file.close();
    std::exit(0);

    // Part 01 TEST RESULT: 7
    // Part 01 Answer : 247

    // EXECUTION OUTPUT:
    //
    // % ./aoc_day04_p1

}
