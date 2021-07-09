// 2021 카카오 채용연계형 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/81301

#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    string answer = "";
    string temp;
    for(int i=0;i<s.length();++i){
        if('0' <= s[i] && s[i] <= '9') answer += s[i];
        else{ 
            temp = "";
            if(s[i] == 'z') answer+='0',i+=3;
            else if(s[i] == 'o') answer+='1',i+=2;
            else if(s[i] == 'e') answer+='8',i+=4;
            else if(s[i] == 'n') answer+='9',i+=3;
            else if(s[i] == 't') {
                for(int j=i;j<i+3;++j)
                    temp+=s[j];
                if(temp == "two") answer+='2',i+=2;
                else answer+='3',i+=4;
            }
            else if(s[i] == 'f') {
               for(int j=i;j<i+4;++j)
                    temp+=s[j];
                if(temp == "four") answer+='4';
                else answer+='5';
                i+=3;
            }
            else{
                for(int j=i;j<i+3;++j)
                    temp+=s[j];
                if(temp == "six") answer+='6',i+=2;
                else answer+='7',i+=4;
            }
        }
    }
    return stoll(answer);
}
