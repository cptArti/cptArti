#include "provinces.h"

#include <cstdint>
#include <queue>

int64_t CountPassports(const std::vector<int>& provinces) {
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> pq;
    for (auto& province : provinces) {
        pq.push(province);
    }
    int64_t total_passports = 0;
    while (pq.size() > 1) {
        const int64_t p1 = pq.top();
        pq.pop();
        const int64_t p2 = pq.top();
        pq.pop();
        int64_t new_province = p1 + p2;
        total_passports += new_province;
        pq.push(new_province);
    }
    return total_passports;
}
