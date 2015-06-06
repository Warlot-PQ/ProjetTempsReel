#include "signauxExterieur.h"
#include "cimenterie.h"
#include "taches.h"
#include <taskLib.h>
#include <string.h>
#include <wdLib.h>

#define INACTIF -1
#define ATTENTE_ENTRE_DEUX_INT 500

//int moteur_task_id;

int capacite_silo_agregat_courrante[3] = {0, 0, 0};
int capacite_silo_ciment_courrante[2] = {0, 0};
int capacite_silo_eau_courrante = 0;

//0 signifie inactif et le pid de la tache en cours sinon, l'index représente le numéro du silo
int agregat_versement_en_cours[3] = {INACTIF, INACTIF, INACTIF};
int agregat_remplissage_en_cours[3] = {INACTIF, INACTIF, INACTIF};
int ciment_versement_en_cours[2] = {INACTIF, INACTIF};
int ciment_remplissage_en_cours[2] = {INACTIF, INACTIF};
int eau_versement_en_cours = INACTIF;
int eau_remplissage_en_cours = INACTIF;
int malaxeur_versement_en_cours = INACTIF;

void OuvrirVanne(char* vanne){
	int valeur;
	printf("Ouverture vanne : %s\n", vanne);
	
	//Vannes bas
	if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_2) == 0
			|| strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
		//Simule le versement des agregats
		
		valeur = taskSpawn("driver_versement_agregat",200,
					                0x100,2000,(FUNCPTR) driver_versement_agregat,
					                0,0,0,0,0,0,0,0,0,0);
		if (strcmp(vanne, cst_vanne_bas_agregat_1) == 0){
			agregat_versement_en_cours[0] = valeur;
			
			printf("Semaphore ??\n");
			
			semGive(sem_fin_malaxeur);
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
						                0x100,2000,(FUNCPTR) driver_versement_ciment,
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
						                0x100,2000,(FUNCPTR) driver_versement_eau,
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
						                0x100,2000,(FUNCPTR) driver_remplissage_agregat,
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
							                0x100,2000,(FUNCPTR) driver_remplissage_ciment,
							                0,0,0,0,0,0,0,0,0,0);
			if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0){
				ciment_remplissage_en_cours[0] = valeur;
			} else if (strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
				ciment_remplissage_en_cours[1] = valeur;
			}
		} else if (strcmp(vanne, cst_vanne_haut_eau) == 0){
			//Simule le remplissage de l'eau
			eau_remplissage_en_cours = taskSpawn("driver_versement_eau",200,
									                0x100,2000,(FUNCPTR) driver_remplissage_eau,
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

void OuvrirBalance(){

}

void FermerBalance(){

}

void AllumerDiodePositionCamion(){
	diode_position_camion = 1;
	printf("\n********** diode_position_camion allumée *************\n");
}

void EteindreDiodePositionCamion(){
	diode_position_camion = 0;
	printf("\n********** diode_position_camion éteinte *************\n");
}

void AllumerDiodeMalaxeur(){
	
}

void EteindreDiodeMalaxeur(){
	
}

void consigne_moteur(int vitesse_voulue){
	int moteur_task_id;
	
	if(vitesse_voulue>0 && vitesse_voulue != vitesse_moteur){
		printf("\n consigne_moteur : taskSpawn \n");
		moteur_task_id = taskSpawn("driver_moteur",100, 0x100,2000,(FUNCPTR) driver_moteur, vitesse_voulue,0,0,0,0,0,0,0,0,0);
	}else{
		printf("\n vitesse_voulue = vitesse_moteur : driver non lancé \n");
	}
}

int getPresence(){
	if(timer_getPresence < 5){
		taskDelay(100);
		timer_getPresence = timer_getPresence + 1;
		printf("timer_getPresence : %d\n", timer_getPresence);
		return 0;
	}else{
		printf("timer_getPresence : %d\n", timer_getPresence);
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
	printf("vitesse_moteur : %d\n", vitesse);
	semGive(sem_vitesse_moteur);
	
	return vitesse;
}

float getImot(){
	float intensite;
	int vitesse;
	
	vitesse = getVmot();
	intensite = (float)(couple_moteur*vitesse)/tension_moteur;
	printf("intensite du moteur : %f\n", intensite);
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
	printf("driver_moteur\n");
	coefficient_directeur = (vitesse_voulue-vitesse_moteur)/5.0;
	while(1){
		
		while(vitesse_moteur != vitesse_voulue){
			printf("VITESSE VOULUE : %d\n\n", vitesse_voulue);
			taskDelay(100);
			semTake(sem_vitesse_moteur, WAIT_FOREVER);
			printf("driver_moteur : prise du jeton \n");
			if (vitesse_voulue > vitesse_moteur){
				vitesse_moteur = vitesse_moteur + coefficient_directeur;
			}
			
			if (vitesse_voulue < vitesse_moteur){
							vitesse_moteur = vitesse_moteur - coefficient_directeur;
			}
			semGive(sem_vitesse_moteur);
			printf("driver_moteur : vitesse moteur = %d \n", vitesse_moteur);
			printf("driver_moteur : vitesse voulue = %d \n", vitesse_voulue);
			printf("driver_moteur : rend le jeton \n");
		}
		
		if(vitesse_voulue == vitesse_moteur){
			printf("driver_moteur : taskDelete\n");
			taskDelete(taskIdSelf());
		}
	}
	return 0;
}

int driver_versement_agregat(){
	int i;
	
	while (1){
		for (i = 0; i < sizeof(agregat_versement_en_cours); i += 1){
			if (agregat_versement_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				
				printf("Silo agregat %d -1\n", i + 1);
				//Decremente contenu silo
				capacite_silo_agregat_courrante[i] -= 1;
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
int driver_versement_ciment(){
	int i;
	
	while (1){
		for (i = 0; i < sizeof(ciment_versement_en_cours); i += 1){
			if (ciment_versement_en_cours[i] != INACTIF){
				taskDelay(ATTENTE_ENTRE_DEUX_INT);
				
				printf("Silo agregat %d -1\n", i + 1);
				//Decremente contenu silo
				capacite_silo_ciment_courrante[i] -= 1;
				//Test silo vide, si oui envoie le signal du capteur silo vide
				if (capacite_silo_ciment_courrante[i] <= 0){
					switch(i){
					case 0:
						semGive(sem_int_min_cim_1);
						break;
					default:
						semGive(sem_int_min_cim_2);
					}
				}
			}
		}
	}
	
	return 0;
}
int driver_versement_eau(){
	
	return 0;
}
int driver_versement_malaxeur(){
	
	return 0;
}
int driver_remplissage_agregat(){
	
	return 0;
}
int driver_remplissage_ciment(){

	return 0;
}
int driver_remplissage_eau(){
	
	return 0;
}