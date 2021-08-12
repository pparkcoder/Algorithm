// https://www.acmicpc.net/problem/16637
// Tip -> char to string 이 중요

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<climits>
using namespace std;
vector<string> v;
bool check[20];
string s;
int n;
int result = -INT_MAX;
void calc() {
	v.clear();
	for (int i = 0; i < n; ++i) {
		string temp = "";
		if (i % 2) 
			v.push_back(s[i] + temp);
		else {
			if (check[i] && check[i + 2]) {
				if (s[i + 1] == '+') v.push_back(to_string((s[i] - '0') + (s[i + 2] - '0')));
				else if (s[i + 1] == '-') v.push_back(to_string((s[i] - '0') - (s[i + 2] - '0')));
				else v.push_back(to_string((s[i] - '0') * (s[i + 2] - '0')));
				i += 2;
			}
			else
				v.push_back(s[i] + temp);
		}
	}
	int temp = stoi(v[0]);
	for (int i = 1; i < v.size(); i += 2) {
		if (v[i] == "+") temp += stoi(v[i + 1]);
		else if (v[i] == "-") temp -= stoi(v[i + 1]);
		else temp *= stoi(v[i + 1]);
	}
	result = max(result, temp);
}
void brute(int index) {
	calc();
	if (index >= n) return;
	for (int i = index; i < n - 2; i += 2) {
		if (!check[i] && !check[i + 2]) {
			check[i] = check[i + 2] = 1;
			brute(i + 2);
			check[i] = check[i + 2] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> s;
	brute(0);
	cout << result;
}
