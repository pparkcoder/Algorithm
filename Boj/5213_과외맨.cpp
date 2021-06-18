// https://www.acmicpc.net/problem/5213

#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
typedef struct {
	int num, n1, n2;
}info;
typedef struct {
	vector<int> v;
	int x, y;
}info2;
info2 I;
queue<info2> q;
info map[501][501];
bool visit[501][501];
int dx[8] = { 0,0,-1,1,-1,-1,1,1 };
int dy[8] = { 1,-1,0,0,1,-1,1,-1 };
int n;

bool check(int x, int y) {
	if (0 < x && x <= n && 0 < y && y <= n && !visit[x][y]) return true;
	return false;
}

void push(vector<int> &v, int nx, int ny) {
	vector<int> temp = v;
	temp.push_back(map[nx][ny].num);
	I = { temp,nx,ny };
	q.push(I);
	visit[nx][ny] = 1;
}

void bfs() {
	vector<int> v, result;
	v.push_back(1);
	I = { v,1,1 };
	q.push(I);
	visit[1][1] = 1;
	int x, y, nx, ny, nnx, nny, max_num;
	max_num = 0;
	while (!q.empty()) {
		vector<int> v = q.front().v;
		x = q.front().x;
		y = q.front().y; q.pop();
		if (map[x][y].num == n * n - n / 2) {
			cout << v.size() << "\n";
			for (int i = 0; i < v.size(); i++)
				cout << v[i] << " ";
			return;
		}
		else if (max_num < map[x][y].num) {
			max_num = map[x][y].num;
			result = v;
		}
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (check(nx, ny)) {
				if (i == 0 && map[x][y].n2 == map[nx][ny].n1) push(v, nx, ny);
				else if (i == 1 && map[x][y].n1 == map[nx][ny].n2) push(v, nx, ny);
			}
			if (i == 2) {
				if (!(x % 2)) {
					if (check(nx, ny) && map[x][y].n1 == map[nx][ny].n2) push(v, nx, ny);
					nnx = x + dx[4], nny = y + dy[4];
					if (check(nnx, nny) && map[x][y].n2 == map[nnx][nny].n1) push(v, nnx, nny);
				}
				else if (x % 2) {
					if (check(nx, ny) && map[x][y].n2 == map[nx][ny].n1) push(v, nx, ny);
					nnx = x + dx[5], nny = y + dy[5];
					if (check(nnx, nny) && map[x][y].n1 == map[nnx][nny].n2) push(v, nnx, nny);
				}
			}
			else if (i == 3) {
				if (!(x % 2)) {
					if (check(nx, ny) && map[x][y].n1 == map[nx][ny].n2) push(v, nx, ny);
					nnx = x + dx[6], nny = y + dy[6];
					if (check(nnx, nny) && map[x][y].n2 == map[nnx][nny].n1) push(v, nnx, nny);
				}
				else if (x % 2) {
					if (check(nx, ny) && map[x][y].n2 == map[nx][ny].n1) push(v, nx, ny);
					nnx = x + dx[7], nny = y + dy[7];
					if (check(nnx, nny) && map[x][y].n1 == map[nnx][nny].n2) push(v, nnx, nny);
				}
			}
		}
	}
	cout << max_num << "\n";
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << " ";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int index = 1;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!(i % 2) && !(j % n)) continue;
			cin >> map[i][j].n1 >> map[i][j].n2;
			map[i][j].num = index++;
		}
	}
	bfs();
}
