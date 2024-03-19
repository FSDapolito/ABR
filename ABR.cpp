#include <iostream>
using namespace std;

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

typedef struct Node* Nodo;

class BinarySearchTree {
private:
    Nodo root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    Nodo insert(Nodo radice, int data) {
        if (radice == nullptr) {
            Nodo nuovoNodo = new Node;
            nuovoNodo->data = data;
            nuovoNodo->left = nullptr;
            nuovoNodo->right = nullptr;
            nuovoNodo->parent = nullptr;
            return nuovoNodo;
        } else {
            if (data < radice->data) {
                radice->left = insert(radice->left, data);
                radice->left->parent = radice;
            } else if (data > radice->data) {
                radice->right = insert(radice->right, data);
                radice->right->parent = radice;
            }
            return radice;
        }
    }

    void inorder(Nodo x) {
        if (x == nullptr) {
            return;
        }

        inorder(x->left);
        cout << x->data << endl;
        inorder(x->right);
    }

    bool search(Nodo radice, int chiave){
        if(radice == nullptr){
            return false;
        }
        if(radice->data == chiave){
            return true;
        }
        if(radice->data<chiave){
            return search(radice->right,chiave);
        }
            return search(radice->left,chiave);
    }

    Nodo Search(Nodo x, int chiave){
        if(x==nullptr){
            return nullptr;
        }
        if(x->data==chiave){
            return x;
        }
        if(x->data<chiave){
            return Search(x->right,chiave);
        }
      
            return Search(x->left,chiave);
        
    }




    Nodo minimum(Nodo x){
        while(x->left!=nullptr)
            x=x->left;
        return x;
    }

    Nodo maximum(Nodo x){
        while(x->right!=nullptr)
            x=x->right;
        return x;
    }



    void transplant(Nodo u, Nodo v)
    {
        if(u->parent==nullptr){
            root=v;
        }
        else if (u==u->parent->left){
            u->parent->left=v;
        }
        else{
            u->parent->right=v;
        }
        if(v!=nullptr){
            v->parent=u->parent;
        }
    }

    //predecessore
    //il piu'grande tra i piu' piccoli
   Nodo predecessore(Nodo radice, int valore) {
    Nodo nodoCorrente = Search(radice, valore);
    if (nodoCorrente != nullptr) {
        // Se il nodo ha un sottoalbero sinistro, allora il predecessore
        // è il massimo di quel sottoalbero.
        if (nodoCorrente->left != nullptr) {
            return maximum(nodoCorrente->left);
        }
        // Se il nodo non ha un sottoalbero sinistro, dobbiamo risalire nell'albero
        // per trovare il predecessore.
        Nodo predecessore = nullptr;
        Nodo corrente = radice;
        while (corrente != nullptr) {
            if (nodoCorrente->data < corrente->data) {
                corrente = corrente->left;
            } else if (nodoCorrente->data > corrente->data) {
                predecessore = corrente;
                corrente = corrente->right;
            } else {
                break; // Abbiamo trovato il nodo, interrompiamo il ciclo.
            }
        }
        return predecessore;
    } else {
        return nullptr; // Il nodo non è presente nell'albero.
    }
}



    //successore
    //il piu'piccolo tra i piu' grandi
    Nodo successore(Nodo x,int chiave){
        Nodo nodoCorrente=Search(x,chiave);
        if(nodoCorrente!=nullptr){
            if(nodoCorrente->right!=nullptr){
                return minimum(nodoCorrente->right);
            }
            Nodo successore = nullptr;
            Nodo corrente = x;
            while (corrente!=nullptr)
            {
                if(nodoCorrente->data<corrente->data){
                    successore=corrente;
                    corrente=corrente->left;
                }
                else if(nodoCorrente->data>corrente->data){
                    corrente=corrente->right;
                }else{
                    break;
                }
            }
            return successore;
            
        }else{
            return nullptr;
        }
    }



    Nodo remove(Nodo radice, int data){
        if(radice ==nullptr){
            return radice;
        }

        if(data<radice->data){
            radice->left=remove(radice->left,data);
        }
        else if(data>radice->data){
            radice->right=remove(radice->right,data);
        }
        else{
            if(radice->left == nullptr){
                Nodo temp = radice->right;
                transplant(radice,temp);
                delete radice;
                return temp;
            }
            else if(radice->right==nullptr){
                Nodo temp  = radice->left;
                transplant(radice, temp);
                delete radice;
                return temp;
            }
            else{
            Nodo temp = minimum(radice->right);
            radice->data=temp->data;
            radice->right=remove(radice->right,temp->data);
            }
        }
        return radice;
    }
};

int main() {
    BinarySearchTree tree;
    Nodo radice = nullptr;


    radice = tree.insert(radice, 20);
    radice = tree.insert(radice, 17);
    radice = tree.insert(radice, 11);
    radice = tree.insert(radice, 19);
    radice = tree.insert(radice, 9);
    radice = tree.insert(radice, 5);
    radice = tree.insert(radice, 24);
    radice = tree.insert(radice, 21);





    if(tree.search(radice, 10)){
        cout<<"La chiave e'stata trovata"<<endl;
    }else{
        cout<<"La chiave non e' contenuta nell'albero"<<endl;
    }

    tree.inorder(radice);
    //tree.remove(radice,5);
    cout<<endl;
    // tree.inorder(radice);
     Nodo pre = tree.predecessore(radice,21);
     cout<<endl;
     if(pre == nullptr){
        cout << " Predecessore nullo "<<endl;
        return 0;
     }
     cout<<pre->data<<endl;
/*
     Nodo suc = tree.successore(radice,12);
     cout <<endl;
     if(suc==nullptr){
        cout<<"Il valore inserito non e' nell'ABR"<<endl;
     }else{
     cout<<"Successore = "<<suc->data<<endl;
     }
     */
        tree.remove(radice,9);

        cout<<endl;
        tree.inorder(radice);


    return 0;
}
