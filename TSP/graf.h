#ifndef GRAF_H
#define GRAF_H
#include "grad.h"
#include "binarni.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <climits>
#include <algorithm>
#include <cmath>

using namespace std;

class Graf {

  struct Grana {
      int tezina;
      int pocetak;
      int kraj;
      Grana(int tezina, int pocetak, int kraj):tezina(tezina),pocetak(pocetak),kraj(kraj) {}
      bool operator<(Grana druga) { return tezina<druga.tezina; }
  };

  int n;
  vector <Grad> gradovi;
  vector <vector <int> > udaljenosti;
  vector<Grana> grane;

  int duzinaTure(vector<int>& tura);
  void ispisiTuru(vector<int>& tura);
  bool provjeriTuru(vector<int>& tura);
  int udaljenost(double x1, double y1, double x2, double y2) {
    return round(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
  }
  vector<int> Zamjena_twoopt( int v1, int v2, vector<int> tura );
  vector<int> vratiTuruNajmanjaGrana();
  vector<int> vratiTwoOptTuru();
  vector<int> vratiTuruNajbliziSusjed();

public:
  Graf(string filename);
  int turaNajbliziSusjed();
  int turaNajmanjaGrana();
  int two_opt();
  int three_opt();
};

Graf::Graf(string filename) {
    ifstream unos(filename);
    while(!unos.eof()) {
        int indeks;
        double latitude;
        double longitude;
        unos>>indeks;
        unos.get();
        unos>>latitude;
        unos.get();
        unos>>longitude;
        unos.get();
        gradovi.push_back(Grad(indeks,latitude,longitude));
    }
    unos.close();
    n = gradovi.size();
    udaljenosti.resize(n);
    for(int i=0;i<n;i++)
        udaljenosti[i].resize(n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
          udaljenosti[i][j] = udaljenost(gradovi[i].latitude,gradovi[i].longitude,gradovi[j].latitude,gradovi[j].longitude);
          if(i<j)
            grane.push_back(Grana(udaljenosti[i][j],i,j));
        }
  }

int Graf::duzinaTure(vector<int>& tura)
{
    int duzina_ture = 0;
    for(int i=0;i<tura.size();i++)
    duzina_ture += udaljenosti[tura[i]][tura[(i+1)%n]];
    return duzina_ture;
}

  void Graf::ispisiTuru(vector<int>& tura) {
    for(int i=0;i<tura.size();i++)
        cout<<tura[i]<<" ";
    cout<<endl;
  }

  bool Graf::provjeriTuru(vector<int>& tura) {
    vector<bool> posjecen(n,false);
    if(tura.size() != n)
        return false;
    else {
        for(int i=0;i<n;i++) {
            if(tura[i]<0 || tura[i]>=n || posjecen[tura[i]] == true)
                return false;
            else posjecen[tura[i]] = true;
        }
    }
    return true;
  }

  int Graf::turaNajbliziSusjed() {
    vector<int> tura;
    int pocetni = 0;
    vector<bool> posjecen(n,false);
    posjecen[pocetni] = true;
    tura.push_back(pocetni);
    for(int i=0;i<n-1;i++) {
      int trenutni = tura[tura.size()-1];
      int udaljenostNajblizeg = INT_MAX;
      int najblizi;
      for(int j=0;j<n;j++) {
        if(!posjecen[j] && udaljenosti[trenutni][j] < udaljenostNajblizeg) {
            udaljenostNajblizeg = udaljenosti[trenutni][j];
            najblizi = j;
        }
      }
      posjecen[najblizi] = true;
      tura.push_back(najblizi);
    }
    //ispisiTuru(tura);
    if(provjeriTuru(tura))
        return duzinaTure(tura);
    else throw "Greska";
  }

  vector<int> Graf::vratiTuruNajbliziSusjed() {
    vector<int> tura;
    int pocetni = 0;
    vector<bool> posjecen(n,false);
    posjecen[pocetni] = true;
    tura.push_back(pocetni);
    for(int i=0;i<n-1;i++) {
      int trenutni = tura[tura.size()-1];
      int udaljenostNajblizeg = INT_MAX;
      int najblizi;
      for(int j=0;j<n;j++) {
        if(!posjecen[j] && udaljenosti[trenutni][j] < udaljenostNajblizeg) {
            udaljenostNajblizeg = udaljenosti[trenutni][j];
            najblizi = j;
        }
      }
      posjecen[najblizi] = true;
      tura.push_back(najblizi);
    }
    //ispisiTuru(tura);
    if(provjeriTuru(tura))
        return tura;
    else throw "Greska";
  }

  int Graf::turaNajmanjaGrana() {
    Ruta ruta(n);
    sort(grane.begin(),grane.end());
    vector<int> stepeni(n,0);
    int trenutna = 0;
    for(int i=0;i<n-1;i++) {
      while(true) {
        Grana trenutnaGrana = grane[trenutna];
        int pocetak = trenutnaGrana.pocetak;
        int kraj = trenutnaGrana.kraj;
        if(stepeni[pocetak] == 2 || stepeni[kraj] == 2) {
            trenutna++;
            continue;
        }
        ruta.dodajGranu(pocetak,kraj);
        if(ruta.imaLiCiklusa(pocetak)) {
            ruta.obrisiGranu(pocetak,kraj);
            trenutna++;
            continue;
        }
        else {
            stepeni[pocetak]++;
            stepeni[kraj]++;
            trenutna++;
            break;
        }

      }
    }

    vector<int> tura = ruta.vratiTuru();
    //ispisiTuru(tura);
    if(provjeriTuru(tura))
        return duzinaTure(tura);
    else throw "Greska";
  }
// dodani algoritmi

/*-----------------------Tura najmanja grana--------------------*/
vector<int> Graf::vratiTuruNajmanjaGrana() {
    Ruta ruta(n);
    sort(grane.begin(),grane.end());
    vector<int> stepeni(n,0);
    int trenutna = 0;
    for(int i=0;i<n-1;i++) {
      while(true) {
        Grana trenutnaGrana = grane[trenutna];
        int pocetak = trenutnaGrana.pocetak;
        int kraj = trenutnaGrana.kraj;
        if(stepeni[pocetak] == 2 || stepeni[kraj] == 2) {
            trenutna++;
            continue;
        }
        ruta.dodajGranu(pocetak,kraj);
        if(ruta.imaLiCiklusa(pocetak)) {
            ruta.obrisiGranu(pocetak,kraj);
            trenutna++;
            continue;
        }
        else {
            stepeni[pocetak]++;
            stepeni[kraj]++;
            trenutna++;
            break;
        }

      }
    }

    vector<int> tura = ruta.vratiTuru();
    if(provjeriTuru(tura))
        return tura;
    else throw "Greska";
  }

/*------------------------Zamjena 2 grane ------------*/

vector<int> Graf::Zamjena_twoopt(int v1, int v2, vector<int> tura) {
    vector<int> ruta;

    for ( int i = 0; i < v1 ; i++ ){
        ruta.push_back(tura[i]);
    }

    for (int i = v2; i >= v1; i--){
        ruta.push_back(tura[i]);
    }

    for ( int i = v2+1 ; i < n; i++ ){
        ruta.push_back(tura[i]);
    }

    return ruta;
}
/*------------------------2opt-----------------*/

int Graf::two_opt() {
    vector<int> tura = vratiTuruNajmanjaGrana();
    bool provjera=true;

    while ( provjera )
    {
        int brojac=0;
        int najmanjaUdaljenost = duzinaTure(tura);

        for ( int i = 0; i < n - 1; i++ ){

            for ( int k = i + 1; k < n; k++){
                vector<int> novaTura;
                novaTura = Zamjena_twoopt( i, k, tura );

                int udaljenost = duzinaTure(novaTura);

                if ( udaljenost < najmanjaUdaljenost ){
                    tura = novaTura;
                    najmanjaUdaljenost = udaljenost;
                    brojac++;
                }
            }

         }
         if(brojac==0) provjera=false;
    }

    return duzinaTure(tura);
}

/*------------------2opt tura-----------------*/

vector<int> Graf::vratiTwoOptTuru() {
    vector<int> tura = vratiTuruNajmanjaGrana();
    bool provjera=true;

    while ( provjera )
    {
        int br=0;
        int najmanja_udaljenost = duzinaTure(tura);

        for ( int i = 0; i < n - 1; i++ ){

            for ( int j = i + 1; j < n; j++){
                vector<int> nova_tura;
                nova_tura = Zamjena_twoopt( i, j, tura );

                int udaljenost = duzinaTure(nova_tura);

                if ( udaljenost < najmanja_udaljenost )
                {
                    tura = nova_tura;
                    najmanja_udaljenost = udaljenost;
                    br++;
                }

            }

         }
         if(br==0) provjera=false;

    }
    return tura;
}

/*--------------3opt----------------*/

int Graf::three_opt() {
    vector<int> tura = vratiTwoOptTuru();
    bool provjera=true;

    while ( provjera )
    {
        int br=0;
        int najmanja_udaljenost = duzinaTure(tura);

        for ( int i = 0; i < n - 2; i++ ){
            for ( int j = i + 1; j < n-1; j++){
                for( int k = j + 1; k < n; k++ ){

                    vector<int> nova_tura;
                    nova_tura = Zamjena_twoopt( i, j, tura );
                    nova_tura = Zamjena_twoopt( j, k, nova_tura );

                    int udaljenost = duzinaTure(nova_tura);

                    if ( udaljenost < najmanja_udaljenost ){
                        tura = nova_tura;
                        najmanja_udaljenost = udaljenost;
                        br++;
                    }

                }
            }
        }
        if(br==0) provjera=false;

    }

    return duzinaTure(tura);

}

#endif // GRAF_H
