#include "PseudoAsmInterpreter.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <program_file>" << endl;
        return 1;
    }
    string filename = argv[1];
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }
    vector<string> program;
    string line;
    while (getline(infile, line)) {
        program.push_back(line);
    }
    infile.close();
    if (DEBUG_MODE)
        cout << "[DEBUG] Loaded program with " << program.size() << " lines." << endl;
    PseudoAsmInterpreter interpreter(program);
    interpreter.run();
    if (interpreter.arrayVars.find("arr") != interpreter.arrayVars.end()) {
        cout << "Array 'arr' contents:" << endl;
        for (int val : interpreter.arrayVars["arr"]) {
            cout << val << " ";
        }
        cout << "\n";
    }
    return 0;
}
