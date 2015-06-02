#include "cimenterie.h"
#include "accesTampons.h"

int ecrire_tampon_cmd_cmd_plus_recent_distance(float distance){
	int index_cmd_plus_recente;
	
	if (distance < 0){
		return PB;
	}
	
	index_cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();
	
	semTake(sem_tampon_cmd, WAIT_FOREVER);
	tampon_cmd[index_cmd_plus_recente + index_tampon_cmd_distance] = distance;
	semGive(sem_tampon_cmd);
	
	return 0;
}
int ecrire_tampon_cmd_cmd_plus_recent_volume(float volume){
	int index_cmd_plus_recente;
		
	if (volume < 0){
		return PB;
	}
	
	index_cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();

	semTake(sem_tampon_cmd, WAIT_FOREVER);
	tampon_cmd[index_cmd_plus_recente + index_tampon_cmd_volume] = volume;
	semGive(sem_tampon_cmd);
		    
	return 0;
}
int ecrire_tampon_cmd_cmd_plus_recent_beton(float beton){
	int index_cmd_plus_recente;
	
	if (beton < 0){
		return PB;
	}
	
	index_cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();

	semTake(sem_tampon_cmd, WAIT_FOREVER);
	tampon_cmd[index_cmd_plus_recente + index_tampon_cmd_beton] = beton;
	semGive(sem_tampon_cmd);
		    
	return 0;
}
int efface_commande_traitee(){
	int index_cmd_en_cours;
	
	index_cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
	
	semTake(sem_tampon_cmd, WAIT_FOREVER);
	tampon_cmd[index_cmd_en_cours + index_tampon_cmd_beton] = 0;
	tampon_cmd[index_cmd_en_cours + index_tampon_fonct_calcul_cmd_agregat_en_cours] = 0;
	tampon_cmd[index_cmd_en_cours + index_tampon_fonct_calcul_cmd_ciment_en_cours] = 0;
	semGive(sem_tampon_cmd);
	
	return 0;
}
float lire_tampon_cmd_cmd_plus_recent_distance(){
	int index_cmd_plus_recente;
	float value;
	
	index_cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();

	semTake(sem_tampon_cmd, WAIT_FOREVER);
	value = tampon_cmd[index_cmd_plus_recente + index_tampon_cmd_distance];
	semGive(sem_tampon_cmd);
	
	return value;
}
float lire_tampon_cmd_cmd_plus_recent_volume(){
	int index_cmd_plus_recente;
	float value;
	
	index_cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();

	semTake(sem_tampon_cmd, WAIT_FOREVER);
	value = tampon_cmd[index_cmd_plus_recente + index_tampon_cmd_volume];
	semGive(sem_tampon_cmd);
	
	return value;
}
float lire_tampon_cmd_cmd_plus_recent_beton(){
	int index_cmd_plus_recente;
	float value;
	
	index_cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();

	semTake(sem_tampon_cmd, WAIT_FOREVER);
	value = tampon_cmd[index_cmd_plus_recente + index_tampon_cmd_beton];
	semGive(sem_tampon_cmd);
	
	return value;
}

//---------------- fonctions d'accès à tampon_qte_silos
int ecrire_tampon_qte_silos_eau(float qte){
	if (qte < 0){
		return PB;
	}
	
	semTake(sem_tampon_qte_silos, WAIT_FOREVER);
	tampon_qte_silos[index_tampon_qte_silos_eau] = qte;
	semGive(sem_tampon_qte_silos);
	
	return 0;
}
int ecrire_tampon_qte_silos_agregat(int numero_silo, float qte){
	if (numero_silo < 0 || numero_silo > 3 || qte < 0){
		return PB;
	}
	
	semTake(sem_tampon_qte_silos, WAIT_FOREVER);
	switch(numero_silo){
	case 1:
		tampon_qte_silos[index_tampon_qte_silos_agregat_1] = qte;
		break;
	case 2:
		tampon_qte_silos[index_tampon_qte_silos_agregat_2] = qte;
		break;
	default:
		tampon_qte_silos[index_tampon_qte_silos_agregat_3] = qte;
	}
	semGive(sem_tampon_qte_silos);
	
	return 0;
}
int ecrire_tampon_qte_silos_ciment(int numero_silo, float qte){
	if (numero_silo < 0 || numero_silo > 2 || qte < 0){
		return PB;
	}
	
	semTake(sem_tampon_qte_silos, WAIT_FOREVER);
	switch(numero_silo){
	case 1:
		tampon_qte_silos[index_tampon_qte_silos_ciment_1] = qte;
		break;
	default:
		tampon_qte_silos[index_tampon_qte_silos_ciment_2] = qte;
	}
	semGive(sem_tampon_qte_silos);
	
	return 0;
}
float lire_tampon_qte_silos_eau(){
	int value;
	
	semTake(sem_tampon_qte_silos, WAIT_FOREVER);
	value = tampon_qte_silos[index_tampon_qte_silos_eau];
	semGive(sem_tampon_qte_silos);
	
	return value;
}
float lire_tampon_qte_silos_agregat(int numero_silo){
	int value;
	
	if (numero_silo < 0 || numero_silo > 3){
		return PB;
	}
	
	semTake(sem_tampon_qte_silos, WAIT_FOREVER);
	switch(numero_silo){
	case 1:
		value = tampon_qte_silos[index_tampon_qte_silos_agregat_1];
		break;
	case 2:
		value = tampon_qte_silos[index_tampon_qte_silos_agregat_2];
		break;
	default:
		value = tampon_qte_silos[index_tampon_qte_silos_agregat_3];
	}
	semGive(sem_tampon_qte_silos);
	
	return value;
}
float lire_tampon_qte_silos_ciment(int numero_silo){
	int value;
	
	if (numero_silo < 0 || numero_silo > 2){
		return PB;
	}
	
	semTake(sem_tampon_qte_silos, WAIT_FOREVER);
	switch(numero_silo){
	case 1:
		value = tampon_qte_silos[index_tampon_qte_silos_ciment_1];
		break;
	default:
		value = tampon_qte_silos[index_tampon_qte_silos_ciment_2];
	}
	semGive(sem_tampon_qte_silos);
	
	return value;
}

//---------------- fonctions d'accès à tampon_fonct_calcul
int incremente_tampon_fonct_calcul_cmd_plus_recente(){
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente] += 1;
	semGive(sem_tampon_fonct_calcul);
			
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_en_cours(){
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours] += 1;
	semGive(sem_tampon_fonct_calcul);
	
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_eau(){
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_eau_en_cours] += 1;
	semGive(sem_tampon_fonct_calcul);
	
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_agregat(){
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_agregat_en_cours] += 1;
	semGive(sem_tampon_fonct_calcul);
	
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_ciment(){
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_ciment_en_cours] += 1;
	semGive(sem_tampon_fonct_calcul);
	
	return 0;
}
int lire_tampon_fonct_calcul_cmd_plus_recente(){
	int value;

	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente];
	semGive(sem_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_en_cours(){
	int value;

	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours];
	semGive(sem_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_eau(){
	int value;

	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_eau_en_cours];
	semGive(sem_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_agregat(){
	int value;

	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_agregat_en_cours];
	semGive(sem_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_ciment(){
	int value;

	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_ciment_en_cours];
	semGive(sem_tampon_fonct_calcul);
	
	return value;
}

int tampon_fonct_calcul_plein(){
	int value;
	int cmd_plus_recente, cmd_en_cours;
	
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	cmd_plus_recente = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente];
	cmd_en_cours = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours];
	semGive(sem_tampon_fonct_calcul);
	
	//Test tampon plein
	if (cmd_plus_recente + 1 == cmd_en_cours){
		value = PB;
	} else {
		value = 0;
	}
	
	return value;
}

int is_tampon_fonct_calcul_premiere_cmd(){
	int value;
	
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	if (tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente] == -1){
		value = 0;
	} else {
		value = PB;
	}
	semGive(sem_tampon_fonct_calcul);
	
	return value;
}

int set_tampon_fonct_calcul_premiere_cmd(){
	semTake(sem_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours] = 0;
	semGive(sem_tampon_fonct_calcul);
	
	return 0;
}

int ecrire_niveau_eau_nul(){
	semTake(sem_niveau_eau, WAIT_FOREVER);
	niveau_eau = 0;
	semGive(sem_niveau_eau);
	
	return 0;
}

int ecrire_niveau_eau_max(){
	semTake(sem_niveau_eau, WAIT_FOREVER);
	niveau_eau = NIVEAU_EAU_MAX;
	semGive(sem_niveau_eau);
	
	return 0;
}

int incremente_niveau_eau(){
	semTake(sem_niveau_eau, WAIT_FOREVER);
	niveau_eau += 1;
	semGive(sem_niveau_eau);
	
	return 0;
}

int decremente_niveau_eau(){
	semTake(sem_niveau_eau, WAIT_FOREVER);
	niveau_eau -= 1;
	semGive(sem_niveau_eau);
	
	return 0;
}

int ecrire_quantite_eau_restante(float valeur){
	semTake(sem_quantite_eau_restante, WAIT_FOREVER);
	quantite_eau_restante = valeur;
	semGive(sem_quantite_eau_restante);
	
	return 0;
}

int decremente_quantite_eau_restante(){
	semTake(sem_quantite_eau_restante, WAIT_FOREVER);
	quantite_eau_restante -= 1;
	semGive(sem_quantite_eau_restante);
	
	return 0;
}

int is_quantite_eau_restante_nulle(){
	int value = 0;
	
	semTake(sem_quantite_eau_restante, WAIT_FOREVER);
	if (quantite_eau_restante <= 0) {
		value = 1;
	}
	semGive(sem_quantite_eau_restante);
	
	return value;
}

int ecrire_quantite_agregat_restante(float valeur){
	semTake(sem_quantite_agregat_restante, WAIT_FOREVER);
	quantite_agregat_restante = valeur;
	semGive(sem_quantite_agregat_restante);
	
	return 0;
}
int decremente_quantite_agregat_restante(){
	semTake(sem_quantite_agregat_restante, WAIT_FOREVER);
	quantite_agregat_restante -= 1;
	semGive(sem_quantite_agregat_restante);
	
	return 0;
}
int is_quantite_agregat_restante_nulle(){
	int value = 0;
		
	semTake(sem_quantite_agregat_restante, WAIT_FOREVER);
	if (quantite_agregat_restante <= 0) {
		value = 1;
	}
	semGive(sem_quantite_agregat_restante);
	
	return value;
}

int ecrire_quantite_agregat_totale_nulle(){
	semTake(sem_quantite_agregat_totale, WAIT_FOREVER);
	quantite_agregat_totale = 0;
	semGive(sem_quantite_agregat_totale);
	
	return 0;
}
int ajouter_quantite_agregat_totale(float valeur){
	semTake(sem_quantite_agregat_totale, WAIT_FOREVER);
	quantite_agregat_totale = valeur;
	semGive(sem_quantite_agregat_totale);
	
	return 0;
}
int decremente_quantite_agregat_totale(){
	semTake(sem_quantite_agregat_totale, WAIT_FOREVER);
	quantite_agregat_totale -= 1;
	semGive(sem_quantite_agregat_totale);
	
	return 0;
}
int is_quantite_agregat_totale_nulle(){
	int value = 0;
		
	semTake(sem_quantite_agregat_totale, WAIT_FOREVER);
	if (quantite_agregat_totale <= 0){
		value = 1;
	}
	semGive(sem_quantite_agregat_totale);
	
	return value;
}

int ecrire_quantite_ciment_restante(float valeur){
	semTake(sem_quantite_ciment_restante, WAIT_FOREVER);
	quantite_ciment_restante = valeur;
	semGive(sem_quantite_ciment_restante);
	
	return 0;
	
}
int decremente_quantite_ciment_restante(){
	semTake(sem_quantite_ciment_restante, WAIT_FOREVER);
	quantite_ciment_restante -= 1;
	semGive(sem_quantite_ciment_restante);
	
	return 0;
};
int is_quantite_ciment_restant_nulle(){
	int value = 0;
		
	semTake(sem_quantite_ciment_restante, WAIT_FOREVER);
	if (quantite_ciment_restante <= 0) {
		value = 1;
	}
	semGive(sem_quantite_ciment_restante);
	
	return value;
}

int ecrire_quantite_ciment_totale_nulle(){
	semTake(sem_quantite_ciment_totale, WAIT_FOREVER);
	quantite_ciment_totale = 0;
	semGive(sem_quantite_ciment_totale);
	
	return 0;
}
int ajouter_quantite_ciment_totale(float valeur){
	semTake(sem_quantite_ciment_totale, WAIT_FOREVER);
	quantite_ciment_totale = valeur;
	semGive(sem_quantite_ciment_totale);
	
	return 0;
}
int decremente_quantite_ciment_totale(){
	semTake(sem_quantite_ciment_totale, WAIT_FOREVER);
	quantite_ciment_totale -= 1;
	semGive(sem_quantite_ciment_totale);
	
	return 0;
}
int is_quantite_ciment_totale_nulle(){
	int value = 0;
		
	semTake(sem_quantite_ciment_totale, WAIT_FOREVER);
	if (quantite_ciment_totale <= 0){
		value = 1;
	}
	semGive(sem_quantite_ciment_totale);
	
	return value;
}

void set_versement_eau_possible(int value){
	if (value != 0 && value != 1){
		value = 0;
	}
	
	semTake(sem_versement_eau_possible, WAIT_FOREVER);
	versement_eau_possible = value;
	semGive(sem_versement_eau_possible);
}
int is_versement_eau_possible(){
	int value = 0;
		
	semTake(sem_versement_eau_possible, WAIT_FOREVER);
	if (versement_eau_possible == 1){
		value = 1;
	} else {
		value = 0;
	}
	semGive(sem_versement_eau_possible);
	
	return value;
}