#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define fori(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) fori(i, (0), (n))

/*
The function compares a with b.
If a is smaller than b, it updates a to be equal to b and returns true.
If a is not smaller than b, it returns false without making any changes.
*/
template<class A, class B>
bool maxEq(A& a, const B& b) {
	return (a < b) && ((a = b), true);
}


using VI = vector<int>;

// Function to check and ensure the line ends with an EOLN (End Of Line)
void seekReadEoln(istream &input) {
    char c;
    if (input.get(c)) { // Read one character
        if (c != '\n') {  // If the character is not a newline
            // cerr << "Expected EOLN but found character: " << c << endl;
            // cout << "bad eol1\n";
            exit(1);  // Quit with error code 1 (incorrect format)
        }
    } else {
        // cerr << "Expected EOLN but input is empty or malformed!" << endl;
        // cout << "bad eol2\n";
        exit(1);  // Quit with error code 1 (incorrect format)
    }
}

// Function to check and ensure the input ends correctly at EOF, skipping blanks
void seekReadEof(istream &input) {
    char c;
    
    // Skip any extra spaces or blank characters
    while (input.get(c)) {
        if (c != ' ' && c != '\t' && c != '\n') {
            // cerr << "Unexpected character after the expected input: " << c << endl;
            exit(1);  // Quit with error code 1 (incorrect format)
        }
    }

    // If we have finished reading the content without errors, it's good.
    if (!input.eof()) {
        // cerr << "Input stream did not terminate correctly at EOF!" << endl;
        exit(1);  // Quit with error code 1 (incorrect EOF)
    }
}

int main(int argc, char const *argv[]) {

	ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
	ifstream test_out(argv[2]);   /* This stream reads from test's output file  */
	ifstream user_out(argv[3]);   /* This stream reads from user's output file  */

    // Reading Input
    int n, m, temp;
    test_in >> n >> m;
    int locs = n + 1;
    vector<VI> dist;
    forn(i, locs) {
        VI temp_vector;
        forn(i, locs) {
            test_in >> temp;
            temp_vector.push_back(temp);
        }
        dist.push_back(temp_vector);
    }

    // Reading your Output
    int outTime;
    user_out >> outTime;
    seekReadEoln(user_out);
    VI plan;
    forn(i, m) {
        user_out >> temp;
        if(temp > n || temp < 0) return 1; // invalid input
        plan.push_back(--temp);
        if(i + 1 < m) // for every lines except last one
            seekReadEoln(user_out); // seek for end of line
    }
    seekReadEof(user_out); // seek for end of file

    // Validation of Driving Schedule
    VI transferred(n, 0); // how many times i is transferred
    int calcTime = -1;
    forn(i, m) { // i: people by car
        int j = plan[i]; // j: people carried by i - if zero no one carried
        transferred[i]++;
        if (j >= 0)
            transferred[j]++;
        maxEq(calcTime, ((j < 0) ? dist[n][i] : (dist[n][j] + dist[j][i]))); // in 0-base j==(-1) means car without extra guest
    }

    // Validation of Transfers:
	forn(i, n) {
        if(transferred[i] < 1) return 1; // person i is not transferrd
        if(transferred[i] > 1) return 1; // person i is transferred more than one
	}

    // Validation of Maximum Time
    if(calcTime != outTime) return 1; // The maximum transfer time is not correctly calculated

    // Comparison with Model Solution
    int modelTime;
    test_out >> modelTime;
    if (outTime < modelTime) return 1; // The output is a correct solution better than the model output!!!
    if (outTime > modelTime) return 1; // The output is a correct solution, but not optimal.

    return 0; // correct
}