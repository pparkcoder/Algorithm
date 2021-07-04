// 2020 카카오 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/67258
// Solving -> 보석을 모두 찾았거나, e index가 끝지점이라면 s증가 / 아니라면 e 증가
// Tip -> e index가 끝지점에 도착했다는 변수 필요 + e index가 gems.size()보다 크거나 같다면 break -> 이미 지나온 구간값에서 답을 찾지 못하였기에

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <climits>
#define mp make_pair
using namespace std;
map<string, int> visit;
vector<int> solution(vector<string> gems) {
	vector<int> answer = { 0,0 };
	int total, s, e, now, len, flag;
  
	for (int i = 0; i < gems.size(); ++i)
		if (!visit[gems[i]]) ++visit[gems[i]];
	total = visit.size();
	visit.clear();
	flag = s = e = now = 0;
	len = INT_MAX;
  
	while (s <= e) {  //flag = 1 : e index가 끝지점에 도착 -> 이 경우에는 계속해서 s index만 증가
		if (!visit[gems[e]]) ++now;
		if (!flag) ++visit[gems[e]];
		if (now == total) {
			if (e - s < len) {
				len = e - s;
				answer[0] = s + 1;
				answer[1] = e + 1;
			}
			if (--visit[gems[s]] <= 0) --now, visit[gems[s]] = 0;
			++s;
			flag = 1;
		}
		else {
			if (e == gems.size() - 1) {
				if (--visit[gems[s]] == 0) --now, visit[gems[s]] = 0;
				++s;
				flag = 1;
			}
			else if (++e >= gems.size()) break;
			else flag = 0;
		}
	}
	return answer;
}
