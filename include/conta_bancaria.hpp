#ifndef CONTABANCARIA_HPP
#define CONTABANCARIA_HPP

#include "Cliente.hpp"
#include <string>
#include <vector>

class ContaBancaria
{
private:
    int numero;
    double saldo;
    Cliente titular;
    std::vector<std::string> historico;

public:
    ContaBancaria() = default;
    ContaBancaria(int numero, const Cliente &titular, double saldoInicial = 0.0);

    int getNumero() const;
    std::string getCpfTitular() const;
    std::string getNomeTitular() const;
    double getSaldo() const;

    void depositar(double valor);
    bool sacar(double valor);
    bool transferir(double valor, ContaBancaria &destino);
    bool transferirDuplo(double valor, ContaBancaria &d1, ContaBancaria &d2);
    void aplicarJuros(double taxa);
    bool pagarBoleto(double valor, const std::string &descricao);

    void exibirInformacoes() const;
    void exibirHistorico() const;

    void registrar(const std::string &evento);

    // Métodos para persistência
    void salvar(std::ofstream &arq) const;
    void carregar(std::ifstream &arq);
};

#endif
