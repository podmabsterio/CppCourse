#include "search.h"
#include <unordered_map>
#include <cctype>
#include <string>
#include <cmath>
#include <algorithm>

const long double EPS = 1e-12;

std::vector<std::string_view> SplitByLines(std::string_view text) {
    std::vector<std::string_view> lines;
    auto line_begin = text.begin();
    bool have_words = false;
    for (auto it = text.begin(); it != text.end(); ++it) {
        if (*it == '\n') {
            line_begin = it + 1;
            have_words = false;
        }
        if (isalpha(*it)) {
            have_words = true;
        }
        if (have_words && it >= line_begin && (it + 1 == text.end() || *(it + 1) == '\n')) {
            lines.emplace_back(line_begin, it - line_begin + 1);
        }
    }
    return lines;
}

std::vector<std::string_view> SplitByWords(std::string_view line) {
    std::vector<std::string_view> words;
    auto word_begin = line.begin();
    for (auto it = line.begin(); it != line.end(); ++it) {
        if (!isalpha(*it)) {
            word_begin = it + 1;
        }
        if (it >= word_begin && (it + 1 == line.end() || !isalpha(*(it + 1)))) {
            words.emplace_back(word_begin, it - word_begin + 1);
        }
    }
    return words;
}

std::string StringToLower(std::string_view word) {
    std::string normalized;
    for (auto letter : word) {
        normalized.push_back(static_cast<char>(tolower(letter)));
    }
    return normalized;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    auto split_query = SplitByWords(query);
    std::unordered_map<std::string, size_t> count_used_in_line;
    auto split_text = SplitByLines(text);
    const size_t lines_quantity = split_text.size();
    std::unordered_map<std::string, std::vector<size_t>> quantity_met_in_line;

    for (auto word : split_query) {
        auto normalized_word = StringToLower(word);
        count_used_in_line[normalized_word] = 0;
        quantity_met_in_line[normalized_word].assign(lines_quantity, 0);
    }
    std::vector<size_t> count_words(lines_quantity, 0);
    for (size_t i = 0; i < split_text.size(); ++i) {
        for (auto word : SplitByWords(split_text[i])) {
            auto normalized_word = StringToLower(word);
            ++count_words[i];
            if (count_used_in_line.count(normalized_word)) {
                ++count_used_in_line[normalized_word];
                ++quantity_met_in_line[normalized_word][i];
            }
        }
    }
    std::unordered_map<std::string, long double> idf;
    for (auto& [word, count] : count_used_in_line) {
        idf[word] = 0;
        if (count != 0) {
            idf[word] = std::log(static_cast<long double>(lines_quantity) / static_cast<long double>(count));
        }
    }
    std::vector<std::pair<long double, size_t>> tf_idf(lines_quantity, {0, 0});
    for (size_t i = 0; i < lines_quantity; ++i) {
        tf_idf[i].second = -i;
        for (auto& [word, count] : quantity_met_in_line) {
            long double tf = static_cast<long double>(count[i]) / static_cast<long double>(count_words[i]);
            tf_idf[i].first += tf * idf[word];
        }
    }
    std::stable_sort(tf_idf.rbegin(), tf_idf.rend());
    std::vector<std::string_view> response;
    for (size_t i = 0; i < results_count && i < lines_quantity; ++i) {
        if (tf_idf[i].first < EPS) {
            break;
        }
        response.emplace_back(split_text[-tf_idf[i].second]);
    }
    return response;
}
