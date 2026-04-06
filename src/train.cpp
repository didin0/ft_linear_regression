#include <iostream>
#include <vector>
#include <csv.h>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../include/matplotlibcpp.h"
namespace plt = matplotlibcpp;

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
    
    if (mileages.empty()) {
        std::cerr << "Erreur : aucune donnee a traiter." << std::endl;
        return 1;
    }

    const auto [min_it, max_it] = std::minmax_element(begin(mileages), end(mileages));
    double min_km = *min_it;
    double max_km = *max_it;

    // Normaliser les kilométrages (entre 0 et 1)
    std::vector<double> norm_mileages;
    for (double km : mileages) {
        norm_mileages.push_back((km - min_km) / (max_km - min_km));
    }

    // Étape 4 : La Descente de Gradient (Le modèle mathématique du sujet)
    double theta0 = 0.0;
    double theta1 = 0.0;
    double learningRate = 0.1; // Pas de 0.1 comme normalized de 0 a 1.
    int iterations = 10000;    // Le nombre de fois qu'on répète l'apprentissage
    int m = mileages.size();   // La taille de notre dataset ('m' dans la formule)

    for (int iter = 0; iter < iterations; ++iter) {
        double sum_error0 = 0.0;
        double sum_error1 = 0.0;

        // Calcul des erreurs
        for (int i = 0; i < m; ++i) {
            double estimatePrice = theta0 + (theta1 * norm_mileages[i]);
            double error = estimatePrice - prices[i];
            
            sum_error0 += error;
            sum_error1 += error * norm_mileages[i];
        }

        // Formule du sujet
        double tmp_theta0 = learningRate * (1.0 / m) * sum_error0;
        double tmp_theta1 = learningRate * (1.0 / m) * sum_error1;

        theta0 -= tmp_theta0;
        theta1 -= tmp_theta1;
    }

    // Dénormalisation
    double final_theta1 = theta1 / (max_km - min_km);
    double final_theta0 = theta0 - (final_theta1 * min_km);

    std::ofstream outFile("thetas.txt");
    if (outFile.is_open()) {
        outFile << final_theta0 << "\n" << final_theta1 << "\n";
        outFile.close();
        std::cout << "Entrainement termine avec succes ! Thetas sauvegardes." << std::endl;
    }

    // Bonus metrics
    // MAE (Mean Absolute Error)
    double mae = 0.0;

    for (int i = 0; i < m; ++i) {
        double prediction = final_theta0 + (final_theta1 * mileages[i]);
        double erreur_price_euro = std::abs(prices[i] - prediction);

        mae += erreur_price_euro;
    }
    mae /=  m;

    std::cout << "MAE : " << mae << "€ en moyenne." << std::endl;

    // MAE (Mean Squared Error)
    double mse = 0.0;

    for (int i = 0; i < m; ++i) {
        double prediction = final_theta0 + (final_theta1 * mileages[i]);
        double erreur_au_carre = (prices[i] - prediction) * (prices[i] - prediction);
        mse += erreur_au_carre;
    }
    mse /=  m;
    std::cout << "MSE : " << mse << std::endl;

    // R²
    double mean_price = 0;
    for (int i = 0; i < m; i++) {
        mean_price += prices[i];
    }
    mean_price /= m;

    double variance = 0;
    for (int i = 0; i < m; i++) {
        variance += (prices[i] - mean_price) * (prices[i] - mean_price);
    }
    variance /= m;

    double R2 = 1.0 - (mse / variance);
    std::cout << "R²  : " << R2*100 << "%" << std::endl;

    return 0;
}