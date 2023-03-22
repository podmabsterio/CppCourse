#include "cow_string.h"

#include <cstring>
#include <stdexcept>

CowString& CowString::operator=(const CowString& other) {
    if (this == &other) {
        return *this;
    }
    if (buffer_->IsUnique()) {
        delete[] buffer_->GetData();
        delete buffer_;
    }
    else {
        (*buffer_)--;
    }
    buffer_ = other.buffer_;
    (*buffer_)++;
    return *this;
}

CowString& CowString::operator=(CowString&& other) {
    if (this == &other) {
        return *this;
    }
    if (buffer_->IsUnique()) {
        delete[] buffer_->GetData();
        delete buffer_;
    }
    else {
        (*buffer_)--;
    }
    buffer_ = other.buffer_;
    other.buffer_ = nullptr;
    return *this;
}

CowString::CowString(const CowString& other) : buffer_(other.buffer_) {
    (*buffer_)++;
}

CowString::CowString(CowString&& other) : buffer_(other.buffer_){
    other.buffer_ = nullptr;
}

CowString::CowString(const std::string_view other) {
    buffer_ = new SharedStr(new char[other.size()], other.size());
    memcpy(buffer_->GetData(), other.data(), other.size());
}

char* CowString::GetData() const{
    return buffer_->GetData();
}

const char& CowString::operator[](size_t index) const {
    return buffer_->GetData()[index];
}

ProxyChar CowString::operator[](size_t index) {
    return ProxyChar(index, this);
}

const char& CowString::At(size_t index) const {
    if (index >= buffer_->Size()) {
        throw std::out_of_range("you should know the limits");
    }
    return buffer_->GetData()[index];
}

void CowString::ChangeElem(size_t index, char value) {
    if (value == buffer_->GetData()[index]) {
        return;
    }
    if (buffer_->IsUnique()) {
        buffer_->GetData()[index] = value;
        return;
    }
    auto copy_of_buffer = buffer_;
    buffer_ = new SharedStr(new char[copy_of_buffer->Size()], copy_of_buffer->Size());
    std::memcpy(buffer_->GetData(), copy_of_buffer->GetData(), copy_of_buffer->Size());
    buffer_->GetData()[index] = value;
}

IteratorCowString CowString::begin() {
    return IteratorCowString(this, 0);
}

IteratorCowString CowString::end() {
    return IteratorCowString(this, buffer_->Size());
}

ConstIteratorCowString CowString::begin() const {
    return ConstIteratorCowString(this, 0);
}

ConstIteratorCowString CowString::end() const {
    return ConstIteratorCowString(this, buffer_->Size());
}

CowString::operator std::string_view() const {
    return std::string_view(buffer_->GetData(), buffer_->Size());
}

CowString::~CowString() {
    if (buffer_ == nullptr) {
        return;
    }
    if (buffer_->IsUnique()) {
        delete[] buffer_->GetData();
        delete buffer_;
        buffer_ = nullptr;
    }
    else {
        (*buffer_)--;
    }
}

bool CowString::operator==(const CowString& other) const {
    return static_cast<std::string_view>(*this) == static_cast<std::string_view>(other);
}

bool CowString::operator==(const std::string_view other) const {
    return static_cast<std::string_view>(*this) == other;
}

CowString CowString::operator+(const CowString& other) const {
    CowString result(new SharedStr(new char[this->Size() + other.Size()], this->Size() + other.Size()));
    std::memcpy(result.GetData(), this->GetData(), this->Size());
    std::memcpy(result.GetData() + this->Size(), other.GetData(), other.Size());
    return result;
}

CowString::CowString(SharedStr* buffer) : buffer_(buffer) {
}

size_t CowString::Size() const {
    return buffer_->Size();
}

CowString CowString::operator+(const std::string_view other) const {
    CowString result(new SharedStr(new char[this->Size() + other.size()], this->Size() + other.size()));
    std::memcpy(result.GetData(), this->GetData(), this->Size());
    std::memcpy(result.GetData() + this->Size(), other.data(), other.size());
    return result;
}

CowString operator+(const std::string_view left, const CowString& right) {
    CowString result(new SharedStr(new char[left.size() + right.Size()], left.size() + right.Size()));
    std::memcpy(result.GetData(), left.data(), left.size());
    std::memcpy(result.GetData() + left.size(), right.GetData(), right.Size());
    return result;
}

CowString& CowString::operator+=(const CowString& other) {
    return *this = *this + other;
}

CowString& CowString::operator+=(const std::string_view other) {
    return *this = *this + other;
}

ConstIteratorCowString::ConstIteratorCowString(const CowString *owner, size_t index) : owner_(owner), index_(index) {
}

const char ConstIteratorCowString::operator*() {
    return (*owner_)[index_];
}

ConstIteratorCowString ConstIteratorCowString::operator++() {
    ++index_;
    return *this;
}

ConstIteratorCowString ConstIteratorCowString::operator++(int) {
    auto old_value = *this;
    ++index_;
    return old_value;
}

ConstIteratorCowString ConstIteratorCowString::operator--() {
    return *this;
}

ConstIteratorCowString ConstIteratorCowString::operator--(int) {
    auto old_value = *this;
    ++index_;
    return old_value;
}

auto ConstIteratorCowString::operator<=>(const ConstIteratorCowString &other) const {
    return index_ - other.index_;
}

bool ConstIteratorCowString::operator==(const ConstIteratorCowString& other) const {
    return owner_ == other.owner_ && index_ == other.index_;
}

ProxyChar IteratorCowString::operator*() {
    return ProxyChar(index_, owner_);
}

IteratorCowString::IteratorCowString(CowString *owner, size_t index) : owner_(owner), index_(index) {
}

IteratorCowString IteratorCowString::operator++() {
    ++index_;
    return *this;
}

IteratorCowString IteratorCowString::operator++(int) {
    auto old_value = *this;
    ++index_;
    return old_value;
}

IteratorCowString IteratorCowString::operator--() {
    return *this;
}

IteratorCowString IteratorCowString::operator--(int) {
    auto old_value = *this;
    ++index_;
    return old_value;
}

auto IteratorCowString::operator<=>(const IteratorCowString &other) const {
    return index_ - other.index_;
}

bool IteratorCowString::operator==(const IteratorCowString& other) const {
    return owner_ == other.owner_ && index_ == other.index_;
}

ProxyChar::ProxyChar(size_t index, CowString *owner) : index_(index), owner_(owner) {
}

ProxyChar& ProxyChar::operator=(char value) {
    owner_->ChangeElem(index_, value);
    return *this;
}

ProxyChar::operator char() const {
    return owner_->GetData()[index_];
}
