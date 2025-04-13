---
marp : true
theme : gradient
class : invert
paginate : true
math: mathjax
---

# [SBS](https://github.com/minjn12/2025gssort/blob/main/)

###### 23002 강민준

---

# [Bogo Sort](https://en.wikipedia.org/wiki/Bogosort)란?

---

# [Bogo Sort](https://en.wikipedia.org/wiki/Bogosort)란,
## "정렬이 될 때까지 무작위로 섞는" 매우 비효율적인 정렬 알고리즘

##### 1. 배열이 정렬되었는지 확인
##### 2. 정렬되지 않았으면 셔플
##### 3. 다시 확인

```python
while not is_sorted(arr):
    shuffle(arr)
```

---

## [test01.py](https://github.com/minjn12/2025gssort/blob/main/test01.py) <!--web-->
## [test01.py](C:\ps\sort\test01.py) <!--local-->

---

# [Bogo Sort](https://en.wikipedia.org/wiki/Bogosort)

| 복잡도 종류       | 값                          |
|------------------|-----------------------------|
| 최악 시간복잡도   | 무제한 (랜덤화 버전), O((n+1)!) (결정화 버전) |
| 최선 시간복잡도   | O(n)                        |
| 평균 시간복잡도   | O((n+1)!)                   |
| 공간복잡도       | O(1)                        |

#### 기대 시도 수 n!
#### n이 조금만 커져도 정렬 불가능에 가깝다

#### n = 12일 때, 1초에 한번씩 정렬할 경우 15.18년 소요

---

# [SBS](https://github.com/minjn12/2025gssort/blob/main/)란? [Smart Bogo Sort](https://github.com/minjn12/2025gssort/blob/main/)

---

# [SBS](https://github.com/minjn12/2025gssort/blob/main/)? 
## [Bogo Sort](https://en.wikipedia.org/wiki/Bogosort)를 일부 개선한 정렬
## [Bogo Sort](https://en.wikipedia.org/wiki/Bogosort)를 부분적으로 활용하자

---

# [SBS](https://github.com/minjn12/2025gssort/blob/main/)? 
#### 1. 앞에서부터 차례대로 원소 확인
#### 2. 현재의 원소가 뒤의 모든 원소보다 작거나 같으면 고정
#### 3. 고정된 부분을 제외하고 무작위 셔플


```python
while not is_sorted(arr):
    fixed = count_fixed_prefix(arr)
    arr[fixed:] = shuffle(arr[fixed:])
```
###### 예시) [1, 4, 3, 2] 의 경우 1을 고정시키고 [4, 3, 2]에 대해서 재정렬 

---

## [test02.py](https://github.com/minjn12/2025gssort/blob/main/test02.py) <!--web-->
## [test02.py](C:\ps\sort\test02.py) <!--local-->

---

# [SBS](https://github.com/minjn12/2025gssort/blob/main/)
| 복잡도 종류       | SmartBogoSort                            | BogoSort                                 |
|------------------|------------------------------------------|------------------------------------------|
| 최선 시간복잡도   | O(n)                                     | O(n)                                     |
| 평균 시간복잡도   | O((n/2)!) ~ O(n²)                        | O(n × n!)                                |
| 최악 시간복잡도   | O(n × n!)                                | 무제한 (랜덤화 버전), O((n+1)!) (결정화 버전) |
| 공간복잡도       | O(1)                                     | O(1)                                     |

---

# 실행 코드

## [main.cpp](https://github.com/minjn12/2025gssort/blob/main/main.cpp)

---

# 다른 정렬과의 속도 비교

---

# 다른 정렬과의 속도 비교
#### 대조군 | 버블 정렬 | 힙 정렬

## 실행 코드 
#### [a.cpp](https://github.com/minjn12/2025gssort/blob/main/a.cpp)
## 결과값
#### [timing_results.csv](https://github.com/minjn12/2025gssort/blob/main/timing_results.csv)

---

<img src=".\coding.png" 
     alt="기본 이미지"
     onerror="this.onerror=null; this.src='https://github.com/minjn12/2025gssort/blob/main/coding.png';" />

---

# 다른 정렬과의 속도 비교

| 알고리즘         | 최선         | 평균                      | 최악             | 공간 복잡도 |
|------------------|--------------|---------------------------|------------------|--------------|
| [SBS](https://github.com/minjn12/2025gssort/blob/main/)    | O(n)         | O((n/2)!) ~ O(n²)         | O(n × n!)        | O(1)         |
| Bubble Sort      | O(n)         | O(n²)                     | O(n²)            | O(1)         |
| Heap Sort        | O(n log n)   | O(n log n)                | O(n log n)       | O(1)         |

---

## [SBS](https://github.com/minjn12/2025gssort/blob/main/)의 추세선

<div style="display: flex; align-items: center; gap: 10px;">

  <div style="flex: 3;">
    <img src=".\output.png" 
     alt="기본 이미지"
     style="width: 100%;"
     onerror="this.onerror=null; this.src='https://github.com/minjn12/2025gssort/blob/main/output.png';" />
  </div>

  <div style="flex: 1; font-size: 18px;">
    
  ## 🔴 지수 함수 피팅  
  $$ y = 8.10 \times 10^4 \cdot e^{0.0020 \cdot N}$$
  
  
  ## 🟢 거듭제곱 함수 피팅  
  $$ y = 8.11 \times 10^{-7} \cdot N^{3.88} $$

  </div>

</div>

---

## [SBS](https://github.com/minjn12/2025gssort/blob/main/) 추세선

#### 🔴 지수 함수 피팅 (Exponential Fit)

$$ y = 4.09 \times 10^{-3} \cdot e^{0.0121 \cdot N}$$

#### 🟢 거듭제곱 함수 피팅 (Power Fit)

$$ y = 2.11 \times 10^{-10} \cdot N^{5.98}$$

<br>

## 거듭제곱 함수 피팅의 R² 값이 더 높아, 실제 평균 실행 시간에 더 잘 맞음  


---

# 다른 정렬과의 비교

<img src=".\output2.png" 
     alt="기본 이미지"
     style="width: 1000;"
     onerror="this.onerror=null; this.src='https://github.com/minjn12/2025gssort/blob/main/output2.png';" /> <!--다른 정렬과의 비교 추세선-->

---

## 매우 비효율적임을 확인.

---

## 시간복잡도 계산

---

## 기대 시간복잡도

#### [SBS](https://github.com/minjn12/2025gssort/blob/main/)는 길이 $n$짜리 배열에 대해 다음과 같은 수식을 따름.


$$
T(n) = \sum_{k=1}^{n} (n-k)! = (n-1)! + (n-2)! + \cdots + 1! + 0!
$$

## 평균적 근사

#### 평균적으로 절반 정도가 고정된다고 가정하면

$$
T(n) \approx O\left(\left(\frac{n}{2}\right)!\right)
$$

## 최악의 경우

$$
T(n) = O(n \cdot n!)
$$

---

### 예시: \( n = 10 \)일 때 계산

-  T(10) = $\sum_{k=1}^{10} (10-k)! = 9! + 8! + \cdots + 0! = \textbf{409,114}$
- 평균 고정 가정: $\left(\frac{10}{2}\right)! = 5! = \textbf{120}$
- 최악의 경우: $10 \cdot 10! = \textbf{36,288,000}$

###  해석 요약

| 구분       | 수식                                           | 계산 예시 (n=10) |
|------------|------------------------------------------------|------------------|
| 기대값     | $\sum_{k=1}^{n} (n-k)!$                    | $409,114$          |
| 평균 근사  | $O\left(\left(\frac{n}{2}\right)!\right)$  | $120$              |
| 최악의 경우 | $O(n \cdot n!)$                            | $36,288,000$  

---

# 감사합니다


