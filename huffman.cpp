#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;
//Nodo del arbol
struct Node {
    char simbolo;
    int frecuencia;
    Node *left, *right;
};

// Agregar nodo al arbol
Node* getNode(char simbolo, int frecuencia, Node* left, Node* right) {
    Node* nodo = new Node();

    nodo->simbolo = simbolo;
    nodo->frecuencia = frecuencia;
    nodo->left =left;
    nodo->right= right;

    return nodo;
}

//ordenar la pila por frecuencia
struct comparar{
    bool operator()(Node*, Node* d){
        return i->frecuencia > d->frecuencia;
    }
};


// revisa el arbol de Huffman y guarda los codigos en un mapa
void encode(Node* raiz, string str, unordered_map<cahr,string> &CodigoHuffman) {
    if (raiz == nullptr)
        return;
    if (!raiz->left && !raiz->right)
    {
        CodigoHuuffman[raiz->simbolo] = str;
    }
    encode(raiz->left,str + "0", CodigoHuffman);
    encode(raiz->right,str + "1", CodigoHuffman);
    
}

// Revisa el arbol y lo decodifica
void decode(Node* raiz, int &index, string str) {
    if (!raiz->left && !raiz->right)
    {
        cout<<raiz->simbolo;
        return;
    }
    index++;
    if (str[index] == '0')
        decode(raiz->left, index, str);
    else 
        decode(raiz->right, index, str);
}

//crea el arbol
void CrearArbol(string text) {
    //cuenta la cantidad de veces que aparece cada simbolo
    unordered_map<char, int> frecuencia;
    for( char simbolo:text){
        frecuencia[simbolo]++;
    }
    //crea una cola de prioridad para guardar los nodos del arbol
    priority_queue<Node*, vector<Node*>, comp> pq;
    //Agrega a la cola de prioridad los nodos de cada caracter
    for(auto pair: frecuencia) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
    //hacer todo el proceso hasta que no haya mas de un nodo en la cola
    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        int sum = left->frecuencia + right->frecuencia;
        pq.push(getNode('\0', sum, left, right));
    }
    Node* raiz = pq top();
    //imprime los codigos codificados de cada caracter
    unordered_map<char, string> CodigoHuffman;
    encode(raiz, "", CodigoHuffman);
    cout<< "\n Los codigos de Huffman son:\n" << '\n';
    for(auto pair: CodigoHuffman){
        cout<< pair.first << " " << pair.second << '\n';
    }
    //imprime el mensaje original que el usuario ingreso, el codificado y lo vuel a decodificar
    cout<< "\nEl mensaje original era:\n " << text << '\n';
    string str = "";
    for(char simbolo: text) {
        str += CodigoHuffman[simbolo];
    }
    cout << "\n El texto codificado es:\n" << str << '\n';
    int index = -1;
    cout<< "\nEl texto decodificado es: \n";
    while(index <(int)str.size() -2){
        decode(raiz, index, str);
    }
    
}
int main(){
    cout<<"Ingrese el mensaje a comprimir: "<<endl;
    getline(cin,text);
    CrearArbol(text);
    return 0;
}