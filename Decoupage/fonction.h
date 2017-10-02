#ifndef FONCTIONS_H_DEFINE
#define FONCTIONS_H_DEFINE

struct Point
{
  int x, y;
};

struct Block
{
  struct Point origin;
  int width, height;
};

struct Line
{
  struct Point origin;
  int width, height;
};

struct Symbol
{
  struct Point origin;
  int width, height;
};

struct Vector
{
  int capacity_b;
  int size_b;
  struct Block *block;
  int capacity_l;
  int size_l;
  struct Line *line;
  int capacity_s;
  int size_s;
  struct Symbol *symbol;
};

//**************** STRUCT INITIALIZING ***********************
void initPoint(struct Point *point);
void initBlock(struct Block *block);
void initLine(struct Line *line);
void initSymbol(struct Symbol *symbol);

//********************** VECTOR OPERATIONS *******************

struct Vector *make_vector();
void vector_push_back_b(struct Vector *vect, struct Block *data);
void vector_push_back_l(struct Vector *vect, struct Line *data);
void vector_push_back_s(struct Vector *vect, struct Symbol *data);

//******************** PIXEL OPERATIONS **********************
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getPixel(SDL_Surface *surface, int x, int y);

//******************** DRAWING *****************************
void drawLines(SDL_Surface *ecran, struct Line line);
void drawColumns(SDL_Surface *ecran, struct Symbol symbol);

//******************** TO PERFECT IMAGE *********************
void blackNWhite(SDL_Surface *ecran);
void eraseLonelyPoint(SDL_Surface *ecran);
//void fillHole(SDL_Surface *ecran);

//**************** BLOCK DETECTION ************************
void blockDetection(SDL_Surface *screen, struct Vector *block);
void createBlock(SDL_Surface *screen, struct Block *block);
void drawBlockBorders(SDL_Surface *screen, struct Block *block);
void searchUpperBorder(SDL_Surface *screen, struct Block *block, int size);
void searchLeftBorder(SDL_Surface *screen, struct Block *block, int size);
void searchBottomBorder(SDL_Surface *screen, struct Block *block, int size);
void searchRightBorder(SDL_Surface *screen, struct Block *block, int size);

//***************** LINE DETECTION *************************
void lineDetection(SDL_Surface *ecran, struct Block *block, struct Vector *line);
void drawLines(SDL_Surface *ecran, struct Line line);

//********************** SYMBOL DETECTION ***********************
void charDetection(SDL_Surface *ecran, struct Line *line, struct Vector *symbol);
void drawBorders(SDL_Surface *ecran, struct Symbol symbol);

#endif
