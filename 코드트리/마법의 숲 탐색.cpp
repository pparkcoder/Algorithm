// https://www.codetree.ai/training-field/frequent-problems/problems/magical-forest-exploration/description?page=1&pageSize=5
// x열 0~1은 처음 시작 위치로 가정하였으므로 실제 map의 유효 범위는 2부터 r+1까지
// 배열 범위 x열 늘리기 + 범위 체크 x열 늘리기
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<climits>
#define mp make_pair
using namespace std;
typedef struct {
	int num, exit;
}info;
typedef struct {
	int x, y, d;
}info2;
info I;
info2 I2;
info map[73][71];
bool visit[73][71];
vector<info2> v;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int r, c, k, check_num;
int result = 0;
bool check_len(int x, int y) {
	if (x > r || 1 > y || y > c || map[x][y].num) return false;
	return true;
}
bool check_bottom(int x, int y) {
	for (int i = 0; i < 4; ++i) {
		if (i == 0) continue;
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!check_len(nx, ny)) return false;
		int nnx = nx + dx[2];
		int nny = ny + dy[2];
		if (!check_len(nnx, nny)) return false;
	}
	return true;
}
bool check_right(int x, int y) {
	for (int i = 0; i < 4; ++i) {
		if (i == 3) continue;
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!check_len(nx, ny)) return false;
		int nnx = nx + dx[1];
		int nny = ny + dy[1];
		if (!check_len(nnx, nny)) return false;
	}
	if (!check_bottom(x, y + 1)) return false;
	return true;
}
bool check_left(int x, int y) {
	for (int i = 0; i < 4; ++i) {
		if (i == 1) continue;
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!check_len(nx, ny)) return false;
		int nnx = nx + dx[3];
		int nny = ny + dy[3];
		if (!check_len(nnx, nny)) return false;
	}
	if (!check_bottom(x, y - 1)) return false;
	return true;
}
void clear() {
	for (int i = 0; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			map[i][j].num = map[i][j].exit = 0;
		}
	}
}
void draw_map(int x, int y, int d) {
	map[x][y].num = check_num;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		map[nx][ny].num = check_num;
		if (i == d) map[nx][ny].exit = 1;
	}
}
void move(int tx, int ty) {
	queue<pair<int, int> > q;
	memset(visit, 0, sizeof(visit));
	q.push(mp(tx, ty));
	visit[tx][ty] = 1;
	int max_x = -INT_MAX;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		int now = map[x][y].num;
		max_x = max(x, max_x);
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (2 <= nx && nx <= r && 1 <= ny && ny <= c && map[nx][ny].num && !visit[nx][ny]) {
				if (now == map[nx][ny].num) {
					q.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
				else {
					if (map[x][y].exit) {
						q.push(mp(nx, ny));
						visit[nx][ny] = 1;
					}
				}
			}
		}
	}
	result += (max_x - 1);
}
void start() {
	for (int i = 0; i < k; ++i) {
		int x = v[i].x;
		int y = v[i].y;
		int d = v[i].d;
		int flag = 0;
		check_num = i + 1;
		while (1) {
			if (check_bottom(x, y)) { // 남쪽 이동 확인
				flag = 1;
				x += 1;
			}
			else if (check_left(x, y)) { // 서쪽 이동 확인
				flag = 1;
				x += 1;
				y -= 1;
				if (--d < 0) d = 3;
			}
			else if (check_right(x, y)) { // 동쪽 이동 확인
				flag = 1;
				x += 1;
				y += 1;
				if (++d > 3) d = 0;
			}
			else break;
		}
		if (!flag) clear();
		else {
			int flag2 = 0;
			for (int j = 0; j < 4; ++j) {
				int nx = x + dx[j];
				int ny = y + dy[j];
				if (2 > nx || nx > r || 1 > ny || ny > c) {
					flag2 = 1;
					break;
				}
			}
			if (!flag2) {
				draw_map(x, y, d);
				move(x, y);
			}
			else clear();
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> r >> c >> k;
	r += 1;
	for (int i = 0; i < k; ++i) {
		int y, d;
		cin >> y >> d;
		I2 = { 0,y,d };
		v.push_back(I2);
	}
	start();
	cout << result;
}
