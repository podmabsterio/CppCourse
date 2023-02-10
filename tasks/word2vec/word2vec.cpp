#include "word2vec.h"

#include <vector>

int64_t Distance(const std::vector<int>& a, const std::vector<int>& b) {
    int64_t distance = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        distance += static_cast<int64_t>(a[i]) * b[i];
    }
    return distance;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> closest_vectors;
    if (words.size() != vectors.size() || words.size() < 2) {
        return closest_vectors;
    }
    int64_t max_distance = Distance(vectors[0], vectors[1]);
    closest_vectors.emplace_back(words[1]);
    for (size_t i = 2; i < vectors.size(); ++i) {
        if (Distance(vectors[0], vectors[i]) > max_distance) {
            max_distance = Distance(vectors[0], vectors[i]);
            closest_vectors.clear();
            closest_vectors.emplace_back(words[i]);
        } else if (Distance(vectors[0], vectors[i]) == max_distance) {
            closest_vectors.emplace_back(words[i]);
        }
    }
    return closest_vectors;
}
