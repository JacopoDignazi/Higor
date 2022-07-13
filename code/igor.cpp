#include "mod_class.h"


		//sistema i dir (quello base a una riga), quello pro esteso, quello a colonna, e a rete
		//savings and loading
		
main(){
	printf("\n\n                     --------===[ HIGER ]===--------\n\n");
	printf("\t\t\t\t\t26/01/2017\n");
	

	char c='A', sel, selmax=1, suppcha, sel_nest;
	int suppspace;
	char* names= 		new char[SIZESURE];
	char* definitions= 	new char[SIZEDEF];
	mod_strutt* strutt;
	mod_ogg* obj;
	
	//crea nuovo, lavora, esplora
	//... carica, salva
	
	do{
		IN_ALL_PROGRAM->dir();
		c='A';
		printf("\n\n %c) Crea nuovi oggetti in modello", c++);
		printf("\n %c) Esplora", c++);
		printf("\n %c) Salva su file", c++);
		printf("\n %c) Carica da file", c++);
//		printf("\n\n %c) Lavora su modello", c++);
//		printf("\n %c) Esplora modello", c++);		
		selmax= c-1;
		
		printf("\n\n inserire una lettera per proseguire (zeta per uscire)\t");		lettcha(sel);
	
		switch(sel){
			case 'a': case 'A': {
				
				names[0]=1;
				
				do{
					printf("\n\n inserire nome struttura di riferimento (zero per uscire)\t"); 
					GETTINGNAME(names);
					if(names[0]!= '0'){	
						if( streq((char*)"global", names)) { strutt= Global;}
						else {strutt= search_strutt(names);}
						if(strutt == MISSING_STRUTT) {
							printf("\n\n struttura \"%s\" attualmente inesistente, creare struttura? (s/n)   ", names);
							do{
								lettcha(suppcha);
							} while(suppcha != 'n' && suppcha != 's');
							if(suppcha== 'n') names[0]= '0';
							else if(suppcha== 's') {
								strutt= new mod_strutt(names);
							}
						}
		//NB DOVREI RISISTEMARE UN PO COME SI ESPRIMONO I DIR				
						if(strutt!= MISSING_STRUTT) strutt->dir_all();
						while(names[0]!= '0'){
							printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
							printf("\n\n inserire nome oggetto(zero per uscire)\n");
							printf(" se l'oggetto non esiste, verrà creato, altrimenti ridefinito\t");
							GETTINGNAME(names); if(names[0]=='0' || names[0]== '\0' || names[0]=='\n') break;
							if(names[0]<='9' && names[0]>='1'){//inserire qui la parte in cui reperisco gli oggetti dal numero
								}
							obj= search(names);
							if(obj== MISSING) printf("\n\t\t oggetto non esistente");
							add_ogg(names, strutt);
							obj=search(names);
							obj->dir();
							printf("\n\n inserire definizione dell'oggetto (maiuscole per altri oggetti\n zero per lasciare indefinito)\n\n  ");
							GETTINGDEF(definitions);
		//DA CAMBIARE QUI PER AVERE O NO AGGIUNTE AUTOMATICHE ALLE STRUTT (aggiungere eventualmente modalità di set_def)
							if(definitions[0] != '0' && definitions[0] != '\0' && definitions[0] !='\n'){
								obj->set_def(definitions);//, strutt);
							}
							obj->dir_all();
							
						}
					}
				}while (names[0]!='0' && names[0]!= '\0' && names[0]!='\n');
			
				break;
			}
			
			case 'c': case 'C':{
				printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
				names[0]=1;
				while(names[0]!= '0'){
					printf("\n\n\n cerca il qualcosa che vuoi salvare (zero per uscire)\t"); 
					GETTINGNAME(names);
					if(names[0]!= '0'){		//oppure un names=0 break;
						
						strutt= search_strutt(names);
						if(strutt == MISSING_STRUTT) {
							obj= search(names);
							if(obj== MISSING) break;
							printf("\n\n oggetto trovato:");
							obj->dir_all();
							printf("\n\n inserire il nome del file di testo su cui salvarlo\n (auto per il nome dell'oggetto)\t\t");
							GETTINGNAME(names);
							if(names[0] != '0'){
								obj->saving(names);
							}
						}
						else{
							printf("\n\n struttura trovata:");
							strutt->dir_all();
							printf("\n\n inserire il nome del file di testo su cui salvarla\n (auto per il nome dell'oggetto)\t\t");
							GETTINGNAME(names);
							if(names[0] != '0'){
								strutt->saving(names);
							}
						}
						
						if( streq((char*)"global", names) ){
							strutt=Global;
							printf("\n\n STRUTTURA GLOBALE:");
							strutt->dir_all();
							printf("\n\n inserire il nome del file di testo su cui salvarla\n (auto per il nome dell'oggetto)\t\t");
							GETTINGNAME(names);
							if(names[0] != '0'){
								strutt->saving(names);
							}
						}
					}
				}
				break;
			}
			
			case 'd': case 'D':{
				printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
				names[0]=1;
				while(names[0]!= '0'){
					do{
						printf("\n\n caricare oggetto o struttura? (o/s)\t");
						lettcha(sel_nest);
					} while(sel_nest != 'o' && sel_nest != 'O' && sel_nest != 's' && sel_nest != 'S' && sel_nest!= '0');
						
						
					printf("\n\n\n nome del file da cui caricare (zero per uscire)\t"); 
					GETTINGNAME(names);
					if(names[0]!= '0'){
						if(sel_nest== 's' || sel_nest== 'S'){	
							strutt=load_newstrutt(names);
							if(strutt!= MISSING_STRUTT) {
								strutt->dir_all();
								printf("\n\n caricamento riuscito con successo\n");
							}
							else{
								printf("\n\n caricamento non riuscito\n");
							}
						}
						if(sel_nest== 'o' || sel_nest== 'O'){	
							obj=load_newobj(names);
							if(obj!= MISSING) {
								obj->dir_all();
								printf("\n\n caricamento riuscito con successo\n");
							}
							else{
								printf("\n\n caricamento non riuscito\n");
							}
						}
					}
					
				}
				break;
			}
			
			case 'b': case 'B': {			//qui la parte di esplorazione
				printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
				names[0]=1;
			}
				
							
						
			
		}
						
				
		//tutti gli altri casi
	
	}	while(sel!= 'z' && sel!= 'Z');
	
}
