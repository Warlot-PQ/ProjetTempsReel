#include "signauxExterieur.h"
#include "cimenterie.h"
#include "taches.h"
#include <taskLib.h>
#include <string.h>
#include <wdLib.h>

int agregat_versement_en_cours[3] = {INACTIF, INACTIF, INACTIF};
int agregat_remplissage_en_cours[3] = {INACTIF, INACTIF, INACTIF};
int ciment_versement_en_cours[2] = {INACTIF, INACTIF};
int ciment_remplissage_en_cours[2] = {INACTIF, INACTIF};
int eau_versement_en_cours = INACTIF;
int eau_remplissage_en_cours = INACTIF;
int malaxeur_versement_en_cours = INACTIF;
int balance_agregat_versement_en_cours = INACTIF;
int balance_ciment_versement_en_cours = INACTIF;
//PID des taches driver (test)
int tache_remplissage_ciment = INACTIF;
int tache_remplissage_agregat = INACTIF;
int tache_remplissage_eau = INACTIF;
int tache_versement_ciment = INACTIF;
int tache_versement_agregat = INACTIF;
int tache_versement_eau = INACTIF;


void OuvrirVanne(char* vanne){
	int valeur;
	printf("Ouverture vanne : %s\n", vanne);
	
	//Vannes bas
	if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_2) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
		//Simule le versement des agregats
		if (agregat_versement_en_cours[0] == INACTIF
				&& agregat_versement_en_cours[1] == INACTIF
				&& agregat_versement_en_cours[2] == INACTIF){
			tache_versement_agregat = taskSpawn("driver_versement_agregat",200,
					                0x100,2000,(FUNCPTR) driver_versement_silo_agregat,
					                0,0,0,0,0,0,0,0,0,0);
		}
		if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0
				&& agregat_versement_en_cours[0] == INACTIF){
			agregat_versement_en_cours[0] = ACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_2) == 0
				&& agregat_versement_en_cours[1] == INACTIF){
			agregat_versement_en_cours[1] = ACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_3) == 0
				&& agregat_versement_en_cours[2] == INACTIF){
			agregat_versement_en_cours[2] = ACTIF;
		}
	} else if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0
					|| strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
		//Simule le versement du ciment;
		if (ciment_versement_en_cours[0] == INACTIF
				&& ciment_versement_en_cours[1] == INACTIF){
			tache_versement_ciment = taskSpawn("driver_versement_ciment",200,
						                0x100,2000,(FUNCPTR) driver_versement_silo_ciment,
						                0,0,0,0,0,0,0,0,0,0);
		}
		if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0
				&& ciment_versement_en_cours[0] == INACTIF){
			ciment_versement_en_cours[0] = ACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_ciment_2) == 0
				&& ciment_versement_en_cours[0] == INACTIF){
			ciment_versement_en_cours[1] = ACTIF;
		}
	} else if (strcmp(vanne, cst_vanne_malaxeur) == 0) {
		//Simule le versement du malaxeur
		if (malaxeur_versement_en_cours == INACTIF){
			malaxeur_versement_en_cours = taskSpawn("driver_versement_malaxeur",200,
							                0x100,2000,(FUNCPTR) driver_versement_malaxeur,
							                0,0,0,0,0,0,0,0,0,0);
		}
	} else {
		//Vannes haut
		if (strcmp(vanne, cst_vanne_haut_agregat_1) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_2) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_3) == 0){
			//Simule le remplissage des agregats
			if (agregat_remplissage_en_cours[0] == INACTIF
					&& agregat_remplissage_en_cours[1] == INACTIF
					&& agregat_remplissage_en_cours[2] == INACTIF){
				tache_remplissage_agregat = taskSpawn("driver_remplissage_agregat",200,
						                0x100,2000,(FUNCPTR) driver_remplissage_silo_agregat,
						                0,0,0,0,0,0,0,0,0,0);
			}
			if (strcmp(vanne, cst_vanne_haut_agregat_1) == 0
					&& agregat_remplissage_en_cours[0] == INACTIF){
				agregat_remplissage_en_cours[0] = ACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_2) == 0
					&& agregat_remplissage_en_cours[1] == INACTIF){
				agregat_remplissage_en_cours[1] = ACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_3) == 0
					&& agregat_remplissage_en_cours[2] == INACTIF){
				agregat_remplissage_en_cours[2] = ACTIF;
			}
		} else if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0
				|| strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
			//Simule le remplissage du ciment
			if (ciment_remplissage_en_cours[0] == INACTIF
					&& ciment_remplissage_en_cours[1] == INACTIF){
				tache_remplissage_ciment = taskSpawn("driver_remplissage_ciment",200,
							                0x100,2000,(FUNCPTR) driver_remplissage_silo_ciment,
							                0,0,0,0,0,0,0,0,0,0);
			}
			if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0
					&& ciment_remplissage_en_cours[0] == INACTIF){
				ciment_remplissage_en_cours[0] = ACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_ciment_2) == 0
					&& ciment_remplissage_en_cours[1] == INACTIF){
				ciment_remplissage_en_cours[1] = ACTIF;
			}
		} else if (strcmp(vanne, cst_vanne_haut_eau) == 0){
			//Simule le remplissage de l'eau
			if (eau_remplissage_en_cours == INACTIF){
				tache_remplissage_eau = taskSpawn("driver_remplissage_eau",200,
									                0x100,2000,(FUNCPTR) driver_remplissage_silo_eau,
									                0,0,0,0,0,0,0,0,0,0);
				eau_remplissage_en_cours = ACTIF;
			}
		} else {
			printf("ERREUR, COMMANDE INCOMPRISE\n");
		}
	}
}

void FermerVanne(char* vanne){
	int valeur = 0;
	//printf("Fermeture vanne : %s\n", vanne);
	
	//Vannes bas
	if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_2) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
		//Simule l'arret du versement des agregats
		if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0){
			agregat_versement_en_cours[0] = INACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_2) == 0){
			agregat_versement_en_cours[1] = INACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
			agregat_versement_en_cours[2] = INACTIF;
		}
		//Si toutes les vannes agregat bas sont fermé, on supprime 
		if (agregat_versement_en_cours[0] == INACTIF
				&& agregat_versement_en_cours[1] == INACTIF
				&& agregat_versement_en_cours[2] == INACTIF){
			taskDelete(tache_versement_agregat);
		}
	} else if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0
					|| strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
		//Simule l'arret du versement du ciment
		if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0){
			ciment_versement_en_cours[0] = INACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
			ciment_versement_en_cours[1] = INACTIF;
		}
		//Si toutes les vannes ciment bas sont fermé, on supprime 
		if (ciment_versement_en_cours[0] == INACTIF
				&& ciment_versement_en_cours[1] == INACTIF){
			taskDelete(tache_versement_ciment);
		}
	} else if (strcmp(vanne, cst_vanne_bas_eau) == 0){
		//Simule l'arret du versement de l'eau
		eau_versement_en_cours = INACTIF;
		taskDelete(tache_versement_eau);
	} else if (strcmp(vanne, cst_vanne_malaxeur) == 0) {
		//Simule l'arret du versement du malaxeur
		taskDelete(malaxeur_versement_en_cours);
		malaxeur_versement_en_cours = INACTIF;
	} else {
		//Vannes haut
		if (strcmp(vanne, cst_vanne_haut_agregat_1) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_2) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_3) == 0){
			//Simule le remplissage des agregats
			if (strcmp(vanne, cst_vanne_haut_agregat_1) == 0){
				agregat_remplissage_en_cours[0] = INACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_2) == 0){
				agregat_remplissage_en_cours[1] = INACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_3) == 0){
				agregat_remplissage_en_cours[2] = INACTIF;
			}
			//Si toutes les vannes agregat heut sont fermé, on supprime 
			if (agregat_remplissage_en_cours[0] == INACTIF
					&& agregat_remplissage_en_cours[1] == INACTIF
					&& agregat_remplissage_en_cours[2] == INACTIF){
				taskDelete(tache_remplissage_agregat);
			}
		} else if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0
				|| strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
			//Simule le remplissage du ciment
			if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0){
				ciment_remplissage_en_cours[0] = INACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
				ciment_remplissage_en_cours[1] = INACTIF;
			}
			//Si toutes les vannes ciment haut sont fermé, on supprime 
			if (ciment_remplissage_en_cours[0] == INACTIF
					&& ciment_remplissage_en_cours[1] == INACTIF){
				taskDelete(tache_remplissage_ciment);
			}
		} else if (strcmp(vanne, cst_vanne_haut_eau) == 0){
			//Simule le remplissage de l'eau
			eau_remplissage_en_cours = INACTIF;
			taskDelete(tache_remplissage_eau);
		} else {
			printf("ERREUR, COMMANDE INCOMPRISE\n");
		}
	}
}

void OuvrirRobinet(char *vanne, int ouverture){
	if (strcmp(vanne, cst_vanne_bas_eau) == 0){
		if (ouverture > 0) {
			if (eau_versement_en_cours == INACTIF){
				tache_versement_eau = taskSpawn("driver_versement_eau",200,
							                0x100,2000,(FUNCPTR) driver_versement_silo_eau,
							                0,0,0,0,0,0,0,0,0,0);
				eau_versement_en_cours = ACTIF;
			}
		} else {
			FermerVanne(cst_vanne_bas_eau);
		}
	}
}

void DemarrageTapis(char *tapis){

}

void ArretTapis(char *tapis){

}

void CommandeMalaxeur(int tension){

}

void OuvrirBalance(char *balance){
	int valeur;
	//printf("Ouverture vanne : %s\n", balance);
	
	//Balance
	if (strcmp(balance, cst_balance_agregat) == 0){
		if (balance_agregat_versement_en_cours == INACTIF) {
			valeur = taskSpawn("driver_versement_agregat",200,
	                0x100,2000,(FUNCPTR) driver_versement_balance_agregat,
	                0,0,0,0,0,0,0,0,0,0);
			balance_agregat_versement_en_cours = valeur;
		}
	} else if(strcmp(balance, cst_balance_ciment) == 0) {
		if (balance_ciment_versement_en_cours == INACTIF){
			valeur = taskSpawn("driver_versement_agregat",200,
			                0x100,2000,(FUNCPTR) driver_versement_balance_ciment,
			                0,0,0,0,0,0,0,0,0,0);
			balance_ciment_versement_en_cours = valeur;
		}
	} else {
		printf("ERREUR, COMMANDE INCOMPRISE\n");
	}
}

void FermerBalance(char *balance){
	int valeur;
	//printf("Fermeture balance : %s\n", balance);
	
	//Balance
	if (strcmp(balance, cst_balance_agregat) == 0){
		valeur = balance_agregat_versement_en_cours;
		taskDelete(valeur);
		balance_agregat_versement_en_cours = INACTIF;
	} else if(strcmp(balance, cst_balance_ciment) == 0) {
		valeur = balance_ciment_versement_en_cours;
		taskDelete(valeur);
		balance_ciment_versement_en_cours = INACTIF;
	} else {
		printf("ERREUR, COMMANDE INCOMPRISE\n");
	}
}

void AllumerDiodePositionCamion(){
	diode_position_camion = 1;
	//printf("\n********** diode_position_camion allumée *************\n");
}

void EteindreDiodePositionCamion(){
	diode_position_camion = 0;
	//printf("\n********** diode_position_camion éteinte *************\n");
}

void AllumerDiodeMalaxeur(){
	diode_malaxeur = 1;
		printf("\n********** diode_malaxeur allumée *************\n");
}

void EteindreDiodeMalaxeur(){
	diode_malaxeur = 0;
		printf("\n********** diode_malaxeur éteinte *************\n");
}

void consigne_moteur(int vitesse_voulue){
	int moteur_task_id;
	
	if(vitesse_voulue>0 && vitesse_voulue != vitesse_moteur){
		//printf("\n consigne_moteur : taskSpawn \n");
		moteur_task_id = taskSpawn("driver_moteur",100, 0x100,2000,(FUNCPTR) driver_moteur, vitesse_voulue,0,0,0,0,0,0,0,0,0);
	}else{
		//printf("\n vitesse_voulue = vitesse_moteur : driver non lancé \n");
	}
}

int getPresence(){
	if(timer_getPresence < 5){
		taskDelay(100);
		timer_getPresence = timer_getPresence + 1;
		//printf("timer_getPresence : %d\n", timer_getPresence);
		return 0;
	}else{
		//printf("timer_getPresence : %d\n", timer_getPresence);
		return 1;
	}
}

int getVolume(){

}

int getDistance(){

}

int getTypeBeton(){

}

int getHygrometrie(){
	return (rand()%100);
}

int getVmot(){
	int vitesse;
	semTake(sem_vitesse_moteur, WAIT_FOREVER);
	vitesse = vitesse_moteur;
	//printf("vitesse_moteur : %d\n", vitesse);
	semGive(sem_vitesse_moteur);
	
	return vitesse;
}

float getImot(){
	float intensite;
	int vitesse;
	
	vitesse = getVmot();
	intensite = (float)(couple_moteur*vitesse)/tension_moteur;
	//printf("intensite du moteur : %f\n", intensite);
	return intensite;
}

int getEtatBmal(){

}

void interruptionMin(char* element){

}

void interruptionMax(char* element){

}

void interruptionPlus(char* element){

}

void interruptionMoins(char* element){

}


int driver_moteur(int vitesse_voulue){
	float coefficient_directeur;
	//printf("driver_moteur\n");
	coefficient_directeur = (vitesse_voulue-vitesse_moteur)/5.0;
	while(1){
		while(vitesse_moteur != vitesse_voulue){
			//printf("VITESSE VOULUE : %d\n\n", vitesse_voulue);
			taskDelay(100);
			semTake(sem_vitesse_moteur, WAIT_FOREVER);
			//printf("driver_moteur : prise du jeton \n");
			if (vitesse_voulue > vitesse_moteur){
				vitesse_moteur = vitesse_moteur + coefficient_directeur;
			}
			
			printf("Vitesse moteur actuelle : %d\n", vitesse_voulue);
			
			if (vitesse_voulue < vitesse_moteur){
							vitesse_moteur = vitesse_moteur - coefficient_directeur;
			}
			semGive(sem_vitesse_moteur);
			//printf("driver_moteur : vitesse moteur = %d \n", vitesse_moteur);
			//printf("driver_moteur : vitesse voulue = %d \n", vitesse_voulue);
			//printf("driver_moteur : rend le jeton \n");
		}
		
		if(vitesse_voulue == vitesse_moteur){
			//printf("driver_moteur : taskDelete\n");
			taskDelete(taskIdSelf());
		}
	}
	return 0;
}

int driver_versement_silo_agregat(){
	int i;
	
	while (1){
		for (i = 0; i < 3; i += 1){
			if (agregat_versement_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				//Decremente contenu silo
				semTake(sem_capacite_silo_agregat_courrante, WAIT_FOREVER);
				capacite_silo_agregat_courrante[i] -= UNITE_VOLUME_VERSEMENT;
				//Simule IT plus balance agregat
				capteur_plus_balance_agregats();
				//Test silo vide, si oui envoie le signal du capteur silo vide
				if (capacite_silo_agregat_courrante[i] <= 0){
					switch(i){
					case 0:
						semGive(sem_int_min_agr_1);
						break;
					case 1:
						semGive(sem_int_min_agr_2);
						break;
					default:
						semGive(sem_int_min_agr_3);
					}
				}
				semGive(sem_capacite_silo_agregat_courrante);
			}
		}
	}
	
	return 0;
}
int driver_versement_silo_ciment(){
	int i;
	
	while (1){
		for (i = 0; i < 2; i += 1){
			if (ciment_versement_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				//Decremente contenu silo
				semTake(sem_capacite_silo_ciment_courrante, WAIT_FOREVER);
				capacite_silo_ciment_courrante[i] -= UNITE_VOLUME_VERSEMENT;
				//Simule IT plus balance agregat
				capteur_plus_balance_ciment();
				//Test silo vide, si oui envoie le signal du capteur silo vide
				if (capacite_silo_ciment_courrante[i] <= 0){
					switch(i){
					case 0:
						capteur_vide_silo_ciment_1();
						break;
					default:
						capteur_vide_silo_ciment_2();
					}
				}
				semGive(sem_capacite_silo_ciment_courrante);
			}
		}
	}
	
	return 0;
}
int driver_versement_silo_eau(){
	while (1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT /2);
		//Decremente contenu silo
		semTake(sem_capacite_silo_eau_courrante, WAIT_FOREVER);
		capacite_silo_eau_courrante -= UNITE_VOLUME_VERSEMENT;
		//Simule IT moins silo eau
		capteur_moins_eau();
		//Test silo vide, si oui envoie le signal du capteur silo vide
		if (capacite_silo_eau_courrante <= 0){
			capteur_vide_eau();
		}
		semGive(sem_capacite_silo_eau_courrante);
	}
	
	return 0;
}
int driver_versement_malaxeur(){
	timer_versement_malaxeur = 0;
	
	while(1){
		timer_versement_malaxeur = timer_versement_malaxeur + 1;
		printf("timer_versement_malaxeur : %d \n", timer_versement_malaxeur);
		taskDelay(80);
		
		if(timer_versement_malaxeur >= cste_temps_versement){
			capteur_vide_malaxeur();
		}
	}
	return 0;
}
int driver_remplissage_silo_agregat(){
	int i;
		
	while (1){
		for (i = 0; i < 3; i += 1){
			if (agregat_remplissage_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT / 2);
				//Decremente contenu silo
				semTake(sem_capacite_silo_agregat_courrante, WAIT_FOREVER);
				capacite_silo_agregat_courrante[i] += UNITE_VOLUME_REMPLISSAGE;
				//Test silo vide, si oui envoie le signal du capteur silo vide
				if (capacite_silo_agregat_courrante[i] >= NIVEAU_AGREGAT_MAX){
					//printf("Capa max agregat %d : %d/%d ", i, capacite_silo_agregat_courrante[i],NIVEAU_AGREGAT_MAX);
					switch(i){
					case 0:
						capteur_plein_silo_agregat_1();
						break;
					case 1:
						capteur_plein_silo_agregat_2();
						break;
					default:
						capteur_plein_silo_agregat_3();
					}
				}
				semGive(sem_capacite_silo_agregat_courrante);
			}
		}
	}
	
	return 0;
}
int driver_remplissage_silo_ciment(){
	int i;
		
	while (1){
		for (i = 0; i < 2; i += 1){
			if (ciment_remplissage_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT / 2);
				//Decremente contenu silo
				semTake(sem_capacite_silo_ciment_courrante, WAIT_FOREVER);
				capacite_silo_ciment_courrante[i] += UNITE_VOLUME_REMPLISSAGE;
				//Test silo vide, si oui envoie le signal du capteur silo vide
				if (capacite_silo_ciment_courrante[i] >= NIVEAU_CIMENT_MAX){
					//printf("Capa max ciment %d : %d/%d ", i, capacite_silo_ciment_courrante[i],NIVEAU_CIMENT_MAX);
					switch(i){
					case 0:
						capteur_plein_silo_ciment_1();
						break;
					default:
						capteur_plein_silo_ciment_2();
					}
				}
				semGive(sem_capacite_silo_ciment_courrante);
			}
		}
	}
	
	return 0;
}
int driver_remplissage_silo_eau(){
	while (1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT / 2);
		
		//Decremente contenu silo
		semTake(sem_capacite_silo_eau_courrante, WAIT_FOREVER);
		capacite_silo_eau_courrante += UNITE_VOLUME_REMPLISSAGE;
		//Simule IT plus silo eau
		capteur_plus_eau();
		//Test silo vide, si oui envoie le signal du capteur silo vide
		if (capacite_silo_eau_courrante >= NIVEAU_EAU_MAX){
			//printf("Capa max eau : %d/%d ", capacite_silo_eau_courrante, NIVEAU_EAU_MAX);
			capteur_plein_eau();
		}
		semGive(sem_capacite_silo_eau_courrante);
	}
	
	return 0;
}

int driver_versement_balance_agregat(){
	while(1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT /2);
		
		//Simule une IT balance moins
		capteur_moins_balance_agregats();
	}
	
	return 0;
}

int driver_versement_balance_ciment(){
	while(1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT /2);
		
		//Simule une IT balance moins
		capteur_moins_balance_ciment();
	}
	
	return 0;
}

int driver_affichage_test(){
	int index = 0, capa_bal_agr = 0, capa_bal_cim = 0;
	int long_silo[] = {0, 0, 0, 0, 0, 0};
	int capa_silo[] = {0, 0, 0, 0, 0, 0};
	int acti_silo_vers[] = {0, 0, 0, 0, 0, 0};
	int acti_silo_rempl[] = {0, 0, 0, 0, 0, 0};
	
	while(1){
		/////////////////////////////////////////////CHARGEMENT DES DONNES
		//Agregat
		for (index = 0; index < 3; index += 1){
			semTake(sem_capacite_silo_agregat_courrante, WAIT_FOREVER);
			long_silo[index] = longueur_entier(capa_silo[index]);
			capa_silo[index] = capacite_silo_agregat_courrante[index];
			acti_silo_vers[index] = agregat_versement_en_cours[index];
			acti_silo_rempl[index] = agregat_remplissage_en_cours[index];
			semGive(sem_capacite_silo_agregat_courrante);
		}
		//Eau
		semTake(sem_capacite_silo_eau_courrante, WAIT_FOREVER);
		long_silo[3] = longueur_entier(capa_silo[3]);
		capa_silo[3] = capacite_silo_eau_courrante;
		acti_silo_vers[3] = eau_versement_en_cours;
		acti_silo_rempl[3] = eau_remplissage_en_cours;
		semGive(sem_capacite_silo_eau_courrante);
		//Ciment
		for (index = 0; index < 2; index += 1){
			semTake(sem_capacite_silo_ciment_courrante, WAIT_FOREVER);
			long_silo[4 + index] = longueur_entier(capa_silo[4 + index]);
			capa_silo[4 + index] = capacite_silo_ciment_courrante[index];
			acti_silo_vers[4 + index] = ciment_versement_en_cours[4 + index];
			acti_silo_rempl[4 + index] = ciment_remplissage_en_cours[4 + index];
			semGive(sem_capacite_silo_ciment_courrante);
		}
		//Balances
		capa_bal_agr = qte_contenu_balance_agregat;
		capa_bal_cim = qte_contenu_balance_ciment;
		
		/////////////////////////////////////////////AFFICHAGE
		
		//Vide la console
		printf("\33[2J");
		printf("\n");

		//Affichage des nom des silos
		affiche_silo(long_silo, capa_silo, acti_silo_vers, acti_silo_rempl, 'r');
		
		//Affichage des nom des silos
		affiche_silo(long_silo, capa_silo, acti_silo_vers, acti_silo_rempl, 't');
		
		//Affichage de la quantites des silos
		affiche_silo(long_silo, capa_silo, acti_silo_vers, acti_silo_rempl, 'q');

		//Affichage du statut des vannes des silos
		affiche_silo(long_silo, capa_silo, acti_silo_vers, acti_silo_rempl, 'v');
		
		
		//Balance quantite
		printf("|bal agr| |bal cim|\n");
		printf("|___%d___| |___%d___|\n", capa_bal_agr, capa_bal_cim);
		//Balance vanne
		if (balance_agregat_versement_en_cours == INACTIF){
			printf("|_______| ");
		} else {
			printf(" |     |");
		}
		if (balance_ciment_versement_en_cours == INACTIF){
			printf("|_______|");
		} else {
			printf(" |     |");
		}
		printf("\n");
		taskDelay(100);
	}
	
	return 0;
	
}

void affiche_silo(int long_silo[6], int capa_silo[6], int acti_silo_vers[6], int acti_silo_rempl[6], char statut){
	char *nom_silo = NULL;
	int num_silo = 0, index = 0;
	char *repetition_vide;
	char *repetition_croix;
	
	for (index = 0; index < 6; index += 1){
		//Nom et numero du silo
		if (index < 3) {
			nom_silo = "agr";
			num_silo = index;
		} else if (index > 3){
			nom_silo = "cim";
			num_silo = index - 3;
		} else {
			nom_silo = "eau";
			num_silo = 1;
		}
		//Calcul les correctifs d'espacement
		if (long_silo[index] == 1){
			repetition_vide = "";
			repetition_croix = "";
		} else if (long_silo[index] == 2){
			repetition_vide = " ";
			repetition_croix = "x";
		} else {
			repetition_vide = "  ";
			repetition_croix = "xx";			
		}
		//Affichage
		if (statut == 't') {
			printf("|%s%s %d| ", nom_silo, repetition_vide, num_silo);
		} else if (statut == 'q'){
			printf("|__%d__| ", capa_silo[index]);
		} else { //statut == 'v' ou 'r'
			if ((statut == 'v' && acti_silo_vers[index] == INACTIF)
					|| (statut == 'r' && acti_silo_rempl[index] == INACTIF)){
					printf(" |xxx%s|  ", repetition_croix, num_silo);
			} else {
				printf(" |  %s |  ", repetition_vide, num_silo);
			}
		}
	}
	printf("\n");
}

int longueur_entier(int entier){
	int valeur = 0;
	
	do{
		entier = entier / 10;
		valeur += 1;
	}while(entier > 0);
	
	return valeur;
}