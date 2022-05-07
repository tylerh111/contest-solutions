#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <iostream>
#include <algorithm>

enum color_t {
    NO_COLOR=0,
    RED = 1,
    BLUE = 2,
};



struct Graph {
    
    int V, E;
    std::vector<std::vector<int>> graph;
    std::vector<std::pair<std::string, color_t>>& vertices;
    
    Graph(std::vector<std::pair<std::string, color_t>>& _vertices, 
          std::vector<std::pair<int, int>>& _edges) : 
        V(_vertices.size()), E(_edges.size()),
        graph(V, std::vector<int>(V, 0)), vertices(_vertices)
    {   
        for (const auto& e : _edges) {
            graph[e.first][e.second] = true;
            graph[e.second][e.first] = true;
        }
        
    }
    
    
    template <typename T>
    bool bipartiteUtil(int src, T& red, T& blue, bool isqueue) {
        
        std::deque<int> deque;
        deque.push_back(src);
        
        while (!deque.empty()) {
            int u = isqueue ? deque.front() : deque.back();
            isqueue ? deque.pop_front() : deque.pop_back();
            
            // std::cout << u << ": (" << vertices[u].first << ", " << vertices[u].second << ")" << std::endl;
            
            for (auto it = graph[u].begin(); it != graph[u].end(); ++it) {
                // std::cout << "\t" << v << ": (" << vertices[v].first << ", " << vertices[v].second << ")" << std::endl;
                if (*it) {
                    int v = it - graph[u].begin();
                    color_t& color_u = vertices[u].second;
                    color_t& color_v = vertices[v].second;

                    if (color_v == NO_COLOR) {
                        if (color_u == BLUE) {
                            color_v = RED;
                            red.insert(vertices[v].first);
                        }
                        else {
                            color_v = BLUE;
                            blue.insert(vertices[v].first);
                        }
                        
                        deque.push_back(v);
                    }
                    
                    if (color_u == color_v) return false;
                }
            }
        }
        
        return true;
    }
    
    
    
    bool bipartite(int src, std::set<std::string>& red, std::set<std::string>& blue) {
        vertices[src].second = RED;
        red.insert(vertices[src].first);
        
        return bipartiteUtil<std::set<std::string>>(src, red, blue, true); // queue (BFS)
        // return bipartiteUtil<std::set<std::string>>(src, red, blue, false); // stack (DFS)
    }
    
    
    
    
    std::tuple<std::set<std::string>, std::set<std::string>> parts() {
        
        std::set<std::string> red;
        std::set<std::string> blue;
        
        for (const auto& v : vertices) {
            if      (v.second == RED)  red.insert(v.first);
            else if (v.second == BLUE) blue.insert(v.first);
        }
        
        return std::make_tuple(red, blue);
    }
    
    
    void print() {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v)
                std::cout << graph[u][v] << ' ';
            std::cout << '\n';
        }
        std::cout << std::flush;
    }
    
};



void print_set(std::set<std::string>& set) {
    for (const auto& str : set)
        std::cout << str << '\n';
}



int main() {
    
    // speed up for input reading
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int lines;
    std::cin >> lines;
    
    int p = 0;
    std::map<std::string, int> names;
    
    // vertices hold the name and color
    std::vector<std::pair<std::string, color_t>> vertices;
    std::vector<std::pair<int, int>> edges(lines);
    
    std::string p1, p2;
    int v1, v2;
    
    for (int i = 0; i < lines; ++i) {
        std::cin >> p1 >> p2;
        
        auto search = names.find(p1);
        if (search == names.end()) {
            v1 = names[p1] = p++;
            vertices.push_back({p1, NO_COLOR});
        }
        else v1 = names[p1];
        
        search = names.find(p2);
        if (search == names.end()) {
            v2 = names[p2] = p++;
            vertices.push_back({p2, NO_COLOR});
        }
        else v2 = names[p2];
        
        edges[i] = {v1, v2};
    }
    
    Graph g(vertices, edges);
    // g.print();
    
    std::set<std::string> red;
    std::set<std::string> blue;
    bool is_bipartite = g.bipartite(0, red, blue);
    
    if (is_bipartite) {
        std::cout << "Plausible\n";
        
        // auto parts = g.parts();
        // auto& red = std::get<0>(parts);
        // auto& blue = std::get<1>(parts);
        
        if      (red.size() < blue.size()) print_set(blue);
        else if (red.size() > blue.size()) print_set(red);
        else if (vertices[names.begin()->second].second == RED)  print_set(red);
        else if (vertices[names.begin()->second].second == BLUE) print_set(blue);
        
    }
    else std::cout << "Busted!\n";
    return 0;
}
