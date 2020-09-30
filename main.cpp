#include <iostream>
#include <fstream>
#include <string>
//STL
#include <vector>
#include <map>
#include <list>
//Locale
#include "filehandler.h"

using namespace std;

int main (int argc, char* argv[]){
    Coder coder;
    string command, inputFilename, outputFilename;
    string tmpFileContent;

    if (argc > 1){
            command = argv[1];
            command = command.substr(1, command.size());
            if (argc == 4){
                inputFilename = argv[2];
                outputFilename = argv[3];
                if (command == "pe"){
                    tmpFileContent = coder.filePackAndEncrypt(inputFilename);
                    coder.writeTreeFile(outputFilename);
                    coder.writeFile(outputFilename, tmpFileContent);
                    return  0;
                }
                if (command == "du"){
                    coder.readTreeFile(inputFilename);
                    tmpFileContent = coder.fileDecryptAndUnpack(inputFilename);
                    coder.writeFile(outputFilename, tmpFileContent);
        //            coder.clearPacker();
                    return  0;
                }
            }
            else {
                if (command == "help"){
                    cout <<
                            "\t Arg0:  \n"
                            "\t\t -pe \"Pack and Encrypt file\"\n"
                            "\t\t -du \"Decrypt and Unpack file\"\n"
                            "\t Arg1:  \n"
                            "\t\t \"Input filename\"\n"
                            "\t Arg2:  \n"
                            "\t\t \"Output filename\"\n";
                    return  0;
                }
                cout << "Unknown command" << endl;
            }
    }
    else {
        cout << "No arguments to process" << endl;
    }

    return  0;
}
