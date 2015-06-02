#include "signauxExterieur.h"
#include "cimenterie.h"
#include "taches.h"

int[] capacite_silo_agregat_courrante = {0, 0, 0};
int[] capacite_silo_ciment_courrante = {0, 0};
int[] capacite_silo_eau_courrante = {0};

//0 signifie inactif et le pid de la tache en cours sinon, l'index représente le numéro du silo
int[] agregat_versement_en_cours = {0, 0, 0};
int[] ciment_versement_en_cours = {0, 0};
int[] agregat_remplissage_en_cours = {0, 0, 0};
int[] ciment_remplissage_en_cours = {0, 0};

void OuvrirVanne(char* vanne){
	int valeur;
}
	printf("Ouverture vanne : %s", vanne);
	
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
		} else if (strcmp(vanne, cst_vanne_bas_agregat_2) == 0){
			agregat_versement_en_cours[1] = valeur;
		} else if (strcmp(vanne, cst_vanne_bas_agregat_3) == 0){
			agregat_versement_en_cours[2] = valeur;
		}
	} else if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0
					|| strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
		//Simule le versement du ciment
		valeur = taskSpawn("driver_versement_ciment",200,
						                0x100,2000,(FUNCPTR) driver_versement_ciment,
						                0,0,0,0,0,0,0,0,0,0);
		if (strcmp(vanne, cst_vanne_bas_ciment_1) == 0){
			ciment_versement_en_cours[0] = valeur;
		} else if (strcmp(vanne, cst_vanne_bas_ciment_2) == 0){
			ciment_versement_en_cours[1] = valeur;
		}
	else if (strcmp(vanne, cst_vanne_bas_eau) == 0){
		//Simule le versement de l'eau
		taskSpawn("driver_versement_eau",200,
						                0x100,2000,(FUNCPTR) driver_versement_eau,
						                0,0,0,0,0,0,0,0,0,0);
	} else if (strcmp(vanne, cst_vanne_malaxeur) == 0) {
		//Simule le versement du malaxeur
		
	} else {
		//Vannes haut
		if (strcmp(vanne, cst_vanne_haut_agregat_1) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_2) == 0
				|| strcmp(vanne, cst_vanne_haut_agregat_3) == 0){
			//Simule le remplissage des agregats
			
		} else if (strcmp(vanne, cst_vanne_haut_ciment_1) == 0
				|| strcmp(vanne, cst_vanne_haut_ciment_2) == 0){
			//Simule le remplissage du ciment
			
		} else if (strcmp(vanne, cst_vanne_haut_eau) == 0){
			//Simule le remplissage de l'eau
			
		} else {
			
		}
	}
}

void FermerVanne(char* vanne){
	
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

int getVmot(){

}

int getImot(){

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




int driver_versement_agregat(){
	
	return 0;
}

int driver_versement_ciment(){

	return 0;
}

int driver_versement_eau(){
	
	return 0;
}
