#include <stdio.h>

void lettcha(char &c){
	char supp;
	while((supp=getchar())!='\n') c=supp;
}

template <typename T> void spazagg(T n, char c=' '){
	int i;
	for(i=1; i<=n; i++) printf("%c", c);
}


bool streq(char str1[], char str2[]){
	long unsigned i=0;
	
	while(str1[i]==str2[i]){
		if(str1[i]=='\0') return 1;
		i++;
	}
	return 0;
}

bool streq(const char* str1, const char* str2){
	long unsigned i=0;
	
	while(str1[i]==str2[i]){
		if(str1[i]=='\0') return 1;
		i++;
	}
	return 0;
}

int strlng(char* str){
	int cont=0;
	while(str[cont]!= '\0') ++cont;
	return cont;
}
inline int strlng(const char* str){
	return strlng((char*) str);}


void strcopy( char* str1, char* str2){				//NON SONO SICURI CONTRO PUNTATORI A STRINGHE COSTANTI
	int i=0;
	do{
		str2[i]=str1[i];
		++i;	
	} while(str1[i] != '\0');
	str2[i]= '\0';
}
inline void strcopy(const char* str1, char* str2){
	strcopy((char*) str1, str2);}
	

void strcopy( char* str1, char* str2, int sizemax){				//NON SONO SICURI CONTRO PUNTATORI A STRINGHE COSTANTI
	int i=0;
	do{
		str2[i]=str1[i];
		++i;	
	} while(str1[i] != '\0' && i<sizemax-2);
	str2[i]= '\0';
}


void addchar(char* str, char add=15){			//NB NON E SICURO CONTRO PUNTATORI A STRINGHE COSTANTI
	static char support[2000];
	strcopy(str, support);
	str[0]=add;	
	strcopy(support, str+1);

}
inline void addchar(const char* str, char add=15){
	printf("CASINO NON POSSO SCRIVERE SU COSTANTI"); }
	
char* addedchar_if(char* to_string, char add){//<------con che carattere undefined obj
	static char supp[2000];
	if(to_string[0] == add) {strcopy(to_string, supp);}
	else{ 
		supp[0]=add;
		strcopy(to_string, supp+1);
	}
	return supp;	
}
inline char* addedchar_if(const char* to_string, char add){
	addedchar_if((char*) to_string, add); }
	
void caps_lock_full(char* string, char fuller= ' '){
	int i=0;
	char c;
	while( (c=string[i]) != '\0'){
		if(c<= 'z' && c>= 'a') string[i]+=('A'-'a');
		if(c == ' ') string[i]=fuller;
		i++;
	}
} 	
inline void caps_lock_full(const char*, char fuller= ' '){
	printf(" CASINO QUESTO E COSTANTE"); }
	
template <int size> char* get_text_until(char* into, char ending_char= '\n', int max=size){
	char supp[size+2];
	int i=0; char c=1;
	while( (c=getchar()) != ending_char && i<size){
		supp[i++]=c;
	} 
	supp[i]= '\0';
	strcopy(supp, into, max>size? size:max);
	if(ending_char != '\n'){ while(getchar()!= '\n');}	//pulizia buffering se ci sono rimaste robe
}

