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

const std::string getPasswordString(std::string const &line)
{
    std::string result{};

    if (not line.length()) {
        std::cerr << "ERROR: empty line found in input file" << std::endl;
        return result;
    }

    size_t const colon = line.find(':');
    if (colon not_eq std::string::npos) {
        return result = line.substr(colon + 2);
    }
    return result;
}

/// @brief Extract the policy elements from the input file line: '1-3 a: abcde'
/// @param line : the line of text read from the puzzle input file
/// @ return the extracted policy range as a number pair
const std::pair<int, int> getPolicyPair(std::string const &line)
{
    std::pair<int, int> result{};

    if (not line.length()) {
        std::cerr << "ERROR: empty line found in input file" << std::endl;
        return result;
    }

    size_t const space = line.find_first_of(' ');
    size_t const dash = line.find('-');

    if ((dash not_eq std::string::npos) and (space not_eq std::string::npos)) {
        try {
            auto const result =
                std::make_pair(std::stoi(line.substr(0, dash)), std::stoi(line.substr(dash + 1, space)));
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
const char getPolicyValue(std::string const &line)
{
    char result{};

    if (not line.length()) {
        std::cerr << "ERROR: empty line found in input file" << std::endl;
        return result;
    }

    size_t const space = line.find_first_of(' ');

    if (space not_eq std::string::npos) {
        char const result = line.at(space + 1);
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

    // start timer for overall execution
    auto const t1 = std::chrono::high_resolution_clock::now();

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
        std::string const password = getPasswordString(line);
        [[maybe_unused]] std::pair<int, int> const policy = getPolicyPair(line);
        char const policy_value = getPolicyValue(line);

        size_t const occurs = count(password.begin(), password.end(), policy_value);
        // check if password is in the required policy range
        if ((occurs >= policy.first) and (occurs <= policy.second)) {
            answer++;
        }
    }

    auto const t2 = std::chrono::high_resolution_clock::now();
    auto const duration = duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Answer: " << answer << std::endl;
    std::cout << "--> Time taken by function: " << duration.count() << " microseconds" << std::endl;

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
    // --> Time taken by function:  4155 microseconds
    //
    // Advent Of Code 2020 :  Day 02 Part 01
    //
    //   » Number of password entries analysed : '1000'
    //   » PUZZLE ANSWER: number of valid passwords according to their policies : 483
}
