#ifndef UTILITY_TESTS
#define UTILITY_TESTS

#include <istream>
#include <string>

struct Edge {
    explicit Edge(std::int32_t weight, const std::string& label)
        : m_weight(weight), m_label(label) {}

    Edge operator+(const Edge& edge) const {
        return Edge(m_weight + edge.m_weight, m_label + edge.m_label);
    }

    [[nodiscard]] std::int32_t weight() const { return m_weight; }

    [[nodiscard]] std::string label() const { return m_label; }

private:
    std::int32_t m_weight;
    std::string m_label;

    friend std::ostream& operator<<(std::ostream& os, const Edge& e);
};

inline std::ostream& operator<<(std::ostream& os, const Edge& e) {
    os << "(" << e.m_weight << ", " << e.m_label << ")";
    return os;
}

inline std::int32_t operator+(std::int32_t value, const Edge& edge) {
    return value + edge.weight();
}

inline std::int64_t operator+(std::int64_t value, const Edge& edge) {
    return value + edge.weight();
}

#endif  // UTILITY_TESTS