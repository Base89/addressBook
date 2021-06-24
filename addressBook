#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

struct Addressee
{
    int id;
    string name, surname, telephoneNumber, email, address;
};
void openFile(vector <Addressee> &addressees);
void checkFile(vector <Addressee> &addressees);
void saveFile(vector <Addressee> &addressees);
void addNewAddressee (vector <Addressee> &addressees);
void searchByName(vector <Addressee> &addressees);
void searchBySurname(vector <Addressee> &addressees);
void deleteAddressee(vector <Addressee> &addressees);
void editAddressee(vector <Addressee> &addressees);
void displayAddressees(vector <Addressee> &addressees);

int main()
{
    vector <Addressee> addressees;
    checkFile(addressees);
    char numberMenu;

    while (1)
    {
        system ("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> numberMenu;

        switch (numberMenu)
        {
        case '1':
            addNewAddressee (addressees);
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
        case '9':
            exit(0);
        }
    }
    return 0;
}

void openFile(vector <Addressee> &addressees)
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
            newAddressee.name = lineInFile;
            break;
        case 3:
            newAddressee.surname = lineInFile;
            break;
        case 4:
            newAddressee.telephoneNumber = lineInFile;
            break;
        case 5:
            newAddressee.email = lineInFile;
            break;
        case 6:
            newAddressee.address = lineInFile;
            break;
        }
        if (dataNumber >= 6)
        {
            addressees.push_back(newAddressee);
            dataNumber = 1;
        }
        else
        {
            dataNumber++;
        }
    }
}

void checkFile(vector <Addressee> &addressees)
{
    fstream addressBook;
    addressBook.open ("ksiazka_adresowa.txt", ios::in);

    if (addressBook.good() == false)
    {
        cout << "Nie mozna otworzyc kontaktow" << endl;
        return;
    }
    else if(addressBook.good() == true)
    {
        openFile(addressees);
    }
    addressBook.close();
}

void saveFile(vector <Addressee> &addressees)
{
    fstream addressBook;
    addressBook.open("ksiazka_adresowa.txt", ios::out);

    for (int i = 0, end = addressees.size(); i < end; i++)
    {
        addressBook << addressees[i].id << '|' << addressees[i].name << '|' << addressees[i].surname << '|' << addressees[i].telephoneNumber << '|'
                    << addressees[i].email << '|' << addressees[i].address << '|' << endl;
    }
    addressBook.close();
    cout << "Zapisano dane" << endl;
    Sleep(1000);
}

void addNewAddressee (vector <Addressee> &addressees)
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
    int lastID = addressees.empty() ? 0 : addressees.back().id;

    Addressee newAddressee;
    newAddressee.id = lastID + 1;
    newAddressee.name = name;
    newAddressee.surname = surname;
    newAddressee.telephoneNumber = telephoneNumber;
    newAddressee.email = email;
    newAddressee.address = address;

    addressees.push_back(newAddressee);

    fstream addressBook;
    addressBook.open("ksiazka_adresowa.txt", ios::out | ios::app);
    addressBook << lastID + 1 << '|' << name << '|' << surname << '|' << telephoneNumber << '|' << email << '|' << address << '|' << endl;
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
            cout << "Czy na pewno chcesz usunac adresata? (t/n) :";
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
        }
    }
    saveFile(addressees);
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
                    cout << "Podaj nowe imie:";
                    cin >> addressees[i].name;
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko:";
                    cin >> addressees[i].surname;
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu:";
                    cin >> addressees[i].telephoneNumber;
                    break;
                case '4':
                    cout << "Podaj nowy e-mail:";
                    cin >> addressees[i].email;
                    break;
                case '5':
                    cout << "Podaj nowy adres:";
                    cin >> addressees[i].address;
                    break;
                case '9':
                    return;
                }
                saveFile(addressees);
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
