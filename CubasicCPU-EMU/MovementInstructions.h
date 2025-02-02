#ifndef MOVEMENT_INSTRUCTIONS_H
#define MOVEMENT_INSTRUCTIONS_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleMovementInstruction(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "CUT") {
        if (tokens.size() >= 2) {
            cout << "CUT executed: Stopping movement of sprite " << tokens[1] << endl;
        }
    }
    else if (instr == "DEF_MOVE") {
        size_t eqPos = trimmed.find('=');
        if (eqPos != string::npos) {
            string spriteID = trim(tokens[1]);
            string params = trim(trimmed.substr(eqPos + 1));
            cout << "DEF_MOVE executed: Defining movement for sprite " << spriteID << " with parameters: " << params << endl;
        }
    }
    else if (instr == "ERA") {
        if (tokens.size() >= 2) {
            cout << "ERA executed: Erasing sprite " << tokens[1] << " from screen." << endl;
        }
    }
    else if (instr == "MOVE") {
        if (tokens.size() >= 2) {
            cout << "MOVE executed: Moving sprite " << tokens[1];
            if (tokens.size() > 2) {
                cout << " with parameters: ";
                for (size_t i = 2; i < tokens.size(); i++) {
                    cout << tokens[i] << " ";
                }
            }
            cout << endl;
        }
    }
    else if (instr == "POSITION") {
        if (tokens.size() >= 4) {
            cout << "POSITION executed: Setting sprite " << tokens[1] << " position to (" << tokens[2] << ", " << tokens[3] << ")" << endl;
        }
    }
    else if (instr == "DEF_SPRITE") {
        if (tokens.size() >= 3) {
            cout << "DEF_SPRITE executed: Defining sprite " << tokens[1] << " with data: ";
            for (size_t i = 2; i < tokens.size(); i++) {
                cout << tokens[i] << " ";
            }
            cout << endl;
        }
    }
    else if (instr == "SPRITE") {
        if (tokens.size() >= 4) {
            cout << "SPRITE executed: Displaying sprite " << tokens[1] << " at (" << tokens[2] << ", " << tokens[3] << ")" << endl;
        }
    }
    else if (instr == "SPRITE_OFF") {
        cout << "SPRITE_OFF executed: Disabling sprite display." << endl;
    }
    else if (instr == "SPRITE_ON") {
        cout << "SPRITE_ON executed: Enabling sprite display." << endl;
    }
}

#endif // MOVEMENT_INSTRUCTIONS_H
