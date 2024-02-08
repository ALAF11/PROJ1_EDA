#include<iostream>
#include<string>
#include<time.h>
#include<stdlib.h>

#include"ficheiros.h"
#include"armazem.h"
#include"Hortas.h"
#include"gestao.h"

using namespace std;


void perguntar_responsasveis(int nh, string alphabet, Hortas* h) {
	for (int k = 0; k < nh; k++) {
		cout << "Qual o nome do responsável da horta " << alphabet[k] << "?" << endl;
		cin >> h[k].agricultor;
	}
}

void area_aleatoria(int nh, string* a, string* ah) {
	for (int i = 0; i < nh; i++) {
		*ah = *(a + rand() % ler_linhas_ficheiro("areas.txt"));
		ah++;
	}
}

void opcoes(Hortas* plantacao, Produto* arm, int armT, int num_hortas, string* area_das_hortas, string* a, int t_ah, int paT, string* area_hortas) {
	bool sair = false;
	do {
		int opcao;
		cout << "***** Bem Vindo Gestor ***** \n";
		cout << "(1). Colher Produto \n";
		cout << "(2). Atualizar tempo de rega \n";
		cout << "(3). Fertilização \n";
		cout << "(4). Gravar Plantação \n";
		cout << "(5). Carregar Plantação \n";
		cout << "(6). Imprimir plantação \n";
		cout << "(7). Criar nova área \n";
		cout << "(8). Mostrar registo de agricultor \n";
		cout << "(9). Alterar área \n";
		cout << "(0). Voltar \n";
		cout << "Seleccione a sua opção:";
		cin >> opcao;
		switch (opcao) {
		case 1:
			colheitaManual(plantacao, num_hortas);
			break;
		case 2:
			atu_temporega(plantacao, arm, armT, num_hortas);
			break;
		case 3:
			ver_fertilizaçao(plantacao, num_hortas);
			break;
		case 4:
			gravarh(plantacao, num_hortas);
			gravar_arm(arm, &armT);
			break;
		case 5:
			carregar(plantacao, num_hortas);
			carregar_arm(arm, &armT);
			break;
		case 6:
			imprimirPlantaçao(plantacao, num_hortas);
			break;
		case 7:
			nova_area(area_das_hortas, a, &t_ah, &paT, area_hortas);
			break;
		case 8:
			cout << endl;
			registoC(plantacao, num_hortas);
			cout << endl;
			break;
		case 9:
			cout << endl;
			alterar_area(plantacao, area_das_hortas, num_hortas, a, paT, &t_ah);
			cout << endl;
			break;
		case 0:
			cout << "Escolheu a opcao VOLTAR" << endl;
			sair = true;
			break;
		}
	} while (!sair);
}

int main() {
	locale::global(locale(""));

	srand(time(NULL));

	string* pa = new string[ler_linhas_ficheiro("areas.txt")]; //Criar array de areas vindas do ficheiro txt de areas
	string* pp = new string[ler_linhas_ficheiro("produtos.txt")]; //Criar array de produtos vindos do ficheiro txt de produtos
	string* pf = new string[ler_linhas_ficheiro("fornecedores.txt")]; //Criar array de fornecedores vindos do ficheiro txt de fornecedores

	int paT = ler_linhas_ficheiro("areas.txt");

	array_ficheiros("areas.txt", pa);
	array_ficheiros("fornecedores.txt", pf);
	array_ficheiros("produtos.txt", pp);

	Produto* arm = new Produto[200]; //Criar/alocar memoria para o armazem
	int armT = 0; //Iniciar a variável do tamanho do armazem

	const string alphabet = "ABCDEFGHIJ"; //Iniciar a constate da abcedário

	int num_hortas = rand() % 6 + 5; //Atribuir o valor do numero de hortas entre 5 e 10 

	string* area_das_hortas = new string[num_hortas]; //Criar array das areas que vamos usar
	int t_ah = num_hortas;

	Produto* novos_pi = new Produto[15]; //Criar/Alocar memoria para array de produtos auxiliar para a inserção dos novos produtos no armazem (pela primeira vez)

	Hortas* plantacao = new Hortas[num_hortas]; //Criar/alocar memoria para o arrays das hortas

	perguntar_responsasveis(num_hortas, alphabet, plantacao); //Perguntar ao utilizador os nomes dos responsaveis das hortas

	area_aleatoria(num_hortas, pa, area_das_hortas); //

	criar_produto(15, num_hortas, pp, area_das_hortas, novos_pi, pf);

	inserir_produtos(arm, &armT, 15, novos_pi);

	delete[] novos_pi;

	cria_hortas(num_hortas, plantacao, area_das_hortas, alphabet, arm);

	mostra_hortas(num_hortas, plantacao);
	mostra_armazem(arm, &armT);

	string* area_hortas = area_das_hortas;

	bool sair = false;
	char opcao;
	do
	{
		cout << "\n(s)eguinte *********** (g)estão\n" << endl;
		cout << "Seleccione a sua opção:";
		cin >> opcao;
		switch (opcao) {
		case 's':

			cout << endl;

			colhido(plantacao, num_hortas);

			novos_pi = new Produto[10];

			criar_produto(10, num_hortas, pp, area_das_hortas, novos_pi,pf);
			plantar_produtos(arm, armT, plantacao, num_hortas);
			inserir_produtos(arm, &armT, 10, novos_pi);
			remover_produtos(arm, &armT);

			cout << endl;

			pragas(plantacao, num_hortas);

			cout << endl;

			tempo_rega(plantacao, num_hortas);

			fertilizaçao(plantacao, num_hortas);

			mostra_hortas(num_hortas, plantacao);
			mostra_armazem(arm, &armT);

			delete[] novos_pi;
			break;
		case 'g':
			opcoes(plantacao, arm, armT, num_hortas, area_das_hortas, pa, t_ah, paT, area_hortas);
			break;
		default:
			break;
		}
	} while (true);

	return 0;
}