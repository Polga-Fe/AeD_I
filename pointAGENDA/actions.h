#ifndef ACTIONS_H
#define ACTIONS_H

/*typedef struct Agenda{}Agenda;*/

void Agenda(char *pBuffer);
void addCtt(char **pBuffer, int *size, char *name);
void removeCtt(char **pBuffer, int *size, char *name);
void searchCtt();

#endif