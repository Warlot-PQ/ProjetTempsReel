#ifndef CIMENTERIE_H
#define CIMENTERIE_H

#include <stdio.h>
#include <unistd.h>
#include <semLib.h>

//----------------Constantes diverses
#define NB_COMMANDE 										10
#define NB_SILOS 											6
#define PB 													-1

//----------------Capacité silo en litre
#define NIVEAU_EAU_MAX										40

//----------------Index des tampons
#define index_tampon_cmd_distance							0
#define index_tampon_cmd_volume								1
#define index_tampon_cmd_beton								2

#define index_tampon_qte_silos_eau 							0
#define index_tampon_qte_silos_agregat_1 					1
#define index_tampon_qte_silos_agregat_2 					2
#define index_tampon_qte_silos_agregat_3 					3
#define index_tampon_qte_silos_ciment_1 					4
#define index_tampon_qte_silos_ciment_2						5

#define index_tampon_fonct_calcul_cmd_plus_recente 			0
#define index_tampon_fonct_calcul_cmd_en_cours				1
#define index_tampon_fonct_calcul_cmd_eau_en_cours 			2
#define index_tampon_fonct_calcul_cmd_agregat_en_cours 		3
#define index_tampon_fonct_calcul_cmd_ciment_en_cours 		4

//----------------Temps
#define temps_versement										20
#define temps_cst											15

//----------------Valeurs pour le moteur
#define Imax												10

//----------------Tampons
float tampon_cmd[NB_COMMANDE * 3];
float tampon_qte_silos[6]; 
int tampon_fonct_calcul[5];
int niveau_eau;
float quantite_eau_restante;
float quantite_agregat_restante;
float quantite_agregat_totale;
float quantite_ciment_restante;
float quantite_ciment_totale;

//----------------Information sur le versement de l'eau
int versement_eau_possible;
int versement_eau_en_cours;

//----------------Sémaphores d'exclusion mutuel
SEM_ID sem_tampon_cmd;
SEM_ID sem_tampon_qte_silos;
SEM_ID sem_tampon_fonct_calcul;
SEM_ID sem_niveau_eau;
SEM_ID sem_quantite_eau_restante;
SEM_ID sem_quantite_agregat_restante;
SEM_ID sem_quantite_agregat_totale;
SEM_ID sem_quantite_ciment_restante;
SEM_ID sem_quantite_ciment_totale;
SEM_ID sem_versement_eau_possible;

//----------------Sémaphore de synchronisation des tâches entre elles
SEM_ID sem_fin_agregat;
SEM_ID sem_fin_ciment;
SEM_ID sem_fin_eau;
SEM_ID sem_fin_malaxeur;
SEM_ID sem_debut_malaxeur;

SEM_ID sem_calcul_agregat;
SEM_ID sem_calcul_ciment;
SEM_ID sem_calcul_eau;

SEM_ID sem_int_min_agr_1;
SEM_ID sem_int_min_agr_2;
SEM_ID sem_int_min_agr_3;
SEM_ID sem_int_max_agr_1;
SEM_ID sem_int_max_agr_2;
SEM_ID sem_int_max_agr_3;

SEM_ID sem_int_min_cim_1;
SEM_ID sem_int_min_cim_2;
SEM_ID sem_int_max_cim_1;
SEM_ID sem_int_max_cim_2;

SEM_ID sem_int_max_eau;
SEM_ID sem_int_min_eau;

SEM_ID sem_demande_versement_agregat;
SEM_ID sem_demande_versement_ciment;
SEM_ID sem_demande_versement_eau;

MSG_Q_ID file_debut_remplissage_balance_agregat;
SEM_ID sem_fin_remplissage_balance_agregat;	//signal la fin du versement d'un silo, demande de fermeture de vanne

MSG_Q_ID file_debut_remplissage_balance_ciment;
SEM_ID sem_fin_remplissage_balance_ciment;	//signal la fin du versement d'un silo, demande de fermeture de vanne

//sémaphore de synchro des balances
SEM_ID sem_pret_balance_agregat;
SEM_ID sem_pret_balance_ciment;
SEM_ID sem_ouverture_balance_agregat;	//demande d'ouverture
SEM_ID sem_ouverture_balance_ciment;		//demande d'ouverture
SEM_ID sem_fin_vers_balance_agregat;
SEM_ID sem_fin_vers_balance_ciment;

SEM_ID sem_agregat_et_ciment_suivant;

SEM_ID sem_debut_moteur;
SEM_ID sem_debut_camion;
SEM_ID sem_diode_allumer_camion;
SEM_ID sem_diode_eteindre_camion;
SEM_ID sem_position_ok_camion;

SEM_ID sem_van_ferme_malaxeur;
SEM_ID sem_van_ouvre_malaxeur;

MSG_Q_ID file_intensite;

typedef struct type_beton{
	int agregat_1;
	int agregat_2;
	int agregat_3;
	int ciment_1;
	int ciment_2;
	int eau;
}type_beton;

type_beton beton_type_1;
type_beton beton_type_2;
type_beton beton_type_3;
//Ktest = 0.5;

#endif
