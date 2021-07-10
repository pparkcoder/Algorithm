// 2021 카카오 채용연계형 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/81302
// Tip -> vector<vector<string>> places를 map에 복사하는 과정을 연습할 것

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#define mp make_pair
using namespace std;
queue<pair<int, int> > q;
char map[5][5];
int visit[5][5];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
void map_copy(vector<vector<string>> places, int num) {
	for (int j = 0; j < places[num].size(); ++j) {
		for (int k = 0; k < places[num][j].size(); ++k) {
			visit[j][k] = 987654321;
			map[j][k] = places[num][j][k];
			if (map[j][k] == 'P') {
				q.push(mp(j, k));
				visit[j][k] = 0;
			}
		}
	}
}
vector<int> solution(vector<vector<string>> places) {
	vector<int> answer;
	for (int i = 0; i < places.size(); ++i) {
		map_copy(places, i);
		int flag = 1;
		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second; q.pop();
			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (0 <= nx && nx < 5 && 0 <= ny && ny < 5 && map[nx][ny] != 'X') {
					if (map[x][y] == 'P' && visit[nx][ny] <= 1) {
						flag = 0;
						break;
					}
					else {
						if (visit[nx][ny] == 987654321) {
							q.push(mp(nx, ny));
							visit[nx][ny] = visit[x][y] + 1;
						}
					}
				}
			}
			if (!flag) break;
		}
		answer.push_back(flag);
		while (!q.empty()) q.pop();
	}
	return answer;
}
