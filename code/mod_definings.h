
#define MAXNSTRUTT 50
#define MAXDOWNOGG 10
#define MAXUPOGG 200
#define MAXEQOGG 10
#define MAXSIZESTRUTT 500
#define MAXGROUP 5

#define SIZENAME 50 
#define SIZEDEF 970
#define SIZECOMM 1000
#define SIZESURE SIZENAME+5
#define CHARUNDEF 15

#define Global IN_ALL_PROGRAM->global_strutt()
#define MISSING IN_ALL_PROGRAM->missing_obj()
#define MISSING_STRUTT NULL

#ifndef SUPP_CHA_H
#include "supp_cha.h"
#define SUPP_CHA_H
#endif


enum int_syst{ alredy_done, not_possible, oversizing, done, loading_error_infile, file_not_found};
//enum err_syst{ 

inline char* UNDEF(char* to_string) { return addedchar_if(to_string, CHARUNDEF); }

char* ADAPTED(char* string, int size= SIZENAME){			//se templatizzo supp_cha posso riscriverlo con puntatori a funzioni istanziate
	static char supp[2000];
	strcopy(string, supp, size);
	caps_lock_full(supp, '_');
	return supp;
}
inline char* ADAPTED(const char* string){
	return ADAPTED((char*) string);}
	
inline void GETTINGNAME(char* name_got){
	get_text_until <SIZENAME> (name_got);}
inline void GETTINGDEF(char* def_got){
	get_text_until <SIZEDEF> (def_got);}
inline void GETTINGCOMM(char* comm_got){
	get_text_until <SIZECOMM>(comm_got);}
	
