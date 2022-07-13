#ifndef MOD_SAVINGS_H
#define MOD_SAVINGS_H

#ifndef MOD_CLASS_H
#define MOD_CLASS_H
#include "mod_class.h"	
#endif



////////SALVATAGGI	
#define MARK_OBJ '*'
#define MARK_STRUCT '$'
#define MARK_GROUP '£'


int mod_ogg::saving(FILE* file_into, char mod='n'){
	
	fprintf(file_into, "\n%c0\nname:%s\n def:%s\n comm:%s\n.", MARK_OBJ, name, def, comment);
	
	int i;
	for(i=1; i<=N_strutt; i++){
		fprintf(file_into, "\n (%s)", strutt_above[i]->name);
	}
	
	fprintf(file_into, "\n %c1\n", MARK_OBJ);

	return done;
	
}

int mod_ogg::saving(char* namefile, char mod='n'){				//salva tra 0* e 1*, con marker per definizione e commento
	
	FILE* fop;
	
	if(mod != 'a'){
		if(streq((char*)"auto", namefile)) strcopy(this->name, namefile);
		int namelenght= strlng(namefile);
		if(namefile[namelenght-1]!= 't' || namefile[namelenght-2]!= 'x' || namefile[namelenght-3]!= 't' || namefile[namelenght-4]!='.') {
			strcopy(".txt", &namefile[namelenght]);
		}
		if(mod== 'n') {fop= fopen(namefile, "w");}
		else{		/*()*/
			fop= fopen(namefile, "w");
		}//altre modalità?
	}
/*	else if(mod== 'a') {
		if( streq((char*)"auto", namefile) ) {printf("\n qualche genere di errore\n"); return not_possible;}
		fop= fopen(namefile, "a");			//la struttura glie lo passa già txtato
	}*/ //altre modalit non è detto che mi servano
	
	saving(fop);
	fclose(fop);
	
	return done;	
	
}


mod_ogg* load_newobj(FILE* fip, char mode='n'){
	
	char suppstring[1200]; int i=0;
	char c;
	
	printf("\n sono dentro loadmacro");
	while ( (c=getc(fip))!= MARK_OBJ){
		if(c== MARK_STRUCT) {printf("\n questo file contiene una struttura\n"); return MISSING;}
		if(c== MARK_GROUP) {printf("\n questo file contiene un gruppo\n"); return MISSING;}
		if(c== '{' || c== '}') {printf("\n questo file contiene un gruppo di oggetti\n"); return MISSING;}
	}
	if(getc(fip) != '0') {printf("\n errore nella lettura del file\n"); return MISSING;}
	
												//fprintf(file_into, "\n%c0\nname:%s\n def:%s\n comm:%s\n.", MARK_OBJ, name, def, comment);
	
	while(getc(fip) != ':');
	while( (c=getc(fip)) != '\n') {
		if(c== ' ') continue;
		suppstring[i++]=c;
		printf("n%c", c);
	}	//NOME
	suppstring[i]='\0';

	mod_ogg* temp=search(suppstring);			
	if(temp!= MISSING) {
		printf("\n trovato oggetto con questo nome\n");	
				//ad esempio potrei semplicemente ridefinire le definizioni di quel temp e poi cancellare questo oggetto
									//certo sovrascriverei la definizione precedente, bon in caso metto un avviso
	}
	else{
		temp=new mod_ogg(suppstring);
	}
													
	i=0;
	while( (c=getc(fip)) != ':');
	while( (c=getc(fip)) != '\n')  {suppstring[i++]=c;		printf("d%c", c);}//DEFINIZIONE
	if(i!=0){
		suppstring[i]='\0';
		temp->set_def(suppstring);
	}
	else{
	}		//se serve
	
	i=0;
	while( (c=getc(fip)) != ':');
	while( (c=getc(fip)) != '\n') {suppstring[i++]=c; 		printf("c%c", c);}//COMMENTO
	if(i!=0){
		suppstring[i]='\0';
		temp->set_comment(suppstring);
	}
	
	while(getc(fip)!= '.') printf("\n\nsta cercando il punto"); 
	
																					/*	for(i=1; i<=N_group; i++){
																							fprintf(fop, "\n (%s)", group[i]->name);
																						}
																						fprintf(fop, "\n %c1\n", MARK_STRUCT);*/
	
	while(1){
		while(getc(fip) != '\n');
		while( (c=getc(fip)) != '(' && c!= MARK_OBJ) ;//printf("abouttoend %c",c);;
		if (c=='('){
			i=0;
			while( (c=getc(fip)) != ')') {suppstring[i++]=c;}
			suppstring[i]='\0';
			add_ogg(temp, suppstring);
			printf("aggiuntaastruttura");
		}
		if (c== MARK_OBJ) {
			if (getc(fip)=='1'){
				while(getc(fip)!='\n');
				return temp;		//ritorno giusto
			}
			else{ 
				printf("\n errore a fine lettura del file\n");
				return MISSING;
			} //ritorno numero di errore
		}
	}	
}
			
mod_ogg* load_newobj(char* namefile, char mod='n'){
	int namelenght= strlng(namefile);
	if(namefile[namelenght-1]!= 't' || namefile[namelenght-2]!= 'x' || namefile[namelenght-3]!= 't' || namefile[namelenght-4]!='.') {
		strcopy(".txt", &namefile[namelenght]);
	}
	
	//controllo che io non stia sovrascrivendo un file
	//eventualmente gli faccio cancellare tutto quel che c'è e ricominciare l'intero file NB MEGLIO DI NO MEGLIO NON FAR CASINI
	//eventualmente faccio si che si possa chiamare solo da oggetti pseudovuoti o con lo stesso nome
	FILE* fip= fopen(namefile, "r");
	if(fip== NULL) {printf("\n file non trovato\n"); return MISSING;}
	printf("sto per entrare in loadmacro");
	return load_newobj(fip); 
}
	
	/*
	
	mod_ogg* temp= new mod_ogg((char*)"temp", Global);
	if(temp->loading(fip)!= done){
		delete temp;
		return MISSING;
	}
	else return temp;
	*/
/*
mod_ogg::loading(FILE* fip, char mod= 's'){
/*	int namelenght= strlng(namefile);
	if(namefile[namelenght-1]!= 't' || namefile[namelenght-2]!= 'x' || namefile[namelenght-3]!= 't' || namefile[namelenght-4]!='.') {
		strcopy(".txt", &namefile[namelenght]);
	}
	
	//controllo che io non stia sovrascrivendo un file
	//eventualmente gli faccio cancellare tutto quel che c'è e ricominciare l'intero file NB MEGLIO DI NO MEGLIO NON FAR CASINI
	//eventualmente faccio si che si possa chiamare solo da oggetti pseudovuoti o con lo stesso nome
	FILE* fip= fopen(namefile, "r");	*/
//suppongo di ricevere gia un file dalla funzione friend load_newobj
/*
	char suppstring[1200]; int i=0;
	char c;
	
	while (getc(fip)!= MARK_OBJ);
	if(getc(fip) != '0') {printf("errore nella lettura del file"); return loading_error_infile;}
	while(getc(fip) != ',');
	
	while( (c=getc(fip)) != ':') {printf("n%c",c);suppstring[i++]=c;}	//NOME
	suppstring[i]='\0';

	mod_ogg* temp=search(suppstring);
	if(temp!= MISSING) {
		printf("\n trovato un altro file con lo stesso nome, \n per ora e' impossibile procedere, poi casomai aggiungo altre funzioni");
		return not_possible;		//ad esempio potrei semplicemente ridefinire le definizioni di quel temp e poi cancellare questo oggetto
									//certo sovrascriverei la definizione precedente, bon in caso metto un avviso
	}
	
	strcopy(suppstring, name, SIZENAME);
	
	i=0;
	while( (c=getc(fip)) != '\n')  {printf("d%c",c); suppstring[i++]=c;}//DEFINIZIONE
	if(i!=0){
		suppstring[i]='\0';
		set_def(suppstring);
		printf("\n definizione ok");
	}
	else{
	}		//se serve
	
	i=0;
	while( (c=getc(fip)) != '\n') {printf("c%c",c); suppstring[i++]=c;}//COMMENTO
	if(i!=0){
		suppstring[i]='\0';
		set_comment(suppstring);
	}
	
	while(getc(fip)!= '.') printf("sta cercando il punto"); 
	
	while(1){
		while(getc(fip) != '\n');
		while( (c=getc(fip)) != ')' && c!= MARK_OBJ) ;//printf("abouttoend %c",c);;
		if (c==')'){
			i=0;
			while( (c=getc(fip)) != '(') suppstring[i++]=c;
			suppstring[i]='\0';
			add_ogg(this, suppstring);
		}
		if (c== MARK_OBJ) {
			if (getc(fip)=='1'){
				while(getc(fip)!='\n');
				return done;		//ritorno giusto
			}
			else{ return loading_error_infile;} //ritorno numero di errore
		}
	}
}*/
	//un save e un load per quando chiamato da una struttura (che non sta ad aprire un file ma lavora continuando su uno che gli viene dato)
	//la struttura ha un save per i dati di struttura e basta
		//e un save_all per salvare anche gli oggetti e i loro dati
			//questa funzione chiama mod_ogg::save_from();


int mod_strutt::saving(char* namefile, char mode= 'n'){
	
	FILE* fop;
	if(streq((char*)"auto", namefile)) strcopy(this->name, namefile);
	int namelenght= strlng(namefile);
	if(namefile[namelenght-1]!= 't' || namefile[namelenght-2]!= 'x' || namefile[namelenght-3]!= 't' || namefile[namelenght-4]!='.') {
		strcopy(".txt", &namefile[namelenght]);
	}
	if(mode== 'n') {fop= fopen(namefile, "w");}
	else{
		//omissis... altre eventualità da salvataggi di grossa portata
	}
	fprintf(fop, "\n%c0,%s;%s\n.", MARK_STRUCT, name, comment);	
	int i;
	for(i=1; i<=N_group; i++){
		fprintf(fop, "\n (%s)", group[i]->name);
	}
	fprintf(fop, "\n %c1\n", MARK_STRUCT);
	
	fprintf(fop, "\n {\n");
	for(i=1;i<=N_ogg; i++){
					//se trovo mark_struct allora continuo, se trovo '}' allora mi fermo
		fprintf(fop, "\n%c", MARK_STRUCT);
		ogg[i]->saving(fop);			//overloada con passaggio di puntatore a file e scrittura diretta senza aprire o chiuder nulla
	}
	
	fprintf(fop, "\n}");
	fclose(fop);
	
	return done;
		
}

	
#endif	
