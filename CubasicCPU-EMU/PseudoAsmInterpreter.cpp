#include "PseudoAsmInterpreter.h"
#include "BasicInstructions.h"
#include "FlowControlInstructions.h"
#include "StackInstructions.h"
#include "ValueFunctions.h"
#include "ScreenControl.h"
#include "MovementInstructions.h"
#include "StringHandling.h"
#include "LogAndInput.h"
#include "ArithmeticInstructions.h"  // Our arithmetic handler

void PseudoAsmInterpreter::preprocessLabels() {
    for (int i = 0; i < program.size(); i++) {
        string line = trim(program[i]);
        if (!line.empty() && line.back() == ':') {
            string labelName = line.substr(0, line.size() - 1);
            labels[labelName] = i;
            if (DEBUG_MODE)
                cout << "[DEBUG] Found label: " << labelName << " at line " << i << endl;
        }
    }
}

int PseudoAsmInterpreter::findMatchingEndif() {
    int level = 1;
    for (int i = pc; i < program.size(); i++) {
        string line = trim(program[i]);
        if (line.substr(0, 2) == "IF") level++;
        else if (line == "ENDIF") {
            level--;
            if (level == 0)
                return i;
        }
    }
    if (DEBUG_MODE)
        cout << "[DEBUG] findMatchingEndif: No matching ENDIF found, returning current PC " << pc << endl;
    return pc;
}

int PseudoAsmInterpreter::findMatchingEndwhile() {
    int level = 1;
    for (int i = pc; i < program.size(); i++) {
        string line = trim(program[i]);
        if (line.substr(0, 5) == "WHILE") level++;
        else if (line == "ENDWHILE") {
            level--;
            if (level == 0)
                return i;
        }
    }
    if (DEBUG_MODE)
        cout << "[DEBUG] findMatchingEndwhile: No matching ENDWHILE found, returning current PC " << pc << endl;
    return pc;
}

void PseudoAsmInterpreter::run() {
    if (DEBUG_MODE)
        cout << "[DEBUG] Starting program execution." << endl;
    while (running && pc < program.size()) {
        string line = program[pc];
        if (DEBUG_MODE)
            cout << "[DEBUG] Executing line " << pc << ": " << line << endl;
        pc++;
        executeLine(line);
    }
    if (DEBUG_MODE)
        cout << "[DEBUG] Program execution finished." << endl;
}

void PseudoAsmInterpreter::executeLine(const string& line) {
    // First, remove inline comments (using our helper function).
    string noComment = stripComments(line);
    string trimmed = trim(noComment);
    if (trimmed.empty()) return;
    if (trimmed.back() == ':') return; // Skip labels.
    if (trimmed[0] == ';' || (trimmed.size() > 1 && trimmed.substr(0, 2) == "//"))
        return; // Skip full-line comments.

    // Tokenize the line (our tokenizer preserves quoted strings and ignores commas outside quotes).
    vector<string> tokens = tokenize(trimmed);
    if (DEBUG_MODE) {
        cout << "[DEBUG] Tokens:";
        for (const auto& t : tokens)
            cout << " [" << t << "]";
        cout << endl;
    }
    if (tokens.empty()) return;
    string instr = tokens[0];

    // Handle the HALT instruction first.
    if (instr == "HALT") {
        running = false;
        if (DEBUG_MODE)
            cout << "[DEBUG] HALT executed: Program termination requested." << endl;
    }
    else if (instr == "PRINT" || instr == "ALLOC" || instr == "DIM" ||
        instr == "FREE" || instr == "CLEAR" || instr == "SET")
        handleBasicInstruction(tokens, trimmed);
    else if (instr == "INIT_LOOP" || instr == "WHILE" || instr == "ENDWHILE" ||
        instr == "IF" || instr == "ELSE" || instr == "ENDIF" ||
        instr == "GOTO" || instr == "CALL" || instr == "RETURN")
        handleFlowControlInstruction(tokens, trimmed);
    else if (instr == "PUSH" || instr == "POP")
        handleStackInstruction(tokens, trimmed);
    else if (instr == "ABS" || instr == "RND" || instr == "SGN" ||
        instr == "POW" || instr == "SQRT" || instr == "MOD" || instr == "TIMER")
        handleValueFunction(tokens, trimmed);
    else if (instr == "CGEN" || instr == "CGSET" || instr == "CLS" ||
        instr == "COLOR" || instr == "LOCATE" || instr == "PALET")
        handleScreenControl(tokens, trimmed);
    else if (instr == "CUT" || instr == "DEF_MOVE" || instr == "ERA" || instr == "MOVE" ||
        instr == "POSITION" || instr == "DEF_SPRITE" || instr == "SPRITE" ||
        instr == "SPRITE_OFF" || instr == "SPRITE_ON")
        handleMovementInstruction(tokens, trimmed);
    else if (instr == "SUBSTR" || instr == "CONCAT" || instr == "LEN")
        handleStringInstruction(tokens, trimmed);
    else if (instr == "LOG" || instr == "INPUT")
        handleLogAndInput(tokens, trimmed);
    else if (instr == "ADD" || instr == "LOAD" || instr == "MUL" || instr == "STORE" || instr == "CHECK_LOOP")
        handleArithmeticInstruction(tokens, trimmed);
    else {
        cout << "[ERROR] Unknown instruction: " << instr << "\n";
    }
}
