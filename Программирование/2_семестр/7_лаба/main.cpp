#include <iostream>
#include <cmath>

class Vector2DPolar {
private:
    double length;  // длина (модуль) вектора
    double angle;   // угол поворота в радианах

    // Нормализация угла в диапазон [0, 2π)
    void normalizeAngle() {
        while (angle < 0) angle += 2 * M_PI;
        while (angle >= 2 * M_PI) angle -= 2 * M_PI;
    }

public:
    // Конструкторы
    Vector2DPolar(double len = 0, double ang = 0)
        : length(len), angle(ang) {
        normalizeAngle();
    }

    Vector2DPolar(const Vector2DPolar& other)
        : length(other.length), angle(other.angle) {}

    // Приведение к декартовым координатам (извлечение элементов)
    std::pair<double, double> toCartesian() const {
        double x = length * cos(angle);
        double y = length * sin(angle);
        return std::make_pair(x, y);
    }

    // Извлечение отдельных элементов
    double getLength() const { return length; }
    double getAngle() const { return angle; }

    // Обновление элементов
    void setLength(double len) { length = len; }
    void setAngle(double ang) { angle = ang; normalizeAngle(); }

    // Арифметические операции с другими векторами

    // Сложение векторов (через декартовы координаты)
    Vector2DPolar operator+(const Vector2DPolar& other) const {
        auto [x1, y1] = toCartesian();
        auto [x2, y2] = other.toCartesian();
        double x_sum = x1 + x2;
        double y_sum = y1 + y2;

        double new_length = sqrt(x_sum * x_sum + y_sum * y_sum);
        double new_angle = atan2(y_sum, x_sum);

        return Vector2DPolar(new_length, new_angle);
    }

    // Вычитание векторов
    Vector2DPolar operator-(const Vector2DPolar& other) const {
        auto [x1, y1] = toCartesian();
        auto [x2, y2] = other.toCartesian();
        double x_diff = x1 - x2;
        double y_diff = y1 - y2;

        double new_length = sqrt(x_diff * x_diff + y_diff * y_diff);
        double new_angle = atan2(y_diff, x_diff);

        return Vector2DPolar(new_length, new_angle);
    }

    // Умножение на скаляр
    Vector2DPolar operator*(double scalar) const {
        return Vector2DPolar(length * scalar, angle);
    }

    // Деление на скаляр
    Vector2DPolar operator/(double scalar) const {
        if (scalar == 0) throw std::invalid_argument("Division by zero");
        return Vector2DPolar(length / scalar, angle);
    }

    // Операции присваивания

    Vector2DPolar& operator+=(const Vector2DPolar& other) {
        *this = *this + other;
        return *this;
    }

    Vector2DPolar& operator-=(const Vector2DPolar& other) {
        *this = *this - other;
        return *this;
    }

    Vector2DPolar& operator*=(double scalar) {
        length *= scalar;
        return *this;
    }

    Vector2DPolar& operator/=(double scalar) {
        if (scalar == 0) throw std::invalid_argument("Division by zero");
        length /= scalar;
        return *this;
    }

    // Приведение к базовому типу (длина вектора)
    operator double() const {
        return length;
    }

    // Ввод из потока
    friend std::istream& operator>>(std::istream& is, Vector2DPolar& vec) {
        is >> vec.length >> vec.angle;
        vec.normalizeAngle();
        return is;
    }

    // Вывод в поток
    friend std::ostream& operator<<(std::ostream& os, const Vector2DPolar& vec) {
        os << "Vector(length=" << vec.length
           << ", angle=" << vec.angle << " rad"
           << " ≈ " << (vec.angle * 180 / M_PI) << "°)";
        return os;
    }
};
int main() {
    // Создание векторов
    Vector2DPolar v1(5, M_PI / 4);  // длина 5, угол 45°
    Vector2DPolar v2(3, M_PI / 2);  // длина 3, угол 90°

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    // Арифметические операции (конвейер)
    auto v3 = v1 + v2;           // сложение
    auto v4 = v3 * 2.0;          // умножение на скаляр
    auto v5 = v4 - v1;         // вычитание

    std::cout << "v3 = v1 + v2: " << v3 << std::endl;
    std::cout << "v4 = v3 * 2: " << v4 << std::endl;
    std::cout << "v5 = v4 - v1: " << v5 << std::endl;

    // Извлечение элементов
    auto [x, y] = v5.toCartesian();
    std::cout << "v5 в декартовых координатах: x=" << x
              << ", y=" << y << std::endl;

    // Приведение к базовому типу
    double len = v5;  // неявное приведение к double (длина)
    std::cout << "Длина v5: " << len << std::endl;

    // Ввод с клавиатуры
    Vector2DPolar v6;
    std::cout << "Введите длину и угол для нового вектора: ";
    std::cin >> v6;
    std::cout << "Введённый вектор: " << v6 << std::endl;

    return 0;
}
