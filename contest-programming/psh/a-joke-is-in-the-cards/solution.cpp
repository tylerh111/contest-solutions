#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>
#include <tuple>


using card_t = std::tuple<int, int, int>;
constexpr card_t card_dflt = std::make_tuple(0, 0, 0);

std::ostream& operator<<(std::ostream& os, const card_t& c)
{
    os << std::get<0>(c) << ' ' << std::get<1>(c) << ' ' << std::get<2>(c);
    return os;
}

auto operator==(const card_t& lhs, const card_t& rhs) {
    return (std::get<0>(lhs) == std::get<0>(rhs) &&
            std::get<1>(lhs) == std::get<1>(rhs) &&
            std::get<2>(lhs) == std::get<2>(rhs));
}

auto operator<(const card_t& lhs, const card_t& rhs) {
    return (std::get<0>(lhs) <= std::get<0>(rhs) &&
            std::get<1>(lhs) <= std::get<1>(rhs) &&
            std::get<2>(lhs) < std::get<2>(rhs));
}

auto operator-(const card_t& lhs, const card_t& rhs) {
    return std::make_tuple(
            std::get<0>(lhs) - std::get<0>(rhs),
            std::get<1>(lhs) - std::get<1>(rhs),
            std::get<2>(lhs) - std::get<2>(rhs));
}


bool isCardNegative(const card_t& c) {
    return std::get<0>(c) < 0 || std::get<1>(c) < 0 || std::get<2>(c) < 0;
}


template <typename T>
using card_map = std::map<card_t, T>;


bool isIdealCard(std::vector<card_t>& cards, 
                 std::vector<card_map<bool>>& memo, 
                 int i, card_t c)
{
    // base cases
    if (isCardNegative(c)) return false;
    if (c == card_dflt) return true;
    if (i < 0) return false;
    
    // if exists return memoized result
    auto isIdeal = memo[i].find(c);
    if (isIdeal != memo[i].end()) return isIdeal->second;
    
    // if not calculate solution
    return memo[i][c] = isIdealCard(cards, memo, i-1, c) ||
                        isIdealCard(cards, memo, i-1, c-cards[i]);
}




bool hasIdealDeck(std::vector<card_t>& cards, int i_p, int i_w, int i_h) {
    std::vector<card_map<bool>> memo(cards.size());
    return isIdealCard(cards, memo, cards.size()-1, std::make_tuple(i_p, i_w, i_h));
}



int main() {
    
    int t;
    std::cin >> t;
    
    int i_p, i_w, i_h;
    int c;
    
    int p, w, h;
    
    for (int i = 0; i < t; ++i) {
        
        // get info for test case
        std::cin >> i_p >> i_w >> i_h >> c;
        
        // fill cards
        std::vector<card_t> cards(c);
        for (int j = 0; j < c; ++j) {
            std::cin >> p >> w >> h;
            cards[j] = {p, w, h};
        }
        
        // find if deck exists
        if (hasIdealDeck(cards, i_p, i_w, i_h)) std::cout << "guffaw\n";
        else std::cout << "groan\n";
    }
    
    return 0;
}
