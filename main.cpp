#include <iostream>
#include <tchar.h>
#include <cmath>
#include <cctype>
using namespace std;
int eller(int p, int q){return (p - 1)*(q - 1);}
int d(int _eller){
    for (int i = 2; i < 1000; i ++){
        if (_eller % i != 0){return i;}
    }
    return 0;
}
int e(int _eller){
    int num;
    for (int i = 0; i < 1000; i ++){
        num = d(_eller) * i;
        if (num % _eller == 1) return i;
    }
    return 0;
}
int Crypto(int _e, int _n, char _chr){
    int KolVhod = 0;int ne5;
    int count = 1;
    int Chislo = 1;
    if (int(_chr) - 96 > 1) {
        while (pow((int(_chr) - 96), Chislo) < _n) {
            Chislo++;
        }
    }
    KolVhod = _e / Chislo; //cout << KolVhod << endl;
    ne5 = _e % Chislo; //cout << ne5 << endl;
    int ChrStp = 0;// cout << ChrStp << endl;
    for (int i = 0; i < KolVhod; i ++) {
        ChrStp = pow((int(_chr) - 96), Chislo);
        count *= ChrStp % _n;
        count %= _n;
    }
    ChrStp = pow((int(_chr) - 96), ne5);
    count *= ChrStp % _n;
    return count % _n;
}
void encrypting(int _p, int _q, char* _CryptoWord, int storage[30], int len) {
    int n = _p * _q;
    int _eller = eller(_p, _q);
    int eNat;
    eNat = e(_eller);
    for (int i = 0; i < strlen(_CryptoWord); i++) {
        cout << "'" << _CryptoWord[i] << "' - ";
        cout << Crypto(eNat, n, _CryptoWord[i]) << endl;
        storage[i] = Crypto(eNat, n, _CryptoWord[i]);
    }
}


bool TrueWord(char* _word){
    int _len = strlen(_word);
    for (int i = 0; i < _len; i++){
        if (int(_word[i]) > 122 || int(_word[i]) < 97 || _len == 0)
            return false;
        }
    return true;
}


int main() {
    int num = 0, len = 0, p, q;
    int* storage = new int[30];
    char word[30] = "";
    for (; num != 228;) {
        cout << "Menu" <<endl;
        cout << "1 - Input word to enc"<< endl;
        cout << "2 - Begin enc"<< endl;
        cout << "3 - DeEncrypt"<< endl;
        cout << "4 - Exit"<< endl;
        cout << endl;
        cout << "Inp num of operation (1-4)" << endl;
        while (!(cin >> num) || cin.get() != '\n' || isdigit(num) ) {
            cout << "Wrong operation. Enter again !\n";
            cin.clear();
            cin.sync();
            cout << "Enter number of operation : ";
        }
        switch (num) {
            case 1:{
                cout<<"Enter word : ";
                while(!(cin >> word) || cin.get() != '\n' || not TrueWord(word))
                {
                    cout<<"Wrong word. Enter again !\n";
                    cin.clear();
                    cin.sync();
                    cout<<"Enter word : ";
                }
            }
            len = strlen(word);break;
            case 2: {
                cout << "p:";
                while (!(cin >> p) || p < 0 || isdigit(p)) {
                    cout << "Wrong p. Enter again !\n";
                    cin.clear();
                    cin.sync();
                    cout << "Enter p : ";
                }
                cout << endl << "q:";
                while (!(cin >> q) || q < 0 || isdigit(q)) {
                    cout << "Wrong q. Enter again !\n";
                    cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
                    cin.sync();//Удалим данные из буффера
                    cout << "Enter q : ";
                }
                if (strcmp(" ", word) != 1) encrypting(p, q, word, storage, len);
                cout << "===================================================" << endl;
                cout << "Encrypted word: ";
                for (int i = 0; i < strlen(word); i++) cout << "[" << storage[i] << "]";
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "Enter p to decrypt:";
                while (!(cin >> p) || p < 0 || isdigit(p)) {
                    cout << "Wrong p. Enter again !\n";
                    cin.clear();
                    cin.sync();
                    cout << "Enter p : ";
                }
                cout << endl << "Enter q to decrypt:";
                while (!(cin >> q) || q < 0 || isdigit(q)) {
                    cout << "Wrong q. Enter again !\n";
                    cin.clear();
                    cin.sync();
                    cout << "Enter q : ";
                }
                int tmpnum = 0;
                cout << "Decrypted word: " << endl << "[";
                for (int i = 0; i < strlen(word); i++) {
                    tmpnum = pow(storage[i], d(eller(p, q)));
                    tmpnum %= p * q;
                    cout << char(tmpnum + 96);
                }
                cout << "]" << endl;
                break;
            }
            case 228:
                break;
            default:
                cout << "Wrong operation. Enter again !\n" << endl;break;
        }
    }
}
