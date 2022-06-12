/** Nama File : StackForChar.c
 *  Deskripsi : File body ADT BinaryTree
 * Author	  : Akmal FAqih 
*/
#include "BinaryTree.h"

/* Return true jika ekspresi tree kosong dan sebaliknya */
boolean IsEmptyTree(BinTree P){
  return (P == Nil);
}

/*Hasil Alokasi Ekspresi Tree menghasilkan address */
addressTree AlokasiTree(infotypeTree X){
  addressTree P;

  P = (addressTree)malloc(sizeof(treeNode));
  if (P != Nil){
    strcpy(Info(P),X);
    Left(P) = Nil;
    Right(P) = Nil;
  }
  return P;
}

/* Membuat agar sebuah tree punya anak */
void CreateTree(infotypeTree X, BinTree L, BinTree R, BinTree *P){
  *P=AlokasiTree(X);
	if(*P!=Nil) {
		strcpy(Info(*P),X);
	   	Left(*P)=L;
		Right(*P)=R;	
  }
}

/* Membuat sebuah ekspresi Node Tree baru tetapi belum ada anak */
void CreateNodeTree(BinTree *P, infotypeTree X){
 *P=AlokasiTree(X);
	if(*P!=Nil) {
		strcpy(Info(*P),X);
	    Left(*P)=Right(*P)=Nil;
	} 
} 

/* Mengkonversi string menjadi float */
float StringToFloat(String X){
  return atof(X);
}

/* Mengembalikan nilai prioritas dari sebuah operator (semakin besar nilai, prioritas semakin diutamakan) */
int Priority(char x){
  switch(x){
    case ')' : return 0;
    case '(': return 0;
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case 'x': return 2;
    case '/': return 2;
    case ':': return 2;
	case '^': return 3;   
    case 'v': return 3;
  }
}

boolean isPriority(char a, char b){ //char a top
  return (Priority(a) >= Priority(b));
} 

/* Return true jika karakter yang dicek atau diperiksa merupakan sebuah operator */
boolean isOperator(char c){
  return(c=='+' || c=='-' || c=='*' || c=='x' || c=='/' || c ==':' || c =='^' || c=='v');
}

