#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;

struct State {
    VI Q, A, B;
    bool operator==(const State& o) const {
        return Q == o.Q && A == o.A && B == o.B;
    }
};

struct StateHash {
    size_t operator()(const State& s) const noexcept {
        // 간단한 벡터 해시 결합
        auto hv = [](const VI& v) {
            size_t h = 1469598103934665603ull; // FNV offset basis
            for (int x : v) {
                h ^= std::hash<int>{}(x);
                h *= 1099511628211ull; // FNV prime
            }
            return h;
        };
        size_t h = hv(s.Q);
        h ^= (hv(s.A) + 0x9e3779b97f4a7c15ull + (h<<6) + (h>>2));
        h ^= (hv(s.B) + 0x9e3779b97f4a7c15ull + (h<<6) + (h>>2));
        return h;
    }
};

static inline VI rotate_queue(const VI& q, int k) {
    if (q.empty()) return q;
    int n = (int)q.size();
    k %= n;
    if (k == 0) return q;
    VI res;
    res.reserve(n);
    // q[k:] + q[:k]
    res.insert(res.end(), q.begin() + k, q.end());
    res.insert(res.end(), q.begin(), q.begin() + k);
    return res;
}

int min_ops(const VI& start_q) {
    int N = (int)start_q.size();
    VI target_q = start_q;
    sort(target_q.begin(), target_q.end());

    State start{start_q, {}, {}};

    deque<pair<State,int>> dq;
    dq.push_back({start, 0});
    unordered_set<State, StateHash> visited;
    visited.insert(start);

    while (!dq.empty()) {
        auto cur = dq.front(); dq.pop_front();
        State s = cur.first;
        int d = cur.second;

        const VI &Q = s.Q, &A = s.A, &B = s.B;

        // QA: Q의 앞 n개를 A로
        if (!Q.empty()) {
            for (int n = 1; n <= (int)Q.size(); ++n) {
                VI moved(Q.begin(), Q.begin() + n);
                VI newQ(Q.begin() + n, Q.end());
                VI newA = A; newA.insert(newA.end(), moved.begin(), moved.end());
                State ns{newQ, newA, B};
                if (!visited.count(ns)) {
                    // 파이썬 코드의 논리를 그대로: newQ == target_q && A, B(원본) 비어있음 검사
                    if (newQ == target_q && A.empty() && B.empty())
                        return d + 1;
                    visited.insert(ns);
                    dq.push_back({ns, d + 1});
                }
            }
        }

        // QB: Q의 앞 n개를 B로
        if (!Q.empty()) {
            for (int n = 1; n <= (int)Q.size(); ++n) {
                VI moved(Q.begin(), Q.begin() + n);
                VI newQ(Q.begin() + n, Q.end());
                VI newB = B; newB.insert(newB.end(), moved.begin(), moved.end());
                State ns{newQ, A, newB};
                if (!visited.count(ns)) {
                    if (newQ == target_q && A.empty() && B.empty())
                        return d + 1;
                    visited.insert(ns);
                    dq.push_back({ns, d + 1});
                }
            }
        }

        // QQ: Q를 회전
        if ((int)Q.size() >= 2) {
            int L = (int)Q.size();
            for (int k = 1; k < L; ++k) {
                VI newQ = rotate_queue(Q, k);
                State ns{newQ, A, B};
                if (!visited.count(ns)) {
                    if (newQ == target_q && A.empty() && B.empty())
                        return d + 1;
                    visited.insert(ns);
                    dq.push_back({ns, d + 1});
                }
            }
        }

        // AQ: A의 뒤 n개를 Q로 (뒤에서 꺼내 앞서서 쌓는 대신, Q 뒤에 붙임)
        if (!A.empty()) {
            for (int n = 1; n <= (int)A.size(); ++n) {
                VI moved(A.end() - n, A.end());
                VI newA(A.begin(), A.end() - n);
                VI newQ = Q; newQ.insert(newQ.end(), moved.begin(), moved.end());
                State ns{newQ, newA, B};
                if (!visited.count(ns)) {
                    if (newQ == target_q && A.empty() && B.empty())
                        return d + 1;
                    visited.insert(ns);
                    dq.push_back({ns, d + 1});
                }
            }
        }

        // BQ: B의 뒤 n개를 Q로
        if (!B.empty()) {
            for (int n = 1; n <= (int)B.size(); ++n) {
                VI moved(B.end() - n, B.end());
                VI newB(B.begin(), B.end() - n);
                VI newQ = Q; newQ.insert(newQ.end(), moved.begin(), moved.end());
                State ns{newQ, A, newB};
                if (!visited.count(ns)) {
                    if (newQ == target_q && A.empty() && B.empty())
                        return d + 1;
                    visited.insert(ns);
                    dq.push_back({ns, d + 1});
                }
            }
        }

        // AB: A의 뒤 n개를 B로
        if (!A.empty()) {
            for (int n = 1; n <= (int)A.size(); ++n) {
                VI moved(A.end() - n, A.end());
                VI newA(A.begin(), A.end() - n);
                VI newB = B; newB.insert(newB.end(), moved.begin(), moved.end());
                State ns{Q, newA, newB};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    dq.push_back({ns, d + 1});
                }
            }
        }

        // BA: B의 뒤 n개를 A로
        if (!B.empty()) {
            for (int n = 1; n <= (int)B.size(); ++n) {
                VI moved(B.end() - n, B.end());
                VI newB(B.begin(), B.end() - n);
                VI newA = A; newA.insert(newA.end(), moved.begin(), moved.end());
                State ns{Q, newA, newB};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    dq.push_back({ns, d + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (true) {
        if (!getline(cin, line)) break;
        if (line == "0") break;

        stringstream ss(line);
        vector<int> parts;
        int x;
        while (ss >> x) parts.push_back(x);
        if (parts.empty()) continue;
        if (parts[0] == 0) break;

        int N = parts[0];
        vector<int> q;
        for (int i = 1; i < (int)parts.size(); ++i) q.push_back(parts[i]);

        cout << min_ops(q) << "\n";
    }
    return 0;
}
