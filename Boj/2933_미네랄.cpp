// Solving -> bfs수행시 x == r 이면 바로 return 금지 -> 같은 그룹이여도 방문처리가 안되고 return 될 수 있기에 -> 끝에 도달했다는 변수 지정 필요(stop)
// Tip -> 미네랄이 내려가고 나서 내려간 미네랄도 방문처리 필요!
// https://www.acmicpc.net/problem/2933

#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#define mp make_pair
using namespace std;
queue<pair<int, int> >q;
vector<pair<int, int> > temp;
vector<int> v;
char map[101][101];
bool visit[101][101];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int r, c, h, n;
void show() {
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j)
			cout << map[i][j];
		cout << "\n";
	}
}
void bfs(int sx, int sy) {
	while (!q.empty()) q.pop();
	temp.clear();
	int x, y, nx, ny, len, index, stop;
	q.push(mp(sx, sy));
	stop = visit[sx][sy] = 1;
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second; q.pop();
		temp.push_back(mp(x, y));
	 	//if (x == r) return;
		if (x == r) stop = 0; 
		for (int i = 0; i < 4; ++i) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= r && 0 < ny && ny <= c && map[nx][ny] == 'x' && !visit[nx][ny]) {
				q.push(mp(nx, ny));
				visit[nx][ny] = 1;
			}
		}
	}
	if (!stop) return;
	for (int i = 0; i < temp.size(); ++i) {
		x = temp[i].first;
		y = temp[i].second;
		map[x][y] = '.';
		visit[x][y] = 0;
	}
	len = 987654321, index = 0;
	for (int i = 0; i < temp.size(); ++i) {
		x = temp[i].first;
		y = temp[i].second;
		for (int j = 1;; ++j) {
			nx = x + j;
			if (nx > r || map[nx][y] == 'x') break;
			index = j;
		}
		len = min(len, index);
	}
	for (int i = 0; i < temp.size(); ++i) {
		x = temp[i].first;
		y = temp[i].second;
		map[x+len][y] = 'x';
		visit[x + len][y] = 1;
	}
}
void start() {
	bool flag = 0;
	for (int i = 0; i < n; ++i) {
		h = v[i];	
		if (!flag) {	// 왼쪽
			for (int j = 1; j <= c; ++j) {
				if (map[h][j] == 'x') {
					map[h][j] = '.';
					break;
				}
			}
		}	
		else {	// 
			for (int j = c; j > 0; --j) {
				if (map[h][j] == 'x') {
					map[h][j] = '.';
					break;
				}
			}
		}
		for (int j = 1; j <= r; ++j) {
			for (int k = 1; k <= c; ++k) {
				if (map[j][k] == 'x' && !visit[j][k]) {
					bfs(j, k);
				}
			}
		}
		flag = !flag;
		memset(visit, 0, sizeof(visit));
	}
	show();
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> r >> c;
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j)
			cin >> map[i][j];
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> h;
		v.push_back(r + 1 - h);
	}
	start();
}
