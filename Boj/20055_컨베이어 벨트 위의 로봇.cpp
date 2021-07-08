// https://www.acmicpc.net/problem/20055

#include<iostream>
#include<deque>
#define mp make_pair
using namespace std;
deque<pair<int, bool> >d;
int n, k, num, cnt;
int start() {
	for (int i = 1;; ++i) {
		num = d.back().first;
		d.pop_back();
		d.push_front(mp(num, 0));
		if (d[n - 1].second) d[n - 1].second = 0;
		for (int i = n - 2; i >= 0; --i) {
			if (d[i].second && d[i + 1].first && !d[i + 1].second) {
				d[i].second = 0;
				--d[i + 1].first;
				d[i + 1].second = 1;
			}
		}
		if (d[n - 1].second) d[n - 1].second = 0;
		if (d[0].first && !d[0].second) {
			--d[0].first;
			d[0].second = 1;
		}
		cnt = 0;
		for (int j = 0; j < 2 * n; ++j) {
			if (!d[j].first) ++cnt;
			if (cnt == k) return i;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < 2 * n; ++i) {
		cin >> num;
		d.push_back(mp(num, 0));
	}
	cout << start();
}
