// https://www.acmicpc.net/problem/23289

#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
typedef struct {
	int x, y, dir;
}info;
info I;
vector<info> v;
vector<pair<int, int> > v2;
queue<pair<int, int> >q;
int dx[5] = { 0,0,0,-1,1 }; // 온풍기 바람 방향
int dy[5] = { 0,1,-1,0,0 };
int dx2[5][3] = { {0,0,0}, {-1,0,1},{-1,0,1},{-1,-1,-1},{1,1,1} }; // 온풍기 바람 방향에 따른 바람 전파 방향
int dy2[5][3] = { {0,0,0}, {1,1,1},{-1,-1,-1},{-1,0,1},{-1,0,1} };
int map[21][21], visit[21][21], memo[21][21], wall[21][21][5];
int r, c, k, w, x, y, dir, t, num;
int result = 0;
bool check() {
	for (int i = 0; i < v2.size(); ++i) 
		if (map[v2[i].first][v2[i].second] < k) return false;
	return true;
}
void make_sub() {
	memset(memo, 0, sizeof(memo));
	int temp_num;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			if (map[i][j]) {
				for (int l = 1; l < 5; ++l) {
					int nx = i + dx[l];
					int ny = j + dy[l];
					if (0 < nx && nx <= r && 0 < ny && ny <= c && !wall[i][j][l] && map[nx][ny] < map[i][j]) {
						temp_num = (map[i][j] - map[nx][ny]) / 4;
						memo[i][j] -= temp_num;
						memo[nx][ny] += temp_num;
					}
				}
			}
		}
	}
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			map[i][j] += memo[i][j];
			if (map[i][j] < 0) map[i][j] = 0;
		}
	}
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			if (i == 1 || i == r || j == 1 || j == c) {
				if (map[i][j] && --map[i][j] < 0) map[i][j] = 0;
			}
		}
	}
}
void move() {
	int nx, ny, visit_num, sx, sy, len;
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < v.size(); ++i) {
		while (!q.empty()) q.pop();
		x = v[i].x;
		y = v[i].y;
		dir = v[i].dir;
		num = 5;
		visit_num = i + 1;
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (0 < nx && nx <= r && 0 < ny && ny <= c) {
			map[nx][ny] += num;
			q.push(make_pair(nx, ny));
			visit[nx][ny] = visit_num;
		}
		else continue;
		while (--num) {
			len = q.size();
			while (len--) {
				sx = q.front().first;
				sy = q.front().second; q.pop();
				for (int j = 0; j < 3; ++j) {
					nx = sx + dx2[dir][j];
					ny = sy + dy2[dir][j];
					if (0 < nx && nx <= r && 0 < ny && ny <= c && visit[nx][ny] != visit_num) {
						if (dir == 1 && !wall[nx][ny][2]) {
							if ((!j && !wall[sx][sy][3]) || (j == 1 && !wall[sx][sy][1]) || (j == 2 && !wall[sx][sy][4])) {
								map[nx][ny] += num;
								q.push(make_pair(nx, ny));
								visit[nx][ny] = visit_num;
							}
						}
						else if (dir == 2 && !wall[nx][ny][1]) {
							if ((!j && !wall[sx][sy][3]) || (j == 1 && !wall[sx][sy][2]) || (j == 2 && !wall[sx][sy][4])) {
								map[nx][ny] += num;
								q.push(make_pair(nx, ny));
								visit[nx][ny] = visit_num;
							}
						}
						else if (dir == 3 && !wall[nx][ny][4]) {
							if ((!j && !wall[nx][ny][2]) || (j == 1 && !wall[nx][ny][3]) || (j == 2 && !wall[nx][ny][1])) {
								map[nx][ny] += num;
								q.push(make_pair(nx, ny));
								visit[nx][ny] = visit_num;
							}
						}
						else if (dir == 4 && !wall[nx][ny][3]) {
							if ((!j && !wall[nx][ny][2]) || (j == 1 && !wall[nx][ny][4]) || (j == 2 && !wall[nx][ny][1])) {
								map[nx][ny] += num;
								q.push(make_pair(nx, ny));
								visit[nx][ny] = visit_num;
							}
						}
					}
				}
			}
			if (q.empty()) break;
		}
	}
}
void start() {
	while (1) {
		move();
		make_sub();
		++result;
		if (check()) break;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> r >> c >> k;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			cin >> map[i][j];
			if (map[i][j]) {
				if (map[i][j] == 5) v2.push_back(make_pair(i, j));
				else {
					I = { i,j,map[i][j] };
					v.push_back(I);
				}
				map[i][j] = 0;
			}
		}
	}
	cin >> w;
	for (int i = 0; i < w; ++i) {
		cin >> x >> y >> t;
		if (!t) wall[x][y][3] = wall[x - 1][y][4] = 1;
		else wall[x][y][1] = wall[x][y + 1][2] = 1;
	}
	start();
	cout << result;
}
