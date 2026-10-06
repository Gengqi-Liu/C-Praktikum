#include <iostream>
#include <limits>
using namespace std;

string wortEinlesen(){
    string eingabe;
    cout << "Bitte ein Wort eingeben, das überprüft werden soll: ";
    cin >> eingabe;
    return eingabe;
}

bool palindrome(string wort){
    int n = wort.size();

    for(int i = 0; i <= n/2; i++){
        if(wort[i] != wort[n-1-i]){return false;}
    }

    return true;
}

int main(){
    string wort = wortEinlesen();

    if(palindrome(wort)){
        cout << wort << " ist ein Palindrom." << endl;
    } else {
        cout << wort << " ist kein Palindrom." << endl;
    }

    return 0;
}
