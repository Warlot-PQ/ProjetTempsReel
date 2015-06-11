#include "cimenterie.h"
#include "accesTampons.h"
#include <string.h>

int ecrire_tampon_cmd_cmd_plus_recent_distance(float distance){
	return ecrire_tampon_cmd_cmd_plus_recent_X('D', distance);
}
int ecrire_tampon_cmd_cmd_plus_recent_volume(float volume){
	return ecrire_tampon_cmd_cmd_plus_recent_X('V', volume);
}
int ecrire_tampon_cmd_cmd_plus_recent_beton(float beton){
	return ecrire_tampon_cmd_cmd_plus_recent_X('B', beton);
}

LOCAL int ecrire_tampon_cmd_cmd_plus_recent_X(char X, float value){
	int offset_tampon_X = 0, index_cmd_plus_recente = 0;
	
	if (value < 0){
		return PB;
	}
	
	index_cmd_plus_recente = lire_tampon_fonct_calcul_cmd_plus_recente();
	
	switch(X){
	case 'D':
		offset_tampon_X = index_tampon_cmd_distance;
		break;
	case 'V':
		offset_tampon_X = index_tampon_cmd_volume;
		break;
	default:	//case 'B'
		offset_tampon_X = index_tampon_cmd_beton;
	}
	
	semTake(sem_exl_tampon_cmd, WAIT_FOREVER);
	tampon_cmd[index_cmd_plus_recente * 3 + offset_tampon_X] = value;
	semGive(sem_exl_tampon_cmd);
	
	return 0;
}

int efface_commande_traitee(){
	int index_cmd_en_cours;
	
	index_cmd_en_cours = lire_tampon_fonct_calcul_cmd_en_cours();
	
	semTake(sem_exl_tampon_cmd, WAIT_FOREVER);
	tampon_cmd[index_cmd_en_cours * 3 + index_tampon_cmd_beton] = 0;
	tampon_cmd[index_cmd_en_cours * 3 + index_tampon_cmd_distance] = 0;
	tampon_cmd[index_cmd_en_cours * 3 + index_tampon_cmd_volume] = 0;
	semGive(sem_exl_tampon_cmd);
	
	return 0;
}

int lire_tampon_cmd_cmd_agregat_en_cours_beton(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('a', 'B');
}
float lire_tampon_cmd_cmd_agregat_en_cours_volume(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('a', 'V');
}
float lire_tampon_cmd_cmd_agregat_en_cours_distance(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('a', 'D');
}
int lire_tampon_cmd_cmd_ciment_en_cours_beton(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('c', 'B');
}
float lire_tampon_cmd_cmd_ciment_en_cours_volume(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('c', 'V');
}
float lire_tampon_cmd_cmd_ciment_en_cours_distance(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('c', 'D');
}
int lire_tampon_cmd_cmd_eau_en_cours_beton(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('e', 'B');
}
float lire_tampon_cmd_cmd_eau_en_cours_volume(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('e', 'V');
}
float lire_tampon_cmd_cmd_eau_en_cours_distance(){
	return lire_tampon_cmd_cmd_Y_en_cours_X('e', 'D');
}

LOCAL float lire_tampon_cmd_cmd_Y_en_cours_X(char Y, char X){
	float value = 0;
	int offset_tampon_X = 0, offset_tampon_Y = 0;
	
	if (value < 0){
		return PB;
	}

	switch(Y){
	case 'e':
		offset_tampon_Y = lire_tampon_fonct_calcul_cmd_eau();
		break;
	case 'a':
		offset_tampon_Y = lire_tampon_fonct_calcul_cmd_agregat();
		break;
	default:	//case 'c'
		offset_tampon_Y = lire_tampon_fonct_calcul_cmd_ciment();
	}
	switch(X){
	case 'D':
		offset_tampon_X = index_tampon_cmd_distance;
		break;
	case 'V':
		offset_tampon_X = index_tampon_cmd_volume;
		break;
	default:	//case 'B'
		offset_tampon_X = index_tampon_cmd_beton;
	}
	
	semTake(sem_exl_tampon_cmd, WAIT_FOREVER);
	value = tampon_cmd[offset_tampon_Y * 3 + offset_tampon_X];
	semGive(sem_exl_tampon_cmd);
	
	return value;
}

//---------------- fonctions d'accès à tampon_qte_silos
int ecrire_tampon_qte_silos_eau(float qte){
	return acces_tampon_qte_silos_X_action('e', 0, 'w', qte);
}
int decremente_tampon_qte_silos_eau(){
	return acces_tampon_qte_silos_X_action('e', 0, 'd', 0);
}
float lire_tampon_qte_silos_eau(){
	return acces_tampon_qte_silos_X_action('e', 0, 'r', 0);
}
int ecrire_tampon_qte_silos_agregat(int numero_silo, float qte){
	return acces_tampon_qte_silos_X_action('a', numero_silo, 'w', qte);
}
int decremente_tampon_qte_silos_agregat(int numero_silo){
	return acces_tampon_qte_silos_X_action('a', numero_silo, 'd', 0);
}
float lire_tampon_qte_silos_agregat(int numero_silo){
	return acces_tampon_qte_silos_X_action('a', numero_silo, 'r', 0);
}
int ecrire_tampon_qte_silos_ciment(int numero_silo, float qte){
	return acces_tampon_qte_silos_X_action('c', numero_silo, 'w', qte);
}
int decremente_tampon_qte_silos_ciment(int numero_silo){
	return acces_tampon_qte_silos_X_action('c', numero_silo, 'd', 0);
}
float lire_tampon_qte_silos_ciment(int numero_silo){
	return acces_tampon_qte_silos_X_action('c', numero_silo, 'r', 0);
}
int is_tampon_qte_silos_eau_nulle(){
	return acces_tampon_qte_silos_X_action('e', 0, 't', 0);
}
int is_tampon_qte_silos_agregat_nulle(int numero_silo){
	return acces_tampon_qte_silos_X_action('a', numero_silo, 't', 0);
}
int is_tampon_qte_silos_ciment_nulle(int numero_silo){
	return acces_tampon_qte_silos_X_action('c', numero_silo, 't', 0);
}

LOCAL float acces_tampon_qte_silos_X_action(char X, int numero_silo, char action, float qte){
	float *valueAdr;
		
	if (numero_silo < 0 || numero_silo > 3){
		return PB;
	}
	
	semTake(sem_exl_tampon_qte_silos, WAIT_FOREVER);
	if (X == 'a') {
		switch(numero_silo){
		case 1:
			valueAdr = &tampon_qte_silos[index_tampon_qte_silos_agregat_1];
			break;
		case 2:
			valueAdr = &tampon_qte_silos[index_tampon_qte_silos_agregat_2];
			break;
		default:
			valueAdr = &tampon_qte_silos[index_tampon_qte_silos_agregat_3];
		}
	} else if (X == 'c'){
		switch(numero_silo){
		case 1:
			valueAdr = &tampon_qte_silos[index_tampon_qte_silos_ciment_1];
			break;
		default:
			valueAdr = &tampon_qte_silos[index_tampon_qte_silos_ciment_2];
		}
	} else {	//X == 'e'
		valueAdr = &tampon_qte_silos[index_tampon_qte_silos_eau];
	}
	semGive(sem_exl_tampon_qte_silos);
	
	if (action == 'w'){
		*valueAdr = qte;
		return 0;
	} else if (action == 'd'){
		*valueAdr -= 1;
		return 0;
	} else if(action == 't'){
		return (*valueAdr <= 0) ? 1 : 0;
	} else { //action == 'r'
		return *valueAdr;
	}
}

//---------------- fonctions d'accès à tampon_fonct_calcul
int incremente_tampon_fonct_calcul_cmd_plus_recente(){
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente] += 1;
	semGive(sem_exl_tampon_fonct_calcul);
			
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_en_cours(){
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours] += 1;
	semGive(sem_exl_tampon_fonct_calcul);
	
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_eau(){
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_eau_en_cours] += 1;
	
	semGive(sem_exl_tampon_fonct_calcul);
	
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_agregat(){
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_agregat_en_cours] += 1;
	semGive(sem_exl_tampon_fonct_calcul);
	
	return 0;
}
int incremente_tampon_fonct_calcul_cmd_ciment(){
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_ciment_en_cours] += 1;
	semGive(sem_exl_tampon_fonct_calcul);
	
	return 0;
}
int lire_tampon_fonct_calcul_cmd_plus_recente(){
	int value;

	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente];
	semGive(sem_exl_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_en_cours(){
	int value;

	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours];
	semGive(sem_exl_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_eau(){
	int value;

	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_eau_en_cours];
	semGive(sem_exl_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_agregat(){
	int value;

	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_agregat_en_cours];
	semGive(sem_exl_tampon_fonct_calcul);
	
	return value;
}
int lire_tampon_fonct_calcul_cmd_ciment(){
	int value;

	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	value = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_ciment_en_cours];
	semGive(sem_exl_tampon_fonct_calcul);
	
	return value;
}

int tampon_fonct_calcul_plein(){
	int value;
	int cmd_plus_recente, cmd_en_cours;
	
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	cmd_plus_recente = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente];
	cmd_en_cours = tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours];
	semGive(sem_exl_tampon_fonct_calcul);
	
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
	
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	if (tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours] == -1){
		value = 0;
	} else {
		value = PB;
	}
	semGive(sem_exl_tampon_fonct_calcul);
	
	return value;
}

int set_tampon_fonct_calcul_premiere_cmd(){
	semTake(sem_exl_tampon_fonct_calcul, WAIT_FOREVER);
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours] = 0;
	semGive(sem_exl_tampon_fonct_calcul);
	
	return 0;
}

void set_versement_eau_possible(int value){
	if (value != 0 && value != 1){
		value = 0;
	}
	
	semTake(sem_exl_versement_eau_possible, WAIT_FOREVER);
	versement_eau_possible = value;
	semGive(sem_exl_versement_eau_possible);
}
int is_versement_eau_possible(){
	int value = 0;
		
	semTake(sem_exl_versement_eau_possible, WAIT_FOREVER);
	if (versement_eau_possible == 1){
		value = 1;
	} else {
		value = 0;
	}
	semGive(sem_exl_versement_eau_possible);
	
	return value;
}
int ajouter_message_affichage(char message[TAILLE_MESSAGE_AFFICHAGE]){
	if (message_plus_recent == 10){
		vider_messages_affichage();
	}
	
	strncpy(buffer_affichage[message_plus_recent], message, sizeof buffer_affichage[message_plus_recent]);
	message_plus_recent += 1;
	
	return 0;
	
}
int vider_messages_affichage(){
	int index;
	
	for (index = 0; index < MAX_MESSAGE_AFFICHAGE; index += 1){
		strncpy(buffer_affichage[index], "", sizeof buffer_affichage[index]);
	}
	message_plus_recent = 0;
	
	return 0;
}
char *get_message_affichage(int index_message){
	return buffer_affichage[index_message];
}
int ajouter_message_affichage_persistant(char message[TAILLE_MESSAGE_AFFICHAGE]){
	strncpy(message_affichage_persistant, message, sizeof message_affichage_persistant);
		
	return 0;
}
char *get_message_affichage_persistant(){
	return message_affichage_persistant;
}