#pragma once

#include <cstddef>
#include <string_view>

class SharedStr {
public:
    SharedStr() = default;
    SharedStr(const std::string_view&);

    size_t operator++() const;
    size_t operator++(int) const;
    size_t operator--() const;
    size_t operator--(int) const;

    char* GetData() const;
    void Nullify();
    bool IsUnique() const;
    size_t size() const;

    ~SharedStr();
private:
    char* data_ = nullptr;
    mutable size_t entity_counter_ = 1;
    size_t size_ = 0;
};

class SharedStrIterator {

};