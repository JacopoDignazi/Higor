#ifndef MOD_CLASS_H
#define MOD_CLASS_H
							//SISTEMA IN MOD LOGISTIC I COMPORTAMENTI IN SET DEF (ELIMINA VUOTI E RICOLLEGA GLI UP)
#include "mod_logistic.h"

//RICERCA OGGETTI E STRUTTURE NEL PROGRAMMA
mod_ogg* search(char* name, mod_strutt* here){
	int i;
	static char this_name[100]; 	//static per risparmio memoria
	strcopy( UNDEF(ADAPTED(name)), this_name); 
	for(i=1; i<=(here->N_ogg); i++){
		if( streq( UNDEF(here->ogg[i]->name), this_name) ) {		//li cerca entrambi eventualmente indefiniti	
			return here->ogg[i]; 
		}
	}	
	return MISSING;	
}
	inline	mod_ogg* search(mod_ogg* obj , mod_strutt* here){
		return search(obj->name, here);} 
	inline mod_ogg* search(const char* name_const , mod_strutt* here){
		return search((char*) name_const, here);}
		
mod_strutt* search_strutt(char* name, mod_struttgroup* in_group= IN_ALL_PROGRAM){
	int i;
	static char this_name[100]; 
	strcopy( ADAPTED(name), this_name, SIZENAME);
	for(i=0; i<=(in_group->N_strutt); i++){
		if( streq(in_group->strutt[i]->name, this_name) ){
			return in_group->strutt[i];
		}
	}
	return MISSING_STRUTT;
}
	
	mod_ogg* search(char* name_obj, char* name_strutt){				//overload con il nome della struttura invece che un puntatore
		mod_strutt* found_strutt= search_strutt(name_strutt);
		if(found_strutt== MISSING_STRUTT){ printf(" modello non trovato\n\n");}
		else{ return search(name_obj, found_strutt);}
	}
	mod_ogg* search(mod_ogg* obj, char* name_strutt){			
		mod_strutt* found_strutt= search_strutt(name_strutt);
		if(found_strutt== MISSING_STRUTT){ printf(" modello non trovato\n\n");}
		return search(obj, found_strutt);
	}

//AGGIUNTA DI OGGETTI ALLE STRUTTURE COSTRUITE-per ora non mi serve l'aggiunta delle strutture ai gruppi			
int add_ogg(char* this_name, mod_strutt* in_strutt){
	if( search(this_name, in_strutt) !=  MISSING) return alredy_done;			//se c'è già nella struttura
	if(in_strutt->N_ogg >= MAXSIZESTRUTT) return oversizing;					//se la struttura non ha capienza sufficiente
		mod_ogg* supp= search(this_name);		//lo cerca globalmente e al limite restituisce missing
	if( supp != MISSING){						//in caso lo trovi allora lavoro su quello
		if(supp->N_strutt >= MAXNSTRUTT) return oversizing;
		if(in_strutt != Global){
			supp->strutt_above[++(supp->N_strutt)]= in_strutt;
			in_strutt->ogg[++(in_strutt->N_ogg)]= supp;	
		}
	}
	else{
		new mod_ogg( this_name, in_strutt); 	//sennò se non lo trova allora lo creo e lo metto già dentro la struttura (oltre che in global)
	}
	in_strutt->order();
	return done;
}
	inline int add_ogg(mod_ogg* this_obj, mod_strutt* in_strutt){
		return add_ogg((this_obj->name), in_strutt);}
	inline int add_ogg(const char* this_name, mod_strutt* in_strutt){
		return add_ogg((char*)this_name, in_strutt);}
	
	int add_ogg(char* obj_name, char* strutt_name){
		mod_strutt* found_strutt= search_strutt(strutt_name);
		if(found_strutt== MISSING_STRUTT){ //printf(" modello non trovato\n\n");}
			found_strutt= new mod_strutt(strutt_name);
		}
		return add_ogg(obj_name, found_strutt);
	}
	int add_ogg(mod_ogg* obj, char* strutt_name){
		mod_strutt* found_strutt= search_strutt(strutt_name);
		if(found_strutt== MISSING_STRUTT){ //printf(" modello non trovato\n\n");}
			found_strutt= new mod_strutt(strutt_name);
		}
		return add_ogg(obj, found_strutt);
	}
				

//RIMUOVERE GLI OGGETTI DALLE STRUTTURE
int remove_ogg(char* name_ogg, mod_strutt* strutt){
	mod_ogg* suppogg= search(name_ogg, strutt);
	if( suppogg== MISSING) return not_possible;
	if( strutt== Global) return not_possible;
	
	int i;
	for(i=1; i<=suppogg->N_strutt; i++){
		if(suppogg->strutt_above[i]== strutt){
			suppogg->strutt_above[i]= NULL;
			--(suppogg->N_strutt);
			do{
				suppogg->strutt_above[i]=suppogg->strutt_above[i+1];
				i++;
			} while( suppogg->strutt_above[i] != NULL);
		}
	}
	for(i=1; i<=strutt->N_ogg; i++){
		if(strutt->ogg[i]== suppogg){
			strutt->ogg[i]= NULL;
			--(strutt->N_ogg);
			do{
				strutt->ogg[i]=strutt->ogg[i+1];
				i++;
			} while( strutt->ogg[i] != NULL);
		}
	}
	return done;
}
	int remove_ogg(char* obj_name, char* strutt_name){
		mod_strutt* found_strutt= search_strutt(strutt_name);
		if(found_strutt == MISSING_STRUTT) printf(" modello non trovato");
		else{ return remove_ogg(obj_name, found_strutt);}
	}
	inline int remove_ogg(mod_ogg* obj, mod_strutt* strutt){
		return remove_ogg(obj->name, strutt);}
	int remove_ogg(mod_ogg* obj, char* strutt_name){
		mod_strutt* found_strutt= search_strutt(strutt_name);
		if(found_strutt == MISSING_STRUTT) printf(" modello non trovato");
		else{ return remove_ogg(obj, found_strutt);}
	}
		
//COLLEGA GLI OGGETTI	
	int link_ogg(char* name1, char* name2){
		mod_ogg*supp1=search(name1); if(supp1== MISSING) return not_possible;			//se non esistono
		mod_ogg*supp2=search(name2); if(supp2== MISSING) return not_possible;
		char suppname1[SIZESURE]; strcopy( supp1->name, suppname1, SIZENAME);
		char suppname2[SIZESURE]; strcopy( supp2->name, suppname2, SIZENAME);
		int i;
		for(i=1; i<= supp1->N_equiv; i++){
			if (streq( UNDEF(supp1->equivalent_ogg[i]->name), suppname2) ) return alredy_done;			//se sono già collegati
		}
		if(supp1->N_equiv >= MAXEQOGG || supp2->N_equiv >= MAXEQOGG) return oversizing; 				//se uno dei due è gia troppo collegato
		supp1->equivalent_ogg[++(supp1->N_equiv)]=supp2;
		supp2->equivalent_ogg[++(supp2->N_equiv)]=supp1;
		return done;
	}

/////SETTAGGI	


/*	void mod_ogg::set_name(char* new_name){ 
		if (this->grade==-1) strcopy(UNDEF(ADAPTED(new_name)), name);
		else strcopy(ADAPTED(new_name), name);
		
		int i;
		for(i=1; i<=N_up; i++){
			up_ogg[i]->set_def(up_ogg[i]->def);
		}
		//gli faccio chiamare il node order degli oggetti up
	} */ //NB cambiare i nomi è un casino perché poi dovrei stare a risettare tutti i collegamenti giusti da parte di eventuali oggetti up

	void mod_strutt::set_name(char* new_name){ 
		strcopy(ADAPTED(new_name), name);
	}	
	void mod_ogg::set_comment(char* new_comment, char mode= 'n'){
		if( mode== 'a'){
			int lngcomment= strlng(comment);
			strcopy(new_comment, &comment[lngcomment+1], SIZECOMM-lngcomment);
		}
		else {
			strcopy(new_comment, comment, SIZECOMM);
		}
	}

	void mod_strutt::set_comment(char* new_comment, char mode= 'n'){
		if( mode== 'a'){
			int lngcomment= strlng(comment);
			strcopy(new_comment, &comment[lngcomment+1], SIZECOMM-lngcomment);
		}
		else {
			strcopy(new_comment, comment, SIZECOMM);
		}
	}	
	
	void mod_ogg::set_def(char* new_def, mod_strutt* into_strutt= Global/*, char mod= 'n'*/){
	//	printf("dentro setdef");
		int i, j;
		for(i=1; i<= N_down; i++){			
			for(j=1; j<= down_ogg[i]->N_up; j++){
				if( down_ogg[i]->up_ogg[j] == this ){			//calcello il collegamento con i down_ogg
					down_ogg[i]->up_ogg[j]=   NULL;			
					do{
						down_ogg[i]->up_ogg[j]=down_ogg[i]->up_ogg[j+1];
						++j;
					} while	(j<= down_ogg[i]->N_up);
					down_ogg[i]->up_ogg[j]= NULL;
					(down_ogg[i]->N_up)-=1;			
				}												//e prima di ridefinire annullo tutti i down_ogg dell'oggetto
			}
			down_ogg[i]=NULL;	
		}
		N_down=0;
		strcopy(new_def, def, SIZEDEF);	
			
		char c; char found_name[SIZESURE];
		j=0; i=0; 
		while( (c=def[i])!= '\n' && c!= '\0'){
			if(c <= 'Z' && c >= 'A' ){
				j=0;
				while((c=def[i++])!= '\n' && c!= '\0' && ((c<= 'Z' && c>= 'A')|| c== '_' ) ){
					found_name[j++]=c;
				}
				found_name[j]='\0';		//carattere di fine stringa
				//strcopy(found_name, found_name, SIZENAME);		//taglio se proprio è troppo lungo
				add_down(found_name, into_strutt);																									
				i--; 	//torna indietro o salta un carattere
				j=0;
			}
			i++;
			if(c== '\n' || c=='\0') break;
		}
		
		node_order();
	}

	
//////INTERFACCIA	

		//sistemare formattazione interfaccia
	void mod_ogg::dir(){
		if(this== MISSING) {printf("\t MISSING\n\n"); return;}
		int space= printf("\n\n ******************** %s **********************\n\n", name) -4;
		printf("  grado: %d\n  N_down: %d\n  N_up: %d\n  N_strutt: %d\n  N_equiv= %d\n\n   def: %s\n   com: %s", grade, N_down, N_up, N_strutt, N_equiv, def, comment);
		printf("\n\n "); spazagg(space, '*'); printf("\n\n");
	}
			
	void mod_strutt::dir(){
		int space= printf("\n\n ****************** structure: %s ********************\n\n", this==Global? "PROGRAM": name) -4;
		printf("  estensione: %d - %d\n   N_ogg: %d\n\n     comm: %s", grade_min, grade_max, N_ogg, comment);
		printf("\n\n "); spazagg(space, '*'); printf("\n\n");
	}
	

	void mod_ogg::dir_all(){
		if(this== MISSING) {printf("\t MISSING\n\n"); return;}
		int space= printf("\n\n ************************* object %s ***************************\n\n", name) -4;
		printf("  grado: %d\n  N_down: %d\n  N_up: %d\n  N_strutt: %d\n  N_equiv= %d\n\n   def: %s\n   com: %s", grade, N_down, N_up, N_strutt, N_equiv, def, comment);
		int i, suppspace;
		for(i=1; i<=N_down; i++){
			suppspace= printf("\n    %d)__%s",  i, down_ogg[i]->name); 
			spazagg(55-suppspace, '_');
			if(down_ogg[i]->grade != -1) {printf("_grade:_%d", down_ogg[i]->grade);}
			else printf("___undefined");
		}
		printf("\n\n "); spazagg(space, '*'); printf("\n\n");
	}
			
	void mod_strutt::dir_all(){
		int space= printf("\n\n ***********************%s%s *************************\n\n", this==Global? " ":" model ", this==Global? "IN ALL PROGRAM": name)-4; 
		int i, suppspace;
		for(i=1; i<=N_ogg; i++){
			suppspace=printf("\n   %d)__%s", i, ogg[i]->name); 
			spazagg(55-suppspace, '_'); 
			if(ogg[i]->grade != -1) {printf("_grade:_%d", ogg[i]->grade);}
			else {printf("___udefined");}
		}
		printf("\n\n "); spazagg(space, '*'); printf("\n\n");
	}
		
	void mod_struttgroup::dir(){
		int i;
		if(this==IN_ALL_PROGRAM) printf("\n\n ...loaded IAP: ");
		else printf("\n\n ...loaded in %s", this->name);
		for(i=(this==IN_ALL_PROGRAM? 0:1); i<=N_strutt; i++){
			printf("\n    ! %d) model: %s, %d-%d  %d", i, strutt[i]->name, strutt[i]->grade_min, strutt[i]->grade_max, strutt[i]->N_ogg);
		}
		printf("\n\n");
	}

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
	
//	printf("\n sono dentro loadmacro");
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
		//printf("n%c", c);
	}	//NOME
	suppstring[i]='\0';

	mod_ogg* temp=search(suppstring);			
	if(temp!= MISSING) {
		//printf("\n trovato oggetto con questo nome\n");	
				//ad esempio potrei semplicemente ridefinire le definizioni di quel temp e poi cancellare questo oggetto
									//certo sovrascriverei la definizione precedente, bon in caso metto un avviso
	}
	else{
		temp=new mod_ogg(suppstring);
	}
													
	i=0;
	while( (c=getc(fip)) != ':');
	while( (c=getc(fip)) != '\n')  {suppstring[i++]=c;}//	printf("d%c", c);}//DEFINIZIONE
	if(i!=0){
		suppstring[i]='\0';
		temp->set_def(suppstring);
	}
	else{
	}		//se serve
	
	i=0;
	while( (c=getc(fip)) != ':');
	while( (c=getc(fip)) != '\n') {suppstring[i++]=c;}// 		printf("c%c", c);}//COMMENTO
	if(i!=0){
		suppstring[i]='\0';
		temp->set_comment(suppstring);
	}
	
	while(getc(fip)!= '.'); //printf("\n\nsta cercando il punto"); 
	
																					/*	for(i=1; i<=N_group; i++){
																							fprintf(fop, "\n (%s)", group[i]->name);
																						}
																						fprintf(fop, "\n %c1\n", MARK_STRUCT);*/
	
	while(1){
		while(getc(fip) != '\n');
		while( (c=getc(fip)) != '(' && c!= MARK_OBJ);
		if (c=='('){
			i=0;
			while( (c=getc(fip)) != ')') {suppstring[i++]=c;}
			suppstring[i]='\0';
			add_ogg(temp, suppstring);
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
	return load_newobj(fip); 
}
	
	
	//un save e un load per quando chiamato da una struttura (che non sta ad aprire un file ma lavora continuando su uno che gli viene dato)
	//la struttura ha un save per i dati di struttura e basta
		//e un save_all per salvare anche gli oggetti e i loro dati
			//questa funzione chiama mod_ogg::save_from();

int mod_strutt::saving(FILE* fop, char mode='n'){
	
	fprintf(fop, "\n%c0\n name:%s\n comm:%s\n.", MARK_STRUCT, name, comment);	
	int i;
	for(i=1; i<=N_group; i++){
		fprintf(fop, "\n (%s)", group[i]->name);
	}
	fprintf(fop, "\n %c1\n", MARK_STRUCT);
	
	fprintf(fop, "\n {\n");
	for(i=1;i<=N_ogg; i++){
					//se trovo mark_struct allora continuo, se trovo '}' allora mi fermo
		fprintf(fop, "\n%c", MARK_STRUCT);
		ogg[i]->saving(fop);			
	}
	
	fprintf(fop, "\n}");	
	return done;
}
	

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
		fop= fopen(namefile, "w");
	}
	saving(fop);
	fclose(fop);
	
		
}

mod_strutt* load_newstrutt(FILE* fip, char mode='n'){
	char c; 
	int i=0;
	char suppstring[1200];
	
	while ( (c=getc(fip))!= MARK_STRUCT){
		if(c== MARK_OBJ) {printf("\n questo file contiene un singolo oggetto\n"); return MISSING_STRUTT;}
		if(c== MARK_GROUP) {printf("\n questo file contiene un gruppo\n"); return MISSING_STRUTT;}
		if(c== '{' || c== '}') {printf("\n questo file contiene un gruppo di oggetti\n"); return MISSING_STRUTT;}
	}
	if(getc(fip) != '0') {printf("\n errore nella lettura del file\n"); return MISSING_STRUTT;}
		
	while(getc(fip) != ':');
	while( (c=getc(fip)) != '\n') {
		if(c== ' ') continue;
		suppstring[i++]=c;
	}	///////////////////////NOME
	suppstring[i]='\0';

	mod_strutt* temp=search_strutt(suppstring);			
	if(temp!= MISSING_STRUTT) {
		//printf("\n trovato oggetto con questo nome\n");	
				//ad esempio potrei semplicemente ridefinire le definizioni di quel temp e poi cancellare questo oggetto
									//certo sovrascriverei la definizione precedente, bon in caso metto un avviso
	}
	else{
		temp=new mod_strutt(suppstring);
	}
													
	i=0;
	while( (c=getc(fip)) != ':');
	while( (c=getc(fip)) != '\n')  {suppstring[i++]=c;	}//	printf("c %c",c);	} //COMMENTO	
	if(i!=0){
		suppstring[i]='\0';
		temp->set_comment(suppstring);
	}
	
	while(getc(fip)!= '.'); //printf("\n\nsta cercando il punto"); 
	
	while(1){
		while(getc(fip) != '\n');
		while( (c=getc(fip)) != '(' && c!= MARK_STRUCT);// printf("\nabouttoend %c",c);
		if (c=='('){
			i=0;
			while( (c=getc(fip)) != ')') {suppstring[i++]=c;}
			suppstring[i]='\0';
			//QUI CI VA IL PEZZO IN CUI AGGIUNGO IL GRUPPO ALLA STRUTTURA CHE PER ORA NON HO MESSO (tipo add_strutt(strutt, group) etc etc
		}
		if (c== MARK_STRUCT) {
			if (getc(fip)=='1'){
				while(getc(fip)!='\n');
				goto loading_objects;		//ritorno giusto
			}
			else{ 
				printf("\n errore a fine lettura delle implementazioni di struttura in gruppi\n");
				return MISSING_STRUTT;
			} 
		}
	}
	
	loading_objects:							
																			/*fprintf(fop, "\n {\n");
																			for(i=1;i<=N_ogg; i++){
																							//se trovo mark_struct allora continuo, se trovo '}' allora mi fermo
																				fprintf(fop, "\n%c", MARK_STRUCT);
																				ogg[i]->saving(fop);			
																			}
																			
																			fprintf(fop, "\n}");*/											
	while( (c=getc(fip))!= '{'){
		if(c==MARK_OBJ || c== MARK_STRUCT) 	{
			printf("\n\n errore nella lettura delle implementazioni di oggetti in file di struttura\n\n\a");
			return MISSING_STRUTT;
		}
		if(c==MARK_STRUCT) {
			printf("\n\n FILE DI LETTURA SCOORDINATO, missing mark_{ before MARK_STRUCT\n\n\a");
			return MISSING_STRUTT;
		}
	}
	//qui inizia la parte di lettura degli oggetti
	while((c=getc(fip))!=MARK_STRUCT || c!= '}'){
		if(c== MARK_STRUCT){
			load_newobj(fip);
		}
		if(c== '}'){
			return temp;
		}
	}
}

mod_strutt* load_newstrutt(char* namefile, char mode='n'){
	int namelenght= strlng(namefile);
	if(namefile[namelenght-1]!= 't' || namefile[namelenght-2]!= 'x' || namefile[namelenght-3]!= 't' || namefile[namelenght-4]!='.') {
		strcopy(".txt", &namefile[namelenght]);
	}
	
	//controllo che io non stia sovrascrivendo un file
	//eventualmente gli faccio cancellare tutto quel che c'è e ricominciare l'intero file NB MEGLIO DI NO MEGLIO NON FAR CASINI
	//eventualmente faccio si che si possa chiamare solo da oggetti pseudovuoti o con lo stesso nome
	FILE* fip= fopen(namefile, "r");
	if(fip== NULL) {printf("\n file non trovato\n"); return MISSING_STRUTT;}
	return load_newstrutt(fip); 
}
		

	
#endif	

