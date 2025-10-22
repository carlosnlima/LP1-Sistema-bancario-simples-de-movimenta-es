#include "../include/app.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// ===============================
// Menu de Login / Criação de Conta
// ===============================
void App::menuLogin()
{
    InterfaceConsole::cabecalho("BANCO SENIORTECH DIGITAL");
    cout << "[1] Entrar / Criar Conta\n";
    cout << "[0] Sair\n";
    cout << "Escolha: ";
    int opc;
    cin >> opc;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ limpa buffer imediatamente

    if (opc == 0)
        exit(0);

    string cpf;
    cout << "Digite seu CPF (apenas números): ";
    getline(cin, cpf);

    string cpfF = InterfaceConsole::formatarCPF(cpf);
    if (cpfF.empty())
    {
        cout << "CPF inválido.\n";
        InterfaceConsole::pausa();
        return;
    }

    contaAtual = banco.buscarPorCpf(cpfF);
    if (contaAtual)
    {
        InterfaceConsole::animacao("Validando acesso");
        cout << "Bem-vindo de volta, " << contaAtual->getNomeTitular() << "!\n";
        InterfaceConsole::pausa();
        return;
    }

    // Cadastro de novo cliente
    string nome;
    cout << "Nome completo: ";
    getline(cin, nome);

    double dep;
    cout << "Depósito inicial: ";
    cin >> dep;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa após leitura numérica

    contaAtual = banco.criarConta(nome, cpfF, dep);
    InterfaceConsole::animacao("Criando conta");
    cout << "Conta criada com sucesso!\n";
    InterfaceConsole::pausa();
}

// ===============================
// Menu Principal (após login)
// ===============================
void App::menuPrincipal()
{
    while (contaAtual)
    {
        InterfaceConsole::limpar();
        InterfaceConsole::cabecalho("MENU PRINCIPAL");
        cout << "Titular: " << contaAtual->getNomeTitular()
             << " | Conta: " << contaAtual->getNumero() << "\n";
        cout << "------------------------------------------\n";
        cout << "[1] Ver informações\n"
             << "[2] Depósito\n"
             << "[3] Saque\n"
             << "[4] Transferência\n"
             << "[5] PIX\n"
             << "[6] Pagar boleto\n"
             << "[7] Aplicar juros\n"
             << "[8] Histórico\n"
             << "[0] Logout\n";
        cout << "------------------------------------------\nEscolha: ";

        int op;
        cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ limpa antes de ler strings

        if (op == 0)
            break;

        switch (op)
        {
        case 1:
            contaAtual->exibirInformacoes();
            break;

        case 2:
        {
            double v;
            cout << "Valor para depósito: R$ ";
            cin >> v;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            contaAtual->depositar(v);
            cout << "Depósito concluído!\n";
            break;
        }

        case 3:
        {
            double v;
            cout << "Valor para saque: R$ ";
            cin >> v;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!contaAtual->sacar(v))
                cout << "Saldo insuficiente.\n";
            else
                cout << "Saque realizado!\n";
            break;
        }

        case 4:
        {
            int num;
            double v;
            cout << "Número da conta destino: ";
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Valor a transferir: R$ ";
            cin >> v;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            auto dest = banco.buscarPorNumero(num);
            if (!dest)
                cout << "Conta não encontrada.\n";
            else if (!contaAtual->transferir(v, *dest))
                cout << "Saldo insuficiente.\n";
            else
                cout << "Transferência concluída.\n";
            break;
        }

        case 5:
        {
            string cpf;
            cout << "CPF destino (apenas números): ";
            getline(cin, cpf);
            string cpfF = InterfaceConsole::formatarCPF(cpf);
            auto dest = banco.buscarPorCpf(cpfF);
            if (!dest)
            {
                cout << "Chave PIX não encontrada.\n";
            }
            else
            {
                double v;
                cout << "Valor: R$ ";
                cin >> v;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!contaAtual->transferir(v, *dest))
                    cout << "Saldo insuficiente.\n";
                else
                    cout << "PIX enviado!\n";
            }
            break;
        }

        case 6:
        {
            string desc;
            cout << "Descrição do boleto: ";
            getline(cin, desc);
            double v;
            cout << "Valor: R$ ";
            cin >> v;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!contaAtual->pagarBoleto(v, desc))
                cout << "Saldo insuficiente.\n";
            else
                cout << "Boleto pago!\n";
            break;
        }

        case 7:
        {
            double t;
            cout << "Taxa de juros (%): ";
            cin >> t;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            contaAtual->aplicarJuros(t);
            cout << "Juros aplicados!\n";
            break;
        }

        case 8:
            contaAtual->exibirHistorico();
            break;

        default:
            cout << "Opção inválida.\n";
            break;
        }

        banco.salvar();
        InterfaceConsole::pausa();
    }
}

// ===============================
// Execução geral do aplicativo
// ===============================
void App::executar()
{
    while (true)
    {
        InterfaceConsole::limpar();
        menuLogin();
        menuPrincipal();
        contaAtual = nullptr;
    }
}
