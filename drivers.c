#include "drivers.h"
#include "cimenterie.h"
#include "accesTampons.h"
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
int moteur_en_cours = INACTIF;
//PID des taches driver (test)
int tache_remplissage_ciment = INACTIF;
int tache_remplissage_agregat = INACTIF;
int tache_remplissage_eau = INACTIF;
int tache_versement_ciment = INACTIF;
int tache_versement_agregat = INACTIF;
int tache_versement_eau = INACTIF;
int tache_versement_balance_agregat = INACTIF;
int tache_versement_balance_ciment = INACTIF;
int tache_moteur = INACTIF;

void OuvrirVanne(char* vanne){
	int valeur;
	char buffer[TAILLE_MESSAGE_AFFICHAGE];

	strcpy(buffer, "Ouverture vanne : ");
	strcat(buffer, vanne);
	
	ajouter_message_affichage(buffer);
	
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
			ajouter_message_affichage("ERREUR, COMMANDE INCOMPRISE");
		}
	}
}

void FermerVanne(char* vanne){
	int valeur = 0;
	char buffer[TAILLE_MESSAGE_AFFICHAGE];

	strcpy(buffer, "Fermeture vanne : ");
	strcat(buffer, vanne);
	
	ajouter_message_affichage(buffer);
	
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
			ajouter_message_affichage("ERREUR, COMMANDE INCOMPRISE");
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
	ajouter_message_affichage("********** Démarrage du tapis *************");
}

void ArretTapis(char *tapis){
	ajouter_message_affichage("********** Arret du tapis *************");
}

void OuvrirBalance(char *balance){
	int valeur;
	char buffer[TAILLE_MESSAGE_AFFICHAGE];

	strcpy(buffer, "Ouverture balance : ");
	strcat(buffer, balance);
	
	ajouter_message_affichage(buffer);
	
	//Balance
	if (strcmp(balance, cst_balance_agregat) == 0){
		if (balance_agregat_versement_en_cours == INACTIF) {
			tache_versement_balance_agregat = taskSpawn("driver_versement_balance_agregat",200,
	                0x100,2000,(FUNCPTR) driver_versement_balance_agregat,
	                0,0,0,0,0,0,0,0,0,0);
			balance_agregat_versement_en_cours = ACTIF;
		}
	} else if(strcmp(balance, cst_balance_ciment) == 0) {
		if (balance_ciment_versement_en_cours == INACTIF){
			tache_versement_balance_ciment = taskSpawn("driver_versement_balance_ciment",200,
			                0x100,2000,(FUNCPTR) driver_versement_balance_ciment,
			                0,0,0,0,0,0,0,0,0,0);
			balance_ciment_versement_en_cours = ACTIF;
		}
	} else {
		ajouter_message_affichage("ERREUR, COMMANDE INCOMPRISE");
	}
}

void FermerBalance(char *balance){
	int valeur;
	char buffer[TAILLE_MESSAGE_AFFICHAGE];
	
	strcpy(buffer, "Fermeture balance : ");
	strcat(buffer, balance);
	
	ajouter_message_affichage(buffer);
	
	//Balance
	if (strcmp(balance, cst_balance_agregat) == 0){
		if (balance_agregat_versement_en_cours != INACTIF){
			taskDelete(tache_versement_balance_agregat);
			balance_agregat_versement_en_cours = INACTIF;
		}
	} else if(strcmp(balance, cst_balance_ciment) == 0) {
		if (balance_ciment_versement_en_cours != INACTIF){
			taskDelete(tache_versement_balance_ciment);
			balance_ciment_versement_en_cours = INACTIF;
		}
	} else {
		ajouter_message_affichage("ERREUR, COMMANDE INCOMPRISE");
	}
}

void AllumerDiodePositionCamion(){
	diode_position_camion = 1;
	ajouter_message_affichage("********** diode_position_camion allumée *************");
}

void EteindreDiodePositionCamion(){
	diode_position_camion = 0;
	ajouter_message_affichage("********** diode_position_camion éteinte *************");
}

void AllumerDiodeMalaxeur(){
	diode_malaxeur = 1;
	ajouter_message_affichage("********** diode_malaxeur allumée *************");
}

void EteindreDiodeMalaxeur(){
	diode_malaxeur = 0;
		ajouter_message_affichage("********** diode_malaxeur éteinte *************");
}

void consigne_moteur(int vitesse_voulue){
	if (moteur_en_cours == INACTIF){
		ajouter_message_affichage("Démarrage du moteur");
		moteur_en_cours = ACTIF;
		tache_moteur = taskSpawn("driver_moteur",100, 0x100,2000,(FUNCPTR) driver_moteur, vitesse_voulue,0,0,0,0,0,0,0,0,0);
	} else if (vitesse_voulue == 0){ //tache_moteur != INACTIF
		ajouter_message_affichage("Arret du moteur");
		taskDelete(tache_moteur);
	}
	
	vitesse_moteur = vitesse_voulue;
}

int getPresence(){
	if(timer_getPresence < 5){
		taskDelay(ATTENTE_ENTRE_DEUX_INT / 2);
		timer_getPresence = timer_getPresence + 1;
		return 0;
	}else{
		return 1;
	}
}

int getHygrometrie(){
	return (rand()%100);
}

int getVmot(){
	int vitesse;
	semTake(sem_vitesse_moteur, WAIT_FOREVER);
	vitesse = vitesse_moteur;
	semGive(sem_vitesse_moteur);
	
	return vitesse;
}

float getImot(){
	float intensite;
	int vitesse;
	
	vitesse = getVmot();
	intensite = (float)(couple_moteur*vitesse)/tension_moteur;
	return intensite;
}

int driver_moteur(int vitesse_voulue){
	float coefficient_directeur;
	coefficient_directeur = (vitesse_voulue - vitesse_moteur)/5.0;
	while(1){
		if (moteur_en_cours != INACTIF) {
			while(vitesse_moteur != vitesse_voulue){
				taskDelay(ATTENTE_ENTRE_DEUX_INT / 2);
				semTake(sem_vitesse_moteur, WAIT_FOREVER);
				
				if (vitesse_voulue > vitesse_moteur){
					vitesse_moteur = vitesse_moteur + coefficient_directeur;
				}
				
				if (vitesse_voulue < vitesse_moteur){
								vitesse_moteur = vitesse_moteur - coefficient_directeur;
				}
				semGive(sem_vitesse_moteur);
			}
			
			moteur_en_cours = INACTIF;
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
				taskDelay(ATTENTE_ENTRE_DEUX_INT /2);
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
				taskDelay(ATTENTE_ENTRE_DEUX_INT /2);
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
		
		semTake(sem_capacite_malaxeur, WAIT_FOREVER);
		capacite_malaxeur_courrante += UNITE_VOLUME_VERSEMENT;
		semGive(sem_capacite_malaxeur);
		
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
	while(1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT /2);
		
		semTake(sem_capacite_malaxeur, WAIT_FOREVER);
		capacite_malaxeur_courrante -= UNITE_VOLUME_VERSEMENT;
			
		if(capacite_malaxeur_courrante <= 0){
			capteur_vide_malaxeur();
		}
		semGive(sem_capacite_malaxeur);
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
		semTake(sem_capacite_malaxeur, WAIT_FOREVER);
		capacite_malaxeur_courrante += UNITE_VOLUME_VERSEMENT;
		semGive(sem_capacite_malaxeur);
	}
	
	return 0;
}

int driver_versement_balance_ciment(){
	while(1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT /2);
		
		//Simule une IT balance moins
		capteur_moins_balance_ciment();
		semTake(sem_capacite_malaxeur, WAIT_FOREVER);
		capacite_malaxeur_courrante += UNITE_VOLUME_VERSEMENT;
		semGive(sem_capacite_malaxeur);
	}
	
	return 0;
}

int driver_affichage_test(){
	int index = 0, index_aff = 0, capa_bal_agr = 0, capa_bal_cim = 0;
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
			acti_silo_vers[4 + index] = ciment_versement_en_cours[index];
			acti_silo_rempl[4 + index] = ciment_remplissage_en_cours[index];
			semGive(sem_capacite_silo_ciment_courrante);
		}
		//Balances
		capa_bal_agr = qte_contenu_balance_agregat;
		capa_bal_cim = qte_contenu_balance_ciment;
		
		/////////////////////////////////////////////AFFICHAGE
		
		//Vide la console
		printf("\33[2J");
		printf("\n");

		//Affichage des messages
		for(index_aff = 0; index_aff < MAX_MESSAGE_AFFICHAGE; index_aff += 1){
			if (strcmp(get_message_affichage(index_aff), "") != 0){
				printf("%s\n", get_message_affichage(index_aff));
			}
		}

		printf("\n");

		printf("%s\n", get_message_affichage_persistant());
		
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
			printf(" |     | ");
		}
		if (balance_ciment_versement_en_cours == INACTIF){
			printf("|_______|");
		} else {
			printf(" |     | ");
		}
		printf("\n");
		
		//Malaxeur
		printf("|malaxeur| ");
		printf("\n");
		semTake(sem_capacite_malaxeur, WAIT_FOREVER);
		printf("|__%d__| ", capacite_malaxeur_courrante);
		printf("\n");
		semGive(sem_capacite_malaxeur);
		if (malaxeur_versement_en_cours == INACTIF){
			printf("|xxxxxx| ");
		} else {
			printf("|      | ");
		}
		printf("\n");
		
		taskDelay(TAUX_RAFFRAICHISSEMENT);
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