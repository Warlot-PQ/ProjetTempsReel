#ifndef ACCES_TAMPONS_H
#define ACCES_TAMPONS_H

#include <stdio.h>
#include <unistd.h>

//----------------Fonctions d'accès aux tampons
//Tampon commande
int ecrire__tampon_cmd_cmd_plus_recent_distance(float distance);
int ecrire_tampon_cmd_cmd_plus_recent_volume(float volume);
int ecrire_tampon_cmd_cmd_plus_recent_beton(float beton);
float lire_tampon_cmd_cmd_plus_recent_distance();
float lire_tampon_cmd_cmd_plus_recent_volume();
float lire_tampon_cmd_cmd_plus_recent_beton();
//Tampon quantité
int ecrire_tampon_qte_silos_eau(float qte);
int ecrire_tampon_qte_silos_agregat(int numero_silo, float qte);
int ecrire_tampon_qte_silos_ciment(int numero_silo, float qte);
float lire_tampon_qte_silos_eau();
float lire_tampon_qte_silos_agregat(int numero_silo);
float lire_tampon_qte_silos_ciment(int numero_silo);
//Tampon fonctionnalité calcul
int incremente_tampon_fonct_calcul_cmd_plus_recente();
int incremente_tampon_fonct_calcul_cmd_en_cours();
int incremente_tampon_fonct_calcul_cmd_eau();
int incremente_tampon_fonct_calcul_cmd_agregat();
int incremente_tampon_fonct_calcul_cmd_ciment();
int lire_tampon_fonct_calcul_cmd_plus_recente();
int lire_tampon_fonct_calcul_cmd_en_cours();
int lire_tampon_fonct_calcul_cmd_eau();
int lire_tampon_fonct_calcul_cmd_agregat();
int lire_tampon_fonct_calcul_cmd_ciment();

#endif