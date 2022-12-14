// https://www.codetree.ai/training-field/frequent-problems/codetree-mon-bread/description?page=3&pageSize=20
// 각 '번호'마다 bfs를 이용해 시작 베이스 캠프 위치 찾기 + 편의점으로부터 모든 거리 구하기
// 베이스 캠프 위치에서 시작, 최단거리는 기존에 이용했던 거리를 사용
// 상 좌 우 하 를 보면서 현재 나보다 작은 값으로 이동(line 64) -> 이동한 점에서 계속 bfs를 할 필요x
// 베이스 캠프 출발, 편의점 도착 시 -1 처리

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, num, life;
}info;
info I;
vector<info> v;
vector<pair<int, int> > dest;
queue < pair<int, int> > q;
int dest_check[16][16][31]; // 사람 번호에 따른 거리
int map[16][16];
int dx[4] = { -1,0,0,1 };
int dy[4] = { 0,-1,1,0 };
int n, m;
pair<int,int> make_start(int x, int y, int num) {
	vector<pair<int, pair<int, int> > >temp;
	q.push(mp(x, y));
	dest_check[x][y][num] = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && !dest_check[nx][ny][num] && map[nx][ny] != -1) {
				q.push(mp(nx, ny));
				dest_check[nx][ny][num] = dest_check[x][y][num] + 1;
				if (map[nx][ny] == 1) {
					temp.push_back(mp(dest_check[nx][ny][num], mp(nx, ny)));
				}
			}
		}
	}
	sort(temp.begin(), temp.end());
	return mp(temp[0].second.first, temp[0].second.second);
}
int start() {
	pair<int, int> result;
	int flag, x, y, num, life, now, nx, ny;
	int st = 1, t = 0;
	while (1) {
		flag = 0;
		for (int i = 1; i < v.size(); ++i) {
			if (!v[i].life) continue;
			flag = 1;
			x = v[i].x;
			y = v[i].y;
			num = v[i].num;
			now = dest_check[x][y][num];
			for (int j = 0; j < 4; ++j) {
				nx = x + dx[j];
				ny = y + dy[j];
				if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny] != -1) {
					if (dest_check[nx][ny][num] < now) {
						v[num].x = nx;
						v[num].y = ny;
						if (nx == dest[num].first && ny == dest[num].second) {
							map[nx][ny] = -1;
							v[num].life = 0;
						}
						break;
					}
				}
			}
		}
		if (st <= m) {
			result = make_start(dest[st].first, dest[st].second, st);
			I = { result.first,result.second,st,1 };
			v.push_back(I);
			map[result.first][result.second] = -1;
			++st;
		}
		else {
			if (!flag) return t;
		}
		++t;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int x, y;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	dest.push_back(mp(-1, -1));
	for (int i = 1; i <= m; ++i) {
		cin >> x >> y;
		dest.push_back(mp(x, y));
	}
	I = { 0,0,0,1 };
	v.push_back(I);
	cout << start();
}
