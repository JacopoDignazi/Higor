#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef SUPP_CHA_H
#include "supp_cha.h"
#define SUPP_CHA_H
#endif

#include "mod_definings.h"
 
class mod_strutt;
class mod_struttgroup;

class mod_ogg{
		
	char name[SIZENAME] ;
	char def[SIZEDEF] ;//= " non definito ";
	char comment[SIZECOMM]; //= " non definito ";
		
	mod_ogg *down_ogg[MAXDOWNOGG+1];
	mod_ogg *up_ogg[MAXUPOGG+1];
	mod_strutt *strutt_above[MAXNSTRUTT+1];
		
	mod_ogg *equivalent_ogg[MAXEQOGG+1];
	
	int grade=-1; 
	int N_down=0;
	int N_up=0; 
	int N_strutt=0;
	int N_equiv=0;
	
	mod_ogg();	
	mod_ogg(char* in_name, mod_strutt* );		//gli devo passare un puntatore o con il nome serve una sovrasovrastruttura
	mod_ogg(char* in_name, mod_strutt*, char* in_def, char* in_comment= NULL);
	int loading(FILE*, char mod);
	int loading(char* name_file, char mode);
	
	int add_down(char*, mod_strutt*);
	void add_up(char* name_down);

	void searching_indef();
	void order_and_grading();
	void node_order(); 
	
	public:
		
		friend mod_strutt;
		friend mod_struttgroup;
		friend mod_ogg* search(char*, mod_strutt*); 
		friend mod_ogg* search(mod_ogg*, mod_strutt*); 
		friend int add_ogg(char*, mod_strutt*);
		friend int add_ogg(mod_ogg*, mod_strutt*);
		friend int remove_ogg(char*, mod_strutt*);
		friend int remove_ogg(mod_ogg*, mod_strutt*);		
		friend int link_ogg(char* name1, char* name2);
		friend mod_ogg* load_newobj(FILE*, char);
		friend mod_ogg* load_newobj(char*, char);
			
		char* get_name(){ return name;} 
		char* get_def(){ return def;}
		char* get_comment(){ return comment;}
		
		void set_name(char* in_name);
		void set_def(char* new_def, mod_strutt* adding_in_strutt);
		void set_comment(char* in_comment, char mode);

	
		void dir();	
		void dir_all();
		
		int saving(FILE*, char mod);
		int saving(char* name_file, char mode);

};

mod_ogg::mod_ogg(){ 
			strcopy("missing", name); 
			strcopy("---", comment);
			strcopy("---", def);  
		}
		
//mod_ogg* Voidobj= new mod_ogg();
