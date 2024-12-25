#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

string toUpperCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

const string YES = "YES";
const string NO = "NO";
bool test_input, user_input;

int main(int argc, char const *argv[]) {
 
	// ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
	ifstream test_out(argv[2]);   /* This stream reads from test's output file  */
	ifstream user_out(argv[3]);   /* This stream reads from user's output file  */

    string ta, ua;
    while(true) {
        test_input = static_cast<bool>(test_out >> ta);
        user_input = static_cast<bool>(user_out >> ua);
        if(!test_input || !user_input) break; // if one of them ended
        ta = toUpperCase(ta);
        ua = toUpperCase(ua);
        if(ua != YES && ua != NO) return 1; // invalid input
        if(ua != ta) return 1; // test case not equal
    }

    if(test_input || user_input)
        return 1; // answer of user or test doesn't end!

    return 0; // correct
}