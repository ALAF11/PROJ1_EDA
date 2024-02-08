#include<iostream>
#include<string>
#include <fstream>

#include"Hortas.h"
#include"armazem.h"
#include"ficheiros.h"
#include"struct.h"


using namespace std;

void colheitaManual(Hortas* h, int nh) {
    string colher;
    cout << "Insira o nome do produto a ser colhido:" << endl;
    cin.ignore();
    getline(cin, colher);
    for (int i = 0; i < nh; i++) {
        for (int j = 0; j < h[i].produtos; j++) {
            if ((h[i].listaProdutos[j].nome.compare(colher)) == 0) {
                h[i].registo[h[i].resT] = h[i].listaProdutos[j].nome;
                h[i].resT++;
                h[i].listaProdutos[j].plantar = true;
                cout << endl;
                cout << "Foi colhido manualmente um produto " << h[i].listaProdutos[j].nome << " de area " << h[i].listaProdutos[j].area << " da horta " << h[i].nome << endl;
                cout << endl;
            }
        }
    }

    int k, y, w;
    for (int k = 0; k < nh; k++) {
        int c = 0;
        for (y = w = 0; y < h[k].produtos; y++) {
            if (h[k].listaProdutos[y].plantar == false) {
                h[k].listaProdutos[w++] = h[k].listaProdutos[y];
            }
            else {
                c++;
            }
        }
        h[k].produtos = h[k].produtos - c;
    }
}

void atu_temporega(Hortas* plantacao, Produto* arm, int armT, int num_hortas) {
    string nProd;
    int tnovo;
    cout << "Indique o nome do produto : " << endl;
    cin >> nProd;
    cout << "Indique o novo tempo de rega :" << endl;
    cin >> tnovo;

    for (int i = 0; i < armT; i++) {
        if (arm[i].nome == nProd) {
            arm[i].rega = tnovo;
            arm[i].temp_para_rega = tnovo;
        }
    }

    for (int j = 0; j < num_hortas; j++) {
        for (int k = 0; k < plantacao[j].produtos; k++) {
            if (plantacao[j].listaProdutos[k].nome == nProd) {
                plantacao[j].listaProdutos[k].rega = tnovo;
                plantacao[j].listaProdutos[k].temp_para_rega = tnovo;
            }
        }

    }

}

void ver_fertilizaçao(Hortas* h, int nh) {
    string area;
    int tempo_fertilizaçao;
    cout << "Insira uma área" << endl;
    cin.ignore();
    getline(cin, area);
    cout << "Insira um tempo de fertilização" << endl;
    cin >> tempo_fertilizaçao;
    for (int i = 0; i < nh; i++) {
        if (h[i].area.compare(area) == 0) {
            h[i].fertilizaçao = tempo_fertilizaçao;
        }
    }
}

void fertilizaçao(Hortas* plantacao, int num_hortas) {
    for (int i = 0; i < num_hortas; i++) {
        if (plantacao[i].fertilizaçao > 0) {
            for (int j = 0; j < plantacao[i].produtos; j++) {
                if (plantacao[i].listaProdutos[j].resistencia + (10) > 100) {
                    plantacao[i].listaProdutos[j].resistencia = 100;
                }
                else {
                    plantacao[i].listaProdutos[j].resistencia = plantacao[i].listaProdutos[j].resistencia + 10;
                }
            }
            plantacao[i].fertilizaçao--;
        }
    }
}

void tempo_rega(Hortas* plantacao, int num_hortas) {
    for (int i = 0; i < num_hortas; i++) {
        for (int j = 0; j < plantacao[i].produtos; j++) {
            if (plantacao[i].listaProdutos[j].temp_para_rega == 0) {
                plantacao[i].listaProdutos[j].temp_para_rega = plantacao[i].listaProdutos[j].rega;
            }
            else {
                plantacao[i].listaProdutos[j].temp_para_rega--;
            }
        }
    }
}

void nova_area(string* area_das_hortas, string* a, int* t_ah, int* paT, string* area_hortas) {
    string na;
    string* x = new string[*t_ah + 1];
    string* y = new string[*paT + 1];


    cout << "Escreva o nome da nova area:" << endl;
    cin.ignore();
    getline(cin, na);

    for (int w = 0; w < *paT; w++) {
        y[w] = a[w];
    }

    delete[] a;

    y[*paT] = na;
    *paT = *paT + 1;

    a = y;


    for (int k = 0; k < *t_ah; k++) {
        x[k] = area_hortas[k];
    }

    delete[] area_hortas;

    x[*t_ah] = na;
    *t_ah = *t_ah + 1;

    area_hortas = x;

    area_das_hortas = area_hortas;

}

void registoC(Hortas* plantacao, int num_hortas) {
    string resp;

    cout << "Intruduza o nome do responsável da horta:" << endl;
    cin.ignore();
    getline(cin, resp);
    for (int i = 0; i < num_hortas; i++) {
        if (plantacao[i].agricultor.compare(resp) == 0) {
            cout << endl;
            cout << "Registo da horta " << plantacao[i].nome << " :" << endl;
            cout << endl;
            for (int j = 0; j < plantacao[i].resT; j++) {
                cout << plantacao[i].registo[j] << endl;
            }
        }
    }
}

void alterar_area(Hortas* plantacao, string* area_das_hortas, int num_hortas, string* a, int paT, int* t_ah) {
    string h;
    string ar;

    cout << "Indique a horta que pretende alterar: " << endl;
    cin >> h;
    cout << "Indique a nova area da horta: " << endl;
    cin.ignore();
    getline(cin, ar);
    for (int i = 0; i < paT; i++) {
        if (ar.compare(a[i]) == 0) {
            for (int j = 0; j < *t_ah; j++) {
                if (ar.compare(area_das_hortas[j]) == 0) {
                    for (int w = 0; w < num_hortas; w++) {
                        if (h.compare(plantacao[w].nome) == 0) {
                            plantacao[w].area = ar;
                            delete[] plantacao[w].listaProdutos;
                            plantacao[w].listaProdutos = new Produto[plantacao[w].capacidade];
                            break;
                        }
                    }
                }
                else {
                    string* b = new string[*t_ah + 1];

                    for (int k = 0; k < *t_ah; k++) {
                        b[k] = area_das_hortas[k];
                    }

                    delete[] area_das_hortas;

                    b[*t_ah] = ar;
                    *t_ah = *t_ah + 1;

                    area_das_hortas = b;

                    for (int l = 0; l < num_hortas; l++) {
                        if (h.compare(plantacao[l].nome) == 0) {
                            plantacao[l].area = ar;
                            delete[] plantacao[l].listaProdutos;
                            plantacao[l].listaProdutos = new Produto[plantacao[l].capacidade];
                        }
                    }
                    break;
                }
            }
        }
    }
}

void limpar_file(string ficheiro) {
    int n = ler_linhas_ficheiro(ficheiro);
    string gravarplant(ficheiro);
    fstream file_out;
    file_out.open(gravarplant, fstream::in | fstream::out);
    if (!file_out.is_open()) {
        cout << "Erro ao abrir " << gravarplant << endl;
        cout << endl;
    }
    else if (file_out.is_open()) {
        string line;
        int line_no = 1;
        while (line_no != n) {
            file_out << "\n" << endl;;
            line_no++;
        }
    }
    file_out.close();
}


void gravarh(Hortas* plant, int nh) {
    string gravarplant("gravarplantacoes.txt");
    fstream file_out;
    file_out.open(gravarplant, fstream::in | fstream::out);
    if (!file_out.is_open()){
        cout << "Erro ao abrir " << gravarplant<<endl;
        cout << endl;
    }
    else if (file_out.is_open()) {
        limpar_file("gravarplantacoes.txt");
        for (int i = 0; i < nh; i++) {
            file_out << plant[i].nome << endl;                          // Primeira linha imprime nome da hortaa
            file_out << plant[i].agricultor << endl;                 //segunda linha agricultor
            file_out << plant[i].area << endl;                        //terceira linha area
            file_out << plant[i].capacidade << endl;                 //quarta linha capacidade
            file_out << plant[i].produtos << endl;                  //Quinta linha nºde produtos
            file_out << plant[i].resT << endl;                     //Sexta tamanho do registo
            if (plant[i].produtos > 0) {
                for (int e = 0; e < plant[i].produtos; e++) {
                    file_out << plant[i].listaProdutos[e].nome << endl;    //SETIMA LINHA A PRIMEIRO PRODUTO DA HORTA
                }
                for (int e = 0; e < plant[i].produtos; e++) {
                    file_out << plant[i].listaProdutos[e].fornecedor << endl;       //DEPOIS DOS PRODUTOS VEM OS FORNECEDORES
                }
                for (int e = 0; e < plant[i].produtos; e++) {
                    file_out << plant[i].listaProdutos[e].rega << endl;            //DEPOIS DE FORNCEDORES VEM A REGA
                }
                for (int e = 0; e < plant[i].produtos; e++) {
                    file_out << plant[i].listaProdutos[e].resistencia << endl;     //DEPOIS DA REGA VEM A RESISTENCIA
                }
                for (int e = 0; e < plant[i].produtos; e++) {
                    file_out << plant[i].listaProdutos[e].temp_para_rega << endl;  //DEPOIS DA RESISTENCIA VEM O TEMP_REGA
                }
            }
            else if (plant[i].resT > 0) {
                for (int e = 0; e < plant[i].resT; e++) {
                    file_out << plant[i].registo[e] << endl;                            //DEPOIS DE VERIFICAR SE TEM REGISTO IMPRIMI-LO OU NAO 
                }
            }
        }
    }
    file_out.close();
}

void gravar_arm(Produto* arm, int* armT) {
    string gravarArma("gravarArmazem.txt");
    fstream file_out;
    file_out.open(gravarArma, fstream::in | fstream::out);
    if (!file_out.is_open()) {
        cout << "Erro ao abrir " << gravarArma << endl;
        cout << endl;
    }
    else if (file_out.is_open()) {
        limpar_file("gravarArmazem.txt");
        for (int i = 0; i < *armT; i++){
            file_out << arm[i].area<<endl;                                //PRIMEIRA LINHA AREA
            file_out << arm[i].nome << endl;                              //SEGUNDA LINHA NOME
            file_out << arm[i].fornecedor << endl;                        //TERCEIRA LINHA FORNECEDOR
            file_out << arm[i].plantar << endl;                           //QUARTA LINHA PLANTAR
            file_out << arm[i].rega << endl;                              //QUINTA LINHA REGA
            file_out << arm[i].temp_para_rega << endl;                    //SEXTA LINHA TEMP PARA REGA
            file_out << arm[i].resistencia << endl;                       //SÉTIMA LINHA RESISTENCIA    
        }
    }
    file_out.close();
}

void carregar(Hortas* plant, int nh) {
    ifstream file_pla;
    file_pla.open("gravarplantacoes.txt", ios::in);
    if (!file_pla.is_open()) {
        cout << "Erro ao abrir o ficheiro das plantações" << endl;
        cout << endl;
    }
    else {
        int linha = 1;
        string line;
        int prod = 0;
        int i = 0;
        int e = 0;
        int k = 0;
        int l = 0;
        int m = 0;
        int n = 0;
        while (getline(file_pla, line)) {
            if (linha == 1) {
                plant[i].nome = line;
            }
            else if (linha == 2) {
                plant[i].agricultor = line;
            }
            else if (linha == 3) {
                plant[i].area = line;
            }
            else if (linha == 4) {
                plant[i].capacidade = stoi(line);
            }
            else if (linha == 5) {
                plant[i].produtos = stoi(line);
                prod = plant[i].produtos;
            }
            else if (linha == 6) {
                plant[i].resT = stoi(line);
            }
            else if (plant[i].produtos > 0) {
                if (linha >= 7 && linha < (7 + prod)) {
                    plant[i].listaProdutos[e].nome = line;
                    e++;
                }
                else if (linha >= (7 + prod) && linha < (7 + 2 * prod)) {
                    plant[i].listaProdutos[k].fornecedor = line;
                    k++;
                }
                else if (linha >= (7 + 2 * prod) && linha < (7 + 3 * prod)) {
                    plant[i].listaProdutos[l].rega = stoi(line);
                    l++;
                }
                else if (linha >= (7 + 3 * prod) && linha < (7 + 4 * prod)) {
                    plant[i].listaProdutos[m].resistencia = stoi(line);
                    m++;
                }
                else if (linha >= (7 + 4 * prod) && linha < (7 + 5 * prod)) {
                    plant[i].listaProdutos[n].temp_para_rega = stoi(line);
                    n++;
                }
            }
            else if (plant[i].resT > 0) {
                if ((linha >= (7 + 5 * prod) && linha < (7 + 5 * prod + plant[i].resT)) || (((linha >= 7) && linha < 7 + plant[i].resT) && (plant[i].produtos == 0))) {
                    //consertar resT
                }
            }
            else if (plant[i].produtos == 0) {
                i++;
                linha = 1;
            }
            else if (linha == (7 + 5 * prod + plant[i].resT - 1)) {
                i++;
                linha = 1;
            }
            linha++;
        }
    }
    file_pla.close();
    cout << endl;
    mostra_hortas(nh, plant);
    cout << endl;
}

void carregar_arm(Produto* arm, int* armT) {
    ifstream file_arm;
    file_arm.open("gravarArmazem.txt", ios::in);
    if (!file_arm.is_open()) {
        cout << "Erro ao abrir o ficheiro das plantações" << endl;
        cout << endl;
    }
    else {
        string line;
        int linha = 1;
        int i = 0;
        while (getline(file_arm, line)) {
            if (linha == 1) {
                arm[i].area = line;
            }
            else if (linha == 2){
                arm[i].nome = line;
            }
            else if (linha == 3) {
                arm[i].fornecedor = line;
            }
            else if (linha == 4) {
                arm[i].plantar = stoi(line);
            }
            else if (linha == 5) {
                arm[i].rega = stoi(line);
            }
            else if (linha==6) {
                arm[i].temp_para_rega = stoi(line);
            }
            else if (linha == 7) {
                arm[i].resistencia = stoi(line);
                i++;
            }
            linha++;
        }
    }
    file_arm.close();
    cout << endl;
    mostra_armazem(arm, armT);
    cout << endl;
}

void swap(int& a, int& b)
{
    int aux = a;
    a = b;
    b = aux;
}

void ordem_alfabetica(Hortas* plant,int nh) {
    int n_prod_total = 0;
    for (int i = 0; i < nh; i++) {
        n_prod_total += plant[i].produtos;
    }
    string* prod = new string[n_prod_total];
    int k = 0;
    for (int i = 0; i < nh; i++) {
        for (int e = 0; e < plant[i].produtos; e++) {
            prod[k] = plant[i].listaProdutos[e].nome;
            k++;
        }
    }
    int primeiro = 0;
    for (int i = 0; i < n_prod_total-1; i++) {
        //int primeiro = 0; 
        for (int j = i + 1; j < n_prod_total; j++) {
            if (prod[j].compare(prod[primeiro]) < 0) primeiro = j;
        }
        if (primeiro != i) swap(prod[i], prod[primeiro]);
    }
    for (int i = 0; i < n_prod_total; i++){
        cout << prod[i] << endl;
    }
}

void imprimirPlantaçao(Hortas* plant, int nh) {
    bool sair = false;
    do
    {
        int opcao;
        cout << "\nComo deseja imprimir a plantação \n";
        cout << "(1). Odem alfabética \n";
        cout << "(2). Tempo de plantação \n";
        cout << "(0). Voltar \n";
        cout << "Seleccione a sua opção:";
        cin >> opcao;
        switch (opcao) {
        case 1:
            ordem_alfabetica(plant, nh);
            break;
        case 2:

            break;
        case 0:
            cout << "Escolheu a opcao VOLTAR" << endl;
            sair = true;
            break;
        }
    } while (!sair);
}