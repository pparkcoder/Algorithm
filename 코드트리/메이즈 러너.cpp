// https://www.codetree.ai/training-field/frequent-problems/problems/maze-runner/description?page=1&pageSize=20
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, life;
}info;
info I;
int map[11][11], visit[11][11];
vector<int> now[11][11];
vector<info>v;
queue<pair<int, int> >q;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int n, m, k, dest_x, dest_y;
int result = 0, people = 0;
void turn(int x, int y, int len) {
	vector<pair<pair<int,vector<int> >,pair<int,int> > >  temp;
	int index = 0, flag = 0;
	for (int i = x; i < x + len; ++i) {
		for (int j = y; j < y + len; ++j) {
			vector<int> temp2;
			for (int l = 0; l < now[i][j].size(); ++l) temp2.push_back(now[i][j][l]);
			temp.push_back(mp(mp(map[i][j], temp2), mp(i, j)));
			map[i][j] = 0;
			
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			now[i][j].clear();
	for (int i = y + len - 1; i >= y; --i) {
		for (int j = x; j < x + len; ++j) {
			map[j][i] = temp[index].first.first;
			vector<int> temp2 = temp[index].first.second;
			int tx = temp[index].second.first;
			int ty = temp[index].second.second;
			if (map[j][i] && --map[j][i] == 0) map[j][i] = 0;
			if (tx == dest_x && ty == dest_y && !flag) {
				dest_x = j;
				dest_y = i;
				flag = 1;
			}
			if (temp2.size()) {
				for (int l = 0; l < temp2.size(); ++l) {
					//now[j][i].push_back(temp2[l]);
					v[temp2[l] - 1].x = j;
					v[temp2[l] - 1].y = i;
				}
			}
			++index;
		}
	}
}
void find() {
	int len = 2, flag = 0;
	while (1) {
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < n; ++j) {
				int sx = i;
				int sy = j;
				int flag1 = 0;
				int flag2 = 0;
				if (1 > sx + len - 1 || sx + len - 1 > n || 1 > sy + len - 1 || sy + len - 1 > n) continue;
				else {
					for (int a = sx; a < sx + len; ++a) {
						for (int b = sy; b < sy + len; ++b) {
							if (a == dest_x && b == dest_y) flag1 = 1;
							if (now[a][b].size()) flag2 = 1;
							if (flag1 && flag2) {
								flag = 1;
								break;
							}
						}
						if (flag) break;
					}
					if (flag) {
						turn(sx, sy, len);
						break;
					}
				}
			}
			if (flag) break;
		}
		if (flag) break;
		++len;
	}
}
void move() {
	for (int i = 0; i < v.size(); ++i) {
		if (!v[i].life) continue;
		int x = v[i].x;
		int y = v[i].y;
		int flag = 0;
		vector < pair<pair<int,int>, pair<int, int> > >temp;
		for (int j = 0; j < 4; ++j) {
			int nx = x + dx[j];
			int ny = y + dy[j];
			if (0 < nx && nx <= n && 0 < ny && ny <= n) {
				temp.push_back(mp(mp(visit[nx][ny],j), mp(nx, ny)));
			}
		}
		sort(temp.begin(), temp.end());
		int nx = temp[0].second.first;
		int ny = temp[0].second.second;
		int min_num = temp[0].first.first;
		for (int j = 0; j < temp.size(); ++j) {
			int tx = temp[j].second.first;
			int ty = temp[j].second.second;
			if (visit[tx][ty] == min_num) {
				if (!map[tx][ty]) {
					++result;
					if (tx == dest_x && ty == dest_y) {
						v[i].life = 0;
						--people;
					}
					else {
						v[i].x = tx;
						v[i].y = ty;
						now[tx][ty].push_back(i + 1);
					}
					flag = 1;
					break;
				}
			}
			else break;
		}
		if(!flag) now[x][y].push_back(i + 1);
	}
}
void bfs() {
	memset(visit, 0, sizeof(visit));
	q.push(mp(dest_x, dest_y));
	visit[dest_x][dest_y] = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
				q.push(mp(nx, ny));
				visit[nx][ny] = visit[x][y] + 1;
			}
		}
	}
}
void start() {
	people = m;
	for (int i = 0; i < k; ++i) {
		bfs();
		move();
		if (people < 1) break;
		find();
	}
	cout << result << "\n" << dest_x << " " << dest_y;
}
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	for (int i = 0; i < m; ++i) {
		cin >> dest_x >> dest_y;
		I = { dest_x,dest_y,1 };
		v.push_back(I);
	}
	cin >> dest_x >> dest_y;
	start();
}
