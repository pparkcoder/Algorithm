// https://www.acmicpc.net/problem/14499

#include<iostream>
#include<deque>
#include<vector>
using namespace std;
deque<int> q;
int dice[4][3];
int map[21][21];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };
vector<int> v;
int n, m, x, k, y, temp;
void f() {
	temp = q.front();
	q.pop_front();
	q.push_back(temp);
}
void b() {
	temp = q.back();
	q.pop_back();
	q.push_front(temp);
}
void start() {
	if (map[x][y]) {
		dice[3][1] = map[x][y];
		map[x][y] = 0;
	}
	else map[x][y] = dice[3][1];
	for (int i = 0; i < v.size(); ++i) {
		int dir = v[i];
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (0 > nx || nx >= n || 0 > ny || ny >= m) continue;
		if (dir > 2) {
			for (int j = 0; j < 4; ++j)
				q.push_back(dice[j][1]);
			if (dir == 4) b();
			else f();
			for (int j = 0; j < 4; ++j) {
				dice[j][1] = q.front();
				q.pop_front();
			}
		}
		else {
			q.push_back(dice[3][1]);
			for (int j = 0; j < 3; ++j)
				q.push_back(dice[1][j]);
			if (dir == 1) b();
			else f();
			dice[3][1] = q.front();
			q.pop_front();
			for (int j = 0; j < 3; ++j) {
				dice[1][j] = q.front();
				q.pop_front();
			}
		}
		if (map[nx][ny]) {
			dice[3][1] = map[nx][ny];
			map[nx][ny] = 0;
		}
		else map[nx][ny] = dice[3][1];
		x = nx;
		y = ny;
		cout << dice[1][1] << "\n";
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> map[i][j];
	while (k--) {
		cin >> temp;
		v.push_back(temp);
	}
	start();
}
