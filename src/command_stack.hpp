#include <string>
using namespace std;

// partial Stack ADT LinkedList implementation
class CommandStack {
    struct Node
    {   
        string data;
        Node* next;
    };

    Node* recent;
public:
    CommandStack();
    ~CommandStack();
    string pop();
    void push(string current_command);
    bool isEmpty();
};