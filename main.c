#include <vxWorks.h>
#include <taskLib.h> 
#include "cimenterie.h"
#include "accesTampons.h"
#include "signauxExterieur.h"
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
	
	//Semaphore de test (driver)
	sem_capacite_silo_agregat_courrante = semMCreate(SEM_Q_FIFO);
	sem_capacite_silo_ciment_courrante = semMCreate(SEM_Q_FIFO);
	sem_capacite_silo_eau_courrante = semMCreate(SEM_Q_FIFO);
	sem_capacite_malaxeur = semMCreate(SEM_Q_FIFO);
	sem_vitesse_moteur = semMCreate(SEM_Q_FIFO);
	
	//Initialise les sémaphores d'exclusion mutulle
	sem_tampon_cmd = semMCreate(SEM_Q_FIFO);
	sem_tampon_fonct_calcul = semMCreate(SEM_Q_FIFO);
	sem_tampon_qte_silos = semMCreate(SEM_Q_FIFO);
	sem_versement_eau_possible = semMCreate(SEM_Q_FIFO);
	
	//Initialise les sémaphores d'initialisation de la cimenterie	
	sem_init_remplissage_silo_agr_1 = semBCreate(SEM_Q_FIFO, 0);
	sem_init_remplissage_silo_agr_2 = semBCreate(SEM_Q_FIFO, 0);
	sem_init_remplissage_silo_agr_3 = semBCreate(SEM_Q_FIFO, 0);
	sem_init_remplissage_silo_cim_1 = semBCreate(SEM_Q_FIFO, 0);
	sem_init_remplissage_silo_cim_2 = semBCreate(SEM_Q_FIFO, 0);
	sem_init_remplissage_silo_eau = semBCreate(SEM_Q_FIFO, 0);
	
	//Initialise les sémaphores de synchronisation des tâches
	sem_fin_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_fin_ciment = semBCreate(SEM_Q_FIFO, 0);
	sem_fin_eau = semBCreate(SEM_Q_FIFO, 0);
	sem_fin_versement_eau = semBCreate(SEM_Q_FIFO, 0);
	sem_fin_malaxeur = semBCreate(SEM_Q_FIFO, 0);
	sem_debut_malaxeur = semBCreate(SEM_Q_FIFO, 0);

	sem_calcul_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_calcul_ciment = semBCreate(SEM_Q_FIFO, 0);
	sem_calcul_eau = semBCreate(SEM_Q_FIFO, 0);

	sem_int_min_agr_1 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_min_agr_2 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_min_agr_3 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_max_agr_1 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_max_agr_2 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_max_agr_3 = semBCreate(SEM_Q_FIFO, 0);
	
	sem_int_min_cim_1 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_min_cim_2 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_max_cim_1 = semBCreate(SEM_Q_FIFO, 0);
	sem_int_max_cim_2 = semBCreate(SEM_Q_FIFO, 0);

	sem_int_plus_eau = semBCreate(SEM_Q_FIFO, 0);
	sem_int_moins_eau = semBCreate(SEM_Q_FIFO, 0);
	sem_int_max_eau = semBCreate(SEM_Q_FIFO, 0);
	sem_int_min_eau = semBCreate(SEM_Q_FIFO, 0);

	sem_int_plus_bal_agr = semBCreate(SEM_Q_FIFO, 0);
	sem_int_moins_bal_agr = semBCreate(SEM_Q_FIFO, 0);
	sem_int_plus_bal_cim = semBCreate(SEM_Q_FIFO, 0);
	sem_int_moins_bal_cim = semBCreate(SEM_Q_FIFO, 0);
	
	sem_demande_versement_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_demande_versement_ciment = semBCreate(SEM_Q_FIFO, 0);
	sem_demande_versement_eau = semBCreate(SEM_Q_FIFO, 0);

	file_debut_remplissage_balance_agregat = msgQCreate(10, 512, MSG_Q_FIFO);
	sem_fin_remplissage_balance_agregat = semBCreate(SEM_Q_FIFO, 0);
	
	sem_ferm_balance_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_ferm_balance_ciment = semBCreate(SEM_Q_FIFO, 0);
	
	file_debut_remplissage_balance_ciment = msgQCreate(10, 512, MSG_Q_FIFO);
	sem_fin_remplissage_balance_ciment = semBCreate(SEM_Q_FIFO, 0);

	//sémaphore de synchro des balances
	sem_pret_balance_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_pret_balance_ciment = semBCreate(SEM_Q_FIFO, 0);
	sem_ouverture_balance_agregat = semBCreate(SEM_Q_FIFO, 0);		//demande d'ouverture
	sem_ouverture_balance_ciment = semBCreate(SEM_Q_FIFO, 0);		//demande d'ouverture
	sem_fin_vers_balance_agregat = semBCreate(SEM_Q_FIFO, 0);
	sem_fin_vers_balance_ciment = semBCreate(SEM_Q_FIFO, 0);

	sem_melange_homogene = semBCreate(SEM_Q_FIFO, 0);
	
	sem_cmd_en_cours = semBCreate(SEM_Q_FIFO, 0);

	sem_debut_camion = semBCreate(SEM_Q_FIFO, 0);
	sem_diode_allumer_camion = semBCreate(SEM_Q_FIFO, 0);
	sem_diode_eteindre_camion = semBCreate(SEM_Q_FIFO, 0);
	sem_position_camion_ok = semBCreate(SEM_Q_FIFO, 0);
	sem_position_camion_ok = semBCreate(SEM_Q_FIFO, 0);
	sem_arret_rotation_moteur = semBCreate(SEM_Q_FIFO, 0);
	sem_vide_malaxeur = semBCreate(SEM_Q_FIFO, 0);

	sem_van_ferme_malaxeur = semBCreate(SEM_Q_FIFO, 0);
	sem_van_ouvre_malaxeur = semBCreate(SEM_Q_FIFO, 0);
	sem_stop_bal_tapis_agrEtCim = semBCreate(SEM_Q_FIFO, 0);
	sem_reprise_bal_tapis_agrEtCim = semBCreate(SEM_Q_FIFO, 0);
	
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
	
	//Initialisation implicite
	//TODO fermeture de toutes les vannes
	
	//Empeche la réquisition (préemption)
	taskLock();
	
	taskSpawn("driver_affichage_test",150,
						0x100,2000,(FUNCPTR) driver_affichage_test,
						0,0,0,0,0,0,0,0,0,0);
	
	taskSpawn("gestion_IHM",200,
		                0x100,2000,(FUNCPTR) gestion_IHM,
		                0,0,0,0,0,0,0,0,0,0);
	
	taskSpawn("gestion_evenement_fin_malax",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_fin_malax,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_fin_agregat",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_fin_agregat,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_fin_ciment",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_fin_ciment,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_evenement_fin_eau",200,
			                0x100,2000,(FUNCPTR) gestion_evenement_fin_eau,
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
	
	taskSpawn("versement_agregat_silos_et_balance",200,
			                0x100,2000,(FUNCPTR) versement_agregat_silos_et_balance,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_silo_agregat_1",200,
			                0x100,2000,(FUNCPTR) remplissage_silo_agregat_1,
			                0,0,0,0,0,0,0,0,0,0);
	
	taskSpawn("remplissage_silo_agregat_2",200,
			                0x100,2000,(FUNCPTR) remplissage_silo_agregat_2,
			                0,0,0,0,0,0,0,0,0,0);
	
	taskSpawn("remplissage_silo_agregat_3",200,
			                0x100,2000,(FUNCPTR) remplissage_silo_agregat_3,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("versement_ciment_silos_et_balance",200,
			                0x100,2000,(FUNCPTR) versement_ciment_silos_et_balance,
			                0,0,0,0,0,0,0,0,0,0);
	 
	taskSpawn("remplissage_silo_ciment_1",200,
			                0x100,2000,(FUNCPTR) remplissage_silo_ciment_1,
			                0,0,0,0,0,0,0,0,0,0);
	
	taskSpawn("remplissage_silo_ciment_2",200,
			                0x100,2000,(FUNCPTR) remplissage_silo_ciment_2,
			                0,0,0,0,0,0,0,0,0,0);
	
	taskSpawn("remplissage_balance_agregats",200,
			                0x100,2000,(FUNCPTR) remplissage_balance_agregats,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("remplissage_balance_ciment",200,
			                0x100,2000,(FUNCPTR) remplissage_balance_ciment,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("arret_et_reprise_versement_balances",200,
			                0x100,2000,(FUNCPTR) arret_et_reprise_versement_balances,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_synchro_balances",200,
			                0x100,2000,(FUNCPTR) gestion_synchro_balances,
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
	
	taskSpawn("gestion_versement_malaxeur",200,
			                0x100,2000,(FUNCPTR) gestion_versement_malaxeur,
			                0,0,0,0,0,0,0,0,0,0);
	taskSpawn("gestion_moteur_malaxeur",200,
			                0x100,2000,(FUNCPTR) gestion_moteur_malaxeur,
			                0,0,0,0,0,0,0,0,0,0);
	//Réautorise la réquisition
	taskUnlock();
	
	
	
	
	
	return 0;
}
