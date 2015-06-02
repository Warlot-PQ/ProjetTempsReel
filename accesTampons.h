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
int tampon_fonct_calcul_plein();
int is_tampon_fonct_calcul_premiere_cmd();
int set_tampon_fonct_calcul_premiere_cmd();
//Niveau eau
int ecrire_niveau_eau_nul();
int ecrire_niveau_eau_max();
int incremente_niveau_eau();
int decremente_niveau_eau();
//Quantité eau restante
int ecrire_quantite_eau_restante(float);
int decremente_quantite_eau_restante();
int is_quantite_eau_restante_nulle();
//Quantité agregat restant
int ecrire_quantite_agregat_restante(float);
int decremente_quantite_agregat_restante();
int is_quantite_agregat_restante_nulle();
//Quantité agregat total
int ecrire_quantite_agregat_totale_nulle();
int ajouter_quantite_agregat_totale(float);
int decremente_quantite_agregat_totale();
int is_quantite_agregat_totale_nulle();
//Quantité ciment restant
int ecrire_quantite_ciment_restante(float);
int decremente_quantite_ciment_restante();
int is_quantite_ciment_restant_nulle();
//Quantité ciment total
int ecrire_quantite_ciment_totale_nulle();
int ajouter_quantite_ciment_totale(float);
int decremente_quantite_ciment_totale();
int is_quantite_ciment_totale_nulle();
//Versement eau possible
void set_versement_eau_possible(bool);
int is_versement_eau_possible();
#endif