vvi Rotate(vvi& v){ // Rotate 90 degree NxM -> MxN
	int N = v.size(), M = v[0].size();
	vvi ret(M, vi(N));
	for(int j = 0; j < M; j++){
		for(int i = 0; i < N; i++){
			ret[j][i] = v[N - 1 - i][j];
		}
	}
	return ret;
}
