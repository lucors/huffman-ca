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


/// \brief ���������� 1, ���� ����� ������� ������, ����� -1
int alter (char);
/// \brief ���������� ��������� ������������� �������
vector <bool> charToBin (char);
/// \brief ����������� ������ ����� � ����� �������������
string boolVecToStr (vector <bool>);
/// \brief ���������� ������ ���������� ���������
/// ������������� �������
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


/// \brief ��������� ������ �� ������ ��������� ��������
class Packer {
protected:
    //����������
    /// \brief ���� �������� ����������� ��� ���������� �������
    vector <bool> tmpReadedCode;
    /// \brief ���� ������������ ������ ��� ������
    string tmpTreeString;

    /// \brief �������� �� ���-�� �������� ����� � ��������� ����� ������. �����
    unsigned readBorder;
    /// \brief ������ ��������
    list <Node *> nodeList;
    /// \brief ������������ ����� �������� � ���-��� ��� ���������
    map <char, int> symbolsFreq;
    /// \brief ������ ������������ ����� �������� � ��� ����� �� ��������
    map <char, vector <bool> > encryptMap;
public:
    /// \brief ������� �-��� ��������
    string pack (string);
    /// \brief  ������� �-��� ����������
    string unpack (string);

    /// \brief �-��� �������� ������������ ����� ��������
    /// � ��� ����� �� ������ ��������
    void fillEncryptMap (Node *);

    /// \brief ���� ���������� � ������ ������ �������
    void printTree(Node *);
    /// \brief �-��� ���������� ������ �������������
    /// ������ ��������
    string getTree ();
    /// \brief �-��� ������� ������ �������� �� ��� ������� �������������
    void setTree (string);

    void clearMyself ();
};


//
class Coder {
protected:
    string coderStringKey = KEY;
    Packer packer;
public:
    /// \brief �-��� ������ ����� (��� �����)
    string readFile (string);
    /// \brief �-��� ������ � ���� (��� �����, ������ ������)
    bool writeFile (string, string);

    /// \brief �-��� �������� � �������������� ����� (��� �����)
    string filePackAndEncrypt (string);
    /// \brief �-��� ��������������� � ���������� ����� (��� �����)
    string fileDecryptAndUnpack (string);

    /// \brief �-��� �������������� ����� (��� �����)
    string fileEncrypt (string);
    /// \brief �-��� ��������������� ����� (��� �����)
    string fileDecrypt (string);

    /// \brief �-��� �������� ����� (��� �����)
    string filePack (string);
    /// \brief �-��� ���������� ����� (��� �����)
    string fileUnpack (string);

    /// \brief �-��� ���������� ������ (������)
    string encrypt (string);
    /// \brief �-��� ����������� ������ (������)
    string decrypt (string);

    /// \brief ���������� ������ ������ �������� � ���� (��� �����)
    void writeTreeFile (string);

    /// \brief ������ ������ ������ �������� �� ����� .huff (��� �����)
    void readTreeFile (string);

    /// \brief ����������� ������ (����� Packer)
    string pack (string);
    /// \brief ������������� ������ (����� Packer)
    string unpack (string);

    void clearPacker ();
    string killSlashR (string);
};

#endif // FILEHANDLER_H
