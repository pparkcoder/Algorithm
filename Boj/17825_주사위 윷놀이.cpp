// https://www.acmicpc.net/problem/17825
// Tip -> ++ny를 진행하면서 파란색 칸 체크가 아닌, 다 끝나고 파란색 칸 체크 후 옮겨주기

#include<iostream>
#include<algorithm>
#define mp make_pair
using namespace std;
int map[5][23] = {
	{0,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0}, // 빨간색 판
	{0,10,13,16,19},  // 파란색 칸
	{0,20,22,24}, // 파란색 칸
	{0,30,28,27,26},  // 파란색 칸
	{0,25,30,35}  // 빨간색 칸
};
int dice[11];
pair<int, int> info[4];
int result = 0;
void brute(int sum, int cnt) {
	if (cnt == 11) {
		result = max(result, sum);
		return;
	}
	int x, y, nx, ny, flag;
	for (int i = 0; i < 4; ++i) {
		nx = x = info[i].first;
		ny = y = info[i].second;
		flag = 0;
		if (x == 0 && y == 22) continue;
		for (int j = 1; j <= dice[cnt]; ++j) {
			++ny;
			if (nx == 0 && ny == 22) break;
			else if ((nx == 1 && ny == 5) || (nx == 2 && ny == 4) || (nx == 3 && ny == 5)) nx = 4, ny = 1;
			else if (nx == 4 && ny == 4) nx = 0, ny = 21;
		}
		if (nx == 0) {  // 파란색 칸으로 옮겨주기
			if (ny == 6) nx = 1, ny = 1;
			else if (ny == 11) nx = 2, ny = 1;
			else if (ny == 16) nx = 3, ny = 1;
		}
		if (!(nx == 0 && ny == 22)) {
			for (int j = 0; j < 4; ++j) {
				if (i == j) continue;
				if (info[j].first == nx && info[j].second == ny) {
					flag = 1;
					break;
				}
			}
		}
		if (!flag) { // 도착 칸에 말이 없는 경우
			info[i] = mp(nx, ny);
			brute(sum + map[nx][ny], cnt + 1);
			info[i] = mp(x, y);
		} 
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	for (int i = 1; i < 11; ++i)
		cin >> dice[i];
	for (int i = 0; i < 4; ++i)
		info[i] = mp(0, 1);
	brute(0, 1);
	cout << result;
}
