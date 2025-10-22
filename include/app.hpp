#ifndef APP_HPP
#define APP_HPP

#include "banco.hpp"
#include "interface_console.hpp"

class App
{
private:
    Banco banco;
    ContaBancaria *contaAtual = nullptr;

    void menuPrincipal();
    void menuLogin();

public:
    void executar();
};

#endif
