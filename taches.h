//#ifndef TACHES_H
//#define TACHES_H

#include <stdio.h>
#include <unistd.h>
#include <semLib.h>
#include <msgQLib.h>
#include <taskLib.h>

//---------------- Module Gestion IHM
/**
 * gestion_IHM : tâche gérant la réception des données émises par l'utilisateur et les stocke dans le tampon_cmd
 * return 0
 **/
int gestion_IHM();

//----------------Module Gestion quantité
//---------------------Gestion évènement
/**
 * gestion_evenement_fin_malax : tâche gérant la réception de signaux événements pour la fin de tâche malaxeur. Réinitialise
 * le système s'il n'y a plus de commande. Efface les données concernant la commande en cours dans tampon_cmd,
 * incrémente cmd_en_cours dans tampon_fonct_calcul, et lance le calcul de qté eau.
 * return 0
 **/
int gestion_evenement_fin_malax();
/**
 * gestion_evenement_fin_agregat : tâche gérant la réception de signaux événements pour la fin du versement de la 
 * balance agrégat : s'il y a encore une commande, relance les calculs de qté agrégats, et incrémente agregat_cmd_en_cours
 * dans tampon fonct_calcul.
 * return 0
 **/
int gestion_evenement_fin_agregat();
/**
 * gestion_evenement_fin_ciment : tâche gérant la réception de signaux événements pour la fin du versement de la 
 * balance ciment : s'il y a encore une commande, relance les calculs de qté ciment, et incrémente ciment_cmd_en_cours
 * dans tampon fonct_calcul. 
 * return 0
 **/
int gestion_evenement_fin_ciment();
/**
 * gestion_evenement_fin_eau : tâche gérant la réception de signaux événements pour la fin du versement de l'eau
 * dans le malaxeur. Incrémente eau_cmd_en_cours dans tampon_fonct.
 **/
int gestion_evenement_fin_eau();

//---------------------Gestion quantité
/**
 * calcul_qte_eau : tâche calculant la quantité d'eau à verser selon le type de béton et selon la ditance à parcourir.
 * Stocke le résultat dans tampon_qte_silo, à l'index attribué (demande de l'hygrométrie ici).
 * return 0 si aucun problème, PB sinon.
 **/
int calcul_qte_eau();
/**
 * calcul_qte_agregat : tâche calculant la quantité d'agrégat à verser selon le type de béton et selon la distance à
 * parcourir. Stocke le résultat dans tampon_qte_silo, à l'index attribué.
 * return 0 si aucun problème, PB sinon.
 **/
int calcul_qte_agregat();
/**
 * calcul_qte_ciment : tâche calculant la quantité de ciment à verser selon le type de béton et selon la distance à
 * parcourir. Stocke le résultat dans tampon_qte_silo, à l'index attribué.
 * return 0 si aucun problème, PB sinon.
 **/
int calcul_qte_ciment();

//----------------Gestion silos agregats et ciments
//-----------------------------Gestion silos agregats
/**
 * versement_agregat_silos_et_balance : tâche gérant les événements de versement des silos agrégats, et l'ouverture de leur balance.
 *  Attends la fin des calculs des volumes d'agrégats, puis verse la bonne qté correspondante dans la balance, silo par silo.
 * Attends signal de gestion synchro pour lancer le tapis et l'ouverture de la balance, et attend que celle-ci siot vide 
 * pour la refermer.
 * return 0
 **/
int versement_agregat_silos_et_balance();
/**
 * remplissage_silo_agregat_1 : tâche gérant le remplissage du silo 1 d'agrégat. Remplit le silo une fois que le silo est vide.
 * return 0
 **/
int remplissage_silo_agregat_1();
/**
 * remplissage_silo_agregat_2 : tâche gérant le remplissage du silo 2 d'agrégat. Remplit le silo une fois que le silo est vide.
 * return 0
 **/
int remplissage_silo_agregat_2();
/**
 * remplissage_silo_agregat_3 : tâche gérant le remplissage du silo 3 d'agrégat. Remplit le silo une fois que le silo est vide.
 * return 0
 **/
int remplissage_silo_agregat_3();
//-----------------------------Gestion silos ciments
/**
 * versement_ciment_silos_et_balance : tâche gérant le versement des silos ciment, et l'ouverture de leur balance. 
 * Attends la fin des calculs des volumes de ciment, puis verse la bonne qté correspondante dans la balance, silo par silo.
 * Attends signal de gestion synchro pour lancer le tapis et l'ouverture de la balance, et attend que celle-ci siot vide 
 * pour la refermer.
 * return 0
 **/
int versement_ciment_silos_et_balance();
/**
 * remplissage_silo_ciment_1 : tâche gérant le remplissage du silo 1 de ciment. Remplit le silo une fois que le silo est vide.
 * return 0
 **/
int remplissage_silo_ciment_1();
/**
 * remplissage_silo_ciment_2 : tâche gérant le remplissage du silo 2 de ciment. Remplit le silo une fois que le silo est vide.
 * return 0
 **/
int remplissage_silo_ciment_2();

//----------------Gestion balances et tapis
//---------------------Gestion balances
/**
 * remplissage_balance_agregats : tâche gérant la réception des signaux d'interruptions plus et moins pour la balance agrégat :
 * incrémente la valeur de la masse contenue par la balance
 * return 0.
 **/
int remplissage_balance_agregats();
int remplissage_balance_ciment();
int arret_et_reprise_versement_balances();

//----------------Gestion silo eau et malaxeur
//-----------------------Gestion synchro
/**
 * gestion_synchro_balances : tâche gérant la synchronisation des composants du module eau/malaxeur/balances : permet leur ouverture uniquement quand
 * elles sont toutes les deux prếtes. il les ferme quand elles sont toutes les deux vides, et lance le malaxeur. Attend que de re
 * -cevoir l'événement "mélange homogène" pour déclencher le versement de l'eau.
 * return 0
 **/
int gestion_synchro_balances();
//-----------------------Gestion silo eau
/**
 * versement_eau : tâche gérant les événéments lors du versement de l'eau : attente d'un événement déclenchant le versement, et gestion de l'interruption
 * quand le silo est vide.
 * return 0
 **/
int versement_eau();
/**
 * remplissage_eau : tâche gérant le remplissage du silo d'eau. Lorsque le silo est vide, on ouvre la vanne du haut et on attend l'événement qui signale
 * que le silo est plein à nouveau pour fermer le robinet.
 * return 0
 **/
int remplissage_eau();
//-----------------------Gestion malaxeur
/**
 * gestion_position_camion : tâche gérant le positionnement du camion. Se lance uniquement lorsque le mélange est homogène et que le système veut passer
 * en phase de versement. Allume la diode signalant que le camion n'est pas en position. Dès qu'il est en position, attend 5 seconde et si toujours en 
 * position, éteint la diode et signale que le versement est possible.
 * return 0
 **/
int gestion_position_camion();
/**
 * gestion_versement_malaxeur : tâche gérant le versement du contenu du malaxeur dans le camion. Se lance uniquement lorsque le temps de malaxage après 
 * que le versement de l'eau ne soit fini. Signale la fin du versement à la tâche de gestion d'événement.
 * return 0
 **/
int gestion_versement_malaxeur();
/**
 * gestion_versement_malaxeur : tâche gérant le contrôle du moteur du système. Effectue le contrôle sur la vitesse de rotation selon l'intensité, et sur
 * le temps de malaxage et l'homogénéisation du système.
 **/
int gestion_moteur_malaxeur();

//----------------Collection de fonctions (ne sont pas des taches) appelées par le milieu extérieur
/**
 * capteur_vide_malaxeur : donne un jeton à sem_vide_malaxeur. Si ce sémaphore a un jeton, c'est que le malaxeur est vide et le signale au travers de 
 * cette fonction
 **/
void capteur_vide_malaxeur();
/**
 * capteur_plein_silo_agregat_1 : donne un jeton à sem_int_max_agr_1. Si ce sémaphore a un jeton, c'est que le silo d'agrégat 1 est plein et le signale
 * au travers de cette fonction.
 **/
void capteur_plein_silo_agregat_1();
/**
 * capteur_vide_silo_agregat_1 : donne un jeton à sem_int_min_agr_1. Si ce sémaphore a un jeton, c'est que le silo d'agrégat 1 est vide et le signale
 * au travers de cette fonction.
 **/
void capteur_vide_silo_agregat_1();
/**
 * capteur_plein_silo_agregat_2 : donne un jeton à sem_int_max_agr_2. Si ce sémaphore a un jeton, c'est que le silo d'agrégat 2 est plein et le signale
 * au travers de cette fonction.
 **/
void capteur_plein_silo_agregat_2();
/**
 * capteur_vide_silo_agregat_2 : donne un jeton à sem_int_min_agr_2. Si ce sémaphore a un jeton, c'est que le silo d'agrégat 2 est vide et le signale
 * au travers de cette fonction.
 **/
void capteur_vide_silo_agregat_2();
/**
 * capteur_plein_silo_agregat_3 : donne un jeton à sem_int_max_agr_3. Si ce sémaphore a un jeton, c'est que le silo d'agrégat 3 est plein et le signale
 * au travers de cette fonction.
 **/
void capteur_plein_silo_agregat_3();
/**
 * capteur_vide_silo_agregat_3 : donne un jeton à sem_int_min_agr_3. Si ce sémaphore a un jeton, c'est que le silo d'agrégat 3 est vide et le signale
 * au travers de cette fonction.
 **/
void capteur_vide_silo_agregat_3();
/**
 * capteur_plein_silo_ciment_1 : donne un jeton à sem_int_max_cim_1. Si ce sémaphore a un jeton, c'est que le silo de ciment 1 est plein et le signale
 * au travers de cette fonction.
 **/
void capteur_plein_silo_ciment_1();
/**
 * capteur_vide_silo_ciment_1 : donne un jeton à sem_int_min_cim_1. Si ce sémaphore a un jeton, c'est que le silo de ciment 1 est vide et le signale
 * au travers de cette fonction.
 **/
void capteur_vide_silo_ciment_1();
/**
 * capteur_plein_silo_ciment_2 : donne un jeton à sem_int_max_cim_2. Si ce sémaphore a un jeton, c'est que le silo de ciment 2 est plein et le signale
 * au travers de cette fonction.
 **/
void capteur_plein_silo_ciment_2();
/**
 * capteur_vide_silo_ciment_2 : donne un jeton à sem_int_min_cim_2. Si ce sémaphore a un jeton, c'est que le silo de ciment 2 est vide et le signale
 * au travers de cette fonction.
 **/
void capteur_vide_silo_ciment_2();
/**
 * capteur_plus_balance_agregats : donne un jeton à sem_int_plus_bal_agr. Si ce sémaphore a un jeton, c'est que la balance des agrégats est plus lourde de 1 kilo et le signale
 * au travers de cette fonction.
 **/
void capteur_plus_balance_agregats();
/**
 * capteur_moins_balance_agregats : donne un jeton à sem_int_moins_bal_agr. Si ce sémaphore a un jeton, c'est que la balance des agrégats est moins lourde de 1 kilo et le signale
 * au travers de cette fonction.
 **/
void capteur_moins_balance_agregats();
/**
 * capteur_plus_balance_ciment : donne un jeton à sem_int_plus_bal_cim. Si ce sémaphore a un jeton, c'est que la balance des ciments est plus lourde de 1 kilo et le signale
 * au travers de cette fonction.
 **/
void capteur_plus_balance_ciment();
/**
 * capteur_moins_balance_ciment : donne un jeton à sem_int_moins_bal_cim. Si ce sémaphore a un jeton, c'est que la balance des ciments est moins lourde de 1 kilo et le signale
 * au travers de cette fonction.
 **/
void capteur_moins_balance_ciment();
/**
 * capteur_plein_eau : donne un jeton à sem_int_max_eau. Si ce sémaphore a un jeton, c'est que le silo d'eau est plein et le signale
 * au travers de cette fonction.
 **/
void capteur_plein_eau();
/**
 * capteur_vide_eau : donne un jeton à sem_int_min_eau. Si ce sémaphore a un jeton, c'est que le silo d'eau est vide et le signale
 * au travers de cette fonction.
 **/
void capteur_vide_eau();
/**
 * capteur_plus_eau(NON UTILISEE) : donne un jeton à sem_int_plus_eau. Si ce sémaphore a un jeton, c'est que la capacité du silo d'eau s'incrémente d'une unité et le signale
 * au travers de cette fonction.
 **/
void capteur_plus_eau();
/**
 * capteur_moins_eau : donne un jeton à sem_int_moins_eau. Si ce sémaphore a un jeton, c'est que la capacité du silo d'eau se décrémente d'une unité et le signale
 * au travers de cette fonction.
 **/
void capteur_moins_eau();
//#endif
