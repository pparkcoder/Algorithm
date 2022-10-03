// https://www.acmicpc.net/problem/2992

#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<algorithm>
using namespace std;
vector<int> v;
bool visit[6];
int result = INT_MAX;
void brute(string s,int num) {
	if (s.length() == v.size()) {
		if (s[0] != '0' && num < stoi(s)) result = min(result, stoi(s));
		return;
	}
	for (int i = 0; i < v.size(); ++i) {
		if (!visit[i]) {
			visit[i] = 1;
			brute(s + to_string(v[i]), num);
			visit[i] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s;
	cin >> s;
	for (int i = 0; i < s.length(); ++i) 
		v.push_back(s[i] - '0');
	brute("", stoi(s));
	cout << (result == INT_MAX ? 0 : result);
}
