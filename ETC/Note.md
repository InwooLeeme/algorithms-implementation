## 문제 풀때 고려해야할 사항들 (계속해서 추가 예정)

-> 2차원 격자 
1. 체스판에 비유해서 도달 가능성을 판단할 수 있나?
  > 칸의 홀-짝 판별성 : ((i + j) & 1) <br> -> 이분매칭할 때도 쓰임
  > 대각선으로만 이동해야할 때(Ex. 비숍)의 최단거리 : max(abs(y1 - y2),abs(x1 - x2)) <br>
  