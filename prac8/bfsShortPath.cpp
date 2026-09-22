#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void bfs(vector<vector<int>>& adj, int source) {
    int n = static_cast<int>(adj.size());

    vector<int> dist(n, -1);
    vector<int> parent(n, -1);

    queue<int> q;

    // Distance of source from itself is 0
    dist[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // If vertex has not been visited
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    cout << "\nMinimum distances from source " << source << ":\n";

    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " : ";

        if (dist[i] == -1)
            cout << "Not reachable";
        else
            cout << dist[i];

        cout << endl;
    }

    // Find shortest path from source to destination
    int destination;

    cout << "\nEnter destination vertex: ";
    cin >> destination;

    if (destination < 0 || destination >= n) {
        cout << "Invalid destination vertex.\n";
        return;
    }

    if (dist[destination] == -1) {
        cout << "No path exists from " << source
             << " to " << destination << endl;
        return;
    }

    vector<int> path;

    for (int v = destination; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "Shortest path: ";

    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\nMinimum distance = "
         << dist[destination] << endl;
}

int main() {
    int n, m;

    cout << "Enter number of vertices: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of vertices must be positive.\n";
        return 1;
    }

    cout << "Enter number of edges: ";
    cin >> m;

    if (m < 0) {
        cout << "Number of edges cannot be negative.\n";
        return 1;
    }

    vector<vector<int>> adj(n);

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid edge: vertices must be between 0 and " << n - 1 << ".\n";
            return 1;
        }

        // Undirected graph
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int source;

    cout << "Enter source vertex: ";
    cin >> source;

    if (source < 0 || source >= n) {
        cout << "Invalid source vertex.\n";
        return 1;
    }

    bfs(adj, source);

    return 0;
}
