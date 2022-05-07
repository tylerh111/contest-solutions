#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>



uint64_t get_lower_8_bytes(char* buf) {
   return (static_cast<uint64_t>(buf[0]) << 56)
        | (static_cast<uint64_t>(buf[1]) << 48)
        | (static_cast<uint64_t>(buf[2]) << 40)
        | (static_cast<uint64_t>(buf[3]) << 32)
        | (static_cast<uint64_t>(buf[4]) << 24)
        | (static_cast<uint64_t>(buf[5]) << 16)
        | (static_cast<uint64_t>(buf[6]) <<  8)
        |  static_cast<uint64_t>(buf[7]);
}



// map for the base62 symbols
char map[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::string base_62_digest(uint64_t n) {
    
    std::string digest;
    
    while (n) {
        digest.push_back(map[n % 62]);
        n /= 62;
    }
    
    std::reverse(digest.begin(), digest.end());

    return digest;
}


std::string encode(std::string base, std::string target) {
    
    char* buffer = new char[target.length()];
    
    // get xor
    for (size_t i = 0; i < target.length(); ++i) {
        buffer[i] = base[i%base.length()] ^ target[i];
    }
    
    // get lower 8 bytes
    uint64_t value = get_lower_8_bytes(buffer+target.length()-8);
    
    // get base 62 digest
    std::string digest = base_62_digest(value);

    delete[] buffer;
    
    return base + "/" + digest;
}



int main() {
    
    std::string base_url;
    std::cin >> base_url;
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i) {
        
        std::string target_url;
        std::cin >> target_url;
        
        std::cout << encode(base_url, target_url) << std::endl;
        
    }
    
    
    return 0;
}
