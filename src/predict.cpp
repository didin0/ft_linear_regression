#include <iostream>
#include <string>
#include <fstream>

int main() {
    double theta0 = 0.0;
    double theta1 = 0.0;
    int mileage = 0.0;

    try {
        std::ifstream inFile("thetas.txt");
        if (inFile.is_open()) {
            inFile >> theta0;
            inFile >> theta1;
            std::cout << theta0 << " | " << theta1 << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur de lecture : " << e.what() << std::endl;
    }

    std::cout << "Enter a mileage :";
    std::cin >> mileage;

    double estimatedPrice = theta0 + (theta1 * mileage);

    std::cout << "The Estimated price is :" << estimatedPrice << std::endl;

    return 0;
}