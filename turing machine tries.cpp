// Unary Addition Turing Machine Simulation
#include <iostream>
using namespace std;


string State = "q0";
int Head = 0;
int TapeLength = 0;
char Tape[1000];

struct Rule {
    string state;
    char read = '_';
    char write = '_';
    char move = '_';
    string nextState;
};

Rule rules[50];
int ruleCount = 0;

void AddRule(string s, char r, char w, char mv, string ns) {
    rules[ruleCount] = { s, r, w, mv, ns };
    ruleCount++;
}

void TransitionRules() {

    // q0: Move until you find the 0
    AddRule("q0", '1', '1', 'R', "q0");
    AddRule("q0", '0', 'S', 'R', "q1");

    // q1: Move through B part until blank
    AddRule("q1", '1', '_', 'L', "q2");
    AddRule("q1", '_', '_', 'L', "q4");

    // q2: Move left back toward S
    AddRule("q2", 'S', '1', 'R', "q3");

    // q3: Place S At New Separator
    AddRule("q3", '_', 'S', 'R', "q1");

    // q4: Clean And Halt
    AddRule("q4", 'S', '_', 'L', "HALT");

}

int ReadNumber(string msg) 
{
    int n;

    do
    {
        cout << msg;
        cin >> n;

    } while (n < 0);

    return n;
}

void FillTape() {

    int a = ReadNumber("Please Enter The First Number (A) : ");
    int b = ReadNumber("Please Enter The Second Number(B) : ");

    TapeLength = a + b + 2;

    for (int i = 0; i < TapeLength; i++) {

        if (i < a)
            Tape[i] = '1';

        else if (i == a)
            Tape[i] = '0';

        else if (i <= a + b)
            Tape[i] = '1';

        else
            Tape[i] = '_';
    }


    // Fill the rest (optional safety)
    for (int i = TapeLength; i < 300; i++)
        Tape[i] = '_';
}

bool ApplyOneStep() {

    for (int i = 0; i < ruleCount; i++) {

        if (rules[i].state == State && Tape[Head] == rules[i].read) {

            // DEBUG OUTPUT
            cout << "\nState: " << State
                << " | Head: " << Head
                << " | Read: " << Tape[Head]
                << " | Write: " << rules[i].write
                << " | Move: " << rules[i].move
                << " | Next State: " << rules[i].nextState << endl;

            // Apply the rule
            Tape[Head] = rules[i].write;
            State = rules[i].nextState;

            if (rules[i].move == 'R') Head++;
            else Head--;

            return true;
        }
    }

    return false; // No matching rule (HALT)
}

void PrintTape() {
    cout << "\nTape : ";
    for (int i = 0; i < TapeLength + 5; i++) {
        cout << Tape[i];
    }
    cout << "\n      ";
    for (int i = 0; i <= Head; i++) cout << " ";
    cout << "^";
    cout << endl;
}

int FinalResult()
{
    int result = 0;

    for (int i = 0; i < TapeLength; i++)
    {
        if (Tape[i] == '1')
            result++;
    }
    return result;
}

void SimulateTM() {

    while (State != "HALT") {
        PrintTape();
        bool ok = ApplyOneStep();
        if (!ok) break;
    }

    cout << "\nMachine HALTED.\n";
    PrintTape();
    cout << "\nFINAL RESULT = " << FinalResult() << endl;
}


int main() {

    FillTape();
    TransitionRules();
    SimulateTM();

    return 0;
}
