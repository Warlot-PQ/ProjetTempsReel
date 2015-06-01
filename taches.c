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
	int cmd_plus_recente, cmd_en_cours;
	
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
		//Ici tous les silos d'agregat ont été versés
		semGive(sem_pret_balance_agregat);	//Signal balance agr prête pour synchro
		
		semTake(sem_ouverture_balance_agregat, WAIT_FOREVER);	//Attente de l'ordre d'ouverture
		av_tapis_agr();
		van_ouvr_bal_agr();
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
		//Ici tous les silos d'agregat ont été versés
		semGive(sem_pret_balance_ciment);	//Signal balance agr prête pour synchro
		
		semTake(sem_ouverture_balance_ciment, WAIT_FOREVER);	//Attente de l'ordre d'ouverture
		av_tapis_cim();
		van_ouvr_bal_cim();
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
	ecrire_quantite_agregat_totale_nulle();
	//Numéro du silo en cours de versement
	int num_silo = 0;
	
	while (1){
		msgQReceive(file_debut_remplissage_balance_agregat, num_silo, 1, WAIT_FOREVER);
		
		ajouter_quantite_agregat_totale(lire_tampon_qte_silos_agregat(num_silo));
		ecrire_quantite_agregat_restant(lire_tampon_qte_silos_agregat(num_silo));
	}
	return 0;
}
int compteur_plus_balance_agregats(){
	decremente_quantite_agregat_restant();
	
	if (is_quantite_agregat_restant_nulle()){
		semGive(sem_fin_remplissage_balance_agregat, WAIT_FOREVER);
	}
}
int compteur_moins_balance_agregats(){
	decremente_quantite_agregat_totale();
	
	if (is_quantite_agregat_totale_nulle()){
		van_ferm_bal_agr();
		
		//TODO tampo de 120s
		
		ar_tapis_agr();
		semGive(sem_fin_vers_balance_agregat, WAIT_FOREVER);
	}
	
}
int gestion_balance_ciment(){
	ecrire_quantite_ciment_totale_nulle();
	//Numéro du silo en cours de versement
	int num_silo = 0;
	
	while (1){
		msgQReceive(file_debut_remplissage_balance_ciment, num_silo, 1, WAIT_FOREVER);
		
		ajouter_quantite_ciment_totale(lire_tampon_qte_silos_ciment(num_silo));
		ecrire_quantite_ciment_restant(lire_tampon_qte_silos_ciment(num_silo));
	}
	return 0;
}
int compteur_plus_balance_ciment(){
	decremente_quantite_ciment_restant();
	
	if (is_quantite_ciment_restant_nulle()){
		semGive(sem_fin_remplissage_balance_ciment, WAIT_FOREVER);
	}
}
int compteur_moins_balance_ciment(){
	decremente_quantite_ciment_totale();
	
	if (is_quantite_ciment_totale_nulle()){
		van_ferm_bal_cim();
		
		//TODO tampo de 120s
		
		ar_tapis_cim();
		semGive(sem_fin_vers_balance_ciment, WAIT_FOREVER);
	}
	
}

int gestion_synchro(){
	while (1){
		//Synchro ouverture des balances
		semTake(sem_pret_balance_agregat, WAIT_FOREVER);
		semTake(sem_pret_balance_ciment, WAIT_FOREVER);
		
		int cmd_agr_en_cours = lire_tampon_fonct_calcul_cmd_agregat();
		int cmd_cim_en_cours = lire_tampon_fonct_calcul_cmd_ciment();
		int cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
		
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
	versement_eau_en_cours = 0;
	
	while(1){
		// Attend une demande de versement
		semTake(sem_demande_versement_eau, WAIT_FOREVER);
		
		versement_eau_en_cours = true;
		
		// Lance le calcul de la quantité d'eau
		semGive(sem_calcul_eau);
		
		ecrire_quantite_eau_restante(lire_tampon_qte_silos_eau());
		
		// Début versement dès que c'est possible, attente si impossible
		while(!is_versement_eau_possible()):
		van_bas_ouvr_eau();
	}
	
	return 0;
}
int remplissage_eau(){
	ecrire_niveau_eau_nul();
	
	// Initialisation du système, remplissage du silo
	//Rupture versement
	van_bas_ferm_eau();
	set_versement_eau_possible(false);
	
	van_haut_ouvr_eau();
	
	// Attente de l'évènement silo plein
	semTake(sem_int_max_eau, WAIT_FOREVER);
	
	van_haut_ferm_eau();
	ecrire_niveau_eau_max();
	//Autorise le versement
	set_versement_eau_possible(true);
	
	while(1){
		semTake(sem_int_min_eau, WAIT_FOREVER);		// silo eau vide
		
		//*************Rupture versement
		set_versement_eau_possible(false);
		van_bas_ferm_eau();
		
		//*************Début du remplissage
		van_haut_ouvr_eau();
		
		// Attente de l'évènement silo plein
		semTake(sem_int_max_eau, WAIT_FOREVER);
		
		//*************Fin du remplissage
		van_haut_ferm_eau();
		ecrire_niveau_eau_max();
		
		//*************Reprise du versement
		set_versement_eau_possible(true);
		if (versement_eau_en_cours == true) {
			van_bas_ouvr_eau();
		}
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
		decremente_quantite_eau_restante();
		
		if(is_quantite_eau_restante_nulle() == 1) {
			van_bas_ferm_eau();
		}
	}
	
	return 0;
}

int gestion_position_camion(){
	int timer_camion_present;
	char* buffer_camion_absent;
	bool position_camion_present_recu;
	position_camion_present = false;
	
	while(1){
		semTake(sem_debut_camion, WAIT_FOREVER);
		semGive(sem_diode_allumer_camion);
		
		while(msgQReceive(file_position_camion_absent_malaxeur, buffer_camion_absent, 100, NO_WAIT) == 0){
			//reception du signal camion_position_present_malaxeur : le camion est en place.
			semTake(sem_position_camion_present_malaxeur, WAIT_FOREVER);
			position_camion_present = true;
			semGive(sem_diode_eteindre_camion);
			timer_camion_present = 0;
			while(timer_camion_present < 5){
				wait(1);
				timer_camion_present += 1;
			}
		}
		semGive(sem_position_camion_ok);
	}
	return 0;
}
int gestion_versement(){
	int temps_versement;
	
	while(1){
		timer_versement = 0;
		semTake(sem_position_camion_ok, WAIT_FOREVER);
		semGive(sem_van_ouvre_malaxeur);
		
		while(temps_versement < temps_versement){
			wait(1);
			timer_versement += 1;
		}
		semGive(sem_arret_rotation_moteur);
		semTake(sem_vide_malaxeur, WAIT_FOREVER);
		semGive(sem_van_ferme_malaxeur);
		semGive(fin_malaxeur);
	}
	return 0;
}
int gestion_moteur(){
	bool Imax_atteint;
	int temps_sans_fluctuation;
	char* buffer_file_intensite, buffer_file_vitesse;
	float intensite, vitesse, intensite_avant;
	intensite_avant = 0;
	
	while(1){
		semTake(debut_malaxeur, WAIT_FOREVER);
		//Invariant à revoir : la tâche boucle tant qu'elle n'a pas envoyé debut_camion.
		while(!Imax_atteint){
			consigne_moteur(vitesse_max);
			Imax_atteint = false;
			temps_sans_fluctuation = 0;
		//invariant à revoir : ne doit pas porter sur Imax_atteint
			while(!Imax_atteint){
				semGive(sem_demande_valeur_intensite_malaxeur);
				msgQReceive(file_valeur_intensite_malaxeur, buffer_file, 100, WAIT_FOREVER);
				sprintf(str, buffer_file, intensite);
				semGive(sem_demande_valeur_vitesse_malaxeur);
				msgQReceive(file_valeur_vitesse_malaxeur, buffer_file, 100, WAIT_FOREVER);
				sprintf(str, buffer_file_valeur_intensite, vitesse);
				
				msgQSend(file_intensite, (char *) intensite, 100, WAIT_FOREVER, MSG_PRI_NORMAL);
				
				if(intensite < Imax){
					if(abs(intensite - intensite_avant) < 0.05){
						temps_sans_fluctuation += 1;
						if(temps_sans_fluctuation < temps_cst){
							if(!Imax_atteint){
								semGive(sem_diode_eteindre_malaxeur);
								semGive(sem_reprise_bal_tapis_agrEtCim);
							}
						}else{
							semGive(debut_camion);
						}
					}else{
						temps_sans_fluctuation = 0;
						if(Imax_atteint){
							semGive(sem_diode_eteindre_malaxeur);
							semGive(sem_reprise_bal_tapis_agrEtCim);
						}
					}
				}else{
					consigne_moteur(0);
					Imax_atteint = true;
					semGive(sem_stop_bal_tapis_agrEtCim);
					semGive(sem_diode_allumer_malax);
				}
			}
		}
		
		semGive(sem_debut_camion);
	}
	return 0;
}
