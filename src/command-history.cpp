#include "../include/command-history.hpp"

/**
 * @brief  Inserts most recent command to command history.
 *
 * This function takes in a Command object parameter and inserts it to the top of
 * the command history. This new command will become the head of the linked list
 * structure.
 *
 * @param command_to_insert: command object that will be inserted
 *
 * @return vector of tokens for command parsing
 */
void CommandHistory::insert_command(const Command &command_to_insert) {

    // inserts at beginning of linked list (constant-time operation)
    CommandNode* newcommand = new CommandNode(command_to_insert);
    if (head != nullptr) {
        newcommand->next = head;
        head->prev = newcommand;
    }
    head = newcommand;
    iterator = head;
    initialHistoryTraversal = true;
}

/**
 * @brief  Detokenization of tokens for Command objects
 *
 * This function converts the tokens member of the Command objects
 * back to normal strings. This is done so that the readline
 * input buffer is re-populated with a string.
 *
 * @param tokens: tokens to detokenize
 *
 * @return detokenized string
 */
string get_raw_command(const vector<string>& tokens) {
    string raw_command = "";
    for (string token : tokens) {
        raw_command += " " + token;
    }
    return raw_command;
}

/**
 * @brief  Trims left whitespaces of string input.
 *
 * This function trims the preceding white space
 * of the string parameter. Has to be used before
 * readline buffer is repopulated, otherwise there
 * will always be whitespace on the left.
 *
 *
 * @param str: string to trim the left whitespace of
 *
 * @return string with preceding whitespace trimmed
 */
const char* trim_left_whitespace(const char* str) {
    if (str == nullptr) {
        return str;
    }

    while(*str && *str == ' ') {
        ++str;
    }

    return str;
}

/**
 * @brief  Go up the command history.
 *
 * This function traverses the command history linkedlist
 * upwards by incrementing to next pointers everytime the
 * arrow key is pressed. The current node in the traversal
 * is pointed to by the `iterator` member variable. After
 * incrementing, the readline input buffer is repopulated
 * with the current command user has navigated to.
 *
 */
void CommandHistory::go_up_history() {
    if (initialHistoryTraversal) {
        rl_replace_line(trim_left_whitespace(get_raw_command(head->command.command_tokens).c_str()), 0); // overwrite readline input buffer
        initialHistoryTraversal = false;
        rl_point = rl_end; // move cursor to end
        return;
    }
    if (head == nullptr) return;

    if (iterator == nullptr) iterator = head;
    else if (iterator->next != nullptr) iterator = iterator->next;

    rl_replace_line(trim_left_whitespace(get_raw_command(iterator->command.command_tokens).c_str()), 0);
    rl_point = rl_end;
    return;
}

/**
 * @brief  Go down the command history.
 *
 * This function traverses the command history linkedlist
 * downwards by decrementing to previous pointers everytime the
 * arrow key is pressed. The current node in the traversal
 * is pointed to by the `iterator` member variable. The decrementation
 * is only done if the `iterator` has been incremented. If user "leaves"
 * the command history by navigating all the way down, the readline
 * input buffer is cleared and the `iterator` is set to the head again.
 * Otherwise, after decrementing, the readline input buffer is repopulated
 * with the current command user has navigated to.
 *
 */
void CommandHistory::go_down_history() {

    if (head == nullptr) return;

    if (iterator == nullptr) {
        rl_replace_line("", 0);
        initialHistoryTraversal = true; // reset traversal if user exits command history
        iterator = head;
        rl_point = rl_end;
        return;
    } else if (iterator->prev != nullptr) iterator = iterator->prev;
    else {
        rl_replace_line("", 0);
        iterator = nullptr;
        rl_point = rl_end;
        return;
    }

    rl_replace_line(trim_left_whitespace(get_raw_command(iterator->command.command_tokens).c_str()), 0);
    rl_point = rl_end;
    return;
}

// destructor to destroy command nodes that were allocated on heap
CommandHistory::~CommandHistory() {
    CommandNode* current = head;
    while (current != nullptr) {
        CommandNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}
