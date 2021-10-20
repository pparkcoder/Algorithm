#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v, v2;
int n, m, num;
void brute(int idx, int cnt) {
	if (cnt == m) {
		for (int i = 0; i < m; ++i)
			cout << v2[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = idx; i < n; ++i) {
			v2.push_back(v[i]);
			brute(i + 1, cnt + 1);
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
	brute(0, 0);
}
