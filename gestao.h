#pragma once
#include "struct.h"

using namespace std;

void colheitaManual(Hortas* h, int nh);
void atu_temporega(Hortas* plantacao, Produto* arm, int armT, int num_hortas);
void ver_fertilizaçao(Hortas* h, int nh);
void fertilizaçao(Hortas* plantacao, int num_hortas);
void tempo_rega(Hortas* plantacao, int num_hortas);
void nova_area(string* area_das_hortas, string* a, int* t_ah, int* paT, string* area_hortas);
void registoC(Hortas* plantacao, int num_hortas);
void alterar_area(Hortas* plantacao, string* area_das_hortas, int num_hortas, string* a, int paT, int* t_ah);
void gravarh(Hortas* plant, int nh);
void gravar_arm(Produto* arm, int* armT);
void carregar(Hortas* plant, int nh);
void carregar_arm(Produto* arm, int* armT);
void ordem_alfabetica(Hortas* plant, int nh);
void imprimirPlantaçao(Hortas* plant, int nh);
void swap(int& a, int& b);
void limpar_file(string ficheiro);