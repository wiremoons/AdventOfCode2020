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
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// loop through a single passport record 'item' and check for 'required_fields' to
// check for the passports records validity
bool isValidPassport(std::string &item, std::vector<std::string> required_fields)
{
    // ensure data has been provided
    if ((item.empty()) or (required_fields.empty())) {
        std::cerr << "ERROR: empty passport record or requirements data passed for validation" << std::endl;
        return false;
    }

    // vector to store the passport fields as pairs
    std::vector<std::pair<std::string, std::string>> passport_fields{};
    // create a stream of the passport record 'item'
    std::stringstream sstream(item);
    std::string field;
    int valid_count{0};

    // using 'item' string stream extract each 'ecl:gry' field as are space separated
    while (getline(sstream, field, ' ')) {

        size_t const colon = field.find_first_of(':');

        // if located a colon - split into the passport fields as a pair and push
        // the pair into main record vector 'passport_fields'
        if (colon not_eq std::string::npos) {
            passport_fields.push_back(std::make_pair(field.substr(0, colon), field.substr(colon + 1, field.length())));
        }
    }

    // for each passport field
    for (auto ppp : passport_fields) {
        // compare to the 'required_fields' to check for validity
        for (auto required : required_fields) {
            // if a validity match occurs - count it
            if (ppp.first == required) {
                valid_count++;
            }
        }
    }

    // clean up stored records and close the string stream
    passport_fields.clear();
    sstream.clear();

    // valid passport record found if it matches all seven 'required_fields'
    if (valid_count == 7) {
        return true;
    }
    // otherwise no validity match
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//                         MAIN ENTRY POINT                                  //
///////////////////////////////////////////////////////////////////////////////

int main()
{
    // puzzle input file stream
    std::ifstream input_file{};
    // vector of passport - each passport entry has pair of strings for the field and filed data
    std::vector<std::pair<std::string, std::string>> passport{};
    // vector of required passport fields - excludes the optional: 'cid'
    std::vector<std::string> required_fields{"byr", "iyr", "eyr", "hcl", "ecl", "pid", "hgt"};

    // Switch comments for 'test'  vs  'final' data file
    // input_file.open("./data/TEST-puzzle-input.txt", std::ios::in);
    input_file.open("./data/puzzle-input.txt", std::ios::in);

    if (not input_file.is_open()) {
        std::cerr << "Error opening puzzle date input file. Aborted." << std::endl;
        std::exit(1);
    }

    // variables to hold input data
    int line_number{0};
    int record_number{0};
    int answer{0};
    std::string passport_item{};
    std::string passport_record{};
    std::vector<std::string> all_passport_records{};

    // read puzzle input delimited by ' ' into 'passport_item' from the file. Empty line designate record end.
    while (std::getline(input_file, passport_item)) {

        // found empty record (blank line) that splits the passport records
        if (passport_item.empty()) {
            // capture the accumulated record as is complete
            all_passport_records.push_back(passport_record);
            // clear accumulated single record ready
            passport_record.clear();
            // do another loop of the input
            continue;
        } else {
            // still in a passport record so collect the fields into a single string
            std::replace(passport_item.begin(), passport_item.end(), '\n', ' ');
            passport_item.erase(std::remove(passport_item.begin(), passport_item.end(), '\n'), passport_item.end());
            passport_record.append(passport_item + " ");
        }
        line_number++;
    }

    // capture last record extracted - as not included in file read loop as EOF is before empty record check
    all_passport_records.push_back(passport_record);

    // use 'all_passport_records' vector of string per record to check validity against 'required_fields'
    for (auto item : all_passport_records) {
        if (isValidPassport(item, required_fields)) {
            answer++;
        }
        record_number++;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "Advent Of Code 2020 :  Day 04 Part 01" << '\n' << '\n';
    std::cout << "  » Number of line entries analysed : '" << line_number << "' for '" << record_number << "' records."
              << '\n';
    std::cout << "  » PUZZLE ANSWER: the number of valid passports is : " << answer << '\n' << std::endl;

    input_file.close();
    std::exit(0);

    // Part 01 TEST RESULT: 7
    // Part 01 Answer : 247

    // EXECUTION OUTPUT:
    //
    // % ./aoc_day04_p1
    //
    // Advent Of Code 2020 :  Day 04 Part 01
    //
    //   » Number of line entries analysed : '818' for '287' records.
    //   » PUZZLE ANSWER: the number of valid passports is : 219
}
