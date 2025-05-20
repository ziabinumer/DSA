#include <iostream> 
#include <vector> // for dynamic array [tb used in ajacency list]
#include <string>
#include <queue> // for traversal
#include <climits> // to use INT_MAX
#include <algorithm> // functions like reverse
using namespace std;

/*
        MIND STORMING
        -> a vector of strings to store city names - can access later by index
            ["lhr", "isl", "rwd"]
            cities[1] = "isl"
        -> a vector containing a vectors of pair of integers to store roads:
         // index 0 to start cities[0] edges and so on
                [
                    [{end city index, distance}, {end, distance}],

                ]
            access methods:
                roads[0] gives cities[0] edges
                roads[0][0].first gives first edge of cities[0] edges and .first gives end index
        
        

*/

class Navigation {
public:
    vector<string> cities;
    vector<vector<pair<int, int>>> roads;

    int findCity(string city) {
        for (int i = 0; i < cities.size(); i++) {
            if (cities[i] == city) return i;
        }
        return -1;
    }

    void addCity(string city) {
        if (findCity(city) == -1) { // make sure city doesnt exist
            cities.push_back(city);
            roads.push_back({});
        }
    }

    // road reps an edge...
    // and since road is bi directional so its undirected edge
    void addRoad(string city1, string city2, int distance) {
        int i = findCity(city1);
        int j = findCity(city2);
        if (i == -1 || j == -1) return;

        roads[i].push_back({j, distance});
        roads[j].push_back({i, distance});
    }

    void removeRoad(string city1, string city2) {
        int i = findCity(city1);
        int j = findCity(city2);
        if (i == -1 || j == -1) return;

        // Remove from start city (city1) to end city (city2)
        for (int k = 0; k < roads[i].size(); k++) {
            if (roads[i][k].first == j) {
                roads[i].erase(roads[i].begin() + k);
                break;
            }
        }

        // Remove from city2 to city1
        for (int k = 0; k < roads[j].size(); k++) {
            if (roads[j][k].first == i) {
                roads[j].erase(roads[j].begin() + k);
                break;
            }
        }
    }

    // Remove a city - equivelent to removing an edge
    void removeCity(string city) {
        int cityIndex = findCity(city);
        if (cityIndex == -1) return;

        /*
            pseudo
            remove all egdes present to this city
            iterate over all cities and their edges
            check if edge or road exists to current city
            remove if exists and reduce index as a removal
            will cause the length of vector (roads pair) to decrease by 1

            IMPORTANT: (shifting indexes of cities down)
            when removing a city its a must to shift index down by 1
            as cities vector will decrease in length and so will indexes of cities
            

        */
        for (int i = 0; i < roads.size(); i++) {
            if (i == cityIndex) continue;
            for (int j = 0; j < roads[i].size(); j++) {
                if (roads[i][j].first == cityIndex) {
                    roads[i].erase(roads[i].begin() + j);
                    j--; 
                } else if (roads[i][j].first > cityIndex) {
                    roads[i][j].first--; // index decrease
                }
            }
        }

        cities.erase(cities.begin() + cityIndex);
        roads.erase(roads.begin() + cityIndex);
    }

    // print graph
    void showGraph() {
        cout << "Connected cities:\n";
        for (int i = 0; i < cities.size(); i++) {
            cout << cities[i] << " -> ";
            for (auto r : roads[i]) {
                cout << cities[r.first] << " (" << r.second << " km), ";
            }
            cout << endl;
        }
    }

    // Shortest path algo (Dijstra - single source)
    void findShortestPath(string startCity, string endCity) {
        int start = findCity(startCity);
        int end = findCity(endCity);

        if (start == -1 || end == -1) {
            cout << "City not found.\n";
            return;
        }

        /*
            distance initially infinite (can achieve using INT_MAX)
            store distance in dist vector
            create parent vector to remember paths
            use priorty queue

        */
        int n = cities.size();
        vector<int> dist(n, INT_MAX); // create a vector of n length and initialize each val large
        vector<int> parent(n, -1); // create another vector of n l and give each -1 (indicating no city)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            for (auto r : roads[u]) {
                int v = r.first;
                int w = r.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[end] == INT_MAX) {
            cout << "No path found from " << startCity << " to " << endCity << endl;
            return;
        }

        // Build path
        vector<int> path;
        for (int cur = end; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());

        // Show path
        cout << "Shortest path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << cities[path[i]];
            if (i != path.size() - 1) cout << " -> ";
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

    nav.showGraph();

    cout << "\nFinding shortest path from Lahore to Quetta:\n";
    nav.findShortestPath("Lahore", "Quetta");

    return 0;
}
