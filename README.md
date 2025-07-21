# Validador de CPF em C++

Este repositório contém um **Validador de CPF** em C++ inspirado em um estilo de código simples e modular, com interface de linha de comando e modo interativo. Além disso, armazena o log de validações em um arquivo externo.

## Funcionalidades

* **Modo Interativo**: solicita ao usuário a entrada do CPF e exibe se é válido ou inválido, permitindo repetir o processo.
* **Linha de Comando**:

  * `--interativo` — entra em modo interativo
  * `-c <CPF>` ou `--cpf <CPF>` — valida um CPF específico
  * `--ajuda` — exibe instruções de uso
* **Persistência**: registra cada validação em `cpfs.txt` no formato:

  ```
  <CPF digitado> - válido
  <CPF digitado> - inválido
  ```

## Pré-requisitos

* Compilador C++ compatível com C++11 ou superior (recomendado: GCC, Clang ou MSVC)
* Sistema operacional com suporte a UTF-8 (para acentuação em PT-BR)

## Como Compilar

```bash
# Usando g++
g++ -std=c++11 -o validador_cpf validador_cpf.cpp
```

## Como Executar

### Modo Interativo

```bash
./validador_cpf --interativo
```

### Validação via Linha de Comando

```bash
./validador_cpf -c 123.456.789-09
```

Se o CPF for válido, retorna código de saída `0`; caso contrário, retorna `1`. Em ambos os casos, grava o resultado em `cpfs.txt`.

### Exemplo de Saída de `cpfs.txt`

```text
123.456.789-09 - inválido
111.444.777-35 - válido
```

## Estrutura de Arquivos

```
├── ValidadorCPF.cpp    # Código-fonte principal
├── cpfs.txt            # Histórico de validações (gerado após uso)
└── README.md           # Este documento
```