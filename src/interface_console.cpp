#include "../include/interface_console.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void InterfaceConsole::limpar()
{
    system(CLEAR);
}

void InterfaceConsole::pausa()
{
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void InterfaceConsole::animacao(const std::string &texto)
{
    std::cout << "\n"
              << texto;
    for (int i = 0; i < 3; i++)
    {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << "\n";
}

std::string InterfaceConsole::formatarCPF(std::string cpf)
{
    cpf.erase(std::remove_if(cpf.begin(), cpf.end(), [](unsigned char c)
                             { return !std::isdigit(c); }),
              cpf.end());
    if (cpf.size() != 11)
        return "";
    return cpf.substr(0, 3) + "." + cpf.substr(3, 3) + "." + cpf.substr(6, 3) + "-" + cpf.substr(9, 2);
}

void InterfaceConsole::cabecalho(const std::string &titulo)
{
    std::cout << "╔════════════════════════════════════════════╗\n";
    std::cout << "║ " << titulo << std::string(42 - titulo.size(), ' ') << "║\n";
    std::cout << "╚════════════════════════════════════════════╝\n";
}
