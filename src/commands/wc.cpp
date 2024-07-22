#include <fstream>
#include <string>
#include <sstream>
#include "../../include/command.hpp"

// constructor for WcCommand objects
WcCommand::WcCommand(const vector<string>& new_tokens) : Command (new_tokens) {
    // set all options to true by default
    command_options['l'] = true, command_options['w'] = true; command_options['c'] = true;

    // handle any user input options
    options_handler();

    // if an illegal option is not found, then continue with main command functionality
    if (!invalid_option_found) wc_fn();
};

/**
 * @brief helper function to count words, characters and lines of a file.
 *
 * This function counts words, characters and lines from the input file,
 * file_to_count_from. It takes the three types of counts as references
 * in order to change them in-place.
 *
 * @params:
 *  - file_to_count_from: an input file stream to count words,
 *       characters, and lines from
 *  - word_count: an integer representing word count of the file
 *  - line_count: an integer representing line count of the file
 *  - character_count: an integer representing character count of the file
 *
 */
void wc_counter(ifstream& file_to_count_from, int& word_count, int& line_count, int& character_count) {
    string line_to_read;
    while (getline(file_to_count_from, line_to_read)) {
        stringstream ss(line_to_read);
        string curr_word;
        line_count ++;
        character_count += line_to_read.length() + 1; // include the newline
        while (ss >> curr_word) {
            word_count ++;
        }
    }
}

/**
 * @brief helper method to append count outputs to `result` string.
 *
 * This function formats and appends the results from counting through
 * a file to the `results` string which will be the output.
 *
 * @params:
 *      - current_word_count: an integer representing word count of the current file
 *      - current_line_count: an integer representing line count of the current file
 *      - current_character_count: an integer representing character count of the current file
 *
 */
void WcCommand::append_count_to_result(const int& current_word_count, const int& current_line_count, const int& current_character_count) {
    result +=
    (command_options.empty() || command_options['l'] == true ? "\t" + to_string(current_line_count) : "") +
    (command_options.empty() || command_options['w'] == true ? "\t" + to_string(current_word_count): "") +
    (command_options.empty() || command_options['c'] == true ? "\t" + to_string(current_character_count): "");
}

/**
 * @brief Count words, characters, and/or lines of an input file.
 *
 * This function counts the words, characters, and/or lines of an input file,
 * handling any explicit options from user input and any invalid input. It
 * supports three options: `-l` for counting lines, `-w` for counting words
 * and `-c` for counting characters. If no options are defined, then it will
 * default to displaying all three counts
 *
 *
 */
void WcCommand::wc_fn() {
    if (num_tokens == 1) {
        result = "wc: Not supported yet\n";
        return;
    }
    int current_word_count, current_line_count, current_character_count;

    int total_word_count = 0, total_line_count = 0, total_character_count = 0;
    for (size_t i = 1; i < num_tokens; i++) {
        current_word_count = 0, current_line_count = 0, current_character_count = 0;

        if (command_tokens[i][0] == '-') {
            continue; // skip option tokens;
        }
        else if(fs::is_directory(command_tokens[i])) {
            result += "wc: " + command_tokens[i] + " is a directory.\n";
            continue;
        } else if (!fs::exists(command_tokens[i])) {
            result += "wc: " + command_tokens[i] + ": No such file or directory.\n";
            continue;
        }

        ifstream input_file(command_tokens[i]);
        if (input_file.is_open()) {
            wc_counter(input_file, current_word_count, current_line_count, current_character_count);
            input_file.close();
        } else {
            result += "wc: unable to open file: " + command_tokens[i] + "\n";
        }

        append_count_to_result(current_word_count, current_line_count, current_character_count);
        result += " " + command_tokens[i] + "\n";

        total_character_count += current_character_count;
        total_word_count += current_word_count;
        total_line_count += current_line_count;
    }

    if (total_word_count > current_word_count) { // signifies that there are multiple files counted from so total word count must be greater
        append_count_to_result(total_word_count, total_line_count, total_character_count);
        result += " total\n";
    }

}
