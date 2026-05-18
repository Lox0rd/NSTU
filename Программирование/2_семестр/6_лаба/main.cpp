#include <iostream>
#include <cmath>

const double PI = 3.1415926;

class PolarVector {
private:
    double length;
    double angle; // хранится в радианах

    void normalizeAngle() {
        while (angle >= 2 * PI) angle -= 2 * PI;
        while (angle < 0) angle += 2 * PI;
    }

    void setFromLenDeg(double len, double angDeg) {
        if (len < 0) {
            length = -len;
            angle = (angDeg - 180.0) * PI / 180.0;
        } else {
            length = len;
            angle = angDeg * PI / 180.0;
        }
        normalizeAngle();
    }

    static double degreesToRadians(double degrees) {
        return degrees * PI / 180.0;
    }

public:
    PolarVector();
    PolarVector(double len, double ang);
    ~PolarVector() = default;

    void input();
    void output() const;

    void read(std::istream& in);
    void write(std::ostream& out) const;

    void setLength(double len);
    void setAngleDegrees(double angDeg);

    double getLength() const;
    double getAngleDegrees() const;
};

PolarVector::PolarVector() : length(0), angle(0) {}

PolarVector::PolarVector(double len, double ang) {
    setFromLenDeg(len, ang);
}

void PolarVector::input() {
    std::cout << "Длина: ";
    double len;
    std::cin >> len;

    std::cout << "Угол (град): ";
    double angDeg;
    std::cin >> angDeg;

    setFromLenDeg(len, angDeg);
}

void PolarVector::output() const {
    std::cout << "Вектор: длина=" << length
              << ", угол=" << angle * 180.0 / PI << "°\n";
}

void PolarVector::read(std::istream& in) {
    double len, angDeg;
    in >> len >> angDeg;
    setFromLenDeg(len, angDeg);
}

void PolarVector::write(std::ostream& out) const {
    out << "Вектор: длина=" << length
        << ", угол=" << angle * 180.0 / PI << "°\n";
}

void PolarVector::setLength(double len) {
    if (len < 0) {
        length = -len;
        angle += PI;
    } else {
        length = len;
    }
    normalizeAngle();
}

void PolarVector::setAngleDegrees(double angDeg) {
    angle = degreesToRadians(angDeg);
    normalizeAngle();
}

double PolarVector::getLength() const {
    return length;
}

double PolarVector::getAngleDegrees() const {
    return angle * 180.0 / PI;
}

int main() {
    PolarVector v1;
    PolarVector v2(-5.0, 45.0);

    std::cout << "v1: ";
    v1.output();
    std::cout << "v2: ";
    v2.output();

    v1.setLength(-3.0);
    v1.setAngleDegrees(90.0);
    std::cout << "После изменений v1: ";
    v1.output();

    std::cout << "\nВведите новый вектор (длина, угол в градусах): ";
    v2.read(std::cin);
    std::cout << "Введённый вектор: ";
    v2.write(std::cout);
    return 0;
}