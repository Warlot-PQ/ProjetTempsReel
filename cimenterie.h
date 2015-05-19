#ifndef CIMENTERIE_H
#define CIMENTERIE_H

#include <stdio.h>
#include <unistd.h>
#include <semLib.h>

//----------------Constantes diverses
#define NB_COMMANDE 										10
#define NB_SILOS 											6
#define PB 													-1

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

//----------------Tampons
extern float tampon_cmd[NB_COMMANDE * 3];
extern float tampon_qte_silos[6]; 
extern float tampon_fonct_calcul[5];

//----------------Sémaphore d'exclusion mutuel
extern SEM_ID sem_tampon_cmd;
extern SEM_ID sem_tampon_qte_silos;
extern SEM_ID sem_tampon_fonct_calcul;

//----------------Sémaphore de synchronisation des tâches entre elles
extern SEM_ID sem_fin_eau;

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

#endif
