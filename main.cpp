#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct Campus {
    int number;
    string surname;

    Campus() {
        surname = "Unknown";
    }

    Campus(const int& number, const string& surname) {
        this->number = number;
        this->surname = surname;
    }

    string toString() {
        string result;
        result = to_string(number) + " " + surname;
        return result;
    }

    friend istream &operator>>(istream &in, Campus &D);

    friend ostream &operator<<(ostream &in, const Campus &D);

    /*void ToBin(ofstream& out) {
        out.write((char*)P, sizeof(Person) * num);
    }
    void readFromBinary(ifstream& fbin) {
        fbin.seekg(0, ios_base::end);
        int posEnd = fbin.tellg();
        delete[] P;
        num = posEnd / sizeof(T);
        P = new Person[num];
        fbin.seekg(0, ios_base::beg);
        fbin.read((char*)P, sizeof(T) * num);
    }*/
};

istream &operator>>(istream &in, Campus &D) {
    string s;
    getline(in, s, ' ');
    D.number = stoi(s);
    getline(in, s, '\n');
    D.surname = s;
    return in;
}

ostream &operator<<(ostream &out, const Campus &D) {
    out << D.surname << ' ' << D.number << endl;
    return out;
}


struct Library {
    int number;
    string surname;
    double price;

    Library() {
        surname = "Unknown";
    }

    Library(const int& number, const double& price ,const string& surname) {
        this->number = number;
        this->price = price;
        this->surname = surname;
    }

    string toString() {
        string result;
        result = to_string(number) + " " + surname + " " + to_string(price);
        return result;
    }

    friend istream &operator>>(istream &in, Library &D);

    friend ostream &operator<<(ostream &in, const Library &D);
};

istream &operator>>(istream &in, Library &D) {
    string s = "";
    getline(in, s, ' ');
    D.number = stoi(s);
    getline(in, s, ' ');
    D.surname = s;
    getline(in, s, '\n');
    D.price = stoi(s);
    return in;
}

ostream &operator<<(ostream &out, const Library &D) {
    out << D.surname << ' ' << D.number << ' ' << D.price << endl;
    return out;
}

template<typename T>
class Stud {
private:
    T *st;
    int size;
public:
    Stud() {
        size = 0;
        st = nullptr;
    }

    Stud(int size) {
        this->size = size;
        st = new Campus[size];
    }

    ~Stud() {
        delete[] st;
    }

    void toText(ostream &out) {
        for (int i = 0; i < size; i++) {
            out << st[i];
        }
    }

    void fromText(istream &in) {
        in >> size;
        {
            string t;
            getline(in, t);
        }
        delete[] st;
        st = new T[size];
        for (int i = 0; i < size; i++) {
            in >> st[i];
        }
    }

    void SortStud() {
        sort(st, st + size, [](T &a, T &b) { return a.number < b.number; });
    }

    void toBin(ofstream &out) {
        this->SortStud();
        out.write((char*) st, (long long) sizeof(T) * size);
    }

    void fromBin(ifstream &fbin) {
        fbin.seekg(0, ios_base::end);
        int posEnd = fbin.tellg();
        delete[] st;
        size = posEnd / sizeof(T);
        st = new T[size];
        fbin.seekg(0, ios_base::beg);
        fbin.read((char *) st, (long long) sizeof(T) * size);
    }
};

int main() {
    ifstream finBinCampus("campusOutBin.txt", ios::binary);
    ifstream finBinLibrary("libraryOutBin.txt", ios::binary);
    Stud<Campus> campus;
    Stud<Library> library;
    campus.fromBin(finBinCampus);
    library.fromBin(finBinLibrary);
    campus.toText(cout);
    library.toText(cout);
    ofstream foutCampus("campusOut.txt");
    ofstream foutLibrary("libraryOut.txt");
    campus.toText(foutCampus);
    library.toText(foutLibrary);
    /*Stud<Campus> campus;
    ofstream fout("campusOut.txt");
    ofstream finBinCampus("campusOutBin.txt", ios::binary);
    campus.fromText(cin);
    campus.toText(fout);
    campus.SortStud();
    campus.toBin(finBinCampus);
     */
    return 0;
}
