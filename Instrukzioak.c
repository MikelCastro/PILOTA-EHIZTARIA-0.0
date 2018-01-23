/* Fitxategui honetan instrukzioen pantailan agertzen den guztia dago.
JOkoaren helburua eta nola jokatu behar den azaltzen du. Baita ere, erabili beharko dituzun teklak erakuzten dizu.
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
#define INSTRUK ".\\img\\foto.bmp"
#define GEZIA1 ".\\img\\gezia.bmp"
#define GEZIA2 ".\\img\\flecha.bmp"
#define GEZIAK ".\\img\\geziak.bmp"
#define SPACEBAR ".\\img\\spaceBar.bmp"
#define RETURN ".\\img\\return.bmp"
#define BACKSPACE ".\\img\\backspace.bmp"
#define ESCAPE ".\\img\\escape.bmp"
GURE_GAUZAK gureGauzak;//Kargatuko diren elementuen fitxategia

// 1.orriko instrukzioak
int instrukzioa1(void)
{
  int ebentu = 0, gelditu = 0;
  POSIZIOA pos;

  jokoarenInstrukzioak1Bistaratu();//1.orria

  //Teklen etasaguaren funtzionamendua gauzatzeko

  while (!gelditu)
  {
    ebentu = ebentuaJasoGertatuBada();
    if (ebentu == SAGU_BOTOIA_EZKERRA)//saguak ematen dituen aukerak:
    {
      pos = saguarenPosizioa();
      if ((pos.x > 10) && (pos.x < 220) && (pos.y > 400) && (pos.y < 455)) { gelditu = 1; pantailaGarbitu(); sarrera(); }//Sarrerara eramaten duen botoia
      else if ((pos.x > 420) && (pos.x < 630) && (pos.y > 400) && (pos.y < 455)) { gelditu = 1; pantailaGarbitu(); instrukzioa2(); }//Instrukzio gehiagoetara eramen duen botoia
    }
    if (ebentu == TECLA_RETURN) //Musika kentzeko/jartzeko aukera
      toggleMusic();
  }
  return gelditu;
}
// 2.orriko instrukzioak
int instrukzioa2(void)
{
  int ebentu = 0, gelditu = 0;
  POSIZIOA pos;

  jokoarenInstrukzioak2Bistaratu();

  while (!gelditu)
  {
    ebentu = ebentuaJasoGertatuBada();
    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
      pos = saguarenPosizioa();
	  if ((pos.x > 10) && (pos.x < 220) && (pos.y > 400) && (pos.y < 455)) { gelditu = 1; pantailaGarbitu(); instrukzioa1(); }//Lehenengoko orrira bueltatzeko botoia
	  else if ((pos.x > 420) && (pos.x < 630) && (pos.y > 400) && (pos.y < 455)) { gelditu = 1; pantailaGarbitu(); instrukzioa3(); }// Hurrengo orrira eramaten duen botoia
    }
    if (ebentu == TECLA_RETURN) toggleMusic();
  }

  return gelditu;
}
// 3.orriko instrukzioak
int instrukzioa3(void)
{
	int ebentu = 0, gelditu = 0;
	POSIZIOA pos;

  jokoarenInstrukzioak3Bistaratu();

	while (!gelditu)
	{
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == SAGU_BOTOIA_EZKERRA)
		{
			pos = saguarenPosizioa();
			if ((pos.x > 10) && (pos.x < 220) && (pos.y > 400) && (pos.y < 455)) { gelditu = 1; pantailaGarbitu(); instrukzioa2(); }//Bigarren orrira bueltatzeko botoia
      else if ((pos.x > 420) && (pos.x < 630) && (pos.y > 400) && (pos.y < 455)) { gelditu = 1; pantailaGarbitu(); nibelaAukeratu(); }//Jokoa hasteko botoia
		}
		if (ebentu == TECLA_RETURN) toggleMusic();
	}

	return gelditu;
}
//Instrukzioetako informazioa bistaratzeko pantailan(1.orria)
void jokoarenInstrukzioak1Bistaratu(void)
{
  textuaGaitu();
  gureGauzak.idIrudi = irudiaKargatu(INSTRUK);
  irudiaMugitu(gureGauzak.idIrudi, 0, 0);
  gureGauzak.idIrudi = irudiaKargatu(GEZIA1);
  irudiaMugitu(gureGauzak.idIrudi, 590, 410);
  gureGauzak.idIrudi = irudiaKargatu(GEZIA2);
  irudiaMugitu(gureGauzak.idIrudi, 30, 410);
  irudiakMarraztu();
  textuaIdatzi(50, 80, "Pilota ehiztariaren jokoa, kolore berdineko hiru pilota edo gehiago");
  textuaIdatzi(50, 105, "elkartzean datza. Arauak oso errazak dira eta seguruenik aspalditik");
  textuaIdatzi(50, 130, "ezagutuko dituzu, baina, hala ere gogorarazi egingo ditugu:");
  textuaIdatzi(60, 165, "-  Jolasa bukatu egingo da, pilota batek beheko marra ukitu egiten");
  textuaIdatzi(60, 190, "badu.");
  textuaIdatzi(60, 220, "-  Kolore berdineko gero eta pilota gehiago elkartu orduan eta ");
  textuaIdatzi(60, 245, " puntuazio hobeagoa lortzeko aukera izango duzu.");
  textuaIdatzi(75, 425, "ATZERA JOAN");
  textuaIdatzi(440, 425, "AURRERA JOAN");
  pantailaBerriztu();
}
//Instrukzioetako informazioa bistaratzeko pantailan(2.orria)
void jokoarenInstrukzioak2Bistaratu(void)
{
  textuaGaitu();
  gureGauzak.idIrudi = irudiaKargatu(INSTRUK);
  irudiaMugitu(gureGauzak.idIrudi, 0, 0);
  gureGauzak.idIrudi = irudiaKargatu(GEZIA2);
  irudiaMugitu(gureGauzak.idIrudi, 30, 410);
  gureGauzak.idIrudi = irudiaKargatu(GEZIA1);
  irudiaMugitu(gureGauzak.idIrudi, 590, 410);
  gureGauzak.idIrudi = irudiaKargatu(SPACEBAR);
  irudiaMugitu(gureGauzak.idIrudi, 50, 200);
  gureGauzak.idIrudi = irudiaKargatu(GEZIAK);
  irudiaMugitu(gureGauzak.idIrudi, 50, 260);
  irudiakMarraztu();
  textuaIdatzi(60, 80, "-  Jokalariak partida irabazi egingo du, pantailako pilota guztiak");
  textuaIdatzi(60, 105, "desagertu egin direnean.  ");
  textuaIdatzi(50, 140, "Beraz, joko honen helburua ahalik eta tiro gutxien eginez puntu");
  textuaIdatzi(50, 165, "gehien lortzean datza. Jokatzeko honako tekla hauek erabiliko dira:");
  textuaIdatzi(130, 200, "-  SPACE BAR: Pilotak jaurti ahal izateko.");
  textuaIdatzi(130, 260, " -  GEZIAK: Piloten norabideak aldatzeko.");
  textuaIdatzi(75, 425, "ATZERA JOAN");
  textuaIdatzi(440, 425, "AURRERA JOAN");
  pantailaBerriztu();
}
//Instrukzioetako informazioa bistaratzeko pantailan(3.orria)
void jokoarenInstrukzioak3Bistaratu(void)
{
  textuaGaitu();
  gureGauzak.idIrudi = irudiaKargatu(INSTRUK);
  irudiaMugitu(gureGauzak.idIrudi, 0, 0);
  gureGauzak.idIrudi = irudiaKargatu(GEZIA2);
  irudiaMugitu(gureGauzak.idIrudi, 30, 410);
  gureGauzak.idIrudi = irudiaKargatu(RETURN);
  irudiaMugitu(gureGauzak.idIrudi, 50, 100);
  gureGauzak.idIrudi = irudiaKargatu(ESCAPE);
  irudiaMugitu(gureGauzak.idIrudi, 50, 160);
  gureGauzak.idIrudi = irudiaKargatu(BACKSPACE);
  irudiaMugitu(gureGauzak.idIrudi, 50, 220);

  irudiakMarraztu();
  textuaIdatzi(130, 100, "- RETURN: musika jartzeko edo kentzeko.");
  textuaIdatzi(130, 160, "-  ESC: Jokoa gelditzeko, hau da, pause jartzeko.");
  textuaIdatzi(130, 220, "-  BACKSPACE: Aterako diren hurrengo pilotak aldatzeko.");
  textuaIdatzi(75, 425, "ATZERA JOAN");
  textuaIdatzi(480, 425, "JOLASTU");
  pantailaBerriztu();
}