// https://www.acmicpc.net/problem/14713
// dest 마지막에 공백문자 하나 넣어줘야 마지막 단어까지 검사
// 앵무새가 말한 단어들은 전부 적어야 함

#include<iostream>
#include<string>
#include<deque>
#include<map>
using namespace std;
map<string, bool> visit;
deque<string> dq[101];
int n, flag;
string s, temp, temp2, dest;
bool check() {
	temp = temp2 = "";
	for (int i = 0; i < dest.length(); ++i) {
		if (dest[i] == ' ') {
			flag = 1;
			for (int j = 0; j < n; ++j) {
				if (dq[j].size() && dq[j].front() == temp) {
					dq[j].pop_front();
					temp = "";
					flag = 0;
					break;
				}
			}
			if (flag) return false;
		}
		else
			temp += (dest[i] + temp2);
	}
	for (int i = 0; i < n; ++i) { // 앵무새가 말한 단어들은 전부 적지 않은 경우
		if (dq[i].size()) return false;
	}
	return true;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	getline(cin, s); // n 입력 후 버퍼에 있는 개행문자 제거
	for (int i = 0; i < n; ++i) {
		getline(cin, s);
		temp = temp2 = "";
		for (int j = 0; j < s.length(); ++j) {
			if (s[j] == ' ') {
				dq[i].push_back(temp);
				temp = "";
			}
			else {
				temp += (s[j] + temp2);
			}
		}
		dq[i].push_back(temp);
	}
	getline(cin, dest);
	dest += " ";
	if (check()) cout << "Possible";
	else cout << "Impossible";
}
