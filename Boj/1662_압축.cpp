// https://www.acmicpc.net/problem/1662
// Tip -> STL에 push 할 때, char to string 인 경우 to_string 사용x -> + " " 를 사용

#include<iostream>
#include<string>
#include<stack>
using namespace std;
stack<string> st;
string s, temp, t = "";
int cnt, res = 0;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	for (int i = 0; i < s.length(); ++i) {
		cnt = 0;
		if (s[i] == ')') {
			while (1) {
				temp = st.top(); st.pop();
				if (temp == "(") break;
				cnt += stoi(temp);
			}
			cnt *= stoi(st.top()); st.pop();
			st.push(to_string(cnt));
		}
		else if (s[i] == '(') st.push(s[i] + t);
		else {
			if (i == s.length() - 1) st.push("1");
			else {
				if ('0' <= s[i] && s[i] <= '9' && s[i + 1] == '(') st.push(s[i]+t);
				else st.push("1");
			}
		}
	}
	while (!st.empty()) {
		res += stoi(st.top());
		st.pop();
	}
	cout << res;
}
