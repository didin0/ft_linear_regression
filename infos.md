# Compréhension du sujet
1. Tu dois implémenter une régression linéaire simple (1 variable: mileage).
2. Tu dois livrer 2 programmes:
3. predict (demande un mileage, calcule theta0 + theta1 * x)
4. train (lit dataset, entraîne theta0/theta1 via gradient descent, sauvegarde les paramètres)
5. Valeurs initiales: theta0 = 0, theta1 = 0.
6. Interdiction d’utiliser une fonction “magique” qui calcule directement la droite.
7. Point critique: mise à jour simultanée de theta0 et theta1 à chaque itération.

# Outils/Libraries recommandés en C++ moderne
## Essentiel (mandatory)
1. Build system: CMake (obligatoire en pratique pour un projet C++ propre).
2. Compilation:
3. clang++ ou g++
4. Standard C++20 (ou C++17 minimum)
5. Flags: -Wall -Wextra -Werror -pedantic -O2
6. CLI parsing: cxxopts (simple) ou CLI11 (plus complet).
7. CSV parsing:
8. Option A: parser maison (très bien pour apprendre)
9. Option B: fast-cpp-csv-parser si tu veux gagner du temps
10. Sérialisation des paramètres:
11. Fichier texte simple (theta0,theta1) suffit
12. Ou JSON avec nlohmann/json (propre et lisible)
# Qualité/industrialisation (fortement conseillé)
1. Format: clang-format
2. Lint statique: clang-tidy
3. Analyse mémoire/sécurité:
4. -fsanitize=address,undefined
5. valgrind (optionnel)
6. Tests unitaires: Catch2 ou GoogleTest
## Bonus visualisation/metrics
1. Graphiques:
2. matplot++ (C++ natif, proche matplotlib)
3. ou export CSV + script Python matplotlib (très pratique)
4. ou gnuplot-iostream
5. Metrics:
6. tu peux coder toi-même MSE, MAE, R² (recommandé ici)
7. pas besoin de grosse lib ML

# Architecture de projet proposée
src/core/LinearModel.hpp/.cpp
src/core/GradientDescentTrainer.hpp/.cpp
src/io/CsvReader.hpp/.cpp
src/io/ParameterStore.hpp/.cpp
src/apps/train.cpp
src/apps/predict.cpp
tests/ (unit tests)
data/ (dataset + éventuellement params)
CMakeLists.txt

# Étapes de réalisation (ordre optimal)
1. Initialiser le squelette CMake
2. 2 exécutables: train et predict
3. activer warnings stricts + sanitizers en Debug
4. Implémenter le modèle linéaire minimal
5. estimate(x) = theta0 + theta1 * x
6. classe immutable ou mutable simple avec getters/setters
7. Implémenter lecture dataset CSV
8. vérifier colonnes attendues (km, price ou similaire)
9. valider données numériques
10. gérer erreurs de fichier proprement
11. Implémenter la descente de gradient
12. calcul des gradients sur tout le dataset
13. utiliser tmp_theta0 et tmp_theta1
14. mettre à jour simultanément
15. hyperparamètres: learning_rate, iterations
16. Normalisation (très recommandé)
17. min-max ou z-score sur mileage
18. entraîne plus stable et plus rapide
19. stocker les infos de normalisation pour predict
20. Sauvegarde/chargement paramètres
21. sauver theta0, theta1 (+ normalisation si utilisée)
22. predict doit marcher même sans entraînement préalable:
23. fallback sur 0,0 ou message explicite
24. Implémenter CLI propre
25. train --data data.csv --lr 0.01 --iters 10000 --out model.json
26. predict --model model.json --mileage 120000
27. Ajouter tests unitaires
28. test estimate simple
29. test 1-2 itérations de gradient sur mini dataset connu
30. test parsing CSV invalide
31. test sauvegarde/chargement modèle
32. Ajouter métriques (bonus)
33. MSE, MAE, R²
34. affichage après entraînement
35. Ajouter visualisation (bonus)
36. scatter plot des points
37. droite de régression superposée

# Pièges fréquents à éviter
1. Oublier la mise à jour simultanée de theta0/theta1.
2. Learning rate trop grand (divergence) ou trop petit (apprentissage lent).
3. Oublier la normalisation si les km sont grands.
4. Mauvaise gestion du cas “fichier modèle absent”.
5. Ne pas séparer logique métier et I/O (rend le test difficile).

# Paramètres de départ recommandés
1. iterations: 5000 à 20000
2. learning_rate:
3. sans normalisation: très petit (1e-10 à 1e-8, à ajuster)
4. avec normalisation: 1e-3 à 1e-1 (souvent plus simple)
5. early stopping: stop si variation de coût < epsilon