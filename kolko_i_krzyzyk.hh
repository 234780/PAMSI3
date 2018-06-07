#ifndef KOLKO_I_KRZYZYK_HH
#define KOLKO_I_KRZYZYK_HH


class KolkoIKrzyzyk{
  //atrybuty:
  int rozmiar;
  int ile_zeby_wygrac;
  char* tablicagry;

  //metody:
public:
  KolkoIKrzyzyk(int rozm, int ile);
  void ObslugaGry();
private:
  void RysujPlansze();
  bool CzyWygrana(char gracz, bool cisza);
  bool CzyRemis(bool cisza);
  int MiniMax(char gracz);
  int AlfaBeta(char gracz, int alfa, int beta);
  int RuchKomputera();
  void Ruch(char &gracz);
  void CzyscPlansze();

};
#endif
