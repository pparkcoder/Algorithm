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
