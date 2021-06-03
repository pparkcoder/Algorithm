#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, cnt, dir;
}info;
info I;
queue<info> q;
vector<pair<int, int> > map[101][101];
int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,-1,1 };
int test_case, n, m, k, result;
int start() {
	int x, y, cnt, dir, nx, ny, len, sum;
	while (m--) {
		while (!q.empty()) {
			x = q.front().x;
			y = q.front().y;
			cnt = q.front().cnt;
			dir = q.front().dir; q.pop();
			nx = x + dx[dir];
			ny = y + dy[dir];
			if (nx == 0 || ny == 0 || nx == n - 1 || ny == n - 1) {
				if (dir == 1 || dir == 3) ++dir;
				else --dir;
				cnt /= 2;
			}
			if (cnt) map[nx][ny].push_back(mp(cnt, dir));
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				len = map[i][j].size();
				if (len) {
					if (len > 1) {
						sum = 0;
						sort(map[i][j].begin(), map[i][j].end());
						for (int l = 0; l < len; ++l)
							sum += map[i][j][l].first;
						I = { i,j,sum,map[i][j][len - 1].second };
						q.push(I);
					}
					else if (len == 1) {
						I = { i,j,map[i][j].front().first,map[i][j].front().second };
						q.push(I);
					}
					map[i][j].clear();
				}
			}
		}
	}
	result = 0;
	while (!q.empty()) {
		result += q.front().cnt;
		q.pop();
	}
	return result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> test_case;
	int x, y, cnt, dir;
	for (int i = 1; i <= test_case; ++i) {
		cin >> n >> m >> k;
		while (k--) {
			cin >> x >> y >> cnt >> dir;
			I = { x,y,cnt,dir };
			q.push(I);
		}
		cout << "#" << i << " " << start() << "\n";
	}
}
