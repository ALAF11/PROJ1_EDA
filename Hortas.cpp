#include <iostream>
#include<string>

#include "Hortas.h"
#include "armazem.h"
#include"struct.h"

using namespace std;

void cria_hortas(int nh, Hortas* p, string* a, string alphabet, Produto* arm) {
    for (int i = 0; i < nh; i++) {
        p[i].area = a[i];
        p[i].capacidade = rand() % 6 + 3;
        p[i].nome = alphabet[i];
        p[i].produtos = 0;
        p[i].listaProdutos = new Produto[p[i].capacidade];
        p[i].registo = new string[200];
        p[i].resT = 0;
        p[i].fertilizaçao = 0;
    }
}

void mostra_hortas(int num_hortas, Hortas* plantacao) {
    for (int i = 0; i < num_hortas; i++) {
        cout << "Horta: " << plantacao[i].nome << " | " << "Responsável: " << plantacao[i].agricultor << " | " << "Capacidade: " << plantacao[i].capacidade << " | " << "Produtos: " << plantacao[i].produtos << " | " << "Área: " << plantacao[i].area << endl;
        for (int j = 0; j < plantacao[i].produtos; j++) {
            cout << "Produto: " << plantacao[i].listaProdutos[j].nome << " | " << "Rega: " << plantacao[i].listaProdutos[j].rega << " | " << "Resistência: " << plantacao[i].listaProdutos[j].resistencia << "%" << endl;
        }
        cout << "------------------------------------------------------------------------------------------" << endl;
    }
}

void colhido(Hortas* plantacao, int nh) {
    for (int i = 0; i < nh; i++) {
        for (int j = 0; j < plantacao[i].produtos; j++) { //percorri todas as hortas com o i e todas as listas de produtos com o j
            if (rand() % 101 < 26) {
                plantacao[i].registo[plantacao[i].resT] = plantacao[i].listaProdutos[j].nome;   //inseri o nome do produto que colhi no registo
                plantacao[i].listaProdutos[j].plantar = true;
                plantacao[i].resT++;
                cout << "Foi colhido um produto " << plantacao[i].listaProdutos[j].nome << " de area " << plantacao[i].listaProdutos[j].area << " da horta " << plantacao[i].nome << endl;
            }
        }
    }

    int k, y, w;
    for (int k = 0; k < nh; k++) {
        int c = 0;
        for (y = w = 0; y < plantacao[k].produtos; y++) {
            if (plantacao[k].listaProdutos[y].plantar == false) {
                plantacao[k].listaProdutos[w++].plantar = plantacao[k].listaProdutos[y].plantar;
            }
            else {
                c++;
            }
        }
        plantacao[k].produtos = plantacao[k].produtos - c;
    }
}