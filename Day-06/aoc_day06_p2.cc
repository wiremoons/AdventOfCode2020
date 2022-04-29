/*
 * @file aoc_day06_p2.cc
 * @brief Advent of Code (AOC) 2020 Puzzle solution for:  Day 06 Part 02.
 *
 * @author Simon Rowe <simon@wiremoons.com>
 * @license open-source released under "MIT License"
 *
 * @date originally created: 29 April 2022
 *
 * @details Advent of Code (AOC) 2020 Puzzle solution. See:
 * https://adventofcode.com/2020/
 */

//
// Build with:
// clang++ -std=c++20 -Wall -o aoc_day06_p2 aoc_day06_p2.cc
//   or
// g++ -std=c++20 -Wall -o aoc_day06_p2 aoc_day06_p2.cc
//

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Solution overview:
// Read each line of the file into a string 'item' and clean it, so is just
// has the characters. Add the clean line to a 'std::map' - so each character
// has a value. Read the rest of the groups answers and also add each answer
// (ie character) to the same 'std::map'. At the end of reading the group
// responses, each response and number of times it was given will be available
// as a key value par in the std::map. Use the number of responses given in the
// group (ie 'group_number') to find any responses that are common to all.
// When a blank line ('.emtpy()'') is found in the input file - that
// is one group's record completed. Add the complete group 'common to all'
// responses to the all 'groups' vector. Count the total entries in the
// 'groups' for the answer.

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
    int records{0};
    int group_number{0};
    std::string item{};
    std::map<char, int> group{};
    std::vector<std::map<char, int>> groups{};

    // read puzzle input delimited by '\n' into 'item' from the file: item == 'BFFFBBFRRR'
    while (std::getline(input_file, item)) {
        line_number++;

        // located blank lines between groups answers - add collects entry to set vector
        if (item.empty()) {
            // get the intersection of the accumulated group records
            // if the total number of group members matches a response,
            // the response is common to all - so the intersection for that group.
            for (auto &[k, v] : group) {
                if (v == group_number) {
                    groups.push_back(group);
                }
            }
            // clear accumulated single record ready and the group members count
            group.clear();
            group_number = 0;
            // count the records added to the sets vector
            records++;
            // read the next line of the file until EOF
            continue;
        } else {
            group_number++;
            // in a group only record so collect the responses into a single string
            // clean it up by removing any new line (ie '\n') from the string.
            std::replace(item.begin(), item.end(), '\n', ' ');
            item.erase(std::remove(item.begin(), item.end(), '\n'), item.end());
            // add each persons response to a 'group map' of responses (ie key 'c' is the response)
            // and value (ie how many times the response if given).
            for (auto c : item) {
                group[c]++;
            }
        }
    }
    // capture last group extracted - as not included in file read loop as EOF is before empty record check
    for (auto &[k, v] : group) {
        if (v == group_number) {
            groups.push_back(group);
        }
    }
    records++;

    // get the total per group unique (intersection) responses for the puzzle answer
    answer = groups.size();

    ///////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "Advent Of Code 2020 :  Day 06 Part 02" << '\n' << '\n';
    std::cout << "  » Number of line entries analysed : '" << line_number << "' creating '" << records << "' records."
              << '\n';
    std::cout << "  » PUZZLE ANSWER: sum of all groups 'everyone answered yes' responses is : " << answer << '\n'
              << std::endl;

    input_file.close();
    std::exit(0);

    // Part 02 TEST RESULT: 6
    // Part 02 Answer : 3437

    // EXECUTION OUTPUT:
    //
    // % ./aoc_day06_p2
    //
    // Advent Of Code 2020 :  Day 06 Part 02
    //
    //   » Number of line entries analysed : '2195' creating '483' records.
    //   » PUZZLE ANSWER: sum of all groups 'everyone answered yes' responses is : 3437
}
