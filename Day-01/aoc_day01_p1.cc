/*
 * @file aoc_day01_p1.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 01 Part 1.
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 *
 * @date originally created: 19 April 2022
 *
 * @details Advent of Code (AOC) 2020 Puzzle solution. See:
 * https://adventofcode.com/2020/
 */

//
// Build with:
// clang++ -std=c++20 -Wall -o aoc_day01_p1 aoc_day01_p1.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day01_p1 aoc_day01_p1.cc
//

#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// GLOBALS
// set if debug output is needed
bool debug{false};

/// @brief Compare the expenses records to find two that total '2020'
/// @param expenses : the vector of expenses as integers
/// @ return the two expenses integers identified multiplied together
int calculateProduct(std::vector<int> &expenses)
{
    int result{0};
    std::cout << "\n\nFinding correct expenses records (slow) to total '2020'..." << std::endl;
    for (size_t i{0}; i < expenses.size(); i++) {
        for (size_t j{0}; j < expenses.size(); j++) {
            if (expenses.at(i) + expenses.at(j) == 2020) {
                std::cout << "Expense records: " << expenses.at(i) << " + " << expenses.at(j) << " = "
                          << expenses.at(i) + expenses.at(j) << std::endl;
                return expenses.at(i) * expenses.at(j);
            }
        }
    }

    return result;
}

/// @brief Compare the expenses records to find two that total '2020'
/// @param expenses : the vector of expenses as integers
/// @ return the two expenses integers identified multiplied together
int calculateProductFast(std::vector<int> &expenses)
{
    int result{0};
    std::cout << "\n\nFinding correct expenses records (fast) to total '2020'..." << std::endl;

    // first sort the expenses list for the binary search
    std::sort(expenses.begin(), expenses.end());

    // loop through expenses records - find match using binary search
    for (auto expense : expenses) {
        int locate = 2020 - expense;
        if ((locate > expense) and (std::binary_search(expenses.begin(), expenses.end(), locate))) {
            std::cout << "Expense records: " << expense << " + " << locate << " = " << expense + locate << std::endl;
            return expense * locate;
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

    // Switch comments for 'test'  vs  'final' data file
    // input_file.open("./data/TEST-puzzle-input.txt", std::ios::in);
    input_file.open("./data/puzzle-input.txt", std::ios::in);

    if (not input_file.is_open()) {
        std::cerr << "Error opening puzzle date input file. Aborted." << std::endl;
        std::exit(1);
    }

    // variables to hold input data
    std::string line{};
    std::vector<int> expenses{0};
    int line_number{0};
    int answer{0};

    // read each line delimited by '\n' into 'line' from the file
    // convert to an integer and add to the vector of int 'expenses'.
    while (std::getline(input_file, line)) {
        try {
            line_number++;
            expenses.push_back(std::stoi(line));
        } catch (std::exception &e) {
            std::cerr << "ERROR: failed to convert to integer on line: " << line_number << std::endl;
            std::cerr << "Exception thrown was: " << e.what() << std::endl;
            std::exit(1);
        }
        line_number++;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    answer = calculateProduct(expenses);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_slow = duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Answer (slow): " << answer << std::endl;
    std::cout << "--> Time taken by function: " << duration_slow.count() << " nanoseconds" << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    answer = calculateProductFast(expenses);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto duration_fast = duration_cast<std::chrono::nanoseconds>(t4 - t3);
    std::cout << "Answer (fast): " << answer << std::endl;
    std::cout << "--> Time taken by function: " << duration_fast.count() << " nanoseconds" << std::endl;

    std::cout << std::endl << "Advent Of Code 2020 :  Day 01 Part 01" << '\n' << '\n';
    std::cout << "  » Number of expenses entries analysed : '" << line_number << "'" << '\n';
    std::cout << "  » PUZZLE ANSWER: two entries that sum to 2020 multiplied together : " << answer << '\n'
              << std::endl;

    // Part 1 TEST RESULT: 514579
    // Part 1 Answer : 567171

    input_file.close();
    std::exit(0);
}
