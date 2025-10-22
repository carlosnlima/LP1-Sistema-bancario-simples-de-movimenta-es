#include "../include/cliente.hpp"

Cliente::Cliente(const std::string &nome, const std::string &cpf)
    : nome(nome), cpf(cpf) {}

std::string Cliente::getNome() const { return nome; }
std::string Cliente::getCpf() const { return cpf; }

void Cliente::setNome(const std::string &nome) { this->nome = nome; }
void Cliente::setCpf(const std::string &cpf) { this->cpf = cpf; }
