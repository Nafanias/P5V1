#include <iostream>
#include <fstream>

// Функция для выполнения метода Рунге-Кутты-Курье
void RungeKuttaCourant(const char* output_filename, const double dt, const int N) {
    double t = 0;
    double x = -0.09;
    double y = -0.36;
    double vx = 0;
    double vy = 1;
    double ax, ay;

    int i = 0;

    double kx[4], ky[4], kvx[4], kvy[4];

    std::ofstream fp(output_filename);

    if (!fp.is_open()) {
        std::cerr << "File open error\n";
        return;
    }

    fp << "# t\tx\ty\tvx\tvy\tax\tay\n";

    // Выполнение метода в цикле
    while (i < N) {
        for (int j = 0; j < 4; ++j) {
            kx[j] = vx + (j == 0 ? 0.0 : 0.5 * dt * kvx[j - 1]);
            ky[j] = vy + (j == 0 ? 0.0 : 0.5 * dt * kvy[j - 1]);
            ax = -4.93 * (x + (j == 0 ? 0.0 : 0.5 * dt * kx[j - 1]) - (t + (j == 0 ? 0.0 : 0.5 * dt))) - 0.35 * (vx + (j == 0 ? 0.0 : 0.5 * dt * kvx[j - 1])) + 0.54;
            ay = -1.38 * (y + (j == 0 ? 0.0 : 0.5 * dt * ky[j - 1])) - 0.35 * (vy + (j == 0 ? 0.0 : 0.5 * dt * kvy[j - 1])) - 0.97;
            kvx[j] = ax;
            kvy[j] = ay;
        }

        x += dt / 6.0 * (kx[0] + 2 * kx[1] + 2 * kx[2] + kx[3]);
        y += dt / 6.0 * (ky[0] + 2 * ky[1] + 2 * ky[2] + ky[3]);
        vx += dt / 6.0 * (kvx[0] + 2 * kvx[1] + 2 * kvx[2] + kvx[3]);
        vy += dt / 6.0 * (kvy[0] + 2 * kvy[1] + 2 * kvy[2] + kvy[3]);

        t += dt;
        i++;

        // Запись результатов в файл
        if (i % 10 == 0) {
            fp << t << "\t" << x << "\t" << y << "\t" << vx << "\t" << vy << "\t" << ax << "\t" << ay << "\n";
        }
    }

    fp.close();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error!\nProgram usage:\n\t" << argv[0] << " output\n";
        return EXIT_FAILURE;
    }

    const double dt = 4.52e-3;
    const int N = 1200;

    // Вызов функции для выполнения метода
    RungeKuttaCourant(argv[1], dt, N);

    return 0;
}