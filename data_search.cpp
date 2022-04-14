#include <iostream>
#include <map>

void myprint(size_t length, size_t h_offset, size_t n_offset) {
    std::cout << "sequence of length = " << length << " found at haystack offset " << h_offset
              << ", needle offset " << n_offset << std::endl;
}

void mysearch(const std::string &needle, const std::string &haystack, size_t threshold) {
    if (threshold == 0 || threshold > needle.size() || threshold > haystack.size())
        throw std::out_of_range("Error");
    size_t n_len = needle.length(), h_len = haystack.length();
    std::multimap<char, size_t> indexes;
    for (size_t i = 0; i < n_len - threshold + 1; i++)  // remember indexes in map for quick lookup
        indexes.emplace(std::pair<char, size_t>(needle[i], i));
    for (size_t h = 0; h < h_len - threshold + 1; h++) {  // looking for matches in map
        if (indexes.count(haystack[h]) == 0) continue;
        auto iter = indexes.find(haystack[h]);
        for (size_t j = 0; j < indexes.count(haystack[h]); j++, iter++) {  // every match
            size_t index = iter->second, hit_counter = 0, cur_h = h;
            for (size_t n = index; n < n_len && cur_h < h_len; n++, cur_h++) {  // compare the required chars
                if (needle[n] != haystack[cur_h]) break;
                hit_counter++;
            }
            if (hit_counter >= threshold) {
                myprint(hit_counter, h, index);
                h = cur_h - 1;
                break;
            }
        }
    }
}


int main() {
    std::string needle = "abcd1234";
    std::string haystack = "vnk2435kvabco8awkh125kjneytbcd12qjhb4acd123xmnbqwnw4t";
    mysearch(needle, haystack, 3);
    return 0;
}
