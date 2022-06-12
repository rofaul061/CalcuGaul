/** Nama File : Kalkulator.h
 *  Deskripsi : File Header ADT Kalkulator
 */

#ifndef KALKULATOR_H
#define KALKULATOR_H
#define Nil NULL

#include "StackForTree.h"
#include <math.h>
#include <conio.h>

typedef char String[50];	//maksimal panjang infix,postfix
typedef char infotypeTree[10]; //
typedef struct treeNode *addressTree;
typedef addressTree Kalkulator;


/* Membuat sebuah ekspresi tree dari ekspresi postfix yang sudah didapatkan. 
 * I.S. : Postfix terdefinisi.
 * F.S. : Mengembalikan ekspresi tree.
*/
Kalkulator BuildExpressionTree(infotypeTree postfix);

/* Mengkonversi ekspresi infix menjadi ekspresi postfix.
 * I.S. : Infix terdefinisi.
 * F.S. : Infix berhasil dikonversi menjadi ekspresi postfix.
 */
void InfixToPostfix(String infix, String postfix);

/* Mengembalikan hasil kalkuasi dari ekspresi tree.
 * I.S. : P terdefinisi.
 * F.S. : Hasil kalkulasi dari P dikembalikan.
 */
float CalculationOfTree(Kalkulator P);

/* Modul untuk Ui OPening
 * I.S : Tampilan opening UI belum tampil
 * F.S : Tampilan Opening Ui sudah tampil
 */
void openingUi();

/* Menampilkan Main Menu
 * I.S : Tampilan main menu belum tampil
 * F.S : Main Menu Ditampilkan
 */
int mainMenu();

/* Menampilkan Menu kalkulator
 * I.S : Menu kalkulator belum tampil
 * F.S : Menu kalkulator sudah tampil
 */
void kalkulatorBasic();

/* Menampilkan Ui kalkulator*/
void uiKalkulator();

/* Menampilkan Aturan kalkulator
 * I.S : Aturan kalkulator belum tampil
 * F.S : Aturan kalkulator sudah tampil
 */
void ShowHowTo();

/* Menampilkan informasi mengenai pembuat aplikasi
 * I.S : informasi mengenai pembuat aplikasi belum tampil
 * F.S : informasi mengenai pembuat aplikasi sudah tampil
 */
void About();

/* Menampilkan Menu kalkulator spesial 
 * I.S : Menu kalkulator spesial belum tampil
 * F.S : Menu kalkulator spesial sudah tampil
 */
void kalkulatorspesial();

/* Menampilkan menu kalkulator Konverter massa
 * I.S : Menu kalkulator konverter massa belum tampil
 * F.S : Menu kalkulator konverter massa sudah tampil
*/
void MenuKonverterMassa();

/* Modul Untuk menghitung diskon
 * I.S : User menginput Harga dan Diskon
 * F.S : Menampilkan Hasil hitung diskon
 */
void kalkulatorDiskon();

/* Modul Untuk menutup seleuruh program
 * I.S : program belum ditutup seluruhnya
 * F.S : Progam sudah ditutup seluruhnya
 */
void Exit();

/* Modul untuk mengkonversi Kg menjadi Mg
 * I.S : Nilai Kg belum di definisikan
 * F.S : Nilai Kg dikonversi mejadi Mg
 */
void KgToMg();

/* Modul untuk mengkonversi Kg menjadi Gr
 * I.S : Nilai Kg belum di definisikan
 * F.S : Nilai Kg dikonversi mejadi Gr
 */
void KgTogr();

/* Modul untuk mengkonversi Gr menjadi Mg
 * I.S : Nilai Gr belum di definisikan
 * F.S : Nilai Gr dikonversi mejadi Mg
 */
void GrToMg();

/* Modul untuk mengkonversi Gr menjadi mg
 * I.S : Nilai Gr belum di definisikan
 * F.S : Nilai Gr dikonversi mejadi Kg
 */
void GrToKg();

/* Modul untuk mengkonversi Mg menjadi Kg
 * I.S : Nilai Mg belum di definisikan
 * F.S : Nilai Mg dikonversi mejadi Kg
 */
void MgtoKg();

/* Modul untuk mengkonversi Mg menjadi Gr
 * I.S : Nilai Mg belum di definisikan
 * F.S : Nilai Mg dikonversi mejadi Gr
 */
void MgToGr();


/* Modul yang berguna untuk menentukan koordinat
 * I.S : Koordinat belum dapat ditentukan sendiri
 * F.S : Dapat menentukan koordinat peletakan input/output
 */
void uiMassa();
void gotoxy(int x, int y);
void loading();
#endif
