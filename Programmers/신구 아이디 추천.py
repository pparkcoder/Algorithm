// 2021 카카오 블라인드
// https://programmers.co.kr/learn/courses/30/lessons/72410
  
def solution(new_id):
    new_id = new_id.lower()
    temp = ''
    
    for i in new_id:
        if i.isalpha() or i.isdigit() or i in ['-','_','.'] :
            temp += i
    while '..' in temp :
        temp = temp.replace('..','.')
        
    new_id = temp
    if new_id[0] == '.':
        if len(new_id) > 1 :
            new_id = new_id[1:]
            
    if new_id[-1] == '.':
        if len(new_id) > 1 :
            new_id = new_id[:-1]
        else :
            new_id = ''
            
    if new_id == '' :
        new_id = 'a'
        
    if len(new_id) >15 :
        new_id = new_id[:15]
        if new_id[-1] == '.' :
            new_id = new_id[:-1]
            
    while len(new_id) < 3:
        new_id += new_id[-1]
        
    answer = new_id
    return answer
