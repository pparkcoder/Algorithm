//https://www.acmicpc.net/problem/19238
// Tip -> 손님을 태운 후, 목적지 까지 가는 경로가 막혀 있을수도 있음 -> v.size()

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;
vector<pair<pair<int, int>, pair<int, int> > > info;
vector<pair<int, pair<int, int> > > v; // 거리, 행, 열
queue<pair<int, int> >q;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[21][21], visit[21][21];
int n, m, sx, sy, fuel, use_fuel, passenger_num;
void init() {
	while (!q.empty()) q.pop();
	memset(visit, 0, sizeof(visit));
	v.clear();
}
bool bfs(int tx, int ty, int flag) { // 0 : 태우기, 1 : 내리기
	init();
	q.push(mp(tx, ty));
	visit[tx][ty] = 1;
	int x, y, nx, ny;
	if (!flag && map[tx][ty] > 1) v.push_back(mp(1, mp(tx, ty))); // 출발지에 승객이 있는 경우 바로 태우기
	else {
		while (!q.empty()) {
			x = q.front().first;
			y = q.front().second; q.pop();
			if (flag && x == info[passenger_num].second.first && y == info[passenger_num].second.second) {
				v.push_back(mp(visit[x][y], mp(x, y)));
				break;
			}
			for (int i = 0; i < 4; ++i) {
				nx = x + dx[i];
				ny = y + dy[i];
				if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny] && map[nx][ny] != 1) {
					q.push(mp(nx, ny));
					visit[nx][ny] = visit[x][y] + 1;
					if (!flag && map[nx][ny] > 1) v.push_back(mp(visit[nx][ny], mp(nx, ny)));
				}
			}
		}
	}
	if (!v.size()) return 0; // 택시가 갈 수 있는 곳이 없는 경우
	if (!flag) sort(v.begin(), v.end());
	use_fuel = visit[v[0].second.first][v[0].second.second] - 1;
	if (fuel - use_fuel < 0) return 0;
	else {
		fuel -= use_fuel;
		sx = v[0].second.first;
		sy = v[0].second.second;
		if (!flag) {
			passenger_num = map[sx][sy] - 2; // 승객번호는 2부터 시작
			map[sx][sy] = 0;
		}
		else fuel += (use_fuel * 2); 
		return 1;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int x, y, dx, dy;
	int num = 2;
	cin >> n >> m >> fuel;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	cin >> sx >> sy;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> dx >> dy;
		map[x][y] = num++;
		info.push_back(mp(mp(x, y), mp(dx, dy)));
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (!bfs(sx, sy, j)) {
				fuel = -1;
				break;
			}
		}
		if (fuel == -1) break;
	}
	cout << fuel;
}
