#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <fstream>

using namespace std;

struct TreeNode {
    unsigned int exp;
    unsigned int height;
    float K;
    TreeNode* bigger;
    TreeNode* smaller;
};

class BinaryTree {
    private:
        TreeNode *root;
        TreeNode *current;
        float result;
        unsigned int delta;
    public:
        BinaryTree() {
            //El arbol binario almacen su raiz y
            //un nodo que usaremos para Horner
            root = NULL;
            current = NULL;
            result = 0.0; //Resultado de Horner
            delta = 0; //La diferencia entre el nodo actual y el anterior
        }
        ~BinaryTree() {
            PostOrder();
            result = 0;
            delta = 0;
            cout << "Se borraron todos los mononomios" << endl;
        }
        
        /*
        Nombre: insert (clase BinaryTree)
        Resumen: inserta un monomio en nuestro polinomio de clase BinaryTree
        Input: e (exponente del monomio a insertar), 
        k (constante del monomio a insertar)
        Retorno: retorna 1, si se inserta. 0 si no es posible
        */
        int insert(unsigned int e, float k) {
            TreeNode *insertion = new TreeNode;
            
            insertion->exp = e;
            insertion->K = k;
            insertion->height = 0;
            insertion->bigger = NULL;
            insertion->smaller = NULL;

            //Si es el primer elemento, remplaza la raiz
            if (root == NULL) {
                cout << "Se inserto la raiz del arbol" << endl;
                root = insertion;
                return 1;
            } 
            //De no ser asi, nos vamos a la funcion de insercion
            if (root != NULL) {
                insertAux(root, insertion);
                return 1;
            }
            return 0;
        }

        /*
        Nombre: insertAux (clase BinaryTree)
        Resumen: inserta un monomio de en el arbol de forma que quede ordenado
        Input: input (posicion en el arbol a insertar),
        insertion (monomio a insertar como hoja de input)
        Retorno: es void, no retorna nada
        */
        void insertAux(TreeNode *input, TreeNode *insertion) {
            if (insertion->exp > input->exp) {
                if (input->bigger != NULL){
                    insertAux(input->bigger, insertion);
                }
                if (input->bigger == NULL){
                    cout << "Se inserto un elemento del arbol" << endl;
                    cout << "   (Mayor a "<< input->exp <<" )" << endl;
                    input->bigger = insertion;
                }
            }
            if (insertion->exp < input->exp) {
                if (input->smaller != NULL){
                    insertAux(input->smaller, insertion);
                }
                if (input->smaller == NULL){
                    cout << "Se inserto un elemento del arbol" << endl;
                    cout << "   (Menor a "<< input->exp <<")" << endl;
                    input->smaller = insertion;
                }
            }
        }

        //Esta y las funciones siguientes, sirven para calcular Horner

        /*
        Nombre: inOrder (clase BinaryTree)
        Resumen: Recorre el arbol en InOrden
        Input: x (valor a evaluar el polinomio)
        Retorno: retorna un float con el valor evaluado del polinomio
        */
        float InOrder(float x) {
            result = 0.0;
            delta = 0.0;
            InOrderAux(root, x);
            cout << "El resultado es " << result << endl;
            return result;
        }

        /*
        Nombre: inOrderAux (clase BinaryTree)
        Resumen: Recorre el arbol en InOrden y evalua con la funcion Process
        Input: x (valor a evaluar el polinomio)
        Retorno: retorna un float con el valor evaluado del polinomio
        */
        void InOrderAux(TreeNode *input, float x) {            
            if(input != NULL) {
                if(input->bigger != NULL) {
                    InOrderAux(input->bigger, x);
                }
                Process(input, x);
                if(input->smaller != NULL) {
                    InOrderAux(input->smaller, x);
                }
            }
        }
        //Para calcular Horner, elevamos X hasta su diferencia con el elemento siguiente (menor)
        //Luego lo sumamos a su constante, y este proceso es matematicamente equivalente a Horner
        //En situaciones en las cuales no estan todos los M monomios
        
        /*
        Nombre: Process (clase BinaryTree)
        Resumen: Calcula el valor del polinomio con metodo de Horner, tomando un
        delta exponente para los monomios que no existen
        Retorno: retorna un float con el valor evaluado del polinomio
        */
        void Process(TreeNode *input, float x) {

            if (delta > input->exp) {
                for(unsigned int i = delta - input->exp; i > 0; i--) {
                    result = result * x;
                }
            }
            delta = input->exp;
            current = input;
            result += (float)current->K;
        }
        //Esta y las funciones posteriores seran para remover los nodos
        //Y se utiliazran como destructor de clase

        /*
        Nombre: PostOrder (clase BinaryTree)
        Resumen: Recorre el arbol en PostOrden
        Input: no hay input
        Retorno: no retorna nada, es void
        */
        void PostOrder() {
            PostOrderAux(root);
        }

        /*
        Nombre: PostOrderAux (clase BinaryTree)
        Resumen: Recorre el arbol en PostOrden
        Input: la raiz origen para recorrer en PostOrden
        Retorno: no retorna nada, es void
        */
        void PostOrderAux(TreeNode *input) {            
            if(input != NULL) {
                if(input->bigger != NULL) {
                    PostOrderAux(input->bigger);
                }
                if(input->smaller != NULL) {
                    PostOrderAux(input->smaller);
                }
                Remove(input);
            }
        }

        /*
        Nombre: Remove (clase BinaryTree)
        Resumen: Elimina los nodos del arbol partiendo desde los hijos, el PostOrden
        era el metodo mas adecuado para esto
        Input: la raiz origen para recorrer en PostOrden
        Retorno: no retorna nada, es void
        */
        void Remove(TreeNode *input) {
            cout << "se borró el elemeto "<< input->K << "X^" << input->exp << endl;
            delete input;
        }

        //Esta y las funciones posteriores seran para obtener los nodos
        //Durante la lectura de COEFICIENTE en el archivo

        /*
        Nombre: PreOrder (clase BinaryTree)
        Resumen: Busca en PreOrden el valor de COEFICIENTE
        Input: e (exponente a buscar de COEFICIENTE)
        Retorno: retorna la constante del monomio en cuestion
        */
        float PreOrder(unsigned int e) {
            result = 0.0;
            delta = 0.0;
            PreOrderAux(root, e);
            return result;
        }
        /*
        Nombre: PreOrderAux (clase BinaryTree)
        Resumen: Busca en PreOrden el valor de COEFICIENTE
        Input: e (exponente a buscar de COEFICIENTE)
        Retorno: retorna la constante del monomio en cuestion
        */
        void PreOrderAux(TreeNode *input, unsigned int e) {            
            if(input != NULL) {
                Get(input, e);
                if(input->bigger != NULL) {
                    PreOrderAux(input->bigger, e);
                }
                if(input->smaller != NULL) {
                    PreOrderAux(input->smaller, e);
                }
            }
        }
        /*
        Nombre: Get (clase BinaryTree)
        Resumen: Evalua si el exponente corresponde
        Retorno: retorna un float con el valor evaluado del polinomio
        */
        void Get(TreeNode *input, unsigned int e) {
            if (e == input->exp) {
                result = input->K;    
            }
        }
        

};
int main(){

    fstream file;
    file.open("ejemplo.txt", ios::in);
    if( !file.is_open() ){
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);
    }

    BinaryTree *arrayFinal;
    string operacion;
    int nroPoly;
    float aux; 

    int N, M, expAux, baseAux;

    file >> N;
    cout << "N es " << N << endl;
    //arrayFinal.setLengthN(N);
    arrayFinal = new BinaryTree[N];

    for (int i = 0; i < N; i++) {
        file >> M;
        cout << "la M numero " << i << " es " << M << endl;
        //arrayFinal.setLengthM(i, M);
        
        for (int k = 0; k < M; k++) {
            file >> expAux >> baseAux;
            cout << "Creamos el nodo " << baseAux << "X^";
            cout << expAux << endl;

            //arrayFinal.add_monomio(i, expAux, baseAux);
            arrayFinal[i].insert(expAux, baseAux);
        }
    }
    cout << "Leimos todos los polinomios!" << endl;

    fstream output;
    output.open("output.txt", ios::out);
    if( !output.is_open() ){
        cout<<"Error al crear el archivo"<<endl;
        exit(1);
    }

    while(!file.eof()) {
        file >> operacion >> nroPoly >> aux;
        if (operacion == "EVALUAR") {
            cout << arrayFinal[nroPoly].InOrder(aux) << endl;
            output << arrayFinal[nroPoly].InOrder(aux) << endl;
        }
        if (operacion == "COEFICIENTE") {
            cout << arrayFinal[nroPoly].PreOrder((int)aux) << endl;    
            output << arrayFinal[nroPoly].PreOrder((int)aux) << endl;
        }
    }

    cout << endl;
    for(int i = 0; i < N; i++) {
        arrayFinal[i].~BinaryTree();
    }
    file.close();
    output.close();
    return 0;
}