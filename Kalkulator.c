/** Nama File 	: Kalkulator.c
 *  Deskripsi 	: File Body ADT Kalkulator 
 *	Author		: Akmal Faqih Fachrezy 		(211524035)
 *				  Gian Sandrova				(211524043)
 *				  Rofa'ul Akrom Hendrawan 	(211524061)
 *  PIC			: 1. Akmal Faqih Fachrezy
 						-InfixToPostfix
						-BuildExpressionTre
						-CalculationOfTree
						-KalkulatorBasic
				  2. Gian Sandrova
				  		-KgtoMg
						-Kgtogr
						-GrtoMg
						-GrtoKg
						-MgtoKg
						-Mgtogr
						-MenuKonverterMassa
						-Exit
				  3. Rofa'ul Akrom Hendrawan
				  		- openingUi
						- mainMenu
						- uiKalkulator
						- ShowHowTo
						- About
						- kalkulatorspesial
						- kalkulatorDiskon
						- uiMassa
						- loading			  
 *
 **/
 
#include "Kalkulator.h"

/* Mengkonversi ekspresi infix menjadi ekspresi postfix.
 * I.S. : Infix terdefinisi.
 * F.S. : Infix berhasil dikonversi menjadi ekspresi postfix.
 */
void InfixToPostfix(String infix, String postfix){
	int i, ukuran, index = 0; //Ukuran ; panjangpostfix
	char tempChar;				//untuk menampung char operator
	StackChar temp;		
    
    NewStackChar(&temp);
    
    ukuran = strlen(infix);
    for(i = 0; i < ukuran; i++) {
        switch(infix[i]) {
        	case '.':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                postfix[index] = infix[i]; //jika operand, langsung dimasukkan
                index++;
                break;
            case '+':
            case '-':
            case '*':
            case 'x':
            case '/':
            case ':':
            case '^':
			case 'v':
                postfix[index] = ' '; //jika operator, diisi spasi 
                index++;            
                if(isEmptyStackChar(temp)){
                    AddStackChar(&temp,infix[i]); //jika stack kosong add stack untuk operator
                }
				else if(!isPriority(Info(Top(temp)),infix[i])){ //jika ispriority not true
                    AddStackChar(&temp,infix[i]);
                }
				else{
                    while(!isEmptyStackChar(temp)&&isPriority(Info(Top(temp)),infix[i])){ // ulangi selama stack tidak kosong dan isPriority true
                        DellStackChar(&temp,&tempChar); //hapus top						  //jika operator yang ingin dimasukan lebih kecil
                        postfix[index] = tempChar; 
                        index++;
                    }                
                    AddStackChar(&temp,infix[i]); //push ke top
                }
                break;
            case ')':
                while(!isEmptyStackChar(temp)&&Info(Top(temp))!='('){//ulangi selama stack tidak kosong dan top tidak samadengan "("
                    DellStackChar(&temp,&tempChar);
                    postfix[index] = tempChar;
                    index++;                    
                }
                DellStackChar(&temp,&tempChar);
                break;
            case '(':
                AddStackChar(&temp,infix[i]);
                break;
        }
    }
    while(!isEmptyStackChar(temp)) { //ulangi selama stack masih ada
        DellStackChar(&temp,&tempChar); //menghapus top
        postfix[index] = tempChar; 	//tempchar untuk menampung operator
        index++;                  
    }    
    postfix[index] = '\0';
}
  
BinTree BuildExpressionTree(infotypeTree postfix){
	int i = 0, j, k;
	StackTree StackTree;
	infotypeStackTree Delete;
	BinTree ExpressionTree, Right, Left;
	infotypeTree tempOperator, tempStr;
	
	NewStackTree(&StackTree);
	while(i < strlen(postfix)){
		//untuk operand
		if (!isOperator(postfix[i]) && postfix[i] != ' '){ // jika postfix ke i bukan operator dan tidak kosong
			j = 0;
			tempStr[j] = postfix[i]; //tempstr untuk menampung operand
			while(!isOperator(postfix[i+1]) && postfix[i+1] != ' '){ //ulangi selama postfix ke i+1 bkan operator dan tidak kosong
				tempStr[j+1] = postfix[i+1];						// untuk angka puluhan ratusan
				j++;
				i++;	
			}
			CreateNodeTree(&ExpressionTree, tempStr); //untuk membuat node baru berisi nilai dari tempStr
			for(k = 0; k < strlen(tempStr); k++) { //untuk mengosongkan tempStr
				tempStr[k] = ' ';
			}
			AddStackTree(&StackTree, ExpressionTree); //memasukkan node yang dibuat ke dalam stack
		}
		
		//untuk operator
		else if(postfix[i] != ' ') { 
			tempOperator[0] = postfix[i];
			CreateNodeTree(&ExpressionTree, tempOperator); //membuat node berisi nilai dari tempOperator
		
			Right = Info(Top(StackTree)); //mengambil top stack untuk dijadikan anak kanan
			DellStackTree(&StackTree, &Delete); //delete top
							 
			Left = Info(Top(StackTree)); //mengambil top stack untuk dijadikan anak kiri
			DellStackTree(&StackTree, &Delete); //delete top
			
			CreateTree(tempOperator, Left, Right, &ExpressionTree); //membuat tree dengan operator sebagai parent
			
			AddStackTree(&StackTree, ExpressionTree);  //push tree yg sudah jadi ke top
		}
		i++;					
	}
	ExpressionTree = Info(Top(StackTree));
	DellStackTree(&StackTree, &ExpressionTree);
	return ExpressionTree;
}

/* Mengembalikan hasil kalkuasi dari ekspresi tree.
 * I.S. : P terdefinisi.
 * F.S. : Hasil kalkulasi dari P dikembalikan.
 */
float CalculationOfTree(BinTree P){
    if(IsEmptyTree(P)) { //mengecek apakah expresi tree kosong
        return 0;  
	}
	//untuk leaf node
    else if(IsEmptyTree(Left(P)) && IsEmptyTree(Right(P))) { //jika dia tidak punya anak
    	//konversi dari char ke float
        return StringToFloat(Info(P));  
    }
  
	//rekursif 
    float left = CalculationOfTree(Left(P));  //untuk mencari leaf node kiri
    float right = CalculationOfTree(Right(P));  //untuk mencari leaf node kana
    
    if(strcmp(Info(P),"+")==0) {
		return left+right;
	}
	else if(strcmp(Info(P),"-")==0) {
		return left-right;
	}
	else if(strcmp(Info(P),"*")==0) {
		return left*right;
	}
	else if(strcmp(Info(P),"x")==0) {
		return left*right;
	}
	else if(strcmp(Info(P),"/")==0) {
		if(right != 0.00){
			return left/right;
		} else{
			return 0;
		}
	}
	else if(strcmp(Info(P),":")==0) {
		if(right != 0.00){
			return left/right;
		} else{
			return 0;
		}
	}
	else if(strcmp(Info(P),"^")==0) {
		return pow(left, right);
	}
	else if(strcmp(Info(P),"v")==0){
		return sqrt(right);
	}
}

void openingUi(){
 system("cls");
 printf("\n");
 printf("\n");
 printf("\n"); 
 printf("\t\t||=========================== Welcome To ============================|| \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||    #=====         #                 #=====                   #    || \n");
 printf("\t\t||    #       ====#  # #====  #     #  #        ====#  #     #  #    || \n");
 printf("\t\t||    #           #  # #      #     #  #            #  #     #  #    || \n");
 printf("\t\t||    #       #===#  # #      #     #  #  ===#  #===#  #     #  #    || \n");
 printf("\t\t||    #       #   #  # #      #     #  #     #  #   #  #     #  #    || \n");
 printf("\t\t||    #=====  #===#  # #====  #=====#  #=====#  #===#  #=====#  #    || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||                           Was made by :                           || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||                       ~~ Gian Sandrova ~~                         || \n");
 printf("\t\t||                    ~~ Akmal Faqih Fachrezy ~~                     || \n");
 printf("\t\t||                  ~~ Rofa'ul Akrom Hendrawan ~~                    || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t|| Press anykey to main menu...                                      || \n");
 printf("\t\t||===================================================================|| \n");
 printf("\n");   
 getch();           
}

int mainMenu(){
 int i;
 int nomor;
 
system("cls");
 printf("\n");
 printf("\n");
 printf("\n");
 printf("\t\t||============================ Menu Gaul's ==========================|| \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||                       1. Calculator                               || \n");
 printf("\t\t||                       2. Special Calculator                       || \n");
 printf("\t\t||                       3. HowTo                                   || \n");
 printf("\t\t||                       4. About                                    || \n");
 printf("\t\t||                       5. Exit                                     || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||   Enter your choice :                                             || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||===================================================================|| \n");
 gotoxy(40,12);
   scanf("%d", &nomor);
  switch(nomor) { 
    case 1 :
    kalkulatorBasic();
    break;
   case 2 : 
    kalkulatorspesial();
    break;
   case 3 : 
    showHowTo();
    break;
   case 4 :
    About();
    break;
  case 5 : 
    Exit();
    break;
   default :
	gotoxy(40,12);
   printf("Nomor yang Anda masukkan tidak valid!");
   getch();
    mainMenu();
  }
 }

void kalkulatorBasic(){
 int option;
 BinTree expTree;
 String postfix, input;
  
	uiKalkulator(); 
	gotoxy(20,5);
	scanf("%s", input);
	InfixToPostfix(input, postfix); 		//untuk mendapatkan nilai postfix
	expTree = BuildExpressionTree(postfix);	//Membuat sebuah ekspresi tree dari postfix yang sudah didapatkan
    gotoxy(20,6);
    printf("Postfix = %s",postfix);
    gotoxy(20,7);
    printf("Hasil   = %g", CalculationOfTree(expTree)); //Mengembalikan hasil kalkulasi dari ekspresi tree
	gotoxy(50,19);
	printf("Lagi[Y/N] ");
	scanf(" %c",&option);
	if(option=='Y'||option=='y'){
		system("cls");
		kalkulatorBasic();
	}else{
		mainMenu();
	 }
}

void uiKalkulator(){
 system("cls");
 printf("\n");
 printf("\n");
 printf("\n"); 
 printf("\t\t||=========================== Calculator =================================|| \n");
 printf("\t\t|| ---------------------------------------------------------------------- || \n");
 printf("\t\t|| |                                                                    | || \n");
 printf("\t\t|| |                                                                    | || \n");
 printf("\t\t|| |                                                                    | || \n");
 printf("\t\t|| ---------------------------------------------------------------------- || \n");
 printf("\t\t|| -----  -----  -----  -----  ------------------------------------------ || \n");
 printf("\t\t|| | 1 |  | 2 |  | 3 |  | + |  |  Operasi Perpangkatan [ ^ ]            | || \n");
 printf("\t\t|| -----  -----  -----  -----  |  Operasi Perkalian    [ * ] atau [ x ] | || \n");
 printf("\t\t|| -----  -----  -----  -----  |  Operasi Pembagian    [ / ] atau [ : ] | || \n");
 printf("\t\t|| | 4 |  | 5 |  | 6 |  | - |  |  Operasi Penjumlahan  [ + ]            | || \n");
 printf("\t\t|| -----  -----  -----  -----  |  Operasi Pengurangan  [ - ]            | || \n");
 printf("\t\t|| -----  -----  -----  -----  |  Operasi Akar Pangkat 2 [ 2v ]         | || \n");
 printf("\t\t|| | 7 |  | 8 |  | 9 |  | x |  |  Dapat menggunakan '(' dan ')'         | || \n");
 printf("\t\t|| -----  -----  -----  -----  |  Bilangan bulat dan desimal saja       | || \n");
 printf("\t\t|| -----  -----  -----  -----  |  Tidak dapat menggunakan spasi         | || \n");
 printf("\t\t|| | . |  | 0 |  | : |  | = |  |                                        | || \n");
 printf("\t\t|| -----  -----  -----  -----  ------------------------------------------ || \n");
 printf("\t\t||========================================================================|| \n");
 printf("\n");   

}


void About(){
 system("cls");
 printf("\n");
 printf("\n");
 printf("\n");
 printf("\t\t||============================   About   ============================|| \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||   Aplikasi ini dibuat untuk memenuhi Tugas Besar Mata Kuliah      || \n");
 printf("\t\t||   Praktikum Struktur Data dan Algoritma Semester 2 Tahun 2022     || \n");
 printf("\t\t||   Dibuat oleh :                                                   || \n");
 printf("\t\t||   1. Akmal Faqih Fachrezy  (211524035)                            || \n");
 printf("\t\t||   2. Gian Sandrova  (211524043)                                   || \n");
 printf("\t\t||   3. Rofa'ul Akrom Hendrawan (211524061)                          || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||   Dengan Dosen Pengampu                                           || \n");
 printf("\t\t||   Bapak Lukmannul Hakim dan Ibu Asri Maspupah                     || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t|| Press anykey to main menu...                                      || \n");
 printf("\t\t||===================================================================|| \n");
 printf("\n");
 getch();
 mainMenu();
 }

void showHowTo(){
 system("cls");
 printf("\n");
 printf("\n");
 printf("\n");
 printf("\t\t||============================   Cara Penggunaan   ============================|| \n");
 printf("\t\t||                                                                             || \n");
 printf("\t\t||  1. Operasi perpangkatan menggunakan '^'                                    || \n");
 printf("\t\t||  2. Operasi perkalian menggunakan '^' atau 'x'                              || \n");
 printf("\t\t||  3. Operasi pembagian menggunakan ':' atau '/'                              || \n");
 printf("\t\t||  4. Operasi penjumlahan menggunakan '+'                                     || \n");
 printf("\t\t||  5. Operasi pengurangan menggunakan '-'                                     || \n");
 printf("\t\t||  6. Operasi akar pangkat 2 menggunakan '2v'                                 || \n");
 printf("\t\t||  7. '(' dan ')' dapat digunakan                                             || \n");
 printf("\t\t||  8. Input Hanya bilangan bulat dan desimal yang                             || \n");
 printf("\t\t||  9. Tidak diperkenankan menggunakan spasi                                   || \n");
 printf("\t\t||                                                                             || \n");
 printf("\t\t|| Press anykey to main menu...                                                || \n");
 printf("\t\t||=============================================================================|| \n");
 printf("\n");
 getch();
 mainMenu();
}

void kalkulatorspesial(){
 int i;
 int nomor;
  	system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
	printf("\t\t||======================== Special Calculator =======================|| \n");
	printf("\t\t||                                                                   || \n");
	printf("\t\t||                                                                   || \n");
	printf("\t\t||                       1. Konverter Massa                          || \n");
	printf("\t\t||                       2. Kalkulator Diskon                        || \n");
	printf("\t\t||                       3. Main Menu                                || \n");
	printf("\t\t||   Enter your choice :                                             || \n");
	printf("\t\t||                                                                   || \n");
	printf("\t\t||===================================================================|| \n");
	gotoxy(40,9);
    scanf("%d", &nomor);
  switch(nomor) { 
    case 1 :
 		MenuKonverterMassa();
    	break;
   	case 2 : 
    	system("cls");
    	kalkulatorDiskon();
   		break; 
	case 3 :
		mainMenu();
		break;    
	default :
		gotoxy(40,11);
		puts("\nNomor yang Anda masukkan tidak valid!");
		break;
	}
  //system("PAUSE");
  getch();
 }  

void MenuKonverterMassa(){
 int i;
 int nomor;
  system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
 printf("\t\t||========================== Konverter Massa ========================|| \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||                       1. Kilogram => Gram                         || \n");
 printf("\t\t||                       2. Kilogram => Miligram                     || \n");
 printf("\t\t||                       3. Gram     => Kilogram                     || \n");
 printf("\t\t||                       4. Gram     => Miligram                     || \n");
 printf("\t\t||                       5. Miligram => Kilogram                     || \n");
 printf("\t\t||                       6. Miligram => Gram                         || \n");
 printf("\t\t||                       7. Back To Calculator Spesial               || \n");
 printf("\t\t||   Enter your choice :                                             || \n");
 printf("\t\t||                                                                   || \n");
 printf("\t\t||===================================================================|| \n");
 gotoxy(40,12);
    scanf("%d", &nomor);
    switch(nomor) { 
    case 1 :
 	KgToGr();
    break;
    case 2 : 
 	KgToMg();
    break;
    case 3 : 
 	GrToKg();
    break;
    case 4 :
    GrToMg();
    break;
    case 5 :
    MgToKg();
    break;
    case 6 :
    MgToGr();
 break;
 case 7 :
 kalkulatorspesial();      
 break;
 default :
 gotoxy(49,15);
    puts("\nNomor yang Anda masukkan tidak valid!");
  }

 } 

void kalkulatorDiskon(){
 
 int harga;
 float diskon;
 float potonganHarga;
 float setelahDiskon;

 char option;
 system("cls");
 printf("\n");
 printf("\n");
 printf("\n"); 
 printf("\t\t||======================== Calculator Diskon =============================|| \n");
 printf("\t\t|| ---------------------------------------------------------------------- || \n");
 printf("\t\t|| |                                                                    | || \n");
 printf("\t\t|| |                                                                    | || \n");
 printf("\t\t|| ---------------------------------------------------------------------- || \n");
 printf("\t\t|| -----  -----  -----  ------------------------------------------------- || \n");
 printf("\t\t|| | 1 |  | 2 |  | 3 | |           < Aturan Calculator Diskon >         | || \n");
 printf("\t\t|| -----  -----  ----- |                                                | || \n");
 printf("\t\t|| -----  -----  ----- |  Harga berupa rupiah                           | || \n");
 printf("\t\t|| | 4 |  | 5 |  | 6 | |  Input diskon tidak boleh negatif              | || \n");
 printf("\t\t|| -----  -----  ----- |  Input tidak diperbolehkan menggunakan spasi   | || \n");
 printf("\t\t|| -----  -----  ----- |  Input diskon Min 0 dan Max 100                | || \n");
 printf("\t\t|| | 7 |  | 8 |  | 9 | |                                                | || \n");
 printf("\t\t|| -----  -----  ----- |                                                | || \n");
 printf("\t\t||        -----        |                                                | || \n");
 printf("\t\t||        | 0 |        |                                                | || \n");
 printf("\t\t||        -----         ------------------------------------------------| || \n");
 printf("\t\t||========================================================================|| \n");
 printf("\n");   
 
 gotoxy(20,5);
 printf("Harga  : Rp."); scanf("%d", &harga);
 gotoxy(20,6);
 printf("Diskon : "); scanf("%f", &diskon);
 gotoxy(50,5);
 if(harga<0||diskon<0||diskon>100){
   printf("Inputan Tidak Valid");
 }else{
 potonganHarga = (harga*diskon)/100;
   printf("Potongan harga       = Rp.%g", potonganHarga);
 gotoxy(50,6);
  setelahDiskon = harga-(harga*diskon)/100;
   printf("Harga Setelah diskon = Rp.%g\n", setelahDiskon);
 }
 
 gotoxy(43,18);
 printf("Lagi [Y/N]");
 scanf(" %c",&option);
 if(option=='Y'||option=='y'){
  system("cls");
  kalkulatorDiskon();
 }else{
  kalkulatorspesial();
 }
 getch();
}

 void gotoxy(int x, int y){
 HANDLE hConsoleOutput;
 COORD dwCursorPosition;
 dwCursorPosition.X = x;
 dwCursorPosition.Y = y;
 hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}
void KgToGr(){
 double value;
 char option;
 system("cls");
 uiMassa();
 gotoxy(20,5);
 printf("Masukkan Nilai Kg : ");
 scanf("%lf",&value);
 if(value < 0)
  printf("Inputan Tidak Boleh Negatif");
 else {
  gotoxy(20,6);
  printf("Hasil converter dari Kg ke Gram  = %2.lf Gr",value*1000);
 }
 gotoxy(43,18);
  printf("LAGI [Y/N]");
  scanf(" %c",&option);
 if(option=='Y'||option=='y'){
  system("cls");
  KgToGr();
 }else{
  kalkulatorspesial();
 }
}

void KgToMg(){
 double value;
 char option;
 system("cls");
 uiMassa();
 gotoxy(20,5);
 printf("Masukkan Nilai Kg : ");
 scanf("%lf",&value);
 if(value < 0)
  printf("Inputan Tidak Boleh Negatif");
 else {
  gotoxy(20,6);
  printf("Hasil converter dari Kg ke Mg  = %2.lf Mg",value*1000000);
 }
 gotoxy(43,18);
  printf("LAGI [Y/N]");
  scanf(" %c",&option);
 if(option=='Y'||option=='y'){
  system("cls");
  KgToMg();
 }else{
  kalkulatorspesial();
 }
}
void MgToGr(){
 double value;
 char option;
 system("cls");
 uiMassa();
 gotoxy(20,5);
 printf("Masukkan Nilai Mg : ");
 scanf("%lf",&value);
 if(value < 0)
  printf("Inputan Tidak Boleh Negatif");
 else {
  gotoxy(20,6);
  printf("Hasil converter dari Mg ke Gram = %g Gram",value/1000);
 } 
   gotoxy(43,18);
   printf("LAGI [Y/N]");
  scanf(" %c",&option);
 if(option=='Y'||option=='y'){
  system("cls");
  MgToGr();
 }else{
  kalkulatorspesial();
 }
}

void MgToKg(){
 double value;
 char option;
 system("cls");
 uiMassa();
 gotoxy(20,5);
 printf("Masukkan Nilai Mg : ");
 scanf("%lf",&value);
 if(value < 0)
  printf("Inputan Tidak Boleh Negatif");
 else {
  gotoxy(20,6);
  printf("Hasil converter dari Mg ke Kg = %g Kg",value/1000000);
 } 
  gotoxy(43,18);
  printf("LAGI [Y/N]");
  scanf(" %c",&option);
 if(option=='Y'||option=='y'){
  system("cls");
  MgToKg();
 }else{
  kalkulatorspesial();
 }
}

void GrToMg(){
 double value;
 char option;
 system("cls");
 uiMassa();
 gotoxy(20,5);
   printf("Masukkan Nilai Gram : ");
 scanf("%lf",&value);
 if(value < 0)
  printf("Inputan Tidak Boleh Negatif");
 else {
  gotoxy(20,6);
  printf("Hasil converter dari Gram ke Mg  = %2.lf Mg",value*1000);
 }
 gotoxy(43,18);
 printf("LAGI [Y/N]");
  scanf(" %c",&option);
 if(option=='Y'||option=='y'){
  system("cls");
  GrToMg();
 }else{
  kalkulatorspesial();
 }
}

void GrToKg(){
 double value;
 char option;
 system("cls");
 uiMassa();
 gotoxy(20,5);
 printf("Masukkan Nilai Gr : ");
 scanf("%lf",&value);
 if(value < 0)
  printf("Inputan Tidak Boleh Negatif");
 else {
  gotoxy(20,6);
  printf("Hasil converter dari Gram ke Kg  = %g Kg",value/1000);
 }
 gotoxy(43,18);
  printf("LAGI [Y/N]");
  scanf(" %c",&option);
 if(option=='Y'||option=='y'){
  system("cls");
  GrToKg();
 }else{
  kalkulatorspesial();
 }
}

void Exit(){
 system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\t||=========================   Thanks Gaul's   =======================|| \n");
    printf("\t\t||                                                                   || \n");
    printf("\t\t||   Terimakasih telah menggunakan aplikasi yang telah kami buat     || \n");
    printf("\t\t||   semoga kedepannya aplikasi ini dapat bermanfaat untuk user      || \n");
    printf("\t\t||   lainnya.                                                        || \n");
    printf("\t\t||                                                                   || \n");
    printf("\t\t||   Semoga hari-hari anda menyenangkan ^_^                          || \n");
    printf("\t\t||                                                                   || \n");
    printf("\t\t||===================================================================|| \n");  
}
void uiMassa(){
 system("cls");
 printf("\n");
 printf("\n");
 printf("\n"); 
 printf("\t\t||========================= Calculator Massa =============================|| \n");
 printf("\t\t|| ---------------------------------------------------------------------- || \n");
 printf("\t\t|| |                                                                    | || \n");
 printf("\t\t|| |                                                                    | || \n");
 printf("\t\t|| ---------------------------------------------------------------------- || \n");
 printf("\t\t|| -----  -----  -----  ------------------------------------------------- || \n");
 printf("\t\t|| | 1 |  | 2 |  | 3 | |           < Aturan Calculator Massa >          | || \n");
 printf("\t\t|| -----  -----  ----- |                                                | || \n");
 printf("\t\t|| -----  -----  ----- |                                                | || \n");
 printf("\t\t|| | 4 |  | 5 |  | 6 | |  Input tidak boleh negatif                     | || \n");
 printf("\t\t|| -----  -----  ----- |  Input tidak diperbolehkan menggunakan spasi   | || \n");
 printf("\t\t|| -----  -----  ----- |  Input desimal menggunakan '.'                 | || \n");
 printf("\t\t|| | 7 |  | 8 |  | 9 | |                                                | || \n");
 printf("\t\t|| -----  -----  ----- |                                                | || \n");
 printf("\t\t||        -----        |                                                | || \n");
 printf("\t\t||        | 0 |        |                                                | || \n");
 printf("\t\t||        -----         ------------------------------------------------| || \n");
 printf("\t\t||========================================================================|| \n");
 printf("\n");   
}
void loading(){

 char load[] = 
     "||========================= Mohon menunggu =======================||\n";

  int i;
 
 system("cls");
  gotoxy(17,10);
     for (i = 0; load[i]!=0 ; i++) {
    Sleep(40);
    printf("%c", load[i]);
}
     gotoxy(17, 10);
  for (i = 0; load[i]!=0 ; i++) {
    Sleep(15);
    printf(" ");
  }

 }
