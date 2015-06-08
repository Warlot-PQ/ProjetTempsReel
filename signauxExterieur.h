//#ifndef SIGNAUX_EXTERIEUR_H
//#define SIGNAUX_EXTERIEUR_H
#include <semLib.h>

//----------------Emission
#define cst_vanne_haut_agregat_1 "VA1.1"
#define cst_vanne_bas_agregat_1 "VA1.2"
#define cst_vanne_haut_agregat_2 "VA2.1"
#define cst_vanne_bas_agregat_2 "VA2.2"
#define cst_vanne_haut_agregat_3 "VA3.1"
#define cst_vanne_bas_agregat_3 "VA3.2"
#define cst_vanne_haut_ciment_1 "VC1.1"
#define cst_vanne_bas_ciment_1 "VC1.2"
#define cst_vanne_haut_ciment_2 "VC2.1"
#define cst_vanne_bas_ciment_2 "VC2.2"
#define cst_vanne_malaxeur "VM"
#define cst_vanne_haut_eau "VE1"
#define cst_vanne_bas_eau "VE2"

#define cst_tapis_agregat "TPA"
#define cst_tapis_ciment "TPC"

#define cst_balance_agregat "BA"
#define cst_balance_ciment "BC"

#define cst_silo_agregat_1 "A1"
#define cst_silo_agregat_2 "A2"
#define cst_silo_agregat_3 "A3"
#define cst_silo_ciment_1 "C1"
#define cst_silo_ciment_2 "C2"
#define cst_silo_eau "E"
#define cst_malaxeur "M"

//----------------Constantes pour le moteur
#define cste_Imax											15.0
#define cste_vitesse_moteur_max								10
#define couple_moteur										50
#define tension_moteur										100

//----------------Constantes pour l'hygronométrie
#define k_hygronometrie										0.5
#define HYGROMETRIE											38	

int vitesse_moteur;

//----------------Diodes
int diode_position_camion;
int diode_malaxeur;

//----------------getPresence
int timer_getPresence;

//----------------driver_versement_malaxeur
int timer_versement_malaxeur;

#define INACTIF -1
#define ACTIF 0
#define ATTENTE_ENTRE_DEUX_INT		100
#define UNITE_VOLUME_REMPLISSAGE	50
#define UNITE_VOLUME_VERSEMENT		1

int capacite_silo_agregat_courrante[3] = {0, 0, 0};
int capacite_silo_ciment_courrante[2] = {0, 0};
int capacite_silo_eau_courrante = 0;
int capacite_malaxeur_courrante = 0;

SEM_ID sem_capacite_silo_agregat_courrante;
SEM_ID sem_capacite_silo_ciment_courrante;
SEM_ID sem_capacite_silo_eau_courrante;
SEM_ID sem_capacite_malaxeur;
SEM_ID sem_vitesse_moteur;


/*
 * Utilisation des signaux, signalInit(...) au debut de chaque tache
*/

/****************************************/
/*************ACTIONNEURS****************/
/****************************************/
/**
*	Ouvre une vanne VEX.Z ou VE1.1
*	vanne : Constante de la vanne, utiliser les defines du .h
**/
void OuvrirVanne(char* vanne);
/**
*	Ferme une vanne VEX.Y ou VE1
*	vanne : Constante de la vanne, utiliser les defines du .h
**/
void FermerVanne(char* vanne);
/**	
*	Ouvre la vanne du bas du silo d'eau (VE2)
*	vanne : Constante, utiliser les defines du .h
*	ouverture : Pourcentage d'ouverture, entre 0 et 100
**/
void OuvrirRobinet(char *vanne, int ouverture);
/**
*	Demmarre un tapis TPA ou TPC
*	tapis : Constante du tapis, utiliser les defines du .h
**/
void DemarrageTapis(char *tapis);
/**
*	Arrete un tapis TPA ou TPC
*	tapis : Constante du tapis, utiliser les defines du .h
**/
void ArretTapis(char *tapis);
/**
*	Fixe la tension du moteur du malaxeur
*	tension : pourcentage de la tension, entre 0 et 100
**/
void CommandeMalaxeur(int tension);
/**
*	Ouvre une balance BA ou BC
*	vanne : Constante de la balance, utiliser les defines du .h
**/
void OuvrirBalance(char *balance);
/**
*	Ferme une balance BA ou BC
*	vanne : Constante de la balance, utiliser les defines du .h
**/
void FermerBalance(char *balance);
/**
 *  Allume la diode signalant que le malaxeur passe en phase de versement et que le camion doit se positionner.
 *  Est appelée quand le camion n'est pas en position
**/
void AllumerDiodePositionCamion();
/**
 *  Eteint la diode signalant que le malaxeur passe en phase de versement et que le camion doit se positionner.
 *  Est appelée quand le camion est en position
**/
void EteindreDiodePositionCamion();
/**
 * 	Allume la diode du malaxeur quand le seuil d'intensité Imax du moteur est atteint
**/
void AllumerDiodeMalaxeur();
/**
 * 	Eteint la diode du malaxeur quand l'intensité du moteur passe sous le seuil Imax
**/
void EteindreDiodeMalaxeur();
/**
 * 	Envoie la consigne de vitesse au moteur
**/
void consigne_moteur(int);
/****************************************/
/***************CAPTEURS*****************/
/****************************************/
/**
*	Indique si le camion est en place
*	return : 1 si oui, 0 sinon
**/
int getPresence();
/****************************************/
/***************DONNEES******************/
/****************************************/
/**
*	Récupère le volume de ciment
*	return : entier
**/
int getVolume();

int getDistance();

int getTypeBeton();

int getHygrometrie();

int getVmot();

float getImot();

int getEtatBmal();
/****************************************/
/*************Interruption***************/
/****************************************/
/**
*	Signal que l'element est vide : A1, A2, A3, C1, C2, E, M
*	element : constante de l'element, utiliser les defines du .h
**/
void interruptionMin(char* element);
/**
*	Signal que l'element est plein : A1, A2, A3, C1, C2, E, M
*	element : constante de l'element, utiliser les defines du .h
**/
void interruptionMax(char* element);
/**
*	Signal que l'element a perdu 1 unité : BA, BC, E
*	element : constante de l'element, utiliser les defines du .h
**/
void interruptionPlus(char* element);
/**
*	Signal que l'element a gagné 1 unité : BA, BC, E
*	element : constante de l'element, utiliser les defines du .h
**/
void interruptionMoins(char* element);

/****************************************/
/****************Taches******************/
/****************************************/
int driver_versement_silo_agregat();
int driver_versement_silo_ciment();
int driver_versement_silo_eau();
int driver_versement_malaxeur();

int driver_moteur(int vitesse_voulue);

int driver_remplissage_silo_agregat();
int driver_remplissage_silo_ciment();
int driver_remplissage_silo_eau();
int driver_versement_balance_agregat();
int driver_versement_balance_ciment();
//----------------Affichage du système dans la console
int driver_affichage_test();
int longueur_entier(int);
void affiche_silo(int[], int[], int[], int[], char);
//#endif