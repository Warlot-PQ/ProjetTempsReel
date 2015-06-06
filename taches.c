#include "cimenterie.h"
#include "accesTampons.h"
#include "taches.h"
#include "signauxExterieur.h"
#include <stdio.h>

/*
 *	Vider le terminal : printf("\33[2J"); 
*/

int gestion_IHM(){
	char valeur_volume[20];
	char valeur_beton[20];
	char valeur_distance[20];
	
	//while(1){
		printf("Initialisation de la cimenterie, remplissage des silos\n");
		semTake(sem_init_remplissage_silo_agr_1, WAIT_FOREVER);
		semTake(sem_init_remplissage_silo_agr_2, WAIT_FOREVER);
		semTake(sem_init_remplissage_silo_agr_3, WAIT_FOREVER);
		semTake(sem_init_remplissage_silo_cim_1, WAIT_FOREVER);
		semTake(sem_init_remplissage_silo_cim_2, WAIT_FOREVER);
		semTake(sem_init_remplissage_silo_eau, WAIT_FOREVER);
			
		printf("Entrez le volume de béton, le type souhaité (1, 2 ou 3) et la distance à parcourir (séparé par les espaces, ex : 50 2 10) :\n");
		//scanf("%d %d %d", &valeur_volume, &valeur_beton, &valeur_distance);
		
		if (tampon_fonct_calcul_plein() == PB){
			printf("Nombre maximum de commande en cours de traitement atteint !\n");
		} else {
			//Signale que l'arrivée d'une commande plus recente
			incremente_tampon_fonct_calcul_cmd_plus_recente();
			//Remplie les caractéristiques de la commande la plus recente
			//ecrire_tampon_cmd_cmd_plus_recent_volume(atoi(valeur_volume));
			//ecrire_tampon_cmd_cmd_plus_recent_beton(atoi(valeur_beton));
			//ecrire_tampon_cmd_cmd_plus_recent_distance(atoi(valeur_distance));
			ecrire_tampon_cmd_cmd_plus_recent_volume(20);
			ecrire_tampon_cmd_cmd_plus_recent_beton(2);
			ecrire_tampon_cmd_cmd_plus_recent_distance(30);
			//Test toute première commande
			if (is_tampon_fonct_calcul_premiere_cmd() != PB){
				//Fixe la commande en cours comme étant la première
				set_tampon_fonct_calcul_premiere_cmd();
				
				printf("Volume : %f, Béton : %d, Distance : %f\n", 
						lire_tampon_cmd_cmd_plus_recent_volume(),
						lire_tampon_cmd_cmd_plus_recent_beton(),
						lire_tampon_cmd_cmd_plus_recent_distance());
				printf("Lancement de la commande !\n");
				semGive(sem_calcul_agregat);
				semGive(sem_calcul_ciment);
				semGive(sem_calcul_eau);
			} else {
				printf("ERREUR %d\n", is_tampon_fonct_calcul_premiere_cmd());
			}
		//}
	}
	return 0;
}
int gestion_evenement_malax(){
	int cmd_plus_recente, cmd_en_cours, index_boucle;
	
	while(1){
		semTake(sem_fin_malaxeur, WAIT_FOREVER);
		
		cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();
		cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
		
		if(cmd_plus_recente != cmd_en_cours){
					efface_commande_traitee();
					incremente_tampon_fonct_calcul_cmd_en_cours();
					semGive(sem_calcul_eau);
		}else{
			for(index_boucle = 0; index_boucle < NB_COMMANDE * 3; index_boucle += 1){
					tampon_cmd[index_boucle] = 0;
			}
				
			for(index_boucle = 0; index_boucle < NB_SILOS; index_boucle += 1){
					tampon_qte_silos[index_boucle] = 0;
			}
				
			tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente] = -1;
			tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours] = -1;
			tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_eau_en_cours] = 0;
			tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_agregat_en_cours] = 0;
			tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_ciment_en_cours] = 0;
		}
	}
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
		semTake(sem_fin_eau, WAIT_FOREVER);
		
		incremente_tampon_fonct_calcul_cmd_eau();
	}
	return 0;
}

int calcul_qte_eau(){
	float V, D, qte_eau;
	int i, B, hygrometrie;
	
	while(1){
		semTake(sem_calcul_eau, WAIT_FOREVER);
		hygrometrie = getHygrometrie();
		//printf("hygronometrie : %d\n", hygrometrie);
//----------------Lecture des valeurs B, V, D dans le tampon_cmd		
	
		printf("cmd en cours : %d\n\n", lire_tampon_fonct_calcul_cmd_en_cours());
		printf("type de béton : %d\n\n", lire_tampon_cmd_cmd_plus_recent_beton());
		
		
		B = lire_tampon_cmd_cmd_plus_recent_beton();
		V = lire_tampon_cmd_cmd_plus_recent_volume();
		D = lire_tampon_cmd_cmd_plus_recent_distance();
		
		//printf("B : %d\n", B);
		//printf("V : %f\n", V);
		//printf("D : %f\n", D);
//----------------Calcul de la quantité d'eau voulue selon le type de béton
		switch(B)
		{
			case 1:
					qte_eau = beton_type_1.eau/100.0*V - HYGROMETRIE/100.0*beton_type_1.agregat_1/100*V + k_hygronometrie*D;
				break;
			case 2:
					qte_eau = beton_type_2.eau/100.0*V - HYGROMETRIE/100.0*beton_type_2.agregat_1/100*V + k_hygronometrie*D;
				break;
			case 3:
					qte_eau = beton_type_3.eau/100.0*V - HYGROMETRIE/100.0*beton_type_3.agregat_1/100*V + k_hygronometrie*D;
				break;
			default:
				printf("calcul_qte_agregat : default case !\n");
				return PB;
		}
//----------------Ecriture dans tampon_qte
		ecrire_tampon_qte_silos_eau(qte_eau);
		
		printf("Quantité eau: %f\n", qte_eau);
		
//----------------Signale la tache "gestion synchro" que le système traite la commande suivante 	
		semGive(sem_agregat_et_ciment_suivant);
	}
	return 0;
}
int calcul_qte_agregat(){
	float V, D, agregat_1, agregat_2, agregat_3;
	int B;

	while(1){
		semTake(sem_calcul_agregat, WAIT_FOREVER);
		
//----------------Lecture des valeurs B, V, D dans le tampon_cmd
		B = lire_tampon_cmd_cmd_plus_recent_beton();
		V = lire_tampon_cmd_cmd_plus_recent_volume();
		D = lire_tampon_cmd_cmd_plus_recent_distance();
		
		//printf("B : %d\n", B);
		//printf("V : %f\n", V);
		//printf("D : %f\n", D);
//----------------Calcul des quantités d'agrégats voulues selon la valeur de B
		switch(B){
			case 1:
				agregat_1 = beton_type_1.agregat_1/100.0*V;
				agregat_2 = beton_type_1.agregat_2/100.0*V;
				agregat_3 = beton_type_1.agregat_3/100.0*V;
				break;
			case 2:
				agregat_1 = beton_type_2.agregat_1/100.0*V;
				agregat_2 = beton_type_2.agregat_2/100.0*V;
				agregat_3 = beton_type_2.agregat_3/100.0*V;
				break;
			case 3:
				agregat_1 = beton_type_3.agregat_1/100.0*V;
				agregat_2 = beton_type_3.agregat_2/100.0*V;
				agregat_3 = beton_type_3.agregat_3/100.0*V;
				break;
			default:
				printf("calcul_qte_agregat : default case !\n");
				return PB;
		}

//----------------Ecriture des quantités dans le tampon_qte
		ecrire_tampon_qte_silos_agregat(1, agregat_1);
		ecrire_tampon_qte_silos_agregat(2, agregat_2);
		ecrire_tampon_qte_silos_agregat(3, agregat_3);
	
		printf("Quantité agregat 1: %f\n", agregat_1);
		printf("Quantité agregat 2: %f\n", agregat_2);
		printf("Quantité agregat 3: %f\n", agregat_3);
		
//----------------Signale la tache "gestion remplissage et versement silos" que le tampon_qte a été mis à jour
		semGive(sem_demande_versement_agregat);
	}
	
	return 0;
}
int calcul_qte_ciment(){
	float V, D, ciment_1, ciment_2;
	int B;
	
	while(1){
		semTake(sem_calcul_ciment, WAIT_FOREVER);
		
//----------------Lecture des valeurs B, V, D dans le tampon_cmd
		B = lire_tampon_cmd_cmd_plus_recent_beton();
		V = lire_tampon_cmd_cmd_plus_recent_volume();
		D = lire_tampon_cmd_cmd_plus_recent_distance();
		
		//printf("B : %d\n", B);
		//printf("V : %f\n", V);
		//printf("D : %f\n", D);
//----------------Calcul des quantités d'agrégats voulues selon la valeur de B
		switch(B){
			case 1:
				ciment_1 = beton_type_1.ciment_1/100.0*V;
				ciment_2 = beton_type_1.ciment_2/100.0*V;
				break;
			case 2:
				ciment_1 = beton_type_2.ciment_1/100.0*V;
				ciment_2 = beton_type_2.ciment_2/100.0*V;
				break;
			case 3:
				ciment_1 = beton_type_3.ciment_1/100.0*V;
				ciment_2 = beton_type_3.ciment_2/100.0*V;
				break;
			default:
				printf("calcul_qte_ciment : default case !\n");
				return PB;
		}
//----------------Ecriture des quantités dans le tampon_qte
		ecrire_tampon_qte_silos_ciment(1, ciment_1);
		ecrire_tampon_qte_silos_ciment(2, ciment_2);
	
		printf("Quantité ciment 1: %f\n", ciment_1);
		printf("Quantité ciment 2: %f\n", ciment_2);
			
//----------------Signale la tache "gestion remplissage et versement silos" que le tampon_qte a été mis à jour
		semGive(sem_demande_versement_ciment);
	}
	
	return 0;
}

int versement_agregat(){
	//Numéro du silo à ouvrir
	int num_silo_entier;
	char num_silo[15];
	
	while(1){
		//Attente de la demande de versement d'agregat
		semTake(sem_demande_versement_agregat, WAIT_FOREVER);
		
		for (num_silo_entier = 1; num_silo_entier <= 3; num_silo_entier += 1) {
			sprintf(num_silo, "%d", num_silo_entier);
			//Signal de début de versement à la balance
			msgQSend(file_debut_remplissage_balance_agregat, num_silo, sizeof(num_silo), WAIT_FOREVER, MSG_PRI_NORMAL);
			
			//Ouverture du silo num_silo
			switch (num_silo_entier){
			case 1:
				OuvrirVanne(cst_vanne_bas_agregat_1);
				break;
			case 2:
				OuvrirVanne(cst_vanne_bas_agregat_2);
				break;
			default:
				OuvrirVanne(cst_vanne_bas_agregat_3);
				break;
			}
			semTake(sem_fin_remplissage_balance_agregat, WAIT_FOREVER);
			
			//Fermeture du silo num_silo
			switch (num_silo_entier){
			case 1:
				FermerVanne(cst_vanne_bas_agregat_1);
				break;
			case 2:
				FermerVanne(cst_vanne_bas_agregat_2);
				break;
			default:
				FermerVanne(cst_vanne_bas_agregat_3);
				break;
			}
		}
		//Ici tous les silos d'agregat ont été versés
		semGive(sem_pret_balance_agregat);	//Signal balance agr prête pour synchro
		
		semTake(sem_ouverture_balance_agregat, WAIT_FOREVER);	//Attente de l'ordre d'ouverture
		DemarrageTapis(cst_tapis_agregat);
		OuvrirBalance(cst_balance_agregat);
	}
	return 0;
}
int remplissage_agregat_1(){
	//Initialisation du système, remplissage du silo
	OuvrirVanne(cst_vanne_haut_agregat_1);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_agr_1, WAIT_FOREVER);
	
	FermerVanne(cst_vanne_haut_agregat_1);
	
	semGive(sem_init_remplissage_silo_agr_1);
	while(1){
		semTake(sem_int_min_agr_1, WAIT_FOREVER);
		
		OuvrirVanne(cst_vanne_haut_agregat_1);
		
		semTake(sem_int_max_agr_1, WAIT_FOREVER);
		
		FermerVanne(cst_vanne_haut_agregat_1);
	}
	
	return 0;
}
int remplissage_agregat_2(){
	//Initialisation du système, remplissage du silo
	OuvrirVanne(cst_vanne_haut_agregat_2);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_agr_2, WAIT_FOREVER);
	
	FermerVanne(cst_vanne_haut_agregat_2);
	
	semGive(sem_init_remplissage_silo_agr_2);
	
	while(1){
		semTake(sem_int_min_agr_2, WAIT_FOREVER);
		
		OuvrirVanne(cst_vanne_haut_agregat_2);
		
		semTake(sem_int_max_agr_2, WAIT_FOREVER);
		
		FermerVanne(cst_vanne_haut_agregat_2);
	}
		
	return 0;
}
int remplissage_agregat_3(){
	//Initialisation du système, remplissage du silo
	OuvrirVanne(cst_vanne_haut_agregat_3);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_agr_3, WAIT_FOREVER);
	
	FermerVanne(cst_vanne_haut_agregat_3);
	
	semGive(sem_init_remplissage_silo_agr_3);
	
	while(1){
		semTake(sem_int_min_agr_3, WAIT_FOREVER);
		
		OuvrirVanne(cst_vanne_haut_agregat_3);
		
		semTake(sem_int_max_agr_3, WAIT_FOREVER);
		
		FermerVanne(cst_vanne_haut_agregat_3);
	}
		
	return 0;
}

int versement_ciment(){
	//Numéro du silo à ouvrir
	int num_silo_entier;
	char num_silo[15];
	
	while(1){
		//Attente de la demande de versement d'agregat
		semTake(sem_demande_versement_ciment, WAIT_FOREVER);
		
		for (num_silo_entier = 1; num_silo_entier <= 2; num_silo_entier += 1) {
			sprintf(num_silo, "%d", num_silo_entier);
			
			//Signal de début de versement à la balance
			msgQSend(file_debut_remplissage_balance_ciment, num_silo, sizeof(num_silo), WAIT_FOREVER, MSG_PRI_NORMAL);
			
			//Ouverture du silo num_silo
			switch (num_silo_entier){
			case 1:
				OuvrirVanne(cst_vanne_bas_ciment_1);
				break;
			default:
				OuvrirVanne(cst_vanne_bas_ciment_2);
				break;
			}
			
			semTake(sem_fin_remplissage_balance_ciment, WAIT_FOREVER);
			
			//Fermeture du silo num_silo
			switch (num_silo_entier){
			case 1:
				FermerVanne(cst_vanne_bas_ciment_1);
				break;
			default:
				FermerVanne(cst_vanne_bas_ciment_2);
				break;
			}
		}
		//Ici tous les silos d'agregat ont été versés
		semGive(sem_pret_balance_ciment);	//Signal balance agr prête pour synchro
		
		semTake(sem_ouverture_balance_ciment, WAIT_FOREVER);	//Attente de l'ordre d'ouverture
		DemarrageTapis(cst_tapis_ciment);
		OuvrirBalance(cst_balance_ciment);
	}
	return 0;
}
int remplissage_ciment_1(){
	//Initialisation du système, remplissage du silo
	OuvrirVanne(cst_vanne_haut_ciment_1);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_cim_1, WAIT_FOREVER);
	
	FermerVanne(cst_vanne_haut_ciment_1);
	
	semGive(sem_init_remplissage_silo_cim_1);
	
	while(1){
		semTake(sem_int_min_cim_1, WAIT_FOREVER);
		
		OuvrirVanne(cst_vanne_haut_ciment_1);
		
		semTake(sem_int_max_cim_1, WAIT_FOREVER);
		
		FermerVanne(cst_vanne_haut_ciment_1);
	}
		
	return 0;
}
int remplissage_ciment_2(){
	//Initialisation du système, remplissage du silo
	OuvrirVanne(cst_vanne_haut_ciment_2);
	
	//Attente de l'évènement silo plein
	semTake(sem_int_max_cim_2, WAIT_FOREVER);
	
	FermerVanne(cst_vanne_haut_ciment_2);
	
	semGive(sem_init_remplissage_silo_cim_2);
	
	while(1){
		semTake(sem_int_min_cim_2, WAIT_FOREVER);
		
		OuvrirVanne(cst_vanne_haut_ciment_2);
		
		semTake(sem_int_max_cim_2, WAIT_FOREVER);
		
		FermerVanne(cst_vanne_haut_ciment_2);
	}
		
	return 0;
}

int gestion_balance_agregats(){
	int num_silo = 0;		//Numéro du silo en cours de versement
	int versement = 1;

	while (1){
		msgQReceive(file_debut_remplissage_balance_agregat, (char*) num_silo, sizeof(num_silo), WAIT_FOREVER);
		versement = 1;
		
		while(versement == 1){
			semTake(sem_int_plus_bal_agr, WAIT_FOREVER);
			
			//Decremente
			decremente_tampon_qte_silos_agregat(num_silo);
			
			if (is_tampon_qte_silos_agregat_nulle(num_silo)){
				versement = 0;
				semGive(sem_fin_remplissage_balance_agregat);
			}
		}
	}
	return 0;
}
int gestion_balance_ciment(){
	int num_silo = 0;		//Numéro du silo en cours de versement
	int versement = 1;

	while (1){
		msgQReceive(file_debut_remplissage_balance_ciment, (char*) num_silo, sizeof(num_silo), WAIT_FOREVER);
		versement = 1;
		
		while(versement == 1){
			semTake(sem_int_plus_bal_cim, WAIT_FOREVER);
			
			//Decremente
			decremente_tampon_qte_silos_ciment(num_silo);
			
			if (is_tampon_qte_silos_ciment_nulle(num_silo)){
				versement = 0;
				semGive(sem_fin_remplissage_balance_ciment);
			}
		}
	}
	return 0;
}
int gestion_synchro(){
	int cmd_agr_en_cours, cmd_cim_en_cours, cmd_en_cours;
	
	while (1){
		//Synchro ouverture des balances
		semTake(sem_pret_balance_agregat, WAIT_FOREVER);
		semTake(sem_pret_balance_ciment, WAIT_FOREVER);
		
		cmd_agr_en_cours = lire_tampon_fonct_calcul_cmd_agregat();
		cmd_cim_en_cours = lire_tampon_fonct_calcul_cmd_ciment();
		cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
		
		//Ici, les balances sont prètes
		if (!(cmd_agr_en_cours == cmd_cim_en_cours
				&& cmd_agr_en_cours == cmd_en_cours)) {
			//Le contenu des balances ne correspond pas à la cmd en cours
			//Attente de la fin de la cmd actuelle
			semTake(sem_agregat_et_ciment_suivant, WAIT_FOREVER);
		}

		//Ici, le contenu des balances correspond à la cmd en cours
		//Démarrage du versement des balances
		semGive(sem_ouverture_balance_agregat);
		semGive(sem_ouverture_balance_ciment);
		
		//Attente de la fin du versement
		semTake(sem_fin_vers_balance_agregat, WAIT_FOREVER);
		semTake(sem_fin_vers_balance_ciment, WAIT_FOREVER);
		
		//Lancement de l'eau
		semGive(sem_demande_versement_eau);
		//Lancement du malaxeur
		semGive(sem_debut_moteur);
	}
	
	return 0;
}

int versement_eau(){
	int versement = 0;
	versement_eau_en_cours = 0;
	
	while(1){
		// Attend une demande de versement
		semTake(sem_demande_versement_eau, WAIT_FOREVER);
		versement = 1;
		versement_eau_en_cours = 1;
		
		// Lance le calcul de la quantité d'eau
		semGive(sem_calcul_eau);
		
		// Début versement dès que c'est possible, attente si impossible
		while(!is_versement_eau_possible());
		OuvrirRobinet(cst_vanne_bas_eau, 100);
		
		while(versement == 1){
			semTake(sem_int_moins_eau, WAIT_FOREVER);
						
			//Decremente
			decremente_tampon_qte_silos_eau();
			
			if (is_tampon_qte_silos_eau_nulle()){
				versement = 0;
				semGive(sem_fin_eau);
			}
		}
	}
	
	return 0;
}
int remplissage_eau(){
	// Initialisation du système, remplissage du silo
	//Rupture versement
	OuvrirRobinet(cst_vanne_bas_eau, 0);
	set_versement_eau_possible(0);
	
	OuvrirVanne(cst_vanne_haut_eau);
	
	// Attente de l'évènement silo plein
	semTake(sem_int_max_eau, WAIT_FOREVER);
	
	FermerVanne(cst_vanne_haut_eau);
	//Autorise le versement
	set_versement_eau_possible(1);
	
	semGive(sem_init_remplissage_silo_eau);
	
	while(1){
		semTake(sem_int_min_eau, WAIT_FOREVER);		// silo eau vide
		
		//*************Rupture versement
		set_versement_eau_possible(0);
		OuvrirRobinet(cst_vanne_bas_eau, 0);
		
		//*************Début du remplissage
		OuvrirVanne(cst_vanne_haut_eau);
		
		// Attente de l'évènement silo plein
		semTake(sem_int_max_eau, WAIT_FOREVER);
		
		//*************Fin du remplissage
		FermerVanne(cst_vanne_haut_eau);
		
		//*************Reprise du versement
		set_versement_eau_possible(1);
		if (versement_eau_en_cours == 1) {
			OuvrirRobinet(cst_vanne_bas_eau, 100);
		}
	}
	
	return 0;
}

int gestion_position_camion(){
	int timer_camion_present;
	int position_camion_ok;
	timer_getPresence = 0;
	
	while(1){
		semTake(sem_debut_camion, WAIT_FOREVER);
		AllumerDiodePositionCamion();
		position_camion_ok = 0;
		
		while(position_camion_ok == 0){
			while(getPresence() == 0){
				//printf("\n******** Camion non positionné ! ********\n");
			}
			EteindreDiodePositionCamion();
			timer_camion_present = 0;
			
			while((timer_camion_present < 5) && (getPresence() == 1)){
				taskDelay(100);
				timer_camion_present = timer_camion_present +1;
				//printf("\n *** CAMION EN POSITION *** \n");
				//printf("timer_camion_present : %d\n", timer_camion_present);
				//printf("\n ************************** \n");
			}
			
			if(timer_camion_present == 5){
				position_camion_ok = 1;
				semGive(sem_position_camion_ok);
				//printf("\n*************** FIN TEST GESTION POSITION CAMION ***************\n");
			}
		}
	}
	
	return 0;
}
int gestion_versement(){
	int timer_versement;
	
	while(1){
		timer_versement = 0;
		semTake(sem_position_camion_ok, WAIT_FOREVER);
		semGive(sem_van_ouvre_malaxeur);
		
		while(timer_versement < cste_temps_versement){
			sleep(1);
			timer_versement += 1;
		}
		semGive(sem_arret_rotation_moteur);
		semTake(sem_vide_malaxeur, WAIT_FOREVER);
		semGive(sem_van_ferme_malaxeur);
		semGive(sem_fin_malaxeur);
	}
	
	return 0;
}
int gestion_moteur(){
	int Imax_atteint,vitesse,temps_sans_fluctuation;
	char buffer_file_intensite[10];
	char buffer_file_vitesse[10];
	float intensite, intensite_avant;
	while(1){
		semTake(sem_debut_malaxeur, WAIT_FOREVER);
		printf("prise du jeton du semaphore sem_debut_malaxeur \n");
		consigne_moteur(cste_vitesse_moteur_max);
		Imax_atteint = 0;
		temps_sans_fluctuation = 0;
		intensite_avant = 0;
		if(getVmot() == 0){
			sleep(5);
		}
		while(temps_sans_fluctuation < cste_temps_cst && getVmot() > 0){
			vitesse = getVmot();
			intensite  = getImot();
			sprintf(buffer_file_intensite, "%f", intensite);
			msgQSend(file_intensite, buffer_file_intensite, 10, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			if(intensite < cste_Imax){
				//printf("intensite_avant : %f\n", intensite_avant);
				if(abs(intensite - intensite_avant) < 0.05*intensite_avant){
					taskDelay(100);
					temps_sans_fluctuation += 1;
				}else{
					temps_sans_fluctuation = 0;
				}
				//printf("\n*** ATTENTE D'HOMOGENEISATION DU MELANGE ***\n");
				//printf("temps_sans_fluctuation : %d \n",temps_sans_fluctuation);
				//printf("cste_temps_cst : %d",cste_temps_cst);
				//printf("\n********************************************\n");
				intensite_avant = intensite;
				if(Imax_atteint){
					EteindreDiodeMalaxeur();
					semGive(sem_reprise_bal_tapis_agrEtCim);
					Imax_atteint = 0;
				}
			}else{
				if(!Imax_atteint){
					consigne_moteur(0);
					Imax_atteint = 1;
					semGive(sem_stop_bal_tapis_agrEtCim);
					AllumerDiodeMalaxeur();
				}
			}
		}
		
		if(temps_sans_fluctuation == cste_temps_cst){
			//printf("temps_sans_fluctuation (fin) : %d \n",temps_sans_fluctuation);
			//printf("\n*************** FIN TEST GESTION_MOTEUR ***************\n");
			semGive(sem_debut_camion);
			taskDelete(taskIdSelf());
		}
	}
	
	return 0;
}



void capteur_plein_silo_agregat_1(){
	semGive(sem_int_max_agr_1);
}
void capteur_vide_silo_agregat_1(){
	semGive(sem_int_min_agr_1);
}
void capteur_plein_silo_agregat_2(){
	semGive(sem_int_max_agr_2);
}
void capteur_vide_silo_agregat_2(){
	semGive(sem_int_min_agr_2);
}
void capteur_plein_silo_agregat_3(){
	semGive(sem_int_max_agr_3);
}
void capteur_vide_silo_agregat_3(){
	semGive(sem_int_min_agr_3);
}
void capteur_plein_silo_ciment_1(){
	semGive(sem_int_max_cim_1);
}
void capteur_vide_silo_ciment_1(){
	semGive(sem_int_min_cim_1);
}
void capteur_plein_silo_ciment_2(){
	semGive(sem_int_max_cim_2);
}
void capteur_vide_silo_ciment_2(){
	semGive(sem_int_min_cim_2);
}
void capteur_plus_balance_agregats(){
	qte_contenu_balance_agregat += 1;
	
	semGive(sem_int_plus_bal_agr);
}
void capteur_moins_balance_agregats(){
	qte_contenu_balance_agregat -= 1;
	
	//semGive(sem_int_moins_bal_agr);
	if (qte_contenu_balance_agregat <= 0){
		qte_contenu_balance_agregat = 0;
		semGive(sem_fin_vers_balance_agregat);
	}
}
void capteur_plus_balance_ciment(){
	qte_contenu_balance_ciment += 1;
		
	semGive(sem_int_plus_bal_cim);
}
void capteur_moins_balance_ciment(){
	qte_contenu_balance_ciment -= 1;
		
	//semGive(sem_int_moins_bal_cim);
	if (qte_contenu_balance_ciment <= 0){
		qte_contenu_balance_ciment = 0;
		semGive(sem_fin_vers_balance_ciment);
	}
}
void capteur_plein_eau(){
	semGive(sem_int_max_eau);
}

void capteur_vide_eau(){
	semGive(sem_int_min_eau);
}

void capteur_plus_eau(){
	//semGive(sem_int_plus_eau);
}

void capteur_moins_eau(){
	semGive(sem_int_moins_eau);
}

