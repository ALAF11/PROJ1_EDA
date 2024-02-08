#pragma once
#include"struct.h"

using namespace std;

void criar_produto(int n_produtos, int nh, string* p, string* a, Produto* s, string* f);
void inserir_produtos(Produto* arm, int* armT, int n_produtos, Produto* novos_p);
void plantar_produtos(Produto* arm, int armT, Hortas* plantacao, int num_hortas);
void remover_produtos(Produto* arm, int* armT);
void mostra_armazem(Produto* arm, int* armT);
void pragas(Hortas* plantacao, int num_hortas);