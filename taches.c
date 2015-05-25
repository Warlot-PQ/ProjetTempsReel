#include "cimenterie.h"
#include "accesTampons.h"
#include "taches.h"

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
	float B, V, D, agregat_1, agregat_2, agregat_3;
	
//----------------Lecture des valeurs B, V, D dans le tampon_cmd
	B = lire_tampon_cmd_cmd_plus_recent_beton();
	V = lire_tampon_cmd_cmd_plus_recent_volume();
	D = lire_tampon_cmd_cmd_plus_recent_distance();

//----------------Calcul des quantités d'agrégats voulu selon la valeur de B
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
	ecrire_tampon_qte_silos_agregat(index_tampon_qte_silos_agregat_1, agregat_1);
	ecrire_tampon_qte_silos_agregat(index_tampon_qte_silos_agregat_2, agregat_2);
	ecrire_tampon_qte_silos_agregat(index_tampon_qte_silos_agregat_3, agregat_3);
	
//----------------Signale la tache "gestion remplissage et versement silos" que le tampon_qte a été mis à jour
	//TODO gestionRemplissageEtVersementSilos!d_agregat
	
	return 0;
}
int calcul_qte_ciment(){
	float B, V, D, ciment_1, ciment_2;
		
	//----------------Lecture des valeurs B, V, D dans le tampon_cmd
		B = lire_tampon_cmd_cmd_plus_recent_beton();
		V = lire_tampon_cmd_cmd_plus_recent_volume();
		D = lire_tampon_cmd_cmd_plus_recent_distance();

	//----------------Calcul des quantités d'agrégats voulu selon la valeur de B
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
		ecrire_tampon_qte_silos_ciment(index_tampon_qte_silos_ciment_1, ciment_1);
		ecrire_tampon_qte_silos_ciment(index_tampon_qte_silos_ciment_2, ciment_2);
		
	//----------------Signale la tache "gestion remplissage et versement silos" que le tampon_qte a été mis à jour
		//TODO gestionRemplissageEtVersementSilos!d_ciment
		
	return 0;
}

int versement_agregat(int numero_silo){
	
	return 0;
}
int remplissage_agregat_1(){
	
	return 0;
}
int remplissage_agregat_2(){
	
	return 0;
}
int remplissage_agregat_3(){
	
	return 0;
}

int versement_ciment(int numero_silo){
	
	return 0;
}
int remplissage_ciment_1(){
	
	return 0;
}
int remplissage_ciment_2(){
	
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