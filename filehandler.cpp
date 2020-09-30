#include <iostream>
#include <string>
#include <fstream>
//STL
#include <vector>
//Local
#include "filehandler.h"

using namespace std;


int alter (char symbol){
    if (static_cast<int>(symbol) % 2 == 0){
        return 1;
    }
    return -1;
}

vector <bool> charToBin (char sybmol){
    vector <bool> array;
    for (int var = 0; var < 8; ++var) {
        bool check = sybmol & (1 << (7-var));
        array.push_back(check);
    }
    return array;
}

string boolVecToStr (vector <bool> array){
    string output;
    for (size_t i = 0; i < array.size(); i++) {
        output += to_string(array[i]);
    }
    return output;
}

string printBin (char symbol){
    string output = " ";
    output += boolVecToStr(charToBin(symbol));
    return output;
}


//CODER
string Coder::readFile (string inFilename){
    ifstream inFile;
    inFile.open(inFilename.c_str(), ios::binary);
    if (inFile.is_open()){
        //Чтение
        string readed;
        char byte;
        while (inFile.get(byte)){
            readed += byte;
        }
        inFile.close();
        return readed;
    }
    else {
        throw "Can't open " + inFilename;
    }
}
bool Coder::writeFile (string outFilename, string outInfo){
    ofstream outFile;
    outFile.open(outFilename.c_str(), ios::binary);
    if (outFile.is_open()){
        outFile << outInfo;
        outFile.close();
        return true;
    }
    else {
        throw "Can't open " + outFilename;
    }
}
string Coder::fileEncrypt (string inFilename){
    string readed = readFile(inFilename);
    cout << "<> Encrypting file " << inFilename;
    readed = encrypt(readed);
    cout << " -- Done" << endl;
    return readed;
}
string Coder::fileDecrypt (string inFilename){
    string readed = readFile(inFilename);
    cout << "<> Decrypting file " << inFilename;
    readed = encrypt(readed);
    cout << " -- Done" << endl;
    return readed;
}
string Coder::filePack (string inFilename){
    string readed = readFile(inFilename);
    cout << "<> Packing file " << inFilename;
    readed = packer.pack(readed);
    cout << " -- Done" << endl;
    return readed;
}
string Coder::fileUnpack (string inFilename){
    string readed = readFile(inFilename);
    cout << "<> Unpacking file " << inFilename;
    readed = packer.unpack(readed);
    cout << " -- Done" << endl;
    return readed;
}
string Coder::filePackAndEncrypt (string inFilename){
    string readed = readFile(inFilename);
    cout << "<> Packing file " << inFilename;
    readed = packer.pack(readed);
    cout << " -- Done" << endl;
    cout << "<> Encrypting file " << inFilename;
    readed = encrypt(readed);
    cout << " -- Done" << endl;
    return readed;
}
string Coder::fileDecryptAndUnpack (string inFilename){
    string readed = readFile(inFilename);
    cout << "<> Decrypting file " << inFilename;
    readed = encrypt(readed);
    cout << " -- Done" << endl;
    cout << "<> Unpacking file " << inFilename;
    readed = packer.unpack(readed);
    cout << " -- Done" << endl;
    return readed;
}
string Coder::encrypt(string input){
    string output;
    char byte;
    for (size_t i = 0, k = 0; i < input.size(); i++, k++){
        if (k > coderStringKey.size()){
            k = 0;
        }
        byte = 0;
        byte = byte | (coderStringKey[k] >> 2);
        output += input[i] ^ byte;
    }
    return output;
}
string Coder::decrypt (string input){
    string output, tmpReaded;
    char byte;
    for (size_t i = 0, k = 0; i < input.size(); i++, k++){
        if (k > coderStringKey.size()){
            k = 0;
        }
        byte = 0;
        byte = byte | (coderStringKey[k] >> 2);
        output += input[i] ^ byte;
    }
    return output;
}
void Coder::writeTreeFile (string filename){
    if (filename.find_first_of(".") > 0){
        filename = filename.substr(0, filename.find_first_of("."));
    }
    filename += ".huff";
    cout << "<> Writing a Huffman tree into file " << filename;
    this->writeFile(filename, packer.getTree());
    cout << " -- Done" << endl;
}
void Coder::readTreeFile (string filename){
    if (filename.find_first_of(".") > 0){
        filename = filename.substr(0, filename.find_first_of("."));
    }
    filename += ".huff";
    cout << "<> Reading a Huffman tree from file " << filename;
    packer.setTree(this->readFile(filename));
    cout << " -- Done" << endl;
}
string Coder::pack (string input){
    return packer.pack(input);
}
string Coder::unpack (string input){
    return packer.unpack(input);
}
void Coder::clearPacker (){
    this->packer.clearMyself();
}
string Coder::killSlashR (string input){
    string output;
    for (size_t i = 0; i < input.size(); i++){
        if (input[i] != '\r'){
            output += input[i];
        }
    }
    return output;
}


//TREE
Node::Node (){
    this->leftSon = this->rightSon = this->parent = nullptr;
}
Node::Node (Node *parent){
    this->leftSon = this->rightSon = nullptr;
    this->parent = parent;
}
Node::Node (char info, Node *parent){
    this->info = info;
    this->parent = parent;
    this->leftSon = this->rightSon = nullptr;
}
Node::Node (char info, int size){
    this->info = info;
    this->size = size;
    this->leftSon = this->rightSon = this->parent = nullptr;
}
Node::Node (Node *leftSon, Node *rightSon){
    this->size = leftSon->size + rightSon->size;
    this->leftSon = leftSon;
    this->rightSon = rightSon;
    leftSon->parent = rightSon->parent = this;
}


//PACKER
void Packer::fillEncryptMap (Node *root){
    if (root->leftSon){
        this->tmpReadedCode.push_back(0);
        fillEncryptMap(root->leftSon);
    }
    if (root->rightSon){
        this->tmpReadedCode.push_back(1);
        fillEncryptMap(root->rightSon);
    }
    if (root->leftSon == nullptr && root->rightSon == nullptr){
        encryptMap[root->info] = tmpReadedCode;
    }
    tmpReadedCode.pop_back();
}
string Packer::pack (string input){
    string huffFile;
    string output;
    vector <bool> binOut;

    for (size_t i = 0; i < input.size(); i++){
        symbolsFreq[input[i]]++;
    }
////Отображает кол-во каждого символа
//    for (map <char, int>::iterator it = symbolsFreq.begin(); it != symbolsFreq.end(); it++){
//        cout << it->first << ':' << it->second << endl;
//    }
    for (map <char, int>::iterator it = symbolsFreq.begin(); it != symbolsFreq.end(); it++){
        Node *tmp = new Node(it->first, it->second);
        nodeList.push_back(tmp);
    }

    while (nodeList.size() > 1){
        nodeList.sort(NodeCompare());
        Node *tmpLeft = nodeList.front();
        nodeList.pop_front();
        Node *tmpRight = nodeList.front();
        nodeList.pop_front();
        Node *parent = new Node(tmpLeft, tmpRight);
        nodeList.push_front(parent);
    }
    Node *root = nodeList.front();
    fillEncryptMap(root);

////Коды символом
//    cout << endl;
//    for (map <char, vector<bool> >::iterator it=encryptMap.begin();
//         it != encryptMap.end(); it++) {
//        cout << it->first << ':';
//        for (size_t i = 0; i < it->second.size(); i++) {
//            cout << it->second[i];
//        }
//        cout << endl;
//    }

    for (size_t i = 0; i < input.size(); i++){
        for (size_t j = 0; j < encryptMap[input[i]].size(); j++) {
            binOut.push_back(encryptMap[input[i]][j]);
        }
    }

    char byte = 0;
    for (size_t i = 0; i < binOut.size(); i++){
        byte = static_cast<char>(byte | binOut[i] << (7-(i % 8)));
        if ((i % 8 == 7) && (i > 0)){
            output += byte;
            byte = 0;
        }
    }
    if (binOut.size() % 8 > 0){
        output += byte;
    }
    readBorder = binOut.size() % 8;

    return output;
}
string Packer::unpack (string input){
    string output;
    char tmpCharToNum;
    vector <bool> binOut;

    if (readBorder > 0){
        readBorder = 8 - readBorder;
    }
    for (size_t i = 0; i < input.size(); i++) {
        tmpCharToNum = input[i];
        vector <bool> tmpVecBool = charToBin(tmpCharToNum);
        binOut.insert(binOut.end(), tmpVecBool.begin(), tmpVecBool.end());
    }

    Node *root = nodeList.front();
    Node *tmp = root;

    for (size_t i=0; i < binOut.size()-readBorder; i++) {
        if (binOut[i]){
            tmp = tmp->rightSon;
        }
        else {
            tmp = tmp->leftSon;
        }
        if (tmp->leftSon == nullptr && tmp->rightSon == nullptr){
            output += tmp->info;
            tmp = root;
        }
    }

    return output;
}
void Packer::printTree(Node *temp){
    if (temp->leftSon == nullptr && temp->rightSon == nullptr){
        tmpTreeString += "1";
        tmpTreeString += temp->info;
    }
    else {
        tmpTreeString += "0";
    }
    if (temp->leftSon){
        printTree(temp->leftSon);
    }
    if (temp->rightSon){
        printTree(temp->rightSon);
    }
}
string Packer::getTree (){
    string output;
    vector <bool> binOut;
    char byte = 0;
    Node *root = nodeList.front();

    output += to_string(readBorder);
    printTree(root);

    for (size_t i = 0; i < tmpTreeString.size(); i++){
        if (tmpTreeString[i] == '0'){
            binOut.push_back(0);
            continue;
        }
        if (tmpTreeString[i] == '1'){
            binOut.push_back(1);
            tmpReadedCode = charToBin(tmpTreeString[i+1]);
            binOut.insert(binOut.end(), tmpReadedCode.begin(), tmpReadedCode.end());
            i++;
            continue;
        }
    }

    for (size_t i = 0; i < binOut.size(); i++){
        byte = static_cast<char>(byte | binOut[i] << (7-(i % 8)));
        if ((i % 8 == 7) && (i > 0)){
            output += byte;
            byte = 0;
        }
    }
    if (binOut.size() % 8 > 0){
        output += byte;
    }

    return output;
}
void Packer::setTree (string readed){
    char byte = readed[0];
    vector <bool> binReaded;
    this->readBorder = static_cast<unsigned>(atoi(&byte));
    nodeList.clear();

    for (size_t i = 1; i < readed.size(); i++){
        tmpReadedCode = charToBin(readed[i]);
        binReaded.insert(binReaded.end(), tmpReadedCode.begin(), tmpReadedCode.end());
    }

    Node *root = new Node;
    Node *temp = root;

    for (size_t iter = 1; iter < binReaded.size();iter++) {
        if (temp->parent && temp->leftSon && temp->rightSon){
            temp = temp->parent;
            iter--;
            continue;
        }
        if (!temp->parent && temp->leftSon && temp->rightSon){
            break;
        }
        if (!binReaded[iter]){
            if (!temp->leftSon){
                Node *left = new Node(temp);
                temp->leftSon = left;
                temp = temp->leftSon;
                continue;
            }
            if (!temp->rightSon){
                Node *right = new Node(temp);
                temp->rightSon = right;
                temp = temp->rightSon;
                continue;
            }
        }
        else {
            char byte = 0;
            for (size_t i = 0; i < 8; i++){
                byte = static_cast<char>(byte | binReaded[iter+i+1] << (7-i));
            }
            iter += 8;
            if (!temp->leftSon){
                Node *left = new Node(byte, temp);
                temp->leftSon = left;
                continue;
            }
            else {
                Node *right = new Node(byte, temp);
                temp->rightSon = right;
                temp = temp->parent;
                continue;
            }
        }
    }
    nodeList.push_back(root);
}
void Packer::clearMyself (){
    tmpReadedCode = *new vector <bool>;
    tmpTreeString = "";
    readBorder = 0;
    nodeList = *new list <Node *>;
    symbolsFreq = *new map <char, int>;
    encryptMap = *new map <char, vector <bool> >;
}
