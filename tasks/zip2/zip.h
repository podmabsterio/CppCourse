#pragma once

#include <iterator>

template <typename Iterator1, typename Iterator2>
class IteratorDualArray {
public:
    IteratorDualArray(Iterator1 it1, Iterator2 it2);

    bool operator==(const IteratorDualArray& other) const;
    bool operator!=(const IteratorDualArray& other) const;

    IteratorDualArray& operator++();
    IteratorDualArray& operator++(int);

    IteratorDualArray& operator--();
    IteratorDualArray& operator--(int);

    auto operator*();

private:
    Iterator1 it1_;
    Iterator2 it2_;
};

template <typename Sequence1, typename Sequence2>
class DualArray {
public:
    DualArray(const Sequence1& sequence1, const Sequence2& sequence2);

    auto begin();
    auto end();

private:
    const Sequence1& sequence1_;
    const Sequence2& sequence2_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return DualArray(sequence1, sequence2);
}

template <typename Sequence1, typename Sequence2>
DualArray<Sequence1, Sequence2>::DualArray(const Sequence1& sequence1, const Sequence2& sequence2)
    : sequence1_(sequence1), sequence2_(sequence2) {
}

template <typename Sequence1, typename Sequence2>
auto DualArray<Sequence1, Sequence2>::end() {
    return IteratorDualArray(std::end(sequence1_), std::end(sequence2_));
}

template <typename Sequence1, typename Sequence2>
auto DualArray<Sequence1, Sequence2>::begin() {
    return IteratorDualArray(std::begin(sequence1_), std::begin(sequence2_));
}

template <typename Iterator1, typename Iterator2>
IteratorDualArray<Iterator1, Iterator2>& IteratorDualArray<Iterator1, Iterator2>::operator--(int) {
    auto copy_of_iterator = this;
    --it1_;
    --it2_;
    return &copy_of_iterator;
}

template <typename Iterator1, typename Iterator2>
IteratorDualArray<Iterator1, Iterator2>& IteratorDualArray<Iterator1, Iterator2>::operator--() {
    --it1_;
    --it2_;
    return *this;
}

template <typename Iterator1, typename Iterator2>
IteratorDualArray<Iterator1, Iterator2>& IteratorDualArray<Iterator1, Iterator2>::operator++(int) {
    auto copy_of_iterator = this;
    ++it1_;
    ++it2_;
    return &copy_of_iterator;
}

template <typename Iterator1, typename Iterator2>
IteratorDualArray<Iterator1, Iterator2>& IteratorDualArray<Iterator1, Iterator2>::operator++() {
    ++it1_;
    ++it2_;
    return *this;
}

template <typename Iterator1, typename Iterator2>
bool IteratorDualArray<Iterator1, Iterator2>::operator==(const IteratorDualArray& other) const {
    return it1_ == other.it1_ && it2_ == other.it2_;
}

template <typename Iterator1, typename Iterator2>
IteratorDualArray<Iterator1, Iterator2>::IteratorDualArray(Iterator1 it1, Iterator2 it2) : it1_(it1), it2_(it2) {
}

template <typename Iterator1, typename Iterator2>
auto IteratorDualArray<Iterator1, Iterator2>::operator*() {
    return std::make_pair(*it1_, *it2_);
}

template <typename Iterator1, typename Iterator2>
bool IteratorDualArray<Iterator1, Iterator2>::operator!=(const IteratorDualArray& other) const {
    return it1_ != other.it1_ && it2_ != other.it2_;
}