#include <ctime>
#include <iostream>
#include <map>
#include <string>

void myprint(size_t length, size_t h_offset, size_t n_offset) {
    std::cout << "sequence of length = " << length << " found at haystack offset " << h_offset
              << ", needle offset " << n_offset << std::endl;
}

void mysearch(const std::string &needle, const std::string &haystack, size_t threshold) {
    if (threshold == 0 || threshold > needle.size() || threshold > haystack.size()) throw std::out_of_range("Error");
    size_t n_len = needle.length(), h_len = haystack.length();
    std::multimap<char, size_t> indexes;
    for (size_t i = 0; i < n_len - threshold + 1; i++)  // remember indexes in map for quick lookup
        indexes.insert(std::pair<char, size_t>(needle[i], i));
    for (size_t h = 0; h < h_len - threshold + 1; h++) {   // looking for matches in map
        if (indexes.contains(haystack[h]) == 0) continue;  // needed std=c++20
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
            }
        }
    }
}

void mysearch_two(const std::string &needle, const std::string &haystack, size_t threshold) {
    if (threshold == 0 || threshold > needle.size() || threshold > haystack.size()) return;
    size_t n_len = needle.length(), h_len = haystack.length();
    size_t search_window = n_len - threshold + 1;
    for (size_t h = 0; h < h_len - threshold + 1; h++) {
        size_t pos = needle.find(haystack[h]);
        if (pos > search_window) continue;
        size_t hit_counter = 0, cur_h = h;
        for (size_t n = pos; n < n_len && cur_h < h_len; n++, cur_h++) {
            if (needle[n] != haystack[cur_h]) break;
            hit_counter++;
        }
        if (hit_counter >= threshold) {
            myprint(hit_counter, h, pos);
            h = cur_h - 1;
        }
    }
}

int main() {
    std::string needle = "eeabcd1234eee";
    std::string haystack = "eeevnk2435kvabco8awkh125kjneytbcd12qjhb4acd123xmnbqwnw4t";
    //unsigned int start_time = std::clock();
    for (int i = 0; i < 1; i++) mysearch_two (needle,haystack, 3);
    //unsigned int end_time = clock();
    //unsigned int search_time = end_time - start_time;
    //std::cout << search_time << std::endl;
    return 0;
}