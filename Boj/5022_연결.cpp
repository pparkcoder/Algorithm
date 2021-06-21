// https://www.acmicpc.net/problem/5022

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y;
	vector<pair<int, int> >path;
}info;
info I;
int a_visit[101][101];
int b_visit[101][101];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int ax1, ay1, ax2, ay2, bx1, by1, bx2, by2, n, m, ans1, ans2;
int result = 987654321;
void a_bfs(vector<pair<int, int> >v, int check);
void b_bfs(vector<pair<int, int> >v, int check) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			b_visit[i][j] = -1;
	queue<info> q;
	vector<pair<int, int> >path, ans;
	int x, y, nx, ny, stop;
	path.push_back(mp(bx1, by1));
	I = { bx1,by1,path };
	q.push(I);
	ans2 = b_visit[bx1][by1] = 0;
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		path = q.front().path; q.pop();
		if (x == bx2 && y == by2) {
			ans2 = b_visit[x][y];
			ans = path;
			break;
		}
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			stop = 0;
			if (0 <= nx && nx <= n && 0 <= ny && ny <= m && b_visit[nx][ny] == -1) {
				if (!check) {
					for (int j = 0; j < v.size(); j++) {
						if (nx == v[j].first && ny == v[j].second) {
							stop = 1;
							break;
						}
					}
				}
				if (stop) continue;
				if (!(nx == ax1 && ny == ay1) && !(nx == ax2 && ny == ay2)) {
					vector<pair<int, int> >temp;
					temp = path;
					temp.push_back(mp(nx, ny));
					I = { nx,ny,temp };
					q.push(I);
					b_visit[nx][ny] = b_visit[x][y] + 1;
				}
			}
		}
	}
	if (b_visit[bx2][by2] != -1) {
		if (check) a_bfs(ans, 1);
		else result = min(result, ans1 + ans2);
	}
	return;
}
void a_bfs(vector<pair<int, int> >v, int check) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			a_visit[i][j] = -1;
	queue<info> q;
	vector<pair<int, int> >path, ans;
	int x, y, nx, ny, stop;
	path.push_back(mp(ax1, ay1));
	I = { ax1,ay1,path };
	q.push(I);
	ans1 = a_visit[ax1][ay1] = 0;
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		path = q.front().path; q.pop();
		if (x == ax2 && y == ay2) {
			ans1 = a_visit[x][y];
			ans = path;
			break;
		}
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			stop = 0;
			if (0 <= nx && nx <= n && 0 <= ny && ny <= m && a_visit[nx][ny] == -1) {
				if (check) {
					for (int j = 0; j < v.size(); j++) {
						if (nx == v[j].first && ny == v[j].second) {
							stop = 1;
							break;
						}
					}
				}
				if (stop) continue;
				if (!(nx == bx1 && ny == by1) && !(nx == bx2 && ny == by2)) {
					vector<pair<int, int> >temp;
					temp = path;
					temp.push_back(mp(nx, ny));
					I = { nx,ny,temp };
					q.push(I);
					a_visit[nx][ny] = a_visit[x][y] + 1;
				}
			}
		}
	}
	if (a_visit[ax2][ay2] != -1) {
		if (!check) b_bfs(ans, 0);
		else result = min(result, ans1 + ans2);
	}
	return;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	cin >> ay1 >> ax1 >> ay2 >> ax2;
	cin >> by1 >> bx1 >> by2 >> bx2;
	vector<pair<int, int> >v;
	a_bfs(v, 0);
	b_bfs(v, 1);
	result == 987654321 ? cout << "IMPOSSIBLE" : cout << result;
}
