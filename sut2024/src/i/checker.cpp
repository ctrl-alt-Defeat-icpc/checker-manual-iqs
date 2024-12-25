// Checker for problem: ride
// Author: Kian Mirjalali
#include "testlib.h"
using namespace std;

#define fori(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) fori(i, (0), (n))

template<class A, class B>
bool maxEq(A& a, const B& b) {
	return (a < b) && ((a = b), true);
}

using VI = vector<int>;

void seekReadEoln() {
    if (!ouf.seekEoln())
        quit(_wa, "Expected EOLN");
}

void seekReadEof() {
	ouf.skipBlanks();
	ouf.readEof();
}

int main(int argc, char* argv[]) {
	registerChecker("ride", argc, argv);

	int n = inf.readInt();
	int m = inf.readInt();
	int locs = n+1;
	vector<VI> dist;
	forn(i, locs)
		dist.push_back(inf.readInts(locs));

	int outTime = ouf.readInt();
	seekReadEoln();
	VI plan;
	forn(i, m) {
		plan.push_back(ouf.readInt(0, n)-1);
		seekReadEoln();
	}
	seekReadEof();

	VI transferred(n, 0);
	int calcTime = -1;
	forn(i, m) {
		int j = plan[i];
		transferred[i]++;
		if (j >= 0)
			transferred[j]++;
		maxEq(calcTime, ((j < 0) ? dist[n][i] : (dist[n][j]+dist[j][i])));
	}
	forn(i, n) {
		quitif(transferred[i] < 1, _wa, "Person %d is not transferred.", i+1);
		quitif(transferred[i] > 1, _wa, "Person %d is transferred more than once.", i+1);
	}
	quitif(calcTime != outTime, _wa, "The maximum transfer time (%d) is not correctly calculated. It is %d.", outTime, calcTime);

	int modelTime = ans.readInt();

	if (outTime < modelTime)
		quitf(_fail, "The output is a correct solution better than the model output!!!");
	if (outTime > modelTime)
		quitf(_wa, "The output is a correct solution, but not optimal.");
	quit(_ok);
}
