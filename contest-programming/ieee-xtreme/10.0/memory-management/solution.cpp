#include <cmath>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <limits>


std::ostream& operator<<(std::ostream& os, const std::pair<uint32_t, uint32_t>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}



template <typename T>
void print_collection(const T& collection) {
    std::cout << "[";
    for (const auto& x : collection) {
        std::cout << x << ", ";
    }
    std::cout << "]";
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int t;
    std::cin >> t;
    
    for (int i = 0; i < t; ++i) {
        
        size_t p, n;
        uint32_t s;
        std::cin >> p >> s >> n;
        
        std::vector<uint32_t> addr_pages(n);
        std::map<uint32_t, uint32_t> page_usage;
        
        // read address and calculate pages
        uint32_t addr;
        for (auto& page : addr_pages) {
            std::cin >> addr;
            page = std::floor(addr / s);
            page_usage[page] = 0;
        }
        
        
        // test lifo and lru
        uint32_t allocs_lifo = 0;
        uint32_t allocs_lru = 0;
        
        std::deque<uint32_t> page_queue_lifo;
        
        // tuple <0> := page
        // tuple <1> := usage
        // tuple <2> := last used
        std::deque<std::tuple<uint32_t, uint32_t, size_t>> page_queue_lru;
        
        std::set<uint32_t> page_set_lifo;
        std::set<uint32_t> page_set_lru;
        
        size_t j = 0;
        for (const auto page : addr_pages) {
            
            // std::cout << "current page = " << page;
            
            auto search_lifo_pages = page_set_lifo.find(page);
            auto search_lru_pages = page_set_lru.find(page);
            
            // check if page exists in lifo pages
            if (search_lifo_pages == page_set_lifo.end()) {
                
                // if set of pages is full
                if (page_set_lifo.size() == p) {
                    uint32_t rpage = page_queue_lifo.front();
                    page_queue_lifo.pop_front();
                    page_set_lifo.erase(rpage);
                    // std::cout << "LIFO: old page = " << rpage << ", new page = " << page << std::endl;
                    allocs_lifo++;
                }
                
                page_queue_lifo.push_back(page);
                page_set_lifo.insert(page);
                // std::cout << "\tLIFO: added page " << page;
            }
            
            
            // check if page exists in lru pages
            if (search_lru_pages == page_set_lru.end()) {
                
                // if set of pages is full
                if (page_set_lru.size() == p) {
                    
                    // get page to be removed
                    auto val = page_queue_lru.back();
                    page_queue_lru.pop_back();
                    page_set_lru.erase(std::get<0>(val));
                    // std::cout << "LRU:  old page = " << val.first << ", new page = " << page << std::endl;
                    
                    allocs_lru++;
                }
                
                page_queue_lru.push_back({page, page_usage[page], j});
                page_set_lru.insert(page);
                // std::cout << "\tLRU:  added page " << page;
            }
            
            auto usage = std::find_if(page_queue_lru.begin(), page_queue_lru.end(),
                        [page](const auto& val) {
                            if (std::get<0>(val) == page) return true;
                            return false;
                        });
            
            
            std::get<1>(*usage) = ++page_usage[page];
            std::get<2>(*usage) = j;
            std::make_heap(page_queue_lru.begin(), page_queue_lru.end(), 
                          [](const auto& a, const auto& b) {
                              return std::get<1>(a) < std::get<1>(b) &&
                                  std::get<2>(a) < std::get<2>(b);
                          });
            
            
            // std::cout << std::endl;
            // std::cout << "\t\tLIFO SET: "; print_collection(page_set_lifo);
            // std::cout << "\t\tLRU  SET: "; print_collection(page_set_lru);
            // std::cout << std::endl;
            // std::cout << "\t\tLIFO QUEUE: "; print_collection(page_queue_lifo);
            // std::cout << "\t\tLRU  QUEUE: "; print_collection(page_queue_lru);
            // std::cout << std::endl;
            
            ++j;
        }
        
        
        // output info
        if (allocs_lifo > allocs_lru)
            std::cout << "yes " << allocs_lifo << " " << allocs_lru << '\n';
        else
            std::cout << "no " << allocs_lifo << " " << allocs_lru << '\n';
        
    }
    
    
    return 0;
}
