/* Fitxategi honetan jokoaren pantailako atal guztiak aurkitzen dira.
Funtzioetan banatuta daude, funtzioetako bakoitza bere eginkizuna baitu.
*/

//.h
#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "OurTypes.h"
#include "Jokoa.h"
#include "Sarrera.h"
//Jokoak kargatu behar dituen irudiak
#define HOME ".\\img\\SarreraB.bmp"
#define BERRIRO ".\\img\\BerriroB.bmp"
#define ITXI ".\\img\\itxiB.bmp"
#define PAUSE ".\\img\\pause.bmp"
#define GAME_OVER ".\\img\\galduPantaila.bmp"
//Jokoan ezarrita dauen koloreak

#define HORIA 255, 255, 51
#define URDINA 0, 51, 255
#define BERDEA 0, 255, 102
#define LARANJA 255, 87, 51
#define MOREA 171, 71, 188
#define ZURIA 255,255,255
#define BELTZA 0,0,0

#define LIMITE_EZKERRA 227
#define LIMITE_ESKUMA 640
//Musika

#define JOKOA_SOUND ".\\sound\\Candyland.wav" 
//1.mailan ikusi behar diren atalak: Fondoa eta kanoien argazki guztiak norabide guztietan
#define L1_FONDO ".\\img\\L1pantaila2.bmp"
#define L1_NOVENTA ".\\img\\L1canon90.bmp"
#define L1_SETENTA ".\\img\\L1canon75.bmp"
#define L1_CUARENTA ".\\img\\L1canon45.bmp"
#define L1_VEINTE ".\\img\\L1canon25.bmp"
#define L1_SETENTAM ".\\img\\L1canon-75.bmp"
#define L1_CUARENTAM ".\\img\\L1canon-45.bmp"
#define L1_VEINTEM ".\\img\\L1canon-25.bmp"
//Elementu aldaezinak, konstanteak.

#define PI 3.14159265358979323846
#define RADIO 15
// Estruktura aldaezinak:

PELOTA PM[14][11], jaurtigaia[4];
GURE_GAUZAK gureGauzak;
char str[20]; double d = 0;

int jokoa(void)//Funtzio printzipala, pantailan ikusi eta funtzionatuko duena
{
  double angle = 90;
  int gertatu = 0;
  int ebentu = 0;
  int kont = 0, o=0;
  int time;
  POSIZIOA pos;
  audioTerminate();
  audioInit();
  loadTheMusic(JOKOA_SOUND);
  playMusic();
  jokoPantailaBistaratu();
  jaurtigaiaSortu();
  time = GetTickCount();
  jaurtigaiaMarraztu();
  pilotaMultzoaSortu();
  matrizeaMarraztu();
  pantailaBerriztu();
  
  while (!gertatu)
  {
    ebentu = ebentuaJasoGertatuBada();
    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
      pos = saguarenPosizioa();
      if ((pos.x > 90) && (pos.x < 90 + 60) && (pos.y > 400) && (pos.y < 400 + 60)) { jokoPantailaBerriztu(); }
      else if ((pos.x > 90 + 60 + 10) && (pos.x < 220) && (pos.y > 400) && (pos.y < 400 + 60)) { gertatu = 1; }
      else if ((pos.x > 20) && (pos.x < 20 + 60) && (pos.y > 400) && (pos.y < 400 + 60)) { gertatu = 1; pantailaGarbitu(); sarrera(); }
    }
    if (ebentu == TECLA_SPACE)
    { 
      o=tiroaEgin(angle, time,o);
      if (o == 1)
      {
        gertatu = 1;
      }
      else if (o == 2)
      {
        time = GetTickCount();
      }
    }
    if (ebentu == TECLA_LEFT)
    {
      angle = kainoiakLeft(angle, kont);
      kont--;
    }
    if (ebentu == TECLA_RIGHT)
    {
      angle = kainoiakRight(angle, kont);
      kont++;
    }
    if (ebentu == TECLA_BACKSPACE)
    {
      hurrengoPilotakSortu();
      jaurtigaiaMarraztu();
      pantailaBerriztu();
    }
    if (ebentu == TECLA_RETURN) 
      toggleMusic();
    if (ebentu == TECLA_ESCAPE)
    {
      kont=pausaMenua(kont);
    }
  }

  return gertatu;
}
//Angeluak radianetara pasatzen duen funtzioa

double radianetara(double angelua)
{
  double radianak;
  radianak = (angelua*PI) / 180;
  return radianak;
}

void pilotaMultzoaSortu(void)//Matrizea sortzen duen funtzioa
{
  srand((unsigned int)time(NULL)); //Koloreak aukeratzeko denbora
  int i = 13;
  int j = 10, k = 300, m = 605; // Matrizearen dimentsioak(i, j) eta non kokatuko den koordenatuak(k, m)

  do {
    if (i % 2 != 0 && j == 10)
    {
      PM[i][j].visible = 0;
      m = 620;
      PM[i][j].x = m;
      PM[i][j].y = k;
    }
    else if (i >= 9)
    {
      PM[i][j].visible = 0;
      PM[i][j].x = m;
      PM[i][j].y = k;
    }
    else
    {
      PM[i][j].visible = 1;
      PM[i][j].color = koloreak();
      zirkuluaMarraztu(PM[i][j].x = m, PM[i][j].y = k, RADIO);
    }

    m -= 35;//pilota arteko pix. kop.
    j--;
    if (j < 0)
    {
      i--;
      j = 10;
      k -= 35;
      m = 605;
    }
 pantailaBerriztu();
  } while (i >= 0);
}

void pilotaMultzoaJaitsi(void)//Min 1.5 pasa ostean, Matrizea jaisteko funtzioa
{
  int i, j;
  i = 13;
  j = 10;
  do {
    PM[i][j].y += 35;
    if (j < 0)
    {
      j = 10;
      i--;
    }
    j--;
  } while (i >= 0);
}

void jokoPantailaBistaratu(void)//Pantailan kargatu eta bistaratuko diren irdudiak
{
  gureGauzak.idIrudi = irudiaKargatu(L1_FONDO);
  gureGauzak.idIrudi2 = irudiaKargatu(BERRIRO);
  gureGauzak.idIrudi3 = irudiaKargatu(HOME);
  gureGauzak.idIrudi4 = irudiaKargatu(ITXI);
  gureGauzak.id = irudiaKargatu(L1_NOVENTA);
  jokoarenElementuakMugitu();
  pantailaBerriztu();
}

void jokoarenElementuakMugitu(void)//Pantailan behin eta berriz kargatu beharko diren elementuak(bakoitzak bere koordenatuekin)
{
  irudiaMugitu(gureGauzak.idIrudi, 0, 0);
  irudiaMugitu(gureGauzak.idIrudi2, 90, 400);
  irudiaMugitu(gureGauzak.idIrudi3, 20, 400);
  irudiaMugitu(gureGauzak.idIrudi4, 160, 400);
  irudiaMugitu(gureGauzak.id, 382, 375);
  irudiakMarraztu();
  arkatzKoloreaEzarri(ZURIA);
  zuzenaMarraztu(228, SCREEN_HEIGHT * 4 / 6, 635, SCREEN_HEIGHT * 4 / 6);
  errektangeluaMarraztu(227, 5, 409, 470);
  textuaGaitu();
  textuaIdatzi(10, 10, "Return: musika ON/OFF");
  textuaIdatzi(10, 60, "PUNTUAK: ");
  textuaIdatzi(10, 90, "LEVEL 1");
  sprintf(str, "%0.lf", d);
  textuaIdatzi(130, 60, str);
}

int koloreak(void)//Ezarritako koloreak era random batetan aukeratzeko funtzioa
{
  int r;
  r = rand() % 5;
  koloreaEzarri(r);
  return r;
}

void koloreaEzarri(int aldagaia)//Hasieran definitutako koloreak, ezarritako koloreak aldagai batekin
{
  if (aldagaia == 0)
    arkatzKoloreaEzarri(HORIA);
  else if (aldagaia == 1)
    arkatzKoloreaEzarri(URDINA);
  else if (aldagaia == 2)
    arkatzKoloreaEzarri(BERDEA);
  else if (aldagaia == 3)
    arkatzKoloreaEzarri(MOREA);
  else
    arkatzKoloreaEzarri(LARANJA);
}

int tiroaEgin(double angle, int time, int o) //Pilotaren jaurtiketa gauzatzeko funtzioa + t=0
{
  double x0 = 432, y0 = 430, denbora = 0;
  int v = 5, t = 0;
  int r = 0;
  angle = radianetara(angle);
  o = 0;
  
  denbora = jaurtigaiaMugitu(angle, x0, y0, v, denbora, r, t);

  o = denboraAldaketa(denbora, time, o);
  jaurtigaiaAldatu();
  return o;
}

void errebotea(double x0, double y0, int v, double angle)//Pilota pareten kontra jotzean errebotea gauzatzeko funtzioa
{
  int t = 1, r = 0;
  double denbora = 0;
  angle = angle * (180 / PI);
  angle = 180- angle;
  angle = radianetara(angle);
  jaurtigaiaMugitu(angle, x0, y0, v, denbora, r, t);
}

void matrizeaMarraztu(void)//Matrizea sortu ostean, pilota multzoa marrazteko balio duen funtzioa
{
  int i = 13, j = 10;
  do {
    koloreaEzarri(PM[i][j].color);
    if (PM[i][j].visible != 0)
    {
      zirkuluaMarraztu(PM[i][j].x, PM[i][j].y, RADIO);
    }
    j--;
    if (j < 0)
    {
      i--;
      j = 10;
    }
  } while (i >= 0);
}

int pilotaAlDago(double angle)//Pilota bat visible edo EZ dagoen ikusiten duen funtzioa
{
  int i = 13, j = 10;
  do
  {
    if ((jaurtigaia[0].x > PM[i][j].x - RADIO && jaurtigaia[0].x <PM[i][j].x + RADIO && jaurtigaia[0].y >PM[i][j].y - RADIO && jaurtigaia[0].y < PM[i][j].y + RADIO && PM[i][j].visible))
    {
      if (!PM[i + 1][j].visible)
      {
        PM[i + 1][j].color = jaurtigaia[0].color;
        PM[i + 1][j].visible = 1;
        pilotakEzabatu(i + 1, j);
      }
      else if (!PM[i][j + 1].visible)
      {
        PM[i][j + 1].color = jaurtigaia[0].color;
        PM[i][j + 1].visible = 1;
        pilotakEzabatu(i, j + 1);
      }
      else if (!PM[i][j - 1].visible)
      {
        PM[i][j - 1].color = jaurtigaia[0].color;
        PM[i][j - 1].visible = 1;
        pilotakEzabatu(i, j - 1);
      }
      else if (PM[i + 1][j].visible)
      {
        if (!PM[i + 1][j + 1].visible)
        {
          PM[i + 1][j + 1].color = jaurtigaia[0].color;
          PM[i + 1][j + 1].visible = 1;
          pilotakEzabatu(i + 1, j + 1);
        }
        else
        {
          PM[i + 1][j - 1].color = jaurtigaia[0].color;
          PM[i + 1][j - 1].visible = 1;
          pilotakEzabatu(i + 1, j - 1);
        }
      }
      return 1;
    }
     else
     {
       j--;
       if (j < 0)
       {
         j = 10;
         i--;
       }
     }
  } while (i >= 0);
  return 0;
}

void jaurtigaiaSortu(void)//Botako den pilota sortzen duen funztioa
{
  hurrengoPilotakSortu();
  jaurtigaia[0].color = koloreak();
  jaurtigaia[0].x = 432;
  jaurtigaia[0].y = 430;
}

void jaurtigaiaMarraztu(void)//Botako den pilota sortu ostean, pantailan bistaratzeko funtzioa
{
  int i = 0;
  do {
    koloreaEzarri(jaurtigaia[i].color);
    zirkuluaMarraztu(jaurtigaia[i].x, jaurtigaia[i].y, RADIO);
    i++;
  } while (i <= 3);
  arkatzKoloreaEzarri(BELTZA);
  errektangeluaMarraztu(35, 240, 160, 40);
  errektangeluaMarraztu(20, 230, 190, 60);
}

void hurrengoPilotakSortu(void)//Jaurtigaiko hurrengoko pilotak sortzen duen funtzioa
{
  int i = 1, x = 80, y = 260;
  srand((unsigned int)time(NULL));
  do
  {
    jaurtigaia[i].x = x;
    jaurtigaia[i].y = y;
    jaurtigaia[i].color = koloreak();
    i++;
    x += 35;
  } while (i <= 3);
}

double kainoiakLeft(double angle, int kont) // Ezkerreruntz marraztuko diren kanoiak
{
  //Kontuan artuta Ezkerreko botoia zenbat aldiz(kont) eman, kargatuko da irudi bat edo bestea.
  pantailaGarbitu();
  if (kont == 3)
  {
    irudiaKendu(gureGauzak.id);
    angle = 135;
    gureGauzak.id = irudiaKargatu(L1_CUARENTA);
  }
  if (kont == 2)
  {
    irudiaKendu(gureGauzak.id);
    angle = 105;
    gureGauzak.id = irudiaKargatu(L1_SETENTA);
  }
  if (kont == 1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 90;
    gureGauzak.id = irudiaKargatu(L1_NOVENTA);
  }
  if (kont == 0)
  {
    irudiaKendu(gureGauzak.id);
    angle = 75;
    gureGauzak.id = irudiaKargatu(L1_SETENTAM);
  }
  if (kont == -1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 45;
    gureGauzak.id = irudiaKargatu(L1_CUARENTAM);
  }
  if (kont == -2)
  {
    angle = 25;
    gureGauzak.id = irudiaKargatu(L1_VEINTEM);
  }
  irudiaMugitu(gureGauzak.id, 382, 375);
  irudiakMarraztu();
  jokoarenElementuakMugitu();
  matrizeaMarraztu();
  jaurtigaiaMarraztu();
  pantailaBerriztu();
  return (double)angle;
}

double kainoiakRight(double angle, int kont)//Eskumaruntz marraztuko diren kanoiak
{
  pantailaGarbitu();
  if (kont == -2)
  {
    irudiaKendu(gureGauzak.id);
    angle = 45;
    gureGauzak.id = irudiaKargatu(L1_CUARENTAM);
  }
  if (kont == -1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 75;
    gureGauzak.id = irudiaKargatu(L1_SETENTAM);
  }
  if (kont == 0)
  {
    irudiaKendu(gureGauzak.id);
    angle = 90;
    gureGauzak.id = irudiaKargatu(L1_NOVENTA);
  }
  if (kont == 1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 105;
    gureGauzak.id = irudiaKargatu(L1_SETENTA);
  }
  if (kont == 2)
  {
    angle = 135;
    gureGauzak.id = irudiaKargatu(L1_CUARENTA);
  }
  if (kont == 3)
  {
    irudiaKendu(gureGauzak.id);
    angle = 155;
    gureGauzak.id = irudiaKargatu(L1_VEINTE);
  }
  irudiaMugitu(gureGauzak.id, 382, 375);
  irudiakMarraztu();
  jokoarenElementuakMugitu();
  matrizeaMarraztu();
  jaurtigaiaMarraztu();
  pantailaBerriztu();
  return angle;
}

int gameOverPantailara(void)//Matrizea pantailako lerro txurira heltzen baldin bada, pantaila hau jarriko da. Jokoa galdu duela esanez
{
  int ebentu = 0, gertatu = 0;
  POSIZIOA pos;

  pantailaGarbitu();
  gureGauzak.idGameOver = irudiaKargatu(GAME_OVER);
  irudiaMugitu(gureGauzak.idGameOver, 0, 0);
  irudiakMarraztu();
  pantailaBerriztu();

  while (!gertatu)
  {
    ebentu = ebentuaJasoGertatuBada();
    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
      pos = saguarenPosizioa();
      if ((pos.x > 10) && (pos.x < 10 + 60) && (pos.y > 10) && (pos.y < 10 + 60)) { gertatu = 1; pantailaGarbitu(); sarrera(); }
    }
  }
  return gertatu;
}

int pausaMenua(int kont)//ESC emanez, pausa pantailako funtzioa
{
  if (kont == 0)
  {
    gureGauzak.id = irudiaKargatu(PAUSE);
    irudiakMarraztu();
    pantailaBerriztu();
    kont++;
  }
  else
  {
    pantailaGarbitu();
    jokoarenElementuakMugitu();
    jokoPantailaBistaratu();
    matrizeaMarraztu();
    jaurtigaiaMarraztu();
    pantailaBerriztu();
    kont--;
  }
  toggleMusic();
  irudiaKendu(gureGauzak.id);
  return kont;
}

void jaurtigaiaAldatu(void)//jautigaian agertuko diren hurrengoko koloreak, array-rekin agertzen diren koloreekin erlazionatzen duen funztioa
{
  jaurtigaia[0].color = jaurtigaia[3].color;
  jaurtigaia[3].color = jaurtigaia[2].color;
  jaurtigaia[2].color = jaurtigaia[1].color;
  jaurtigaia[1].color = koloreak();
  koloreaEzarri(jaurtigaia[0].color);
  jaurtigaia[0].x = 432;
  jaurtigaia[0].y = 430;
  jaurtigaiaMarraztu();
  pantailaBerriztu();
}

double jaurtigaiaMugitu(double angle, double x0, double y0, int v, double denbora, int r, int t)
{
  int aurkituta;
  do {
    jaurtigaia[0].x = x0 - v * cos(angle)*t;
    jaurtigaia[0].y = y0 - v * sin(angle)*t;
    t++;
    pantailaGarbitu();
    jokoarenElementuakMugitu();
    denbora = GetTickCount();
    jaurtigaiaMarraztu();
    aurkituta = pilotaAlDago(angle);
    matrizeaMarraztu();
    pantailaBerriztu();
    if (jaurtigaia[0].x <= LIMITE_EZKERRA || jaurtigaia[0].x >= LIMITE_ESKUMA)
    {
      errebotea(jaurtigaia[0].x, jaurtigaia[0].y, v, angle);
      r = 1;
    }
  } while (!r && !aurkituta && jaurtigaia[0].y >= 0);
  return denbora;
}

int denboraAldaketa(double denbora, int time, int o)//1.5min 
{
  if ((denbora - time) >= 90000 && o == 0)
  {
    pilotaMultzoaJaitsi();
    o = 2;
  }
  return o;
}
// Hurrengo funtzioak pilotak nola kendu azaltzen dute, bai diagonalean, bai horizontalean, baita bertikalean
void diagonalaEzkerra(int i, int j)
{
  int k;
  k = i;
  if (PM[i - 1][j].color == PM[i][j].color && PM[i - 2][j - 1].color == PM[i][j].color && PM[i - 2][j - 2].color == PM[i][j].color)
  {
    PM[i - 1][j].visible = 0;
    PM[i - 2][j - 1].visible = 0;
    PM[i - 2][j - 2].visible = 0;
  }
}

void diagonalaEskuma(int i, int j)
{
  int k;
  k = i;
  if (PM[i - 1][j].color == PM[i][j].color && PM[i - 2][j + 1].color == PM[i][j].color && PM[i - 2][j + 2].color == PM[i][j].color)
  {
    PM[i][j].visible = 0;
    PM[i - 1][j].visible = 0;
    PM[i - 2][j + 1].visible = 0;
    PM[i - 2][j + 2].visible = 0;
  }
}

void horizontalaAurretikAtzera(int i, int j)
{
  int k;
  if (PM[i][j - 1].color == PM[i][j].color && PM[i][j - 2].color == PM[i][j].color)
  {
    for (k = 0; k <= -2; k--)
    {
      PM[i][j - k].visible = 0;
    }
  } 
}

void horizontalaAtzetikAurrera(int i, int j)
{
  int k;
  if (PM[i][j + 1].color == PM[i][j].color && PM[i][j + 2].color == PM[i][j].color)
  {
    for (k = 0; k <= 2; k++)
    {
      PM[i][j + k].visible = 0;
    }  
  }
}

void horizontalaZentrotikAlboetara(int i, int j)
{
  int k;
  if (PM[i][j + 1].color == PM[i][j].color && PM[i][j - 1].color == PM[i][j].color)
  {
    for (k = -1; k <= 1; k++)
    {
      PM[i][j + k].visible = 0;
    }
  }
}

void bertikalaBehetikGora(int i, int j)
{
  int k;
  if (PM[i - 1][j].color == PM[i][j].color && PM[i - 2][j].color == PM[i][j].color)
  {
    for (k = -2; k <= 0; k++)
    {
      PM[i + k][j].visible = 0;
    }
  }
}

void bertikalaGoitikBehera(int i, int j)
{
  int k;
  if (PM[i + 1][j].color == PM[i][j].color && PM[i + 2][j].color == PM[i][j].color)
  {
    for (k = 0; k <= 2; k++)
    {
      PM[i + k][j].visible = 0;
    }
  }
}

void bertikalaZentrotikAlboetara(int i, int j)
{
  int k;
  if (PM[i + 1][j].color == PM[i][j].color && PM[i - 1][j].color == PM[i][j].color)
  {
    for (k = -1; k <= 1; k++)
    {
      PM[i + k][j].visible = 0;
    }
  }
}
//Bertikalean, horizontalean eta diagonalean invisible jarritako pilotak guztiz ezabatzeko funtzioa
void pilotakEzabatu(int i, int j)
{
  d += 100;
  diagonalaEzkerra(i, j);
  diagonalaEskuma(i, j);
  diagonalaEskumaErditik(i, j);
  horizontalaAurretikAtzera(i, j);
  horizontalaAtzetikAurrera(i, j);
  horizontalaZentrotikAlboetara(i, j);
  bertikalaBehetikGora(i, j);
  bertikalaGoitikBehera(i, j);
  bertikalaZentrotikAlboetara(i, j);
}

void jokoPantailaBerriztu(void)
{
  d = 0;
  pantailaGarbitu();
  jokoarenElementuakMugitu(); 
  jaurtigaiaSortu(); 
  jaurtigaiaMarraztu(); 
  pilotaMultzoaSortu(); 
  pantailaBerriztu();
}

void diagonalaEskumaErditik(int i, int j)
{
  {
    int k;
    k = i;
    if (PM[i + 1][j + 1].color == PM[i][j].color && PM[i - 1][j].color == PM[i][j].color)
    {
      PM[i + 1][j + 1].visible = 0;
      PM[i - 1][j].visible = 0;
      PM[i][j].visible = 0;
    }
  }
}