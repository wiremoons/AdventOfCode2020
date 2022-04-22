/*
 * @file aoc_day03_p2.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 03 Part 02.
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 *
 * @date originally created: 22 April 2022
 *
 * @details Advent of Code (AOC) 2020 Puzzle solution. See:
 * https://adventofcode.com/2020/
 */

//
// Build with:
// clang++ -std=c++20 -Wall -o aoc_day03_p2 aoc_day03_p2.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day03_p2 aoc_day03_p2.cc
//

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int getTreeCount(std::vector<std::string> const &tree_map, int const move_x, int const move_y)
{
    int pos_x{0}, pos_y{0}, result{0};
    int const max_x = (tree_map.at(0).length() - 1);

    while (pos_y < (tree_map.size() - 1)) {
        pos_y = pos_y + move_y;
        pos_x = pos_x + move_x;
        // wrap map if on right hand edge
        pos_x > max_x ? pos_x = 0 + ((pos_x - max_x) - 1) : pos_x;
        // read current map point character
        char map_point = tree_map.at(pos_y).at(pos_x);
        if (map_point == '#') {
            result++;
        }
    }

    return result;
}

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
    // input_file.open("./data/TEST-puzzle-input.txt", std::ios::in);
    input_file.open("./data/puzzle-input.txt", std::ios::in);

    if (not input_file.is_open()) {
        std::cerr << "Error opening puzzle date input file. Aborted." << std::endl;
        std::exit(1);
    }

    // variables to hold input data
    std::string line{};
    int line_number{0};
    long answer{0};

    // read puzzle input each line delimited by '\n' into 'line' from the file
    while (std::getline(input_file, line)) {
        tree_map.push_back(line);
        line_number++;
    }

    answer = getTreeCount(tree_map, 1, 1);
    answer = answer * getTreeCount(tree_map, 3, 1);
    answer = answer * getTreeCount(tree_map, 5, 1);
    answer = answer * getTreeCount(tree_map, 7, 1);
    answer = answer * getTreeCount(tree_map, 1, 2);

    // end timer calculation
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_slow = duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Answer: " << answer << std::endl;
    std::cout << "--> Time taken by function: " << duration_slow.count() << " microseconds" << std::endl;

    std::cout << std::endl << "Advent Of Code 2020 :  Day 03 Part 02" << '\n' << '\n';
    std::cout << "  » Number of grid line entries analysed : '" << line_number << "'" << '\n';
    std::cout << "  » PUZZLE ANSWER: product of tree encountered moving 5 different routes is : " << answer << '\n'
              << std::endl;

    input_file.close();
    std::exit(0);

    // Part 02 TEST RESULT: 7
    // Part 02 Answer : 2983070376

    // EXECUTION OUTPUT:
    //
    // % ./aoc_day03_p2
    // Answer: 2983070376
    // --> Time taken by function: 1374 microseconds
    //
    // Advent Of Code 2020 :  Day 03 Part 02
    //
    //   » Number of grid line entries analysed : '323'
    //   » PUZZLE ANSWER: product of tree encountered moving 5 different routes is : 2983070376
}
