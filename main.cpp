#include <iostream>
#include <string>
using namespace std;

enum Ordenacao {
    POR_TITULO,
    POR_AUTOR
};

struct Livro {
    string titulo;
    string autor;
    int isbn;
    bool disponivel;
};

struct Estante {
    Livro* livro;
    Estante* prox;
};

Ordenacao tipoOrdenacao = POR_TITULO;

void ImprimeLista(Estante* head) {
    Estante* aux = head->prox;
    while (aux != nullptr) {
        if (aux->livro != nullptr) {
            cout << "Titulo: " << aux->livro->titulo << ", Autor: " << aux->livro->autor << ", ISBN: " << aux->livro->isbn << ", Disponivel: " << (aux->livro->disponivel ? "Sim" : "Nao") << endl;
        }
        aux = aux->prox;
    }
}

void criaEstante(Estante*& e) {
    e = new Estante;
    e->livro = nullptr;
    e->prox = nullptr;
}

void criaLivro(Livro*& l, string titulo, string autor, int isbn) {
    l = new Livro;
    l->titulo = titulo;
    l->autor = autor;
    l->isbn = isbn;
    l->disponivel = true;
}

void insereLivroNaEstante(Estante*& head, Livro* l) {
    Estante* aux = head;
    Estante* novo;
    criaEstante(novo);
    novo->livro = l;

    if (aux->prox == nullptr) { // Se a estante est� vazia
        aux->prox = novo;
    } else {
        while (aux->prox != nullptr) {
            if ((tipoOrdenacao == POR_TITULO && l->titulo < aux->prox->livro->titulo) ||
                (tipoOrdenacao == POR_AUTOR && l->autor < aux->prox->livro->autor)) {
                novo->prox = aux->prox;
                aux->prox = novo;
                break;
            }
            aux = aux->prox;
        }
        if (aux->prox == nullptr) { // Chegou ao final da estante
            aux->prox = novo;
        }
    }
    ImprimeLista(head);
}

void removeLivroDaEstante(Estante*& head, int isbn) {
    Estante* aux = head;
    Estante* exc = nullptr;

    while (aux->prox != nullptr && aux->prox->livro->isbn != isbn) {
        aux = aux->prox;
    }

    if (aux->prox == nullptr) {
        cout << "O livro nao esta na estante" << endl;
    }
    else {
        exc = aux->prox;
        aux->prox = exc->prox;
        delete exc->livro;
        delete exc;
        cout << "Livro removido com sucesso." << endl;
    }
    ImprimeLista(head);
}

void atualizaStatusLivro(Estante*& head, int isbn) {
    Estante* aux = head;

    while (aux->prox != nullptr && aux->prox->livro->isbn != isbn) {
        aux = aux->prox;
    }

    if (aux->prox == nullptr) {
        cout << "O livro nao esta na estante" << endl;
    }
    else {
        aux = aux->prox;
        aux->livro->disponivel = !aux->livro->disponivel;
        cout << "Status atualizado com sucesso." << endl;
    }
    ImprimeLista(head);
}

void buscaPorTitulo(Estante* head, const string& titulo) {
    Estante* aux = head;
    while (aux != nullptr) {
        if (aux->livro != nullptr && aux->livro->titulo == titulo) {
            cout << "Livro encontrado:" << endl;
            cout << "Titulo: " << aux->livro->titulo << ", Autor: " << aux->livro->autor << ", ISBN: " << aux->livro->isbn << ", Disponivel: " << (aux->livro->disponivel ? "Sim" : "Nao") << endl;
        }
        aux = aux->prox;
    }
}

void buscaPorAutor(Estante* head, const string& autor) {
    Estante* aux = head;
    while (aux != nullptr) {
        if (aux->livro != nullptr && aux->livro->autor == autor) {
            cout << "Livro encontrado do autor '" << autor << "':" << endl;
            cout << "Titulo: " << aux->livro->titulo << endl;
        }
        aux = aux->prox;
    }
}

void alterarOrdenacaoParaPorTitulo(Estante*& head) {
    tipoOrdenacao = POR_TITULO;

    Estante* novaEstante = nullptr;
    criaEstante(novaEstante);
    Estante* aux = head->prox;

    while (aux != nullptr) {
        Estante* prox = aux->prox;
        insereLivroNaEstante(novaEstante, aux->livro);
        aux = prox;
    }

    while (head->prox != nullptr) {
        Estante* temp = head->prox;
        head->prox = temp->prox;
        delete temp;
    }

    head->prox = novaEstante->prox;
    delete novaEstante;
    ImprimeLista(head);
}

void alterarOrdenacaoParaPorAutor(Estante*& head) {
    tipoOrdenacao = POR_AUTOR;

    Estante* novaEstante = nullptr;
    criaEstante(novaEstante);
    Estante* aux = head->prox;

    while (aux != nullptr) {
        Estante* prox = aux->prox;
        insereLivroNaEstante(novaEstante, aux->livro);
        aux = prox;
    }

    while (head->prox != nullptr) {
        Estante* temp = head->prox;
        head->prox = temp->prox;
        delete temp;
    }

    head->prox = novaEstante->prox;
    delete novaEstante;
    ImprimeLista(head);
}

int main() {
    Estante* e = nullptr;
    criaEstante(e);

    while (true) {
        cout << "Escolha uma opcao:" << endl;
        cout << "1. Adicionar livro" << endl;
        cout << "2. Remover livro" << endl;
        cout << "3. Emprestimo e devolucao" << endl;
        cout << "4. Busca por titulo" << endl;
        cout << "5. Busca por autor" << endl;
        cout << "6. Reordenar por titulo" << endl;
        cout << "7. Reordenar por autor" << endl;
        cout << "8. Imprimir lista" << endl;
        cout << "9. Sair" << endl;

        int escolha;
        cin >> escolha;

        if (escolha == 1) {
            string titulo, autor;
            int isbn;
            cout << "Digite o titulo do livro: ";
            cin.ignore(); // Limpar o buffer
            getline(cin, titulo);
            cout << "Digite o autor do livro: ";
            getline(cin, autor);
            cout << "Digite o ISBN do livro: ";
            cin >> isbn;
            Livro* novoLivro = nullptr;
            criaLivro(novoLivro, titulo, autor, isbn);
            insereLivroNaEstante(e, novoLivro);
        }
        else if (escolha == 2) {
            int isbn;
            cout << "Digite o ISBN do livro a ser removido: ";
            cin >> isbn;
            removeLivroDaEstante(e, isbn);
        }
        else if (escolha == 3) {
            int isbn;
            cout << "Digite o ISBN do livro a ser atualizado: ";
            cin >> isbn;
            atualizaStatusLivro(e, isbn);
        }
        else if (escolha == 4) {
            string titulo;
            cout << "Digite o titulo do livro a ser buscado: ";
            cin.ignore();
            getline(cin, titulo);
            buscaPorTitulo(e, titulo);
        }
        else if (escolha == 5) {
            string autor;
            cout << "Digite o autor dos livros a serem buscados: ";
            cin.ignore();
            getline(cin, autor);
            buscaPorAutor(e, autor);
        }
        else if (escolha == 6) {
            alterarOrdenacaoParaPorTitulo(e);
        }
        else if (escolha == 7) {
            alterarOrdenacaoParaPorAutor(e);
        }
        else if (escolha == 8) {
            ImprimeLista(e);
        }
        else if (escolha == 9) {
            break;
        }
        else {
            cout << "Opcao invalida. Tente novamente." << endl;
        }
    }

    while (e != nullptr) {
        Estante* temp = e;
        e = e->prox;
        delete temp;
    }

    return 0;
}
