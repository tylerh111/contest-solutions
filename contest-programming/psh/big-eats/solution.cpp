
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

long solve(
    const std::vector<long>& cat_a, 
    const std::vector<long>& cat_b,
    long m) 
{

    auto best = std::numeric_limits<long>::max();

    auto ai = cat_a.begin();
    auto bi = cat_b.rbegin();

    while(ai != cat_a.end() && bi != cat_b.rend()) {
        auto res = *ai + *bi;

        // check if we found a better combination
        if (std::abs(res - m) < std::abs(best))
            best = res - m;

        // pick new item
        if (res < m) ai++;
        else if (m < res) bi++;
        else break;
    }

    return m + best;
}


int main() {

    long a,b,m;
    std::cin >> a >> b >> m;

    std::vector<long> cat_a(a);
    std::vector<long> cat_b(b);

    for (auto& i : cat_a) {
        std::cin >> i;
    }
    std::sort(begin(cat_a), end(cat_a));

    for (auto& i : cat_b) {
        std::cin >> i;
    }
    std::sort(begin(cat_b), end(cat_b));

    std::cout << solve(cat_a, cat_b, m) << '\n';

}
