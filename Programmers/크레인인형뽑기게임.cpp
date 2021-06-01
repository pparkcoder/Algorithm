// 2019 카카오 개발자 겨울 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/64061

#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    stack<int> st;
    int result = 0;
    int n = board.size();
    for(int i=0;i<moves.size();++i){
        int pick = moves[i] - 1;
        for(int j=0;j<n;++j){
            if(board[j][pick]){
                if(!st.empty() && st.top() == board[j][pick]){
                    st.pop();
                    result+=2;
                }
                else
                    st.push(board[j][pick]);
                board[j][pick] = 0;
                break;
            }
        }
    }
    return result;
}
