#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../analizador.h"

TEST_CASE("buscarSubcadena encuentra patrones", "[subcadena]") {
    REQUIRE(buscarSubcadena("abcde", "bcd") == 2);
    REQUIRE(buscarSubcadena("abcde", "xyz") == -1);
}

TEST_CASE("palindromoMasLargo detecta correctamente", "[palindromo]") {
    auto [inicio, fin, pal] = palindromoMasLargo("banana");
    REQUIRE(pal == "anana");
    REQUIRE(inicio == 2);
    REQUIRE(fin == 6);
}

TEST_CASE("lcs encuentra subsecuencia común", "[lcs]") {
    auto [sx, ex, sy, ey, common] = lcs("abcde", "abfde");
    REQUIRE(common == "de");
    REQUIRE(sx == 4);
    REQUIRE(ex == 5);
}
