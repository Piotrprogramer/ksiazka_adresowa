#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

struct Friends {
    int id;
    string name, lastName, phoneNumber, email, adres;
};

int changeToInt(string z1) {
    int x = std::stoi(z1);
    return x;
}

bool checkId(vector<Friends> friends, int &personID) {
    bool founded = false;
    for(int i=0; i< friends.size(); i++) {
        if( friends[i].id == personID ) {
            personID = i;
            founded = true;
            break;
        }
    }
    return founded;
}

string unpacContact(string personInfo, int &startPoint) {
    string info = "";
    char sign;

    for(int i =startPoint; i<personInfo.length(); i++) {
        sign = personInfo[i];
        if (sign == '|') {
            startPoint = ++i;
            break;
        } else {
            info+=sign;
        }
    }
    return info;
}

void saveToFile( Friends newContact) {
    std::ofstream file;
    file.open("ksiazka.txt", ios::out | ios::app);
    if( file.good() == true ) {
        file<<newContact.id<<"|";
        file<<newContact.name<<"|";
        file<<newContact.lastName<<"|";
        file<<newContact.phoneNumber<<"|";
        file<<newContact.email<<"|";
        file<<newContact.adres<<"|"<<endl;
        file.close();
        cout << "Osobe dodano poprawnie";
    } else std::cout << "Dostep do fileu zostal zabroniony!" << std::endl;
    Sleep(1500);
}

void saveAllContact( vector <Friends> contacts) {
    std::ofstream file;
    file.open("ksiazka.txt", ios::out);
    if( file.good() == true ) {
        for(int i=0; i<contacts.size(); i++) {
            file<<contacts[i].id<<"|";
            file<<contacts[i].name<<"|";
            file<<contacts[i].lastName<<"|";
            file<<contacts[i].phoneNumber<<"|";
            file<<contacts[i].email<<"|";
            file<<contacts[i].adres<<"|"<<endl;
        }
        file.close();
    } else {
        std::cout << "Nie udalo sie wprowadzic zmian" << std::endl;
        Sleep(2000);
    }
}

void loadDataFromFile( vector<Friends> &friends) {
    fstream file;
    file.open("ksiazka.txt", ios::in );
    if(file.good() == true) {
        string line;
        while( getline(file, line)) {
            int infoStart = 0;
            Friends newContact;
            newContact.id = changeToInt(unpacContact(line, infoStart));
            newContact.name = unpacContact(line,infoStart);
            newContact.lastName = unpacContact(line,infoStart);
            newContact.phoneNumber = unpacContact(line,infoStart);
            newContact.email = unpacContact(line,infoStart);
            newContact.adres = unpacContact(line,infoStart);
            friends.push_back(newContact);
        }
        file.close();
    }
}

void deleteContact ( vector <Friends> & friends) {
    vector <Friends>::iterator it;
    int idContactToErase = 0;
    bool isIDcorrect = false;
    char choice ;
    cout<<"Podaj ID adresata: ";
    cin>> idContactToErase;
    isIDcorrect = checkId(friends, idContactToErase);

    if(isIDcorrect) {
        cout<<endl<<"Aby potwierdzic usuwanie wcisnij 't'";
        choice = getch();
        if(choice == 't') {
            it = friends.begin() + idContactToErase;
            friends.erase (it);
            saveAllContact(friends);
            cout<<endl<<"Adresat zostal usuniety."<<endl;
            Sleep(1500);
        } else {
            cout<<endl<<"Usuwanie zostalo przerwane."<<endl;
            Sleep(1500);
        }
    } else {
        cout<<"Osoba o podanym ID nie istnieje.";
        Sleep(1500);
    }
    std::cin.clear();
}

void addAddressees(vector <Friends> &friends) {
    string name, lastName;
    cout << "Podaj imie: ";
    cin >> name ;
    cout << "Podaj nazwisko: ";
    cin >> lastName;
    Friends newContact;

    for(int i=0; i<friends.size(); i++) {
        if(name == friends[i].name && lastName == friends[i].lastName) {
            cout << "Taka osoba jest juz zapisana. "<<endl;
            cout << "Podaj jeszcze raz imie: "<<endl;
            cin >> name;
            cout << "Podaj jeszcze raz nazwisko: "<<endl;
            cin >> lastName;
            i = 0;
        } else i++;
    }
    newContact.name = name;
    newContact.lastName = lastName;

    cout << "Podaj nr telefonu: ";
    cin >>  newContact.phoneNumber;
    cout << "Podaj email: ";
    cin >>  newContact.email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, newContact.adres );
    newContact.name = name;
    newContact.lastName = lastName;
    if (friends.empty()) newContact.id = 1;
    else newContact.id = friends[friends.size()-1].id+1;
    friends.push_back(newContact);
    saveToFile(newContact);
}

void displayPerson(Friends personInfo) {
    cout<<endl<<"ID :" <<personInfo.id<<endl;
    cout<< "Imie: " << personInfo.name <<endl;
    cout<< "Nazwisko: " << personInfo.lastName <<endl;
    cout<< "Nr telefonu: " << personInfo.phoneNumber <<endl;
    cout<< "email: " << personInfo.email <<endl;
    cout<< "adres: " << personInfo.adres <<endl;
}

void displayAllFriend(vector<Friends> friends) {
    for(int i = 0; i<friends.size(); i++) {
        cout<<endl<<"ID :"<<friends[i].id <<endl;
        cout<<"Imie: " <<friends[i].name <<endl;
        cout<<"Nazwisko: "<<friends[i].lastName <<endl;
        cout<<"Nr telefonu: " <<friends[i].phoneNumber <<endl;
        cout<<"email: "<<friends[i].email <<endl;
        cout<<"adres: "<<friends[i].adres <<endl;
    }
    system("pause");
}

void findFriendByName(vector <Friends> friends) {
    string name = "";
    bool znaleziono = false;

    cout<<endl<<"Podaj imie: ";
    cin >> name;

    for(int i=0; i<friends.size(); i++) {
        if(friends[i].name == name) {
            displayPerson(friends[i]);
            znaleziono = true;
        }
    }
    if(znaleziono==false) cout <<"Osoba o imieniu '"<<name<<"' nie znajduje sie w ksiazce telefonicznej."<<endl;
    system("pause");
}

void findFriendByLastname(vector <Friends> friends) {
    string lastName = "";
    bool znaleziono = false;
    cout<<endl<<"Podaj nazwisko: ";
    cin >> lastName;

    for(int i=0; i<friends.size(); i++) {
        if(friends[i].lastName == lastName) {
            displayPerson(friends[i]);
            znaleziono = true;
        }
    }
    if(znaleziono==false) cout <<"Osoba o nazwisku '"<<lastName<<"' nie znajduje sie w ksiazce telefonicznej."<<endl;
    system("pause");
}

void editPersonalData(vector<Friends> &friends) {
    int idContactToEdit;
    bool isIDcorrect;
    cout<<"Podaj ID adresata: ";
    cin>> idContactToEdit;
    isIDcorrect = checkId(friends, idContactToEdit);
    if (isIDcorrect) {

        char token;
        while(token != '9'){
            system("cls");
            displayPerson(friends[idContactToEdit]);
            cout<<"\n";
            cout<< "1. Edytuj imie. " <<endl;
            cout<< "2. Edytuj nazwisko. " << endl;
            cout<< "3. Edytuj nr telefonu. " << endl;
            cout<< "4. Edytuj email. " << endl;
            cout<< "5. Edytuj adres. " <<endl;
            cout<< "9. Zakoncz edytowanie. " <<endl;

            cin>>token;
            if( token=='1' ) {
                cout<<"Podaj nowe imie: ";
                cin >> friends[idContactToEdit].name;
                saveAllContact(friends);
            }
            else if(token == '2'){
                cout<<"Podaj nowe nazwisko: ";
                cin>>friends[idContactToEdit].lastName;
                saveAllContact(friends);
            }
            else if(token == '3'){
                cout<<"Podaj nowy nr telefonu: ";
                cin>>friends[idContactToEdit].phoneNumber;
                saveAllContact(friends);
            }
            else if(token == '4'){
                cout<<"Podaj nowy email: ";
                cin>>friends[idContactToEdit].email;
                saveAllContact(friends);
            }
            else if (token == '5'){
                cout<<"Podaj nowy adres: ";
                cin.sync();
                getline(cin, friends[idContactToEdit].adres);
                saveAllContact(friends);
            }
        }
    } else {
        cout << "Osoba o podanym ID nie istnieje.";
        Sleep(1500);
    }
}

int main() {
    char token;
    vector <Friends> addressees;
    loadDataFromFile(addressees);

    while(1) {
        system("cls");
        cout<< "1. Dodaj adresata" <<endl;
        cout<< "2. Wyszukaj po imieniu" <<endl;
        cout<< "3. Wyszukaj po nazwisku" <<endl;
        cout<< "4. Wyœwietl wszystkich adresatow" <<endl;
        cout<< "5. Usun adresata" <<endl;
        cout<< "6. Edytuj adresata" <<endl;
        cout<< "9. Zakoncz program" <<endl;
        cout<< "Twoj wybor: ";
        cin >> token;

        switch (token) {
        case '1': {
            addAddressees(addressees);
            break;
        }
        case '2': {
            findFriendByName(addressees);
            break;
        }
        case '3': {
            findFriendByLastname(addressees);
            break;
        }
        case '4': {
            displayAllFriend(addressees);
            break;
        }
        case '5': {

            deleteContact(addressees);
            break;
        }
        case '6': {
            editPersonalData(addressees);
            break;
        }
        case '9': {
            exit(0);
        }
        }
    }
    return 0;
}
