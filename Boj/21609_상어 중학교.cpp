// https://www.acmicpc.net/problem/21609

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#define mp make_pair
using namespace std;
vector< pair<pair<int, int >, pair<int,pair<int,vector<pair<int,int> > > > > > v; // 블럭의 수, 무지개블럭의 수, 기준블럭의 x좌표, 기준블럭의 y좌표, 모든 블럭의 좌표
queue<pair<int, int> >q;
int map[21][21];
bool visit[21][21];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m;
int result = 0;
void turn() {
	vector<int> temp;
	for (int i = n; i > 0; --i)
		for (int j = 1; j <= n; ++j)
			temp.push_back(map[j][i]);
	int index = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			map[i][j] = temp[index++];
}
void down() {
	for (int i = 0; i < n; ++i) {
		for (int j = n; j > 1; --j) {
			for (int k = n; k > 0; --k) {
				if (map[j][k] == -2 && map[j - 1][k] > -1) {
					map[j][k] = map[j - 1][k];
					map[j - 1][k] = -2;
				}
			}
		}
	}
}
void bfs(int num, int sx, int sy) {
	memset(visit, 0, sizeof(visit));
	vector<pair<int, int> > temp;
	q.push(mp(sx, sy));
	visit[sx][sy] = 1;
	int x, y, nx, ny;
	int cnt = 0, rainbow = 0, stand_x = sx, stand_y = sy;
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second; q.pop();
		++cnt;
		temp.push_back(mp(x, y));
		if (map[x][y]) {
			if (x < stand_x) {
				stand_x = x;
				stand_y = y;
			}
			else if (x == stand_x) {
				if (y < stand_y)
					stand_y = y;
			}
		}
		for (int i = 0; i < 4; ++i) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
				if (!map[nx][ny] || map[nx][ny] == num) {
					q.push(mp(nx, ny));
					visit[nx][ny] = 1;
					if (!map[nx][ny]) ++rainbow;
				}
			}
		}
	}
	if (cnt > 1) 
		v.push_back(mp(mp(cnt, rainbow), mp(stand_x, mp(stand_y,temp))));
}
void start() {
	vector<pair<int, int> > temp;
	int len;
	while (1) {
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) 
				if (map[i][j] > 0) // 방문처리를 체크하면 틀림
					bfs(map[i][j], i, j);
		if (!v.size()) break;
		sort(v.begin(), v.end());
		len = v.size();
		temp = v[len - 1].second.second.second;
		for (int i = 0; i < temp.size(); ++i)
			map[temp[i].first][temp[i].second] = -2;
		result += (v[len - 1].first.first * v[len-1].first.first);
		down();
		turn();
		down();
		v.clear();
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	start();
}
