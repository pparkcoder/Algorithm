// https://www.codetree.ai/training-field/frequent-problems/problems/ancient-ruin-exploration/description?page=1&pageSize=5
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int sum, dir, y, x;
}info;
info I;
vector<info> result;
vector<pair<int, int> > v, boom_list;
vector<int> piece;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[6][6], map2[6][6], visit[6][6];
int K, M, ans;
int piece_index = 0;
bool cmp_boom(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second) return a.first > b.first;
	else return a.second < b.second;
}
bool cmp_result(info a, info b) {
	if (a.sum == b.sum) {
		if (a.dir == b.dir) {
			if (a.y == b.y) return a.x < b.x;
			else return a.y < b.y;
		}
		else return a.dir < b.dir;
	}
	else return a.sum > b.sum;
}
void copy_map(int flag) {
	if (!flag) {
		for (int i = 1; i < 6; ++i)
			for (int j = 1; j < 6; ++j)
				map2[i][j] = map[i][j];
	}
	else {
		for (int i = 1; i < 6; ++i)
			for (int j = 1; j < 6; ++j)
				map[i][j] = map2[i][j];
	}
}
void turn(int x, int y, int d) {
	vector<int> temp;
	for (int t = 1; t <= d; ++t) {
		temp.clear();
		int index = 0;
		for (int i = x - 1; i <= x + 1; ++i)
			for (int j = y - 1; j <= y + 1; ++j)
				temp.push_back(map2[i][j]);
		for (int i = y + 1; i >= y - 1; --i)
			for (int j = x - 1; j <= x + 1; ++j)
				map2[j][i] = temp[index++];
	}
}
int bfs(int x, int y, int flag) {
	vector<pair<int, int> > temp;
	queue<pair<int, int> > q;
	q.push(mp(x, y));
	visit[x][y] = 1;
	int num = map2[x][y];
	int cnt = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		++cnt;
		if (flag) temp.push_back(mp(x, y));
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx < 6 && 0 < ny && ny < 6 && !visit[nx][ny] && num == map2[nx][ny]) {
				q.push(mp(nx, ny));
				visit[nx][ny] = 1;
			}
		}
	}
	if (cnt >= 3) {
		if (flag) {
			for (int i = 0; i < temp.size(); ++i)
				boom_list.push_back(temp[i]);
		}
		return cnt;
	}
	else return 0;
}
bool boom() {
	memset(visit, 0, sizeof(visit));
	boom_list.clear();
	for (int i = 1; i < 6; ++i) {
		for (int j = 1; j < 6; ++j) {
			if (!visit[i][j]) {
				bfs(i, j, 1);
			}
		}
	}
	if (!boom_list.size()) return false;
	else {
		ans += boom_list.size();
		sort(boom_list.begin(), boom_list.end(), cmp_boom);
		for (int i = 0; i < boom_list.size(); ++i) {
			int x = boom_list[i].first;
			int y = boom_list[i].second;
			map2[x][y] = piece[piece_index++];
		}
		return true;
	}
}
int calc(int x, int y, int dir) {
	memset(visit, 0, sizeof(visit));
	int sum = 0;
	for (int i = 1; i < 6; ++i) {
		for (int j = 1; j < 6; ++j) {
			if (!visit[i][j]) {
				sum += bfs(i, j, 0);
			}
		}
	}
	if (sum >= 3) return sum;
	else return 0;
}
bool make_best() {
	for (int i = 0; i < v.size(); ++i) {
		for (int dir = 1; dir < 4; ++dir) {
			int x = v[i].first;
			int y = v[i].second;
			copy_map(0);
			turn(x, y, dir);
			int piece_sum = calc(x, y, dir);
			if (piece_sum >= 3) {
				I = { piece_sum, dir, y,x };
				result.push_back(I);
			}
		}
	}
	if (!result.size()) return false;
	else {
		sort(result.begin(), result.end(), cmp_result);
		return true;
	}
}
void start() {
	for (int t = 1; t <= K; ++t) {
		result.clear();
		if (!make_best()) break;
		copy_map(0);
		turn(result[0].x, result[0].y, result[0].dir);
		ans = 0;
		while (1) {
			if (!boom()) break;
		}
		copy_map(1);
		cout << ans << " ";
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> K >> M;
	for (int i = 1; i < 6; ++i)
		for (int j = 1; j < 6; ++j)
			cin >> map[i][j];
	for (int i = 1; i <= M; ++i) {
		int num;
		cin >> num;
		piece.push_back(num);
	}
	for (int i = 2; i < 5; ++i)
		for (int j = 2; j < 5; ++j)
			v.push_back(mp(i, j));
	start();
}
