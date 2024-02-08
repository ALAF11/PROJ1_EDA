#include<iostream>
#include<string>
#include"armazem.h"
#include"ficheiros.h"

using namespace std;



void criar_produto(int n_produtos, int nh, string* p, string* a, Produto* s, string *f) {
    for (int i = 0; i < n_produtos; i++) {
        s[i].nome = *(p + rand() % ler_linhas_ficheiro("produtos.txt"));
        s[i].fornecedor = *(f + rand () % ler_linhas_ficheiro("fornecedores.txt"));
        s[i].area = *(a + rand() % nh);
        s[i].rega = rand() % 5 + 1;
        s[i].resistencia =rand() % 101;
        s[i].plantar = false;
        s[i].temp_para_rega = s[i].rega;
    }
}


void inserir_produtos(Produto* arm,int* armT, int n_produtos, Produto* novos_p) {

    int w = 0;
    for (int i = *armT; i < n_produtos+*armT; i++) {
        if (i == 0) {
            arm[0] = novos_p[0];
        }
        else if (i > 0) {
            for (int j = i - 1; j > -1; j--) {
                if (novos_p[w].area.compare(arm[j].area)==0) {
                    if (i == 1) {
                        arm[i] = novos_p[w];
                    }
                    else {
                        for (int k = i; k > j; k--) {
                            arm[k] = arm[k - 1];
                            if (novos_p[w].area.compare(arm[k - 1].area) == 0) {
                                arm[k - 1] = novos_p[w];
                            }
                        }
                        break;
                    }
                }
                else {
                    arm[i] = novos_p[w];
                }
            }
        }
        w++;
    }
    *armT = *armT + n_produtos;
}

void plantar_produtos(Produto* arm, int armT, Hortas* plantacao, int num_hortas) {
    int t = armT;
    int c = 0;
    while (c < 10) {
        for (int i = 0; i < armT; i++) { //for de variável i que percorre os produtos para plantar no armazem
            for (int j = 0; j < num_hortas; j++) { //for de variável j que percorre as hortas
                if ((plantacao[j].area.compare(arm[i].area) == 0) && (plantacao[j].produtos < plantacao[j].capacidade) && t > 0) { //if que compara a area da plantacao com a area do produto a plantar, só executa quando as areas forem iguais, se a horta não estiver cheia e se o armazem ainda tiver produtos
                    int k = plantacao[j].produtos;
                    plantacao[j].listaProdutos[k] = arm[i]; //copia o produto do armazem para a horta
                    plantacao[j].produtos++; //aumenta em 1 o número de produtos na horta
                    arm[i].plantar = true;
                    t--;
                    c++;
                    break;
                }
            }
        }
    }
}

void remover_produtos(Produto* arm, int* armT) {
    int i, j;
    int c = 0;
    for (i = j = 0; i < *armT; i++){
        if (arm[i].plantar == false) {
            arm[j++] = arm[i];
        }
        else{
            c++;
        }
    }
    *armT = *armT - c;
}

void mostra_armazem(Produto* arm, int* armT) {
    cout << "Armazém: " << endl;
    for (int i = 0; i < *armT; i++) {
        cout << "Nome: " << arm[i].nome << " | " << "Resistência: " << arm[i].resistencia << "%" << " | " << "Área: " << arm[i].area << endl;
    }
}

void pragas(Hortas* plantacao, int num_hortas) {
    for (int i = 0; i < num_hortas; i++) {
        for (int j = 0; j < plantacao[i].produtos; j++) {
            if (plantacao[i].listaProdutos[j].temp_para_rega == 1) {
                if (rand() % 100 + 1 < (101 - plantacao[i].listaProdutos[j].resistencia)) {
                    plantacao[i].listaProdutos[j].plantar = true;
                    cout << "Foi perdido um produto " << plantacao[i].listaProdutos[j].nome << " da área " << plantacao[i].listaProdutos[j].area << " da horta " << plantacao[i].nome << endl;
                }
            }
        }
    }

    int k, y, w;
    for (int k = 0; k < num_hortas; k++) {
        int c = 0;
        for (y = w = 0; y < plantacao[k].produtos; y++) {
            if (plantacao[k].listaProdutos[y].plantar == false) {
                plantacao[k].listaProdutos[w++] = plantacao[k].listaProdutos[y];
            }
            else {
                c++;
            }
        }
        plantacao[k].produtos = plantacao[k].produtos - c;
    }
}