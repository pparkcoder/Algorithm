// 2020 카카오 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/67259

#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;
typedef struct {
	int x, y, dir;
}info;
info I;
queue<info> q;
int visit[25][25][4];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int solution(vector<vector<int>> board) {
	int n = board.size();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < 4; ++k)
				visit[i][j][k] = INT_MAX;
	for (int i = 0; i < 4; ++i) {
		I = { 0,0,i };
		q.push(I);
		visit[0][0][i] = 0;
	}
	int answer = INT_MAX;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int dir = q.front().dir; q.pop();
		if (x == n - 1 && y == n - 1) {
			answer = min(answer, visit[x][y][dir]);
			continue;
		}
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 <= nx && nx < n && 0 <= ny && ny < n && !board[nx][ny]) {
				int money = 100;
				if (dir != i) money += 500; // 코너인 경우
				if (visit[nx][ny][i] > visit[x][y][dir] + money) {
					I = { nx,ny,i };
					q.push(I);
					visit[nx][ny][i] = visit[x][y][dir] + money;
				}
			}
		}
	}
	return answer;
}
