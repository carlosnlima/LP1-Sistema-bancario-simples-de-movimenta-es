#include <iostream>
#include <string>
#include <vector>
using namespace std;

// criacao da Classe Cliente
class Cliente
{
private:
    string nome;
    string cpf;

public:
    Cliente(string nome, string cpf)
    {
        this->nome = nome;
        this->cpf = cpf;
    }

    string getNome()
    {
        return nome;
    }

    string getCPF()
    {
        return cpf;
    }
};

// criacao da Classe ContaBancaria
class ContaBancaria
{
private:
    int numero;
    double saldo;
    Cliente titular;

public:
    ContaBancaria(int numero, Cliente titular, double saldo = 0.0) : titular(titular)
    {
        this->numero = numero;
        this->saldo = saldo;
    }

    void depositar(double valor)
    {
        if (valor > 0)
        {
            saldo += valor;
        }
    }

    void sacar(double valor)
    {
        if (valor > 0 && valor <= saldo)
        {
            saldo -= valor;
        }
        else
        {
            cout << "Saldo insuficiente para saque!" << endl;
        }
    }

    void transferir(double valor, ContaBancaria &destino)
    {
        if (valor > 0 && valor <= saldo)
        {
            saldo -= valor;
            destino.depositar(valor);
            cout << "Transferido: R$ " << valor << " da conta " << numero
                 << " para a conta " << destino.numero << endl;
        }
        else
        {
            cout << "Saldo insuficiente para transferência!" << endl;
        }
    }

    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2)
    {
        if (valor > 0 && valor <= saldo)
        {
            double metade = valor / 2.0;
            saldo -= valor;
            destino1.depositar(metade);
            destino2.depositar(metade);
            cout << "Transferido: R$ " << metade << " para cada conta ("
                 << destino1.numero << " e " << destino2.numero
                 << ") da conta " << numero << endl;
        }
        else
        {
            cout << "Saldo insuficiente para transferência dupla!" << endl;
        }
    }

    void exibirSaldo()
    {
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }

    void exibirInformacoes()
    {
        cout << "Titular: " << titular.getNome() << ", CPF: " << titular.getCPF() << endl;
        cout << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
    }
};

int main()
{
    // aqui, criei os clientes iguais ao solicitados na atividade. Pensei em colocar mais alguns para ficar mais didatico, porem deixei no basico.
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // nessa parte, criei as contas bancarias com os saldos iniciais de cada cliente
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Aqui, sera possivel exibir o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana podera transferir  R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // aqui, temos a exibicao dos dos saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}