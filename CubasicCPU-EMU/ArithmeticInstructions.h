#ifndef ARITHMETIC_INSTRUCTIONS_H
#define ARITHMETIC_INSTRUCTIONS_H

#include "PseudoAsmInterpreter.h"
#include <functional> // for std::plus and std::multiplies

inline void PseudoAsmInterpreter::handleArithmeticInstruction(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (DEBUG_MODE)
        cout << "[DEBUG] Executing Arithmetic Instruction: " << trimmed << " at PC=" << pc - 1 << endl;

    if (instr == "ADD") {
        // Syntax: ADD Rdest, Rsrc
        string destToken = tokens[1];
        if (!destToken.empty() && destToken.back() == ',')
            destToken.pop_back();
        string srcToken = tokens[2];
        int destReg = parseRegister(destToken);
        int srcReg = parseRegister(srcToken);
        if (destReg >= 0 && destReg < 8 && srcReg >= 0 && srcReg < 8) {
            // Use the system-provided plus functor.
            registers[destReg] = std::plus<int>()(registers[destReg], registers[srcReg]);
            if (DEBUG_MODE)
                cout << "[DEBUG] ADD: R" << destReg << " becomes " << registers[destReg] << endl;
        }
        else {
            cout << "[ERROR] ADD: Invalid register(s) provided." << endl;
        }
    }
    else if (instr == "LOAD") {
        // Syntax: LOAD var, Rn
        string varName = tokens[1];
        if (!varName.empty() && varName.back() == ',')
            varName.pop_back();
        string regToken = tokens[2];
        int regNum = parseRegister(regToken);
        if (scalarVars.find(varName) != scalarVars.end() && regNum >= 0 && regNum < 8) {
            registers[regNum] = scalarVars[varName];
            if (DEBUG_MODE)
                cout << "[DEBUG] LOAD: Variable '" << varName << "' value " << scalarVars[varName]
                << " loaded into R" << regNum << endl;
        }
        else {
            cout << "[ERROR] LOAD: Variable '" << varName << "' not found or invalid register." << endl;
        }
    }
    else if (instr == "MUL") {
        // Syntax: MUL Rdest, Rsrc OR MUL Rdest, immediate OR MUL Rdest, variable
        string destToken = tokens[1];
        if (!destToken.empty() && destToken.back() == ',')
            destToken.pop_back();
        int destReg = parseRegister(destToken);

        // Check if the second token is a register.
        if (!tokens[2].empty() && tokens[2][0] == 'R') {
            int srcReg = parseRegister(tokens[2]);
            if (destReg >= 0 && destReg < 8 && srcReg >= 0 && srcReg < 8) {
                // Use the system-provided multiplies functor.
                registers[destReg] = std::multiplies<int>()(registers[destReg], registers[srcReg]);
                if (DEBUG_MODE)
                    cout << "[DEBUG] MUL: R" << destReg << " becomes " << registers[destReg]
                    << " (multiplied by R" << srcReg << ")" << endl;
            }
            else {
                cout << "[ERROR] MUL: Invalid register(s) provided." << endl;
            }
        }
        else {
            // Try to convert the token to an integer.
            try {
                int immediate = stoi(tokens[2]);
                if (destReg >= 0 && destReg < 8) {
                    registers[destReg] = std::multiplies<int>()(registers[destReg], immediate);
                    if (DEBUG_MODE)
                        cout << "[DEBUG] MUL: R" << destReg << " becomes " << registers[destReg]
                        << " (multiplied by " << immediate << ")" << endl;
                }
            }
            catch (invalid_argument&) {
                // If conversion fails, assume it is a scalar variable.
                if (scalarVars.find(tokens[2]) != scalarVars.end()) {
                    int value = scalarVars[tokens[2]];
                    if (destReg >= 0 && destReg < 8) {
                        registers[destReg] = std::multiplies<int>()(registers[destReg], value);
                        if (DEBUG_MODE)
                            cout << "[DEBUG] MUL: R" << destReg << " becomes " << registers[destReg]
                            << " (multiplied by variable " << tokens[2] << " with value " << value << ")" << endl;
                    }
                }
                else {
                    cout << "[ERROR] MUL: Could not parse operand '" << tokens[2] << "' as an immediate or variable." << endl;
                }
            }
        }
    }
    else if (instr == "STORE") {
        // Syntax: STORE Rn, arr[i]
        string regToken = tokens[1];
        if (!regToken.empty() && regToken.back() == ',')
            regToken.pop_back();
        int regNum = parseRegister(regToken);
        string arrayToken = tokens[2];
        size_t bracketOpen = arrayToken.find('[');
        size_t bracketClose = arrayToken.find(']');
        if (bracketOpen != string::npos && bracketClose != string::npos) {
            string arrayName = arrayToken.substr(0, bracketOpen);
            string indexVar = arrayToken.substr(bracketOpen + 1, bracketClose - bracketOpen - 1);
            int index = 0;
            if (scalarVars.find(indexVar) != scalarVars.end())
                index = scalarVars[indexVar];
            else
                index = stoi(indexVar);
            if (arrayVars.find(arrayName) != arrayVars.end()) {
                if (index >= 0 && index < arrayVars[arrayName].size()) {
                    arrayVars[arrayName][index] = registers[regNum];
                    if (DEBUG_MODE)
                        cout << "[DEBUG] STORE: Stored R" << regNum << " (" << registers[regNum]
                        << ") into " << arrayName << "[" << index << "]" << endl;
                }
                else {
                    cout << "[ERROR] STORE: Index " << index << " out of bounds for array '" << arrayName << "'." << endl;
                }
            }
            else {
                cout << "[ERROR] STORE: Array '" << arrayName << "' not found." << endl;
            }
        }
    }
    else if (instr == "CHECK_LOOP") {
        // Syntax: CHECK_LOOP var
        string varName = tokens[1];
        if (loopInfos.find(varName) != loopInfos.end()) {
            scalarVars[varName]++;  // Increment loop variable.
            LoopInfo li = loopInfos[varName];
            if (DEBUG_MODE)
                cout << "[DEBUG] CHECK_LOOP: Variable '" << varName << "' incremented to " << scalarVars[varName] << endl;
            if (scalarVars[varName] <= li.endValue) {
                if (DEBUG_MODE)
                    cout << "[DEBUG] CHECK_LOOP: Loop condition true, jumping back to line " << li.loopStartLine << endl;
                pc = li.loopStartLine;
            }
            else {
                loopInfos.erase(varName);
                if (DEBUG_MODE)
                    cout << "[DEBUG] CHECK_LOOP: Loop condition false, exiting loop for '" << varName << "'" << endl;
            }
        }
        else {
            cout << "[ERROR] CHECK_LOOP: No loop info for variable '" << varName << "'." << endl;
        }
    }
}

#endif // ARITHMETIC_INSTRUCTIONS_H
