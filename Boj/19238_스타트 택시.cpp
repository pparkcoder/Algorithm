//https://www.acmicpc.net/problem/19238
// Tip -> 손님을 태운 후, 목적지 까지 가는 경로가 없을수도 있음

#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int start_x, start_y, dest_x, dest_y;
}info;
info I;
vector<info> v;
vector<pair<pair<int, int>, pair<int, int> > > temp;
queue<pair<int, int> > q;
int map[21][21];
int visit[21][21];
bool check[401];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, fuel, start_x, start_y, dest_x, dest_y;
int sx, sy;
bool func() {
	for (int i = 1; i <= m; ++i)
		if (!check[i]) return false;
	return true;
}
pair<int, int> bfs(int taxi_x, int taxi_y, int flag, int num) {
	while (!q.empty()) q.pop();
	memset(visit, -1, sizeof(visit));
	temp.clear();
	q.push(mp(taxi_x, taxi_y));
	visit[taxi_x][taxi_y] = 0;
	if (map[taxi_x][taxi_y]) return mp(0, map[taxi_x][taxi_y]);
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		if (flag && x == v[num].dest_x && y == v[num].dest_y) return mp(visit[x][y], num);
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny] != -1 && visit[nx][ny] == -1) {
				q.push(mp(nx, ny));
				visit[nx][ny] = visit[x][y] + 1;
				if (map[nx][ny]) temp.push_back(mp(mp(visit[nx][ny], nx), mp(ny, map[nx][ny])));
			}
		}
	}
	if (flag || !temp.size()) return mp(-1, -1);
	sort(temp.begin(), temp.end());
	return mp(temp.front().first.first, temp.front().second.second);
}
int start() {
	while (1) {
		if (func()) return fuel;
		pair<int, int> result = bfs(sx, sy, 0, 0);
		int len = result.first;
		int num = result.second;
		if (len == -1 || fuel - len < 0) return -1;
		//태우기
		fuel -= len;
		map[v[num].start_x][v[num].start_y] = 0;
		pair<int, int> result2 = bfs(v[num].start_x, v[num].start_y, 1, num);
		int len2 = result2.first;
		if (len2 == -1 || fuel - len2 < 0) return -1;
		//내리기
		fuel -= len2;
		fuel += (len2 * 2);
		sx = v[num].dest_x;
		sy = v[num].dest_y;
		check[num] = 1;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> fuel;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> map[i][j];
			if (map[i][j]) map[i][j] = -1;
		}
	}
	cin >> sx >> sy;
	I = { -1,-1,-1,-1 };
	v.push_back(I);
	for (int i = 1; i <= m; ++i) {
		cin >> start_x >> start_y >> dest_x >> dest_y;
		I = { start_x,start_y,dest_x,dest_y };
		v.push_back(I);
		map[start_x][start_y] = i;
	}
	cout << start();
}
