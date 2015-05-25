#include "cimenterie.h"
#include "accesTampons.h"
#include "taches.h"
#include "signauxExterieur.h"

int gestion_IHM(){
	char valeur_volume;
	char valeur_beton;
	char valeur_distance;
	
	while(1){
		printf("Entrez le volume de béton souhaité :\n");
		valeur_volume = getchar();
		printf("Entrez le type de béton souhaité (1,2,3) :\n");
		valeur_beton = getchar();
		printf("Entrez la distance à parcourir :\n");
		valeur_distance = getchar();
		
		if (tampon_fonct_calcul_plein() == PB){
			printf("Nombre maximum de commande en cours de traitement atteint !\n");
		} else {
			//Signale que l'arrivée d'une commande plus recente
			incremente_tampon_fonct_calcul_cmd_plus_recente();
			//Remplie les caractéristiques de la commande la plus recente
			ecrire_tampon_cmd_cmd_plus_recent_volume((int) valeur_volume);
			ecrire_tampon_cmd_cmd_plus_recent_beton((int) valeur_beton);
			ecrire__tampon_cmd_cmd_plus_recent_distance((int) valeur_distance);
			
			//Test toute première commande
			if (is_tampon_fonct_calcul_premiere_cmd() != PB){
				//Fixe la commande en cours comme étant la première
				set_tampon_fonct_calcul_premiere_cmd();
				
				//TODO lance calcul_eau, calcul_agr et calcul_cim
			}
		}
	}
	return 0;
}
int gestion_evenement_malax(){
	
	return 0;
}
int gestion_evenement_agregat(){
	
	return 0;
}
int gestion_evenement_ciment(){
	
	return 0;
}
int gestion_evenement_eau(){
	while(1){
		semTake(sem_fin_eau);
		
		incremente_tampon_fonct_calcul_cmd_eau();
	}
	return 0;
}

int calcul_qte_eau(){
	
	return 0;
}
int calcul_qte_agregat(){
	
	return 0;
}
int calcul_qte_ciment(){
	
	return 0;
}

int versement_agregat(){
	//Numéro du silo à ouvrir
	int num_silo = 0;
	
	while(1){
		//Attente de la demande de versement d'agregat
		semTake(sem_demande_versement_agregat, WAIT_FOREVER);
		
		for (num_silo = 1; num_silo <= 3; num_silo += 1) {
			//Signal de début de versement à la balance
			msgQSend(file_debut_remplissage_balance_agregat, (char *) num_silo, 1, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			//Ouverture du silo num_silo
			van_bas_ouvr_agregat((int) num_silo);
			
			semTake(sem_demande_versement_agregat, WAIT_FOREVER)
			
			//Fermeture du silo num_silo
			van_bas_ferm_agregat((int) num_silo);
		}
	}
	return 0;
}
int remplissage_agregat_1(){
	while(1){
		semTake(sem_int_min_agr_1, WAIT_FOREVER);
		
		van_haut_ouvr_agregat(1);
		
		semTake(sem_int_max_agr_1, WAIT_FOREVER);
		
		van_haut_ferm_agregat(1);
	}
	
	return 0;
}
int remplissage_agregat_2(){
	while(1){
		semTake(sem_int_min_agr_2, WAIT_FOREVER);
		
		van_haut_ouvr_agregat(2);
		
		semTake(sem_int_max_agr_2, WAIT_FOREVER);
		
		van_haut_ferm_agregat(2);
	}
		
	return 0;
}
int remplissage_agregat_3(){
	while(1){
		semTake(sem_int_min_agr_3, WAIT_FOREVER);
		
		van_haut_ouvr_agregat(3);
		
		semTake(sem_int_max_agr_3, WAIT_FOREVER);
		
		van_haut_ferm_agregat(3);
	}
		
	return 0;
}

int versement_ciment(){
	//Numéro du silo à ouvrir
	int num_silo = 0;
	
	while(1){
		//Attente de la demande de versement d'agregat
		semTake(sem_demande_versement_ciment, WAIT_FOREVER);
		
		for (num_silo = 1; num_silo <= 3; num_silo += 1) {
			//Signal de début de versement à la balance
			msgQSend(file_debut_remplissage_balance_ciment, (char *) num_silo, 1, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			//Ouverture du silo num_silo
			van_bas_ouvr_ciment((int) num_silo);
			
			semTake(sem_demande_versement_ciment, WAIT_FOREVER)
			
			//Fermeture du silo num_silo
			van_bas_ferm_ciment((int) num_silo);
		}
	}
	return 0;
}
int remplissage_ciment_1(){
	while(1){
		semTake(sem_int_min_cim_1, WAIT_FOREVER);
		
		van_haut_ouvr_ciment(1);
		
		semTake(sem_int_max_cim_1, WAIT_FOREVER);
		
		van_haut_ferm_ciment(1);
	}
		
	return 0;
}
int remplissage_ciment_2(){
	while(1){
		semTake(sem_int_min_cim_2, WAIT_FOREVER);
		
		van_haut_ouvr_ciment(2);
		
		semTake(sem_int_max_cim_2, WAIT_FOREVER);
		
		van_haut_ferm_ciment(2);
	}
		
	return 0;
}

int gestion_balance_agregats(){
	
	return 0;
}
int gestion_balance_ciment(){
	
	return 0;
}

int gestion_synchro(){
	
	return 0;
}

int versement_eau(){
	
	return 0;
}
int remplissage_eau(){
	
	return 0;
}

int gestion_position_camion(){
	
	return 0;
}
int gestion_versement(){
	
	return 0;
}
int gestion_moteur(){
	
	return 0;
}