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

#define INACTIF 											-1
#define ACTIF												0
#define ATTENTE_ENTRE_DEUX_INT								100
#define TAUX_RAFFRAICHISSEMENT								50
#define UNITE_VOLUME_REMPLISSAGE							2
#define UNITE_VOLUME_VERSEMENT								1

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
*	Fixe la vitesse du moteur du malaxeur
*	vitesse : pourcentage entre 0 et 100
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
 * getHygrometrie : fonction random entre 1 et 100
 * @return rand()%100
 **/
int getHygrometrie();
/**
 * getVMot : retourne la vitesse actuelle du moteur (ressource critique protégée par un sémaphore d'exclusion 
 * mutuelle)
 * @return vitesse_moteur
 **/
int getVmot();

/**
 * getVMot : retourne l'intensité absorbée par le moteur calcultée en fonction du couple (défini en global)
 * et de vitesse_moteur.
 * @return intensite
 **/
float getImot();
/****************************************/
/****************Taches******************/
/****************************************/
/**
 * driver_versement_silo_agregat : driver modélisant la gestion du versement du contenu des silos d'agrégats.
 * return 0
 **/
int driver_versement_silo_agregat();
/**
 * driver_versement_silo_ciment : driver modélisant la gestion du versement du contenu des silos des ciments.
 * return 0
 **/
int driver_versement_silo_ciment();
/**
 * driver_versement_silo_eau : driver modélisant la gestion du versement due l'eau dans le malaxeur.
 * return 0
 **/
int driver_versement_silo_eau();
/**
 * driver_versement_malaxeur : driver modélisant la gestion du versement due l'eau dans le malaxeur.
 * return 0
 **/
int driver_versement_malaxeur();
/**
 * driver_moteur : driver modélisant la gestion de la vitesse du moteur selon la consigne reçue. Modifie la
 * valeur de vitesse_moteur. Calcule un coefficient d'incrémentation pour que la vitesse voulue soit atteinte
 * en 5 secondes.
 * in : (int) vitesse_voulue
 * return 0
 **/
int driver_moteur(int vitesse_voulue);
/**
 * driver_remplissage_silo_agregat : driver modélisant la gestion du remplissage des silos agrégats. Lancé quand
 * le silo est vide.
 * return 0
 **/
int driver_remplissage_silo_agregat();
/**
 * driver_remplissage_silo_ciment : driver modélisant la gestion du remplissage des silos ciments. Lancé quand
 * le silo est vide.
 * return 0
 **/
int driver_remplissage_silo_ciment();
/**
 * driver_remplissage_silo_eau : driver modélisant la gestion du remplissage du silo d'eau. Lancé quand
 * le silo est vide.
 * return 0
 **/
int driver_remplissage_silo_eau();
/**
 * driver_versement_balance_agregat : driver modélisant le versement du contenu de la balance des agrégats.
 * Se lance quand les silos ont fini de verser leur quantités d'agrégats respectifs.
 * return 0
 **/
int driver_versement_balance_agregat();
/**
 * driver_versement_balance_ciment : driver modélisant le versement du contenu de la balance des ciments.
 * Se lance quand les silos ont fini de verser leur quantités de ciments respectifs.
 * return 0
 **/
int driver_versement_balance_ciment();

//----------------Affichage du système dans la console
/**
 * driver_affichage_test : affichage de l'état du système en temps réel dans la console. Recupère les informations
 * depuis les tampons. Rafraîchit la console selon la valeur de TAUX_RAFFRAICHISSEMENT définie en globale.
 * return 0
 **/
int driver_affichage_test();
/**
 * longueur_entier : retourne la longueur d'un entier (on le divise par 10 successivement jusqu'à ce qu'il 
 * atteigne 0, en incrémentant la valeur que l'on retourne).
 * in : int valeur à tester
 * return longueur
 **/
int longueur_entier(int);
/**
 * affiche_silo : représente l'état des différents silos présents dans le système dans la console.
 * return void
 **/
void affiche_silo(int[], int[], int[], int[], char);
