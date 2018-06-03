#include <iostream>
#include <stdlib.h>
#define INFINITY 2147483647 
using namespace std;

void plansza(char* tablicagry, int rozmiar){
  int i, j;
  int ile;

  if(rozmiar<5)
    ile=rozmiar;
  else
    ile=5;
  cout <<endl<<endl;
  cout<<"-------------------------------------------------------------"<<endl;
  cout<<"-----------------------KOLKO I KRZYZYK-----------------------"<<endl;
  cout<<"------------------ X - KOMPUTER, O - GRACZ ------------------"<<endl;
  cout<<"-------------------------------------------------------------"<<endl;
  if(ile==1)
  cout<<"----------ABY WYGRAC MUSISZ ULOZYC "<<ile<<" ZNAK W RZEDZIE----------"<<endl;
  else if(ile<5)
    cout<<"----------ABY WYGRAC MUSISZ ULOZYC "<<ile<<" ZNAKI W RZEDZIE---------"<<endl;
  else
    cout<<"---------ABY WYGRAC MUSISZ ULOZYC "<<ile<<" ZNAKOW W RZEDZIE---------"<<endl;
  cout<<"-------------------------------------------------------------"<<endl<<endl;
  for(i = 0; i <= rozmiar*rozmiar; i++){
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

bool CzyWygrana(char* tablicagry, int rozmiar,  char gracz, bool cisza){
  bool test;
  int i,k,j;
  int ile_zeby_wygrac;
  int ilezliczono=0;

  if(rozmiar<5)
    ile_zeby_wygrac=rozmiar;
  else
    ile_zeby_wygrac=5;

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
    if(!cisza){
      system("clear");
      plansza(tablicagry,rozmiar);
      cout << "\nGRACZ " << gracz << " WYGRYWA!!!\n\n";
    }
    return true;
  }
  return false;
}

bool CzyRemis(char* tablicagry, int rozmiar,  bool cisza){
  int i;
  
  for(i=1; i<rozmiar*rozmiar+1; i++)
    if(tablicagry[i]==' ')
      return false;


  if(!cisza){
    system("clear");
    plansza(tablicagry,rozmiar); cout << "\nREMIS !!!\n\n";
  }
  return true;     
}


int MiniMax(char* tablicagry, int rozmiar, char gracz){
  int min=10;//cos wiekszego niz zwraca minimax
  int max=-10;//cos mniejszego niz zwraca minimax
  int wynik; //to, co zwraca minimax
    int i;

    //sprawdzamy czy koniec rozgrywki
    if(CzyWygrana(tablicagry, rozmiar, gracz, true)){
      if(gracz=='X')
	return 1;
      else
	return -1;
    }

    if(CzyRemis(tablicagry, rozmiar, true))
      return 0;

    // gramy dalej?

    //zamiana graczy
    if(gracz=='X')
      gracz='O';
    else
      gracz='X';

    
    if(gracz=='X'){//jesli ruch komputera
      for(i=1; i<rozmiar*rozmiar+1;i++){
	if(tablicagry[i]==' '){
	  tablicagry[i]=gracz;
	  wynik=MiniMax(tablicagry, rozmiar, gracz);
	  tablicagry[i]=' ';
	  if(wynik>max)
	    max=wynik;
	}
      }
      return max;
    }
    else{//ruch czlowieka
      for(i=1; i<rozmiar*rozmiar+1; i++){
	if(tablicagry[i]==' '){
	  tablicagry[i]=gracz;
	  wynik=MiniMax(tablicagry, rozmiar, gracz);
	  tablicagry[i]=' ';
	  if(wynik<min)
	    min=wynik;
	}
      }
      return min;
    }

    
  }

int AlfaBeta(char* tablicagry, int rozmiar, char gracz, int alfa, int beta){
  int i;
  int r, x;
  int pomoc;

  //ocena gry
  if(CzyWygrana(tablicagry, rozmiar, gracz, true)){
    if(gracz=='X')
      return 1;
    else
      return -1;
  }

  if(CzyRemis(tablicagry, rozmiar, true))
    return 0;
  
  //gramy dalej?
  //zamiana gracza

  if(gracz=='X')
    gracz='O';
  else
    gracz='X';

  
  if(gracz=='X'){// ruch komputera
    r=-INFINITY;
    for(i=1; i<rozmiar*rozmiar+1;i++){
      if(tablicagry[i]==' '){
	tablicagry[i]=gracz;
	pomoc=max(r, alfa);
	x=AlfaBeta(tablicagry, rozmiar,gracz, pomoc, beta);
	tablicagry[i]=' ';
	if(x>=beta)
	  return x;
	r=max(r, x);
      }
    }
  }
  else{//ruch czlowieka
    r=INFINITY;
    for(i=1; i<rozmiar*rozmiar+1;i++){
      if(tablicagry[i]==' '){
	tablicagry[i]=gracz;
	pomoc=min(r, beta);
	x=AlfaBeta(tablicagry,rozmiar,gracz, alfa, pomoc);
	tablicagry[i]=' ';
	if(x<=alfa)
	  return x;
	r=min(r,x);
      }
    }
  }
  cout<<r<<endl;
  return r;
}

int RuchKomputera(char* tablicagry, int rozmiar){
  int ruch, i, wynik, max;
  max = -10;

  for(i = 1; i < rozmiar*rozmiar+1; i++){
    if(tablicagry[i] == ' '){
      tablicagry[i] = 'X';
       wynik=AlfaBeta(tablicagry, rozmiar, 'X', INFINITY, -INFINITY);
       // wynik = MiniMax(tablicagry, rozmiar,'X');
      tablicagry[i] = ' ';
      if(wynik > max){
        max = wynik;
	ruch = i;
      }
    }
  }//koniec for
  return ruch;
}


void Ruch(char* tablicagry, int rozmiar, char &gracz){
  int ruch;
  system("clear");
  plansza(tablicagry,rozmiar);
  if(gracz == 'O'){ //kolej czlowieka
    cout << "\nRuch: ";
    cin >> ruch;
  }
  else{ // kolej komputera
    ruch = RuchKomputera(tablicagry, rozmiar);
  }
  cout << "---------------------------\n\n";
  if((ruch >= 1) && (ruch < rozmiar*rozmiar+1) && (tablicagry[ruch] == ' ')) tablicagry[ruch] = gracz;
  gracz = (gracz == 'O') ? 'X' : 'O';
}



int main(){
  int rozmiar=3;
  char* tablicagry;
  char gracz,wybor;
  int i;

  tablicagry=new char[rozmiar*rozmiar+1];
  
  do{
    for(i = 1; i < rozmiar*rozmiar+1; i++)
      tablicagry[i] = ' ';
    gracz = 'O';
    
    while(!CzyWygrana(tablicagry,rozmiar,'X',false) && !CzyWygrana(tablicagry,rozmiar,'O',false) && !CzyRemis(tablicagry, rozmiar,false)){
      Ruch(tablicagry, rozmiar,gracz);
    }
    
    cout << "Jeszcze raz ? (T = TAK) : ";
    cin >> wybor; 
    cout << "\n\n\n";

  } while((wybor == 'T') || (wybor == 't'));
}
