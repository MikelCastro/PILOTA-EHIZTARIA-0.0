#ifndef JOKOA_H
#define JOKOA_H

int jokoa(void);
void pilotaMultzoaSortu(void);
double radianetara(double angelua);
void jokoPantailaBistaratu(void);
void jokoarenElementuakMugitu(void);
int koloreak(void);
void koloreaEzarri(int aldagaia);
int tiroaEgin(double angle, int time, int o);
void errebotea(double x0, double y0, int v, double angle);
void matrizeaMarraztu(void);
void jaurtigaiaSortu(void);
void jaurtigaiaMarraztu(void);
void hurrengoPilotakSortu(void);
double kainoiakLeft(double angle, int kont);
double kainoiakRight(double angle, int kont);
int pilotaAlDago(double angle);
void pilotaMultzoaJaitsi(void);
int gameOverPantailara(void);
int pausaMenua(int kont);
void jaurtigaiaAldatu(void);
double jaurtigaiaMugitu(double angle, double x0, double y0, int v, double denbora, int r, int t);
int denboraAldaketa(double denbora, int time, int o);
void diagonalaEzkerra(int i, int j);
void diagonalaEskuma(int i, int j);
void diagonalaEskumaErditik(int i, int j);
void horizontalaAurretikAtzera(int i, int j);
void horizontalaAtzetikAurrera(int i, int j);
void horizontalaZentrotikAlboetara(int i, int j);
void bertikalaBehetikGora(int i, int j);
void bertikalaGoitikBehera(int i, int j);
void bertikalaZentrotikAlboetara(int i, int j);
void pilotakEzabatu(int i, int j);
void jokoPantailaBerriztu(void);
#endif
