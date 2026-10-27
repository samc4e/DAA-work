#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    // g[u] = list of {v, weight}
    vector<vector<pair<int,int>>> g(n);

    cout << "Enter edges (u v w):\n";
    while (e--) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});   // undirected graph
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    // Start: every distance is "infinity", source is 0
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    // Min-heap of {distance, vertex} -> always gives the closest vertex first
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Old (longer) entry for u, skip it
        if (d > dist[u]) continue;

        // Relax: can we reach a neighbour cheaper by going through u?
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest distances from " << src << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " : ";
        if (dist[i] == INT_MAX) cout << "Not reachable";
        else cout << dist[i];
        cout << '\n';
    }
}
