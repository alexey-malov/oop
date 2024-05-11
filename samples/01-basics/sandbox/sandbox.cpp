struct Point {
    double x, y;
};

class Circle {
    Point m_center;
    double m_radius;
};

struct Complex {
    double real;
    double im;
}

class Rational {
    int m_numerator;
    int m_denominator;
};

class Polygon {
    std::vector<Point> m_vertices;
};