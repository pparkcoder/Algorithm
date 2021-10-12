// vector
#include<iostream>
#include<vector>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, num, dir, live;
}info;
info I;
vector<info> v;
vector<pair<int, int> > map[101][101];
int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,-1,1 };
int t, n, m, k, result, x, y, num, dir;
int turn(int d) {
	if (d == 1) return 2;
	if (d == 2) return 1;
	if (d == 3) return 4;
	if (d == 4) return 3;
}
void check() {
	int len, sum;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			len = map[i][j].size();
			if (len) {
				if (len > 1) {
					sum = 0;
					sort(map[i][j].begin(), map[i][j].end());
					for (int l = 0; l < len - 1; ++l) {
						sum += map[i][j][l].first;
						v[map[i][j][l].second].live = 0;
					}
					v[map[i][j].back().second].num += sum;
				}
				map[i][j].clear();
			}
		}
	}
}
void start() {
	int nx, ny, ndir;
	while (m--) {
		for (int i = 0; i < k; ++i) {
			if (!v[i].live) continue;
			x = v[i].x;
			y = v[i].y;
			num = v[i].num;
			dir = v[i].dir;

			nx = x + dx[dir];
			ny = y + dy[dir];
			ndir = dir;
			if (!nx || !ny || nx == n - 1 || ny == n - 1) num /= 2, ndir = turn(dir);
			if (!num) {
				v[i].live = 0;
				continue;
			}

			v[i].x = nx;
			v[i].y = ny;
			v[i].num = num;
			v[i].dir = ndir;
			map[nx][ny].push_back(mp(num, i));
		}
		check();
	}
	for (int i = 0; i < k; ++i)
		if (v[i].live) result += v[i].num;
	v.clear();
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> n >> m >> k;
		for (int i = 0; i < k; ++i) {
			cin >> x >> y >> num >> dir;
			I = { x,y,num,dir,1 };
			v.push_back(I);
		}
		result = 0;
		start();
		cout << "#" << l << " " << result << "\n";
	}
}
// queue 이용
// #include<iostream>
// #include<vector>
// #include<queue>
// #include<algorithm>
// #define mp make_pair
// using namespace std;
// typedef struct {
// 	int x, y, cnt, dir;
// }info;
// info I;
// queue<info> q;
// vector<pair<int, int> > map[101][101];
// int dx[5] = { 0,-1,1,0,0 };
// int dy[5] = { 0,0,0,-1,1 };
// int test_case, n, m, k, result;
// int start() {
// 	int x, y, cnt, dir, nx, ny, len, sum;
// 	while (m--) {
// 		while (!q.empty()) {
// 			x = q.front().x;
// 			y = q.front().y;
// 			cnt = q.front().cnt;
// 			dir = q.front().dir; q.pop();
// 			nx = x + dx[dir];
// 			ny = y + dy[dir];
// 			if (nx == 0 || ny == 0 || nx == n - 1 || ny == n - 1) {
// 				if (dir == 1 || dir == 3) ++dir;
// 				else --dir;
// 				cnt /= 2;
// 			}
// 			if (cnt) map[nx][ny].push_back(mp(cnt, dir));
// 		}
// 		for (int i = 0; i < n; ++i) {
// 			for (int j = 0; j < n; ++j) {
// 				len = map[i][j].size();
// 				if (len) {
// 					if (len > 1) {
// 						sum = 0;
// 						sort(map[i][j].begin(), map[i][j].end());
// 						for (int l = 0; l < len; ++l)
// 							sum += map[i][j][l].first;
// 						I = { i,j,sum,map[i][j][len - 1].second };
// 						q.push(I);
// 					}
// 					else if (len == 1) {
// 						I = { i,j,map[i][j].front().first,map[i][j].front().second };
// 						q.push(I);
// 					}
// 					map[i][j].clear();
// 				}
// 			}
// 		}
// 	}
// 	result = 0;
// 	while (!q.empty()) {
// 		result += q.front().cnt;
// 		q.pop();
// 	}
// 	return result;
// }
// int main() {
// 	ios::sync_with_stdio(0); cin.tie(0);
// 	cin >> test_case;
// 	int x, y, cnt, dir;
// 	for (int i = 1; i <= test_case; ++i) {
// 		cin >> n >> m >> k;
// 		while (k--) {
// 			cin >> x >> y >> cnt >> dir;
// 			I = { x,y,cnt,dir };
// 			q.push(I);
// 		}
// 		cout << "#" << i << " " << start() << "\n";
// 	}
// }
