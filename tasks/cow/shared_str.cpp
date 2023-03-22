#include "shared_str.h"

char* SharedStr::GetData() {
    return data_;
}

bool SharedStr::IsUnique() const {
    return entity_counter_ == 1;
}

size_t& SharedStr::Size() {
    return size_;
}

size_t SharedStr::operator++() const {
    return ++entity_counter_;
}

size_t SharedStr::operator++(int) const {
    return entity_counter_++;
}

size_t SharedStr::operator--() const {
    return --entity_counter_;
}

size_t SharedStr::operator--(int) const {
    return entity_counter_--;
}

void SharedStr::Nullify() {
    data_ = nullptr;
    size_ = 0;
    entity_counter_ = 1;
}

void SharedStr::UpdateData(char* data) {
    data_ = data;
}

SharedStr::SharedStr(char* data, size_t size) : data_(data), size_(size) {
}
