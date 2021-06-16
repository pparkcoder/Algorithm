// https://www.acmicpc.net/problem/18809

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, color;
}info;
info I;
queue<info> q;
vector<info> v;
vector<pair<int, int> > v2;
int map[51][51];
pair<int, int> cmap[51][51];
bool visit[51][51];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, g, r;
int result = -987654321;
void bfs() {
	int cnt = 0;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int color = q.front().color; q.pop();
		if (cmap[x][y].first == 3) continue;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m && map[nx][ny]) {
				if (!cmap[nx][ny].first) {
					I = { nx,ny,color };
					q.push(I);
					cmap[nx][ny].first = color;
					cmap[nx][ny].second = cmap[x][y].second + 1;
				}
				else if ((color == 1 && cmap[nx][ny].first == 2) || (color == 2 && cmap[nx][ny].first == 1)) {
					if (cmap[nx][ny].second == cmap[x][y].second + 1) {
						++cnt;
						cmap[nx][ny].first = 3;
					}
				}
			}
		}
	}
	result = max(result, cnt);
	return;
}
void brute(int g_cnt, int r_cnt, int index, int color) {
	if (r_cnt == r) {
		memset(cmap, 0, sizeof(cmap));
		for (int i = 0; i < v.size(); i++) {
			I = { v[i].x,v[i].y,v[i].color }; q.push(I);
			cmap[v[i].x][v[i].y].first = v[i].color;
		}
		bfs();
		return;
	}
	if (color == 1 && g_cnt == g) {
		color = 2;
		index = 0;
	}
	for (int i = index; i < v2.size(); i++) {
		int x = v2[i].first;
		int y = v2[i].second;
		if (!visit[x][y]) {
			visit[x][y] = 1;
			I = { x,y,color }; v.push_back(I);
			if (color == 1) brute(g_cnt + 1, r_cnt, i + 1, color);
			else brute(g_cnt, r_cnt + 1, i + 1, color);
			v.pop_back();
			visit[x][y] = 0;
		}
	}
}

/*---------- TLE code ----------*/
//void brute(int g_cnt, int r_cnt, int index, int color) {
//	if (!g_cnt && !r_cnt) {
//		memset(cmap, 0, sizeof(cmap));
//		for (int i = 0; i < v.size(); ++i) {
//			int x = v[i].x;
//			int y = v[i].y;
//			int c = v[i].color;
//			I = { x,y,c };
//			q.push(I);
//			cmap[x][y].first = c;
//		}
//		bfs();
//		return;
//	}
//	if (!g_cnt) index = 0, color = 2;
//	for (int i = index; i < v2.size(); ++i) {
//		int x = v2[i].first;
//		int y = v2[i].second;
//		if (!visit[x][y]) {
//			I = { x,y,color };
//			v.push_back(I);
//			visit[x][y] = 1;
//			if (g_cnt) brute(g_cnt - 1, r_cnt, i + 1, color);
//			else brute(g_cnt, r_cnt - 1, i + 1, color);
//			visit[x][y] = 0;
//			v.pop_back();
//		}
//	}
//}
/*---------- TLE code ----------*/
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> g >> r;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 2) v2.push_back(mp(i, j));
		}
	}
	brute(0, 0, 0, 1);
	cout << result;
}
