# BS (Bidirectional Search, 양방향 탐색)

> 시작 노드에서 시작하는 정방향 탐색과, 목표 지점에서 거꾸로 올라오는 역방향 탐색을 동시에 진행하는 탐색방법

너비 우선 탐색보다 훨씬 적은 수의 정점만 방문하고도 답을 찾을 수 있음

역방향 간선이 많거나, 찾아내기 어려운 경우는 양방향 탐색을 사용하기 어려움

너비 우선 탐색보다 메모리, 시간 효율적

예제: 3x3 퍼즐 https://www.acmicpc.net/problem/1525
  
  
   
  
# IDS ( Iteratively Deepening Search, 점점 깊어지는 탐색)

> 목표 노드가 찾아질 때까지 깊이 제한을 1 씩 증가시키면서 연속적인 깊이우선 탐색을 수행하는 탐색방법

휴리스틱을 이용하여 가지치기도 이용 → limit 정해준다

너비우선 / 양방향 탐색 다 못 쓸 경우 사용
  
  
  
  
#### 비교 표

![img](https://k.kakaocdn.net/dn/PvmqX/btqzhqZ2O3O/lBWwSL4H1K977OJ1B5wmSK/img.png)


참고:

http://www.aistudy.com/heuristic/search_yoo.htm

https://going-to-end.tistory.com/entry/%EC%9D%B8%EA%B3%B5%EC%A7%80%EB%8A%A5-Uninformed-Search-BFS-DFS-Depth-limted-Search-Iterative-Deepening-Search-Bi-directional-Search-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98%EB%93%A4%EC%9D%98-%EC%B0%A8%EC%9D%B4%EC%A0%90
