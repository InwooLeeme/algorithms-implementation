## 빡구현때 자주 나오는 유형을 정리할 거임

#### 배열의 이동
https://blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=coding-abc&logNo=221941314324&categoryNo=18&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView

### 2차원을 배열을 1차원으로
in [n x m] matrix
1. (i, j) => i*m + j
2. i*m + j / m = i,j = i*m + j % m
