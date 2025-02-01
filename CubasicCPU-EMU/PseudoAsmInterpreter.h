#ifndef PSEUDO_ASM_INTERPRETER_H
#define PSEUDO_ASM_INTERPRETER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

// Debug flag
static const bool DEBUG_MODE = false;

// Structure to hold loop information.
struct LoopInfo {
    int startValue;
    int endValue;
    int loopStartLine;
};

// Utility function: trim whitespace from both ends of a string.
inline string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == string::npos || end == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

// Utility function: strip inline comments (starting with ';') not inside quotes.
inline string stripComments(const string& line) {
    bool inQuote = false;
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            inQuote = !inQuote;
        }
        else if (c == ';' && !inQuote) {
            return trim(line.substr(0, i));
        }
    }
    return line;
}

// New tokenizer that respects quoted strings.
// New tokenizer that respects quoted strings and ignores commas outside quotes.
inline vector<string> tokenize(const string& line) {
    vector<string> tokens;
    bool inQuote = false;
    string current;
    for (char c : line) {
        if (c == '"') {
            current.push_back(c);
            inQuote = !inQuote;
            if (!inQuote) {  // End of quoted string; push token and clear
                tokens.push_back(current);
                current.clear();
            }
        }
        else if (!inQuote && c == ',') {
            // If a comma is found outside quotes, finish current token (if any) and skip the comma.
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            // Do not push the comma as a token.
        }
        else if (!inQuote && isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        }
        else {
            current.push_back(c);
        }
    }
    if (!current.empty())
        tokens.push_back(current);
    return tokens;
}

// Utility function: parse a register token (e.g., "R1") and return its numeric index.
inline int parseRegister(const string& regToken) {
    if (!regToken.empty() && regToken[0] == 'R') {
        return stoi(regToken.substr(1));
    }
    return -1;
}

// Utility function: evaluate a simple condition (e.g., "var < 10").
inline bool evaluateCondition(const string& cond, const unordered_map<string, int>& scalarVars) {
    string condition = cond;
    condition.erase(remove(condition.begin(), condition.end(), '\t'), condition.end());
    condition = trim(condition);
    vector<string> ops = { "<=", ">=", "==", "!=", "<", ">" };
    string op;
    size_t opPos = string::npos;
    for (const auto& candidate : ops) {
        opPos = condition.find(candidate);
        if (opPos != string::npos) {
            op = candidate;
            break;
        }
    }
    if (op.empty()) return false;
    string left = trim(condition.substr(0, opPos));
    string right = trim(condition.substr(opPos + op.size()));
    int leftVal = 0, rightVal = 0;
    if (scalarVars.find(left) != scalarVars.end())
        leftVal = scalarVars.at(left);
    else
        leftVal = stoi(left);
    if (scalarVars.find(right) != scalarVars.end())
        rightVal = scalarVars.at(right);
    else
        rightVal = stoi(right);
    if (op == "<")   return leftVal < rightVal;
    if (op == "<=")  return leftVal <= rightVal;
    if (op == "==")  return leftVal == rightVal;
    if (op == "!=")  return leftVal != rightVal;
    if (op == ">")   return leftVal > rightVal;
    if (op == ">=")  return leftVal >= rightVal;
    return false;
}

// Forward declarations for group handler member functions.
class PseudoAsmInterpreter {
public:
    vector<string> program;
    int pc;
    bool running;
    int registers[8];
    unordered_map<string, int> scalarVars;
    unordered_map<string, vector<int>> arrayVars;
    unordered_map<string, LoopInfo> loopInfos;
    unordered_map<string, int> labels;
    vector<int> callStack;
    vector<int> dataStack;
    vector<pair<int, string>> whileStack;
    int screenWidth = 80;
    int screenHeight = 25;
    vector<vector<string>> screen;

    PseudoAsmInterpreter(const vector<string>& prog)
        : program(prog), pc(0), running(true) {
        for (int i = 0; i < 8; i++) {
            registers[i] = 0;
        }
        screen.resize(screenHeight, vector<string>(screenWidth, "BLACK"));
        preprocessLabels();
    }

    // Group handler function declarations.
    void handleBasicInstruction(const vector<string>& tokens, const string& trimmed);
    void handleFlowControlInstruction(const vector<string>& tokens, const string& trimmed);
    void handleStackInstruction(const vector<string>& tokens, const string& trimmed);
    void handleValueFunction(const vector<string>& tokens, const string& trimmed);
    void handleScreenControl(const vector<string>& tokens, const string& trimmed);
    void handleMovementInstruction(const vector<string>& tokens, const string& trimmed);
    void handleStringInstruction(const vector<string>& tokens, const string& trimmed);
    void handleLogAndInput(const vector<string>& tokens, const string& trimmed);
    void handleArithmeticInstruction(const vector<string>& tokens, const string& trimmed);

    void preprocessLabels();
    int findMatchingEndif();
    int findMatchingEndwhile();
    void run();
    void executeLine(const string& line);
};

#endif // PSEUDO_ASM_INTERPRETER_H
