#include "../include/banco.hpp"
#include <fstream>
#include <iostream>

Banco::Banco() { carregar(); }

void Banco::carregar()
{
    std::ifstream arq(arquivo, std::ios::binary);
    if (!arq)
    {
        // criar contas padrão
        contas.emplace_back(1001, Cliente("Ana Souza", "111.111.111-11"), 500.0);
        contas.emplace_back(1002, Cliente("Bruno Silva", "222.222.222-22"), 350.0);
        contas.emplace_back(1003, Cliente("Carla Mendes", "333.333.333-33"), 150.0);
        salvar();
        return;
    }
    contas.clear();
    while (arq.peek() != EOF)
    {
        ContaBancaria c;
        c.carregar(arq);
        if (arq)
            contas.push_back(c);
    }
}

void Banco::salvar() const
{
    std::ofstream arq(arquivo, std::ios::binary | std::ios::trunc);
    for (auto &c : contas)
        c.salvar(arq);
}

ContaBancaria *Banco::buscarPorCpf(const std::string &cpf)
{
    for (auto &c : contas)
        if (c.getCpfTitular() == cpf)
            return &c;
    return nullptr;
}

ContaBancaria *Banco::buscarPorNumero(int numero)
{
    for (auto &c : contas)
        if (c.getNumero() == numero)
            return &c;
    return nullptr;
}

ContaBancaria *Banco::criarConta(const std::string &nome, const std::string &cpf, double deposito)
{
    int novoNumero = 1000 + contas.size() + 1;
    contas.emplace_back(novoNumero, Cliente(nome, cpf), deposito);
    salvar();
    return &contas.back();
}

const std::vector<ContaBancaria> &Banco::getContas() const
{
    return contas;
}
