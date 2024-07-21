#include <fstream>
#include <string>
#include <sstream>
#include "../../include/command.hpp"


WcCommand::WcCommand(const vector<string>& new_tokens) : Command (new_tokens) {
    command_options['l'] = true, command_options['w'] = true; command_options['c'] = true;
    options_handler();
    if (!invalid_option_found) wc_fn();
};

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

void WcCommand::append_count_to_result(int current_word_count, int current_line_count, int current_character_count) {
    result +=
    (command_options.empty() || command_options['l'] == true ? "\t" + to_string(current_line_count) : "") +
    (command_options.empty() || command_options['w'] == true ? "\t" + to_string(current_word_count): "") +
    (command_options.empty() || command_options['c'] == true ? "\t" + to_string(current_character_count): "");
}

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

    if (total_word_count != current_word_count) { // signifies that there are multiple files counted from so total word count must be greater
        append_count_to_result(total_word_count, total_line_count, total_character_count);
        result += " total\n";
    }

}
