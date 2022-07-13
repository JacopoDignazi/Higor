#include "mod_ogg.h"

class mod_struttgroup;

class mod_strutt{					//potrei anche privatizzare questi primi qui sotto
		
	char name[SIZENAME];
	char comment[SIZECOMM];
		
	mod_ogg* ogg[MAXSIZESTRUTT+1];
	
	mod_struttgroup* group[MAXGROUP+1]; 
		
	int N_ogg=0;			//non ci inserirsco l'oggetto vuoto
	int N_group=0;
	int grade_max=-1;
	int grade_min=-1;
	
	void order();//funzione per ordinare in grado gli oggetti e la struttura
	void tree();//funzione per sistemare i puntatori		//posso inglobare con quella sopra
	void tree_order();	

	mod_strutt();
	
	public:
			
		mod_strutt(char* in_name);
		
		friend mod_ogg;
		friend mod_struttgroup;
		friend mod_ogg* search(char*, mod_strutt*); 
		friend mod_ogg* search(mod_ogg*, mod_strutt*); 
		friend mod_strutt* search_strutt(char*, mod_struttgroup*);
		friend int add_ogg(mod_ogg*, mod_strutt*);
		friend int add_ogg(char*, mod_strutt*);	
		friend int remove_ogg(char*, mod_strutt*);
			
		char* get_name(){ return name;}
		char* get_comment(){ return comment;}
		
		void set_name(char* in_name);
		void set_comment( char* in_comment, char mode);	
				 
		void dir();
		void dir_all();
		
		int saving(char* name_file, char);
		int saving(FILE* fop, char);
/*		int loading_obj(FILE*, char mod);
		int loading_obj(char* name_file);
		int loading_all(FILE*, char mod);
		int loading_all(char* name_file);
		*/
};

mod_strutt::mod_strutt(){ 
	strcopy("GLOBAL", name); 		
	strcopy(" struttura generica di contenimento ", comment);		
}

class mod_struttgroup{				//unico oggetto per ora
	
	char name[SIZENAME];
	
	mod_strutt* strutt[MAXNSTRUTT];
	int N_strutt=0;
	
	friend mod_strutt;
	friend mod_ogg;
	friend mod_strutt* search_strutt(char*, mod_struttgroup*);
	
	public:
		
		mod_struttgroup();
		void dir();
		
		mod_strutt* global_strutt(){ return strutt[0];	}
		mod_ogg* missing_obj(){ return strutt[0]->ogg[0]; }
		
//		int saving_all(FILE*, char mod);
		int saving_all(char* name_file, char);
//		int loading_all(FILE*, char mod);
//		int loading_all(char* name_file);
};
//add_ogg(Voidobj, Global);

mod_struttgroup::mod_struttgroup(){
	
	strcopy("IN ALL PROGRAM", name);
	strutt[0]= new mod_strutt();
	strutt[0]->ogg[0]=new mod_ogg();
	strutt[0]->group[0]= this;		
	strutt[0]->ogg[0]->strutt_above[0]=strutt[0];
}

mod_struttgroup* IN_ALL_PROGRAM= new mod_struttgroup();



