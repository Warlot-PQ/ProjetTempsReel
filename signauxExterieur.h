#ifndef SIGNAUX_EXTERIEUR_H
#define SIGNAUX_EXTERIEUR_H

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
#define cst_vanne_malaxeur "M"
#define cst_vanne_haut_eau "VE1"
#define cst_vanne_bas_eau "VE2"

#define cst_tapis_agregat "TPA"
#define cst_tapis_ciment "TPC"

#define cst_balance_agregat "BA"
#define cst_balance_ciment "BC";

#define cst_silo_agregat_1 "A1"
#define cst_silo_agregat_2 "A2"
#define cst_silo_agregat_3 "A3"
#define cst_silo_ciment_1 "C1"
#define cst_silo_ciment_2 "C2"
#define cst_silo_eau "E"
#define cst_balance_agregat "BA"
#define cst_balance_ciment "BC"
#define cst_malaxeur "M"

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
void OuvrirBalance();
/**
*	Ferme une balance BA ou BC
*	vanne : Constante de la balance, utiliser les defines du .h
**/
void FermerBalance();

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

int getImot();

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
#endif
