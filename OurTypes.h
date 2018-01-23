#ifndef OURTYPES_H
#define OURTYPES_H
#define SOINU_KOP 5

#include "ebentoak.h"

typedef enum { JOLASTEN, GALDU, IRABAZI }EGOERA;
typedef enum { IRUDIA, MARGOA, TESTUA } MOTA;

typedef struct
{
  POSIZIOA pos;
  int id;
  MOTA mota;
}JOKO_ELEMENTUA;

typedef struct S_GURE_GAUZAK
{
  int idSounds[SOINU_KOP];
  int idIrudi, idIrudi2, idIrudi3, idIrudi4, fondo, id, idGameOver;
}GURE_GAUZAK;

typedef struct S_PELOTA
{
  double x;
  double y;
  int visible;
  int color;

}PELOTA;

#endif