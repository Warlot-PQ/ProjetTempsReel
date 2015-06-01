#ifndef SIGNAUX_EXTERIEUR_H
#define SIGNAUX_EXTERIEUR_H

//----------------Emission
void van_haut_ouvr_agregat(int);

void van_haut_ferm_agregat(int);

void van_bas_ouvr_agregat(int);

void van_bas_ferm_agregat(int);

void van_haut_ouvr_ciment(int);

void van_haut_ferm_ciment(int);

void van_bas_ouvr_ciment(int);

void van_bas_ferm_ciment(int);

void van_haut_ouvr_eau();

void van_haut_ferm_eau();

void van_bas_ouvr_eau();

void van_bas_ferm_eau();

void demande_hygrometrie(); //demande l'hygrometrie et bloque tant que la valeur n'est pas reçu

void av_tapis_agr();

void ar_tapis_agr();

void av_tapis_cim();

void ar_tapis_cim();

void van_ouvr_bal_cim();

void van_ferm_bal_cim();

//----------------Reception
Silos Agrégat min
Silos Agrégat max
Silos Ciment min
Silos Ciment max

Silo Eau min
Silo Eau max
Silo Eau moins
Silo Eau plus
#endif