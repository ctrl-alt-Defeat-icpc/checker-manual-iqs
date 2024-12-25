// Checker for problem: connection
// Author: Alireza Samimi
#include "testlib.h"
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> pll;

ll ansval = 0;

vector<pair<ll, pll>> a;
vector<pll> b;
vector<bool> matched;
priority_queue<pll, vector<pll>, greater<pll>> pq;

int main(int argc, char* argv[]) {
	registerChecker("connection", argc, argv);

	int w = inf.readInt();
	int h = inf.readInt();
	int n = inf.readInt();
	a.resize(n);
	b.resize(n);
	matched.resize(n, false);
	for (int i = 0; i < n; i++) {
	    a[i].first = inf.readInt();
		a[i].second = {0, 0};
	}
	for (int i = 0; i < n; i++) {
        b[i].second = inf.readInt();
        b[i].first = inf.readInt();
    }
    for (int i = 0; i < n; i++) {
        int p = ouf.readInt();
        if (p < 1 || p > n) {
            quitf(_wa, "Invalid index %d.", p);
        }
        if (matched[p - 1]) {
            quitf(_wa, "Index %d is used more than once.", p);
        }
        matched[p - 1] = true;
        a[i].second = b[p - 1];
        ansval -= abs(a[i].first - b[p - 1].first) + b[p - 1].second;
    }
    sort(a.begin(), a.end());
    auto b_sorted = b;
    sort(b_sorted.begin(), b_sorted.end());
    for (int i = 0; i < n; i++) {
        ansval += abs(a[i].first - b_sorted[i].first) + b_sorted[i].second;
    }
    if (ansval < 0) {
        quitf(_wa, "Wrong length of the connections, difference %d.", ansval);
    }
    if (ansval > 0) {
        quitf(_fail, "Something is wrong with the checker.");
    }
    for (auto [l, p] : a) {
        auto [r, t] = p;
        while(!pq.empty() && pq.top().second < l) {
            pq.pop();
        }
        if (!pq.empty() && pq.top().first <= t) {
            quitf(_wa, "Connections are intersecting.");
        }
        pq.push({t, r});
    }
    pq = {};
    reverse(a.begin(), a.end());
    for (auto [l, p] : a) {
        auto [r, t] = p;
        while(!pq.empty() && pq.top().second > l) {
            pq.pop();
        }
        if (!pq.empty() && pq.top().first <= t) {
            quitf(_wa, "Connections are intersecting.");
        }
        pq.push({t, r});
    }
    quitf(_ok, "Connections are correct.");
}
