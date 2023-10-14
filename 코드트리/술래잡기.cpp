// https://www.codetree.ai/frequent-problems/hide-and-seek/description
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

// second
// 술래와 같은 위치에 있는 경우도 포함하여 find에서 넣어줘야 함
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#define mp make_pair
using namespace std;
typedef struct {
	int num, x, y, d;
}info;
info I;
vector<info> v;
vector<pair<int, int> > map[100][100]; // 도망자 번호, 방향
int visit[100][100];
bool tree[100][100];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int n, m, h, k, sx, sy;
int sd = 0, now = 0, cnt = 0, len = 1;
int result = 0;
bool flag = 0;
void kill(int t) {
	int kill_cnt = 0;
	for (int i = 0; i < 3; ++i) {
		int nx = sx + dx[sd] * i;
		int ny = sy + dy[sd] * i;
		if (1 > nx || nx > n || 1 > ny || ny > n) break;
		if (tree[nx][ny]) continue;
		int temp = map[nx][ny].size();
		if (temp) {
			kill_cnt += temp;
			map[nx][ny].clear();
		}
	}
	result += (t * kill_cnt);
}
void move2() {
	sx += dx[sd];
	sy += dy[sd];
	++now;
	if (sx == 1 && sy == 1) {
		sd = 2;
		flag = !flag;
		cnt = now = 0;
	}
	if (flag && sx == n && sy == 1) {
		sd = 1;
		cnt = now = 0;
		--len;
	}
	if (sx == (n / 2) + 1 && sy == (n / 2) + 1) {
		sd = 0;
		flag = !flag;
		cnt = now = 0;
		len = 1;
	}
	if (now == len) {
		++cnt;
		now = 0;
		if (!flag && ++sd > 3) sd = 0;
		else if (flag && --sd < 0) sd = 3;
	}
	if (cnt == 2) {
		cnt = 0;
		if (!flag) ++len;
		else --len;
	}
}
void move1() {
	for (int i = 0; i < v.size(); ++i) {
		int num = v[i].num;
		int x = v[i].x;
		int y = v[i].y;
		int d = v[i].d;
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (1 > nx || nx > n || 1 > ny || ny > n) {
			if (d < 2) d += 2;
			else d -= 2;
			nx = x + dx[d];
			ny = y + dy[d];
		}
		if (nx == sx && ny == sy) {
			nx = x;
			ny = y;
		}
		for (int j = 0; j < map[x][y].size(); ++j) {
			if (num == map[x][y][j].first) {
				map[x][y].erase(map[x][y].begin() + j);
				break;
			}
		}
		v[i].x = nx;
		v[i].y = ny;
		v[i].d = d;
		map[nx][ny].push_back(mp(num, d));
	}
}
void find() {
	memset(visit, 0, sizeof(visit));
	v.clear();
	queue<pair<int, int> > q;
	q.push(mp(sx, sy));
	visit[sx][sy] = 1;
	if (map[sx][sy].size()) {
		for (int i = 0; i < map[sx][sy].size(); ++i) {
			I = { map[sx][sy][i].first, sx, sy, map[sx][sy][i].second };
			v.push_back(I);
		}
	}
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
				q.push(mp(nx, ny));
				visit[nx][ny] = visit[x][y] + 1;
				if (visit[nx][ny] <= 4 && map[nx][ny].size()) {
					for (int j = 0; j < map[nx][ny].size(); ++j) {
						I = { map[nx][ny][j].first, nx,ny,map[nx][ny][j].second };
						v.push_back(I);
					}
				}
			}
		}
	}
}
void start() {
	for (int t = 1; t <= k; ++t) {
		find();
		move1();
		move2();
		kill(t);
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> h >> k;
	int x, y, d, td;
	for (int i = 1; i <= m; ++i) {
		cin >> x >> y >> d;
		if (d == 1) td = 1;
		else td = 2;
		map[x][y].push_back(mp(i, td));
	}
	for (int i = 1; i <= h; ++i) {
		cin >> x >> y;
		tree[x][y] = 1;
	}
	sx = sy = (n / 2) + 1;
	start();
}
