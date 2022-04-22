/*
 * @file aoc_day02_p1.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 02 Part 1.
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
// clang++ -std=c++20 -Wall -o aoc_day02_p1 aoc_day02_p1.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day02_p1 aoc_day02_p1.cc
//

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

/// @brief Extract the password element from the input file line: '1-3 a: abcde'
/// @param line : the line of text read from the puzzle input file
/// @ return the extracted password string
using std::count;

std::string getPasswordString(std::string &line)
{
    std::string result{};

    if (not line.length()) {
        std::cerr << "ERROR: empty line found in input file" << std::endl;
        return result;
    }

    const size_t colon = line.find(':');
    if (colon not_eq std::string::npos) {
        return result = line.substr(colon + 2);
    }
    return result;
}

/// @brief Extract the policy elements from the input file line: '1-3 a: abcde'
/// @param line : the line of text read from the puzzle input file
/// @ return the extracted policy range as a number pair
std::pair<int, int> getPolicyPair(std::string &line)
{
    std::pair<int, int> result{};

    if (not line.length()) {
        std::cerr << "ERROR: empty line found in input file" << std::endl;
        return result;
    }

    const size_t space = line.find_first_of(' ');
    const size_t dash = line.find('-');

    if ((dash not_eq std::string::npos) and (space not_eq std::string::npos)) {
        try {
            auto result = std::make_pair(std::stoi(line.substr(0, dash)), std::stoi(line.substr(dash + 1, space)));
            return result;
        } catch (std::exception &e) {
            std::cerr << "ERROR: failed to find policy entries with exception: " << e.what() << std::endl;
            return result;
        }
    }
    return result;
}

/// @brief Extract the policy elements from the input file line: '1-3 a: abcde'
/// @param line : the line of text read from the puzzle input file
/// @ return the extracted policy range as a number pair
char getPolicyValue(std::string &line)
{
    char result{};

    if (not line.length()) {
        std::cerr << "ERROR: empty line found in input file" << std::endl;
        return result;
    }

    const size_t space = line.find_first_of(' ');

    if (space not_eq std::string::npos) {
        result = line.at(space + 1);
        return result;
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
    int line_number{0};
    int answer{0};

    // read each line delimited by '\n' into 'line' from the file
    // extract required parts and count valid passwords.
    while (std::getline(input_file, line)) {
        line_number++;
        std::string password = getPasswordString(line);
        [[maybe_unused]] std::pair<int, int> policy = getPolicyPair(line);
        char policy_value = getPolicyValue(line);

        size_t occurs = count(password.begin(), password.end(), policy_value);
        // check if password is in the required policy range
        if ((occurs >= policy.first) and (occurs <= policy.second)) {
            answer++;
        }
        // reset
        occurs = -1;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    // function here
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_slow = duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Answer: " << answer << std::endl;
    std::cout << "--> Time taken by function: " << duration_slow.count() << " nanoseconds" << std::endl;

    std::cout << std::endl << "Advent Of Code 2020 :  Day 02 Part 01" << '\n' << '\n';
    std::cout << "  » Number of password entries analysed : '" << line_number << "'" << '\n';
    std::cout << "  » PUZZLE ANSWER: number of valid passwords according to their policies : " << answer << '\n'
              << std::endl;

    input_file.close();
    std::exit(0);

    // Part 1 TEST RESULT: 2
    // Part 1 Answer : 483

    // EXECUTION OUTPUT:
    //
    // % ./aoc_day02_p1
    //
    //     Answer: 483
    // --> Time taken by function: 42 nanoseconds
    //
    // Advent Of Code 2020 :  Day 02 Part 01
    //
    //   » Number of password entries analysed : '1000'
    //   » PUZZLE ANSWER: number of valid passwords according to their policies : 483
}
