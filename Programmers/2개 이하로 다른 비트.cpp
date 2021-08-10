// ���� �ڵ� ç���� ����2
// https://programmers.co.kr/learn/courses/30/lessons/77885
// ù��° �ڵ� TLE, �ι�° �ڵ� AC
// ���� ���̴� ������ shift ���� ���� �׳� �����ִ°� �� ���� ��ٰ� �����Ѵ�...

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