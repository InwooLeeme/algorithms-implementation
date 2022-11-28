struct rabinkarp {
  typedef modnum<998244353> mnum1;
  typedef modnum<1000000007> mnum2;
  typedef pair<mnum1, mnum2> shash;
  int STRING_SZ;
  const mnum1 HASH1 = 3137;
  const mnum2 HASH2 = 1009;
  vector<shash> hashes;
  vector<mnum1> hash1pows;
  vector<mnum2> hash2pows;
  rabinkarp() {}
  rabinkarp(const string& s) {
    STRING_SZ = sz(s);
    hash1pows.resize(STRING_SZ+1);
    hash1pows[0] = 1;
    for(int i = 1; i <= STRING_SZ; i++) hash1pows[i] = hash1pows[i-1] * HASH1;
    hash2pows.resize(STRING_SZ+1);
    hash2pows[0] = 1;
    for(int i = 1; i <= STRING_SZ; i++) hash2pows[i] = hash2pows[i-1] * HASH2;
    hashes.resize(STRING_SZ+1);
    for(int i = 0; i < sz(s); i++) {
      hashes[i+1].first = hashes[i].first * HASH1 + s[i];
      hashes[i+1].second = hashes[i].second * HASH2 + s[i];
    }
  }
  inline pii getHash(int lhs, int rhs) {
    // [lhs, rhs)
    mnum1 a = hashes[rhs].first - hashes[lhs].first * hash1pows[rhs-lhs];
    mnum2 b = hashes[rhs].second - hashes[lhs].second * hash2pows[rhs-lhs];
    return {(int)a, (int)b};
  }
  inline pii hashStr(const string& s) {
    mnum1 a = 0;
    mnum2 b = 0;
    for(auto x: s) {
      a = a * HASH1 + x;
      b = b * HASH2 + x;
    }
    return {(int)a, (int)b};
  }
};
