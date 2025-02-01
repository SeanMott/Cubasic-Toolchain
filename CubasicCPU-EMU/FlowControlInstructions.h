#ifndef FLOW_CONTROL_INSTRUCTIONS_H
#define FLOW_CONTROL_INSTRUCTIONS_H

#include "PseudoAsmInterpreter.h"

inline void PseudoAsmInterpreter::handleFlowControlInstruction(const vector<string>& tokens, const string& trimmed) {
    string instr = tokens[0];
    if (instr == "INIT_LOOP") {
        string varName = tokens[1];
        if (varName.back() == ',') varName.pop_back();
        int startVal = stoi(tokens[2].substr(0, tokens[2].back() == ',' ? tokens[2].size() - 1 : tokens[2].size()));
        int endVal = stoi(tokens[3]);
        scalarVars[varName] = startVal;
        LoopInfo li;
        li.startValue = startVal;
        li.endValue = endVal;
        li.loopStartLine = pc;
        loopInfos[varName] = li;
    }
    else if (instr == "WHILE") {
        size_t posDo = trimmed.find("DO");
        if (posDo == string::npos) {
            cout << "WHILE syntax error." << endl;
            return;
        }
        string condition = trim(trimmed.substr(5, posDo - 5));
        if (evaluateCondition(condition, scalarVars)) {
            whileStack.push_back(make_pair(pc, condition));
        }
        else {
            pc = findMatchingEndwhile() + 1;
        }
    }
    else if (instr == "ENDWHILE") {
        if (!whileStack.empty()) {
            auto top = whileStack.back();
            if (evaluateCondition(top.second, scalarVars)) {
                pc = top.first;
            }
            else {
                whileStack.pop_back();
            }
        }
    }
    else if (instr == "IF") {
        size_t posThen = trimmed.find("THEN");
        if (posThen == string::npos) {
            cout << "IF syntax error." << endl;
            return;
        }
        string condition = trim(trimmed.substr(3, posThen - 3));
        if (!evaluateCondition(condition, scalarVars)) {
            int jumpLine = findMatchingEndif();
            pc = jumpLine + 1;
        }
    }
    else if (instr == "ELSE") {
        int jumpLine = findMatchingEndif();
        pc = jumpLine + 1;
    }
    else if (instr == "ENDIF") {
        // No action needed.
    }
    else if (instr == "GOTO") {
        string label = tokens[1];
        if (labels.find(label) != labels.end()) {
            pc = labels[label] + 1;
        }
        else {
            cout << "GOTO error: label not found: " << label << endl;
        }
    }
    else if (instr == "CALL") {
        string label = tokens[1];
        if (labels.find(label) != labels.end()) {
            callStack.push_back(pc);
            pc = labels[label] + 1;
        }
        else {
            cout << "CALL error: label not found: " << label << endl;
        }
    }
    else if (instr == "RETURN") {
        if (!callStack.empty()) {
            pc = callStack.back();
            callStack.pop_back();
        }
        else {
            cout << "RETURN error: call stack is empty." << endl;
        }
    }
}

#endif // FLOW_CONTROL_INSTRUCTIONS_H
