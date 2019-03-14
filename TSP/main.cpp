#include <iostream>
#include "graf.h"
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

int main() {
  clock_t t1,t2,t3,t4,t5;
  t1=clock();

  string filename1("djibouti.txt");
  Graf G1(filename1);
  cout<<"***********DJIBOUTI***********"<<endl;
  cout<<"Tura najblizi susjed: "<<G1.turaNajbliziSusjed()<<endl;
  cout<<"Tura najmanja grana: "<<G1.turaNajmanjaGrana()<<endl;
  cout<<"2opt tura: "<<G1.two_opt()<<endl;
  t2=clock();
  float prva ((float)t2-(float)t1);
  cout<<"Vrijeme izvrsavanja 2opt-a: "<<prva/CLOCKS_PER_SEC<<endl;
  cout<<"3opt tura: "<<G1.three_opt()<<endl;
  t2=clock();
  float prva1 ((float)t2-(float)t1);
  cout<<"Vrijeme izvrsavanja 3opt-a: "<<prva1/CLOCKS_PER_SEC<<endl;
  cout<<endl;

  t1=clock();
  string filename2("westernSahara.txt");
  Graf G2(filename2);
  cout<<"***********WESTERN SAHARA***********"<<endl;
  cout<<"Tura najblizi susjed: "<<G2.turaNajbliziSusjed()<<endl;
  cout<<"Tura najmanja grana: "<<G2.turaNajmanjaGrana()<<endl;
  cout<<"2opt tura: "<<G2.two_opt()<<endl;
  t3=clock();
  float druga ((float)t3-(float)t1);
  cout<<"Vrijeme izvrsavanja 2opt-a: "<<druga/CLOCKS_PER_SEC<<endl;
  cout<<"3opt tura: "<<G2.three_opt()<<endl;
  t3=clock();
  float druga1 ((float)t3-(float)t1);
  cout<<"Vrijeme izvrsavanja: "<<druga1/CLOCKS_PER_SEC<<endl;
  cout<<endl;

  t1=clock();
  string filename3("qatar.txt");
  Graf G3(filename3);
  cout<<"***********QATAR***********"<<endl;
  cout<<"Tura najblizi susjed: "<<G3.turaNajbliziSusjed()<<endl;
  cout<<"Tura najmanja grana: "<<G3.turaNajmanjaGrana()<<endl;
  cout<<"2opt tura: "<<G3.two_opt()<<endl;
  t4=clock();
  float treca ((float)t4-(float)t1);
  cout<<"Vrijeme izvrsavanja 2opt-a: "<<treca/CLOCKS_PER_SEC<<endl;
  cout<<"3opt tura: "<<G3.three_opt()<<endl;
  t4=clock();
  float treca1 ((float)t4-(float)t1);
  cout<<"Vrijeme izvrsavanja 3opt-a: "<<treca1/CLOCKS_PER_SEC<<endl;
  cout<<endl;

  t1=clock();
  string filename4("luksemburg.txt");
  Graf G4(filename4);
  cout<<"***********LUKSEMBURG***********"<<endl;
  cout<<"Tura najblizi susjed: "<<G4.turaNajbliziSusjed()<<endl;
  cout<<"Tura najmanja grana: "<<G4.turaNajmanjaGrana()<<endl;
  cout<<"2opt tura: "<<G4.two_opt()<<endl;
  t5=clock();
  float cetvrta ((float)t5-(float)t1);
  cout<<"Vrijeme izvrsavanja 2opt-a: "<<cetvrta/CLOCKS_PER_SEC<<endl;
  cout<<"3opt tura uzima previse vremena."<<endl;
  cout<<endl;

  return 0;
}
