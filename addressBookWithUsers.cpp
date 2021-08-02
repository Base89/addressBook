#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

struct User
{
    int id;
    string name, password;
};
void openFileUsers(vector <User> &users);
void checkFileUsers(vector <User> &users);
void saveFileUsers(vector <User> &users);
void registration(vector <User> &users);
int log(vector <User> &users);
void changePassword(vector <User> &users, int idLoginUser);

struct Addressee
{
    int id, idUser;
    string name, surname, telephoneNumber, email, address;
};
int getLastIdAdd();
void openFileAdd(vector <Addressee> &addressees, int &idLoginUser);
void checkFileAdd(vector <Addressee> &addressees, int &idLoginUser);
void saveFileAdd(vector <Addressee> &addressees, Addressee modifiedAddresse);
void saveFileAdd(vector <Addressee> &addressees, int idDeletedAddressee);
void addNewAddressee (vector <Addressee> &addressees, int idLoginUser);
void searchByName(vector <Addressee> &addressees);
void searchBySurname(vector <Addressee> &addressees);
void deleteAddressee(vector <Addressee> &addressees);
void editAddressee(vector <Addressee> &addressees);
void displayAddressees(vector <Addressee> &addressees);

int main()
{
    int idLoginUser = 0;
    vector <User> users;
    vector <Addressee> addressees;
    checkFileUsers(users);
    char numberMenu;

    while(1)
    {
        if (idLoginUser == 0)
        {
            system ("cls");
            cout << "1. Zarejestruj" << endl;
            cout << "2. Zaloguj" << endl;
            cout << "9. Zakoncz" << endl;
            cin >> numberMenu;

            if (numberMenu == '1')
            {
                registration(users);
            }
            else if (numberMenu == '2')
            {
                idLoginUser = log(users);
                checkFileAdd(addressees, idLoginUser);
            }
            else if (numberMenu == '9')
            {
                exit(0);
            }
        }
        else
        {
            system ("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> numberMenu;

            switch (numberMenu)
            {
            case '1':
                addNewAddressee(addressees, idLoginUser);
                break;
            case '2':
                searchByName(addressees);
                break;
            case '3':
                searchBySurname(addressees);
                break;
            case '4':
                displayAddressees(addressees);
                break;
            case '5':
                deleteAddressee(addressees);
                break;
            case '6':
                editAddressee(addressees);
                break;
            case '7':
                changePassword(users, idLoginUser);
                break;
            case '8':
                idLoginUser = 0;
                addressees.clear();
                break;
            case '9':
                exit(0);
            }
        }
    }
    return 0;
}

void openFileUsers(vector <User> &users)
{
    fstream usersList;
    string lineInFile;
    int dataNumber = 1;
    User newUser;

    usersList.open("lista_uzytkownikow.txt", ios::in);

    while (getline(usersList, lineInFile, '|'))
    {
        switch (dataNumber)
        {
        case 1:
            newUser.id = atoi(lineInFile.c_str());
            break;
        case 2:
            newUser.name = lineInFile;
            break;
        case 3:
            newUser.password = lineInFile;
            break;
        }
        if (dataNumber >= 3)
        {
            users.push_back(newUser);
            dataNumber = 1;
        }
        else
        {
            dataNumber++;
        }
    }
}

void checkFileUsers(vector <User> &users)
{
    fstream usersList;
    usersList.open ("lista_uzytkownikow.txt", ios::in);

    if (usersList.good() == false)
    {
        cout << "Nie mozna otworzyc listy uzytkownikow" << endl;
        Sleep(1000);
        return;
    }
    else if(usersList.good() == true)
    {
        openFileUsers(users);
    }
    usersList.close();
}

void saveFileUsers(vector <User> &users)
{
    fstream usersList;
    usersList.open("lista_uzytkownikow.txt", ios::out);

    for (int i = 0, end = users.size(); i < end; i++)
    {
        usersList << users[i].id << '|' << users[i].name << '|' << users[i].password << '|' << endl;
    }
    usersList.close();
    cout << "Zapisano dane" << endl;
    Sleep(1000);
}

void registration(vector <User> &users)
{
    string name, password;
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> name;
    int i = 0;
    int end = users.size();
    while (i < end)
    {
        if (users[i].name == name)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> name;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: " << endl;
    cin >> password;
    int lastID = users.empty() ? 0 : users.back().id;

    User newUser;
    newUser.name = name;
    newUser.password = password;
    newUser.id = lastID + 1;
    cout << "Konto zalozone" << endl;
    Sleep(1000);

    users.push_back(newUser);

    fstream usersList;
    usersList.open("lista_uzytkownikow.txt", ios::out | ios::app);
    usersList << lastID + 1 << '|' << name << '|' << password << '|' << endl;
    usersList.close();
    saveFileUsers(users);

    cout << "Dodano uzytkownika" << endl;
    Sleep(1000);
}

int log(vector <User> &users)
{
    string name, password;
    cout << "Podaj nazwe: " << endl;
    cin >> name;
    int i = 0;
    int end = users.size();
    while (i < end)
    {
        if (users[i].name == name)
        {
            for (int attemps = 0; attemps < 3; attemps++)
            {
                cout << "Podaj haslo: " << endl;
                cin >> password;
                if (users[i].password == password)
                {
                    cout << "Zalogowales sie!" << endl;
                    Sleep(1000);
                    return users[i].id;
                }
                cout << "Pozostalo prob " << 3 - (attemps + 1) << ": " << endl;
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sek..." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Uzytkownik o podanym loginie nie istnieje" << endl;
    Sleep(1000);
    return 0;
}

int getLastIdAdd()
{
    int lastIdAddressee;
    fstream addressBook;
    string lineInFile;
    int dataNumber = 1;

    addressBook.open("ksiazka_adresowa.txt", ios::in);

    while (getline(addressBook, lineInFile, '|'))
    {
        if (dataNumber == 1 && addressBook.eof() == false)
        {
            lastIdAddressee = atoi(lineInFile.c_str());
            dataNumber++;
        }
        else if (dataNumber >= 7)
        {
            dataNumber = 1;
        }
        else
        {
            dataNumber++;
        }
    }
    addressBook.close();
    return lastIdAddressee;
}

void changePassword(vector <User> &users, int idLoginUser)
{
    string password;
    cout << "Podaj nowe haslo: " << endl;
    cin >> password;
    for (int i = 0, end = users.size(); i < end; i++)
    {
        if (users[i].id == idLoginUser)
        {
            users[i].password = password;
            saveFileUsers(users);
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1000);
        }
    }
}
void openFileAdd(vector <Addressee> &addressees, int &idLoginUser)
{
    fstream addressBook;
    string lineInFile;
    int dataNumber = 1;
    Addressee newAddressee;

    addressBook.open("ksiazka_adresowa.txt", ios::in);

    while (getline(addressBook, lineInFile, '|'))
    {
        switch (dataNumber)
        {
        case 1:
            newAddressee.id = atoi(lineInFile.c_str());
            break;
        case 2:
            newAddressee.idUser = atoi(lineInFile.c_str());
            break;
        case 3:
            newAddressee.name = lineInFile;
            break;
        case 4:
            newAddressee.surname = lineInFile;
            break;
        case 5:
            newAddressee.telephoneNumber = lineInFile;
            break;
        case 6:
            newAddressee.email = lineInFile;
            break;
        case 7:
            newAddressee.address = lineInFile;
            break;
        }
        if (dataNumber >= 7)
        {
            if (newAddressee.idUser == idLoginUser)
            {
                addressees.push_back(newAddressee);
                dataNumber = 1;
            }
            else
            {
                dataNumber = 1;
            }
        }
        else
        {
            dataNumber++;
        }
    }
}

void checkFileAdd(vector <Addressee> &addressees, int &idLoginUser)
{
    fstream addressBook;
    addressBook.open ("ksiazka_adresowa.txt", ios::in);

    if (addressBook.good() == false)
    {
        cout << "Nie mozna otworzyc kontaktow" << endl;
        Sleep(1000);
        return;
    }
    else if(addressBook.good() == true)
    {
        openFileAdd(addressees, idLoginUser);
    }
    addressBook.close();
}

void saveFileAdd(vector <Addressee> &addressees, Addressee modifiedAddresse)
{
    fstream addressBook, addressBookTemp;
    addressBook.open("ksiazka_adresowa.txt", ios::in);
    addressBookTemp.open("ksiazka_adresowa_tymczasowy.txt", ios::out | ios::app);

    string lineInFile;
    int dataNumber = 1;
    Addressee newAddressee;

    while (getline(addressBook, lineInFile, '|'))
    {
        switch (dataNumber)
        {
        case 1:
            newAddressee.id = atoi(lineInFile.c_str());
            break;
        case 2:
            newAddressee.idUser = atoi(lineInFile.c_str());
            break;
        case 3:
            newAddressee.name = lineInFile;
            break;
        case 4:
            newAddressee.surname = lineInFile;
            break;
        case 5:
            newAddressee.telephoneNumber = lineInFile;
            break;
        case 6:
            newAddressee.email = lineInFile;
            break;
        case 7:
            newAddressee.address = lineInFile;
            break;
        }
        if (dataNumber >= 7)
        {
            if (newAddressee.id == modifiedAddresse.id)
            {
                addressBookTemp << modifiedAddresse.id << '|' << modifiedAddresse.idUser << '|' << modifiedAddresse.name << '|' << modifiedAddresse.surname << '|'
                                << modifiedAddresse.telephoneNumber << '|' << modifiedAddresse.email << '|' << modifiedAddresse.address << '|' << endl;
                dataNumber = 1;
            }
            else
            {
                addressBookTemp << newAddressee.id << '|' << newAddressee.idUser << '|' << newAddressee.name << '|' << newAddressee.surname << '|'
                                << newAddressee.telephoneNumber << '|' << newAddressee.email << '|' << newAddressee.address << '|' << endl;
                dataNumber = 1;
            }
        }
        else
        {
            dataNumber++;
        }
    }
    addressBook.close();
    addressBookTemp.close();

    remove("ksiazka_adresowa.txt");
    char oldName[] = "ksiazka_adresowa_tymczasowy.txt";
    char newName[] = "ksiazka_adresowa.txt";
    rename(oldName, newName);
    cout << "Zapisano dane" << endl;
    Sleep(1000);
}

void saveFileAdd(vector <Addressee> &addressees, int idDeletedAddressee)
{
    fstream addressBook, addressBookTemp;
    addressBook.open("ksiazka_adresowa.txt", ios::in);
    addressBookTemp.open("ksiazka_adresowa_tymczasowy.txt", ios::out | ios::app);

    string lineInFile;
    int dataNumber = 1;
    Addressee newAddressee;

    while (getline(addressBook, lineInFile, '|'))
    {
        switch (dataNumber)
        {
        case 1:
            newAddressee.id = atoi(lineInFile.c_str());
            break;
        case 2:
            newAddressee.idUser = atoi(lineInFile.c_str());
            break;
        case 3:
            newAddressee.name = lineInFile;
            break;
        case 4:
            newAddressee.surname = lineInFile;
            break;
        case 5:
            newAddressee.telephoneNumber = lineInFile;
            break;
        case 6:
            newAddressee.email = lineInFile;
            break;
        case 7:
            newAddressee.address = lineInFile;
            break;
        }
        if (dataNumber >= 7)
        {
            if (newAddressee.id == idDeletedAddressee)
            {
                dataNumber = 1;
            }
            else
            {
                addressBookTemp << newAddressee.id << '|' << newAddressee.idUser << '|' << newAddressee.name << '|' << newAddressee.surname << '|'
                                << newAddressee.telephoneNumber << '|' << newAddressee.email << '|' << newAddressee.address << '|' << endl;
                dataNumber = 1;
            }
        }
        else
        {
            dataNumber++;
        }
    }
    addressBook.close();
    addressBookTemp.close();

    remove("ksiazka_adresowa.txt");
    char oldName[] = "ksiazka_adresowa_tymczasowy.txt";
    char newName[] = "ksiazka_adresowa.txt";
    rename(oldName, newName);
    cout << "Zapisano dane" << endl;
    Sleep(1000);
}

void addNewAddressee (vector <Addressee> &addressees, int idLoginUser)
{
    string name, surname, telephoneNumber, email, address;
    cout << "Dodawanie adresata:" << endl << "----------------------" << endl;
    cout << "Podaj imie: " << endl;
    cin >> name;
    cout << "Podaj nazwisko: " << endl;
    cin >> surname;
    cout << "Podaj numer telefonu: " << endl;
    cin.sync();
    getline(cin, telephoneNumber);
    cout << "Podaj email: " << endl;
    cin >> email;
    cout << "Podaj adres: " << endl;
    cin.sync();
    getline(cin, address);
    int lastID = getLastIdAdd();

    Addressee newAddressee;
    newAddressee.id = lastID + 1;
    newAddressee.idUser = idLoginUser;
    newAddressee.name = name;
    newAddressee.surname = surname;
    newAddressee.telephoneNumber = telephoneNumber;
    newAddressee.email = email;
    newAddressee.address = address;

    addressees.push_back(newAddressee);

    fstream addressBook;
    addressBook.open("ksiazka_adresowa.txt", ios::out | ios::app);
    addressBook << lastID + 1 << '|' << idLoginUser << '|' << name << '|' << surname << '|' << telephoneNumber << '|' << email << '|' << address << '|' << endl;
    addressBook.close();

    cout << "Dodano adresata" << endl;
    Sleep(1000);
}

void searchByName(vector <Addressee> &addressees)
{
    string name;
    cout << "Podaj imie osoby do wyszukania: ";
    cin.sync();
    getline(cin, name);
    for (int i = 0, end = addressees.size(); i < end; i++)
    {
        if (addressees[i].name == name)
        {
            cout << endl;
            cout << "ID: " << addressees[i].id << endl;
            cout << addressees[i].name << " " << addressees[i].surname << endl;
            cout << "Telefon: " << addressees[i].telephoneNumber << endl;
            cout << "Email: " << addressees[i].email << endl;
            cout << "Adres: " << addressees[i].address << endl;
            cout << endl;
        }
    }
    system("pause");
}

void searchBySurname(vector <Addressee> &addressees)
{
    string surname;
    cout << "Podaj nazwisko osoby do wyszukania: ";
    cin.sync();
    getline(cin, surname);
    for (int i = 0, end = addressees.size(); i < end; i++)
    {
        if (addressees[i].surname == surname)
        {
            cout << endl;
            cout << "ID: " << addressees[i].id << endl;
            cout << addressees[i].name << " " << addressees[i].surname << endl;
            cout << "Telefon: " << addressees[i].telephoneNumber << endl;
            cout << "Email: " << addressees[i].email << endl;
            cout << "Adres: " << addressees[i].address << endl;
            cout << endl;
        }
    }
    system("pause");
}

void deleteAddressee(vector <Addressee> &addressees)
{
    int id = 0;
    cout << "Podaj ID osoby do usuniecia: ";
    cin >> id;
    for (int i = 0, end = addressees.size(); i < end; i++)
    {
        if (addressees[i].id == id)
        {
            char choice;
            cout << "Czy na pewno chcesz usunac adresata? (t/n): ";
            cin >> choice;
            if (choice == 't')
            {
                addressees.erase(addressees.begin() + i);
                cout << "Usunieto adresata" << endl;
                Sleep(1000);
            }
            else if (choice == 'n')
            {
                return;
            }
            else
            {
                cout << "Niepoprawny wybor" << endl;
                Sleep(1000);
                return;
            }
        }
        else
        {
            cout << "Niedozwolony wybor" << endl;
            Sleep(1000);
            return;
        }
    }
    int idDeletedAddressee = id;
    saveFileAdd(addressees, idDeletedAddressee);
}

void editAddressee(vector <Addressee> &addressees)
{
    int id = 0;
    cout << "Podaj ID osoby do edycji danych: ";
    cin >> id;
    for (int i = 0, end = addressees.size(); i < end; i++)
    {
        if (addressees[i].id == id)
        {
            char numberMenu;

            while (1)
            {
                system ("cls");
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer telefonu" << endl;
                cout << "4. E-mail" << endl;
                cout << "5. Adres zamieszkania" << endl;
                cout << "9. Powrot do menu" << endl;
                cin >> numberMenu;

                switch (numberMenu)
                {
                case '1':
                    cout << "Podaj nowe imie: ";
                    cin >> addressees[i].name;
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    cin >> addressees[i].surname;
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    cin.sync();
                    getline(cin, addressees[i].telephoneNumber);
                    break;
                case '4':
                    cout << "Podaj nowy e-mail: ";
                    cin >> addressees[i].email;
                    break;
                case '5':
                    cout << "Podaj nowy adres: ";
                    cin.sync();
                    getline(cin, addressees[i].address);
                    break;
                case '9':
                    return;
                }
                saveFileAdd(addressees, addressees[i]);
                cout << "Zmieniono dane adresata" << endl;
                Sleep(1000);
            }
        }
    }
    system("pause");
}

void displayAddressees(vector <Addressee> &addressees)
{
    for (int i = 0, end = addressees.size(); i < end; i++)
    {
        cout << endl;
        cout << "ID: " << addressees[i].id << endl;
        cout << addressees[i].name << " " << addressees[i].surname << endl;
        cout << "Telefon: " << addressees[i].telephoneNumber << endl;
        cout << "Email: " << addressees[i].email << endl;
        cout << "Adres: " << addressees[i].address << endl;
        cout << endl;
    }
    system("pause");
}
