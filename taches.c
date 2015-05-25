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
	int cmd_plus_recente, cmd_en_cours;
	
	while(1){
		semTake(sem_fin_agregat, WAIT_FOREVER);
		
		cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();
		cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
		
		if(cmd_plus_recente != cmd_en_cours){
			incremente_tampon_fonct_calcul_cmd_agregat();
			semGive(sem_calcul_agregat);
		}
	}
	
	return 0;
}
int gestion_evenement_ciment(){
	int cmd_plus_recente, cmd_en_cours;
		
		while(1){
			semTake(sem_fin_ciment, WAIT_FOREVER);
			
			cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();
			cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
			
			if(cmd_plus_recente != cmd_en_cours){
				incremente_tampon_fonct_calcul_cmd_ciment();
				semGive(sem_calcul_ciment);
			}
		}
		
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
	float B, V, D, qte_eau, hygronometrie;
	
	while(1){
		semTake(sem_calcul_eau, WAIT_FOREVER);
		demande_hygrometrie();
		
//----------------Lecture des valeurs B, V, D dans le tampon_cmd		
		B = lire_tampon_cmd_cmd_plus_recent_beton();
		V = lire_tampon_cmd_cmd_plus_recent_volume();
		D = lire_tampon_cmd_cmd_plus_recent_distance();
		
//----------------Calcul de la quantité d'eau voulue selon le type de béton
		switch(B){
			case 1:
				qte_eau = beton_type_1.eau*V - hygronometrie*V*beton_type_1.agregat_1 + K*D;
				break;
			case 2:
				qte_eau = beton_type_2.eau*V - hygronometrie*V*beton_type_2.agregat_1 + K*D;
				break;
			case 3:
				qte_eau = beton_type_3.eau*V - hygronometrie*V*beton_type_3.agregat_1 + K*D;
				break;
			default:
				printf("calcul_qte_agregat : default case !\n");
				return PB;
		}
		
//----------------Ecriture dans tampon_qte
		ecrire_tampon_qte_silos_eau(qte_eau);
		
//----------------Signale la tache "gestion synchro" que le système traite la commande suivante 	
		semGive(sem_agregat_et_ciment_suivant);
	}
	return 0;
}
int calcul_qte_agregat(){
	float B, V, D, agregat_1, agregat_2, agregat_3;


	while(1){
		semTake(sem_calcul_agregat, WAIT_FOREVER);
		
//----------------Lecture des valeurs B, V, D dans le tampon_cmd
		B = lire_tampon_cmd_cmd_plus_recent_beton();
		V = lire_tampon_cmd_cmd_plus_recent_volume();
		D = lire_tampon_cmd_cmd_plus_recent_distance();

//----------------Calcul des quantités d'agrégats voulues selon la valeur de B
		switch(B){
			case 1:
				agregat_1 = beton_type_1.agregat_1*V;
				agregat_2 = beton_type_1.agregat_2*V;
				agregat_3 = beton_type_1.agregat_3*V;
				break;
			case 2:
				agregat_1 = beton_type_2.agregat_1*V;
				agregat_2 = beton_type_2.agregat_2*V;
				agregat_3 = beton_type_2.agregat_3*V;
				break;
			case 3:
				agregat_1 = beton_type_3.agregat_1*V;
				agregat_2 = beton_type_3.agregat_2*V;
				agregat_3 = beton_type_3.agregat_3*V;
				break;
			default:
				printf("calcul_qte_agregat : default case !\n");
				return PB;
		}

//----------------Ecriture des quantités dans le tampon_qte
		ecrire_tampon_qte_silos_agregat(1, agregat_1);
		ecrire_tampon_qte_silos_agregat(2, agregat_2);
		ecrire_tampon_qte_silos_agregat(3, agregat_3);
	
//----------------Signale la tache "gestion remplissage et versement silos" que le tampon_qte a été mis à jour
		semGive(sem_demande_versement_agregat);
	}
	
	return 0;
}
int calcul_qte_ciment(){
	float B, V, D, ciment_1, ciment_2;
	
	while(1){
		semTake(sem_calcul_ciment, WAIT_FOREVER);
		
//----------------Lecture des valeurs B, V, D dans le tampon_cmd
		B = lire_tampon_cmd_cmd_plus_recent_beton();
		V = lire_tampon_cmd_cmd_plus_recent_volume();
		D = lire_tampon_cmd_cmd_plus_recent_distance();
	
//----------------Calcul des quantités d'agrégats voulues selon la valeur de B
		switch(B){
			case 1:
				agregat_1 = beton_type_1.ciment_1*V;
				agregat_2 = beton_type_1.ciment_2*V;
				break;
			case 2:
				agregat_1 = beton_type_2.ciment_1*V;
				agregat_2 = beton_type_2.ciment_2*V;
				break;
			case 3:
				agregat_1 = beton_type_3.ciment_1*V;
				agregat_2 = beton_type_3.ciment_2*V;
				break;
			default:
				printf("calcul_qte_ciment : default case !\n");
				return PB;
		}
	
//----------------Ecriture des quantités dans le tampon_qte
		ecrire_tampon_qte_silos_ciment(1, ciment_1);
		ecrire_tampon_qte_silos_ciment(2, ciment_2);
			
//----------------Signale la tache "gestion remplissage et versement silos" que le tampon_qte a été mis à jour
		semGive(sem_demande_versement_ciment);
	}
		
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
			
			semTake(sem_fin_remplissage_balance_agregat, WAIT_FOREVER);
			
			//Fermeture du silo num_silo
			van_bas_ferm_agregat((int) num_silo);
		}
	}
	return 0;
}
int remplissage_agregat_1(){
	//Initialisation du système, remplissage du silo
	van_haut_ouvr_agregat(1);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_agr_1, WAIT_FOREVER);
	
	van_haut_ferm_agregat(1);
	
	while(1){
		semTake(sem_int_min_agr_1, WAIT_FOREVER);
		
		van_haut_ouvr_agregat(1);
		
		semTake(sem_int_max_agr_1, WAIT_FOREVER);
		
		van_haut_ferm_agregat(1);
	}
	
	return 0;
}
int remplissage_agregat_2(){
	//Initialisation du système, remplissage du silo
	van_haut_ouvr_agregat(2);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_agr_2, WAIT_FOREVER);
	
	van_haut_ferm_agregat(2);
	
	while(1){
		semTake(sem_int_min_agr_2, WAIT_FOREVER);
		
		van_haut_ouvr_agregat(2);
		
		semTake(sem_int_max_agr_2, WAIT_FOREVER);
		
		van_haut_ferm_agregat(2);
	}
		
	return 0;
}
int remplissage_agregat_3(){
	//Initialisation du système, remplissage du silo
	van_haut_ouvr_agregat(3);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_agr_3, WAIT_FOREVER);
	
	van_haut_ferm_agregat(3);
	
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
		
		for (num_silo = 1; num_silo <= 2; num_silo += 1) {
			//Signal de début de versement à la balance
			msgQSend(file_debut_remplissage_balance_ciment, (char *) num_silo, 1, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			//Ouverture du silo num_silo
			van_bas_ouvr_ciment((int) num_silo);
			
			semTake(sem_fin_remplissage_balance_ciment, WAIT_FOREVER)
			
			//Fermeture du silo num_silo
			van_bas_ferm_ciment((int) num_silo);
		}
	}
	return 0;
}
int remplissage_ciment_1(){
	//Initialisation du système, remplissage du silo
	van_haut_ouvr_ciment(1);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_cim_1, WAIT_FOREVER);
	
	van_haut_ferm_ciment(1);
	
	while(1){
		semTake(sem_int_min_cim_1, WAIT_FOREVER);
		
		van_haut_ouvr_ciment(1);
		
		semTake(sem_int_max_cim_1, WAIT_FOREVER);
		
		van_haut_ferm_ciment(1);
	}
		
	return 0;
}
int remplissage_ciment_2(){
	//Initialisation du système, remplissage du silo
	van_haut_ouvr_ciment(2);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_cim_2, WAIT_FOREVER);
	
	van_haut_ferm_ciment(2);
	
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
	while(1){
		semTake(sem_demande_versement_eau, WAIT_FOREVER);
		
		
		
		
		
		
		
		
	}
	
	return 0;
}
int remplissage_eau(){
	ecrire_niveau_eau_nul();
	
	// Initialisation du système, remplissage du silo
	semTake(versement_eau, WAIT_FOREVER); // versement impossible
	
	van_haut_ouvr_eau();
	
	// Attente de l'évènement silo plein
	semTake(sem_int_max_eau, WAIT_FOREVER);
	
	van_haut_ferm_eau();
	ecrire_niveau_eau_max();
	semGive(versement_eau);		// autorise le versment
	
	while(1){
		semTake(sem_int_min_eau, WAIT_FOREVER);		// silo eau vide
		semTake(versement_eau, WAIT_FOREVER); // versement impossible
		
		van_haut_ouvr_eau();
		
		// Attente de l'évènement silo plein
		semTake(sem_int_max_eau, WAIT_FOREVER);
		
		van_haut_ferm_eau();
		ecrire_niveau_eau_max();
		semGive(versement_eau);		// autorise le versment
	}
	
	return 0;
}

int compteur_plus_eau(){
	while (1){
		semTake(sem_int_plus_eau, WAIT_FOREVER);
		incremente_niveau_eau();
	}
	
	return 0;
}

int compteur_moins_eau(){
	while (1){
		semTake(sem_int_moins_eau, WAIT_FOREVER);
		decremente_niveau_eau();
	}
	
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