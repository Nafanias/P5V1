#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error!\nProgram usage:\n\t" << argv[0] << " output\n";
        return EXIT_FAILURE;
    }

    const double dt = 4.52e-3;
    double t = 0;
    double x = -0.09;
    double y = -0.36;
    double vx = 0;
    double vy = 1;
    double ax, ay;
    const int N = 1200;
    int i = 0;
    std::ofstream fp(argv[1]);

    if (!fp.is_open()) {
        std::cerr << "File open error\n";
        return EXIT_FAILURE;
    }

    fp << "# t\tx\ty\tvx\tvy\tax\tay\n";
    while (i < N) {
        ax = -4.93 * (x - t) - 0.35 * vx + 0.54;
        ay = -1.38 * y - 0.35 * vy - 0.97;

        if (i % 10 == 0)
            fp << t << "\t" << x << "\t" << y << "\t" << vx << "\t" << vy << "\t" << ax << "\t" << ay << "\n";

        x += vx * dt;
        y += vy * dt;
        vx += ax * dt;
        vy += ay * dt;
        t += dt;
        i++;
    }

    fp.close();
    return 0;
}
