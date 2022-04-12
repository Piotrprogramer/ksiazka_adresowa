#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdio>

using namespace std;

struct Friends {
    int id, userID;
    string name, lastName, phoneNumber, email, adres;
};

struct User {
    int id=0;
    string userName, password;
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

void addUsersToFile( User newContact) {
    std::ofstream file;
    file.open("uzytkownicy.txt", ios::out | ios::app);
    if( file.good() == true ) {
        file<<newContact.id<<"|";
        file<<newContact.userName<<"|";
        file<<newContact.password<<"|"<<endl;
        file.close();
        cout << "Uzytkownika dodano poprawnie";
    } else std::cout << "Dostep do fileu zostal zabroniony!" << std::endl;
    Sleep(1500);
}

void saveAllUsersToFile(vector<User> allUsers) {
    std::ofstream file;
    file.open("uzytkownicy.txt", ios::out );
    if( file.good() == true ) {
        for(int i=0; i<allUsers.size(); i++){
        file<<allUsers[i].id<<"|";
        file<<allUsers[i].userName<<"|";
        file<<allUsers[i].password<<"|"<<endl;
        }
    file.close();
    } else std::cout << "Dostep do fileu zostal zabroniony!" << std::endl;
    Sleep(1500);
}

void addContactToFile( Friends newContact, string fileName) {
    std::ofstream file;
    file.open(fileName, ios::out | ios::app);
    if( file.good() == true ) {
        file<<newContact.id<<"|";
        file<<newContact.userID<<"|";
        file<<newContact.name<<"|";
        file<<newContact.lastName<<"|";
        file<<newContact.phoneNumber<<"|";
        file<<newContact.email<<"|";
        file<<newContact.adres<<"|"<<endl;
        file.close();
    } else {
        std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
        Sleep(1500);
    }
}

void rewriteOryginalContact(string line, string fileName){
    std::ofstream file;
    file.open(fileName, ios::out | ios::app);
    if( file.good() == true ) {
        file<<line<<endl;
        file.close();
    }
}

void saveAllContact( vector <Friends> contacts) {
    if(contacts.empty()){
        ofstream plik;
        plik.open("ksiazka.txt");
        plik.close();
    }
    else{
    fstream file;
    int contactNumber = 0;
    file.open("ksiazka.txt", ios::in);
    if( file.good() == true ) {
        string line;
        while( getline(file, line)) {
            int infoStart = 0;
            Friends newContact;
            newContact.id = changeToInt(unpacContact(line, infoStart));
            newContact.userID = changeToInt(unpacContact(line, infoStart));
            newContact.name = unpacContact(line,infoStart);
            newContact.lastName = unpacContact(line,infoStart);
            newContact.phoneNumber = unpacContact(line,infoStart);
            newContact.email = unpacContact(line,infoStart);
            newContact.adres = unpacContact(line,infoStart);
            if (newContact.userID == contacts[contactNumber].userID && newContact.id >= contacts[contactNumber].id) {
                addContactToFile(contacts[contactNumber], "ksiazka_temporary.txt");
                contactNumber++;
            }
            else if ( newContact.userID != contacts[0].userID) rewriteOryginalContact(line,"ksiazka_temporary.txt");
        }
        file.close();
        remove("ksiazka.txt");
        rename("ksiazka_temporary.txt", "ksiazka.txt");
    }
    }
}

void loadDataFromFile( vector<Friends> &friends, int userId, string savedFile) {
    fstream file;
    file.open(savedFile, ios::in );
    if(file.good() == true) {
        string line;
        while( getline(file, line)) {
            int infoStart = 0;
            Friends newContact;
            newContact.id = changeToInt(unpacContact(line, infoStart));
            newContact.userID = changeToInt(unpacContact(line, infoStart));
            newContact.name = unpacContact(line,infoStart);
            newContact.lastName = unpacContact(line,infoStart);
            newContact.phoneNumber = unpacContact(line,infoStart);
            newContact.email = unpacContact(line,infoStart);
            newContact.adres = unpacContact(line,infoStart);
            if (userId == newContact.userID) friends.push_back(newContact);
        }
        file.close();
    }
}

void loadUserFromFile( vector <User> &users, string savedFile) {
    fstream file;
    file.open(savedFile, ios::in );
    if(file.good() == true) {
        string line;
        while( getline(file, line)) {
            int infoStart = 0;
            User newContact;
            newContact.id = changeToInt(unpacContact(line, infoStart));
            newContact.userName = unpacContact(line,infoStart);
            newContact.password = unpacContact(line,infoStart);
            users.push_back(newContact);
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

int createUserId(string savedFile){
int newID=1;
string test;
    fstream file;
    file.open(savedFile, ios::in );
    if(file.good() == true) {
        string line;
        while( getline(file, line)){
            int infoStart = 0;
            if (line.length()>0)newID = changeToInt(unpacContact(line, infoStart))+1;
        }
        file.close();
    }
    return newID;
}

void addAddressees(vector <Friends> &friends, int userID) {
    string name, lastName;
    cout << "\nPodaj imie: ";
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
    newContact.id = createUserId("ksiazka.txt");
    newContact.userID = userID;
    friends.push_back(newContact);
    addContactToFile(newContact, "ksiazka.txt");
}

void addUser(vector <User> &users) {
    string userName, password;
    User newUser;
    cout << "Nazwe uzytkownika: ";
    cin >> userName ;


    for(int i=0; i<users.size(); ) {
        if(userName == users[i].userName) {
            cout << "Taki uzytkownik juz istnieje "<<endl;
            cout << "Podaj inna nazwe uzytkownika: "<<endl;
            cin >> userName;
            i = 0;
        } else i++;
    }
    cout <<"Podaj haslo: ";
    cin >> password;
    newUser.userName = userName;
    newUser.password = password;
    if (users.empty()) newUser.id = 1;
    else newUser.id = users[users.size()-1].id+1;
    users.push_back(newUser);
    addUsersToFile(newUser);
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

            token = getch();
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

User userLogin(vector <User> users, User user){
    string userName, password;
    cout<<"Podaj nazwe uzytkownika: ";
    cin >> userName;
        for(int i=0; i<users.size(); i++) {
        if(userName == users[i].userName ) {
            cout<<"Podaj haslo: ";
            cin >>password;
            if (password == users[i].password ) return users[i];
            else {for(int j=0; j<2; j++){
                cout << "Podales nieprawidlowe haslo, zostalo prob "<<2-j<<"\nSprobuj ponownie: ";
                cin >>password;
                if (password == users[i].password )  return users[i];
                }
                cout<< "Niprawidlowe haslo, logowanie nie powiodlo sie";
                Sleep(3000);
                return user;
            }
        }
    }
    cout<< "Podany uzytkownik nie istnieje";
    Sleep(3000);
    return user;
}

User userLogInMenu(){
    User user;
    vector <User> users;
    loadUserFromFile(users, "uzytkownicy.txt");
    char token;
    while(user.id == 0){
        system("cls");
        cout<< "1. Logowanie " <<endl;
        cout<< "2. Rejestracja" <<endl;
        cout<< "9. Zamknij program" <<endl<<endl;
        token = ' ';
        while (token != '1' && token != '2' && token != '9'){
            token = getch();
            }
        switch(token){
        case '1':{
            user = userLogin(users, user);
            break;
            }
        case '2':{
            addUser(users);
            break;
            }
        case '9':{exit(0);}
        }
        }
        return user;
}

void changePassword(User &user){
    vector <User> users;
    loadUserFromFile(users, "uzytkownicy.txt");
    string password;
    cout<< "Podaj stare haslo: ";
    cin >> password;
    for(int i=0; i<2; i++){
    if (password == user.password) {
        cout<<"Podaj nowe haslo: ";
        cin >> password;
        user.password = password;
        for(int j=0; j<users.size(); j++){
            if(users[i].userName == user.userName){
            users[i].password = password;
            break;
            }
        }
        saveAllUsersToFile(users);
        break;
        }
    else{
        cout<<"Haslo niepoprawne, zostalo prob: "<<2-i<<endl;
        cout<<"Podaj stare haslo: ";
        cin>>password;
        }
    }
}

int main() {
    char token;
    User user = userLogInMenu();
    vector <Friends> addressees;
    loadDataFromFile(addressees,user.id, "ksiazka.txt");

    while(1) {
        system("cls");
        cout<< "Zalogowany uzytkownik: "<< user.userName <<"  haslo: "<<user.password<<endl;
        cout<< "1. Dodaj adresata" <<endl;
        cout<< "2. Wyszukaj po imieniu" <<endl;
        cout<< "3. Wyszukaj po nazwisku" <<endl;
        cout<< "4. Wyœwietl wszystkich adresatow" <<endl;
        cout<< "5. Usun adresata" <<endl;
        cout<< "6. Edytuj adresata" <<endl;
        cout<< "7. Zmien haslo" <<endl;
        cout<< "9. Wyloguj sie" <<endl;

        cout<< "Twoj wybor: ";
        token = getch();
        cout<<token<<endl;
        switch (token) {
        case '1': {
            addAddressees(addressees, user.id);
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
        case '7': {
            changePassword(user);
            break;
        }
        case '9': {
            user = userLogInMenu();
            addressees.clear();
            loadDataFromFile(addressees,user.id, "ksiazka.txt");
            break;
        }
        }
    }
    return 0;
}
