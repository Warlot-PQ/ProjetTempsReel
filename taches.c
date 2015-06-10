#include "cimenterie.h"
#include "accesTampons.h"
#include "taches.h"
#include "signauxExterieur.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/****************************************************************************
 * 								tache.c										*
 * L'ensemble des tâches lancées par le système sont regroupées ici.		*
 * Auteurs : Piere-Quentin WARLOT, Jean-Michel NOKAYA						*																			*
 * ***************************************************************************/

/**
 * gestion_IHM() :	Récupère les informations entrées par l'utilisateur et les
 * stocke dans le tampon tampon_cmd.
 * @return 0
 */

int gestion_IHM(){
	float valeur_volume;
	int valeur_beton, premier_essai = 1;
	float valeur_distance;
	
//	**************	Initialisation de la cimenterie : remplissage des silos 1 à 1  **************** //
	printf("Initialisation de la cimenterie, remplissage des silos\n");
	semTake(sem_init_remplissage_silo_agr_1, WAIT_FOREVER);
	semTake(sem_init_remplissage_silo_agr_2, WAIT_FOREVER);
	semTake(sem_init_remplissage_silo_agr_3, WAIT_FOREVER);
	semTake(sem_init_remplissage_silo_cim_1, WAIT_FOREVER);
	semTake(sem_init_remplissage_silo_cim_2, WAIT_FOREVER);
	semTake(sem_init_remplissage_silo_eau, WAIT_FOREVER);
	
//	**************	lancement de la tâche  **************** //
	while(1){
		//	**************	récupération de données via des scanf (contrôle des données assurées) **************** //
		do{
			if (premier_essai == 0) {
				ajouter_message_affichage("Valeurs entrées incorrect.\n");
				ajouter_message_affichage("Vous pouvez répéter la question ?\n");
			}
			
			ajouter_message_affichage("Entrez le volume de béton souhaité :\n");
			scanf("%f", &valeur_volume);
			ajouter_message_affichage("Entrez le type de béton souhaité (1,2,3) :\n");
			scanf("%d", &valeur_beton);
			ajouter_message_affichage("Entrez la distance à parcourir :\n");
			scanf("%f", &valeur_distance);
			premier_essai = 0;
			vider_messages_affichage();
		} while (!(valeur_volume > 0 
				&& (valeur_beton == 1 || valeur_beton == 2 || valeur_beton == 3) 
				&& valeur_distance > 0));
		
		premier_essai = 1;
		
		if (tampon_fonct_calcul_plein() == PB){
			printf("Nombre maximum de commande en cours de traitement atteint !\n");
		
		//	**************	Si Ok (tampon non plein) :   **************** //
		} else {
			
			//	**************	incrémentation de cmd_plus_récente dans tampon_fonct_calcul  **************** //
			incremente_tampon_fonct_calcul_cmd_plus_recente();
			
			//	**************	insertion des données entrées dans tampon_cmd  **************** //
			ecrire_tampon_cmd_cmd_plus_recent_volume(valeur_volume);
			ecrire_tampon_cmd_cmd_plus_recent_beton(valeur_beton);
			ecrire_tampon_cmd_cmd_plus_recent_distance(valeur_distance);
			
			//	**************	Si première commande, on lance les tâches de calcul de quantité  **************** //
			if (is_tampon_fonct_calcul_premiere_cmd() != PB){
				//Fixe la commande en cours comme étant la première
				set_tampon_fonct_calcul_premiere_cmd();
				
				printf("Démarrage de la commande V %f, B %d, D %f", valeur_volume, valeur_beton, valeur_distance);
				
				semGive(sem_calcul_agregat);
				semGive(sem_calcul_ciment);
				semGive(sem_calcul_eau);
			} else {
				printf("ERREUR %d\n", is_tampon_fonct_calcul_premiere_cmd());
			}
		}
	}
	return 0;
}

/*
 *	 gestion_evenement_malax() :Tâche gérant les événements suivants la fin de traitement d'une commande
 * donnée par le malaxeur.
 * @return 0									
 */
int gestion_evenement_malax(){
	int cmd_plus_recente, cmd_en_cours, index_boucle;
	
	while(1){
		
		//	**************	Attente de la fin de versement du mélange dans le malaxeur  **************** //
		semTake(sem_fin_malaxeur, WAIT_FOREVER);
		
		/* Il s'agit d'une fin de traitement d'une commande : lecture des
		 * variables cmd_plus_recente et cmd_en_cours dans tampon_fonct_calcul 
		 */
		cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();
		cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
		
		/* Si elles sont différentes : il reste des commandes à traiter,
		 * effacement des données de traitement de la commandes en cours, MAJ de cmd_en_cours pour passer au
		 * traitement de la commande suivante
		 */
		if(cmd_plus_recente != cmd_en_cours){
			efface_commande_traitee();
			incremente_tampon_fonct_calcul_cmd_en_cours();
			semGive(sem_calcul_eau);
			
		/*Sinon, cela veut dire qu'il n'y a plus de commande à traiter :
		 * on re initialise le système
		 */
		} else {
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

/*
 * gestion_evenement_agregat() : tâche gérant les les événements suivants la fin du versement des agrégats
 * dans la balance pour une commande donnée.
 * @return 0
 */
int gestion_evenement_agregat(){
	int cmd_plus_recente, cmd_en_cours;
	
	while(1){
		
		//	**************	Attente de la fin du versement des agrégats dans la balance  **************** //
		semTake(sem_fin_agregat, WAIT_FOREVER);
		
		//  ******* Lecture des variables cmd_plus_recente et cmd_en_cours dans tampon_fonct_calcul *******/
		cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();
		cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
		
		/*	Si elles sont différentes : il reste des commandes à traiter,
		 * on incrémente la valeur de cmd_agregat_en_cours dans tampon_fonct_calcul et on signale que l'on peut 
		 * lancer les calculs de quantités pour les agrégats de la commande suivante.
		 */
		if(cmd_plus_recente != cmd_en_cours){
			incremente_tampon_fonct_calcul_cmd_agregat();
			semGive(sem_calcul_agregat);
		}
		
		//	**************	Sinon, plus de commande à traiter, la tâche ne fait rien  **************** //
	}
	
	return 0;
}

/*
 * gestion_evenement_ciment() : tâche gérant la fin de versement des ciments dans la balance.
 * Fonctionnement identique à gestion_evenement_agregat().
 * @return 0
 */
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

/*
 * gestion_evenement_eau() :tâche gérant la fin du versement de l'eau.
 * Attente du signal de fin de versement de l'eau dans le malaxeur, et incrémente cmd_eau_en_cours dans 
 * tampon_fonct_calcul
 * @return 0
 */
int gestion_evenement_eau(){
	while(1){
		semTake(sem_fin_eau, WAIT_FOREVER);
		
		incremente_tampon_fonct_calcul_cmd_eau();
	}
	return 0;
}

/*
 * calcul_qte_eau() : 	tâche gérant le calcul de la quantité d'eau à verser dans le malaxeur pour une 
 * commande donnée.
 * @return 0
 */
int calcul_qte_eau(){
	float V, D, qte_eau;
	int i, B, hygrometrie;
	
	while(1){
		
		//	**************	Attente du signal de lancement des calculs  **************** //
		semTake(sem_calcul_eau, WAIT_FOREVER);
		
		//	**************	récupération de l'hygrométrie  **************** //
		hygrometrie = getHygrometrie();
		//printf("hygronometrie : %d\n", hygrometrie);
		//printf("cmd en cours : %d\n\n", lire_tampon_fonct_calcul_cmd_en_cours());
		//printf("type de béton : %d\n\n", lire_tampon_cmd_cmd_plus_recent_beton());
		
		//	**************	lecture des valeurs B, V, D de la commande en cours  **************** //
		B = lire_tampon_cmd_cmd_eau_en_cours_beton();
		V = lire_tampon_cmd_cmd_eau_en_cours_volume();
		D = lire_tampon_cmd_cmd_eau_en_cours_distance();
		
		//	**************	calcul de la quantité d'eau à verser selon le type de béton (B)  **************** //
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
		//	**************	écriture de cette faleur dans tampon_qte_silo **************** //
		ecrire_tampon_qte_silos_eau(qte_eau);

		//printf("Quantité eau: %f\n", qte_eau);
		
		//	**************	Signale au gestionnaire de synchronisation que le tampon_qte_silo a été mis à jour pour l'eau.  **************** //
		semGive(sem_cmd_en_cours);
	}
	return 0;
}

/*
 * calcul_qte_agregat() : 	tâche gérant le calcul de la quantité d'argegats à verser dans le malaxeur pour une 
 * commande donnée.
 * @return 0
 */
int calcul_qte_agregat(){
	float V, D, agregat_1, agregat_2, agregat_3;
	int B;
	
	while(1){
		//	**************  Attente du signal de lancement des calculs  **************** //
		semTake(sem_calcul_agregat, WAIT_FOREVER);

		//	**************	lecture des valeurs B, V, D de la commande en cours  **************** //
		B = lire_tampon_cmd_cmd_agregat_en_cours_beton();
		V = lire_tampon_cmd_cmd_agregat_en_cours_volume();
		D = lire_tampon_cmd_cmd_agregat_en_cours_distance();

		//	**************	calcul de la quantité d'agrégat à verser selon le type de béton (B)  **************** //
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
		
		//	**************	écriture de cette faleur dans tampon_qte_silo  **************** //
		ecrire_tampon_qte_silos_agregat(1, agregat_1);
		ecrire_tampon_qte_silos_agregat(2, agregat_2);
		ecrire_tampon_qte_silos_agregat(3, agregat_3);
		
		//	**************	Signale au gestionnaire de versement des agrégats que le tampon_qte_silo a été mis à jour pour les agrégats.  **************** //
		semGive(sem_demande_versement_agregat);
	}
	
	return 0;
}

/*
 * calcul_qte_ciment() : 	tâche gérant le calcul de la quantité de ciment à verser dans le malaxeur pour une 
 * commande donnée.
 * Fonctionnement similaire à calcul_qte_agregat
 * @return 0
 */
int calcul_qte_ciment(){
	float V, D, ciment_1, ciment_2;
	int B;
	
	while(1){
		
		//	**************  Attente du signal de lancement des calculs  **************** //
		semTake(sem_calcul_ciment, WAIT_FOREVER);
	
		//	**************	lecture des valeurs B, V, D de la commande en cours  **************** //
		B = lire_tampon_cmd_cmd_ciment_en_cours_beton();
		V = lire_tampon_cmd_cmd_ciment_en_cours_volume();
		D = lire_tampon_cmd_cmd_ciment_en_cours_distance();

		//printf("B : %d\n", B);
		//printf("V : %f\n", V);
		//printf("D : %f\n", D);
		
		//	**************	calcul de la quantité de ciment à verser selon le type de béton (B)  **************** //
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

		//	**************	écriture de cette faleur dans tampon_qte_silo  **************** //
		ecrire_tampon_qte_silos_ciment(1, ciment_1);
		ecrire_tampon_qte_silos_ciment(2, ciment_2);
	
		//printf("Quantité ciment 1: %f\n", ciment_1);
		//printf("Quantité ciment 2: %f\n", ciment_2);
			
		//	**************	Signale au gestionnaire de versement des ciments que le tampon_qte_silo a été mis à jour pour les ciments.  **************** //
		semGive(sem_demande_versement_ciment);
	}
	
	return 0;
}

/*
 * versement_agrégat() : tâche gérant le versement du contenu des silos des agrégats dans la balance.
 * @return 0
 */
int versement_agregat(){
	//Numéro du silo à ouvrir
	int num_silo_entier;
	char num_silo[256];
	
	while(1){
		//	**************	Attente du signal de début de versement (depuis le calcul_qte_agregat)  **************** //
		semTake(sem_demande_versement_agregat, WAIT_FOREVER);
		
		//	**************	On verse les silos 1 à 1  **************** //
		for (num_silo_entier = 1; num_silo_entier <= 3; num_silo_entier += 1) {
			
			sprintf(num_silo, "%d", num_silo_entier);

			//	**************	Signal de début de versement à la balance **************** //
			msgQSend(file_debut_remplissage_balance_agregat, num_silo, sizeof num_silo, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			printf("Debut versement silo agregat %d.\n", num_silo_entier);
			
			//	**************	Ouverture du silo num_silo **************** //
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
			
			printf("Fin versement silo agregat %d.\n", num_silo_entier);
						
			//	**************	Fermeture du silo num_silo  **************** //
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
		/* Ici tous les silos d'agregat ont été versés
		 * Signal balance agr prête pour synchro
		 */
		semGive(sem_pret_balance_agregat);

		//	**************	Attente de l'ordre d'ouverture et de démarrage des tapis **************** //
		semTake(sem_ouverture_balance_agregat, WAIT_FOREVER);	
		DemarrageTapis(cst_tapis_agregat);
		OuvrirBalance(cst_balance_agregat);
	}
	return 0;
}

/*
 * remplissage_agregat_1() : tâche gérant le remplissage du silo d'agrégat 1 quant le silo est vide
 * @return 0
 */
int remplissage_agregat_1(){
	
	//	**************	Initialisation du système, remplissage du silo **************** //
	OuvrirVanne(cst_vanne_haut_agregat_1);
	
	//	**************	Attente de l'évènement silo plein **************** //
	semTake(sem_int_max_agr_1, WAIT_FOREVER);
	
	FermerVanne(cst_vanne_haut_agregat_1);
	
	semGive(sem_init_remplissage_silo_agr_1);
	
	//	**************	Core de la tâche **************** //
	while(1){
		//	**************	Attente de l'événement de silo vide **************** //
		semTake(sem_int_min_agr_1, WAIT_FOREVER);
		
		OuvrirVanne(cst_vanne_haut_agregat_1);
		
		//	**************	Attente de l'évènement silo plein **************** //
		semTake(sem_int_max_agr_1, WAIT_FOREVER);
		
		FermerVanne(cst_vanne_haut_agregat_1);
	}
	
	return 0;
}

/*
 * remplissage_agregat_2() : tâche gérant le remplissage du silo d'agrégat 2 quant le silo est vide
 * fonctionnement identique à remplissage_agregat_1()
 * @return 0
 */
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

/*
 * remplissage_agregat_3() : tâche gérant le remplissage du silo d'agrégat 3 quant le silo est vide
 * fonctionnement identique à remplissage_agregat_1()
 * @return 0
 */
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

/*
 * versement_ciment() : tâche gérant le versement des ciments dans la balance.
 * @return 0
 */
int versement_ciment(){
	
	//	**************	Numéro du silo à ouvrir **************** //
	int num_silo_entier;
	char num_silo[256];
	
	while(1){
		
		//	**************	Attente de la demande de versement des ciments **************** //
		Numéro du silo à ouvrir
		semTake(sem_demande_versement_ciment, WAIT_FOREVER);
		
		for (num_silo_entier = 1; num_silo_entier <= 2; num_silo_entier += 1) {
			sprintf(num_silo, "%d", num_silo_entier);
			
			//	**************	Signal de début de versement à la balance **************** //
			msgQSend(file_debut_remplissage_balance_ciment, num_silo, sizeof num_silo, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			//	**************	Ouverture du silo num_silo **************** //
			switch (num_silo_entier){
			case 1:
				OuvrirVanne(cst_vanne_bas_ciment_1);
				break;
			default:
				OuvrirVanne(cst_vanne_bas_ciment_2);
				break;
			}
			
			semTake(sem_fin_remplissage_balance_ciment, WAIT_FOREVER);
			
			//	**************	Fermeture du silo num_silo **************** //
			switch (num_silo_entier){
			case 1:
				FermerVanne(cst_vanne_bas_ciment_1);
				break;
			default:
				FermerVanne(cst_vanne_bas_ciment_2);
				break;
			}
		}

		/* Si tous les silos d'agregat ont été versés
		 * Signal balance agr prête pour synchro
		 */
		semGive(sem_pret_balance_ciment);	
		
		//	**************	Attente de l'ordre d'ouverture  **************** //
		semTake(sem_ouverture_balance_ciment, WAIT_FOREVER);
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
	int num_silo_entier = 0;		//Numéro du silo en cours de versement
	char num_silo[256];
	int versement = 1;

	while (1){
		msgQReceive(file_debut_remplissage_balance_agregat, num_silo, sizeof num_silo, WAIT_FOREVER);
		num_silo_entier = atoi(num_silo);
		versement = 1;

		while(versement == 1){
			semTake(sem_int_plus_bal_agr, WAIT_FOREVER);

			printf("Quantité restante : %f\n", lire_tampon_qte_silos_agregat(num_silo_entier));
			
			//Decremente
			decremente_tampon_qte_silos_agregat(num_silo_entier);

			if (is_tampon_qte_silos_agregat_nulle(num_silo_entier)){
				versement = 0;
				semGive(sem_fin_remplissage_balance_agregat);
			}
		}
		if (num_silo_entier == 3){
			semTake(sem_ferm_balance_agregat, WAIT_FOREVER);
			FermerBalance(cst_balance_agregat);
			
			semGive(sem_fin_agregat);
		}
	}
	return 0;
}
int gestion_balance_ciment(){
	int num_silo_entier = 0;		//Numéro du silo en cours de versement
	char num_silo[256];
	int versement = 1;

	while (1){
		msgQReceive(file_debut_remplissage_balance_ciment, num_silo, sizeof num_silo, WAIT_FOREVER);
		num_silo_entier = atoi(num_silo);
		versement = 1;
		
		while(versement == 1){
			semTake(sem_int_plus_bal_cim, WAIT_FOREVER);
			
			//Decremente
			decremente_tampon_qte_silos_ciment(num_silo_entier);
			
			if (is_tampon_qte_silos_ciment_nulle(num_silo_entier)){
				versement = 0;
				
				semGive(sem_fin_remplissage_balance_ciment);
			}
		}
		if (num_silo_entier == 2){
			semTake(sem_ferm_balance_ciment, WAIT_FOREVER);
			FermerBalance(cst_balance_ciment);
			
			semGive(sem_fin_ciment);
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
		
		semTake(sem_cmd_en_cours, WAIT_FOREVER);

		printf("Ouverture des balances, debut versement !\n");
		
		//Ici, le contenu des balances correspond à la cmd en cours
		//Démarrage du versement des balances
		semGive(sem_ouverture_balance_agregat);
		semGive(sem_ouverture_balance_ciment);
		
		//Attente de la fin du versement
		semTake(sem_fin_vers_balance_agregat, WAIT_FOREVER);
		semTake(sem_fin_vers_balance_ciment, WAIT_FOREVER);

		printf("Fermeture des balances, fin versement !\n");

		//Lancement du malaxeur
		semGive(sem_debut_malaxeur);
		
		//Attente du delai Teau entre la fin du versement agregat/ciment + l'obtention d'un mélange homogène et celle du debut de l'eau
		taskDelay(sysClkRateGet() * cste_temps_eau);
		
		semTake(sem_melange_homogene, WAIT_FOREVER);
		
		//Lancement de l'eau
		semGive(sem_demande_versement_eau);
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
		
		// Début versement dès que c'est possible, attente si impossible
		while(!is_versement_eau_possible());
		OuvrirRobinet(cst_vanne_bas_eau, 100);
		
		while(versement == 1){
			semTake(sem_int_moins_eau, WAIT_FOREVER);
			
			printf("quantité eau restante : %f\n", lire_tampon_qte_silos_eau());
			//Decremente
			decremente_tampon_qte_silos_eau();
			
			if (is_tampon_qte_silos_eau_nulle()){
				versement = 0;
				OuvrirRobinet(cst_vanne_bas_eau, 0);
				semGive(sem_fin_versement_eau);
				semGive(sem_fin_eau);
				semTake(sem_attente_fin_eau, WAIT_FOREVER);
				attente_fin_eau = 1;
				semGive(sem_attente_fin_eau);
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
				printf("\n******** Camion non positionné ! ********\n");
			}
			EteindreDiodePositionCamion();
			timer_camion_present = 0;
			
			while((timer_camion_present < 5) && (getPresence() == 1)){
				taskDelay(100);
				timer_camion_present = timer_camion_present +1;
				printf("\n *** CAMION EN POSITION *** \n");
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
	//printf("\n*************** TEST GESTION_VERSEMENT MALAXEUR ***************\n");
	while(1){
		semTake(sem_position_camion_ok, WAIT_FOREVER);
		semTake(sem_fin_versement_eau, WAIT_FOREVER);
		
		OuvrirVanne(cst_vanne_malaxeur);
		semTake(sem_vide_malaxeur, WAIT_FOREVER);
		FermerVanne(cst_vanne_malaxeur);
		//printf("\n*************** FIN TEST GESTION_VERSEMENT MALAXEUR ***************\n");
		printf("FINIIIIIIIII\n");
		semGive(sem_fin_malaxeur);
	}
	
	return 0;
}
int gestion_moteur(){
	int Imax_atteint,vitesse,temps_sans_fluctuation, temps_malaxage_apres_fin_eau;
	char buffer_file_intensite[10];
	char buffer_file_vitesse[10];
	float intensite, intensite_avant;
	semTake(sem_attente_fin_eau, WAIT_FOREVER);
	attente_fin_eau = 0;
	semGive(sem_attente_fin_eau);
	//semGive(sem_stupide);
	while(1){
		
		semTake(sem_debut_malaxeur, WAIT_FOREVER);
		
		consigne_moteur(cste_vitesse_moteur_max);
		
		Imax_atteint = 0;
		temps_sans_fluctuation = 0;semTake(sem_attente_fin_eau, WAIT_FOREVER);
		attente_fin_eau = 0;
		semGive(sem_attente_fin_eau);
		temps_malaxage_apres_fin_eau = 0;
		intensite_avant = 0;
		
		taskDelay(sysClkRateGet() * 2);
		
		while(temps_sans_fluctuation < cste_temps_cst){
			vitesse = getVmot();
			intensite  = getImot();
			
			//printf("Vitesse moteur : %d\n", vitesse);
			
			sprintf(buffer_file_intensite, "%f", intensite);
			//msgQSend(file_intensite, buffer_file_intensite, 10, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			if(intensite < 0.8*cste_Imax){
				//printf("intensite_avant : %f\n", intensite_avant);
				if(abs(intensite - intensite_avant) < 0.05*intensite_avant){
					taskDelay(sysClkRateGet() * 1);
					temps_sans_fluctuation += 1;
				}else{
					temps_sans_fluctuation = 0;
				}
				printf("\n*** ATTENTE D'HOMOGENEISATION DU MELANGE ***\n");
				//printf("temps_sans_fluctuation : %d \n",temps_sans_fluctuation);
				//printf("cste_temps_cst : %d",cste_temps_cst);
				//printf("\n********************************************\n");
				intensite_avant = intensite;
				if(Imax_atteint){
					EteindreDiodeMalaxeur();
					printf("\n*** Reprise versement ***\n");
					semGive(sem_reprise_bal_tapis_agrEtCim);
					Imax_atteint = 0;
				}
			}else{
				if(!Imax_atteint){
					consigne_moteur(0);
					Imax_atteint = 1;
					printf("\n*** Stop versement ***\n");
					semGive(sem_stop_bal_tapis_agrEtCim);
					AllumerDiodeMalaxeur();
				}
			}
		}
		
		printf("\n***MELANGE HOMOGENE ***\n");
		
		//printf("temps_sans_fluctuation (fin) : %d \n",temps_sans_fluctuation);
		//printf("\n*************** FIN TEST GESTION_MOTEUR ***************\n");
		semGive(sem_melange_homogene);
		
		while(temps_malaxage_apres_fin_eau < cste_temps_malaxeur && !Imax_atteint){
			vitesse = getVmot();
			intensite  = getImot();
			
			//printf("Vitesse moteur : %d\n", vitesse);
			
			sprintf(buffer_file_intensite, "%f", intensite);
			//msgQSend(file_intensite, buffer_file_intensite, 10, WAIT_FOREVER, MSG_PRI_NORMAL);
			
			if(intensite < 0.8*cste_Imax){
				//printf("intensite_avant : %f\n", intensite_avant);
				if(abs(intensite - intensite_avant) < 0.05*intensite_avant){
					taskDelay(sysClkRateGet() * 1);
					temps_sans_fluctuation += 1;
				}else{
					temps_sans_fluctuation = 0;
				}
				semTake(sem_attente_fin_eau, WAIT_FOREVER);
				if(attente_fin_eau == 1){
					printf("\n*** TEMPS DE MALAXAGE APRES HOMOGENEISATION ET AVANT VERSEMENT DANS LE CAMION ***\n");
					printf("temps_malaxage_apres_fin_eau : %d \n", temps_malaxage_apres_fin_eau);
					temps_malaxage_apres_fin_eau += 1;
				//printf("cste_temps_cst : %d",cste_temps_cst);
				//printf("\n********************************************\n");
				}else{
					printf("\n*** ATTENTE FIN EAU ***\n");
					temps_malaxage_apres_fin_eau = 0;
				}
				semGive(sem_attente_fin_eau);
				intensite_avant = intensite;
				if(Imax_atteint){
					EteindreDiodeMalaxeur();
					printf("\n*** Reprise versement ***\n");
					semGive(sem_reprise_bal_tapis_agrEtCim);
					Imax_atteint = 0;
				}
			}else{
				if(!Imax_atteint){
					consigne_moteur(0);
					Imax_atteint = 1;
					printf("\n*** Stop versement ***\n");
					semGive(sem_stop_bal_tapis_agrEtCim);
					AllumerDiodeMalaxeur();
				}
			}
		}
		
		//SI on arrive ici, cela veut dire que soit : le temps de malaxage après la fin du versement de l'eau s'est écoulé, soit l'intensité a dépassé le seuil.
		if(temps_malaxage_apres_fin_eau == cste_temps_malaxeur){
			printf("\n*** FIN DE LA TACHE MOTEUR ET DEBUT DE CONTROLE DE POSITIONNEMENT ***\n");
			consigne_moteur(0);
			semTake(sem_attente_fin_eau, WAIT_FOREVER);
			attente_fin_eau = 0;
			semGive(sem_attente_fin_eau);
			semGive(sem_debut_camion);
		}else{
			semGive(sem_debut_malaxeur);
		}
	}
	
	return 0;
}


void capteur_vide_malaxeur(){
	semGive(sem_vide_malaxeur);
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
	qte_contenu_balance_agregat += UNITE_VOLUME_VERSEMENT;
	
	semGive(sem_int_plus_bal_agr);
}
void capteur_moins_balance_agregats(){
	qte_contenu_balance_agregat -= UNITE_VOLUME_VERSEMENT;

	//semGive(sem_int_moins_bal_agr);
	if (qte_contenu_balance_agregat <= 0){
		qte_contenu_balance_agregat = 0;
		
		semGive(sem_ferm_balance_agregat);
		semGive(sem_fin_vers_balance_agregat);
	}
}
void capteur_plus_balance_ciment(){
	qte_contenu_balance_ciment += UNITE_VOLUME_VERSEMENT;
		
	semGive(sem_int_plus_bal_cim);
}
void capteur_moins_balance_ciment(){
	qte_contenu_balance_ciment -= UNITE_VOLUME_VERSEMENT;
	
	//semGive(sem_int_moins_bal_cim);
	if (qte_contenu_balance_ciment <= 0){
		qte_contenu_balance_ciment = 0;

		semGive(sem_ferm_balance_ciment);
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

