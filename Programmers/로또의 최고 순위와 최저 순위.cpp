// 로또의 최고 순위와 최저 순위
// 2021 Dev-Matching
// https://programmers.co.kr/learn/courses/30/lessons/77484

#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    int cnt = 0,zero_cnt = 0;
    int min_score,max_score,temp;
    for(int i=0;i<lottos.size();++i){
        for(int j=0;j<win_nums.size();++j){
            if(lottos[i] == win_nums[j]){
                ++cnt;
                break;
            }
        }
        if(!lottos[i]) ++zero_cnt;
    }
    min_score = (7 - cnt > 5 ? 6 : 7 - cnt);
    temp = abs(min_score - zero_cnt);
    max_score = (temp == 0 ? 1 : temp);
    answer = {max_score,min_score};
    return answer;
}
