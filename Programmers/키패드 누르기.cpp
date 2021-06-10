// 2020 카카오 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/67256

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#define mp make_pair
using namespace std;
int map[5][4];
pair<int, int> info[11];
int lx = 4, ly = 1, rx = 4, ry = 3;
char update_left(int x,int y) {
	lx = x;
	ly = y;
	return 'L';
}
char update_right(int x,int y){
	rx = x;
	ry = y;
	return 'R';
}
string solution(vector<int> numbers, string hand) {
	string answer = "";
	int num = 1;
	for (int i = 1; i < 4; ++i) {
		for (int j = 1; j < 4; ++j) {
			map[i][j] = num++;
			info[map[i][j]] = mp(i, j);
		}
	}
	map[4][2] = 0;
	info[0] = mp(4, 2);
	for (int i = 0; i < numbers.size(); ++i) {
		num = numbers[i];
		int x = info[num].first;
		int y = info[num].second;
		if (num == 1 || num == 4 || num == 7) answer += update_left(x, y);
		else if (num == 3 || num == 6 || num == 9) answer += update_right(x, y);
		else {
			int l_len = abs(lx - x) + abs(ly - y);
			int r_len = abs(rx - x) + abs(ry - y);
			if (l_len < r_len) answer += update_left(x, y);
			else if (l_len > r_len) answer += update_right(x, y);
			else {
				if (hand == "left") answer += update_left(x, y);
				else answer += update_right(x, y);
			}
		}
	}
	return answer;
}
