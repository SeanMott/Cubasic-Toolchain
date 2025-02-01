#ifndef LOG_AND_INPUT_H
#define LOG_AND_INPUT_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleLogAndInput(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "LOG") {
        size_t firstQuote = trimmed.find('"');
        size_t lastQuote = trimmed.rfind('"');
        if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
            // Extract the message within the quotes.
            string message = trimmed.substr(firstQuote + 1, lastQuote - firstQuote - 1);
            cout << "[LOG] " << message;
            // Process the remaining tokens (ignoring commas).
            for (size_t i = 1; i < tokens.size(); i++) {
                // Skip tokens that are exactly a comma.
                if (tokens[i] == ",")
                    continue;
                // Also skip tokens that are fully quoted.
                if (tokens[i].front() == '"' && tokens[i].back() == '"')
                    continue;
                // If token starts with 'R', assume it's a register.
                if (!tokens[i].empty() && tokens[i][0] == 'R') {
                    int reg = parseRegister(tokens[i]);
                    if (reg >= 0 && reg < 8) {
                        cout << " " << registers[reg];
                    }
                    else {
                        cout << " " << tokens[i];
                    }
                }
                // Otherwise, if it exists in scalarVars, print its value.
                else if (scalarVars.find(tokens[i]) != scalarVars.end()) {
                    cout << " " << scalarVars[tokens[i]];
                }
                // Otherwise, just print the token.
                else {
                    cout << " " << tokens[i];
                }
            }
            cout << endl;
        }
        else {
            cout << "[LOG] (No quoted message found)" << endl;
        }
    }
    else if (instr == "INPUT") {
        size_t firstQuote = trimmed.find('"');
        size_t lastQuote = trimmed.rfind('"');
        if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
            string prompt = trimmed.substr(firstQuote + 1, lastQuote - firstQuote - 1);
            cout << "[INPUT] " << prompt;
            int userInput;
            cin >> userInput;
            size_t commaPos = trimmed.find(',', lastQuote);
            if (commaPos != string::npos) {
                string varName = trim(trimmed.substr(commaPos + 1));
                scalarVars[varName] = userInput;
                if (DEBUG_MODE)
                    cout << "[DEBUG] INPUT: Variable '" << varName << "' set to " << userInput << endl;
            }
        }
    }
}

#endif // LOG_AND_INPUT_H
