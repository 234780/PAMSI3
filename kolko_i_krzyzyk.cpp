#include <iostream>
#include <stdlib.h>
#include "kolko_i_krzyzyk.hh"
#define INFINITY 2147483647 
using namespace std;

void KolkoIKrzyzyk::RysujPlansze(){
  int i, j;
  cout <<endl<<endl;
  cout<<"-------------------------------------------------------------"<<endl;
  cout<<"-----------------------KOLKO I KRZYZYK-----------------------"<<endl;
  cout<<"------------------ X - KOMPUTER, O - GRACZ ------------------"<<endl;
  cout<<"-------------------------------------------------------------"<<endl;
  if(ile_zeby_wygrac==1)
    cout<<"----------ABY WYGRAC MUSISZ ULOZYC "<<ile_zeby_wygrac<<" ZNAK W RZEDZIE----------"<<endl;
  else if(ile_zeby_wygrac<5)
    cout<<"----------ABY WYGRAC MUSISZ ULOZYC "<<ile_zeby_wygrac<<" ZNAKI W RZEDZIE---------"<<endl;
  else
    cout<<"---------ABY WYGRAC MUSISZ ULOZYC "<<ile_zeby_wygrac<<" ZNAKOW W RZEDZIE---------"<<endl;
  cout<<"-------------------------------------------------------------"<<endl<<endl;
  
  for(i = 1; i <= rozmiar*rozmiar+1; i++){
    cout<<" "<<tablicagry[i]<<" ";
    if(i % rozmiar)
      cout << "|";
    else if (i!= rozmiar*rozmiar && i!=0){
      cout<<endl;
      for(j=0; j<rozmiar;  j++)
	cout<<"--- ";
      cout<<endl;
    }
    else
      cout<<endl<<endl<<endl;  
  }    
}

bool KolkoIKrzyzyk::CzyWygrana(char gracz, bool cisza){
  bool test;
  int i,k,j;
  int ilezliczono=0;

  test = false;

  // Sprawdzamy wiersze
  for(k=0; k<rozmiar; k++){ // iterujemy wiersze
    for(i=k*rozmiar+1; i<k*rozmiar+rozmiar-ile_zeby_wygrac+2;i++){//start
      for(j=0; j<ile_zeby_wygrac;j++){
	if(tablicagry[i+j]==gracz)
	  ilezliczono++;
      }
      if(ilezliczono==ile_zeby_wygrac)
	test=true;
      else
	ilezliczono=0;
    }
  }
  
  // Sprawdzamy kolumny
  if(test==false){
    for(i=1; i<rozmiar*(rozmiar-ile_zeby_wygrac+1)+1; i++){
      for(j=0; j<ile_zeby_wygrac; j++){
	if(tablicagry[i+j*rozmiar]==gracz)
	  ilezliczono++;
      }
      if(ilezliczono==ile_zeby_wygrac)
	test=true;
      else
	ilezliczono=0;
    }
  }
  // Sprawdzamy przekątną prawo w dol
  if(test==false){
    for(k=0; k<rozmiar-ile_zeby_wygrac+1;k++){//wiersz
      for(i=k*rozmiar+1; i<k*rozmiar+rozmiar-ile_zeby_wygrac+2;i++){//start
	for(j=0; j<ile_zeby_wygrac; j++){
	  if(tablicagry[i+rozmiar*j+j]==gracz)
	    ilezliczono++;
	}
	if(ilezliczono==ile_zeby_wygrac)
	  test=true;
	else
	  ilezliczono=0;      }
    }
  }

  // Sprawdzamy przekątną lewo w dol
  if(test==false){
    for(k=0; k<rozmiar-ile_zeby_wygrac+1;k++){//wiersz
      for(i=k*rozmiar+ile_zeby_wygrac; i<k*rozmiar+rozmiar+1; i++){//start
	for(j=0; j<ile_zeby_wygrac; j++){
	  if(tablicagry[i+j*rozmiar-j]==gracz)
	    ilezliczono++;
	}
	if(ilezliczono==ile_zeby_wygrac)
	  test=true;
	else
	  ilezliczono=0;
      }
    }
  }

  if(test==true){
    if(cisza==false){
      system("clear");
      RysujPlansze();
      cout << "\nGRACZ " << gracz << " WYGRYWA!!!\n\n";
    }
    return true;
  }
  return false;
}

bool KolkoIKrzyzyk::CzyRemis(bool cisza){
  int i;
  
  for(i=1; i<rozmiar*rozmiar+1; i++)
    if(tablicagry[i]==' ')
      return false; // jest puste pole?


  if(cisza==false){ //jesli ma byc odzew
    system("clear");
    RysujPlansze();
    cout << "\nREMIS !!!\n\n";
  }
  return true;     // wszystkie pola juz zajete? REMIS!
}


int KolkoIKrzyzyk::MiniMax(char gracz){
  int min=10;//cos wiekszego niz zwraca minimax
  int max=-10;//cos mniejszego niz zwraca minimax
  int wynik; //to, co zwraca minimax
  int i;

  //sprawdzamy czy koniec rozgrywki
  if(CzyWygrana(gracz, true)){
    if(gracz=='X') 
      return 1;
    else
      return -1;
  }

  if(CzyRemis(true))
    return 0;

  // gramy dalej?

  //zamiana graczy
  if(gracz=='X')
    gracz='O';
  else
    gracz='X';

    
  if(gracz=='X'){//jesli ruch komputera, maksymalizujemy wynik
    for(i=1; i<rozmiar*rozmiar+1;i++){
      if(tablicagry[i]==' '){
	tablicagry[i]=gracz;
	wynik=MiniMax(gracz);
	tablicagry[i]=' ';
	if(wynik>max)
	  max=wynik;
      }
    }
    return max;
  }
  else{//ruch czlowieka, minimalizujemy wynik
    for(i=1; i<rozmiar*rozmiar+1; i++){
      if(tablicagry[i]==' '){
	tablicagry[i]=gracz;
	wynik=MiniMax(gracz);
	tablicagry[i]=' ';
	if(wynik<min)
	  min=wynik;
      }
    }
    return min;
  } 
}

int KolkoIKrzyzyk::AlfaBeta(char gracz, int alfa, int beta){
  int i;
  int r, x;
  int pomoc;

  //sprawdzamy czy koniec rozgrywki
  if(CzyWygrana(gracz, true)){
    if(gracz=='X')
      return 1;
    else
      return -1;
  }

  if(CzyRemis(true))
    return 0;

  // gramy dalej?

  //zamiana graczy
  if(gracz=='X')
    gracz='O';
  else
    gracz='X';

  
  if(gracz=='X'){// ruch komputera
    r=-INFINITY; // ta nieskonczonosc mi sie nie podoba :(
    for(i=1; i<rozmiar*rozmiar+1;i++){
      if(tablicagry[i]==' '){
	tablicagry[i]=gracz;
	pomoc=max(r, alfa);
	x=AlfaBeta(gracz, pomoc, beta);
	tablicagry[i]=' ';
	if(x>=beta)
	  return x;
	r=max(r, x);
      }
    }
  }
  else{//ruch czlowieka
    r=INFINITY; // ta tez...
    for(i=1; i<rozmiar*rozmiar+1;i++){
      if(tablicagry[i]==' '){
	tablicagry[i]=gracz;
	pomoc=min(r, beta);
	x=AlfaBeta(gracz, alfa, pomoc);
	tablicagry[i]=' ';
	if(x<=alfa)
	  return x;
	r=min(r,x);
      }
    }
  }
  return r;
}


int KolkoIKrzyzyk::RuchKomputera(){
  int ruch, i, wynik;
  int max;
  max=-10;
  //max = -INFINITY;

  
  for(i = 1; i < rozmiar*rozmiar+1; i++){
    if(tablicagry[i] == ' '){
      tablicagry[i] = 'X';
      wynik=AlfaBeta('X', -INFINITY, INFINITY);
      // wynik = MiniMax('X');
      tablicagry[i] = ' ';
      if(wynik > max){
	max = wynik;
      	ruch = i;
      }
    }
  }//koniec for
  
  return ruch;
}


void KolkoIKrzyzyk::Ruch(char &gracz){
  int ruch;
  system("clear");
  RysujPlansze();
  if(gracz == 'O'){ //kolej czlowieka
    cout << "\nRuch: ";
    cin >> ruch;
  }
  else{ // kolej komputera
    ruch = RuchKomputera();
  }
  
  if((ruch >= 1) && (ruch < rozmiar*rozmiar+1) && (tablicagry[ruch] == ' '))
    tablicagry[ruch] = gracz;
  gracz = (gracz == 'O') ? 'X' : 'O';
}

KolkoIKrzyzyk::KolkoIKrzyzyk(int rozm, int ile){
  int i;
  
  rozmiar=rozm;
  ile_zeby_wygrac=ile;

  tablicagry=new char[rozmiar*rozmiar+1];
  for(i=0; i<rozmiar*rozmiar+1; i++)
    tablicagry[i]=' ';
}

void KolkoIKrzyzyk::CzyscPlansze(){
  int i;
  for (i=0; i<rozmiar*rozmiar+1; i++)
    tablicagry[i]=' ';
}

void KolkoIKrzyzyk::ObslugaGry(){
  char wybor;
  char gracz;

  do {
    gracz='O'; //zawsze zaczyna czlowiek
    CzyscPlansze();
    while(!CzyWygrana('X', false) && !CzyWygrana('O', false) && !CzyRemis(false))
      Ruch(gracz);
   
    cout<<"Jeszcze raz? (T=TAK) ";
    cin>>wybor;
   
   
  } while((wybor=='T')||(wybor=='t'));
 
}

