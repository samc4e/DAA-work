#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<pair<int,int>>> g(n);

    while (e--) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<bool> vis(n);
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    pq.push({0, 0});
    int mst = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (vis[u]) continue;

        vis[u] = true;
        mst += w;

        for (auto [v, wt] : g[u])
            if (!vis[v])
                pq.push({wt, v});
    }

    cout << "MST weight = " << mst << '\n';
}

