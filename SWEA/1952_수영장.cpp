#include<iostream>
#include<algorithm>
using namespace std;
int months[13];
int money[4];
int t, result;
void dfs(int month, int total_money) {
	if (month > 12) {
		result = min(result,total_money);
		return;
	}
	if (!months[month]) dfs(month + 1, total_money);
	else {
		dfs(month + 1, total_money + money[0] * months[month]);
		dfs(month + 1, total_money + money[1]);
		dfs(month + 3, total_money + money[2]);
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		for (int i = 0; i < 4; ++i)
			cin >> money[i];
		for (int i = 1; i < 13; ++i)
			cin >> months[i];
		result = money[3];
		dfs(1, 0);
		cout << "#" << l << " " << result << "\n";
	}
}
