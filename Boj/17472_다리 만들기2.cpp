// https://www.acmicpc.net/problem/17472
// Tip -> 연결여부 무조건 체크

#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, num;
}info;
info I;
vector<info> v;
vector<pair<int, pair<int, int> > > temp;
queue<pair<int, int> >q;
queue<int> q2;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[11][11];
bool connect[7][7], visit[11][11], visit2[7];
int n, m;
int island_cnt = 0, stop = 0, result = -1;
void counting(int sx, int sy, int num) {
	q.push(mp(sx, sy));
	visit[sx][sy] = 1;
	map[sx][sy] = num;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		I = { x,y,num };
		v.push_back(I);
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m && map[nx][ny] && !visit[nx][ny]) {
				q.push(mp(nx, ny));
				visit[nx][ny] = 1;
				map[nx][ny] = num;
			}
		}
	}
}
void calc(int sx, int sy, int start_num) {
	for (int i = 0; i < 4; ++i) {
		int x = sx;
		int y = sy;
		int len = 0;
		int flag = 0;
		int end_num;
		while (1) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (1 > nx || nx > n || 1 > ny || ny > m || map[nx][ny] == start_num) {
				flag = 1;
				break;
			}
			if (map[nx][ny] && map[nx][ny] != start_num) {
				end_num = map[nx][ny];
				break;
			}
			++len;
			x = nx;
			y = ny;
		}
		if (!flag && len > 1)
			temp.push_back(mp(len, mp(start_num, end_num)));
	}
}
bool check() {
	memset(visit2, 0, sizeof(visit2));
	q2.push(1);
	visit2[1] = 1;
	while (!q2.empty()) {
		int now = q2.front(); q2.pop();
		for (int i = 1; i <= island_cnt; ++i) {
			if (!visit2[i] && connect[now][i]) {
				q2.push(i);
				visit2[i] = 1;
			}
		}
	}
	for (int i = 1; i <= island_cnt; ++i)
		if (!visit2[i]) return false;
	return true;
}
void brute(int index, int bridge_cnt,int bridge_len) {
	if (bridge_cnt == island_cnt - 1) {
		if (check()) {
			result =  bridge_len;
			stop = 1;
		}
		return;
	}
	for (int i = index; i < temp.size(); ++i) {
		int len = temp[i].first;
		int start_num = temp[i].second.first;
		int end_num = temp[i].second.second;
		if (!connect[start_num][end_num] && !connect[end_num][start_num]) {
			connect[start_num][end_num] = connect[end_num][start_num] = 1;
			brute(i + 1, bridge_cnt + 1, bridge_len + len);
			connect[start_num][end_num] = connect[end_num][start_num] = 0;
		}
		if (stop) return;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> map[i][j];
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j] && !visit[i][j]) {
				counting(i, j, ++island_cnt);
			}
		}
	}
	for (int i = 0; i < v.size(); ++i) 
		calc(v[i].x, v[i].y, v[i].num);
	
	sort(temp.begin(), temp.end());
	temp.erase(unique(temp.begin(), temp.end()), temp.end());
	brute(0, 0, 0);
	cout << (result == -1 ? -1 : result);
}
