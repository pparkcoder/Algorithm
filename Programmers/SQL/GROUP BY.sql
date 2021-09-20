-- 고양이와 개는 몇 마리 있을까
SELECT ANIMAL_TYPE,COUNT(ANIMAL_TYPE) FROM ANIMAL_INS GROUP BY ANIMAL_TYPE ORDER BY ANIMAL_TYPE

-- 동명 동물 수 찾기
SELECT NAME, COUNT(NAME) AS COUNT
FROM ANIMAL_INS 
GROUP BY NAME
HAVING COUNT(NAME) >= 2
ORDER BY NAME

-- 입양 시각 구하기(1)
SELECT HOUR(DATETIME) AS HOUR, COUNT(DATETIME) AS COUNT
FROM ANIMAL_OUTS
WHERE 9 <= HOUR(DATETIME) AND HOUR(DATETIME) <= 19
GROUP BY HOUR(DATETIME)
ORDER BY HOUR(DATETIME)