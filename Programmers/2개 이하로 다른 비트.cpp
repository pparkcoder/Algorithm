// 월간 코드 챌린지 시즌2
// https://programmers.co.kr/learn/courses/30/lessons/77885
// 첫번째 코드 TLE, 두번째 코드 AC
// 논리적 차이는 없으나 shift 연산 보다 그냥 곱해주는게 더 빨라서 됬다고 생각한다...

#include<iostream>
#include<vector>
using namespace std;
//vector<long long> solution(vector<long long> numbers) {
//	vector<long long> answer;
//	for (int i = 0; i < numbers.size(); ++i) {
//		long long num = numbers[i];
//		if (!(num % 2)) answer.push_back(num + 1);
//		else {
//			int temp = 0;
//			while (1) {
//				if (!(num & (1 << temp))) break;
//				++temp;
//			}
//			answer.push_back(num + (1 << --temp));
//		}
//	}
//	return answer;
//}
  
vector<long long> solution(vector<long long> numbers) {
	vector<long long> answer;
	for (int i = 0; i < numbers.size(); ++i) {
		long long num = numbers[i];
		if (!(num % 2)) answer.push_back(num + 1);
		else {
			long long temp = 1;
			while (1) {
				if (!(num & temp)) break;
				temp *= 2;
			}
			temp /= 2;
			answer.push_back(num + temp);
		}
	}
	return answer;
}
