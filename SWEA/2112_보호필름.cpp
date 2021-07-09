// Tip -> temp vector를 계속해서 만들면 TLE -> 한번만 만들고 clear()를 이용

#include<iostream>
#include<vector>
#define mp make_pair
using namespace std;
int map[14][21];
int t, d, w, k, flag, result;
bool check() {
	int cnt;
	for (int i = 1; i <= w; ++i) {
		cnt = 0;
		for (int j = 1; j < d; ++j) {
			if (map[j][i] == map[j + 1][i]) ++cnt;
			else cnt = 0;
			if (cnt == k - 1) break;
		}
		if (cnt < k - 1) return false;
	}
	return true;
}
void brute(int index, int now_cnt,int max_cnt) {
	if (now_cnt == max_cnt) {
		if (check()) flag = 1;
		return;
	}
	vector<int> temp;
	for (int i = index; i <= d; ++i) {
		for (int j = 1; j <= w; ++j)
			temp.push_back(map[i][j]);
		for (int j = 0; j < 2; ++j) {
			for (int k = 1; k <= w; ++k) map[i][k] = j;
			brute(i + 1, now_cnt + 1, max_cnt);
			if (flag) return;
		}
		for (int j = 1, temp_index = 0; j <= w; ++j) map[i][j] = temp[temp_index++];
		temp.clear();
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> d >> w >> k;
		for (int i = 1; i <= d; ++i)
			for (int j = 1; j <= w; ++j)
				cin >> map[i][j];
		flag = 0;
		for (int i = 0; i <= d; ++i) {
			brute(1, 0, i);
			if (flag) {
				result = i;
				break;
			}
		}
		cout << "#" << l << " " << result << "\n";
	}
}
