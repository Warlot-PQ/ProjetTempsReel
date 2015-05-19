#include <vxWorks.h>
#include <taskLib.h> 
#include <semLib.h> 
#include "cimenterie.h"
#include "accesTampons.h"
#include "taches.h"

int main(){
	int index_boucle;
	
	//Initialise les sémaphores
	sem_tampon_cmd = semMCreate(SEM_Q_FIFO);
	sem_tampon_fonct_calcul = semMCreate(SEM_Q_FIFO);
	sem_tampon_qte_silos = semMCreate(SEM_Q_FIFO);
		
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
		
	//Empeche la réquisition (préemption) et lance toutes les tâches
	taskLock();
	
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
