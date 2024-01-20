// 석유 덩어리의 최대 개수를 생각하지 않는 풀이가 더 효율적

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#define mp make_pair
using namespace std;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[501][501], visit[501][501], check[125001];
vector<int> v[501];
queue<pair<int, int> > q;
int n, m, num;
void bfs(int sx, int sy, int check_num) {
	int cnt = 1;
	q.push(mp(sx, sy));
	visit[sx][sy] = check_num;
	v[sy].push_back(check_num);
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m) {
				if (map[nx][ny] && !visit[nx][ny]) {
					q.push(mp(nx, ny));
					visit[nx][ny] = check_num;
					v[ny].push_back(check_num);
					++cnt;
				}
			}
		}
	}
	check[check_num] = cnt;
}
int solution(vector<vector<int>> land) {
	int result = 0;
	n = land.size(), m = land[0].size(), num = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			map[i][j] = land[i - 1][j - 1];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j] && !visit[i][j]) {
				bfs(i, j, ++num);
			}
		}
	}
	
	for (int i = 1; i <= m; ++i) {
        if(v[i].size()){
            sort(v[i].begin(), v[i].end());
            v[i].erase(unique(v[i].begin(), v[i].end()), v[i].end());
            int temp = 0;
            for (int j = 0; j < v[i].size(); ++j) {
                temp += check[v[i][j]];
            }
            result = max(temp, result);
        }
	}
	return result;
}
