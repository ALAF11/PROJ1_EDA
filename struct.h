#pragma once

using namespace std;

struct Produto {
    string nome;
    string area;
    string fornecedor;
    int rega;
    int temp_para_rega;
    int resistencia;
    bool plantar;
};

struct Hortas {
    string nome;
    string area;
    string agricultor;
    int capacidade;
    int produtos;
    Produto* listaProdutos;
    string* registo;
    int resT;
    int fertilizaçao;
};
