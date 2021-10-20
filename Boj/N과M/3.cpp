#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v, v2;
int n, m;
void brute(int cnt) {
	if (cnt == m) {
		for (int i = 0; i < m; ++i)
			cout << v2[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = 0; i < n; ++i) {
		v2.push_back(v[i]);
		brute(cnt + 1);
		v2.pop_back();

	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		v.push_back(i);
	sort(v.begin(), v.end());
	brute(0);
}
