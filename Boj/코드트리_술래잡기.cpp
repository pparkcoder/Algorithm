// 방향을 바로 틀어줘야 함 - 정방향은 구현한 그대로, 역방향은 한칸 더 보도록 구현해야 함

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
typedef struct {
	int x, y, dir, life;
}info;
info I;
vector<info> v;
vector<int> map[100][100];
bool visit[100][100], tree[100][100];
int dx1[4] = { -1,0,1,0 };
int dy1[4] = { 0,1,0,-1 };
int dx2[4] = { 1,0,-1,0 };
int dy2[4] = { 0,1,0,-1 };
int n, m, h, k, x, y, dir, nx, ny, sx, sy;
int result = 0, cnt = 0, check_cnt = 1, temp = 0, sdir = 0, flag = 0 // flag  0 : 정방향, 1: 역방향
void kill(int turn) {
	int snx, sny, ans;
	for (int i = 0; i < 3; ++i) {
		if (!flag) {
			snx = sx + dx1[sdir] * i;
			sny = sy + dy1[sdir] * i;
		}
		else {
			snx = sx + dx2[sdir] * i;
			sny = sy + dy2[sdir] * i;
		}
		if (1 > snx || snx > n || 1 > sny || sny > n) break;
		if (tree[snx][sny]) continue;
		ans = map[snx][sny].size();
		if (ans) {
			result += (ans * turn);
			for (int j = 0; j < ans; ++j)
				v[map[snx][sny][j]].life = 0;
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			map[i][j].clear();
}
void move(int turn) {
	int snx, sny;
	int flag2 = 0;
	if (!flag) { // 중앙에서 시작 - dx1 사용
		snx = sx + dx1[sdir];
		sny = sy + dy1[sdir];
		++cnt;
		if (cnt == check_cnt) {
			cnt = 0;
			++temp;
			if (++sdir > 3) sdir = 0;
		}
		if (temp && temp % 2 == 0) temp = 0, ++check_cnt;
		if (snx == 1 && sny == 1) flag = 1, sdir = 0, cnt = 0, check_cnt = 1, temp = 0;
	}
	else { // 1,1에서 시작 - dx2 사용
		visit[sx][sy] = 1;
		snx = sx + dx2[sdir];
		sny = sy + dy2[sdir];
		int snnx = snx + dx2[sdir];
		int snny = sny + dy2[sdir];
		if (1 > snnx || snnx > n || 1 > snny || snny > n || visit[snnx][snny]) {
			if (++sdir > 3) sdir = 0;
		}
		if (snx == (n / 2) + 1 && sny == (n / 2) + 1) flag = 0, sdir = 0, memset(visit, 0, sizeof(visit));
	}
	sx = snx;
	sy = sny;
}
void start() {
	for (int i = 1; i <= k; ++i) {
		for (int j = 0; j < v.size(); ++j) {
			if (!v[j].life) continue;
			x = v[j].x;
			y = v[j].y;
			dir = v[j].dir;
			if (abs(sx - x) + abs(sy - y) > 3) { // 움직이지 못하는 경우에도 잡힐 수 있으므로 map에 넣어줘야 함
				nx = x;
				ny = y;
			}
			else {
				nx = x + dx1[dir];
				ny = y + dy1[dir];
				if (1 > nx || nx > n || 1 > ny || ny > n) {
					if (dir < 2) dir += 2;
					else dir -= 2;
					nx = x + dx1[dir];
					ny = y + dy1[dir];
				}
				if (nx == sx && ny == sy) nx = x, ny = y;
				v[j].x = nx;
				v[j].y = ny;
				v[j].dir = dir;
			}
			map[nx][ny].push_back(j);
		}
		move(i);
		kill(i);
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> h >> k;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> dir;
		I = { x,y,dir,1 };
		v.push_back(I);
	}
	for (int i = 0; i < h; ++i) {
		cin >> x >> y;
		tree[x][y] = 1;
	}
	sx = sy = (n / 2) + 1;
	start();
	cout << result;
}
