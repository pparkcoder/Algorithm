// 1번
#include<iostream>
#include<queue>
#include<climits>

using namespace std;
typedef struct {
    int x, y, cnt, num;
} info;
info I;
queue<info> q;
char map[21][21];
int visit[21][21][10][10]; // x, y ,동전수, 동전최대숫자
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int n, sx, sy, ex, ey;
int result = INT_MAX;

void start() {
    I = {sx, sy, 0, 0};
    q.push(I);
    visit[sx][sy][0][0] = 0;
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int cnt = q.front().cnt;
        int num = q.front().num;q.pop();
        if (x == ex && y == ey && cnt >= 3) {
            result = min(result, visit[x][y][cnt][num]);
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny] != '#') {
                if ('1' <= map[nx][ny] && map[nx][ny] <= '9') { // 동전인 경우
                    if (num < map[nx][ny] - '0' &&
                        visit[nx][ny][cnt + 1][map[nx][ny] - '0'] > visit[x][y][cnt][num] + 1) { // 줍는 경우
                        I = {nx, ny, cnt + 1, map[nx][ny] - '0'};
                        q.push(I);
                        visit[nx][ny][cnt + 1][map[nx][ny] - '0'] = visit[x][y][cnt][num] + 1;
                    }
                    if (visit[nx][ny][cnt][num] > visit[x][y][cnt][num] + 1) { // 안줍는 경우
                        I = {nx, ny, cnt, num};
                        q.push(I);
                        visit[nx][ny][cnt][num] = visit[x][y][cnt][num] + 1;
                    }
                } else { // 길인 경우
                    if (visit[nx][ny][cnt][num] > visit[x][y][cnt][num] + 1) {
                        I = {nx, ny, cnt, num};
                        q.push(I);
                        visit[nx][ny][cnt][num] = visit[x][y][cnt][num] + 1;
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> map[i][j];
            if (map[i][j] == 'S') sx = i, sy = j, map[sx][sy] = '.';
            else if (map[i][j] == 'E') ex = i, ey = j, map[ex][sy] = '.';
            for (int k = 0; k < 10; ++k)
                for (int l = 0; l < 10; ++l)
                    visit[i][j][k][l] = INT_MAX;
        }
    }
    start();
    cout << (result == INT_MAX ? -1 : result);
}

// 2번
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;
vector<int> priority[9], tmap[101][5];
vector<pair<int, int> > order;
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
int map[101][5];
int n;
int result = 0;
void move() {
	int nx, ny, dir, len;
	for (int i = 1; i < 101; ++i) {
		for (int j = 1; j < 5; ++j) {
			if (map[i][j]) {
				for (int l = 0; l < 8; ++l) {
					dir = priority[map[i][j]][l];
					nx = i + dx[dir];
					ny = j + dy[dir];
					if (0 < nx && nx < 101 && 0 < ny && ny < 5) {
						tmap[nx][ny].push_back(map[i][j]);
						map[i][j] = 0;
						break;
					}
				}
			}
		}
	}
	for (int i = 1; i < 101; ++i) {
		for (int j = 1; j < 5; ++j) {
			len = tmap[i][j].size();
			if (len) {
				if (len > 1) sort(tmap[i][j].begin(), tmap[i][j].end());
				map[i][j] = tmap[i][j][0];
				tmap[i][j].clear();
			}
		}
	}
}
void total_down() {
	vector<int> temp;
	for (int i = 1; i < 5; ++i) {
		temp.clear();
		for (int j = 100; j > 0; --j) {
			if (map[j][i]) {
				temp.push_back(map[j][i]);
				map[j][i] = 0;
			}
		}
		if (temp.size()) {
			int index = 0;
			for (int j = 100; j > 0; --j) {
				map[j][i] = temp[index++];
				if (index == temp.size()) break;
			}
		}
	}
}
bool check() {
	int cnt;
	for (int i = 100; i > 0; --i) {
		cnt = 0;
		for (int j = 1; j < 5; ++j) {
			if (map[i][j]) ++cnt;
			else break;
		}
		if (cnt == 4) {
			for (int j = 1; j < 5; ++j)
				map[i][j] = 0;
			return true;
		}
	}
	return false;
}
void block_down(int num, int x, int y) {
	int nx;
	while (1) {
		nx = x + 1;
		if (100 < nx || map[nx][y]) break;
		x = nx;
	}
	map[x][y] = num;
}
void brute(int index, int sum) {
	if (index == n) {
		result = max(result, sum);
		return;
	}
	int k = order[index].first, c = order[index].second;
	int ans, copy_map[101][5];
	memcpy(copy_map, map, sizeof(map));
	if (c) {
		ans = 0;
		block_down(k, 0, c);
		if (check()) {
			++ans;
			total_down();
		}
		move();
		total_down();
		while (1) {
			if (check()) {
				++ans;
				total_down();
			}
			else break;
		}
		brute(index + 1, sum + ans);
	}
	else {
		for (int i = 1; i < 5; ++i) {
			ans = 0;
			block_down(k, 0, i);
			if (check()) {
				++ans;
				total_down();
			}
			move();
			total_down();
			while (1) {
				if (check()) {
					++ans;
					total_down();
				}
				else break;
			}
			brute(index + 1, sum + ans);
			memcpy(map, copy_map, sizeof(copy_map));
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int num, k, c, sum;
	cin >> n;
	for (int i = 1; i < 9; ++i) {
		for (int j = 1; j < 9; ++j) {
			cin >> num;
			priority[i].push_back(num - 1);
		}
	}
	for (int i = 0; i < n; ++i) {
		cin >> k >> c;
		order.push_back(mp(k, c));
	}
	for (int i = 0; i < n; ++i) {
		k = order[i].first;
		c = order[i].second;
		if (c) {
			block_down(k, 0, c);
			if (check()) {
				++result;
				total_down();
			}
			move();
			total_down();
			while (1) {
				if (check()) {
					++result;
					total_down();
				}
				else break;
			}
		}
		else {
			brute(i, result);
			break;
		}
	}
	cout << result;
}
