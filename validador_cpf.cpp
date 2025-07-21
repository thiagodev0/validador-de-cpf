#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <clocale>
#include <fstream>

using namespace std;

class ValidadorCPF
{
public:
    ValidadorCPF() = default;

    void definirCPF(const string& cpf)
    {
        cpf_ = limpar(cpf);
    }

    bool validar() const
    {
        if (cpf_.size() != 11 || todosIguais())
        {
            return false;
        }

        if (!validarDigito(9))
        {
            return false;
        }

        if (!validarDigito(10))
        {
            return false;
        }

        return true;
    }

private:
    string cpf_;

    static string limpar(const string& s)
    {
        string out;

        for (char c : s)
        {
            if (isdigit(static_cast<unsigned char>(c)))
            {
                out += c;
            }
        }

        return out;
    }

    bool todosIguais() const
    {
        return all_of(cpf_.begin(), cpf_.end(), [&](char c) { return c == cpf_[0]; });
    }

    bool validarDigito(int pos) const
    {
        int soma = 0;
        int peso = pos + 1;

        for (int i = 0; i < pos; ++i)
        {
            soma += (cpf_[i] - '0') * (peso--);
        }

        int resto = (soma * 10) % 11;

        if (resto == 10)
        {
            resto = 0;
        }

        return resto == (cpf_[pos] - '0');
    }
};

void salvarResultado(const string& cpf, bool valido)
{
    ofstream arquivo("cpfs.txt", ios::app);

    if (arquivo)
    {
        arquivo << cpf << " - " << (valido ? "válido" : "inválido") << '\n';
    }
}

bool simOuNao(const string& perg)
{
    char r;
    cout << perg << " (s/n)? ";
    cin >> r;
    return tolower(r) == 's';
}

void modoInterativo()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    cout << "\n*** Validador de CPF - Modo Interativo ***\n";

    do
    {
        string cpf;
        cout << "Digite o CPF: ";
        cin >> cpf;

        ValidadorCPF v;
        v.definirCPF(cpf);
        bool valido = v.validar();

        if (valido)
        {
            cout << "CPF válido!" << endl;
        }
        else
        {
            cout << "CPF inválido!" << endl;
        }

        salvarResultado(cpf, valido);
    }
    while (simOuNao("Validar outro CPF"));
}

void ajuda()
{
    cout << "\nUso: validador_cpf [opções]\n";
    cout << "  --interativo       Modo Interativo" << endl;
    cout << "  -c CPF             Validar o CPF especificado" << endl;
    cout << "  --ajuda            Exibe esta ajuda" << endl;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    if (argc == 1)
    {
        modoInterativo();
        return 0;
    }

    bool inter = false;
    string cpfArg;

    for (int i = 1; i < argc; ++i)
    {
        string a = argv[i];

        if (a == "--interativo")
        {
            inter = true;
            break;
        }

        if ((a == "-c" || a == "--cpf") && i + 1 < argc)
        {
            cpfArg = argv[++i];
        }
        else if (a == "--ajuda")
        {
            ajuda();
            return 0;
        }
    }

    if (inter)
    {
        modoInterativo();
    }
    else if (!cpfArg.empty())
    {
        ValidadorCPF v;
        v.definirCPF(cpfArg);
        bool valido = v.validar();

        if (valido)
        {
            cout << "CPF válido: " << cpfArg << endl;
        }
        else
        {
            cerr << "CPF inválido: " << cpfArg << endl;
        }

        salvarResultado(cpfArg, valido);
        return valido ? 0 : 1;
    }
    else
    {
        ajuda();
        return 1;
    }

    return 0;
}