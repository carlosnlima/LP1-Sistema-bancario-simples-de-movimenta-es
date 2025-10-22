#ifndef BANCO_HPP
#define BANCO_HPP

#include "conta_bancaria.hpp"
#include <vector>
#include <string>

class Banco
{
private:
    std::vector<ContaBancaria> contas;
    const std::string arquivo = "contas.dat";

public:
    Banco();
    void carregar();
    void salvar() const;

    ContaBancaria *buscarPorCpf(const std::string &cpf);
    ContaBancaria *buscarPorNumero(int numero);
    ContaBancaria *criarConta(const std::string &nome, const std::string &cpf, double deposito);
    const std::vector<ContaBancaria> &getContas() const;
};

#endif
