// https://www.acmicpc.net/problem/21609

// 2168KB , 4ms
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int cnt, rainbow_cnt, pibot_x, pibot_y, x, y;
}info;
info I;
vector<info> v;
vector<pair<int, int> > boom;
vector<int> temp2;
queue<pair<int, int> >q;
int map[21][21];
bool visit[21][21];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m;
int result = 0;
bool cmp(info a, info b) {
	if (a.cnt == b.cnt) {
		if (a.rainbow_cnt == b.rainbow_cnt) {
			if (a.pibot_x == b.pibot_x) return a.pibot_y < b.pibot_y;
			else return a.pibot_x < b.pibot_x;
		}
		else return a.rainbow_cnt < b.rainbow_cnt;
	}
	else return a.cnt < b.cnt;
}
void bfs(int sx, int sy, int flag) {
	while (!q.empty()) q.pop();
	memset(visit, 0, sizeof(visit));
	q.push(mp(sx, sy));
	visit[sx][sy] = 1;
	int cnt = 0, rainbow_cnt = 0, pibot_x = sx, pibot_y = sy;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		if (!flag) {
			++cnt;
			if (map[x][y] == 6) ++rainbow_cnt;
			else {
				if (x < pibot_x) {
					pibot_x = x;
					pibot_y = y;
				}
				else if (x == pibot_x && y < pibot_y)
					pibot_y = y;
			}
		}
		else boom.push_back(mp(x, y));
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
				if (map[nx][ny] == map[sx][sy] || map[nx][ny] == 6) {
					q.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
			}
		}
	}
	if (!flag && cnt > 1) {
		I = { cnt,rainbow_cnt,pibot_x,pibot_y,sx,sy };
		v.push_back(I);
	}
	else if (flag) {
		int len = boom.size();
		result += (len * len);
		for (int i = 0; i < len; ++i)
			map[boom[i].first][boom[i].second] = 0;
		boom.clear();
		v.clear();
	}
}
void down() {
	for (int i = n - 1; i > 0; --i) {
		for (int j = 1; j <= n; ++j) {
			if (map[i][j] > 0) {
				int x = i;
				int y = j;
				while (1) {
					int nx = x + 1;
					int ny = y;
					if (nx > n) break;
					if (!map[nx][ny]) {
						map[nx][ny] = map[x][y];
						map[x][y] = 0;
						x = nx;
						y = ny;
					}
					else break;
				}
			}
		}
	}
}
void turn() {
	for (int i = 1; i <= n; ++i)
		for (int j = n; j > 0; --j)
			temp2.push_back(map[i][j]);
	memset(map, 0, sizeof(map));
	int index = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			map[j][i] = temp2[index++];
	temp2.clear();
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> map[i][j];
			if (!map[i][j]) map[i][j] = 6;
		}
	}
	while (1) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (0 < map[i][j] && map[i][j] <= m)
					bfs(i, j, 0);
			}
		}
		if (!v.size()) break;
		sort(v.begin(), v.end(), cmp);
		bfs(v[v.size() - 1].x, v[v.size() - 1].y, 1);
		down();
		turn();
		down();
	}
	cout << result;
}

// 3352KB, 4ms
// #include<iostream>
// #include<vector>
// #include<algorithm>
// #include<queue>
// #include<cstring>
// #define mp make_pair
// using namespace std;
// vector< pair<pair<int, int >, pair<int,pair<int,vector<pair<int,int> > > > > > v; // 블럭의 수, 무지개블럭의 수, 기준블럭의 x좌표, 기준블럭의 y좌표, 모든 블럭의 좌표
// queue<pair<int, int> >q;
// int map[21][21];
// bool visit[21][21];
// int dx[4] = { 0,0,-1,1 };
// int dy[4] = { -1,1,0,0 };
// int n, m;
// int result = 0;
// void turn() {
// 	vector<int> temp;
// 	for (int i = n; i > 0; --i)
// 		for (int j = 1; j <= n; ++j)
// 			temp.push_back(map[j][i]);
// 	int index = 0;
// 	for (int i = 1; i <= n; ++i)
// 		for (int j = 1; j <= n; ++j)
// 			map[i][j] = temp[index++];
// }
// void down() {
// 	for (int i = 0; i < n; ++i) {
// 		for (int j = n; j > 1; --j) {
// 			for (int k = n; k > 0; --k) {
// 				if (map[j][k] == -2 && map[j - 1][k] > -1) {
// 					map[j][k] = map[j - 1][k];
// 					map[j - 1][k] = -2;
// 				}
// 			}
// 		}
// 	}
// }
// void bfs(int num, int sx, int sy) {
// 	memset(visit, 0, sizeof(visit));
// 	vector<pair<int, int> > temp;
// 	q.push(mp(sx, sy));
// 	visit[sx][sy] = 1;
// 	int x, y, nx, ny;
// 	int cnt = 0, rainbow = 0, stand_x = sx, stand_y = sy;
// 	while (!q.empty()) {
// 		x = q.front().first;
// 		y = q.front().second; q.pop();
// 		++cnt;
// 		temp.push_back(mp(x, y));
// 		if (map[x][y]) {
// 			if (x < stand_x) {
// 				stand_x = x;
// 				stand_y = y;
// 			}
// 			else if (x == stand_x) {
// 				if (y < stand_y)
// 					stand_y = y;
// 			}
// 		}
// 		for (int i = 0; i < 4; ++i) {
// 			nx = x + dx[i];
// 			ny = y + dy[i];
// 			if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
// 				if (!map[nx][ny] || map[nx][ny] == num) {
// 					q.push(mp(nx, ny));
// 					visit[nx][ny] = 1;
// 					if (!map[nx][ny]) ++rainbow;
// 				}
// 			}
// 		}
// 	}
// 	if (cnt > 1) 
// 		v.push_back(mp(mp(cnt, rainbow), mp(stand_x, mp(stand_y,temp))));
// }
// void start() {
// 	vector<pair<int, int> > temp;
// 	int len;
// 	while (1) {
// 		for (int i = 1; i <= n; ++i) 
// 			for (int j = 1; j <= n; ++j) 
// 				if (map[i][j] > 0) // 방문처리를 체크하면 틀림
// 					bfs(map[i][j], i, j);
// 		if (!v.size()) break;
// 		sort(v.begin(), v.end());
// 		len = v.size();
// 		temp = v[len - 1].second.second.second;
// 		for (int i = 0; i < temp.size(); ++i)
// 			map[temp[i].first][temp[i].second] = -2;
// 		result += (v[len - 1].first.first * v[len-1].first.first);
// 		down();
// 		turn();
// 		down();
// 		v.clear();
// 	}
// 	cout << result;
// }
// int main() {
// 	ios::sync_with_stdio(0); cin.tie(0);
// 	cin >> n >> m;
// 	for (int i = 1; i <= n; ++i)
// 		for (int j = 1; j <= n; ++j)
// 			cin >> map[i][j];
// 	start();
// }
