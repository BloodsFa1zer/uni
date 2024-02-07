#include <iostream>
#include <cmath>

using namespace std;

// Функція, рівняння якої потрібно розв'язати
double f(double x) {
    return x*x - 1; // x^3+3*x^2+12*x+8
}

// Похідна функції
double derivative(const std::function<double(double)>& f, double x, double h) {
    return (f(x + h) - f(x)) / h;
}

int main() {
    double x = 0.5;  // Точка, в якій ми обчислюємо похідну
    double h = 0.0001; // Мала приріст
    cout.precision(20);


    while (true) {
        double y = f(x);
        double dy = derivative(f, x, h);

        x = x - y / dy;
        cout << "Found a root: " << x << endl;
        if (abs(y) < h) {
            break;
        }
    }

    return 0;
}
