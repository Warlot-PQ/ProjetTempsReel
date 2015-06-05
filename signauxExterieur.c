#include "signauxExterieur.h"
#include "cimenterie.h"
#include "taches.h"
#include <taskLib.h>
#include <string.h>

#define INACTIF -1
#define ATTENTE_ENTRE_DEUX_INT 100

int capacite_silo_agregat_courrante[3] = {0, 0, 0};
int capacite_silo_ciment_courrante[2] = {0, 0};
int capacite_silo_eau_courrante = 0;

//PID des tâches
//0 signifie inactif et le pid de la tache en cours sinon, l'index représente le numéro du silo
int agregat_versement_en_cours[3] = {INACTIF, INACTIF, INACTIF};
int agregat_remplissage_en_cours[3] = {INACTIF, INACTIF, INACTIF};
int ciment_versement_en_cours[2] = {INACTIF, INACTIF};
int ciment_remplissage_en_cours[2] = {INACTIF, INACTIF};
int eau_versement_en_cours = INACTIF;
int eau_remplissage_en_cours = INACTIF;
int malaxeur_versement_en_cours = INACTIF;
int balance_agregat_versement_en_cours = INACTIF;
int balance_ciment_versement_en_cours = INACTIF;

void OuvrirVanne(char* vanne){
	int valeur;
	printf("Ouverture vanne : %s\n", vanne);
	
	//Vannes bas
	if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_2) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
		//Simule le versement des agregats
		printf("tache versement agregat lancee\n");
		
		valeur = taskSpawn("driver_versement_agregat",200,
					                0x100,2000,(FUNCPTR) driver_versement_silo_agregat,
					                0,0,0,0,0,0,0,0,0,0);
		if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0){
			agregat_versement_en_cours[0] = valeur;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_2) == 0){
			agregat_versement_en_cours[1] = valeur;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
			agregat_versement_en_cours[2] = valeur;
		}
	} else if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0
					|| strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
		//Simule le versement du ciment
		printf("tache versement ciment lancee\n");
		
		valeur = taskSpawn("driver_versement_ciment",200,
						                0x100,2000,(FUNCPTR) driver_versement_silo_ciment,
						                0,0,0,0,0,0,0,0,0,0);
		if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0){
			ciment_versement_en_cours[0] = valeur;
		} else if (strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
			ciment_versement_en_cours[1] = valeur;
		}
	} else if (strcmp(vanne, cst_vanne_bas_eau) == 0){
		//Simule le versement de l'eau
		printf("tache versement eau lancee%s\n");
		
		eau_versement_en_cours = taskSpawn("driver_versement_eau",200,
						                0x100,2000,(FUNCPTR) driver_versement_silo_eau,
						                0,0,0,0,0,0,0,0,0,0);
	} else if (strcmp(vanne, cst_vanne_malaxeur) == 0) {
		//Simule le versement du malaxeur
		printf("tache versement malaxeur lancee\n");
		
		malaxeur_versement_en_cours = taskSpawn("driver_versement_malaxeur",200,
							                0x100,2000,(FUNCPTR) driver_versement_malaxeur,
							                0,0,0,0,0,0,0,0,0,0);
	} else {
		//Vannes haut
		if (strcmp(vanne, cst_vanne_haut_agregat_1) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_2) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_3) == 0){
			//Simule le remplissage des agregats
			valeur = taskSpawn("driver_remplissage_agregat",200,
						                0x100,2000,(FUNCPTR) driver_remplissage_silo_agregat,
						                0,0,0,0,0,0,0,0,0,0);
			if (strcmp(vanne, cst_vanne_haut_agregat_1) == 0){
				agregat_remplissage_en_cours[0] = valeur;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_2) == 0){
				agregat_remplissage_en_cours[1] = valeur;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_3) == 0){
				agregat_remplissage_en_cours[2] = valeur;
			}
		} else if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0
				|| strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
			//Simule le remplissage du ciment
			valeur = taskSpawn("driver_remplissage_ciment",200,
							                0x100,2000,(FUNCPTR) driver_remplissage_silo_ciment,
							                0,0,0,0,0,0,0,0,0,0);
			if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0){
				ciment_remplissage_en_cours[0] = valeur;
			} else if (strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
				ciment_remplissage_en_cours[1] = valeur;
			}
		} else if (strcmp(vanne, cst_vanne_haut_eau) == 0){
			//Simule le remplissage de l'eau
			eau_remplissage_en_cours = taskSpawn("driver_versement_eau",200,
									                0x100,2000,(FUNCPTR) driver_remplissage_silo_eau,
									                0,0,0,0,0,0,0,0,0,0);
		} else {
			printf("ERREUR, COMMANDE INCOMPRISE\n");
		}
	}
}

void FermerVanne(char* vanne){
	int valeur = 0;
	printf("Fermeture vanne : %s\n", vanne);
	
	//Vannes bas
	if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_2) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
		//Simule l'arret du versement des agregats
		if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0){
			valeur = agregat_versement_en_cours[0];
			agregat_versement_en_cours[0] = INACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_2) == 0){
			valeur = agregat_versement_en_cours[1];
			agregat_versement_en_cours[1] = INACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
			valeur = agregat_versement_en_cours[2];
			agregat_versement_en_cours[2] = INACTIF;
		}
		taskDelete(valeur);
	} else if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0
					|| strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
		//Simule l'arret du versement du ciment
		if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0){
			valeur = ciment_versement_en_cours[0];
			ciment_versement_en_cours[0] = INACTIF;
		} else if (strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
			valeur = ciment_versement_en_cours[1];
			ciment_versement_en_cours[1] = INACTIF;
		}
		taskDelete(valeur);
	} else if (strcmp(vanne, cst_vanne_bas_eau) == 0){
		//Simule l'arret du versement de l'eau
		taskDelete(eau_versement_en_cours);
		eau_versement_en_cours = INACTIF;
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
				valeur = agregat_remplissage_en_cours[0];
				agregat_remplissage_en_cours[0] = INACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_2) == 0){
				valeur = agregat_remplissage_en_cours[1];
				agregat_remplissage_en_cours[1] = INACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_agregat_3) == 0){
				valeur = agregat_remplissage_en_cours[2];
				agregat_remplissage_en_cours[2] = INACTIF;
			}
			taskDelete(valeur);
		} else if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0
				|| strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
			//Simule le remplissage du ciment
			if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0){
				valeur = ciment_remplissage_en_cours[0];
				ciment_remplissage_en_cours[0] = INACTIF;
			} else if (strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
				valeur = ciment_remplissage_en_cours[1];
				ciment_remplissage_en_cours[1] = INACTIF;
			}
			taskDelete(valeur);
		} else if (strcmp(vanne, cst_vanne_haut_eau) == 0){
			//Simule le remplissage de l'eau
			taskDelete(eau_remplissage_en_cours);
			eau_remplissage_en_cours = INACTIF;
		} else {
			printf("ERREUR, COMMANDE INCOMPRISE\n");
		}
	}
}

void OuvrirRobinet(char *vanne, int ouverture){

}

void DemarrageTapis(char *tapis){

}

void ArretTapis(char *tapis){

}

void CommandeMalaxeur(int tension){

}

void OuvrirBalance(char *balance){
	int valeur;
	printf("Ouverture balance : %s\n", balance);
	
	//Balance
	if (strcmp(balance, cst_balance_agregat) == 0){
		valeur = taskSpawn("driver_versement_agregat",200,
                0x100,2000,(FUNCPTR) driver_versement_balance_agregat,
                0,0,0,0,0,0,0,0,0,0);
		balance_agregat_versement_en_cours = valeur;
	} else if(strcmp(balance, cst_balance_ciment) == 0) {
		valeur = taskSpawn("driver_versement_agregat",200,
		                0x100,2000,(FUNCPTR) driver_versement_balance_ciment,
		                0,0,0,0,0,0,0,0,0,0);
		balance_ciment_versement_en_cours = valeur;
	} else {
		printf("ERREUR, COMMANDE INCOMPRISE\n");
	}
}

void FermerBalance(char *balance){
	int valeur;
	printf("Fermeture balance : %s\n", balance);
	
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
	
}

void EteindreDiodePositionCamion(){
	
}

void AllumerDiodeMalaxeur(){
	
}

void EteindreDiodeMalaxeur(){
	
}

void consigne_moteur(float intensite){
	
}

int getPresence(){

}

int getVolume(){

}

int getDistance(){

}

int getTypeBeton(){

}

int getHygrometrie(){
	
}

float getVmot(){

}

float getImot(){

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


int driver_versement_silo_agregat(){
	int i;
	
	while (1){
		for (i = 0; i < sizeof(agregat_versement_en_cours); i += 1){
			if (agregat_versement_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				//Decremente contenu silo
				capacite_silo_agregat_courrante[i] -= 1;
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
			}
		}
	}
	
	return 0;
}
int driver_versement_silo_ciment(){
	int i;
	
	while (1){
		for (i = 0; i < sizeof(ciment_versement_en_cours); i += 1){
			if (ciment_versement_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				//Decremente contenu silo
				capacite_silo_ciment_courrante[i] -= 1;
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
			}
		}
	}
	
	return 0;
}
int driver_versement_silo_eau(){
	while (1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT);
		//Decremente contenu silo
		capacite_silo_eau_courrante -= 1;
		//Test silo vide, si oui envoie le signal du capteur silo vide
		if (capacite_silo_eau_courrante <= 0){
			capteur_vide_eau();
		}
	}
	
	return 0;
}
int driver_versement_malaxeur(){
	//TODO driver_versement_malaxeur()
	
	return 0;
}
int driver_remplissage_silo_agregat(){
	int i;
		
	while (1){
		for (i = 0; i < sizeof(agregat_remplissage_en_cours); i += 1){
			if (agregat_remplissage_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				//Decremente contenu silo
				capacite_silo_agregat_courrante[i] += 1;
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
			}
		}
	}
	
	return 0;
}
int driver_remplissage_silo_ciment(){
	int i;
		
	while (1){
		for (i = 0; i < sizeof(ciment_remplissage_en_cours); i += 1){
			if (ciment_remplissage_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				//Decremente contenu silo
				capacite_silo_ciment_courrante[i] += 1;
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
			}
		}
	}
	
	return 0;
}
int driver_remplissage_silo_eau(){
	while (1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT);
		
		//Decremente contenu silo
		capacite_silo_eau_courrante += 1;
		//Test silo vide, si oui envoie le signal du capteur silo vide
		if (capacite_silo_eau_courrante >= NIVEAU_EAU_MAX){
			capteur_plein_eau();
		}
	}
	
	return 0;
}

int driver_versement_balance_agregat(){
	while(1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT);
		
		//Simule une IT balance moins
		capteur_moins_balance_agregats();
	}
	
	return 0;
}

int driver_versement_balance_ciment(){
	while(1){
		taskDelay(ATTENTE_ENTRE_DEUX_INT);
		
		//Simule une IT balance moins
		capteur_moins_balance_ciment();
	}
	
	return 0;
}