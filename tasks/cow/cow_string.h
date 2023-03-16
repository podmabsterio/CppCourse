#pragma once

#include "shared_str.h"

#include <cstddef>
#include <string_view>

class CowString {
public:
    CowString(CowString const &other);
    CowString(CowString&&);

    CowString& operator=(const CowString&);
    CowString& operator=(CowString&&);

    char* GetData();

private:
    SharedStr* buffer_;
};

class ProxyChar {
    ProxyChar(char& real, const CowString* owner);
    const CowString* owner_;
    char& real_;
};