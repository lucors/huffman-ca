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
#define KEY "Komi-san my love"


/// \brief Возвращает 1, если номер символа четный, иначе -1
int alter (char);
/// \brief Возвращает побитовое представление символа
vector <bool> charToBin (char);
/// \brief Преобразует вектор битов в текст представление
string boolVecToStr (vector <bool>);
/// \brief Возвращает строку содержащую побитовое
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


/// \brief Упаковщик файлов на основе алгоритма Хаффмана
class Packer {
protected:
    //Временнные
    /// \brief Сюда временно считывается код очередного символа
    vector <bool> tmpReadedCode;
    /// \brief Сюда записывается дерево при обходе
    string tmpTreeString;

    /// \brief Отвечает за кол-во значимых битов в последнем байте упаков. файла
    unsigned readBorder;
    /// \brief Дерево Хаффмана
    list <Node *> nodeList;
    /// \brief Соответствие между символом и кол-вом его появлений
    map <char, int> symbolsFreq;
    /// \brief Хранит соответствие между символом и его кодом по Хаффману
    map <char, vector <bool> > encryptMap;
public:
    /// \brief Главная ф-ция упаковки
    string pack (string);
    /// \brief  Главная ф-ция распаковки
    string unpack (string);

    /// \brief Ф-ция создания соответствия между символом
    /// и его кодом по дереву Хаффмана
    void fillEncryptMap (Node *);

    /// \brief Сбор информации о дереве прямым обходом
    void printTree(Node *);
    /// \brief Ф-ция возвращает сжатое представление
    /// дерева Хаффмана
    string getTree ();
    /// \brief Ф-ция создает дерево Хаффмана по его сжатому представлению
    void setTree (string);

    void clearMyself ();
};


//
class Coder {
protected:
    string coderStringKey = KEY;
    Packer packer;
public:
    /// \brief Ф-ция чтения файла (Имя файла)
    string readFile (string);
    /// \brief Ф-ция запись в файл (Имя файла, строка записи)
    bool writeFile (string, string);

    /// \brief Ф-ция упаковки и зашифровывания файла (Имя файла)
    string filePackAndEncrypt (string);
    /// \brief Ф-ция расшифровывания и распаковки файла (Имя файла)
    string fileDecryptAndUnpack (string);

    /// \brief Ф-ция зашифровывания файла (Имя файла)
    string fileEncrypt (string);
    /// \brief Ф-ция расшифровывания файла (Имя файла)
    string fileDecrypt (string);

    /// \brief Ф-ция упаковки файла (Имя файла)
    string filePack (string);
    /// \brief Ф-ция распаковки файла (Имя файла)
    string fileUnpack (string);

    /// \brief Ф-ция зашифровки строки (Строка)
    string encrypt (string);
    /// \brief Ф-ция расшифровки строки (Строка)
    string decrypt (string);

    /// \brief Записывает сжатое дерево Хаффмана в файл (Имя файла)
    void writeTreeFile (string);

    /// \brief Читает сжатое дерево Хаффмана из файла .huff (Имя файла)
    void readTreeFile (string);

    /// \brief Упаковывает строку (метод Packer)
    string pack (string);
    /// \brief Распаковывает строку (метод Packer)
    string unpack (string);

    void clearPacker ();
    string killSlashR (string);
};

#endif // FILEHANDLER_H
