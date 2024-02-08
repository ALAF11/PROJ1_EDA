#pragma once
#include"struct.h"

using namespace std;

void cria_hortas(int nh, Hortas* p, string* a, string alphabet, Produto* arm);
void mostra_hortas(int num_hortas, Hortas* plantacao);
void colhido(Hortas* plantacao, int nh);