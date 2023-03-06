#pragma once

#include <map>
#include <vector>
#include <string>

class Poly {
public:
    struct Monomial {
        size_t power;
        int64_t coefficient;
    };

    explicit Poly();
    explicit Poly(const std::vector<int64_t>& coefficients);
    explicit Poly(const std::vector<Monomial>& monomials);
    explicit Poly(std::initializer_list<Monomial> monomials);
    explicit Poly(std::initializer_list<int64_t> coefficients);

    int64_t operator()(int64_t value) const;
    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;
    Poly operator+(const Poly& other) const;
    Poly operator-() const;
    Poly operator-(const Poly& other) const;
    void operator+=(const Poly& other);
    void operator-=(const Poly& other);
    Poly operator*(const Poly& other);
    void operator*=(const Poly& other);

    std::string Representation() const;

    friend std::ostream& operator<<(std::ostream& stream, const Poly& poly);

private:
    std::map<size_t, int64_t, std::greater<size_t>> poly_;

    void Normalize();
};
