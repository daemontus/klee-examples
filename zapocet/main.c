#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int num_of_cols = 64;

typedef
struct riadok {
  char * bunky[64];
  struct riadok * next;
  struct riadok * prev;
} riadok;

typedef 
struct tabulka {
  int skutocnyPocet;
  int maxDlzky[64];
  riadok * first;
  riadok * last;
} tabulka;

char * citajRiadok(FILE * input);
riadok * pridajBunku(riadok * r, char * text, int pozicia);
riadok * novyRiadok();
tabulka * novaTabulka();
tabulka * pridajRiadok(tabulka * t, riadok * r, int pocet);
void vypisTabulku(tabulka * t);

int main(int argc, char const *argv[])
{
  if(argc != 2) {
    perror("invalid argument");
    return 1;
  }
  char * filename =  malloc(sizeof(char)*strlen(argv[1])+1);
  strcpy(filename, argv[1]);

  FILE * input = fopen(filename, "r");
  if(input == NULL) {
    free(filename);
    perror("invlaid file");
    return 1;
  }

  tabulka * table = novaTabulka();

  char * line = citajRiadok(input);
  while(line) {
    riadok * novy = novyRiadok();
    //char * bunka = strtok(line, ",");
    int pocet = 0;
    int i = 0;
    /*while(bunka != NULL) {
      novy = pridajBunku(novy, bunka, pocet);
      bunka = strtok(NULL, ",");
      pocet++;
      }*/
    char * bunka = line;
    int k = strlen(line);
    while(i < k) {
      if(line[i] == ',') {
	line[i] = '\0';
	novy = pridajBunku(novy, bunka, pocet);
	pocet++;
	bunka = line+i+1;
      }
      ++i;
    }
    line[i] = '\0';
    novy = pridajBunku(novy, bunka, pocet);
    pocet++;
    bunka = line+i+1;
    table = pridajRiadok(table, novy, pocet);
    line = citajRiadok(input);
  }
  vypisTabulku(table);
  free(filename);
  return 0;
}

void vypisTabulku(tabulka * t) {
  riadok * akt = t->first;
  while(akt != NULL) {
    for (int i = 0; i < t->skutocnyPocet; ++i)
      {
	printf("#-");
	for (int j = 0; j < t->maxDlzky[i]; ++j)
	  {
	    printf("-");
	  }
	printf("-");
      }
    printf("#");
    printf("\n");
    for (int i = 0; i < t->skutocnyPocet; ++i)
      {
	if(akt->bunky[i] != NULL) {
	  printf("| %-*s ",t->maxDlzky[i], akt->bunky[i]);
	}
	else {
	  printf("| %-*s ",t->maxDlzky[i], " ");
	}
      }
    printf("|");
    printf("\n");
    akt = akt->next;
  }
  for (int i = 0; i < t->skutocnyPocet; ++i)
    {
      printf("#-");
      for (int j = 0; j < t->maxDlzky[i]; ++j)
	{
	  printf("-");
	}
      printf("-");
    }
  printf("#");
  printf("\n");
}

char * citajRiadok(FILE * input) {
  char * line = malloc(1025*sizeof(char));
  memset(line, 0, 1025*sizeof(char));
  char c = fgetc(input);
  int i = 0;
  while(c != '\n' && c != EOF && i<1024) {
    line[i] = c;
    ++i;
    c = fgetc(input);
  }
  if(strlen(line) != 0) return line;
  else {
    free(line);
    return NULL;
  }
}

riadok * pridajBunku(riadok * r, char * text, int pozicia) {
  r->bunky[pozicia] = text;
  return r;
}

riadok * novyRiadok() {
  riadok * r = malloc(sizeof(riadok));
  for (int i = 0; i < num_of_cols; ++i)
    {
      r->bunky[i] = NULL;
    }
  return r;
}

tabulka * novaTabulka() {
  tabulka * t = malloc(sizeof(tabulka));
  t->first = NULL;
  t->last = NULL;
  t->skutocnyPocet = 0;
  for (int i = 0; i < num_of_cols; ++i)
    {
      t->maxDlzky[i] = 0;
    }
  return t;
}

tabulka * pridajRiadok(tabulka * t, riadok * r, int pocet) {
  if(t->last == NULL) {
    t->first = r;
    t->last = r;
  }
  else {
    t->last->next = r;
    r->prev = t->last;
    t->last = r;
  }
  for (int i = 0; i < num_of_cols; ++i)
    {
      if(r->bunky[i] != NULL) {
	if(strlen(r->bunky[i]) > t->maxDlzky[i]) {
	  t->maxDlzky[i] = strlen(r->bunky[i]);
	}
      }
    }
  if(pocet > t->skutocnyPocet) {
    t->skutocnyPocet = pocet;
  }
  return t;
}

