// https://www.acmicpc.net/problem/1938

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef struct {
	int x1, x2, x3, Y1, y2, y3, dir, cnt;
}info;
info I;
queue<info>q;
vector<pair<int, int> >v;
char map[51][51];
int visit[51][51][2];	//0 가로방향 , 1 세로방향
int dx[8] = { -1,1,0,0,-1,-1,1,1 };
int dy[8] = { 0,0,-1,1,-1,1,-1,1 };
int x1, x2, x3, Y1, y2, y3, dir, n;
bool safe(int a, int b, int d) {
	if (!visit[a][b][d]) {
		visit[a][b][d] = 1;
		return true;
	}
	return false;
}
bool find(int a1, int a2, int a3, int b1, int b2, int b3) {
	if (map[a1][b1] == 'E' && map[a2][b2] == 'E' && map[a3][b3] == 'E') return true;
	return false;
}
int bfs() {
	int nx1, nx2, nx3, nY1, ny2, ny3, cnt;
	while (!q.empty()) {
		x1 = q.front().x1; Y1 = q.front().Y1;
		x2 = q.front().x2; y2 = q.front().y2;
		x3 = q.front().x3; y3 = q.front().y3;
		dir = q.front().dir;
		cnt = q.front().cnt; q.pop();
		//cout << x1 << "," << Y1 << " / " << x2 << "," << y2 << " / " << x3 << "," << y3 << " / " << dir << "\n";
		if (find(x1, x2, x3, Y1, y2, y3)) return cnt;
		for (int i = 0; i < 4; i++) {
			nx1 = x1 + dx[i], nY1 = Y1 + dy[i];
			nx2 = x2 + dx[i], ny2 = y2 + dy[i];
			nx3 = x3 + dx[i], ny3 = y3 + dy[i];
			if (0 < nx1 && nx1 <= n && 0 < nx2 && nx2 <= n && 0 < nx3 && nx3 <= n) {
				if (0 < nY1 && nY1 <= n && 0 < ny2 && ny2 <= n && 0 < ny3 && ny3 <= n) {
					if (dir) {
						if (i == 0 && map[nx1][nY1] != '1' && safe(nx2, ny2, dir)) {
							I = { nx1,nx2,nx3,nY1,ny2,ny3,dir,cnt + 1 };
							q.push(I);
						}
						if (i == 1 && map[nx3][ny3] != '1' && safe(nx2, ny2, dir)) {
							I = { nx1,nx2,nx3,nY1,ny2,ny3,dir,cnt + 1 };
							q.push(I);
						}
						if ((i == 2 || i == 3) && map[nx1][nY1] != '1' && map[nx2][ny2] != '1' && map[nx3][ny3] != '1' && safe(nx2, ny2, dir)) {
							I = { nx1,nx2,nx3,nY1,ny2,ny3,dir,cnt + 1 };
							q.push(I);
						}
					}
					else {
						if (i == 2 && map[nx1][nY1] != '1' && safe(nx2, ny2, dir)) {
							I = { nx1,nx2,nx3,nY1,ny2,ny3,dir,cnt + 1 };
							q.push(I);
						}
						if (i == 3 && map[nx3][ny3] != '1' && safe(nx2, ny2, dir)) {
							I = { nx1,nx2,nx3,nY1,ny2,ny3,dir,cnt + 1 };
							q.push(I);
						}
						if ((i == 0 || i == 1) && map[nx1][nY1] != '1'&& map[nx2][ny2] != '1'&& map[nx3][ny3] != '1' && safe(nx2, ny2, dir)) {
							I = { nx1,nx2,nx3,nY1,ny2,ny3,dir,cnt + 1 };
							q.push(I);
						}
					}
				}
			}
		}
		int flag = 0;
		for (int i = 0; i < 8; i++) {
			if (map[x2 + dx[i]][y2 + dy[i]] == '1' || 1 > x2 + dx[i] || x2 + dx[i] > n || 1 > y2 + dy[i] || y2 + dy[i] > n) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			if (!dir) {
				if (safe(x2, y2, 1 - dir)) {
					I = { x1 - 1, x2, x3 + 1, Y1 + 1, y2, y3 - 1,1 - dir,cnt + 1 };
					q.push(I);
				}
			}
			else {
				if (safe(x2, y2, 1 - dir)) {
					I = { x1 + 1, x2, x3 - 1, Y1 - 1, y2, y3 + 1,1 - dir,cnt + 1 };
					q.push(I);
				}
			}
		}
	}
	return 0;
}
int main() {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'B')
				v.push_back(make_pair(i, j));
		}
	}
	x1 = v[0].first; Y1 = v[0].second;
	x2 = v[1].first; y2 = v[1].second;
	x3 = v[2].first; y3 = v[2].second;
	v.clear();
	if (x1 == x2) dir = 0;
	else dir = 1;
	I = { x1,x2,x3,Y1,y2,y3,dir,0 };
	q.push(I);
	visit[x2][y2][dir] = 1;
	cout << bfs();
}
