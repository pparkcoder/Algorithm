// https://www.codetree.ai/frequent-problems/artistry/description
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<map>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, group_num, cnt;
}info;
info I;
vector<info> v, v2;
queue<pair<int, int> > q, q2;
map<pair<int, int>, int> calc;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int board[30][30], group[30][30];
bool visit[30][30];
int n, group_cnt, turn_cnt, limit;
int result = 0;
void turn2() {
	vector<int> temp;
	for (int i = n; i > 0; --i) { // 십자 회전
		if (i == limit) continue;
		temp.push_back(board[limit][i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (i == limit) continue;
		temp.push_back(board[i][limit]);
	}
	int index = 0;
	for (int i = 1; i <= n; ++i) {
		if (i == limit) continue;
		board[i][limit] = temp[index++];
	}
	for (int i = 1; i <= n; ++i) {
		if (i == limit) continue;
		board[limit][i] = temp[index++];
	}
}
void turn1(int sx, int sy, int lx, int ly) { // 사각형 회전
	vector<int> temp;
	for (int i = sx; i <= lx; ++i)
		for (int j = sy; j <= ly; ++j)
			temp.push_back(board[i][j]);
	int index = 0;
	for (int i = ly; i >= sy; --i)
		for (int j = sx; j <= lx; ++j)
			board[j][i] = temp[index++];
}
void dfs(int index, int cnt) {
	if (cnt == 2) {
		int cnt1 = v2[0].cnt;
		int cnt2 = v2[1].cnt;
		int num1 = board[v2[0].x][v2[0].y];
		int num2 = board[v2[1].x][v2[1].y];
		int temp = calc[mp(v2[0].group_num, v2[1].group_num)];
		result += ((cnt1 + cnt2) * num1 * num2 * temp);
		return;
	}
	for (int i = index; i < v.size(); ++i) {
		v2.push_back(v[i]);
		dfs(i + 1, cnt + 1);
		v2.pop_back();
	}
}
void bfs(int sx, int sy, int num) { // 인접한 곳 맞닿은 변의 개수 계산
	q2.push(mp(sx, sy));
	visit[sx][sy] = 1;
	while (!q2.empty()) {
		int x = q2.front().first;
		int y = q2.front().second; q2.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
				if (group[nx][ny] == num) {
					q2.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
				else
					++calc[mp(num, group[nx][ny])];
			}
		}
	}
}
void make_group(int sx, int sy, int num) {
	q.push(mp(sx, sy));
	group[sx][sy] = num;
	int cnt = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n) {
				if (!group[nx][ny] && board[nx][ny] == board[sx][sy]) {
					q.push(mp(nx, ny));
					group[nx][ny] = num;
					++cnt;
				}
			}
		}
	}
	I = { sx,sy,num,cnt };
	v.push_back(I);
}
void init() {
	v.clear();
	v2.clear();
	while (!q.empty()) q.pop();
	while (!q2.empty()) q2.pop();
	calc.clear();
	memset(group, 0, sizeof(group));
	memset(visit, 0, sizeof(visit));
	group_cnt = 1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> board[i][j];
	for (int l = 0; l < 4; ++l) {
		init();
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (!group[i][j])
					make_group(i, j, group_cnt++);
		for (int i = 0; i < v.size(); ++i)
			bfs(v[i].x, v[i].y, v[i].group_num);
		turn_cnt = n / 4;
		limit = n / 2 + 1;
		dfs(0, 0);
		turn1(1, 1, limit - 1, limit - 1);
		turn1(1, limit + 1, limit - 1, n);
		turn1(limit + 1, 1, n, limit - 1);
		turn1(limit + 1, limit + 1, n, n);
		turn2();
	}
		cout << result;
}
