// https://www.codetree.ai/training-field/frequent-problems/destroy-the-turret/description?page=3&pageSize=20
// 가장 최근에 공격한 것 : 증감연산이 아닌 해당 turn을 넣어서 체크(line 151~152) -> 두 포탑이 하나씩 공격했을 경우 누가 최근인지 알 수 없기 때문에
/*
4 5 4
3 10 0 1 5
3 0 6 0 0
1 10 3 1 1
5 0 0 0 3
*/

#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int power, check, x, y;
}info;
typedef struct {
	int x, y;
	vector<pair<int, int> > temp;
}info2;
info I;
info2 I2;
vector<info> v;
queue<info2> q;
pair<int, int> map[11][11];
bool visit[11][11], visit2[11][11];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int dx2[8] = { -1,-1,-1,0,0,1,1,1 };
int dy2[8] = { -1,0,1,-1,1,-1,0,1 };
int start_x, start_y, target_x, target_y;
int n, m, k, num;
void init() {
	memset(visit, 0, sizeof(visit));
	memset(visit2, 0, sizeof(visit2));
	while (!q.empty()) q.pop();
}
bool cmp(info a, info b) {
	if (a.power == b.power) {
		if (a.check == b.check) {
			if (a.x + a.y == b.x + b.y) return a.y > b.y;
			else return a.x + a.y > b.x + b.y;
		}
		else return a.check > b.check;
	}
	else return a.power < b.power;
}
pair<int, int> dir_check(int x, int y, int dir, int flag) {
	int nx, ny;
	if (!flag) {
		nx = x + dx[dir];
		ny = y + dy[dir];
	}
	else {
		nx = x + dx2[dir];
		ny = y + dy2[dir];
	}
	if (nx > n) nx -= n;
	else if (nx < 1) nx += n;
	if (ny > m) ny -= m;
	else if (ny < 1) ny += m;
	return mp(nx, ny);
}
bool clean() {
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j].first <= 0) map[i][j].first = 0;
			else ++cnt;
		}
	}
	if (cnt == 1) return false;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j].first && !visit2[i][j]) ++map[i][j].first;
		}
	}
	return true;
}
void boom() {
	map[target_x][target_y].first -= map[start_x][start_y].first;
	visit2[target_x][target_y] = 1;
	for (int i = 0; i < 8; ++i) {
		pair<int, int> result = dir_check(target_x, target_y, i, 1);
		int nx = result.first;
		int ny = result.second;
		if (nx == start_x && ny == start_y) continue;
		if (map[nx][ny].first) {
			map[nx][ny].first -= (map[start_x][start_y].first / 2);
			visit2[nx][ny] = 1;
		}
	}
}
bool laser() {
	init();
	vector<pair<int, int> > temp;
	I2 = { start_x,start_y,temp };
	q.push(I2);
	visit[start_x][start_y] = visit2[start_x][start_y] = 1;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		temp = q.front().temp; q.pop();
		if (x == target_x && y == target_y) {
			for (int i = 0; i < temp.size(); ++i) {
				int tx = temp[i].first;
				int ty = temp[i].second;
				if (tx != target_x || ty != target_y) map[tx][ty].first -= (map[start_x][start_y].first / 2);
				else map[tx][ty].first -= map[start_x][start_y].first;
				visit2[tx][ty] = 1;
			}
			return true;
		}
		for (int i = 0; i < 4; ++i) {
			pair<int, int> result = dir_check(x, y, i, 0);
			int nx = result.first;
			int ny = result.second;
			if (!visit[nx][ny] && map[nx][ny].first) {
				vector<pair<int, int> > temp2 = temp;
				temp2.push_back(mp(nx, ny));
				I2 = { nx,ny,temp2 };
				q.push(I2);
				visit[nx][ny] = 1;
			}
		}
	}
	return false;
}
void make_vector() {
	v.clear();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j].first) {
				I = { map[i][j].first ,map[i][j].second,i, j };
				v.push_back(I);
			}
		}
	}
}
int start() {
	for (int turn = 0; turn < k; ++turn) {
		if (turn) make_vector();
		sort(v.begin(), v.end(), cmp);
		start_x = v[0].x;
		start_y = v[0].y;
		map[start_x][start_y].first += (n + m);
		//++map[start_x][start_y].second;
		map[start_x][start_y].second = turn + 1;
		target_x = v[v.size() - 1].x;
		target_y = v[v.size() - 1].y;
		if (!laser()) boom();
		if (!clean()) break;
	}
	make_vector();
	sort(v.begin(), v.end(), cmp);
	return map[v[v.size() - 1].x][v[v.size() - 1].y].first;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> num;
			if (num) {
				map[i][j].first = num;
				I = { map[i][j].first ,0,i, j };
				v.push_back(I);
			}
		}
	}
	cout << start();
}

// 2번째 풀이
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<climits>
#define mp make_pair
using namespace std;
typedef struct {
	int num, turn, sum, y, x;
}info;
typedef struct {
	int x, y;
	vector<pair<int, int> > temp;
}info2;
info I;
info2 I2;
vector<info> v;
int map[11][11], turn_check[11][11];
bool attack[11][11];
int dx[8] = { 0,1,0,-1,-1,-1,1,1 };
int dy[8] = { 1,0,-1,0,-1,1,-1,1 };
int N, M, K, wx, wy, lx, ly;
bool cmp(info a, info b) {
	if (a.num == b.num) {
		if (a.turn == b.turn) {
			if (a.sum == b.sum) return a.y > b.y;
			else return a.sum > b.sum;
		}
		else return a.turn > b.turn;
	}
	else return a.num < b.num;
}
bool repair() {
	int cnt = 0;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			if (map[i][j]) ++cnt;
	if (cnt <= 1) return false;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			if (map[i][j] && !attack[i][j]) ++map[i][j];
	return true;
}
void check() {
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			if (map[i][j] <= 0) map[i][j] = 0;
}
void boom(int turn) {
	memset(attack, 0, sizeof(attack));
	attack[wx][wy] = 1;
	map[lx][ly] -= map[wx][wy];
	attack[lx][ly] = 1;
	for (int i = 0; i < 8; ++i) {
		int nx = lx + dx[i];
		int ny = ly + dy[i];

		if (nx > N) nx = 1;
		else if (nx < 1) nx = N;
		if (ny > M) ny = 1;
		else if (ny < 1) ny = M;

		if (nx == wx && ny == wy) continue;

		if (map[nx][ny]) {
			map[nx][ny] -= (map[wx][wy] / 2);
			attack[nx][ny] = 1;
		}
	}
	turn_check[wx][wy] = turn;
}
bool razer(int turn) {
	int visit[11][11];
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			visit[i][j] = INT_MAX;
	memset(attack, 0, sizeof(attack));
	queue<info2> q;
	vector<pair<int, int> > temp;
	I2 = { wx,wy,temp };
	q.push(I2);
	attack[wx][wy] = visit[wx][wy] = 1;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		temp = q.front().temp; q.pop();
		if (x == lx && y == ly) {
			for (int i = 0; i < temp.size(); ++i) {
				int tx = temp[i].first;
				int ty = temp[i].second;
				if (tx == lx && ty == ly) map[tx][ty] -= map[wx][wy];
				else map[tx][ty] -= (map[wx][wy] / 2);
				attack[tx][ty] = 1;
			}
			turn_check[wx][wy] = turn;
			return true;
		}
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx > N) nx = 1;
			else if (nx < 1) nx = N;
			if (ny > M) ny = 1;
			else if (ny < 1) ny = M;

			if (!map[nx][ny] || visit[x][y] + 1 > visit[nx][ny]) continue;

			vector<pair<int, int> > temp2 = temp;
			temp2.push_back(mp(nx, ny));
			I2 = { nx,ny,temp2 };
			q.push(I2);
			visit[nx][ny] = visit[x][y] + 1;
		}
	}
	return false;
}
void choice() {
	v.clear();
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (map[i][j]) {
				I = { map[i][j],turn_check[i][j],i + j,j,i };
				v.push_back(I);
			}
		}
	}
	sort(v.begin(), v.end(), cmp);
	wx = v[0].x;
	wy = v[0].y;
	lx = v[v.size() - 1].x;
	ly = v[v.size() - 1].y;
	map[wx][wy] += (N + M);
}
void start() {
	int result = 0;
	memset(turn_check, 0, sizeof(turn_check));
	for (int t = 1; t <= K; ++t) {
		choice();
		if (!razer(t)) boom(t);
		check();
		if (!repair()) break;
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j)
			if (map[i][j]) result = max(result, map[i][j]);
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			cin >> map[i][j];
	start();
}
