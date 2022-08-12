#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<cmath>
#define mp make_pair
using namespace std;
map<string,string> in_out;
map<string,int> result;
int calc(string before,string after){
    int index = before.find(':');
    int sh = stoi(before.substr(0,index)) * 3600;
    int sm = stoi(before.substr(index+1)) * 60;
    int eh = stoi(after.substr(0,index)) * 3600;
    int em = stoi(after.substr(index+1)) * 60;
    return ((eh + em) - (sh + sm)) / 60;

}
vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    int basic_m = fees[0],basic_fare = fees[1],unit_m=fees[2],unit_fare=fees[3];
    string target,car_time,car_num,check;
    int index1,index2,temp;
    double temp2;
    for(int i=0;i<records.size();++i){
        target = records[i];
        index1 = target.find(' ');
        index2 = target.rfind(' ');
        car_time = target.substr(0,index1);
        car_num = target.substr(index1+1,index2 - index1 -1 );
        check = target.substr(index2+1);
        if(check == "IN"){
            in_out[car_num] = car_time;
        }
        else{
            temp = calc(in_out[car_num],car_time);
            result[car_num] += temp;
            in_out[car_num] = "";
        }
    }
    for(auto iter : in_out){
        car_num = iter.first;
        if(in_out[car_num] != ""){ // 출차하지 않은 차는 23:59분을 기준
            temp = calc(in_out[car_num],"23:59");
            result[car_num] += temp;
        }
        if(result[car_num] <= basic_m){
            temp2 = basic_fare;
        }
        else{
            temp2 = basic_fare + ceil(double(result[car_num] - basic_m) / unit_m) * unit_fare;
        }
        answer.push_back(temp2);
    }
    return answer;
}
