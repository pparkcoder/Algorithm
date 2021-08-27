// 2021 Dev-Matching
// https://programmers.co.kr/learn/courses/30/lessons/77486
// Tip -> center 노드를 제외한 시작 노드의 번호를 2로 설정했기에, 배열의 크기는 2개 더 많아야 함-> max 노드의 수는 10000이므로 마지막 노드의 번호는 10002 -> 배열의 크기 10003  

#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;
map<string, int> enc;
int parent[10003];
int total[10003];
vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
	string s;
	int money, now, temp, next;
	enc["center"] = 1;
	for (int i = 0; i < enroll.size(); ++i) {
		s = enroll[i];
		enc[s] = i + 2;
	}
	for (int i = 0; i < referral.size(); ++i) {
		s = referral[i];
		if (s == "-") parent[i + 2] = 1;
		else parent[i + 2]= enc[s];
	}
	for (int i = 0; i < seller.size(); ++i) {
		s = seller[i];
		money = amount[i] * 100;
		now = enc[s];
		while (1) {
			temp = money * 0.1;
			if (now == 1 || temp < 1) {
				total[now] += money;
				break;
			}
			else if (temp >= 1) {
				total[now] += (money - temp);
				money *= 0.1;
				next = parent[now];
				now = next;

			}
		}
	}
	vector<int> answer;
	for (int i = 0; i < enroll.size(); ++i)
		answer.push_back(total[i + 2]);
	return answer;
}
