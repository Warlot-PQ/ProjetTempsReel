#include <vxWorks.h>
#include <taskLib.h> 
#include <semLib.h> 
#include "cimenterie.h"
#include "accesTampons.h"
#include "taches.h"

int main(){
	int index_boucle;
	
	//Initialise les types de béton
	beton_type_1.agregat_1 = 16;
	beton_type_1.agregat_2 = 32;
	beton_type_1.agregat_3 = 0;
	beton_type_1.ciment_1 = 20;
	beton_type_1.ciment_2 = 0;
	beton_type_1.eau = 32;

	beton_type_2.agregat_1 = 22;
	beton_type_2.agregat_2 = 31;
	beton_type_2.agregat_3 = 0;
	beton_type_2.ciment_1 = 17;
	beton_type_2.ciment_2 = 0;
	beton_type_2.eau = 30;

	beton_type_3.agregat_1 = 30;
	beton_type_3.agregat_2 = 0;
	beton_type_3.agregat_3 = 20;
	beton_type_3.ciment_1 = 0;
	beton_type_3.ciment_2 = 20;
	beton_type_3.eau = 30;
	
	versement_eau_possible = 1;
	versement_eau_en_cours = 0;
	
	//Initialise les sémaphores d'exclusion mutulle
	sem_tampon_cmd = semMCreate(SEM_Q_FIFO);
	sem_tampon_fonct_calcul = semMCreate(SEM_Q_FIFO);
	sem_tampon_qte_silos = semMCreate(SEM_Q_FIFO);
		
	//Initialise les sémaphores de synchronisation des tâches
	sem_tampon_cmd = semMCreate(SEM_Q_FIFO);
	sem_tampon_qte_silos = semMCreate(SEM_Q_FIFO);
	sem_tampon_fonct_calcul = semMCreate(SEM_Q_FIFO);
	sem_niveau_eau = semMCreate(SEM_Q_FIFO);
	sem_quantite_eau_restante = semMCreate(SEM_Q_FIFO);
	sem_quantite_agregat_restante = semMCreate(SEM_Q_FIFO);
	sem_quantite_agregat_totale = semMCreate(SEM_Q_FIFO);
	sem_versement_eau_possible = semMCreate(SEM_Q_FIFO);
	
	/*
	sem_demande_hygronometrie
	sem_hygronometrie
	sem_fin_agregat
	sem_fin_ciment
	sem_fin_eau
	sem_fin_malaxeur
	sem_debut_malaxeur

	sem_calcul_agregat
	sem_calcul_ciment
	sem_calcul_eau

	extern SEM_ID sem_int_min_agr_1
	extern SEM_ID sem_int_min_agr_2
	extern SEM_ID sem_int_min_agr_3
	extern SEM_ID sem_int_max_agr_1
	extern SEM_ID sem_int_max_agr_2
	extern SEM_ID sem_int_max_agr_3

	extern SEM_ID sem_int_min_cim_1
	extern SEM_ID sem_int_min_cim_2
	extern SEM_ID sem_int_max_cim_1
	extern SEM_ID sem_int_max_cim_2

	extern SEM_ID sem_int_max_eau
	extern SEM_ID sem_int_min_eau
	extern SEM_ID sem_int_plus_eau
	extern SEM_ID sem_int_moins_eau

	extern SEM_ID sem_demande_versement_agregat
	sem_demande_versement_ciment
	sem_demande_versement_eau

	file_debut_remplissage_balance_agregat
	sem_fin_remplissage_balance_agregat
	
	file_debut_remplissage_balance_ciment
	sem_fin_remplissage_balance_ciment*/

	//sémaphore de synchro des balances
	extern SEM_ID sem_pret_balance_agregat;
	extern SEM_ID sem_pret_balance_ciment;
	extern SEM_ID sem_ouverture_balance_agregat;	//demande d'ouverture
	extern SEM_ID sem_ouverture_balance_ciment;		//demande d'ouverture
	extern SEM_ID sem_fin_vers_balance_agregat;
	extern SEM_ID sem_fin_vers_balance_ciment;

	extern SEM_ID sem_agregat_et_ciment_suivant;

	extern SEM_ID sem_debut_camion;
	extern SEM_ID sem_diode_allumer_camion;
	extern SEM_ID sem_diode_eteindre_camion;
	extern SEM_ID sem_position_camion_absent_malaxeur;
	extern SEM_ID sem_position_camion_present_malaxeur;
	extern SEM_ID sem_position_ok;

	extern SEM_ID sem_van_ferme_malaxeur;
	extern SEM_ID sem_van_ouvre_malaxeur;
	
	
	
	
	

	sem_fin_eau = semBCreate(SEM_Q_FIFO, 0);
	sem_fin_malaxeur = semBCreate(SEM_Q_INFO, 0);
	sem_debut_malaxeur = semBCreate(SEM_Q_INFO, 0);
	
	sem_calcul_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_calcul_ciment = semBCreate(SEM_Q_FIFO, 0);
	sem_calcul_eau = semBCreate(SEM_Q_FIFO, 0);
	sem_demande_versement_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_demande_versement_ciment = semBCreate(SEM_Q_FIFO, 0);
	sem_demande_hygronometrie = semBCreate(SEM_Q_INFO, 0);
	sem_hygronometrie = semBCreate(SEM_Q_INFO, 0);
	sem_agregat_et_ciment_suivant = semBCreate(SEM_Q_INFO, 0);
	
	sem_debut_camion = semBCreate(SEM_Q_INFO, 0);
	sem_diode_allumer_camion = semBCreate(SEM_Q_INFO, 0);
	sem_diode_eteindre_camion = semBCreate(SEM_Q_INFO, 0);
	file_position_camion_absent_malax = msgQCreate(1000, 100, MSG_Q_FIFO);
	sem_position_camion_present_malax = semBCreate(SEM_Q_INFO, 0);
	sem_position_camion_ok = semBCreate(SEM_Q_INFO, 0);
	
	sem_van_ouvre_malaxeur = semBCreate(SEM_Q_INFO, 0);
	sem_van_ferme_malaxeur = semBCreate(SEM_Q_INFO, 0);
	
	versement_eau = semBCreate(SEM_Q_FIFO, 1);
	
	file_intensite = msgQCreate(1000, 100, MSG_Q_FIFO);
	
	
	
	//Initialise le contenu des tampons
	for(index_boucle = 0; index_boucle < NB_COMMANDE * 3; index_boucle += 1){
		tampon_cmd[index_boucle] = 0;
	}
	
	for(index_boucle = 0; index_boucle < NB_SILOS; index_boucle += 1){
		tampon_qte_silos[index_boucle] = 0;
	}
	
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_plus_recente] = -1;
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_en_cours] = -1;
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_eau_en_cours] = 0;
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_agregat_en_cours] = 0;
	tampon_fonct_calcul[index_tampon_fonct_calcul_cmd_ciment_en_cours] = 0;
		
	//Empeche la réquisition (préemption)
	taskLock();
	
	//Lance les tâches
	taskSpawn("gestion_IHM",200,
		                0x100,2000,(FUNCPTR) gestion_IHM,
		                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_cmd",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_cmd,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_malax",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_malax,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_agregat",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_agregat,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_ciment",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_ciment,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_eau",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_eau,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("calcul_qte_eau",200,
			                0x100,2000,(FUNCPTR) calcul_qte_eau,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("calcul_qte_agregat",200,
			                0x100,2000,(FUNCPTR) calcul_qte_agregat,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("calcul_qte_ciment",200,
			                0x100,2000,(FUNCPTR) calcul_qte_ciment,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("versement_agregat",200,
			                0x100,2000,(FUNCPTR) versement_agregat,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_agregat_1",200,
			                0x100,2000,(FUNCPTR) remplissage_agregat_1,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_agregat_2",200,
			                0x100,2000,(FUNCPTR) remplissage_agregat_2,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_agregat_3",200,
			                0x100,2000,(FUNCPTR) remplissage_agregat_3,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("versement_ciment",200,
			                0x100,2000,(FUNCPTR) versement_ciment,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_ciment_1",200,
			                0x100,2000,(FUNCPTR) remplissage_ciment_1,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_ciment_2",200,
			                0x100,2000,(FUNCPTR) remplissage_ciment_2,
			                0,0,0,0,0,0,0,0,0,0);

	taskSpawn("gestion_balance_agregats",200,
			                0x100,2000,(FUNCPTR) gestion_balance_agregats,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_balance_ciment",200,
			                0x100,2000,(FUNCPTR) gestion_balance_ciment,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_synchro",200,
			                0x100,2000,(FUNCPTR) gestion_synchro,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("versement_eau",200,
			                0x100,2000,(FUNCPTR) versement_eau,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_eau",200,
			                0x100,2000,(FUNCPTR) remplissage_eau,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_position_camion",200,
			                0x100,2000,(FUNCPTR) gestion_position_camion,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_versement",200,
			                0x100,2000,(FUNCPTR) gestion_versement,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_moteur",200,
			                0x100,2000,(FUNCPTR) gestion_moteur,
			                0,0,0,0,0,0,0,0,0,0);
	
	//Réautorise la réquisition
	taskUnlock();
	
	return 0;
}
