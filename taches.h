#ifndef TACHES_H
#define TACHES_H

#include <stdio.h>
#include <unistd.h>
#include <semLib.h>
#include <msgQLib.h>

//----------------Gestion IHM
//GestionIHM
int gestion_IHM();

//----------------Gestion quantité
//Gestion évènement
int gestion_evenement_malax();
int gestion_evenement_agregat();
int gestion_evenement_ciment();
int gestion_evenement_eau();
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
int gestion_balance_agregats();
int gestion_balance_ciment();

//----------------Gestion silo eau et malaxeur
//Gestion synchro
int gestion_synchro();
//Gestion silo eau
int versement_eau();
int remplissage_eau();
//Gestion malaxeur
int gestion_position_camion();
int gestion_versement();
int gestion_moteur();

//----------------Collection de fonctions (ne sont pas des taches)
int compteur_plus_balance_agregats();
int compteur_moins_balance_agregats();
int compteur_plus_balance_ciment();
int compteur_moins_balance_ciment();
int compteur_plus_eau();
int compteur_moins_eau();

#endif
