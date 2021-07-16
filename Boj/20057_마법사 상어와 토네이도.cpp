// https://www.acmicpc.net/problem/20057

#include<iostream>
using namespace std;
int sand_dx[4][10] = { {-1,1,-2,2,0,-1,1,-1,1,0},{-1,-1,0,0,2,0,0,1,1,1},{-1,1,-2,2,0,-1,1,-1,1,0},{1,1,0,0,-2,0,0,-1,-1,-1} };
int sand_dy[4][10] = { {1,1,0,0,-2,0,0,-1,-1,-1},{-1,1,-2,2,0,-1,1,-1,1,0},{-1,-1,0,0,2,0,0,1,1,1},{-1,1,-2,2,0,-1,1,-1,1,0} };
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
int map[500][500];
int n;
int result = 0;
void calc(int x, int y, int dir, int total_sand) {
	int use_sum = 0, use_sand = 0;
	int nx, ny;
	for (int i = 0; i < 10; ++i) {
		nx = x + sand_dx[dir][i];
		ny = y + sand_dy[dir][i];
		if (i < 2) use_sand = total_sand * 0.01;
		else if (i < 4) use_sand = total_sand * 0.02;
		else if (i < 5) use_sand = total_sand * 0.05;
		else if (i < 7) use_sand = total_sand * 0.07;
		else if (i < 9) use_sand = total_sand * 0.1;
		else if (i == 9) use_sand = total_sand - use_sum;
		if (1 > nx || nx > n || 1 > ny || ny > n) result += use_sand;
		else map[nx][ny] += use_sand;
		use_sum += use_sand;
	}
	map[x][y] = 0;
}
void start() {
	int x, y, dir, now_len, move_cnt, move_len;
	x = y = (n / 2) + 1;
	now_len = move_cnt = dir = 0;
	move_len = 1;
	while (0 < x && x <= n && 0 < y && y <= n) {
		x += dx[dir];
		y += dy[dir];
		if(map[x][y]) calc(x, y, dir, map[x][y]);
		++now_len;
		if (now_len == move_len) {
			now_len = 0;
			++move_cnt;
			if (++dir > 3) dir = 0;
		}
		if (move_cnt == 2) {
			move_cnt = 0;
			++move_len;
		}
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	start();
}
