/*
 * @file aoc_day05_p2.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 05 Part 02.
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 *
 * @date originally created: 24 April 2022
 *
 * @details Advent of Code (AOC) 2020 Puzzle solution. See:
 * https://adventofcode.com/2020/
 */

//
// Build with:
// clang++ -std=c++20 -Wall -o aoc_day05_p2 aoc_day05_p2.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day05_p2 aoc_day05_p2.cc
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// NB: The full row and col can be converted together to obtain the answer of seatID
// in one calculation. First convert to binary equivalents than convert binary to
// decimal to get the actual seat ID.
//
// Example conversion:
// F == 0 and B == 1  and  L == 0 and R == 1
// Each positions binary value: 512, 256, 128, 64, 32, 16, 8, 4, 2, 1
// BFFFBBFRRR == 1000110111 == 512+0+0+0+32+16+0+4+2+1 == 567
// Where 567 is the 'Seat ID' that is needed for the answer!

// translate the seat row (F or B) or seat col (L or R) to equivalent binary representation:
char convertToBinaryChar(char c)
{
    if (c == 'F') {
        return '0';
    }
    if (c == 'B') {
        return '1';
    }
    if (c == 'L') {
        return '0';
    }
    if (c == 'R') {
        return '1';
    }
    return c;
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
    int line_number{0};
    int answer{0};
    std::string item{};
    std::vector<int> all_seat_ids{};

    // read puzzle input delimited by '\n' into 'item' from the file: item == 'BFFFBBFRRR'
    while (std::getline(input_file, item)) {
        // convert: F == 0 or B == 1 or L == 0 or R == 1 with 'convertToBinaryChar' function;
        std::transform(item.begin(), item.end(), item.begin(), convertToBinaryChar);
        // convert binary to decimal and place in the vector of in 'all_seat_ids'
        all_seat_ids.push_back(std::stoi(item, 0, 2));
        line_number++;
    }
    // sort all the Seat ID to the largest number can be extracted for the answer
    std::sort(all_seat_ids.begin(), all_seat_ids.end());

    // calculate our seat for Part 02 answer
    auto seat_id =
        std::adjacent_find(all_seat_ids.begin(), all_seat_ids.end(), [](auto l, auto r) { return r == l + 2; });
    answer = *seat_id + 1;

    ///////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "Advent Of Code 2020 :  Day 05 Part 02" << '\n' << '\n';
    std::cout << "  » Number of line entries analysed : '" << line_number << "'." << '\n';
    std::cout << "  » PUZZLE ANSWER: Your Seat ID is : " << answer << '\n' << std::endl;

    input_file.close();
    std::exit(0);

    // Part 02 TEST RESULT: 1
    //      BFFFBBF RRR: row 70, column 7, seat ID 567.
    //      FFFBBBFRRR: row 14, column 7, seat ID 119.
    //      BBFFBBFRLL: row 102, column 4, seat ID 820.
    // Part 02 Answer : 727

    // EXECUTION OUTPUT:
    //
    // % ./aoc_day05_p2
    //
    // Advent Of Code 2020 :  Day 05 Part 02
    //
    //   » Number of line entries analysed : '965'.
    //   » PUZZLE ANSWER: Your Seat ID is : 727
    //
}
