#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

class Navigation {
public:
    vector<string> cities;
    vector<vector<pair<int, int>>> adjList;  

    int getCityIndex(const string& city) {
        for (int i = 0; i < (int)cities.size(); i++) {
            if (cities[i] == city) return i;
        }
        return -1;
    }

    void addCity(const string& city) {
        if (getCityIndex(city) == -1) {
            cities.push_back(city);
            adjList.push_back(vector<pair<int, int>>());
        }
    }

    void addRoad(const string& city1, const string& city2, int dist) {
        int idx1 = getCityIndex(city1);
        int idx2 = getCityIndex(city2);
        if (idx1 == -1 || idx2 == -1) return;

        adjList[idx1].push_back({idx2, dist});
        adjList[idx2].push_back({idx1, dist});
    }

    void removeRoad(const string& city1, const string& city2) {
        int idx1 = getCityIndex(city1);
        int idx2 = getCityIndex(city2);
        if (idx1 == -1 || idx2 == -1) return;

        auto& edges1 = adjList[idx1];
        edges1.erase(
            remove_if(edges1.begin(), edges1.end(), [&](const pair<int,int>& p) { return p.first == idx2; }),
            edges1.end()
        );

        auto& edges2 = adjList[idx2];
        edges2.erase(
            remove_if(edges2.begin(), edges2.end(), [&](const pair<int,int>& p) { return p.first == idx1; }),
            edges2.end()
        );
    }

    void removeCity(const string& city) {
        int idx = getCityIndex(city);
        if (idx == -1) return;

        // Remove all edges to this city first
        for (int i = 0; i < (int)adjList.size(); i++) {
            if (i == idx) continue;
            auto& edges = adjList[i];
            edges.erase(
                remove_if(edges.begin(), edges.end(), [&](const pair<int,int>& p){ return p.first == idx; }),
                edges.end()
            );

            for (auto& p : edges) {
                if (p.first > idx) p.first--;
            }
        }

        cities.erase(cities.begin() + idx);
        adjList.erase(adjList.begin() + idx);
    }

    void displayGraph() {
        cout << "Graph adjacency list:\n";
        for (int i = 0; i < (int)cities.size(); i++) {
            cout << cities[i] << " -> ";
            for (auto& edge : adjList[i]) {
                cout << "(" << cities[edge.first] << ", " << edge.second << " km) ";
            }
            cout << "\n";
        }
    }

    // Dijkstra's algorithm to find shortest path and distance -- Written by AI (Couldnt understand really)
    void shortestPath(const string& startCity, const string& endCity) {
        int start = getCityIndex(startCity);
        int end = getCityIndex(endCity);
        if (start == -1 || end == -1) {
            cout << "One or both cities not found.\n";
            return;
        }

        int n = (int)cities.size();
        vector<int> dist(n, numeric_limits<int>::max());
        vector<int> parent(n, -1);
        dist[start] = 0;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [curDist, u] = pq.top(); pq.pop();
            if (curDist > dist[u]) continue;  

            for (auto& [v, w] : adjList[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[end] == numeric_limits<int>::max()) {
            cout << "No path from " << startCity << " to " << endCity << "\n";
            return;
        }

        // reconstruct path
        vector<int> path;
        for (int cur = end; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest path from " << startCity << " to " << endCity << ": ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << cities[path[i]];
            if (i != (int)path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal distance: " << dist[end] << " km\n";
    }
};

int main() {
    Navigation nav;

    nav.addCity("Lahore");
    nav.addCity("Islamabad");
    nav.addCity("Multan");
    nav.addCity("Peshawar");
    nav.addCity("Karachi");
    nav.addCity("Quetta");

    nav.addRoad("Lahore", "Islamabad", 270);
    nav.addRoad("Lahore", "Multan", 340);
    nav.addRoad("Islamabad", "Peshawar", 180);
    nav.addRoad("Multan", "Karachi", 900);
    nav.addRoad("Karachi", "Quetta", 700);
    nav.addRoad("Quetta", "Lahore", 1050);

    nav.displayGraph();

    cout << "\nFind shortest path from Lahore to Quetta:\n";
    nav.shortestPath("Lahore", "Quetta");

    return 0;
}
