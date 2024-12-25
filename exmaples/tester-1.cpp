#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int N = 1024;
int color[N][N];

bool checkBandwidth(int x, int n) {
    if(x < 0 || x == n)
        return false;
    return true;
}

int isValid(int x, int y, int n) {
	int row, col, counter = 0;
	int direction[4][2] = {
		{x, y - 1},
		{x - 1, y},
		{x + 1, y},
		{x, y + 1}
	};
	for(int i = 0; i < 4; i++) {
		row = direction[i][0], col = direction[i][1];
		if(!checkBandwidth(row, n) || !(checkBandwidth(col, n))) continue;
		if(color[row][col] == color[x][y]) counter++;
	}
	if(counter == 2) return 1;
	if(counter < 2) return 0;
	return 2;
}

int main(int argc, char const *argv[]) {

	ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
	ifstream test_out(argv[2]);   /* This stream reads from test's output file  */
	ifstream user_out(argv[3]);   /* This stream reads from user's output file  */

	int n, a, b, result;
	int num[3] = {0};
	int conunttile[3] = {0};
	test_in >> n >> a >> b;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			user_out >> color[i][j];

	if(color[a][b]) return 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			if (i == a && j == b) continue;
			else {
				if(color[i][j] > 3 || color[i][j] < 1) return 1;
				num[color[i][j] - 1]++;
				result = isValid(i, j, n);
				if(result == 1) conunttile[color[i][j] - 1]++;
				else if(result == 2) return 1;
			}
		}


	for(int i = 0; i < 3; i++) {
		if(num[i] / 3 != conunttile[i]) {
			return 1;
		}
	}

	return 0;
}