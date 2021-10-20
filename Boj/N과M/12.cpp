#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string>
using namespace std;
vector<int> v, v2;
map<string, int> check;
int n, m, num;
void brute(int idx, int cnt, string s) {
	if (cnt == m) {
		if (!check[s]) {
			check[s] = 1;
			for (int i = 0; i < m; ++i)
				cout << v2[i] << " ";
			cout << "\n";
		}
		return;
	}
	for (int i = idx; i < n; ++i) {
		v2.push_back(v[i]);
		brute(i, cnt + 1, s + to_string(v[i]) + "/");
		v2.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());
	brute(0, 0, "");
}
