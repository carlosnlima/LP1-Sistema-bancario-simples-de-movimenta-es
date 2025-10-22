Projeto da Disciplina Linguagem de Programação I Banco SeniorTech Digital 2.0

Um sistema bancário simples e modular desenvolvido em C++, com arquitetura orientada a objetos e persistência em arquivo binário, simulando as principais operações de um banco digital.

Objetivo

Aplicar conceitos de Programação Orientada a Objetos (POO) em um contexto prático de simulação bancária, explorando encapsulamento, sobrecarga, persistência e interface de console interativa.

Funcionalidades Principais:

Criação de clientes com nome e CPF (com máscara automática).

Criação e gerenciamento de contas bancárias associadas a clientes.

Login automático pelo CPF, com criação de conta se não existir.

Depósitos, saques e transferências entre contas.

PIX via CPF do destinatário.

Pagamentos de boletos com descrição.

Aplicação de juros ao saldo.

Histórico detalhado de transações.

Persistência automática em arquivo binário (contas.dat).

Reset completo via script (reset.sh).

Conceitos Trabalhados:

Classes e objetos (Cliente, ContaBancaria, Banco, App).

Encapsulamento e uso de atributos privados.

Construtores personalizados.

Sobrecarga de métodos (transferir() para uma ou duas contas).

Vetores e manipulação de strings.

Persistência binária com ifstream e ofstream.

Interface textual interativa (menu por console).

Estrutura do Projeto:

sistema_bancario/
│
├── include/
│ ├── app.hpp
│ ├── banco.hpp
│ ├── cliente.hpp
│ ├── conta_bancaria.hpp
│ └── interface_console.hpp
│
├── src/
│ ├── app.cpp
│ ├── banco.cpp
│ ├── cliente.cpp
│ ├── conta_bancaria.cpp
│ └── interface_console.cpp
│
├── main.cpp
├── contas.dat
├── build.sh
└── reset.sh

Reset do Sistema:

Para apagar todos os dados e iniciar com as contas padrão (Ana, Bruno, Carla):

./reset.sh

ou manualmente:

rm -f contas.dat

Compilação e Execução:

Dentro da pasta sistema_bancario:

g++ -std=c++17 src/\*.cpp main.cpp -Iinclude -o banco
./banco

Ou, se preferir, use o script automático:

chmod +x build.sh
./build.sh

🧪 Contas Iniciais
Titular CPF Conta Saldo Inicial
Ana Souza 111.111.111-11 1001 R$ 500,00
Bruno Silva 222.222.222-22 1002 R$ 350,00
Carla Mendes 333.333.333-33 1003 R$ 150,00
📚 Desenvolvido com

Linguagem: C++17

IDE: Visual Studio Code (macOS)

Paradigma: Programação Orientada a Objetos

Autor:

Francisco Carlos Nascimento de Lima
Projeto acadêmico desenvolvido para a Disciplina de Linguagem de Programação I, com foco na prática de POO e persistência de dados em C++.
