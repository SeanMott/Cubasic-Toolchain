#ifndef STRING_HANDLING_H
#define STRING_HANDLING_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleStringInstruction(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "SUBSTR") {
        if (tokens.size() >= 5) {
            size_t firstQuote = trimmed.find('"');
            size_t lastQuote = trimmed.rfind('"');
            if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
                string str = trimmed.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                int startIdx = stoi(tokens[2]);
                int len = stoi(tokens[3]);
                string substrResult = str.substr(startIdx, len);
                string dest = tokens[4];
                cout << "SUBSTR executed: Result = " << substrResult << endl;
            }
        }
    }
    else if (instr == "CONCAT") {
        string result;
        size_t pos = trimmed.find('"');
        while (pos != string::npos) {
            size_t endPos = trimmed.find('"', pos + 1);
            if (endPos == string::npos) break;
            result += trimmed.substr(pos + 1, endPos - pos - 1);
            pos = trimmed.find('"', endPos + 1);
        }
        string dest = tokens.back();
        cout << "CONCAT executed: Result = " << result << endl;
    }
    else if (instr == "LEN") {
        size_t firstQuote = trimmed.find('"');
        size_t lastQuote = trimmed.rfind('"');
        if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
            string str = trimmed.substr(firstQuote + 1, lastQuote - firstQuote - 1);
            int length = str.size();
            string dest = tokens.back();
            cout << "LEN executed: Result = " << length << endl;
        }
    }
}

#endif // STRING_HANDLING_H
