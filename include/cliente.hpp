#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <iostream>

class Cliente
{
private:
    std::string nome;
    std::string cpf;

public:
    Cliente() = default;
    Cliente(const std::string &nome, const std::string &cpf);

    std::string getNome() const;
    std::string getCpf() const;

    void setNome(const std::string &nome);
    void setCpf(const std::string &cpf);
};

#endif
