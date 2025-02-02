#ifndef SCREEN_CONTROL_H
#define SCREEN_CONTROL_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleScreenControl(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "CGEN") {
        if (tokens.size() >= 2) {
            cout << "CGEN executed: Setting background sprite to " << tokens[1] << endl;
        }
    }
    else if (instr == "CGSET") {
        if (tokens.size() >= 3) {
            cout << "CGSET executed: Setting sprite " << tokens[1] << " background to " << tokens[2] << endl;
        }
    }
    else if (instr == "CLS") {
        for (int r = 0; r < screenHeight; r++) {
            fill(screen[r].begin(), screen[r].end(), "BLACK");
        }
        for (int i = 0; i < 50; i++) cout << endl;
        cout << "[CLS executed: Screen cleared]" << endl;
    }
    else if (instr == "COLOR") {
        if (tokens.size() >= 4) {
            int col = stoi(tokens[1]);
            int row = stoi(tokens[2]);
            string colorCode = tokens[3];
            if (row >= 0 && row < screenHeight && col >= 0 && col < screenWidth) {
                screen[row][col] = colorCode;
                cout << "COLOR executed: Set cell (" << col << ", " << row << ") to " << colorCode << endl;
            }
            else {
                cout << "COLOR error: Coordinates (" << col << ", " << row << ") are out of bounds." << endl;
            }
        }
    }
    else if (instr == "LOCATE") {
        if (tokens.size() >= 3) {
            cout << "LOCATE executed: Moving cursor to (" << tokens[1] << ", " << tokens[2] << ")" << endl;
        }
    }
    else if (instr == "PALET") {
        if (tokens.size() >= 6) {
            cout << "PALET executed: Setting palette " << tokens[1] << " with colors: ";
            for (size_t i = 2; i < tokens.size(); i++) {
                cout << tokens[i] << " ";
            }
            cout << endl;
        }
    }
}

#endif // SCREEN_CONTROL_H
