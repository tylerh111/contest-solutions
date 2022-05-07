
#include <iostream>
#include <vector>
#include <deque>
#include <numeric>
#include <algorithm>

std::vector<int> create_sets(int n) {
    std::vector<int> res(n);
    std::iota(res.begin(), res.end(), 0);
    return res;
}

int root(std::vector<int> &p, int x) {
    return x == p[x] ? x : (p[x] = root(p, p[x]));
}

void union_sets(std::vector<int> &p, int a, int b) {
    a = root(p, a);
    b = root(p, b);
    p[b] = a;
}


template <typename T>
void pretty_print(const std::vector<T>& v, const int n, const int m, char delim = '\0') {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::clog << v[i*m+j];
            if (delim != '\0') std::clog << delim;
        }
        std::clog << '\n';
    }
}

int solve(const int n, const int m, std::vector<char>& grid) {

    // find all land (L) positions
    // find number of water (W) positions
    std::deque<int> land_pos;
    std::deque<int> water_pos;

    int i = 0;
    int land = 0;
    for (auto& point : grid) {
        switch (point) {
        case 'L':
            land++;
            land_pos.push_back(i);
            break;
        case 'W':
            water_pos.push_back(i);
            break;
        }
        ++i;
    }

    if (land == 0) return 0;

    // grid_mark : visited list
    // masses    : disjoint set of land and water
    std::vector<bool> grid_mark(grid.size(), false);
    auto masses = create_sets(grid.size());
    
    // expand mass at pos to pos_next if a cloud
    auto expand_mass = [&] (auto& mass_queue, char mass, int pos, int pos_next) {
        if (grid[pos_next] == 'C' || grid[pos_next] == mass) {
            // std::clog << "expanding: " << pos << " to " << pos_next << '\n';
            union_sets(masses, pos, pos_next);
            grid[pos_next] = mass;
            mass_queue.push_back(pos_next);
        }
    };

    auto expand = [&] (auto& mass_queue, char mass) {
        // expand all known masses in mass queue
        while (mass_queue.size() > 0) {
            auto pos = mass_queue.front();
            mass_queue.pop_front();
            if (grid_mark[pos]) continue;
            grid_mark[pos] = true;

            // expand land in all directions (L,R,D,U)
            if ((pos%m) != m-1) expand_mass(mass_queue, mass, pos, pos+1);
            if ((pos%m) != 0)   expand_mass(mass_queue, mass, pos, pos-1);
            if ((pos/m) != n-1) expand_mass(mass_queue, mass, pos, ((pos/m)+1)*m + (pos%m));
            if ((pos/m) != 0)   expand_mass(mass_queue, mass, pos, ((pos/m)-1)*m + (pos%m));

            // pretty_print(masses, n, m, ','); std::clog << '\n';
        }
    };
    
    // expand land and water (in order)
    expand(land_pos, 'L');
    expand(water_pos, 'W');

    // normalize the disjoint set
    for (std::size_t i = 0; i < masses.size(); ++i) {
        root(masses, i);
    }
    pretty_print(masses, n, m, ','); std::clog << '\n';

    // get the minimum number of land masses
    std::sort(begin(masses), end(masses));
    auto last_unique = std::unique(begin(masses), end(masses));

    land = 0;
    for (auto it = begin(masses); it != last_unique; ++it) {
        if (grid[*it] == 'L') land++;
    }

    return land;
}


int main() {

    int n,m;
    std::cin >> n >> m;
    
    std::vector<char> grid(n*m);
    for (auto& point : grid) {
        std::cin >> point;
    }

    pretty_print(grid, n, m);
    std::clog << '\n';

    std::cout << solve(n, m, grid) << '\n';

    pretty_print(grid, n, m);
    std::clog << '\n';
}

