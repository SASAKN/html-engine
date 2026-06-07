#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Node Types
typedef enum NodeType {
    ElementNode,
    TextNode,
    FrameNode // <frameset>
} tokeniser_node_types_t;

// Attributes
typedef struct Attributes {
    char *key;
    char *value;
} attr_t;

// Main node structure
typedef struct TokeniserNode {

    tokeniser_node_types_t node_type;
    char *tag_name;
    char *data; // for text node

    attr_t *tag_attr;
    int attr_count;


    struct TokeniserNode *parent;
    struct TokeniserNode *first_child; // for parent elems
    struct TokeniserNode* next_sibling; // for children elems
    int children_count; // for parent elems

} tokeniser_node_t;

// Tokeniser State Machine
typedef enum tokeniser_states {
    TagStart,
    TagContents,
    TagEnd,
    Data,
    Comments
} tokeniser_states_t;

char *extract_tag_name(char *marker, char *current) {

    if (current < marker) return NULL;

    size_t len = current - marker;
    char *tag_name = malloc(len + 1);
    if (tag_name) {
        memcpy(tag_name, marker, len);
        tag_name[len] = '\0';
    }
    return tag_name;

}


tokeniser_node_t *tokeniser(char *html) {

    char *current = &html[0];
    char *marker = NULL;
    tokeniser_states_t status = Data; // state machine


    // main loop
    while (*current != '\0') {
        switch (status) {
            case Data:
                if (*current == '<') {
                    status = TagStart;
                }
                current++;
                break;
            case TagStart:
                if (*current == '/') {

                } else {
                    status = TagContents;
                    marker = current; // drop marker at the start of the tag name
                    // DO NOT INCREMENT HERE, we want to enter tag name collection.
                }
                break;
            case TagContents:
                if (*current == '>') {

                    // tag name collection
                    char *tag_name = extract_tag_name(marker, current);
                    printf("%s", tag_name);

                    status = Data;
                    current++;
                } else {
                    current++; // keep moving until we get to the end of the tag name
                }
                break;
            
            default:
                break;
        }
    }
    return NULL;
}


int main() {
    // sample html
    const char html[] = "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Sample Website</title> </head> <body> <h1>Hello</h1> <h2>This is a sample website for testing my parser</h2> </body> </html>";

    // for testing
    tokeniser("<div>");
    
    return 0;
}