//Codificare Hamming la Sursa
//Limbaj C++
#include <iostream> // Includem toate bibliotecile necesare, pentru input/output si 
#include <cmath>    // calcularea puterilor lui 2 mai usor
using namespace std;
bool B2[5], MesajFinal[200], MesajUtil[200], MatriceHamming[20][400];  // Declaram Vectorii de care ne vom folosi: B2 - vector folosit pentru
//transformarea in B2 a numerelor, MesajFinal - mes transmis dupa c. Hamming, MesajUtil - mes pe care il codificam, MatriceHamming - matricea necesara codificarii
void transformareDinB10inB2(int numar, int pas){ // Functia necesara transformarii fiecarui numar reprezentat in Matricea Hamming in B2
    int cat = numar / 2;
    if(cat == 0) // Functia recursiva se opreste cand catul e 0, caci atunci avem toti bitii necesari reprezentarii in B2
        B2[pas] = numar % 2;  //Tinem minte valoare fiecarui Bit, prin calcularea restului impartirii la Baza
    else{
        transformareDinB10inB2(numar / 2, pas - 1); // Apelam functia pana cand ajungem la ultima cifra binara
        B2[pas] = numar % 2;  // Dupa ce am aflat Bitul cel mai important, ii aflam si pe restul, pana la cel mai nesemnificativ
    }
}
void aflareBitiParitate(int doilaputere, int lungimeMesajFinal, int BitiParitate){ // Functie pt aflarea Bitilor de paritate
   // Cautam Linia in care Bitul sa nu fie nul, astfel incat sa putem afla Bitul de paritate din relatia rezultata
    int poz = 1;        
    while(poz <= BitiParitate){
        if(MatriceHamming[poz][doilaputere] == 1){ // Daca elementul de pe aceeasi coloana cu bitul de paritate nu e nul, putem afla bitul de paritate
            int suma = 0; // "suma" tine cont de numarul total de biti de 1
            for(int i = 1; i <= lungimeMesajFinal; ++i)
                suma += MatriceHamming[poz][i] * MesajFinal[i];
            if(suma % 2 == 1)// Astfel, facand suma modulo 2, vom afla daca bitul de paritate va fi 1 sau 0. Noi vrem ca paritatea sirurilor sa fie para
                MesajFinal[doilaputere] = 1;
            return; // Daca gasim Bitul, returnam nimic, pt a nu continua cautarea
        }
        poz++; // Daca nu am aflat inca bitul, ne continuam cautarea pe linia urmatoare
    }
}
int main(){
    cout << "Introduceti lungimea mesajului pe care doriti sa-l codificati Hamming:\n";
    int lungimeMesaj;  // Declaram si citim lungimea mesajului initial
    cin >> lungimeMesaj;
    cout << "Introduceti mesajul de lungimea " << lungimeMesaj << "(cu spatiu intre fiecare bit):\n";
    for(int i = 1; i <= lungimeMesaj; ++i)
        cin >> MesajUtil[i];  // Citim mesajul pe care vrem sa-l transmitem
    int contorBiti = 1;
    for(int i = 1; pow(2, i) < lungimeMesaj + i + 1; ++i)
        contorBiti++;  // Aflam numarul de biti de paritate minimi necesari pt codificare
    int BitiParitate = contorBiti;
    int lungimeMesajFinal = lungimeMesaj + BitiParitate; // Aflam lungimea mesajului final, pe care il vom transmite cu tot cu bitii de paritate
    for(int i = 1; i <= lungimeMesajFinal; ++i){
        transformareDinB10inB2(i, BitiParitate);  // Transformam in B2 toate numerele de la 1 la ultimul nr reprezentat in binar in matricea hamming
        for(int j = BitiParitate; j >= 1; --j)
            MatriceHamming[j][i] = B2[BitiParitate -(BitiParitate - j)];  // Trecem numerele aflate in B2 in matricea Hamming
    }
    int j = 0, putere = 0; // Declaram variabilele necesare pt aflarea pozitiilor bitilor de paritate in mes final
    for(int i = 1; i <= lungimeMesajFinal; ++i){
        if(i == pow(2, putere)){  // Daca i == o putere a lui doi, mai mica decat lungimea mes final, vom nota acea bit cu 0, pt ca nu ne va afecta calculele ulterioare
            MesajFinal[i] = 0;
            putere++;  // Crestem puterea pt a afla si restul pozitiilor ale bitilor de paritate
        }
        else
            MesajFinal[i] = MesajUtil[++j]; // Daca pozitia pe care suntem acum, nu apartine unui bit de paritate, copiem bitii mesajului initial
    }
    for(int i = 0; i <= BitiParitate - 1; ++i)  // Calculam valoare bitilor de paritate, prin functia definita mai devreme
        aflareBitiParitate(pow(2, i), lungimeMesajFinal, BitiParitate);
    cout << "Mesajul codificat Hamming:\n";
    for(int i = 1; i <= lungimeMesajFinal; ++i) // Afisam mesajul pe care vrem sa-l transmitem, codificat Hamming
        cout << MesajFinal[i] << " ";
    return 0;
} 
/*
+Logica Programului si Formule de calcul folosite
    -Formula H * v transpus = 0:
        H = MatriceHamming[][]
        v transpus = MesajFinal[]
    -Dupa citirea vectorilor, aflam matricea dimensiunile matricei hamming prin formula:
        2 ^ r >= m + r + 1, unde:
        m - lungimea mesajului = lungimeMesaj, pe care o citim la inceput
        r - numar biti paritate, aflata printr-un for care se opreste cand conditia este satisfacuta
    -Dupa aflarea dimensiunilor matricei, o definim.
        Stim ca numarul de coloane este dat de m + r, adica lungimea mes final, iar numarul de linii = r
        Astfel, fiecare coloana va contine, in binar, numarul coloanei respective
    -Dupa definirea matricei, alcatuim v transpus, prin adaugarea la mesajul initial, 
        bitii de paritate pe pozitiile care sunt puteri ale lui 2.
    -Pasul final consta in aflarea bitilor de paritate, pe care ii calculam inmultind
         linia Matricei Hamming cu coloana lui v transpus
    -Finalul, afisarea mesajului codificat Hamming
+Bibliografie
    -PBInfo (Matrice, si vectori)
    -Youtube.com/ZeceLaExamene
    -Suport de Curs BTI
*/