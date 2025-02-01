#ifndef VALUE_FUNCTIONS_H
#define VALUE_FUNCTIONS_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleValueFunction(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "ABS") {
        if (tokens.size() >= 3) {
            string operand = tokens[1];
            string dest = tokens[2];
            int value = 0;
            if (!operand.empty() && operand[0] == 'R') {
                int regIndex = parseRegister(operand);
                value = abs(registers[regIndex]);
            }
            else {
                value = abs(stoi(operand));
            }
            if (!dest.empty() && dest[0] == 'R') {
                int regDest = parseRegister(dest);
                registers[regDest] = value;
            }
            else {
                scalarVars[dest] = value;
            }
            cout << "ABS executed: Result = " << value << endl;
        }
    }
    else if (instr == "RND") {
        if (tokens.size() >= 3) {
            string operand = tokens[1];
            string dest = tokens[2];
            int modValue = (!operand.empty() && operand[0] == 'R') ? registers[parseRegister(operand)] : stoi(operand);
            int rndVal = (modValue != 0) ? rand() % modValue : rand();
            if (!dest.empty() && dest[0] == 'R') {
                int regDest = parseRegister(dest);
                registers[regDest] = rndVal;
            }
            else {
                scalarVars[dest] = rndVal;
            }
            cout << "RND executed: Result = " << rndVal << endl;
        }
    }
    else if (instr == "SGN") {
        if (tokens.size() >= 3) {
            string operand = tokens[1];
            string dest = tokens[2];
            int value = (!operand.empty() && operand[0] == 'R') ? registers[parseRegister(operand)] : stoi(operand);
            int sgn = (value > 0) ? 1 : ((value < 0) ? -1 : 0);
            if (!dest.empty() && dest[0] == 'R') {
                int regDest = parseRegister(dest);
                registers[regDest] = sgn;
            }
            else {
                scalarVars[dest] = sgn;
            }
            cout << "SGN executed: Result = " << sgn << endl;
        }
    }
    else if (instr == "POW") {
        if (tokens.size() >= 4) {
            double base = stod(tokens[1]);
            double exponent = stod(tokens[2]);
            double resultVal = pow(base, exponent);
            string dest = tokens[3];
            cout << "POW executed: Result = " << resultVal << endl;
        }
    }
    else if (instr == "SQRT") {
        if (tokens.size() >= 3) {
            double value = stod(tokens[1]);
            double resultVal = sqrt(value);
            string dest = tokens[2];
            cout << "SQRT executed: Result = " << resultVal << endl;
        }
    }
    else if (instr == "MOD") {
        if (tokens.size() >= 4) {
            int a = stoi(tokens[1]);
            int b = stoi(tokens[2]);
            int resultVal = (b != 0) ? a % b : 0;
            string dest = tokens[3];
            cout << "MOD executed: Result = " << resultVal << endl;
        }
    }
    else if (instr == "TIMER") {
        if (tokens.size() >= 2) {
            int delayMs = stoi(tokens[1]);
            cout << "TIMER executed: Delaying for " << delayMs << " milliseconds." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
    }
}

#endif // VALUE_FUNCTIONS_H
