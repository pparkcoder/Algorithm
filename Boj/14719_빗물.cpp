// https://www.acmicpc.net/problem/14719

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v;
int w, h;
int result = 0;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int num, left, right, temp;
	cin >> h >> w;
	for (int i = 0; i < w; ++i) {
		cin >> num;
		v.push_back(num);
	}
	for (int i = 1; i < w - 1; ++i) {
		left = right = 0;
		for (int j = i - 1; j >= 0; --j) left = max(v[j], left);
		for (int j = i + 1; j < w; ++j) right = max(v[j], right);
		temp = min(left, right) - v[i];
		if (temp > 0) result += temp;
	}
	cout << result;
}
