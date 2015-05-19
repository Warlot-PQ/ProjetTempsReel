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
float tampon_cmd[NB_COMMANDE * 3];
float tampon_qte_silos[6]; 
float tampon_fonct_calcul[5];

//----------------Sémaphore d'exclusion mutuel
SEM_ID sem_tampon_cmd;
SEM_ID sem_tampon_qte_silos;
SEM_ID sem_tampon_fonct_calcul;

#endif
