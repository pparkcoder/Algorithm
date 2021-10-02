// https://www.acmicpc.net/problem/10711

#include<iostream>
#include<queue>
#define mp make_pair
using namespace std;
queue<pair<int, int> > q;
char map[1001][1001];
int check[1001][1001];
bool visit[1001][1001];
int dx[8] = { -1,-1,-1,0,1,1,1,0 };
int dy[8] = { -1,0,1,1,1,0,-1,-1 };
int h, w;
int bfs() {
	int pool = 0;
	while (1) {
		vector<pair<int, int> > v;
		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second; q.pop();
			for (int i = 0; i < 8; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (0 < nx && nx <= h && 0 < ny && ny <= w) {
					if (!visit[nx][ny] && '1' <= map[nx][ny] && map[nx][ny] <= '8') {
						++check[nx][ny];
						if (check[nx][ny] >= map[nx][ny] - '0') {
							v.push_back(mp(nx, ny));
							visit[nx][ny] = 1;
						}
					}
				}
			}
		}
		if (!v.size()) return pool;
		for (int i = 0; i < v.size(); i++)
			q.push(mp(v[i].first, v[i].second));
		++pool;
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> h >> w;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> map[i][j];
			if (map[i][j] == '9') 
                visit[i][j] = 1;
			else if (map[i][j] == '.') {
				q.push(mp(i, j));
				visit[i][j] = 1;
			}
		}
	}
	cout << bfs();
}
