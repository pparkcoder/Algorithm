// https://www.acmicpc.net/problem/19237

#include<iostream>
#include<vector>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int num, x, y, dir, life;
}info;
info I;
vector<info> v;
vector<pair<int, int> > map[21][21]; // 번호,시간
vector<int> priority[400][4];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int n, m, k;
bool cmp(info a, info b) {
	if (a.num < b.num) return true;
	else return false;
}
bool check() {
	int temp;
	for (int i = 0; i < m; ++i) {
		if (!v[i].life) continue;
		int x = v[i].x;
		int y = v[i].y;
		int num = v[i].num;
		map[x][y].push_back(mp(num, k + 1));
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			temp = map[i][j].size();
			if (temp) {
				if (temp > 1) {
					sort(map[i][j].begin(), map[i][j].end());
					if (map[i][j][0].first == map[i][j][1].first) map[i][j][0].second = k + 1;
					else {
						for (int l = 1; l < temp; ++l)
							v[map[i][j][l].first - 1].life = 0;
					}
					map[i][j].erase(map[i][j].begin() + 1, map[i][j].end());
				}
				if (--map[i][j][0].second <= 0) map[i][j].clear();
			}
		}
	}
	for (int i = 1; i < m; ++i)
		if (v[i].life) return false;
	return true;
}
int start() {
	int num, x, y, dir, nx, ny, ndir, flag;
	for (int l = 1; l < 1001; ++l) {
		for (int i = 0; i < m; ++i) {
			if (!v[i].life) continue;
			num = v[i].num;
			x = v[i].x;
			y = v[i].y;
			dir = v[i].dir;
			flag = 0;
			for (int temp = 0; temp < 2; ++temp) {
				for (int j = 0; j < 4; ++j) {
					ndir = priority[i][dir][j];
					nx = x + dx[ndir];
					ny = y + dy[ndir];
					if (0 < nx && nx <= n && 0 < ny && ny <= n) {
						if (!temp && !map[nx][ny].size()) {
							flag = 1;
							break;
						}
						else if (temp && map[nx][ny][0].first == num) {
							flag = 1;
							break;
						}
					}
				}
				if (flag) {
					v[i].x = nx;
					v[i].y = ny;
					v[i].dir = ndir;
					break;
				}
			}
		}
		if (check()) return l;
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int num, dir;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> num;
			if (num) {
				map[i][j].push_back(mp(num, k));
				I = { num,i,j,0,1 };
				v.push_back(I);
			}
		}
	}
	sort(v.begin(), v.end(), cmp);
	for (int i = 0; i < m; ++i) {
		cin >> dir;
		v[i].dir = dir - 1;
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int l = 0; l < 4; ++l) {
				cin >> dir;
				priority[i][j].push_back(dir - 1);
			}
		}
	}
	cout << start();
}
