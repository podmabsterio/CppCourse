#pragma once

#include <cstddef>
#include <string_view>

class SharedStr {
public:
    SharedStr() = default;

    SharedStr(char* data, size_t size);

    size_t operator++() const;
    size_t operator++(int) const;
    size_t operator--() const;
    size_t operator--(int) const;

    char* GetData();
    void UpdateData(char* data);
    void Nullify();
    bool IsUnique() const;
    size_t& Size();

private:
    char* data_ = nullptr;
    mutable size_t entity_counter_ = 1;
    size_t size_ = 0;
};
