#include <stdio.h>
#include <stdbool.h>

//LONG INT - hodnoty cisel || INT = Indexy v poliach (s vynimkou globalneho prvocisla G ktore podla zadania nikdy nepresiahne INT a nemeni sa)
//Funkcie na overovanie prvociselnosti
bool isPrimeNumber(long int);

//Funkcie na spracovanie vstupu
voidparseExpression(int);
voidfeedLine(char *);
voidfeedSpaces(char *);
int parseInt(char *, int *);
voidparseTerm(long int *, char *, int);

//Funkcie na pracu s globalnou maticou
voidnormMatrix();
voidflushMatrix();
voidelimination();
voidsolutions (int, int);
int max (int, int);
voidswap_rows (int, int, int);
voidsubstractRow (int, int, int);
voidmultiRow (long int, int, int);

//Funkcie na pracu s cislami
long int inverse(long int);
long int sqrt_get(long int);
long int power(long int, long int);
long int sqrt_help(long int, long int, long int);

//Funkcie na vypis
void printSolutions(int);
void printMatrix(int,int);


long int matrix[10][11];
long int output[10];
int g = 0;
int flag = 0;

int
main(int argc, char const *argv[])
{
  //Ak je zapnuty prepinac, uprav globalnu premennu
  if ((argc == 2) && (*(*++argv) == '-') && (*++(*argv) == 'e')) { 
    flag = 1;
  }

  //Nacitaj zo vstupu jedno cislo, docitaj riadok do konca a over prvociselnost
  char c = getchar();
  parseInt(&c, &g);
  feedLine(&c);
  if (!isPrimeNumber(g)) {
    printf("NOT A PRIME\n");
    return 0;
  }

  //M - pocet rovnic, N - pocet premennych
  int m,n;
  
  //nacitaj dve cisla a docitaj riadok
  c = getchar();
  parseInt(&c, &n);
  feedSpaces(&c);
  parseInt(&c, &m);
  feedLine(&c);

  //pokracuj az do -1 -1
  //while ((m >= 0) || (n >= 0)) {
    flushMatrix();//vyprazdnit maticu a riesenia

    //precitaj vsetky rovnice
    for (int i = 0; i < m; ++i) {
      parseExpression(i);
    }

    //Gaussian elimination
    normMatrix();
    elimination(n+1,m);
    printMatrix(n+1,m);
    
    solutions(n+1,m);
    
    //Precitaj dalsie dve cisla
    //c = getchar();
    //parseInt(&c, &n);
    //feedSpaces(&c);
    //parseInt(&c, &m);
    //feedLine(&c);
    //}
  return 0;
}

/**
   Funkcia predpoklada ze matica je v schodovitom tvare a nasledne z nej vycita riesenia
   Ako argumenty berie rozmery matice
*/
void 
solutions(int col, int row) 
{
  int x = -1;
  int y = col - 1;
  //Hlada v matici riadky indikujuce prazdnu mnozinu rieseni (0=2 a pod.)
  do {
    x++;
    if(x == row) break;
    y = col - 1;
    while ((matrix[x][y] == 0) && (y >- 1)) {
      y--;
    }
    //ak su vsetko nuly okrem absolutneho clena, sustava nema riesenie
    if (y == 0) {
      printf("NO SOLUTION\n");
      return;
    }
  } while (y == -1); //ak je cely riadok nulovy, pokracuje sa a neberie sa do uvahy
  y = 1;
  int skipped = 0; //urcuje pocet volnych parametrov
  long int sol = 1;
  //Pre kazdy zostavajuci platny riadok vycitame riesenia
  while ((x < row) && (y < col)) {
    skipped = y;
    y = col - 1;
    //najde prvu nenulovu hodnotu najviac vpravo
    while (matrix[x][y] == 0) {
      --y;
    }
    //aktualizuje sa pocet rieseni podal poctu preskocenych neznamych
    skipped = y - skipped;
    sol = sol * power(g, skipped);
    skipped = 0;
    //vystupna hodnota sa vypocita podla zvysnych hodnot v riadku matice
    output[y-1] = -1 * matrix[x][0];
    output[y-1] = output[y-1] % g;
    for (int i = y-1; i > 0; --i) {
      output[y-1] = output[y-1] - output[i-1] * matrix[x][i];
      output[y-1] = output[y-1] % g;
    }
    if (output[y-1] < 0) {
      output[y-1] += g;
    }
    ++y;
    ++x;
  }
  //zapocitaju sa pripadne nulove stlpce na konci matice
  while ((matrix[x-1][y] == 0) && (y<col)) {
    ++skipped;
    ++y;
  }
  //ak je pocet rovnic 0, nic z vyssie uvedeneho sa nestalo a tak treba zratat riesenia nanovo
  if (x == 0) {
    while ((matrix[x][y] == 0) && (y<col)) {
      ++skipped;
      ++y;
    }
  }
  sol = sol * power(g, skipped);
  
  //Vypis
  if (sol == 1) {
    printf("ONE SOLUTION\n");
  } else {
    if(flag == 0) {
      printf("MANY SOLUTIONS\n");
    } else {
      if((sol <= 1000000000000) && (sol>1)) {
	printf("%ld SOLUTIONS\n", sol);
      } else {
	printf("TOO MANY SOLUTIONS\n");
      }
    }
  }
  //vypis samotnych rieseni
  printSolutions(col - 1);
}

//mocnicna a na e pre a > 0
long int 
power(long int a, long int e) 
{
  if (e < 1) return 1;
  if (e == 1) return a;
  else return a*power(a, e - 1);
}

//vypis riesenie x1...xN
void 
printSolutions(int n) 
{
  for (int i = 0; i < n; ++i)
    {
      printf("x%d = %ld\n", i+1, output[i]);
    }
}

//Gaussova eliminacia - argumenty = rozmery matice
void 
elimination(int col, int row) 
{
  int x = row - 1;
  int y = col - 1;
  while ((x >= 0) && (y >= 1)) {
    //najdem maximum v danom stlpci
    int max_row = max(y, x);
    //ak je max = 0, preskocim nulovy stlpec
    if (matrix[max_row][y] == 0) {
      --y;
      continue;
    }
    //vymenim maximum
    if (max_row != x) swap_rows(max_row, x, col);
    //upravim riadok tak aby "zacinal" 1
    multiRow(inverse(matrix[x][y]), x, col); 
    //odcitam ho od zvysnych riadkov tak aby vznikli nuly
    for (int i = x-1; i >= 0; --i)
      {
	if (matrix[i][y] == 0) {
	  continue;
	}
	if (matrix[i][y] != 1) {
	  multiRow(inverse(matrix[i][y]), i, col);
	}
	substractRow(x, i, col);
      }
    --x;
    --y;

  }
}

// Odcitam od riadka B riadok A, col urcuje dlzku riadka
void 
substractRow(int a, int b, int col) 
{
  for (int i = 0; i < col; ++i)
    {
      matrix[b][i] = (matrix[b][i] - matrix[a][i]) % g;
      if (matrix[b][i] < 0) {
	matrix[b][i] += g;
      }
    }
}

//Vynasobi riador R konstantov E, col urcuje dlzku riadka
void 
multiRow(long int e, int r, int col) 
{
  for (int i = 0; i < col; ++i)
    {
      matrix[r][i] = (e * matrix[r][i]) % g;
    }
}

//hlada maximum v stlpci s indexom column, zacina od riadka start
int 
max(int column, int start) 
{
  int max = start;
  for (int i = start; i >= 0; --i)
    {
      if (matrix[i][column] > matrix[max][column]) {
	max = i;
      }
    }
  return max;
}

//vymeni dva riadky M a N, len urcuje dlzku riadka
void 
swap_rows(int m, int n, int len) 
{
  long int cache = 0;
  for (int i = 0; i < len; ++i) {
    cache = matrix[m][i];
    matrix[m][i] = matrix[n][i];
    matrix[n][i] = cache;
  }
}

//Pomocou rozsireneho euklidovho algoritmu pocita inverznu hodnotu k zadanemu cislu B
long int 
inverse(long int b) 
{
  if(b == 0 || b == 1) {
    return 1;
  }
  long int a = g;
  long int mod = 0;
  long int q0 = 0;
  long int q1 = 1;
  long int q2 = 0;
  while (b != 1) {
    q2 = -1 * q1 * (a / b) + q0;
    q0 = q1;
    q1 = q2;
    mod = a % b;
    a = b;
    b = mod;
  }
  if (q2<0) {
    q2 = q2 + g;
  }
  return q2;
}

//Precita jeden cely riadok s rovnicou - line urcuje cislo rovnice
void 
parseExpression(int line) 
{
  int e = 1;
  char c = getchar();
  parseTerm(matrix[line], &c, e);
  while (c == '+') {
    c = getchar();
    parseTerm(matrix[line], &c, e);
  }
  if (c == '=') {
    e = -1;
    c = getchar();
  }
  parseTerm(matrix[line], &c, e);
  while (c == '+') {
    c = getchar();
    parseTerm(matrix[line], &c, e);
  }
  feedLine(&c);
}

//Precita jeden vyraz (a | xb | a xb) zo vstupu a ulozi ho do matice na prislusnu poziciu - row, riadok matice - c, znak obsahujuci zaciatok vyrazu, e - indikuje znamieknko vyrazu
void 
parseTerm(long int *row, char *c, int e) 
{
  int a = 0;
  int x = 0;
  int lenA = 0;
  int lenX = 0;
  feedSpaces(c);
  lenA = parseInt(c, &a);
  feedSpaces(c);
  if (*c == 'x') { 
    *c = getchar();
    lenX = parseInt(c, &x); 
  }
  if ((lenX > 0) && (lenA == 0)) a = 1;
  feedSpaces(c);
  row[x] = (row[x] + a * e) % g;
}

//Precita jedno cele cislo zo vstupu a ulozi ho do Z (c obsahuje prvy znak cisla)
int 
parseInt(char *c, int *z) 
{
  int x = 0;
  int e = 1;
  int r = 0;
  if (*c == '-') {
    ++r;
    e = -1;
    *c = getchar();
  }
  while ((*c >= '0') && (*c <='9')) {
    ++r;
    x = (x * 10) + (int)(*c - '0');
    *c = getchar();
  }
  *z = x * e; 
  return r;
}

//precita znaky az do konca riadku
void 
feedLine(char *c) 
{
  while (*c != '\n') { 
    *c = getchar(); 
  }
}

//precita vsetky volne medzery
void 
feedSpaces(char * c) 
{
  while(*c == ' ') {
    *c = getchar(); 
  }
}


//vypise maticu (kontrola)
void 
printMatrix(int n, int m) 
{
  for (int i = 0; i < m; ++i)
    {
      for (int j = 0; j < n; ++j)
	{
	  printf("%ld, ", matrix[i][j]);
	}
      printf("\n");
    }
}

//vynuluje maticu a riesenia
void 
flushMatrix() 
{
  for (int i = 0; i < 10; ++i)
    {
      output[i] = 0;
      for (int j = 0; j < 11; ++j)
	{
	  matrix[i][j] = 0;
	}
    }
}

//vynormuje maticu (odstrani zaporne cisla a cisla vacise ako G)
void 
normMatrix() 
{
  for (int i = 0; i < 10; ++i)
    {
      for (int j = 0; j < 11; ++j)
	{
	  matrix[i][j] = matrix[i][j] % g;
	  if (matrix[i][j] < 0) {
	    matrix[i][j] = matrix[i][j] + g;
	  }
	}
    }
}

//Linearne overenie prvociselnosti
bool 
isPrimeNumber(const long int x) 
{
  if(x == 1) {
    return false;
  }
  if(x == 2) {
    return true;
  }
  long int z = 2;
  if(x % z == 0) {
    return false;
  }
  long int c = sqrt_get(x);
  ++z;
  while (z <= c) {
    if (x % z == 0) {
      return false;
    }
    z=z + 2;
  }
  return true;
}

//Rekurzivne binarne hladanie odmocniny:
long int 
sqrt_get(long int x) 
{
  return sqrt_help(x,x / 2,x / 2);
}

long int 
sqrt_help(long int condition, long int aproximation, long int accuracy) 
{
  if((accuracy == 0) || (aproximation * aproximation == condition)) { 
    return aproximation; 
  } else if (aproximation * aproximation > condition) { 
    return sqrt_help(condition, aproximation - accuracy / 2 - (accuracy % 2), accuracy / 2); 
  } else if (aproximation * aproximation < condition) { 
    return sqrt_help(condition, aproximation + accuracy / 2 + (accuracy % 2), accuracy / 2); 
  } else return 0;
}
