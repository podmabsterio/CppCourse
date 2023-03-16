#include "shared_str.h"

SharedStr::~SharedStr() {
    delete data_;
    entity_counter_--;
}

SharedStr::SharedStr(const std::string_view& other) {
    data_ = new char[other.size()];
    size_ = other.size();
    memcpy(data_, other.data(), size_);
}

char* SharedStr::GetData() const {
    return data_;
}

bool SharedStr::IsUnique() const {
    return entity_counter_ == 1;
}

size_t SharedStr::size() const {
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
    entity_counter_ = 0;
}
