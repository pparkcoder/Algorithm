//https://www.acmicpc.net/problem/2470

//5356KB, 28ms
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#define mp make_pair
using namespace std;
vector<int> v;
vector<pair<int, pair<int, int> > > result;
int n, num, s, e, sum;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());
	s = 0, e = v.size() - 1;
	while (s < e && s != e) {
		sum = v[s] + v[e];
		result.push_back(mp(abs(sum), mp(v[s], v[e])));
		if (sum < 0) sum -= v[s++];
		else sum -= v[e--];
	}
	sort(result.begin(), result.end());
	cout << result[0].second.first << " " << result[0].second.second;
}

//2916KB, 16ms
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<climits>
#define mp make_pair
using namespace std;
vector<int> v;
int n, num, s, e, sum, result1, result2;
int result = INT_MAX;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());
	s = 0, e = v.size() - 1;
	while (s < e && s != e) {
		sum = v[s] + v[e];
		if (abs(sum) < result) {
			result = abs(sum);
			result1 = v[s];
			result2 = v[e];
		}
		if (sum < 0) sum -= v[s++];
		else sum -= v[e--];
	}
	cout << result1 << " " << result2;
}
