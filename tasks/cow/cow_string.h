#pragma once

#include "shared_str.h"

#include <cstddef>
#include <string_view>

class CowString;

class ProxyChar {
public:
    ProxyChar(size_t index, CowString* owner);

    ProxyChar& operator=(char value);

    operator char() const;

private:
    size_t index_;
    CowString* const owner_;
};

class IteratorCowString;
class ConstIteratorCowString;

class CowString {
public:
    CowString(CowString const &other);
    CowString(CowString&&);
    CowString(const std::string_view other);

    CowString& operator=(const CowString&);
    CowString& operator=(CowString&&);

    char* GetData() const;

    void ChangeElem(size_t index, char value);

    const char& operator[](size_t index) const;
    ProxyChar operator[](size_t index);

    const char& At(size_t index) const;

    IteratorCowString begin();
    IteratorCowString end();
    ConstIteratorCowString begin() const;
    ConstIteratorCowString end() const;

    size_t Size() const;

    operator std::string_view() const;

    bool operator==(const CowString& other) const;
    bool operator==(const std::string_view) const;
    CowString operator+(const CowString& other) const;
    CowString operator+(const std::string_view other) const;

    CowString& operator+=(const CowString& other);
    CowString& operator+=(const std::string_view other);

    friend CowString operator+(const std::string_view left, const CowString& right);

    ~CowString();

    friend ProxyChar;

private:
    explicit CowString(SharedStr* buffer);

    SharedStr* buffer_;
};

class ConstIteratorCowString {
public:
    ConstIteratorCowString(const CowString* owner, size_t index);

    ConstIteratorCowString operator++();
    ConstIteratorCowString operator++(int);
    ConstIteratorCowString operator--();
    ConstIteratorCowString operator--(int);
    auto operator<=>(const ConstIteratorCowString& other) const;
    bool operator==(const ConstIteratorCowString& other) const;

    const char operator*();
private:
    const CowString* const owner_;
    size_t index_;
};

class IteratorCowString {
public:
    IteratorCowString(CowString* owner, size_t index);

    IteratorCowString operator++();
    IteratorCowString operator++(int);
    IteratorCowString operator--();
    IteratorCowString operator--(int);
    bool operator==(const IteratorCowString& other) const;
    auto operator<=>(const IteratorCowString& other) const;

    ProxyChar operator*();

private:
    CowString* const owner_;
    size_t index_;
};
