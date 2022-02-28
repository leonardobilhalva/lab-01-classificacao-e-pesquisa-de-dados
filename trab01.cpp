//+------------------------------------------------------------------+
//|                                                   Laboratório 01 |
//|  Aluno: Leonardo Barros Bilhalva  e Santiago del Castillo Gonzaga|
//|                    Disciplina: Classificação e Pesquisa de Dados |
//+------------------------------------------------------------------+
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include <math.h>
#include <iomanip>

using namespace std;


//--------------------------------------------------------------------------
vector<int> ins_direta_shell_sort(/*Vetor*/vector<int> vet, /*Tamanho do vetor*/int quantidade, /*Inicio do incremento*/int primeiroTermo, /*incremento*/int passos) // Funcao fornecida pelo professor
{
    int passoauxiliar, passo1, chave;

    for (passo1 = (primeiroTermo + passos); passo1 < quantidade; passo1 += passos)
    {
        passoauxiliar = (passo1 - passos);
        chave = vet[passo1];
        while ((passoauxiliar >= 0) && (vet[passoauxiliar] > chave))
        {
            vet[passoauxiliar + passos] = vet[passoauxiliar];
            passoauxiliar = (passoauxiliar - passos);
        }
        vet[passoauxiliar + passos] = chave;
    }    
    return vet;
}

//--------------------------------------------------------------------------

void shell_sort(/*Vetor*/vector<int> C, /*Tamanho do Vetor*/int n, ofstream& escrita_saida)                            //Funcao para exercicio 1 -> shell sort potencia de 2
{
    int    /*Inicio de um segmento*/j;
    int /*Valor do Incremento*/p;

    int a = 0;
    while(a < C.size())
    { 
        escrita_saida << C[a] << ", ";
        a++;
    }
    escrita_saida << " SEQ=SHELL" << endl;                              // Escreve no arquivo a sequencia original

    for(p = n/2; p >= 1; p = p/2)                                       //logica do incremento: Shell -> potencia de 2
    { 
        for (j=0;j <= p; j++)            
        C = ins_direta_shell_sort(C, n, j, p);                   //função de passada pelo professor

        a = 0;
        while(a < C.size())
        { 
        escrita_saida << C[a] << ", ";                               // escreve no arquivo a sequencia atual
        a++;
        }
        escrita_saida << " INCR= " << p << endl;                    // Escreve no arquivo o incremento atual
    }
}

void shell_sort_knuth(/*Vetor*/vector<int> C, /*Tamanho do Vetor*/int n, ofstream& escrita_saida)                      //Funcao para exercicio 1 - > shell sort incremento knuth
{
    int    /*Inicio de um segmento*/j;
    int /*Valor do Incremento*/p;
    int knuth = 1;

    while(knuth < n) //descobre o maior numero da sequencia de knuth
    {
        if(((3 * knuth) + 1) > n)
        break;  //se próximo elemento de knuth será maior que o tamanho do vetor atual, usa o atual número de knuth

        knuth = (3 * knuth) + 1;
    }

    int a = 0;
    while(a < C.size())
    { 
        escrita_saida << C[a] << ", ";
        a++;
    }
    escrita_saida << " SEQ=KNUT" << endl;                              // Escreve no arquivo a sequencia original

    for(p = knuth; p >= 1; p = (p-1)/3)                                       //logica do incremento: Shell -> knuth
    {
        for (j=0;j <= p; j++)            
        C = ins_direta_shell_sort(C, n, j, p);                   //função de passada pelo professor

        a = 0;
        while(a < C.size())
        { 
        escrita_saida << C[a] << ", ";                               // escreve no arquivo a sequencia atual
        a++;
        }
        escrita_saida << " INCR= " << p << endl;                    // Escreve no arquivo o incremento atual
    }
}

//--------------------------------------------------------------------------

long recursao_ciura_corrige(double a, double h_ciura_atual)  //Essa funcao recursivamente descobre qual o passo atual que o numero maior que 701*2.25 se enquadra.
{
    if(a>h_ciura_atual) //se o n�mero de elementos recebido em a for maior que o passo atual de ciura, chama a fun��o recursivamente aumentando o h_ciura_atual para o pr�ximo passo de ciura.
    {
        return recursao_ciura_corrige(a, h_ciura_atual*2.25);
    }
    else                //se o n�mero de elementos recebido em a for menor que o passo atual de ciura, utiliza o �ltimo passo. Para isso, divide h_ciura_atual por 2,25;
    {
        return h_ciura_atual/2.25;
    }

}

//--------------------------------------------------------------------------

double ciura_corrige(double a)         //Essa fun��o corrige a entrada do "H" de ciura
{
        if (a>=701*2.25) return recursao_ciura_corrige(a, 701*2.25);

        //Passos da sequ�ncia de Ciura que conhecemos
		if (a>=701) return 701;
		if (a>=301) return 301;
		if (a>=132) return 132;
		if (a>=57) return 57;
		if (a>=23) return 23;
		if (a>=10) return 10;
		if (a>=4) return 4;
		if (a>=1) return 1;
}

//--------------------------------------------------------------------------

double ciura_next(double a)           //Essa funcao passa para o proximo "H" de Ciura
{
      	if (a<=1) return 0;
		if (a<=4) return 1;
		if (a<=10) return 4;
		if (a<=23) return 10;
		if (a<=57) return 23;
		if (a<=132) return 57;
		if (a<=301) return 132;
		if (a<=701) return 301;
		if (a<=701*2.25) return 701;

		return a/2.25;// Aqui, qualquer n�mero acima de 701*2,25 ter� o pr�ximo passo pela multiplica��o de 2,25. Ent�o, a divis�o direta dele por 2,25 concede o pr�ximo passo de ciura.
}

//--------------------------------------------------------------------------

void shell_sort_ciura(/*Vetor*/vector<int> C, /*Tamanho do Vetor*/int n, ofstream& escrita_saida)                      //Funcao para exercicio 1 - > shell sort incremento knuth
{
    int    /*Inicio de um segmento*/j;
    double ciura = n;

    ciura = ciura_corrige(ciura);

    int a = 0;
    while(a < C.size())
    { 
        escrita_saida << C[a] << ", ";
        a++;
    }
    escrita_saida << " SEQ=CIURA" << endl;                              // Escreve no arquivo a sequencia original

    while(ciura>=1)
    {
        for (j=0;j <= ciura; j++)            
        C = ins_direta_shell_sort(C, n, j, ciura);                   //função de passada pelo professor

        a = 0;
        while(a < C.size())
        { 
        escrita_saida << C[a] << ", ";                               // escreve no arquivo a sequencia atual
        a++;
        }
        escrita_saida << " INCR= " << ciura << endl;                    // Escreve no arquivo o incremento atual

        ciura = ciura_next(ciura);                          //usa a funçao corrige_next para retornar a "ciura" o proximo numero da sequencia de ciura
	    ciura = floor(ciura);                               // garante que e o piso
    }
}

//================================================================
//================================================================

void shell_sort_exer_2(/*Vetor*/vector<int> C, /*Tamanho do Vetor*/int n, ofstream& escrita_saida)                            //Funcao para exercicio 1 -> shell sort potencia de 2
{
    int    /*Inicio de um segmento*/j;
    int /*Valor do Incremento*/p;    
    
                                                                //Parte para contar o tempo  ------ \/
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);                            //Parte para contar o tempo  ------ /\


    escrita_saida << "SHELL" << ", " << n << ", ";                              // Escreve no arquivo

    for(p = n/2; p >= 1; p = p/2)                                       //logica do incremento: Shell -> potencia de 2        
        for (j=0;j <= p; j++)            
        C = ins_direta_shell_sort(C, n, j, p);                   //função de passada pelo professor

    QueryPerformanceCounter(&end);                              //Parte para contar o tempo  ------
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    escrita_saida << interval*1000 << endl;
}

void shell_sort_knuth_exer_2(/*Vetor*/vector<int> C, /*Tamanho do Vetor*/int n, ofstream& escrita_saida)                      //Funcao para exercicio 1 - > shell sort incremento knuth
{
    int    /*Inicio de um segmento*/j;
    int /*Valor do Incremento*/p;
    int knuth = 1;


                                                                //Parte para contar o tempo  ------ \/
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);                            //Parte para contar o tempo  ------ /\

    while(knuth < n) //descobre o maior numero da sequencia de knuth
    {
        if(((3 * knuth) + 1) > n)
        break;  //se próximo elemento de knuth será maior que o tamanho do vetor atual, usa o atual número de knuth

        knuth = (3 * knuth) + 1;
    }

    int a = 0;
    escrita_saida << "KNUTH" << ", " << n << ", ";                                // Escreve no arquivo a sequencia original

    for(p = knuth; p >= 1; p = (p-1)/3)                                       //logica do incremento: Shell -> knuth
        for (j=0;j <= p; j++)            
        C = ins_direta_shell_sort(C, n, j, p);                   //função de passada pelo professor

    QueryPerformanceCounter(&end);                              //Parte para contar o tempo  ------
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    escrita_saida << interval*1000 << endl;
}

void shell_sort_ciura_exer_2(/*Vetor*/vector<int> C, /*Tamanho do Vetor*/int n, ofstream& escrita_saida)                      //Funcao para exercicio 1 - > shell sort incremento knuth
{
    int    /*Inicio de um segmento*/j;
    double ciura = n;

                                                               //Parte para contar o tempo  ------ \/
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);                            //Parte para contar o tempo  ------ /\

    ciura = ciura_corrige(ciura);
    escrita_saida << "CIURA" << ", " << n << ", ";              // Escreve no arquivo a sequencia original

    while(ciura>=1)
    {
        for (j=0;j <= ciura; j++)            
        C = ins_direta_shell_sort(C, n, j, ciura);                   //função de passada pelo professor
        ciura = ciura_next(ciura);                          //usa a funçao corrige_next para retornar a "ciura" o proximo numero da sequencia de ciura
	    ciura = floor(ciura);                               // garante que e o piso
    }

    QueryPerformanceCounter(&end);                              //Parte para contar o tempo  ------
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    escrita_saida << interval*1000 << endl;
}

int main ()
{
    cout << "Laboratorio 01 -> comecou!" << endl;
    ifstream leitura_entrada;       //Inicia o Arquivo de leitura
    ofstream escrita_saida;         //Inicia o Arquivos de saida


    leitura_entrada.open("entrada1.txt");
    escrita_saida.open("saida1.txt");

    string linha;        // aloca linha
    string word;         // aloca palavra
    vector<int> numeros; // alocar os números
    vector<vector <int>> vetor_de_numeros;
    int quantidade_vetor_de_numeros = 0;
    int quantidade_numeros = 0;  //quantidade de numeros na linha

    while(getline(leitura_entrada, linha))
    {        
      numeros.clear();                            //limpa o vetor que aloca o numeros da linha
      istringstream var(linha);                   //Coloca linha em var      
      getline(var, word, ' ');                    //Retira a primeira parte de linha até a ' ' -> algum número
      quantidade_numeros = stoi(word);              //Aloca a quantidade de palavras da linha
    
      while (quantidade_numeros > 0){             //Roda pelo total de números para retirar na linha      
      getline(var, word, ' ');                    //Retira a primeira parte de linha até a , -> algum número
      numeros.push_back(stoi(word));              //Aloca o número atual

      quantidade_numeros--;   //diminui a quantidade total
      }
      quantidade_vetor_de_numeros ++;
      vetor_de_numeros.push_back(numeros);       //Aloca o vetor atual em um vetor de vetores
    }

    /* for (int i = 0; i < vetor_de_numeros.size(); i++) {
        for (int j = 0; j < vetor_de_numeros[i].size(); j++)
            cout << vetor_de_numeros[i][j] << " ";
        cout << endl;
    }*/ // prova real do que contem o vetor

    int a = 0;
    while(quantidade_vetor_de_numeros > a) // percorre o vetor de vetores de números
    {        
       shell_sort(vetor_de_numeros[a], vetor_de_numeros[a].size(), escrita_saida);
       shell_sort_knuth(vetor_de_numeros[a], vetor_de_numeros[a].size(), escrita_saida);
       shell_sort_ciura(vetor_de_numeros[a], vetor_de_numeros[a].size(), escrita_saida);
        a ++;
    }

    leitura_entrada.close();
    escrita_saida.close();

    //Fim da primeira parte
    //================================================================
    //Iincio da segunda parte        
    escrita_saida << fixed << setprecision(6); // precisao das casas decimais na escrita

    leitura_entrada.open("entrada2.txt");
    escrita_saida.open("saida2.txt");

    numeros.clear();
    vetor_de_numeros.clear();
    quantidade_vetor_de_numeros = 0;
    quantidade_numeros = 0;

    while(getline(leitura_entrada, linha))
    {        
      numeros.clear();                            //limpa o vetor que aloca o numeros da linha
      istringstream aux(linha);                   //Coloca linha em var      
      getline(aux, word, ' ');                    //Retira a primeira parte de linha até a ' ' -> algum número
      quantidade_numeros = stoi(word);              //Aloca a quantidade de palavras da linha
    
      while (quantidade_numeros > 0){             //Roda pelo total de números para retirar na linha      
      getline(aux, word, ' ');                    //Retira a primeira parte de linha até a , -> algum número
      numeros.push_back(stoi(word));              //Aloca o número atual

      quantidade_numeros--;   //diminui a quantidade total
      }
      quantidade_vetor_de_numeros ++;
      vetor_de_numeros.push_back(numeros);       //Aloca o vetor atual em um vetor de vetores
    }

    /*for (int i = 0; i < vetor_de_numeros.size(); i++) {
        for (int j = 0; j < vetor_de_numeros[i].size(); j++)
            cout << vetor_de_numeros[i][j] << " ";
        cout << endl;
    }*/ // prova real do que contem o vetor

    a = 0;
    while(quantidade_vetor_de_numeros > a) // percorre o vetor de vetores de números
    {        
        shell_sort_exer_2(vetor_de_numeros[a], vetor_de_numeros[a].size(), escrita_saida);
        shell_sort_knuth_exer_2(vetor_de_numeros[a], vetor_de_numeros[a].size(), escrita_saida);
        shell_sort_ciura_exer_2(vetor_de_numeros[a], vetor_de_numeros[a].size(), escrita_saida);
        a ++;
    }

    cout << "Laboratorio 01 -> terminou!" << endl;
    return 0;
    
}