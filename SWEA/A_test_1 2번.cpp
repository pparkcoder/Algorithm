#include<iostream>
#include<queue>
using namespace std;
typedef struct {
	int x, y, monster, people;
}info;
info I;
queue<info> q;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[51][51];
int visit[51][51][16][16]; //x,y,몬스터,고객
int t, n, total, temp;
void q_push(int x, int y, int monster, int people,int nx,int ny, int new_monster, int new_people) {
	I = { nx,ny,new_monster,new_people };
	q.push(I);
	visit[nx][ny][new_monster][new_people] = visit[x][y][monster][people] + 1;
}
int bfs() {
	while (!q.empty()) q.pop();
	if (map[1][1] > 0) { // 시작점에 몬스터가 있는 경우 -> 잡고 시작
		int new_monster = 0 | 1 << (map[1][1] - 1);
		I = { 1,1,new_monster,0 };
		q.push(I);
		visit[1][1][new_monster][0] = 0;
	}
	else {
		I = { 1,1,0,0 };
		q.push(I);
		visit[1][1][0][0] = 0;
	}
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int monster = q.front().monster;
		int people = q.front().people; q.pop();
		if (monster == total && people == total) return visit[x][y][total][total];
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n) {
				if (!map[nx][ny]) { //몬스터, 사람이 아닌 경우
					if (visit[nx][ny][monster][people] > visit[x][y][monster][people] + 1) {
						q_push(x, y, monster, people, nx, ny, monster, people);
					}
				}
				else {
					if (map[nx][ny] > 0) { //몬스터인 경우
						int new_monster = monster | 1 << (map[nx][ny] - 1); // 잡기
						if (visit[nx][ny][new_monster][people] > visit[x][y][monster][people] + 1) {
							q_push(x, y, monster, people, nx, ny, new_monster, people);
						}
					}
					else { // 고객인 경우
						if (monster & (1 << (abs(map[nx][ny]) - 1))) { // 대응되는 몬스터를 잡은 경우
							int new_people = people | 1 << (abs(map[nx][ny]) - 1);
							if (visit[nx][ny][monster][new_people] > visit[x][y][monster][people] + 1) {
								q_push(x, y, monster, people, nx, ny, monster, new_people);
							}
						}
						else { // 못잡은 경우
							if (visit[nx][ny][monster][people] > visit[x][y][monster][people] + 1) {
								q_push(x, y, monster, people, nx, ny, monster, people);
							}
						}

					}
				}
			}
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> n;
		temp = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> map[i][j];
				if (map[i][j] > 0) ++temp;
				for (int a = 0; a < 16; ++a)
					for (int b = 0; b < 16; ++b)
						visit[i][j][a][b] = INT_MAX;
			}
		}
		total = (1 << temp) - 1;
		cout << "#" << l << " " << bfs() << "\n";
	}
}
