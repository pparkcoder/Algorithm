// https://www.acmicpc.net/problem/2304

#include<iostream>
#include<vector>
#include<algorithm>
#define mp make_pair
using namespace std;
vector<pair<int, int> > v;
int n, l, h;
int result = 0, max_l = 0, max_h = 0;
void start() {
	int stop, left, right, temp, st;
	st = max_l;
	while (1) {
		left = stop = 0;
		for (int i = st - 1; i >= 0; --i) {
			if (left < v[i].second) {
				temp = i;
				left = v[i].second;
				stop = 1;
			}
		}
		if (!stop) break; 
		result += ((v[st].first - v[temp].first) * left);
		st = temp;
	}
	st = max_l;
	while (1) {
		right = stop = 0;
		for (int i = st + 1; i < n; ++i) {
			if (right < v[i].second) {
				temp = i;
				right = v[i].second;
				stop = 1;
			}
		}
		if (!stop) break;
		result += (abs(v[st].first - v[temp].first) * right);
		st = temp;
	}
	result += max_h;
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> l >> h;
		v.push_back(mp(l, h));
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < n; ++i) {
		if (max_h < v[i].second) {
			max_h = v[i].second;
			max_l = i;
		}
	}
	start();
}
