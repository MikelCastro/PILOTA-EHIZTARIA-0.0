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
#include "JokoaLvL2.h"

#define HOME ".\\img\\SarreraB.bmp"
#define BERRIRO ".\\img\\BerriroB.bmp"
#define ITXI ".\\img\\itxiB.bmp"
#define PAUSE ".\\img\\pause.bmp"
#define GAME_OVER ".\\img\\galduPantaila.bmp"

#define HORIA 255, 255, 51
#define URDINA 0, 51, 255
#define BERDEA 0, 255, 102
#define LARANJA 255, 87, 51
#define MOREA 171, 71, 188
#define ZURIA 255,255,255
#define BELTZA 0,0,0
#define GORRIA 204,0,0
#define TURKESA 38, 198, 218

#define LIMITE_EZKERRA 227
#define LIMITE_ESKUMA 640


#define JOKOA_SOUND ".\\sound\\Candyland.wav"
#define GAMEOVER_SOUND ".\\sound\\Game Over.wav" 

#define L2_FONDO ".\\img\\L2pantaila2.bmp"
#define L2_NOVENTA ".\\img\\L2canon90.bmp"
#define L2_SETENTA ".\\img\\L2canon75.bmp"
#define L2_CUARENTA ".\\img\\L2canon45.bmp"
#define L2_VEINTE ".\\img\\L2canon25.bmp"
#define L2_SETENTAM ".\\img\\L2canon-75.bmp"
#define L2_CUARENTAM ".\\img\\L2canon-45.bmp"
#define L2_VEINTEM ".\\img\\L2canon-25.bmp"

#define PI 3.14159265358979323846
#define RADIO 15

GURE_GAUZAK gureGauzak;
PELOTA PM[14][11], jaurtigaia[4];
char str[20]; double d1 = 0;

int jokoa2(void)
{
  double angle = 90;
  int gertatu = 0;
  int ebentu = 0;
  int kont = 0, o = 0;
  int time;
  POSIZIOA pos;

  audioTerminate();
  audioInit();
  loadTheMusic(JOKOA_SOUND);
  playMusic();

  jokoPantailaBistaratu2();
  jaurtigaiaSortu2();
  time = GetTickCount();
  jaurtigaiaMarraztu2();
  pilotaMultzoaSortu2();
  matrizeaMarraztu2();
  pantailaBerriztu();

  while (!gertatu)
  {
    ebentu = ebentuaJasoGertatuBada();
    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
      pos = saguarenPosizioa();
      if ((pos.x > 90) && (pos.x < 90 + 60) && (pos.y > 400) && (pos.y < 400 + 60)) { jokoPantailaBerriztu2(); }
      else if ((pos.x > 90 + 60 + 10) && (pos.x < 220) && (pos.y > 400) && (pos.y < 400 + 60)) { gertatu = 1; }
      else if ((pos.x > 20) && (pos.x < 20 + 60) && (pos.y > 400) && (pos.y < 400 + 60)) { gertatu = 1; pantailaGarbitu(); sarrera(); }
    }
    if (ebentu == TECLA_SPACE)
    {
      o = tiroaEgin2(angle, time, o);
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
      angle = kainoiakLeft2(angle, kont);
      kont--;
    }
    if (ebentu == TECLA_RIGHT)
    {
      angle = kainoiakRight2(angle, kont);
      kont++;
    }
    if (ebentu == TECLA_BACKSPACE)
    {
      hurrengoPilotakSortu2();
      jaurtigaiaMarraztu2();
      pantailaBerriztu();
    }
    if (ebentu == TECLA_RETURN)
      toggleMusic();

    if (ebentu == TECLA_ESCAPE)
    {
      kont = pausaMenua2(kont);
    }
  }

  return gertatu;
}

double kainoiakLeft2(double angle, int kont)
{
  pantailaGarbitu();
  if (kont == 3)
  {
    irudiaKendu(gureGauzak.id);
    angle = 135;
    gureGauzak.id = irudiaKargatu(L2_CUARENTA);
  }
  if (kont == 2)
  {
    irudiaKendu(gureGauzak.id);
    angle = 105;
    gureGauzak.id = irudiaKargatu(L2_SETENTA);
  }
  if (kont == 1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 90;
    gureGauzak.id = irudiaKargatu(L2_NOVENTA);
  }
  if (kont == 0)
  {
    irudiaKendu(gureGauzak.id);
    angle = 75;
    gureGauzak.id = irudiaKargatu(L2_SETENTAM);
  }
  if (kont == -1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 45;
    gureGauzak.id = irudiaKargatu(L2_CUARENTAM);
  }
  if (kont == -2)
  {
    angle = 25;
    gureGauzak.id = irudiaKargatu(L2_VEINTEM);
  }
  irudiaMugitu(gureGauzak.id, 382, 375);
  irudiakMarraztu();
  jokoarenElementuakMugitu();
  matrizeaMarraztu2();
  jaurtigaiaMarraztu2();
  pantailaBerriztu();
  return (double)angle;
}

double kainoiakRight2(double angle, int kont)
{
  pantailaGarbitu();
  if (kont == -2)
  {
    irudiaKendu(gureGauzak.id);
    angle = 45;
    gureGauzak.id = irudiaKargatu(L2_CUARENTAM);
  }
  if (kont == -1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 75;
    gureGauzak.id = irudiaKargatu(L2_SETENTAM);
  }
  if (kont == 0)
  {
    irudiaKendu(gureGauzak.id);
    angle = 90;
    gureGauzak.id = irudiaKargatu(L2_NOVENTA);
  }
  if (kont == 1)
  {
    irudiaKendu(gureGauzak.id);
    angle = 105;
    gureGauzak.id = irudiaKargatu(L2_SETENTA);
  }
  if (kont == 2)
  {
    angle = 135;
    gureGauzak.id = irudiaKargatu(L2_CUARENTA);
  }
  if (kont == 3)
  {
    irudiaKendu(gureGauzak.id);
    angle = 155;
    gureGauzak.id = irudiaKargatu(L2_VEINTE);
  }
  irudiaMugitu(gureGauzak.id, 382, 375);
  irudiakMarraztu();
  jokoarenElementuakMugitu();
  matrizeaMarraztu2();
  jaurtigaiaMarraztu2();
  pantailaBerriztu();
  return angle;
}

int koloreak2(void)
{
  int r;
  r = rand() % 7;
  koloreaEzarri2(r);
  return r;
}

void koloreaEzarri2(int aldagaia)
{
  if (aldagaia == 0)
    arkatzKoloreaEzarri(HORIA);
  else if (aldagaia == 1)
    arkatzKoloreaEzarri(URDINA);
  else if (aldagaia == 2)
    arkatzKoloreaEzarri(BERDEA);
  else if (aldagaia == 3)
    arkatzKoloreaEzarri(GORRIA);
  else if (aldagaia == 4)
    arkatzKoloreaEzarri(TURKESA);
  else if (aldagaia == 5)
    arkatzKoloreaEzarri(MOREA);
  else
    arkatzKoloreaEzarri(LARANJA);
}

void pilotaMultzoaSortu2(void)
{
  srand((unsigned int)time(NULL));
  int i = 13;
  int j = 10, k = 300, m = 605;

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
      PM[i][j].color = koloreak2();
      zirkuluaMarraztu(PM[i][j].x = m, PM[i][j].y = k, RADIO);
    }

    m -= 35;
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

void jaurtigaiaAldatu2(void)
{
  jaurtigaia[0].color = jaurtigaia[3].color;
  jaurtigaia[3].color = jaurtigaia[2].color;
  jaurtigaia[2].color = jaurtigaia[1].color;
  jaurtigaia[1].color = koloreak2();
  koloreaEzarri2(jaurtigaia[0].color);
  jaurtigaia[0].x = 432;
  jaurtigaia[0].y = 430;
  jaurtigaiaMarraztu2();
  pantailaBerriztu();
}

void hurrengoPilotakSortu2(void)
{
  int i = 1, x = 80, y = 260;
  srand((unsigned int)time(NULL));
  do
  {
    jaurtigaia[i].x = x;
    jaurtigaia[i].y = y;
    jaurtigaia[i].color = koloreak2();
    i++;
    x += 35;
  } while (i <= 3);
}

void jaurtigaiaSortu2(void)
{
  hurrengoPilotakSortu2();
  jaurtigaia[0].color = koloreak2();
  jaurtigaia[0].x = 432;
  jaurtigaia[0].y = 430;
}

void jokoPantailaBistaratu2(void)
{
  gureGauzak.idIrudi = irudiaKargatu(L2_FONDO);
  gureGauzak.idIrudi2 = irudiaKargatu(BERRIRO);
  gureGauzak.idIrudi3 = irudiaKargatu(HOME);
  gureGauzak.idIrudi4 = irudiaKargatu(ITXI);
  gureGauzak.id = irudiaKargatu(L2_NOVENTA);
  jokoarenElementuakMugitu();
  pantailaBerriztu();
}

int denboraAldaketa2(double denbora, int time, int o)
{
  if ((denbora - time) >= 60000 && o == 0)
  {
    pilotaMultzoaJaitsi();
    o = 2;
  }
  return o;
}

int tiroaEgin2(double angle, int time, int o)
{
  double x0 = 432, y0 = 430, denbora = 0;
  int v = 5, t = 0;
  int r = 0;
  angle = radianetara(angle);
  o = 0;

  denbora = jaurtigaiaMugitu2(angle, x0, y0, v, denbora, r, t);

  o = denboraAldaketa2(denbora, time, o);
  jaurtigaiaAldatu2();
  return o;
}

void matrizeaMarraztu2(void)
{
  int i = 13, j = 10;
  do {
    koloreaEzarri2(PM[i][j].color);
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

void jaurtigaiaMarraztu2(void)
{
  int i = 0;
  do {
    koloreaEzarri2(jaurtigaia[i].color);
    zirkuluaMarraztu(jaurtigaia[i].x, jaurtigaia[i].y, RADIO);
    i++;
  } while (i <= 3);
  arkatzKoloreaEzarri(BELTZA);
  errektangeluaMarraztu(35, 240, 160, 40);
  errektangeluaMarraztu(20, 230, 190, 60);
}

int pausaMenua2(int kont)
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
    matrizeaMarraztu2();
    jaurtigaiaMarraztu2();
    pantailaBerriztu();
    kont--;
  }
  toggleMusic();
  irudiaKendu(gureGauzak.id);
  return kont;
}

double jaurtigaiaMugitu2(double angle, double x0, double y0, int v, double denbora, int r, int t)
{
  int aurkituta;
  do {
    jaurtigaia[0].x = x0 - v * cos(angle)*t;
    jaurtigaia[0].y = y0 - v * sin(angle)*t;
    t++;
    pantailaGarbitu();
    jokoarenElementuakMugitu();
    denbora = GetTickCount();
    jaurtigaiaMarraztu2();
    aurkituta = pilotaAlDago(angle);
    matrizeaMarraztu2();
    pantailaBerriztu();
    if (jaurtigaia[0].x <= LIMITE_EZKERRA || jaurtigaia[0].x >= LIMITE_ESKUMA)
    {
      errebotea2(jaurtigaia[0].x, jaurtigaia[0].y, v, angle);
      r = 1;
    }
  } while (!r && !aurkituta && jaurtigaia[0].y >= 0);
  return denbora;
}

void jokoPantailaBerriztu2(void)
{
  d1 = 0;
  pantailaGarbitu();
  jokoarenElementuakMugitu();
  jaurtigaiaSortu2();
  jaurtigaiaMarraztu2();
  pilotaMultzoaSortu2();
  pantailaBerriztu();
}

void errebotea2(double x0, double y0, int v, double angle)
{
  int t = 1, r = 0;
  double denbora = 0;
  angle = angle * (180 / PI);
  angle = 180 - angle;
  angle = radianetara(angle);
  jaurtigaiaMugitu2(angle, x0, y0, v, denbora, r, t);
}
