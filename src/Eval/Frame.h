#ifndef LISPINTERPRETER3_FRAME_H
#define LISPINTERPRETER3_FRAME_H

#include "../Level2Parser/Level2Token.h"
#include <map>
#include <string>

using namespace std;

// TODO at this point should eval go in class with Frame?

class Frame {
private:
    map<string, Level2Token*> name_to_token_map;
    Frame* parent_frame;
public:
    Frame() {
        this->parent_frame = nullptr;
    }
    Frame(Frame* parent_frame) {
        this->parent_frame = parent_frame;
    }
    Frame* get_parent_frame() {
        return parent_frame;
    }
    void Define(string name, Level2Token* value) {
        name_to_token_map.insert({name, value});
    }
    Level2Token* FindDefinition(string name) { // TODO should we search in parent frames????
        return (name_to_token_map.find(name))->second;
    }
    bool Contains(string name) {
        return name_to_token_map.find(name) != name_to_token_map.end();
    }
};

#endif //LISPINTERPRETER3_FRAME_H
