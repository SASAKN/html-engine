#include <stdio.h>



// Tokeniser State Machine
enum tokeniser_states {
    TagStart,
    TagContents,
    TagEnd,
    Data,
    Comments
} tokeniser_states_t;

int main() {
    const char *html = "";
    return 0;
}