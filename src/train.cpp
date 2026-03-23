#include <iostream>
#include <vector>
#include <csv.h>
#include <fstream>

int main() {
    std::vector<double> mileages;
    std::vector<double> prices;

    try {
        io::CSVReader<2> in("data.csv");

        in.read_header(io::ignore_extra_column, "km", "price");

        double km;
        double price;

        while (in.read_row(km, price)) {
            mileages.push_back(km);
            prices.push_back(price);
        }

        std::cout << "Succes! " << mileages.size() << " readed lignes from CSV" <<std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur de lecture : " << e.what() << std::endl;
    }

    double theta0 = 5.0;
    double theta1 = -0.5;

    std::ofstream outFile("thetas.txt");
    if (outFile.is_open()) {
        outFile << theta0 << "\n" << theta1 << "\n";
        outFile.close();
        std::cout << "Thetas Sauvegardes!" << std::endl;
    }

    return 0;
}