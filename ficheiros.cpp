#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int ler_linhas_ficheiro(string ficheiro) {
	ifstream file;
	file.open(ficheiro, ios::in);
	int num_linhas=0;
	if (file.is_open()){
		string line;
		while (getline(file,line)){
			num_linhas++;
		}
	}
	return num_linhas;
}

void array_ficheiros(string ficheiro,string* p) {
	ifstream file;
	file.open(ficheiro, ios::in);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			*p = line;
			p++;
		}
	}
	file.close();
}
