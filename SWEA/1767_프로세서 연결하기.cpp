//시간 줄이는 법 고민하기

#include<iostream>
#include<vector>
#define mp make_pair
using namespace std;
vector<pair<int, int> >v;
int map[13][13];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int t, n, result_core, result_len;
bool check(int x, int y, int dir, vector<pair<int, int> > &temp) {
	while (1) {
		x += dx[dir];
		y += dy[dir];
		if (1 > x || x > n || 1 > y || y > n) return true;
		if (map[x][y] > 0) return false;
		temp.push_back(mp(x, y));
	}
}
void dfs(int index, int core, int len) {
	if (index == v.size()) {
		if (result_core < core) {
			result_core = core;
			result_len = len;
		}
		else if (result_core == core) {
			if (result_len > len)
				result_len = len;
		}
		return;
	}
	vector<pair<int, int> >temp;
	int x, y;
	for (int i = index; i < v.size(); i++) {
		x = v[i].first;
		y = v[i].second;
		for (int j = 0; j < 4; j++) {
			if (check(x, y, j, temp)) {
				for (int k = 0; k < temp.size(); k++)
					map[temp[k].first][temp[k].second] = 2;
				dfs(i + 1, core + 1, len + temp.size());
				for (int k = 0; k < temp.size(); k++)
					map[temp[k].first][temp[k].second] = 0;
			}
			temp.clear();
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> t;
	for (int test = 1; test <= t; test++) {
		v.clear();
		result_core = 0, result_len = 987654321;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
				if (map[i][j]) {
					if (i == 1 || i == n || j == 1 || j == n) ++result_core;
					else v.push_back(mp(i, j));
				}
			}
		}
		dfs(0, result_core, 0);
		cout << "#" << test << " " << result_len << "\n";
	}
}
