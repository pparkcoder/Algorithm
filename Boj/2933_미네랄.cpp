// https://www.acmicpc.net/problem/2933

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
char map[101][101];
int visit[101][101];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
queue<pair<int, int> >q;
vector<pair<int, int> >v;
int r, c, n, order, min_num;
void init() {
	while (!q.empty()) q.pop();
	v.clear();
	memset(visit, 0, sizeof(visit));
	min_num = 987654321;
}
void bfs(int sx, int sy) {
	init();
	q.push(make_pair(sx, sy));
	visit[sx][sy] = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		if (x == r) return;
		v.push_back(make_pair(x, y));
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= r && 0 < ny && ny <= c && map[nx][ny] == 'x' && !visit[nx][ny]) {
				q.push(make_pair(nx, ny));
				visit[nx][ny] = 1;
			}
		}
	}
	for (int i = 0; i < v.size(); i++)
		map[v[i].first][v[i].second] = '.';
	for (int i = 0; i < v.size(); i++) {
		int x = v[i].first;
		int y = v[i].second;
		int len = 0;
		for (int j = 1;; j++) {
			if (map[x + j][y] == 'x' || x + j > r) {
				break;
			}
			++len;
		}
		min_num = min(min_num, len);
	}
	for (int i = 0; i < v.size(); i++) {
		int x = v[i].first + min_num;
		int y = v[i].second;
		map[x][y] = 'x';
	}
}

void start(int num, int turn) {
	int x, y, flag;
	flag = 0;
	if (turn % 2) { 
		for (int i = 1; i <= c; i++) {
			if (map[num][i] == 'x') {
				map[num][i] = '.';
				x = num, y = i;
				flag = 1;
				break;
			}
		}
	}
	else { 
		for (int i = c; i > 0; i--) {
			if (map[num][i] == 'x') {
				map[num][i] = '.';
				x = num, y = i;
				flag = 1;
				break;
			}
		}
	}
	if (flag) {
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= r && 0 < ny && ny <= c && map[nx][ny] == 'x')
				bfs(nx, ny);
		}
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> r >> c;
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			cin >> map[i][j];
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> order;
		start(r + 1 - order, i);
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++)
			cout << map[i][j];
		cout << "\n";
	}
}
