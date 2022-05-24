#include "Level2Parser.h"
#include <iostream>

enum ParseState {
    Beginning,
    PastFirstOpeningBrace,
    CollectingBracedContent,
    End
};

namespace Level2Parser {

list<Level2Token*> Parse(list<Level1Token> tokens) {
    list<Level2Token*> result;
    list<Level1Token> braced_tokens_buffer;
    ParseState next_st = Beginning;
    int brace_counter = 0;

    list<Level1Token>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); ++it) {
        Level1Token crnt_token = *it;

        switch(next_st) {
            case Beginning: {
                if (crnt_token.get_type() == Level1TokenType::kOpeningBrace) {
                    next_st = PastFirstOpeningBrace;
                    break;
                }
                if (crnt_token.get_type() == Level1TokenType::kIdentifier) {
                    // Let's now pretend that if we met Identifier right from start,
                    // then this is the only object we legally could meet.
                    // For example "foo" is legal Lisp expression (Lisp interpreter
                    // will tell us the meaning of "foo" - maybe it is user defined procedure
                    // for example), but "foo a b" without braces is illegal,
                    // legal would be "(foo a b)".
                    // TODO checked this in Racket and this is not true, "2 3 7"
                    // will give us "2", "3" and "7", however unbraced "define a 1"
                    // will give error. Need to think about this case
                    result.push_back(new Identifier(crnt_token.get_content()));
                    next_st = End;
                    break;
                }
                break;
            }
            case PastFirstOpeningBrace: {
                if (crnt_token.get_type() == Level1TokenType::kIdentifier) {
                    result.push_back(new Identifier(crnt_token.get_content()));
                    // TODO check if identifier a reserved word? here or in eval()
                    break;
                }
                if (crnt_token.get_type() == Level1TokenType::kOpeningBrace) {
                    braced_tokens_buffer.push_back(crnt_token);
                    brace_counter = 1;
                    next_st = CollectingBracedContent;
                    break;
                }
                break;
            }
            case CollectingBracedContent: {
                if (crnt_token.get_type() == Level1TokenType::kOpeningBrace) brace_counter++;
                if (crnt_token.get_type() == Level1TokenType::kClosingBrace) brace_counter--;
                braced_tokens_buffer.push_back(crnt_token);
                if (brace_counter == 0) {
                    result.push_back(new UnparsedList(braced_tokens_buffer));
                    next_st = PastFirstOpeningBrace;
                    braced_tokens_buffer.clear();
                }
                break;
            }
            case End: {
                break; // TODO dummy end, doesn't exit from cycle
            }
        }
    }

    return result;
}

void Print(list<Level2Token*> lisp_values) {
    list<Level2Token*>::iterator it;
    int i = 0;
    cout << "..." << endl;
    for (it = lisp_values.begin(); it != lisp_values.end(); ++it, i++) {
        cout << "Level 2 token " << i << ": \"" << (*it)->to_string() << "\"" << endl;
    }
}

} // namespace Level2Parser

