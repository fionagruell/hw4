#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

void read(double* p, const int N, const string fname)
{
  ifstream in(fname.c_str());
  for(int i=0; i<N;i++){
    in>> p[i];
      
  }
  in.close();
  
}
void filter(double* p, const int N)
{
  double p1=p[0];
  double pp=p[1];
  double ppp=(p[N-2]+p[N-1]+p1)/3; //Endpunkt berechnet, ohne dass p [N-1] überschrieben wird
  p[0]=(p[N-1]+p[0]+p[1])/3;//periodische Randbedingungen p[-1]=p[N-1]
  
  for(int i=1; i<N-1; i++){
   pp=p[i]; //Platzhalter speichert p[i], bevor es verändert wird
    p[i]=(p1+pp+p[i+1])/3;
    p1=pp;
  }
  p[N-1]=ppp;
  

}
void write(double* p, const int N){
  ofstream out ("output.dat");
  for(int i=0; i<N; i++){
  out <<p[i] << endl; //Ausgabe in Datei
  }
  out.close();
}

int main(void){
  
  int n; //Anzahl der Glättungsdurchläufe
  n=1;
  const string filename="noisy.txt";
  const int N=237; //# Zeilen zum Auslesen, hier fest
  double* p=new double[N];
  //cout << "Bitte Zahl n der Glättungsvorgänge angeben" << endl;
  //cin >> n;
  //cout << n << "  wurde eingegeben" << endl;
  read(p,N,filename);
  for(int i=1; i<=n;i++){
  filter(p,N);
  }
  write(p,N);
  
delete [] p;
  return 0;  

}
