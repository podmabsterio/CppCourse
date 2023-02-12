#include "search.h"
#include <unordered_map>
#include <cctype>
#include <string>
#include <cmath>

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::unordered_map<std::string, std::vector<size_t> > count_query;
    std::string query_word;
    for (size_t i = 0; i < query.size(); ++i) {
        if (isalpha(query[i])) {
            query_word += static_cast<char>(tolower(query[i]));
        }
        if (!query_word.empty() && (!isalpha(query[i]) || i == query.size() - 1)) {
            count_query[query_word].emplace_back(0);
            query_word.clear();
        }
    }
    std::unordered_map<std::string, size_t> was_in_line;
    std::string text_word;
    std::vector<size_t> word_count(1, 0);
    size_t documents_quantity = 0;
    std::vector<std::string_view> lines;
    auto line_begin = text.begin();
    for (auto it = text.begin(); it != text.end(); ++it) {
        if (it != text.begin() && *(it - 1) == '\n') {
            line_begin = it;
        }
        if (isalpha(*it)) {
            text_word += static_cast<char>(tolower(*it));
        }
        if (!text_word.empty() && (!isalpha(*it) || it == text.end() - 1)) {
            if (count_query.count(text_word)) {
                ++count_query[text_word].back();
            }
            ++word_count.back();
            text_word.clear();
        }
        if (word_count.back() > 0 && (*it == '\n' || it == text.end() - 1)) {
            ++documents_quantity;
            word_count.emplace_back(0);
            if (it == text.end() - 1) {
                lines.emplace_back(line_begin, (it - line_begin + 1));
            } else {
                lines.emplace_back(line_begin, (it - line_begin));
            }
            for (auto& [key, count] : count_query) {
                if (count.back() > 0) {
                    ++was_in_line[key];
                }
                count.emplace_back(0);
            }
        }
    }
    std::vector<std::pair<double, size_t> > tf_idf(documents_quantity, {0, 0});
    for (size_t i = 0; i < documents_quantity; ++i) {
        for (auto& [key, count] : count_query) {
            double tf = static_cast<double>(count[i]) / word_count[i];
            double idf = 0;
            if (was_in_line[key] != 0) {
                idf = std::log(static_cast<double>(documents_quantity) / was_in_line[key]);
            }
            tf_idf[i].first += tf * idf;
            tf_idf[i].second = i;
        }
    }
    std::sort(tf_idf.rbegin(), tf_idf.rend());
    std::vector<std::string_view> response;
    for (size_t i = 0; i < results_count; ++i) {
        response.emplace_back(lines[tf_idf[i].second]);
    }
    return response;
}
