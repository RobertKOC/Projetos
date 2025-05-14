#include <locale.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Transacao {
    string descricao;
    double valor;
    bool entrada; // true = entrada, false = saída
};

vector<Transacao> transacoes;
double saldo = 0.0;

// função para salvar transações no arquivo
void salvarTransacoes() {
    ofstream arquivo("banco.txt");
    for (const auto& t : transacoes) {
        arquivo << t.entrada << ";" << t.descricao << ";" << t.valor << "\n";
    }
    arquivo.close();
}

// função para carregar transações do arquivo
void carregarTransacoes() {
    ifstream arquivo("banco.txt");
    string linha;
    while (getline(arquivo, linha)) {
        Transacao t;
        size_t pos1 = linha.find(";");
        size_t pos2 = linha.find(";", pos1 + 1);

        t.entrada = stoi(linha.substr(0, pos1));
        t.descricao = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        t.valor = stod(linha.substr(pos2 + 1));

        transacoes.push_back(t);
        saldo += (t.entrada ? t.valor : -t.valor);
    }
    arquivo.close();
}

void adicionarEntrada() {
    Transacao t;
    cout << "Descrição da entrada: ";
    cin.ignore();
    getline(cin, t.descricao);
    cout << "Valor: R$ ";
    cin >> t.valor;
    t.entrada = true;

    saldo += t.valor;
    transacoes.push_back(t);
    salvarTransacoes();
    cout << "Entrada registrada com sucesso!\n";
}

void adicionarSaida() {
    Transacao t;
    cout << "Descrição da saída: ";
    cin.ignore();
    getline(cin, t.descricao);
    cout << "Valor: R$ ";
    cin >> t.valor;
    t.entrada = false;

    saldo -= t.valor;
    transacoes.push_back(t);
    salvarTransacoes();
    cout << "Saída registrada com sucesso!\n";
}

void verTransacoes() {
    cout << "\n=== Transações ===\n";
    for (const auto& t : transacoes) {
        cout << (t.entrada ? "[ENTRADA] " : "[SAÍDA]   ");
        cout << t.descricao << " - R$" << t.valor << endl;
    }
}

void verSaldo() {
    cout << "\n=== Saldo Atual ===\n";
    cout << "R$ " << saldo << endl;
}

void menu() {
    int opcao;
    do {
        cout << "\n=== Menu do Fluxo de Caixa ===\n";
        cout << "1. Adicionar Entrada\n";
        cout << "2. Adicionar Saída\n";
        cout << "3. Ver Transações\n";
        cout << "4. Ver Saldo\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: adicionarEntrada(); break;
            case 2: adicionarSaida(); break;
            case 3: verTransacoes(); break;
            case 4: verSaldo(); break;
            case 5: cout << "Saindo...\n"; break;
            default: cout << "Opção inválida.\n";
        }
    } while (opcao != 5);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    carregarTransacoes();
    menu();
    return 0;
}
