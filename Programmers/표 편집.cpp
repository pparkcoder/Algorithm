// 2021 카카오 채용연계형 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/81303
// 효율성 TC 6,9,10 TLE -> 고민이 필요...

#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
stack<int> st;
string solution(int n, int k, vector<string> cmd) {
	string answer = "";
	int now_index = k;
	int now_size = n;
	int temp,len;
	for (int i = 0; i < cmd.size(); ++i) {
		if (cmd[i][0] == 'U') {
			cmd[i][0] = ' ';
			now_index -= stoi(cmd[i]);
		}
		else if (cmd[i][0] == 'D') {
			cmd[i][0] = ' ';
			now_index += stoi(cmd[i]);
		}
		else if (cmd[i][0] == 'C') {
			st.push(now_index);
			if (--now_size == now_index)
				--now_index ;
		}
		else {
			temp = st.top();
			st.pop();
			++now_size;
			if (temp <= now_index)
				++now_index;
		}
	}
	for (int i = 0; i < now_size; ++i)
		answer += 'O';
	len = st.size();
	for (int i = 0; i < len; ++i) {
		answer.insert(answer.begin() + st.top(), 'X');
		st.pop();
	}
	return answer;
}
