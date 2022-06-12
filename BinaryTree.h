/** Nama File : StackForChar.c
 *  Deskripsi : File header ADT BinaryTree
 * Author	  : Akmal FAqih 
*/
#ifndef BINTREE_H
#define BINTREE_H

#define Nil NULL
#define Info(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right
#define Next(P) (P)->next

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StackForChar.h" 
#include "boolean.h"

typedef char String[50];
typedef char infotypeTree[10];
typedef struct treeNode *addressTree;
typedef struct treeNode {
			infotypeTree info;
			addressTree left;
			addressTree right;
		} treeNode;
typedef addressTree BinTree;

/* Return true jika ekspresi tree kosong dan sebaliknya */
boolean IsEmptyTree(BinTree P);

/*Hasil Alokasi Ekspresi Tree menghasilkan address */
addressTree AlokasiTree(infotypeTree X);

/* Membuat agar sebuah tree punya anak */
void CreateTree(infotypeTree X, BinTree L, BinTree R, BinTree *P);

/* Membuat sebuah ekspresi Node Tree baru tetapi belum ada anak */
void CreateNodeTree(BinTree *P, infotypeTree X);

/* Mengembalikan nilai prioritas dari sebuah operator (semakin besar nilai, prioritas semakin diutamakan) */
int Priority(char x);

/* Mengembalikan true jika operator1 memiliki prioritas yang lebih tinggi daripada operator2 */
boolean isPriority(char a, char b); 

/* Return true jika karakter yang dicek atau diperiksa merupakan sebuah operator */
boolean isOperator(char c);

/* Mengkonversi string menjadi float */
float StringToFloat(String X);

#endif
