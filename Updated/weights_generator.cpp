#include <fstream>
#include <iostream>
using namespace std;

int main() {
    srand(time(0));
    int inp, oup, l1, l2;

    ifstream fileIn;
    fileIn.open("network-size.txt");
    fileIn >> inp >> oup >> l1 >> l2;
    fileIn.close();

    ofstream file;
    file.open("weights.txt");

    cout << "Note: writing -32 will randomize all weights between -1.00 to 1.00"
         << endl;

    cout << "What value you want to initialize all weights to. ";
    double initialize;
    cin >> initialize;
    double num;
    if (initialize == -32) {
        for (int i = 0; i < oup; i++) {
            num = (double)(rand() % 101) / 100;
            file << num << " ";
        }
        file << endl;
        for (int i = 0; i < l2; i++) {
            num = (double)(rand() % 101) / 100;
            file << num << " ";
        }
        file << endl;
        for (int i = 0; i < l1; i++) {
            num = (double)(rand() % 101) / 100;
            file << num << " ";
        }
        file << endl;
        for (int i = 0; i < l2; i++) {
            for (int j = 0; j < oup; j++) {
                num = (double)(rand() % 101) / 100;
                file << num << " ";
            }
            file << endl;
        }
        for (int i = 0; i < l1; i++) {
            for (int j = 0; j < l2; j++) {
                num = (double)(rand() % 101) / 100;
                file << num << " ";
            }
            file << endl;
        }
        for (int i = 0; i < inp; i++) {
            for (int j = 0; j < l1; j++) {
                num = (double)(rand() % 101) / 100;
                file << num << " ";
            }
            file << endl;
        }
    }
}