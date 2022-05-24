#ifndef LISPINTERPRETER2_LEVEL2TOKEN_H
#define LISPINTERPRETER2_LEVEL2TOKEN_H

#include "../Level1Parser/Level1Token.h"
#include <string>
#include <list>

using namespace std;

enum class Level2TokenType {
    kIdentifier = 0, // contains string value
    kUnparsedList // contains list<Level1Token>, we will keep this unparsed for some time
};

class Level2Token {
protected:
    Level2TokenType type;
    Level2Token() {}
public:
    Level2TokenType get_type() {return type;}
    virtual string get_identif_val() = 0;               // TODO BAD! I made
    virtual list<Level1Token> get_unparsed_list() = 0; // every subclass to have these methods
                                 // so I can call them anywhere I want WITHOUT CASTING
    // for debug
    virtual string to_string() = 0;
};

class Identifier : public Level2Token {
private:
    string val;
public:
    Identifier(string val) {
        this->type = Level2TokenType::kIdentifier;
        this->val = val;
    }
    string get_identif_val() override {
        return val;
    }
    list<Level1Token> get_unparsed_list() override {
        return list<Level1Token>();
    }
    string to_string() override {
        return val;
    }
};

class UnparsedList : public Level2Token {
private:
    list<Level1Token> unparsed_list;
public:
    UnparsedList(list<Level1Token> unparsed_list) { // TODO better by pointer????
        this->type = Level2TokenType::kUnparsedList;
        this->unparsed_list = unparsed_list; // TODO move()?
    }
    string get_identif_val() override {
        return nullptr;
    }
    list<Level1Token> get_unparsed_list() override {
        return unparsed_list;
    }
    string to_string() override {
        list<Level1Token>::iterator it;
        string output = "";
        for (it = unparsed_list.begin(); it != unparsed_list.end(); ++it) {
            output.append(it->get_content());
            output.append(" ");
        }
        return output;
    }
};

#endif //LISPINTERPRETER2_LEVEL2TOKEN_H
