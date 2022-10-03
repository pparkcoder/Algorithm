// https://www.acmicpc.net/problem/20920

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef struct {
	int cnt, len;
	string s;
}info;
info I;
vector<info> v;
map<string, int> visit;
int n, m, cnt, len;
string s;
bool cmp(info a, info b) {
	if (a.cnt == b.cnt) {
		if (a.len == b.len) return a.s > b.s;
		else return a.len < b.len;
	}
	else return a.cnt < b.cnt;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		if (s.length() >= m) ++visit[s];
	}
	for (auto iter = visit.begin(); iter != visit.end(); ++iter) {
		cnt = iter->second;
		s = iter->first;
		len = s.length();
		I = { cnt,len,s };
		v.push_back(I);
	}
	sort(v.begin(), v.end(), cmp);
	for (int i = v.size() - 1; i >= 0; --i) 
		cout << v[i].s << "\n";
}
