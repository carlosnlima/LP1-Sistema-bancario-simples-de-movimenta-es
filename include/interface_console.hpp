#ifndef INTERFACECONSOLE_HPP
#define INTERFACECONSOLE_HPP

#include "banco.hpp"
#include <string>

class InterfaceConsole
{
public:
    static void limpar();
    static void pausa();
    static void animacao(const std::string &texto);
    static std::string formatarCPF(std::string cpf);
    static void cabecalho(const std::string &titulo);
};

#endif
