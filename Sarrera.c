/* Fitxategui honetan jokoa kargatzen den hasierako pantaila da, hau da, jokoaren sarrera.
Honek hiru botoi ditu: bata jokoa hasteko, bestea instrukzioetara eramaten dizuna eta azkenik, amaitu jartzen duen botoia, jokotik ireteteko
aukera ematen duena.
*/

//.h
#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"
#include "OurTypes.h"
#include "Instrukzioak.h"
#include "Jokoa.h"
#include "Sarrera.h"
#include "JokoaLvL2.h"
#include "JokoaLvL3.h"

//Kargatuko diren elementuak
#define PORTADA ".\\img\\portada.bmp"
#define NIBELA ".\\img\\nibelak.bmp"
#define INTRO_SOUND ".\\sound\\Lift.wav" 

GURE_GAUZAK gureGauzak;// Argazkiak kargatzeko fitxategia

void sarrera(void)
{
  int ebentu = 0, irten = 0;
  POSIZIOA pos;
  audioTerminate();
  audioInit();
  loadTheMusic(INTRO_SOUND);//Pantaila kargatzerakoan jartzen den musika
  playMusic();
  sarreraPantailaBistaratu();//Bistaratuko den pantaila
  while (!irten)//Teklen etasaguaren funtzionamendua gauzatzeko
  {
    ebentu = ebentuaJasoGertatuBada();
    if (ebentu == SAGU_BOTOIA_EZKERRA)// saguak ematen duen aukerak:
    {
      pos = saguarenPosizioa();
      if ((pos.x > 465) && (pos.x < 615) && (pos.y > 270) && (pos.y < 270 + 50)) irten = 1;//Jokotik ireteteko botoia
      else if ((pos.x > 25) && (pos.x < 175) && (pos.y > 270) && (pos.y < 270 + 50)) { pantailaGarbitu(); irten = nibelaAukeratu(); }//Jokora eramaten duen botoia
      else if ((pos.x > 230) && (pos.x < 410) && (pos.y > 270) && (pos.y < 270 + 50)) { pantailaGarbitu(); irten = instrukzioa1(); }//Instrukzioeta eramaten duen botoia
    }
    if (ebentu == TECLA_RETURN) //Musika kentzeko/jartzeko aukera ematen du
      toggleMusic();
  }

  sgItxi();
}

//Sarrerako pantailan agertu(kargatu) behar diren elemntuak
void sarreraPantailaBistaratu(void)
{
  audioInit();
  textuaGaitu();
  pantailaGarbitu();
  gureGauzak.fondo = irudiaKargatu(PORTADA);
  irudiaMugitu(gureGauzak.fondo, 0, 0);
  irudiakMarraztu();
  arkatzKoloreaEzarri(0, 0, 0);
  //Botoiak, pantailan bertan idatzita
  errektangeluaMarraztu(25, 270, 150, 50);
  textuaIdatzi(70, 280, "HASI");
  errektangeluaMarraztu(230, 270, 180, 50);
  textuaIdatzi(250, 280, "INSTRUKZIOAK");
  errektangeluaMarraztu(465, 270, 150, 50);
  textuaIdatzi(505, 280, "AMAITU");
  pantailaBerriztu();
}


int nibelaAukeratu(void) //Nibel desberdinak aukeratzeko funtzioa.
{
  int ebentu = 0, gelditu = 0;
  POSIZIOA pos;

  
  textuaGaitu();
  pantailaGarbitu();
  gureGauzak.fondo = irudiaKargatu(NIBELA);
  irudiaMugitu(gureGauzak.fondo, 0, 0);
  irudiakMarraztu();
  pantailaBerriztu();

  while (!gelditu)
  {
    ebentu = ebentuaJasoGertatuBada();
    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
      pos = saguarenPosizioa();
      if ((pos.x > 30) && (pos.x < 520) && (pos.y > 40) && (pos.y < 130)) { gelditu = 1; pantailaGarbitu(); jokoa();}
      else if ((pos.x > 30) && (pos.x < 520) && (pos.y > 190) && (pos.y < 280)) { gelditu = 1; pantailaGarbitu(); jokoa2(); }
      else if ((pos.x > 30) && (pos.x < 520) && (pos.y > 340) && (pos.y < 430)) { gelditu = 1; pantailaGarbitu(); jokoa3(); }
    }
    if (ebentu == TECLA_RETURN) toggleMusic();
  }

  return gelditu;
}