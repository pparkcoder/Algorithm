# 2020 카카오 인턴십
# https://programmers.co.kr/learn/courses/30/lessons/67257
  
 from itertools import permutations
from collections import deque

def solution(expression):
    queue = deque(expression)
    tool = set()
    graph = []
    string = ''
    while queue:
        x = queue.popleft()
        if x not in ['+', '-', '*']:
            if queue:
                string += x
            else:
                string += x
                graph.append(int(string))
                tool = list(tool)
        else:
            graph.append(int(string))
            graph.append(x)
            tool.add(x)
            string = ''

    times = list(permutations(tool, len(tool)))
    ans = 0

    for i in range(len(times)):
        temp = graph.copy()
        for j in range(len(times[0])):
            while times[i][j] in temp:
                a = temp.index(times[i][j])
                if times[i][j] == '+':
                    temp.insert(a+2, temp[a-1] + temp[a+1])
                elif times[i][j] == '-':
                    temp.insert(a+2, temp[a-1] - temp[a+1])
                else:
                    temp.insert(a+2, temp[a-1] * temp[a+1])
                del temp[a+1]
                del temp[a]
                del temp[a-1]
        ans = max(ans, abs(temp[0]))
    return ans
