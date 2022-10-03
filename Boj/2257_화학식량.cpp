// https://www.acmicpc.net/problem/2257

#include<iostream>
#include<stack>
#include<string>
using namespace std;
stack<string> st;
int result = 0;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s, new_s, temp, symbol = "";
	char c;
	cin >> s;
	for (int i = 0; i < s.length(); ++i) {
		c = s[i];
		if (('A' <= c && c <= 'Z') || c == '(') st.push(c + symbol);
		else if (c == ')') {
			new_s = "";
			while (1) {
				temp = st.top(); st.pop();
				if (temp == "(") break;
				new_s = temp + new_s;
			}
			st.push(new_s);
		}
		else {
			temp = st.top(); st.pop();
			new_s = temp;
			for (int j = 0; j < (c - '0') - 1; ++j) 
				new_s += temp;
			st.push(new_s);
		}
	}
	while (!st.empty()) {
		temp = st.top(); st.pop();
		for (int i = 0; i < temp.length(); ++i) {
			if (temp[i] == 'H') result += 1;
			else if (temp[i] == 'C') result += 12;
			else result += 16;
		}
	}
	cout << result;
}
