/*
 * @file aoc_day08_p1.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 08 Part 01.
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 *
 * @date originally created: 28 Sep 2022
 *
 * @details Advent of Code (AOC) 2020 Puzzle solution. See:
 * https://adventofcode.com/2020/
 */

//
// Build with:
// clang++ -std=c++20 -Wall -o aoc_day08_p1 aoc_day08_p1.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day08_p1 aoc_day08_p1.cc
//

#include <fstream>
#include <iostream>
#include <string>

// Solution overview:
// Read each line of the file into a string 'item' and

///////////////////////////////////////////////////////////////////////////////
//                         MAIN ENTRY POINT                                  //
///////////////////////////////////////////////////////////////////////////////

int main()
{
    // puzzle input file stream
    std::ifstream input_file{};

    // Switch comments for 'test'  vs  'final' data file
    input_file.open("./data/TEST-puzzle-input.txt", std::ios::in);
    // input_file.open("./data/puzzle-input.txt", std::ios::in);

    if (not input_file.is_open()) {
        std::cerr << "Error opening puzzle date input file. Aborted." << std::endl;
        std::exit(1);
    }

    // variables to hold input data
    int line_number{0};
    int answer{0};
    std::string item{};

    // read puzzle input delimited by '\n' into 'item' from the file: item == 'BFFFBBFRRR'
    while (std::getline(input_file, item)) {
        line_number++;
    }

    ///////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "Advent Of Code 2020 :  Day 08 Part 01" << '\n' << '\n';
    std::cout << "  » Number of line entries analysed : '" << line_number << "'." << '\n';
    std::cout << "  » PUZZLE ANSWER: value of the accumulator before any instruction is executed a second time : " << answer
              << '\n'
              << std::endl;

    input_file.close();
    std::exit(0);

    // Part 01 TEST RESULT: 5
    // Part 02 Answer :

    // EXECUTION OUTPUT:
    //
    // %
}
