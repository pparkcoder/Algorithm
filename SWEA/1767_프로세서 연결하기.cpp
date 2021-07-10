#include<iostream>
#include<vector>
#include<algorithm>
#define mp make_pair
using namespace std;
vector<pair<int, int> > v;
int map[13][13];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int t, n, result_core, result_len;
int check(int x, int y, int dir) {
	for (int i = 1;; ++i) {
		int nx = x + dx[dir] * i;
		int ny = y + dy[dir] * i;
		if (1 > nx || nx > n || 1 > ny || ny > n) return i - 1;
		if (map[nx][ny]) break;
	}
	return 0;
}
void make_len(int x, int y, int dir, int num,int len) {
	for (int i = 1;i<=len; ++i) {
		int nx = x + dx[dir] * i;
		int ny = y + dy[dir] * i;
		map[nx][ny] = num;
	}
}
void dfs(int core_cnt, int len_cnt, int index) {
	if (index == v.size()) {
		if (result_core < core_cnt) {
			result_core = core_cnt;
			result_len = len_cnt;
		}
		else if (result_core == core_cnt)
			result_len = min(result_len, len_cnt);
		return;
	}
	int x = v[index].first;
	int y = v[index].second;
	int len;
	for (int i = 0; i < 4; ++i) {
		len = check(x, y, i);
		if (len) {
			make_len(x, y, i, 2,len);
			dfs(core_cnt + 1, len_cnt + len, index + 1);
			make_len(x, y, i, 0,len);
		}
	}
	dfs(core_cnt, len_cnt, index + 1);
	return;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int tc = 1; tc <= t; ++tc) {
		cin >> n;
		result_core = -987654321, result_len = 987654321;
		v.clear();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> map[i][j];
				if (map[i][j]) {
					if (i == 1 || j == 1 || i == n || j == n) continue;
					v.push_back(mp(i, j));
				}
			}
		}
		dfs(0, 0, 0);
		cout << "#" << tc << " " << result_len << "\n";
	}
}
