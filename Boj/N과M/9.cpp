#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string>
using namespace std;
vector<int> v, v2;
map<string, int> check;
bool visit[9];
int n, m, num;
void brute(int cnt,string s) {
	if (cnt == m) {
		if (!check[s]) {
			check[s] = 1;
			for (int i = 0; i < m; ++i)
				cout << v2[i] << " ";
			cout << "\n";
		}
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (!visit[i]) {
			v2.push_back(v[i]);
			visit[i] = 1;
			brute(cnt + 1,s + to_string(v[i]));
			visit[i] = 0;
			v2.pop_back();
		}
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
	brute(0, "");
}
