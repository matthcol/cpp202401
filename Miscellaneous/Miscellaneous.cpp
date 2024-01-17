// NB: doc
// - constexpr: https://en.cppreference.com/w/cpp/language/constexpr
//
// compile (CLI): 
// g++ -std=c++20 Miscellaneous.cpp -o app
// cl /Zc:__cplusplus /std:c++20 .\Miscellaneous.cpp

#include <iostream>
#include <numbers>
#include <cmath>
#include <vector>

#define MY_VERSION 10
#define IF(test,expr1,expr2) (test ? expr1 : expr2)

constexpr double myabs(double x) {
    return x < 0 ? -x : x;
}


void playWithConstexprVariables() {
#if __cplusplus < 202002L
    const double TWO_PI = 4 * atan(1);
    const double VAL = 3 * myabs(-TWO_PI);
#else
    constexpr double TWO_PI = 2 * std::numbers::pi;
    constexpr double VAL = 3 * myabs(-TWO_PI);
#endif
    std::cout << "2 PI = " << TWO_PI << std::endl
        << "VAL = " << VAL << std::endl;;
}

constexpr size_t compute_size_nd(size_t nd, size_t size1d) {
    return nd * size1d;
}

void demoArraySizeConstExpr() {
    const size_t N = 1000;
    double temperatures[compute_size_nd(2, N)];
}

void playWithMyMacros() {
    std::vector<int> cppVersions{ 98,11,14,17,20,23,26 };
    for (auto version : cppVersions) {
        int fullVersion = IF(version == 98, version + 1900, version + 2000);
        std::cout << fullVersion << std::endl;
    }
}

int main()
{
    playWithConstexprVariables();
    std::cout << "C++ version (std): " << __cplusplus << std::endl
#ifdef _MSVC_LANG
        << "C++ version (MSVC): " << _MSVC_LANG << std::endl
#endif // _MSVC_LANG
    ;
    playWithMyMacros();
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
