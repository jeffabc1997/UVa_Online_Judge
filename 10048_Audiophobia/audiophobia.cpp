#include<iostream>
#include<vector>
// #include<algorithm>
#include<set>
#include<utility>
// #include<climits>
using namespace std;

const int pain = 1e9;

/* DFS + Binary Search to decide max weight */ // (But maybe can also be solved by Floyd-Warshall)
void dfs(vector<vector<pair<int, int>>>& adj, vector<int>& visited, int node, int limit_db) {
    visited[node-1] = 1;
    int v, weight;
    for(auto neighbor: adj[node-1]) {
        v = neighbor.first;
        weight = neighbor.second;
        if((visited[v-1] == 0) && (weight <= limit_db)) {
            dfs(adj, visited, v, limit_db);
        }
    }
    visited[node-1] = 2;

}

bool connected(vector<vector<pair<int, int>>>& adj, int source, int dest ,int limit_db) {

    int n = adj.size();
    vector<int> visited(n, 0);
    dfs(adj, visited, source, limit_db);
    if(visited[dest-1] == 0) {
        return false;
    }
    return true;
}

int binary_query(vector<vector<pair<int, int>>>& adj, vector<int>& ordered_db, int source, int dest) {
    int left = 0, right = ordered_db.size()-1, mid, limit_db, accepted_db = pain;
    while(left <= right) {
        mid = (left + right) / 2; // use mid to choose edge weight
        limit_db = ordered_db[mid];
        // cout << "Check Mid " << mid << endl;
        if(connected(adj, source, dest, limit_db)) {
            if(limit_db < accepted_db) {
                accepted_db = limit_db;
            }
            
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if(accepted_db >= pain) {
        cout << "no path" << endl;
        
    } else {
        cout << accepted_db << endl;
    }
    return accepted_db;
}
void session(int n, int m, int q) {
    
    vector<int> source(q);
    vector<int> dest(q);
    vector<vector<pair<int, int>>> adj(n);
    set<int> unique_sound;
    for(int i = 0, a, b, db; i < m; i++) {
        cin >> a >> b >> db; 
        if(db >= pain) {
            continue;
        }
        adj[a-1].push_back({b, db});
        adj[b-1].push_back({a, db});
        unique_sound.insert(db);
    }
    
    for(int i = 0; i < q; i++) {
        cin >> source[i] >> dest[i];
    }
    vector<int> ordered_db(unique_sound.begin(), unique_sound.end()); // it's in non-decreasing order
    // for(int x: ordered_db) {
    //     cout << x << " "; 
    // }
    for(int i = 0; i < q; i++) {
        binary_query(adj, ordered_db, source[i], dest[i]);
    }

}

int main() {
    int n = 0, m = 0, q = 0, counter = 1;
    while(1) {
        
        cin >> n >> m >> q;
        if(n == 0) {
            return 0;
        }
        if(counter > 1) {
            cout << endl; // deal with line break
        }
        cout << "Case #" << counter++ << endl;
        session(n, m, q);
        
    }
    
    return 0;
}