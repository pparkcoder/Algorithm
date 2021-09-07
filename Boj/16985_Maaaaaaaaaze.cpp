// https://www.acmicpc.net/problem/16985

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int h, x, y;
}info;
info I;
vector<pair<int, int> >v;
queue<info> q;
int map[6][6][6];
int cmap[6][6][6];
int visit[6][6][6];
int check[6];
int dh[6] = { -1,1,0,0,0,0 };
int dx[6] = { 0,0,0,0,-1,1 };
int dy[6] = { 0,0,-1,1,0,0 };
int result = 987654321;
void bfs() {
	memset(visit, 0, sizeof(visit));
	while (!q.empty()) q.pop();
	I = { 1,1,1 };
	q.push(I);
	visit[1][1][1] = 1;
	while (!q.empty()) {
		int h = q.front().h;
		int x = q.front().x;
		int y = q.front().y; q.pop();
		if (h == 5 && x == 5 && y == 5) {
			result = min(result, visit[h][x][y] - 1);
			return;
		}
		for (int i = 0; i < 6; i++) {
			int nh = h + dh[i];
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nh && nh < 6 && 0 < nx && nx < 6 && 0 < ny && ny < 6 && cmap[nh][nx][ny] && !visit[nh][nx][ny]) {
				I = { nh,nx,ny };
				q.push(I);
				visit[nh][nx][ny] = visit[h][x][y] + 1;
			}
		}
	}
}
void turn() {
	vector<int> temp;
	int num, cnt, index;
	for (int l = 0; l < v.size(); l++) {
		num = v[l].first;
		cnt = v[l].second;
		index = 0;
		for (int j = 1; j < 6; j++)
			for (int k = 1; k < 6; k++)
				temp.push_back(map[num][j][k]);
		if (cnt == 0) {
			for (int j = 1; j < 6; j++)
				for (int k = 1; k < 6; k++)
					cmap[l + 1][j][k] = temp[index++];
		}
		else if (cnt == 1) {
			for (int j = 5; j > 0; j--)
				for (int k = 1; k < 6; k++)
					cmap[l + 1][k][j] = temp[index++];
		}
		else if (cnt == 2) {
			for (int j = 5; j > 0; j--)
				for (int k = 5; k > 0; k--)
					cmap[l + 1][j][k] = temp[index++];
		}
		else {
			for (int j = 1; j < 6; j++)
				for (int k = 5; k > 0; k--)
					cmap[l + 1][k][j] = temp[index++];
		}
		temp.clear();
	}
}
void dfs(int cnt) {
	if (cnt == 6) {
		turn();
		if(cmap[1][1][1] && cmap[5][5][5]) bfs();
		return;
	}
	for (int i = 1; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (!check[i]) {
				check[i] = 1;
				v.push_back(mp(i, j));
				dfs(cnt + 1);
				v.pop_back();
				check[i] = 0;
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	for (int i = 1; i < 6; i++)
		for (int j = 1; j < 6; j++)
			for (int k = 1; k < 6; k++)
				cin >> map[i][j][k];
	dfs(1);
	cout << (result == 987654321 ? -1 : result);
}
