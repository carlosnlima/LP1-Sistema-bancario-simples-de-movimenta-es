#include "../include/conta_bancaria.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

ContaBancaria::ContaBancaria(int numero, const Cliente &titular, double saldoInicial)
    : numero(numero), saldo(saldoInicial), titular(titular)
{
    registrar("Conta criada com saldo inicial: R$ " + to_string(saldoInicial));
}

int ContaBancaria::getNumero() const { return numero; }
std::string ContaBancaria::getCpfTitular() const { return titular.getCpf(); }
std::string ContaBancaria::getNomeTitular() const { return titular.getNome(); }
double ContaBancaria::getSaldo() const { return saldo; }

void ContaBancaria::registrar(const string &evento)
{
    historico.push_back(evento);
}

void ContaBancaria::depositar(double valor)
{
    if (valor <= 0)
        return;
    saldo += valor;
    registrar("Depósito: +R$ " + to_string(valor));
}

bool ContaBancaria::sacar(double valor)
{
    if (valor <= 0 || valor > saldo)
        return false;
    saldo -= valor;
    registrar("Saque: -R$ " + to_string(valor));
    return true;
}

bool ContaBancaria::transferir(double valor, ContaBancaria &destino)
{
    if (valor <= 0 || valor > saldo)
        return false;
    saldo -= valor;
    destino.saldo += valor;
    registrar("Transferência para " + destino.getNomeTitular() + " (-R$ " + to_string(valor) + ")");
    destino.registrar("Transferência recebida de " + titular.getNome() + " (+R$ " + to_string(valor) + ")");
    return true;
}

bool ContaBancaria::transferirDuplo(double valor, ContaBancaria &d1, ContaBancaria &d2)
{
    if (valor <= 0 || valor > saldo)
        return false;
    double metade = valor / 2;
    saldo -= valor;
    d1.saldo += metade;
    d2.saldo += (valor - metade);
    registrar("Transferência dupla (-R$ " + to_string(valor) + ")");
    d1.registrar("Recebeu transferência dupla (+R$ " + to_string(metade) + ")");
    d2.registrar("Recebeu transferência dupla (+R$ " + to_string(valor - metade) + ")");
    return true;
}

void ContaBancaria::aplicarJuros(double taxa)
{
    if (taxa <= 0)
        return;
    double acrescimo = saldo * (taxa / 100);
    saldo += acrescimo;
    registrar("Juros aplicados: +" + to_string(acrescimo));
}

bool ContaBancaria::pagarBoleto(double valor, const string &descricao)
{
    if (valor <= 0 || valor > saldo)
        return false;
    saldo -= valor;
    registrar("Boleto pago (" + descricao + "): -R$ " + to_string(valor));
    return true;
}

void ContaBancaria::exibirInformacoes() const
{
    cout << "\n------------------------------------------\n";
    cout << "Titular: " << titular.getNome() << "\n";
    cout << "CPF:     " << titular.getCpf() << "\n";
    cout << "Conta:   " << numero << "\n";
    cout << fixed << setprecision(2);
    cout << "Saldo:   R$ " << saldo << "\n";
    cout << "------------------------------------------\n";
}

void ContaBancaria::exibirHistorico() const
{
    cout << "\n===== Histórico =====\n";
    for (auto &h : historico)
        cout << "- " << h << "\n";
}

void ContaBancaria::salvar(ofstream &arq) const
{
    size_t nomeLen = titular.getNome().size();
    size_t cpfLen = titular.getCpf().size();
    size_t histSize = historico.size();

    arq.write(reinterpret_cast<const char *>(&numero), sizeof(numero));
    arq.write(reinterpret_cast<const char *>(&saldo), sizeof(saldo));
    arq.write(reinterpret_cast<const char *>(&nomeLen), sizeof(nomeLen));
    arq.write(titular.getNome().c_str(), nomeLen);
    arq.write(reinterpret_cast<const char *>(&cpfLen), sizeof(cpfLen));
    arq.write(titular.getCpf().c_str(), cpfLen);
    arq.write(reinterpret_cast<const char *>(&histSize), sizeof(histSize));

    for (auto &h : historico)
    {
        size_t len = h.size();
        arq.write(reinterpret_cast<const char *>(&len), sizeof(len));
        arq.write(h.c_str(), len);
    }
}

void ContaBancaria::carregar(ifstream &arq)
{
    size_t nomeLen, cpfLen, histSize;
    string nome, cpf;

    arq.read(reinterpret_cast<char *>(&numero), sizeof(numero));
    arq.read(reinterpret_cast<char *>(&saldo), sizeof(saldo));
    arq.read(reinterpret_cast<char *>(&nomeLen), sizeof(nomeLen));
    nome.resize(nomeLen);
    arq.read(&nome[0], nomeLen);
    arq.read(reinterpret_cast<char *>(&cpfLen), sizeof(cpfLen));
    cpf.resize(cpfLen);
    arq.read(&cpf[0], cpfLen);
    titular = Cliente(nome, cpf);
    arq.read(reinterpret_cast<char *>(&histSize), sizeof(histSize));
    historico.clear();
    for (size_t i = 0; i < histSize; ++i)
    {
        size_t len;
        arq.read(reinterpret_cast<char *>(&len), sizeof(len));
        string h(len, '\0');
        arq.read(&h[0], len);
        historico.push_back(h);
    }
}
