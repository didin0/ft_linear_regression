#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>

int main() {
    double theta0 = 0.0;
    double theta1 = 0.0;
    double mileage = 0.0;
    std::string input;
    std::string::size_type sz;

    std::ifstream inFile("thetas.txt");
    if (inFile.is_open()) {
        inFile >> theta0;
        inFile >> theta1;
    }

    while (true) {
        std::cout << "Enter a mileage: ";
        std::getline(std::cin, input);
        if (input.find(',') != std::string::npos) {
            std::replace(input.begin(), input.end(), ',', '.');
        }
        try {
            mileage = std::stod(input, &sz);
            if (sz != input.size()) {
                std::cerr << "Erreur : Veuillez entrer uniquement des chiffres : " << std::endl;
                continue;
            }
            if (mileage < 0) {
                std::cerr << "Erreur : Veuillez entrer uniquement des positifs : " << std::endl;
                continue;
            }
            break;
        } catch (const std::exception& e) {
            std::cerr << "Erreur : Veuillez entrer un kilometrage valide : " << e.what() << std::endl;
        }
    }

    double estimatedPrice = theta0 + (theta1 * mileage);

    // Un prix de voiture ne peut pas être négatif
    if (estimatedPrice < 0) {
        estimatedPrice = 0;
    }

    std::cout << "The estimated price is: " << estimatedPrice << std::endl;

    return 0;
}