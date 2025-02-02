#ifndef BASIC_INSTRUCTIONS_H
#define BASIC_INSTRUCTIONS_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleBasicInstruction(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "PRINT") {
        size_t firstQuote = trimmed.find('"');
        size_t lastQuote = trimmed.rfind('"');
        if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
            string content = trimmed.substr(firstQuote + 1, lastQuote - firstQuote - 1);
            cout << content << endl;
        }
    }
    else if (instr == "ALLOC") {
        string varName = tokens[1];
        if (varName.back() == ',') varName.pop_back();
        int size = stoi(tokens[2]);
        arrayVars[varName] = vector<int>(size, 0);
    }
    else if (instr == "DIM") {
        size_t start = trimmed.find('(');
        size_t end = trimmed.find(')');
        if (start != string::npos && end != string::npos && end > start) {
            string varName = trim(trimmed.substr(4, start - 4));
            int size = stoi(trim(trimmed.substr(start + 1, end - start - 1)));
            arrayVars[varName] = vector<int>(size, 0);
        }
    }
    else if (instr == "FREE") {
        string varName = tokens[1];
        if (arrayVars.find(varName) != arrayVars.end()) {
            arrayVars.erase(varName);
        }
    }
    else if (instr == "CLEAR") {
        string varName = tokens[1];
        if (scalarVars.find(varName) != scalarVars.end()) {
            scalarVars[varName] = 0;
        }
        else if (arrayVars.find(varName) != arrayVars.end()) {
            fill(arrayVars[varName].begin(), arrayVars[varName].end(), 0);
        }
    }
    else if (instr == "SET") {
        // Two cases: simple assignment or a binary expression.
        if (tokens.size() == 4) {
            // Simple assignment: SET dest = value
            string operand = tokens[1];
            if (tokens[2] != "=") {
                cout << "[ERROR] SET syntax error. Expected '=' after operand." << endl;
                return;
            }
            try {
                int value = stoi(tokens[3]);
                if (!operand.empty() && operand[0] == 'R') {
                    int regNum = parseRegister(operand);
                    if (regNum >= 0 && regNum < 8) {
                        registers[regNum] = value;
                        if (DEBUG_MODE)
                            cout << "[DEBUG] SET: R" << regNum << " set to " << value << endl;
                    }
                }
                else {
                    scalarVars[operand] = value;
                    if (DEBUG_MODE)
                        cout << "[DEBUG] SET: Variable '" << operand << "' set to " << value << endl;
                }
            }
            catch (...) {
                cout << "[ERROR] SET: Could not parse value." << endl;
            }
        }
        else if (tokens.size() == 6) {
            // Expression: SET dest = left op right
            string dest = tokens[1];
            if (tokens[2] != "=") {
                cout << "[ERROR] SET syntax error. Expected '=' after destination." << endl;
                return;
            }
            string left = tokens[3];
            string op = tokens[4];
            string right = tokens[5];
            int leftVal = 0, rightVal = 0;
            try {
                if (scalarVars.find(left) != scalarVars.end())
                    leftVal = scalarVars[left];
                else
                    leftVal = stoi(left);
            }
            catch (...) {
                cout << "[ERROR] SET: Could not parse left operand '" << left << "'." << endl;
                return;
            }
            try {
                if (scalarVars.find(right) != scalarVars.end())
                    rightVal = scalarVars[right];
                else
                    rightVal = stoi(right);
            }
            catch (...) {
                cout << "[ERROR] SET: Could not parse right operand '" << right << "'." << endl;
                return;
            }
            int result = 0;
            if (op == "+")
                result = leftVal + rightVal;
            else if (op == "-")
                result = leftVal - rightVal;
            else if (op == "*")
                result = leftVal * rightVal;
            else if (op == "/") {
                if (rightVal == 0) {
                    cout << "[ERROR] SET: Division by zero." << endl;
                    return;
                }
                result = leftVal / rightVal;
            }
            else {
                cout << "[ERROR] SET: Unknown operator '" << op << "'." << endl;
                return;
            }
            // Assign result to destination.
            if (!dest.empty() && dest[0] == 'R') {
                int regNum = parseRegister(dest);
                if (regNum >= 0 && regNum < 8) {
                    registers[regNum] = result;
                    if (DEBUG_MODE)
                        cout << "[DEBUG] SET: R" << regNum << " set to " << result
                        << " (expression: " << left << " " << op << " " << right << ")" << endl;
                }
            }
            else {
                scalarVars[dest] = result;
                if (DEBUG_MODE)
                    cout << "[DEBUG] SET: Variable '" << dest << "' set to " << result
                    << " (expression: " << left << " " << op << " " << right << ")" << endl;
            }
        }
        else {
            cout << "[ERROR] SET syntax error. Unrecognized token count: " << tokens.size() << endl;
        }
    }
}

#endif // BASIC_INSTRUCTIONS_H
