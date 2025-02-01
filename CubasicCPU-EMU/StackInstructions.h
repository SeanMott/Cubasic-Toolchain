#ifndef STACK_INSTRUCTIONS_H
#define STACK_INSTRUCTIONS_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleStackInstruction(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "PUSH") {
        string operand = tokens[1];
        if (!operand.empty() && operand[0] == 'R') {
            int regNum = parseRegister(operand);
            if (regNum >= 0 && regNum < 8) {
                dataStack.push_back(registers[regNum]);
            }
        }
        else {
            int value = stoi(operand);
            dataStack.push_back(value);
        }
    }
    else if (instr == "POP") {
        if (dataStack.empty()) {
            cout << "POP error: data stack is empty." << endl;
            return;
        }
        string regToken = tokens[1];
        int regNum = parseRegister(regToken);
        if (regNum >= 0 && regNum < 8) {
            registers[regNum] = dataStack.back();
            dataStack.pop_back();
        }
    }
}

#endif // STACK_INSTRUCTIONS_H
