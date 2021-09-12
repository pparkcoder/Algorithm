// https://www.acmicpc.net/problem/16939

#include<iostream>
#include<deque>
using namespace std;
deque<int> q;
int map[7][9], cmap[7][9];
int num, temp, value;
bool check(int flag) {
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 8; j++)
			cmap[i][j] = map[i][j];

	int index = 0;
	if (flag == 0) {	// up_down
		for (int i = 1; i <= 6; i++)
			cmap[i][3] = q.at(index++);
		cmap[3][8] = q.at(index++);
		cmap[4][8] = q.at(index);
	}
	else if (flag == 1) {		 //left_right
		for (int i = 1; i <= 8; i++)
			cmap[3][i] = q.at(index++);
	}
	else {
		for (int i = 3; i <= 4; i++)
			cmap[2][i] = q.at(index++);
		for (int i = 3; i <= 4; i++)
			cmap[i][5] = q.at(index++);
		for (int i = 4; i >=3; i--)
			cmap[5][i] = q.at(index++);
		for (int i = 4; i >=3; i--)
			cmap[i][2] = q.at(index++);
	}
	q.clear();

	value = cmap[1][3];
	for (int i = 1; i <= 2; i++) {
		for (int j = 3; j <= 4; j++)
			if (cmap[i][j] != value) return false;
	}
	value = cmap[3][3];
	for (int i = 3; i <= 4; i++) {
		for (int j = 3; j <= 4; j++)
			if (cmap[i][j] != value) return false;
	}
	value = cmap[5][3];
	for (int i = 5; i <= 6; i++) {
		for (int j = 3; j <= 4; j++)
			if (cmap[i][j] != value) return false;
	}
	value = cmap[3][1];
	for (int i = 3; i <= 4; i++) {
		for (int j = 1; j <= 2; j++)
			if (cmap[i][j] != value) return false;
	}
	value = cmap[3][5];
	for (int i = 3; i <= 4; i++) {
		for (int j = 5; j <= 6; j++)
			if (cmap[i][j] != value) return false;
	}
	value = cmap[3][7];
	for (int i = 3; i <= 4; i++) {
		for (int j = 7; j <= 8; j++)
			if (cmap[i][j] != value) return false;
	}
	return true;
}
bool middle(int flag) {
	for (int i = 3; i <= 4; i++)
		q.push_back(map[2][i]);
	for (int i = 3; i <= 4; i++)
		q.push_back(map[i][5]);
	for (int i = 4; i >= 3; i--)
		q.push_back(map[5][i]);
	for (int i = 4; i >=3; i--)
		q.push_back(map[i][2]);
	if (!flag) {// left
		for (int i = 1; i <= 2; i++) {
			temp = q.back();
			q.pop_back();
			q.push_front(temp);
		}
	}
	else {
		for (int i = 1; i <= 2; i++) {
			temp = q.front();
			q.pop_front();
			q.push_back(temp);
		}
	}
	return check(2);
}
bool left_right(int flag) {
	for (int i = 1; i <= 8; i++)
		q.push_back(map[3][i]);
	if (!flag) {	//right
		for (int i = 1; i <= 2; i++) {
			temp = q.front();
			q.pop_front();
			q.push_back(temp);
		}
	}
	else {	//left
		for (int i = 1; i <= 2; i++) {
			temp = q.back();
			q.pop_back();
			q.push_front(temp);
		}
	}
	return check(1);
}
bool up_down(int flag) {
	for (int i = 1; i <= 6; i++)
		q.push_back(map[i][3]);
	q.push_back(map[3][8]);
	q.push_back(map[4][8]);
	if (!flag) { //up
		for (int i = 1; i <= 2; i++) {
			temp = q.back();
			q.pop_back();
			q.push_front(temp);
		}
	}
	else { //down
		for (int i = 1; i <= 2; i++) {
			temp = q.front();
			q.pop_front();
			q.push_back(temp);
		}
	}
	return check(0);
}
int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	for (int i = 1; i <= 6; i++)
		for (int j = 3; j <= 4; j++)
			cin >> map[i][j];
	for (int i = 3; i <= 4; i++)
		for (int j = 1; j <= 2; j++)
			cin >> map[i][j];
	for (int i = 3; i <= 4; i++)
		for (int j = 5; j <= 6; j++)
			cin >> map[i][j];
	for (int i = 3; i <= 4; i++)
		for (int j = 7; j <= 8; j++)
			cin >> map[i][j];
	if (left_right(0) || left_right(1) || up_down(0) || up_down(1) || middle(0) || middle(1)) cout << 1;
	else cout << 0;
}
