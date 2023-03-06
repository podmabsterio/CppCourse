#include "poly.h"

namespace {
int64_t IntegerPower(const int64_t base, const int64_t exp) {
    if (exp == 0) {
        return 1;
    }
    if (exp % 2 == 0) {
        return IntegerPower(base, exp / 2) * IntegerPower(base, exp / 2);
    }
    return base * IntegerPower(base, exp - 1);
}

std::string MonomialToString(Poly::Monomial monomial) {
    std::string result;
    result += std::to_string(monomial.coefficient);
    if (monomial.power >= 1) {
        result += "x";
    }
    if (monomial.power > 1) {
        result += "^" + std::to_string(monomial.power);
    }
    return result;
}
}

Poly::Poly() {
    poly_[0];
}

Poly::Poly(const std::vector<int64_t>& coefficients) {
    for (size_t i = 0; i < coefficients.size(); ++i) {
        if (coefficients[i] != 0) {
            poly_[i] = coefficients[i];
        }
    }
}

Poly::Poly(std::initializer_list<int64_t> coefficients) : Poly(static_cast<std::vector<int64_t>>(coefficients)) {
}

Poly::Poly(const std::vector<Monomial>& monomials) {
    for (auto& monomial : monomials) {
        if (monomial.coefficient != 0) {
            poly_[monomial.power] = monomial.coefficient;
        }
    }
}

Poly::Poly(std::initializer_list<Monomial> monomials) : Poly(static_cast<std::vector<Monomial>>(monomials)) {
}

void Poly::Normalize() {
    std::vector<size_t> empty_keys;
    for (auto& [power, coefficient] : poly_) {
        if (coefficient == 0) {
            empty_keys.push_back(power);
        }
    }
    for (auto key : empty_keys) {
        poly_.erase(key);
    }
    if (poly_.empty()) {
        poly_[0];
    }
}

int64_t Poly::operator()(int64_t value) const {
    int64_t result = 0;
    for (auto [power, coefficient] : poly_) {
        result += coefficient * IntegerPower(value, static_cast<int64_t>(power));
    }
    return result;
}

bool Poly::operator==(const Poly& other) const {
    return this->poly_ == other.poly_;
}

bool Poly::operator!=(const Poly& other) const {
    return this->poly_ != other.poly_;
}

Poly Poly::operator+(const Poly& other) const {
    Poly result = *this;
    for (auto [power, coefficient] : other.poly_) {
        result.poly_[power] += coefficient;
    }
    result.Normalize();
    return result;
}

Poly Poly::operator-(const Poly& other) const {
    return *this + (-other);
}

Poly Poly::operator-() const {
    Poly result;
    for (auto [power, coefficient] : poly_) {
        result.poly_[power] = -coefficient;
    }
    return result;
}

void Poly::operator+=(const Poly& other) {
    *this = *this + other;
}

void Poly::operator-=(const Poly& other) {
    *this = *this - other;
}

Poly Poly::operator*(const Poly& other) {
    Poly result;
    for (auto [power_this, coefficient_this] : poly_) {
        for (auto [power_other, coefficient_other] : other.poly_) {
            result.poly_[power_this + power_other] += coefficient_this * coefficient_other;
        }
    }
    return result;
}

std::string Poly::Representation() const{
    std::string result = "y = " + MonomialToString({poly_.begin()->first, poly_.begin()->second});
    for (auto it = poly_.begin(); it != poly_.end(); ++it) {
        if (it == poly_.begin()) {
            continue;
        }
        std::string sign = " + ";
        if (it->second == 0) {
            continue;
        }
        if (it->second < 0) {
            sign = " - ";
        }
        result += sign + MonomialToString({it->first, abs(it->second)});
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, const Poly& poly) {
    stream << poly.Representation();
    return stream;
}
