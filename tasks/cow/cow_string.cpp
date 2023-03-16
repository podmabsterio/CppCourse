#include "cow_string.h"
#include <cstring>

CowString& CowString::operator=(const CowString& other) {
    buffer_ = other.buffer_;
    buffer_++;
    return *this;
}

CowString& CowString::operator=(CowString&& other) {
    buffer_ = other.buffer_;
    other.buffer_->Nullify();
    return *this;
}

CowString::CowString(const CowString& other) : buffer_(other.buffer_) {
    buffer_++;
}

CowString::CowString(CowString&& other) : buffer_(other.buffer_){
    other.buffer_->Nullify();
}

char* CowString::GetData() {
    return buffer_->GetData();
}

ProxyChar::ProxyChar(char& real, const CowString* owner) : owner_(owner), real_(real){
}
