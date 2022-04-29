/*
 * @file aoc_day06_p1.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 06 Part 01.
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
// clang++ -std=c++20 -Wall -o aoc_day06_p1 aoc_day06_p1.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day06_p1 aoc_day06_p1.cc
//

#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>

// Solution overview:
// Read each line of the file into a string 'item' and clean it, so is just 
// has the characters. Add the clean line to a 'std::set' - so only the unique 
// responses for each group are collected. 
// When a blank line ('.emtpy()'') is found in the input file - that
// is one group's record. Add the complete group record to a vector of sets.
// Count the size of each set (ie size of each groups unique responses) and 
// total them all up for the 'answer'.

///////////////////////////////////////////////////////////////////////////////
//                         MAIN ENTRY POINT                                  //
///////////////////////////////////////////////////////////////////////////////

int main()
{
    // puzzle input file stream
    std::ifstream input_file{};

    // Switch comments for 'test'  vs  'final' data file
    //input_file.open("./data/TEST-puzzle-input.txt", std::ios::in);
    input_file.open("./data/puzzle-input.txt", std::ios::in);

    if (not input_file.is_open()) {
        std::cerr << "Error opening puzzle date input file. Aborted." << std::endl;
        std::exit(1);
    }

    // variables to hold input data
    int line_number{0};
    int answer{0};
    int records{0};
    std::string item{};
    std::set<char> group {};
    std::vector<std::set <char>> groups{};

    // read puzzle input delimited by '\n' into 'item' from the file: item == 'BFFFBBFRRR'
    while (std::getline(input_file, item)) {
        line_number++;

        // located blank lines between groups answers - add collects entry to set vector
        if (item.empty()){
            // capture the accumulated group records as is complete 'groups' set
            groups.push_back(group);
            // clear accumulated single record ready
            group.clear();
            // count the records added to the sets vector
            records++;
            // read the next line of the file until EOF
            continue;
        } else {
            // still in a group only record so collect the fields into a single string
            // clean up an new line (ie '\n') from the string.
            std::replace(item.begin(), item.end(), '\n', ' ');
            item.erase(std::remove(item.begin(), item.end(), '\n'), item.end());
            // add the group results to a 'group set'
            for (auto c : item ){
                group.insert(c);
            }
        }

    }
    // capture last group extracted - as not included in file read loop as EOF is before empty record check
    groups.push_back(group);;
    records++;

    // get sizes or each group and total them for the puzzle answer
    for (auto g : groups) {
        answer = answer + g.size();
    }

    ///////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "Advent Of Code 2020 :  Day 06 Part 01" << '\n' << '\n';
    std::cout << "  » Number of line entries analysed : '" << line_number << "' creating '" << records << "' records." << '\n';
    std::cout << "  » PUZZLE ANSWER: sum of all groups 'yes' responses is : " << answer << '\n' << std::endl;

    input_file.close();
    std::exit(0);

    // Part 01 TEST RESULT: 11
    // Part 01 Answer : 6630

    // EXECUTION OUTPUT:
    //
    // % ./aoc_day06_p1
    //
    // Advent Of Code 2020 :  Day 06 Part 01
    //
    //   » Number of line entries analysed : '2195' creating '483' records.
    //   » PUZZLE ANSWER: sum of all groups 'yes' responses is : 6630

}
