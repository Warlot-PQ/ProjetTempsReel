#ifndef CIMENTERIE_H
#define CIMENTERIE_H

#include <stdio.h>
#include <stdlib.h>
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
#define vitesse_moteur_max									10
//----------------Tampons
extern float tampon_cmd[NB_COMMANDE * 3];
extern float tampon_qte_silos[6]; 
extern int tampon_fonct_calcul[5];
extern int niveau_eau;
extern float quantite_eau_restante;
extern float quantite_agregat_restante;
extern float quantite_agregat_totale;
extern float quantite_ciment_restante;
extern float quantite_ciment_totale;

//----------------Information sur le versement de l'eau
extern int versement_eau_possible;
extern int versement_eau_en_cours;

//----------------Sémaphores d'exclusion mutuel
extern SEM_ID sem_tampon_cmd;
extern SEM_ID sem_tampon_qte_silos;
extern SEM_ID sem_tampon_fonct_calcul;
extern SEM_ID sem_niveau_eau;
extern SEM_ID sem_quantite_eau_restante;
extern SEM_ID sem_quantite_agregat_restante;
extern SEM_ID sem_quantite_agregat_totale;
extern SEM_ID sem_quantite_ciment_restante;
extern SEM_ID sem_quantite_ciment_totale;
extern SEM_ID sem_versement_eau_possible;

//----------------Sémaphore de synchronisation des tâches entre elles
extern SEM_ID sem_fin_agregat;
extern SEM_ID sem_fin_ciment;
extern SEM_ID sem_fin_eau;
extern SEM_ID sem_fin_malaxeur;
extern SEM_ID sem_debut_malaxeur;

extern SEM_ID sem_calcul_agregat;
extern SEM_ID sem_calcul_ciment;
extern SEM_ID sem_calcul_eau;

extern SEM_ID sem_int_min_agr_1;
extern SEM_ID sem_int_min_agr_2;
extern SEM_ID sem_int_min_agr_3;
extern SEM_ID sem_int_max_agr_1;
extern SEM_ID sem_int_max_agr_2;
extern SEM_ID sem_int_max_agr_3;

extern SEM_ID sem_int_min_cim_1;
extern SEM_ID sem_int_min_cim_2;
extern SEM_ID sem_int_max_cim_1;
extern SEM_ID sem_int_max_cim_2;

extern SEM_ID sem_int_max_eau;
extern SEM_ID sem_int_min_eau;

extern SEM_ID sem_demande_versement_agregat;
extern SEM_ID sem_demande_versement_ciment;
extern SEM_ID sem_demande_versement_eau;

extern MSG_Q_ID file_debut_remplissage_balance_agregat;
extern SEM_ID sem_fin_remplissage_balance_agregat;	//signal la fin du versement d'un silo, demande de fermeture de vanne

extern MSG_Q_ID file_debut_remplissage_balance_ciment;
extern SEM_ID sem_fin_remplissage_balance_ciment;	//signal la fin du versement d'un silo, demande de fermeture de vanne

//sémaphore de synchro des balances
extern SEM_ID sem_pret_balance_agregat;
extern SEM_ID sem_pret_balance_ciment;
extern SEM_ID sem_ouverture_balance_agregat;	//demande d'ouverture
extern SEM_ID sem_ouverture_balance_ciment;		//demande d'ouverture
extern SEM_ID sem_fin_vers_balance_agregat;
extern SEM_ID sem_fin_vers_balance_ciment;

extern SEM_ID sem_agregat_et_ciment_suivant;

extern SEM_ID sem_debut_moteur;
extern SEM_ID sem_debut_camion;
extern SEM_ID sem_position_camion_ok;
extern SEM_ID sem_diode_eteindre_camion;
extern SEM_ID sem_position_ok;
extern SEM_ID sem_arret_rotation_moteur;
extern SEM_ID sem_vide_malaxeur;
extern SEM_ID sem_van_ferme_malaxeur;
extern SEM_ID sem_van_ouvre_malaxeur;
extern SEM_ID sem_stop_bal_tapis_agrEtCim;
extern SEM_ID sem_reprise_bal_tapis_agrEtCim;

extern MSG_Q_ID file_intensite;

typedef struct type_beton{
	int agregat_1;
	int agregat_2;
	int agregat_3;
	int ciment_1;
	int ciment_2;
	int eau;
}type_beton;

extern type_beton beton_type_1;
extern type_beton beton_type_2;
extern type_beton beton_type_3;
extern K = 0.5;

#endif
