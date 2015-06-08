#ifndef ACCES_TAMPONS_H
#define ACCES_TAMPONS_H

#include <stdio.h>
#include <unistd.h>

//----------------Fonctions d'accès aux tampons
//Tampon commande
int ecrire_tampon_cmd_cmd_plus_recent_distance(float distance);
int ecrire_tampon_cmd_cmd_plus_recent_volume(float volume);
int ecrire_tampon_cmd_cmd_plus_recent_beton(float beton);
int efface_commande_traitee();
float lire_tampon_cmd_cmd_plus_recent_distance();
float lire_tampon_cmd_cmd_plus_recent_volume();
int lire_tampon_cmd_cmd_plus_recent_beton();
float lire_tampon_cmd_cmd_agregat_en_cours_beton();
float lire_tampon_cmd_cmd_agregat_en_cours_volume();
float lire_tampon_cmd_cmd_agregat_en_cours_distance();
float lire_tampon_cmd_cmd_ciment_en_cours_beton();
float lire_tampon_cmd_cmd_ciment_en_cours_volume();
float lire_tampon_cmd_cmd_ciment_en_cours_distance();
float lire_tampon_cmd_cmd_eau_en_cours_beton();
float lire_tampon_cmd_cmd_eau_en_cours_volume();
float lire_tampon_cmd_cmd_eau_en_cours_distance();
//Tampon quantité
int ecrire_tampon_qte_silos_eau(float qte);
int ecrire_tampon_qte_silos_agregat(int numero_silo, float qte);
int ecrire_tampon_qte_silos_ciment(int numero_silo, float qte);
int decremente_tampon_qte_silos_eau();
int decremente_tampon_qte_silos_agregat(int numero_silo);
int decremente_tampon_qte_silos_ciment(int numero_silo);
int is_tampon_qte_silos_eau_nulle();
int is_tampon_qte_silos_agregat_nulle(int numero_silo);
int is_tampon_qte_silos_ciment_nulle(int numero_silo);
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
int tampon_fonct_calcul_plein();
int is_tampon_fonct_calcul_premiere_cmd();
int set_tampon_fonct_calcul_premiere_cmd();
//Versement eau possible
void set_versement_eau_possible(bool);
int is_versement_eau_possible();
#endif