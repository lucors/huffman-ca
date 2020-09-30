#include <iostream>
#include <fstream>
#include <string>
//STL
#include <vector>
#include <map>
#include <list>

using namespace std;

#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#define KEY "Somebody once told me"


///  Возвращает 1, если номер символа четный, иначе -1
int alter (char);
///  Возвращает побитовое представление символа
vector <bool> charToBin (char);
///  Преобразует вектор битов в текст представление
string boolVecToStr (vector <bool>);
///  Возвращает строку содержащую побитовое
/// представление символа
string printBin (char);


//Tree
struct Node {
    int size;
    char info;
    Node *parent;
    Node *leftSon, *rightSon;

    Node ();
    Node (Node *);
    Node (char, Node *);
    Node (char, int);
    Node (Node *, Node *);
};

struct NodeCompare {
     bool operator() (Node *comp1, Node *comp2){
        return comp1->size < comp2->size;
    }
};


///  Упаковщик файлов на основе алгоритма Хаффмана
class Packer {
protected:
    //Временнные
    ///  Сюда временно считывается код очередного символа
    vector <bool> tmpReadedCode;
    ///  Сюда записывается дерево при обходе
    string tmpTreeString;

    ///  Отвечает за кол-во значимых битов в последнем байте упаков. файла
    unsigned readBorder;
    ///  Дерево Хаффмана
    list <Node *> nodeList;
    ///  Соответствие между символом и кол-вом его появлений
    map <char, int> symbolsFreq;
    ///  Хранит соответствие между символом и его кодом по Хаффману
    map <char, vector <bool> > encryptMap;
public:
    ///  Главная ф-ция упаковки
    string pack (string);
    ///   Главная ф-ция распаковки
    string unpack (string);

    ///  Ф-ция создания соответствия между символом
    /// и его кодом по дереву Хаффмана
    void fillEncryptMap (Node *);

    ///  Сбор информации о дереве прямым обходом
    void printTree(Node *);
    ///  Ф-ция возвращает сжатое представление
    /// дерева Хаффмана
    string getTree ();
    ///  Ф-ция создает дерево Хаффмана по его сжатому представлению
    void setTree (string);

    void clearMyself ();
};



class Coder {
protected:
    string coderStringKey = KEY;
    Packer packer;
public:
    ///  Ф-ция чтения файла (Имя файла)
    string readFile (string);
    ///  Ф-ция запись в файл (Имя файла, строка записи)
    bool writeFile (string, string);

    ///  Ф-ция упаковки и зашифровывания файла (Имя файла)
    string filePackAndEncrypt (string);
    ///  Ф-ция расшифровывания и распаковки файла (Имя файла)
    string fileDecryptAndUnpack (string);

    ///  Ф-ция зашифровывания файла (Имя файла)
    string fileEncrypt (string);
    ///  Ф-ция расшифровывания файла (Имя файла)
    string fileDecrypt (string);

    ///  Ф-ция упаковки файла (Имя файла)
    string filePack (string);
    ///  Ф-ция распаковки файла (Имя файла)
    string fileUnpack (string);

    ///  Ф-ция зашифровки строки (Строка)
    string encrypt (string);
    ///  Ф-ция расшифровки строки (Строка)
    string decrypt (string);

    ///  Записывает сжатое дерево Хаффмана в файл (Имя файла)
    void writeTreeFile (string);

    ///  Читает сжатое дерево Хаффмана из файла .huff (Имя файла)
    void readTreeFile (string);

    ///  Упаковывает строку (метод Packer)
    string pack (string);
    ///  Распаковывает строку (метод Packer)
    string unpack (string);

    void clearPacker ();
    string killSlashR (string);
};



#endif // FILEHANDLER_H
