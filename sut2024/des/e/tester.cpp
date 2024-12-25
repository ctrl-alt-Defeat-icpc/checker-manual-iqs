#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> pll;

ll ansval = 0;

vector<pair<ll, pll>> a;
vector<pll> b;
vector<bool> matched;
/*
a: Vector of power supplies, where a[i].first is hi and a[i].second stores the matched consumer's coordinates.
b: Vector of consumers, where b[i].first is xi and b[i].second is yi.
matched: Boolean array to ensure no consumer is matched more than once.
*/
priority_queue<pll, vector<pll>, greater<pll>> pq;
bool input_flag;

int main(int argc, char const *argv[]) {
 
	ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
	// ifstream test_out(argv[2]);   /* This stream reads from test's output file  */
	ifstream user_out(argv[3]);   /* This stream reads from user's output file  */

    int w, h, n;
    test_in >> w >> h >> n;
    a.resize(n);
    b.resize(n);
    matched.resize(n, false);

    for (int i = 0; i < n; i++) {
        test_in >> a[i].first; // Read hi (vertical position of power supply i)
        a[i].second = {0, 0}; // Initialize the matched consumer
    }
    for (int i = 0; i < n; i++) {
        test_in >> b[i].second; // Read yi (vertical position of consumer i)
        test_in >> b[i].first; // Read xi (horizontal position of consumer i)
    }

    // verify contestant's output
    int p;
    for(int i = 0; i < n; i++) {
        input_flag = static_cast<bool>(user_out >> p);
        if(!input_flag) return 1; // you should exactly n input
        if(p < 1 || n < p) return 1; // index out of range
        if(matched[p - 1]) return 1; // index use more than once
        matched[p - 1] = true; // Mark consumer p-1 as matched
        a[i].second = b[p - 1]; // Assign consumer p-1 to power supply i
        ansval -= abs(a[i].first - b[p - 1].first) + b[p - 1].second; // Subtract wire length
    }
    input_flag = static_cast<bool>(user_out >> p);
    if(input_flag) return 1; // you should exactly n input


    // Sort and Recompute Wire Length
    sort(a.begin(), a.end());
    auto b_sorted = b;
    sort(b_sorted.begin(), b_sorted.end());
    for (int i = 0; i < n; i++) {
        ansval += abs(a[i].first - b_sorted[i].first) + b_sorted[i].second;
    }

    // Check Total Wire Length
    if(ansval < 0) return 1; // wrong length
    if(ansval > 0) return 1; // something wrong in checker

    // Check Wire Intersections
    for (auto [l, p] : a) {
        auto [r, t] = p;
        while (!pq.empty() && pq.top().second < l) {
            pq.pop();
        }
        if (!pq.empty() && pq.top().first <= t) 
            return 1; // Connections are intersecting
        pq.push({t, r});
    }

    pq = {};
    reverse(a.begin(), a.end());
    for (auto [l, p] : a) {
        auto [r, t] = p;
        while(!pq.empty() && pq.top().second > l) {
            pq.pop();
        }
        if (!pq.empty() && pq.top().first <= t)
            return 1; // Connections are intersecting
        pq.push({t, r});
    }

    return 0; // correct
}