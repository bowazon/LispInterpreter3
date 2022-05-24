#ifndef LISPINTERPRETER3_FRAME_H
#define LISPINTERPRETER3_FRAME_H

#include <map>
#include <string>
#include "LispValue.h"

using namespace std;

// TODO at this point should eval go in class with Frame?
class LispValue;

class Frame {
private:
    map<string, LispValue*> name_to_token_map;
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
    void Define(string name, LispValue* value) {
        name_to_token_map.insert({name, value});
    }
    LispValue* FindDefinition(string name) { // TODO should we search in parent frames????
        return (name_to_token_map.find(name))->second;
    }
    bool Contains(string name) {
        return name_to_token_map.find(name) != name_to_token_map.end();
    }
};

#endif //LISPINTERPRETER3_FRAME_H
