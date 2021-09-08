// https://www.acmicpc.net/problem/15686

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, int> > one, two, temp;
int map[51][51];
int n, m, ans, r1, c1, r2, c2, len;
int result = 987654321;
void calc() {
	ans = 0;
	for (int i = 0; i < one.size(); i++) {
		r1 = one[i].first;
		c1 = one[i].second;
		len = 987654321;
		for (int j = 0; j < temp.size(); j++) {
			r2= temp[j].first;
			c2 = temp[j].second;
			len = min(len, abs(r1 - r2) + abs(c1 - c2));
		}
		ans += len;
	}
	result = min(result, ans);
}
void brute(int index, int cnt, int MAX) {
	if (cnt == MAX) {
		calc();
		return;
	}
	for (int i = index; i < two.size(); i++) {
		temp.push_back(make_pair(two[i].first, two[i].second));
		brute(i + 1, cnt + 1, MAX);
		temp.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) one.push_back(make_pair(i, j));
			else if (map[i][j] == 2) two.push_back(make_pair(i, j));
		}
	}
	for (int i = 1; i <= m; i++)
		brute(0, 0, i);
	cout << result;
}
