// https://www.acmicpc.net/problem/23290
// Tip -> 상어가 갈 수 있는 길은 중복조합 가능 
// **만약 재 방문한 곳에 물고기 있었다면 그곳을 재 방문하였을 시 물고기는 없음 처리가 중요**

#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, dir;
}info;
info I;
vector<info> v, v2;
vector<pair<int, int> >temp;
vector<int>map[5][5];
int dx[9] = { 0, 0,-1,-1,-1,0,1,1,1 };
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dx2[5] = { 0,-1,0,1,0 };
int dy2[5] = { 0,0,-1,0,1 };
int smell[5][5];
bool visit[5][5];
int m, s, sx, sy;
bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first) return a.second > b.second;
	else return a.first < b.first;
}
void dfs(int cnt, string dir, int depth, int x, int y) {
	if (depth == 3) {
		temp.push_back(mp(cnt, stoi(dir)));
		return;
	}
	string s = dir;
	for (int i = 1; i < 5; ++i) {
		int nx = x + dx2[i];
		int ny = y + dy2[i];
		if (0 < nx && nx <= 4 && 0 < ny && ny <= 4) {
			if (!visit[nx][ny]) { // 방문하지 않은 경우
				visit[nx][ny] = 1;
				dfs(cnt + map[nx][ny].size(), s + to_string(i), depth + 1, nx, ny); // 물고기가 있다면 그 수만큼 넘기기
				visit[nx][ny] = 0;
			}
			else dfs(cnt, s + to_string(i), depth + 1, nx, ny);	// 재 방문하였다면, 물고기는 없음 처리
		}
	}
}
void eat(int dir) {
	string ndir = to_string(dir);
	for (int i = 0; i < 3; ++i) {
		int nx = sx + dx2[ndir[i] - '0'];
		int ny = sy + dy2[ndir[i] - '0'];
		if(map[nx][ny].size()) smell[nx][ny] = 3;
		map[nx][ny].clear();
		sx = nx;
		sy = ny;
	}
	temp.clear();
}
void copy() {
	for (int i = 0; i < v.size(); ++i) {
		int x = v[i].x;
		int y = v[i].y;
		int dir = v[i].dir;
		map[x][y].push_back(dir);
	}
	v.clear();
	v2.clear();
	int len;
	for (int i = 1; i < 5; ++i) {
		for (int j = 1; j < 5; ++j) {
			len = map[i][j].size();
			if (len) {
				for (int k = 0; k < len; ++k) {
					I = { i,j,map[i][j][k] };
					v.push_back(I);
				}
				map[i][j].clear();
			}
		}
	}
}
void smell_down() {
	for (int i = 1; i < 5; ++i)
		for (int j = 1; j < 5; ++j)
			if (smell[i][j]) --smell[i][j];
}
void start() {
	while (s--) {
		v2 = v;
		for (int i = 0; i < v2.size(); ++i) {
			int x = v2[i].x;
			int y = v2[i].y;
			int dir = v2[i].dir;
			int ndir = dir;
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			int flag = 0;
			if (1 > nx || nx > 4 || 1 > ny || ny > 4 || (sx == nx && sy == ny) || smell[nx][ny]) {
				while (1) {
					if (--dir < 1) dir = 8;
					if (ndir == dir) break;
					nx = x + dx[dir];
					ny = y + dy[dir];
					if (0 < nx && nx <= 4 && 0 < ny && ny <= 4 && !(nx == sx && ny == sy) && !smell[nx][ny]) {
						flag = 1;
						break;
					}
				}
				if (!flag) {
					nx = x;
					ny = y;
					dir = ndir;
				}
			}
			v2[i].x = nx;
			v2[i].y = ny;
			v2[i].dir = dir;
			map[nx][ny].push_back(dir);
		}
		dfs(0, "", 0, sx, sy);
		sort(temp.begin(), temp.end(),cmp);
		eat(temp[temp.size() - 1].second);
		smell_down();
		copy();
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> m >> s;
	int x, y, dir;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> dir;
		I = { x,y,dir };
		v.push_back(I);
	}
	cin >> sx >> sy;
	start();
	cout << v.size();
}
