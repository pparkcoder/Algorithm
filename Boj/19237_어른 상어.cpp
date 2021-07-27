// https://www.acmicpc.net/problem/19237

#include<iostream>
#include<vector>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, dir;
}info;
info I;
vector<pair<int, int> > map[21][21];
vector<info> v;
vector<int> priority[400][5];
int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,-1,1 };
int n, m, k, num;
bool check() {
	for (int i = 1; i < v.size(); ++i)
		if (v[i].x != -1) return false;
	return true;
}
int start() {
	int x, y, dir, nx, ny, ndir, flag;
	for (int t = 0; t <= 1000; ++t) {
		for (int i = 0; i < v.size(); ++i) {
			if (check()) return t;
			x = v[i].x;
			y = v[i].y;
			dir = v[i].dir;
			flag = 0;
			if (x == -1) continue;
			for (int j = 0; j < 4; ++j) {
				ndir = priority[i][dir - 1][j];
				nx = x + dx[ndir];
				ny = y + dy[ndir];
				if (0 < nx && nx <= n && 0 < ny && ny <= n && !map[nx][ny].size()) {
					flag = 1;
					break;
				}
			}
			if (!flag) {
				for (int j = 0; j < 4; ++j) {
					ndir = priority[i][dir - 1][j];
					nx = x + dx[ndir];
					ny = y + dy[ndir];
					if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny].front().first == i + 1) break;
				}
			}
			v[i].x = nx;
			v[i].y = ny;
			v[i].dir = ndir;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (map[i][j].size() && --map[i][j].front().second <= 0)
					map[i][j].clear();
			}
		}
		for (int i = 0; i < v.size(); ++i) {
			x = v[i].x;
			y = v[i].y;
			if (x == -1) continue;
			map[x][y].push_back(mp(i + 1, k));
		}
		vector<int> temp;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (map[i][j].size() > 1) {
					for (int l = 0; l < map[i][j].size(); ++l)
						temp.push_back(map[i][j][l].first);
					sort(temp.begin(), temp.end());
					for (int l = 1; l < map[i][j].size(); ++l)
						if (temp[l] != temp.front())	v[temp[l] - 1].x = -1;
					map[i][j].clear();
					map[i][j].push_back(mp(temp.front(), k));
					temp.clear();
				}
			}
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	vector<pair<int, pair<int, int> > > temp;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> num;
			if (1 <= num && num <= m) {
				map[i][j].push_back(mp(num, k));
				temp.push_back(mp(num, mp(i, j)));
			}
		}
	}
	sort(temp.begin(), temp.end());
	for (int i = 0; i < m; ++i) {
		cin >> num;
		I = { temp[i].second.first,temp[i].second.second,num };
		v.push_back(I);
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int l = 0; l < 4; ++l) {
				cin >> num;
				priority[i][j].push_back(num);
			}
		}
	}
	cout << start();
}
