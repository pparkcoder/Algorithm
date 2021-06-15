// https://www.acmicpc.net/problem/16137

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, cnt, flag;
}info;
info I;
queue<info> q;
vector<pair<int, int> > v;
int map[11][11];
bool visit[11][11];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int result = 987654321;
int n, m;

bool check(int x, int y) {
	int nx1, ny1, nx2, ny2;
	for (int i = 0; i < 2; ++i) {
		nx1 = x + dx[i];
		ny1 = y + dy[i];
		if (0 <= nx1 && nx1 < n && 0 <= ny1 && ny1 < n && !map[nx1][ny1]) {
			for (int j = 2; j < 4; ++j) {
				nx2 = x + dx[j];
				ny2 = y + dy[j];
				if (0 <= nx2 && nx2 < n && 0 <= ny2 && ny2 < n && !map[nx2][ny2])
					return false;
			}
		}
	}
	return true;
}

int bfs() {
	memset(visit, 0, sizeof(visit));
	I = { 0,0,0,0 };
	q.push(I);
	visit[0][0] = 1;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int cnt = q.front().cnt;
		int flag = q.front().flag; q.pop();
		if (x == n - 1 && y == n - 1) return cnt;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 <= nx && nx < n && 0 <= ny && ny < n && !visit[nx][ny]) {
				if (map[nx][ny] == 1) {
					I = { nx,ny,cnt + 1,0 };
					q.push(I);
					visit[nx][ny] = 1;
				}
				else if (map[nx][ny] > 1 && !flag) {
					if ((cnt + 1) % map[nx][ny] == 0) {
						I = { nx,ny,cnt + 1,1 };
						q.push(I);
						visit[nx][ny] = 1;
					}
					else {  //시간이 안되서 다리를 못건너는 경우 기다리기
						I = { x,y,cnt + 1,0 };
						q.push(I);
					}
				}
			}
		}
	}
	return 987654321;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> map[i][j];
			if (!map[i][j])
				v.push_back(mp(i, j));
		}
	}
  int x, y;
	for (int i = 0; i < v.size(); ++i) {
		x = v[i].first;
		y = v[i].second;
		if (check(x, y)) {
			map[x][y] = m;
			result = min(result,bfs());
			map[x][y] = 0;
		}
	}
	cout << result;
}
