//
// Created by Yaroslav Rebenko on 21.07.2018.
//

#ifndef GROBNERBASIS_MODULETERM_H
#define GROBNERBASIS_MODULETERM_H

#include "Polynomial.hpp"
#include "ModuleBasis.hpp"

template<typename Pow>
using ModuleMonomial = Term<Term<double, Monomial<Pow>>, ModuleBasis >;

template<typename Pow>
ModuleMonomial<Pow> operator*(const ModuleMonomial<Pow>& mt, const Term<double, Monomial<Pow>>& t) {
    return ModuleMonomial<Pow>(mt.coef * t, mt.monom);
}

#endif //GROBNERBASIS_MODULETERM_H
