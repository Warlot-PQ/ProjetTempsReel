//#ifndef TACHES_H
//#define TACHES_H

#include <stdio.h>
#include <unistd.h>
#include <semLib.h>
#include <msgQLib.h>
#include <taskLib.h>

//----------------Gestion IHM
//GestionIHM
int gestion_IHM();

//----------------Gestion quantité
//Gestion évènement
int gestion_evenement_fin_malax();
int gestion_evenement_fin_agregat();
int gestion_evenement_fin_ciment();
int gestion_evenement_fin_eau();
//Gestion quantité
int calcul_qte_eau();
int calcul_qte_agregat();
int calcul_qte_ciment();

//----------------Gestion silos agregats et ciments
//Gestion silos agregats
int versement_agregat();
int remplissage_agregat_1();
int remplissage_agregat_2();
int remplissage_agregat_3();
//Gestion silos ciments
int versement_ciment();
int remplissage_ciment_1();
int remplissage_ciment_2();

//----------------Gestion balances et tapis
//Gestion balances
int gestion_quantite_balance_agregats();
int gestion_quantite_balance_ciment();
int arret_et_reprise_versement_balances();

//----------------Gestion silo eau et malaxeur
//Gestion synchro
int gestion_synchro_balances();
//Gestion silo eau
int versement_eau();
int remplissage_eau();
//Gestion malaxeur
int gestion_position_camion();
int gestion_versement_malaxeur();
int gestion_moteur_malaxeur();

//----------------Collection de fonctions (ne sont pas des taches)
void capteur_vide_malaxeur();
void capteur_plein_silo_agregat_1();
void capteur_vide_silo_agregat_1();
void capteur_plein_silo_agregat_2();
void capteur_vide_silo_agregat_2();
void capteur_plein_silo_agregat_3();
void capteur_vide_silo_agregat_3();
void capteur_plein_silo_ciment_1();
void capteur_vide_silo_ciment_1();
void capteur_plein_silo_ciment_2();
void capteur_vide_silo_ciment_2();
void capteur_plus_balance_agregats();
void capteur_moins_balance_agregats();
void capteur_plus_balance_ciment();
void capteur_moins_balance_ciment();
void capteur_plein_eau();
void capteur_vide_eau();
void capteur_plus_eau();
void capteur_moins_eau();
//#endif
