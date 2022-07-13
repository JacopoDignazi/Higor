#include "mod_strutt.h"

#ifndef SUPP_CHA_H
#include "supp_cha.h"
#define SUPP_CHA_H
#endif

	
	//RICERCA OGGETTI
	mod_ogg* search(char* name, mod_strutt* here= Global);
	mod_ogg* search(mod_ogg* obj , mod_strutt* here= Global);
	mod_ogg* search(const char* name_const , mod_strutt* here= Global);
	//PER AGGIUNGERE OGGETTI A STRUTTURE
	int add_ogg(char* this_name, mod_strutt* in_strutt= Global);
	int add_ogg(const char* this_name, mod_strutt* in_strutt= Global);	
	int remove_ogg(char* name_ogg, mod_strutt* strutt);
	
	
	//PER CREARE OGGETTI	
	mod_ogg::mod_ogg(char* new_name, mod_strutt* in_strutt= Global){
		int i;
		for(i=0; i<= MAXDOWNOGG; i++){down_ogg[i]= NULL;}
		for(i=0; i<=MAXNSTRUTT; i++){ strutt_above[i]= NULL;}
		for(i=0; i<=MAXUPOGG; i++){   up_ogg[i]=NULL; }
		for(i=0; i<=MAXEQOGG; i++){   equivalent_ogg[i]=NULL;}
		
		strcopy(UNDEF(ADAPTED(new_name)), name );
		if(search(name) == MISSING){ 
			this->strutt_above[0]= Global;
			Global->ogg[++(Global->N_ogg)]= this;
		}
		if(in_strutt != Global){						
			this->strutt_above[++(this->N_strutt)]= in_strutt;
			in_strutt->ogg[++(in_strutt->N_ogg)]= this;
		}
		strcopy("undefined", def);
		strcopy("undefined", comment);
	}
	
	//PER CREARE STRUTTURE	
	mod_strutt::mod_strutt(char* new_name){			//NB dovrò templatizzarne un'altra per più gruppi
		strcopy(ADAPTED(new_name), name);				//posso aggiunger roba per gruppo di strutture
		int i;
		for(i=0; i<= MAXSIZESTRUTT; i++){ ogg[i]=NULL;	}
		IN_ALL_PROGRAM->strutt[++(IN_ALL_PROGRAM->N_strutt)]= this;
	}
	
		
	//PER AGGIUNGERE DOWN (sfruttata da set_def)	
	int mod_ogg::add_down(char* new_name, mod_strutt* there=Global){
		int i;
		static char new_name_from[SIZESURE]; strcopy( UNDEF(ADAPTED(new_name)), new_name_from, SIZENAME);
		for(i=1; i<=this->N_down; i++){
		//	printf("\n %d searching -%s- in %s,\n down: -%s-\n", i, new_name_from, this->name, UNDEF(this->down_ogg[i]->name)); 
			if( streq( UNDEF(this->down_ogg[i]->name), new_name_from) ) return 1;		//non fa nulla se c'è già
		}
		for(i=1; i<=this->N_up; i++){
		//	printf("\n %d searching -%s- in %s,\n down: -%s-\n", i, new_name_from, this->name, UNDEF(this->up_ogg[i]->name)); 
			if( streq( UNDEF(this->up_ogg[i]->name), new_name_from) ) return 2;			//o se è tra gli indotti
		}
		mod_ogg* supp= search(new_name_from);
		if(supp==MISSING){ add_ogg(new_name_from);}//se non esiste neanche
			supp=search(new_name_from, there);
		if(supp==MISSING){ add_ogg(new_name_from, there);}//se non esiste nel there
		
		supp=search(new_name_from);			//così sicuro punta di nuovo all'oggetto		
		if(this==supp) return -1;	
		this->down_ogg[++(this->N_down)]=supp;	
		supp->up_ogg[++(supp->N_up)]=this;
		
		//grading(); 	//conviene lasciarlo ad ogni chiamata?
		return 3;
	}
	
	
	//ORDINAMENTO IN MOD_OGG
	void mod_ogg::order_and_grading(){
		
		bool flagfin;
		int i;
		mod_ogg* temp;
		
		while(1){										//ordino i down
			flagfin=true;
			for(i=1; i<=N_down-1; i++){				
				if(down_ogg[i]->grade > down_ogg[i+1]->grade){
					flagfin=false;			//metto a i+1 il maggiore dei due
					temp=down_ogg[i+1];
					down_ogg[i+1]=down_ogg[i];
					down_ogg[i]=temp;
				}
			}
			for(i=N_down-1; i>=1; i--){ 				
				if(down_ogg[i]->grade > down_ogg[i+1]->grade){
					flagfin=false;			//metto a i+1 il maggiore dei due
					temp=down_ogg[i+1];				//stessa cosa di sopra ma lo faccio tornando indietro
					down_ogg[i+1]=down_ogg[i];
					down_ogg[i]=temp;
				}
			}
			if(flagfin) break;
		}
		while(1){										//ordino gli up
			flagfin=true;
			for(i=1; i<=N_up-1; i++){				
				if(up_ogg[i]->grade > up_ogg[i+1]->grade){
					flagfin=false;			//metto a i+1 il maggiore dei due
					temp=up_ogg[i+1];
					up_ogg[i+1]=up_ogg[i];
					up_ogg[i]=temp;
				}
			}
			for(i=N_up-1; i>=1; i--){ 
				if(up_ogg[i]->grade > up_ogg[i+1]->grade){
					flagfin=false;			//metto a i+1 il maggiore dei due
					temp=up_ogg[i+1];				//stessa cosa di sopra ma lo faccio tornando indietro
					up_ogg[i+1]=up_ogg[i];
					up_ogg[i]=temp;
				}
			}
			if(flagfin) break;
		}
		for(i=1; i<=N_up; i++){	//controllo che sia tutto ok 
			if(up_ogg[i]==NULL){
				printf("\n\n ERRORE ACQUISITO IN ORDER_AND_GRADING DI %s\n   oggetto DOWN[%d] nullo", name, i);
				return;
			}
		}
		for(i=1; i<=N_down; i++){	
			if(down_ogg[i]==NULL){
				printf("\n\n ERRORE ACQUISITO IN ORDER_AND_GRADING DI %s\n   oggetto DOWN[%d] nullo", name, i);
				return;
			}
		}
		int grademax=-2;
		for(i=1; i<=N_down; i++){
			if(down_ogg[i]->grade > grademax) grademax=down_ogg[i]->grade;		//stabilisce il grado
		}
		
		if(grade != grademax+1){	//se il grado è cambiato devo risistemare l'ordine di quelli sotto->up, e sopra->down, oltre che delle strutture
			grade= grademax+1;
			for(i=0; i<=N_strutt; i++){
				strutt_above[i]->order();			//riordino le strutture
			}
			for(i=1; i<=N_up; i++){
				up_ogg[i]->order_and_grading();			//riordino gli oggetti up
			}
			for(i=1; i<=N_down; i++){
				down_ogg[i]->order_and_grading();			//e anche quelli sotto
			}
		}
	}
			
	void mod_ogg::node_order(){	
		int i, j;
		bool flagfin;
		mod_ogg* temp;
		
		for(i=1; i<=N_down; i++){		//tolgo eventuali vuoti in down
			if (down_ogg[i]== NULL){
				for(j=i; j<N_down; j++){
					down_ogg[j]=down_ogg[j+i];
				}
				--N_down;
				--i;	
			}
		}
		for(i=1; i<=N_up; i++){			//tolgo eventuali vuoti in up
			if (up_ogg[i]== NULL){
				for(j=i; j<N_up; j++){
					up_ogg[j]=up_ogg[j+i];
				}
				--N_up;
				--i;	
			}
		}
		
		for(i=1; i<=N_up; i++){	//controllo che sia tutto ok 
			if(up_ogg[i]==NULL){
				printf("\n\n ERRORE CON ORDINAMENTO IN NODE_ORDER DI %s\n   oggetto DOWN[%d] nullo", name, i);
				return;
			}
		}
		for(i=1; i<=N_down; i++){	
			if(down_ogg[i]==NULL){
				printf("\n\n ERRORE CON ORDINAMENTO IN NODE_ORDER DI %s\n   oggetto DOWN[%d] nullo", name, i);
				return;
			}
		}
		
		order_and_grading();		//riordina e gradua gli oggetti sopra, sotto e le strutture
		
		i=0;
		if(name[0]== CHARUNDEF && grade >= 0 ){
			do{
				name[i]=name[i+1];
				i++;
			} while(name[i]!= '\0');		//prototipo di funzione removechar
		}
		else if(name[0] != CHARUNDEF && grade < 0 ){		
			strcopy(UNDEF(name), name);
		}				
	}
	
	//ORDINAMENTO IN STRUTT
	void mod_strutt::order(){
		int i, j;
		bool flagfin;
		mod_ogg* temp;					//tolgo eventuali vuoti
		for(i=1; i<=N_ogg; i++){
			if (ogg[i]== NULL){
				for(j=i; j<N_ogg; j++){
					ogg[i]=ogg[i+1];
				}
				--N_ogg;
				--i;	
			}
		}
		for(i=1; i<=N_ogg; i++){//controllo
			if(ogg[i]==NULL) {printf("\n\n ERRORE NELL'ORDINAMENTO DI STRUTTURA %s, trovato OGG[%d] vuoto", name, i); return;}
		}
		while(1){								//ordino gli oggetti per grado
			flagfin=true;
			for(i=1; i<=N_ogg-1; i++){				
				if(ogg[i]->grade > ogg[i+1]->grade){
					flagfin=false;			//metto a i+1 il maggiore dei due
					temp=ogg[i+1];
					ogg[i+1]=ogg[i];
					ogg[i]=temp;
				}
			}
			for(i=N_ogg-1; i>=1; i--){ 
				if(ogg[i]->grade > ogg[i+1]->grade){
					flagfin=false;			//metto a i+1 il maggiore dei due
					temp=ogg[i+1];				//stessa cosa di sopra ma lo faccio tornando indietro
					ogg[i+1]=ogg[i];
					ogg[i]=temp;
				}
			}
			if(flagfin) break;
		}
		grade_min= ogg[1]->grade;
		grade_max= ogg[N_ogg]->grade;			
	}
