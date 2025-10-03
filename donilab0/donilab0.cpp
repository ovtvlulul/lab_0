#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pipe {
    string name = "";
    double length = 0.0;
    int diameter = 0;
    bool underRepair = false;
};

struct CompressorStation {
    string name = "";
    int totalShops = 0;
    int workingShops = 0;
    int stationClass = 0;
};

void clearInput() {
    cin.clear();
    cin.ignore(1000, '\n');
}

void waitForEnter() {
    cout << "Press Enter to continue...";
    cin.get();
}

void inputPipe(Pipe& pipe) {
    cout << "Enter pipe name: ";
    getline(cin, pipe.name);

    cout << "Enter pipe length (km): ";
    while (!(cin >> pipe.length) || pipe.length <= 0) {
        cout << "Error! Enter positive number: ";
        clearInput();
    }
    clearInput();

    cout << "Enter pipe diameter (mm): ";
    while (!(cin >> pipe.diameter) || pipe.diameter <= 0) {
        cout << "Error! Enter positive number: ";
        clearInput();
    }
    clearInput();

    pipe.underRepair = false;
    cout << "Pipe added!\n";
}

void showPipe(const Pipe& pipe) {
    if (pipe.name == "") {
        cout << "No pipe data\n";
        return;
    }
    cout << "=== PIPE DATA ===" << endl;
    cout << "Name: " << pipe.name << endl;
    cout << "Length: " << pipe.length << " km" << endl;
    cout << "Diameter: " << pipe.diameter << " mm" << endl;
    cout << "Under repair: " << (pipe.underRepair ? "YES" : "NO") << endl;
    cout << "==================" << endl;
}

void editPipe(Pipe& pipe) {
    if (pipe.name == "") {
        cout << "No pipe to edit\n";
        waitForEnter();
        return;
    }

    cout << "Current repair status: " << (pipe.underRepair ? "YES" : "NO") << endl;
    cout << "Change? (1-yes, 0-no): ";
    int choice;
    cin >> choice;
    clearInput();

    if (choice == 1) {
        pipe.underRepair = !pipe.underRepair;
        cout << "Repair status changed to: " << (pipe.underRepair ? "YES" : "NO") << endl;
    }
    waitForEnter();
}

void inputStation(CompressorStation& station) {
    cout << "Enter station name: ";
    getline(cin, station.name);

    cout << "Enter total shops: ";
    while (!(cin >> station.totalShops) || station.totalShops <= 0) {
        cout << "Error! Enter positive number: ";
        clearInput();
    }

    cout << "Enter working shops: ";
    while (!(cin >> station.workingShops) || station.workingShops < 0 || station.workingShops > station.totalShops) {
        cout << "Error! Enter 0 to " << station.totalShops << ": ";
        clearInput();
    }
    clearInput();

    cout << "Enter station class: ";
    while (!(cin >> station.stationClass) || station.stationClass <= 0) {
        cout << "Error! Enter positive number: ";
        clearInput();
    }
    clearInput();

    cout << "Station added!\n";
}

void showStation(const CompressorStation& station) {
    if (station.name == "") {
        cout << "No station data\n";
        return;
    }
    cout << "=== STATION DATA ===" << endl;
    cout << "Name: " << station.name << endl;
    cout << "Total shops: " << station.totalShops << endl;
    cout << "Working shops: " << station.workingShops << endl;
    cout << "Station class: " << station.stationClass << endl;
    cout << "====================" << endl;
}

void editStation(CompressorStation& station) {
    if (station.name == "") {
        cout << "No station to edit\n";
        waitForEnter();
        return;
    }

    cout << "Current working shops: " << station.workingShops << "/" << station.totalShops << endl;
    cout << "1 - Start shop" << endl;
    cout << "2 - Stop shop" << endl;
    cout << "0 - Cancel" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;
    clearInput();

    if (choice == 1) {
        if (station.workingShops < station.totalShops) {
            station.workingShops++;
            cout << "Shop started. Now working: " << station.workingShops << endl;
        }
        else {
            cout << "All shops already working" << endl;
        }
    }
    else if (choice == 2) {
        if (station.workingShops > 0) {
            station.workingShops--;
            cout << "Shop stopped. Now working: " << station.workingShops << endl;
        }
        else {
            cout << "No shops working" << endl;
        }
    }
    waitForEnter();
}

void saveToFile(const Pipe& pipe, const CompressorStation& station) {
    if (pipe.name == "" && station.name == "") {
        cout << "No data to save\n";
        waitForEnter();
        return;
    }

    // Сохраняем в папку с проектом (рядом с .cpp файлом)
    string filePath = "pipeline_data.txt";
    ofstream file(filePath);
    int a;

    if (file.is_open()) {
        if (pipe.name != "") {
            file << "Pipe\n" << pipe.name << "\n" << pipe.length << "\n"
                << pipe.diameter << "\n" << pipe.underRepair << "\n";
        }
        if (station.name != "") {
            file << "Station\n" << station.name << "\n" << station.totalShops << "\n"
                << station.workingShops << "\n" << station.stationClass << "\n";
        }
        file.close();
        cout << "Data saved to: " << filePath << endl;
        cout << "File location: Same folder as your .cpp file" << endl;
    }
    else {
        cout << "Error saving file!" << endl;
    }
    waitForEnter();
}

void loadFromFile(Pipe& pipe, CompressorStation& station) {
    // Загружаем из папки с проектом
    string filePath = "pipeline_data.txt";
    ifstream file(filePath);

    if (file.is_open()) {
        string line;

        // Сбрасываем текущие данные
        pipe = Pipe();
        station = CompressorStation();

        while (getline(file, line)) {
            if (line == "Pipe") {
                getline(file, pipe.name);
                file >> pipe.length >> pipe.diameter >> pipe.underRepair;
                file.ignore();
                cout << "Pipe data loaded" << endl;
            }
            else if (line == "Station") {
                getline(file, station.name);
                file >> station.totalShops >> station.workingShops >> station.stationClass;
                file.ignore();
                cout << "Station data loaded" << endl;
            }
        }
        file.close();
        cout << "Data loaded from: " << filePath << endl;
    }
    else {
        cout << "Error loading file! File 'pipeline_data.txt' not found." << endl;
        cout << "Make sure you saved data first (option 6)" << endl;
    }
    waitForEnter();
}

int main() {
    Pipe myPipe;
    CompressorStation myStation;
    int choice;

    cout << "=== Pipeline Management System ===" << endl;

    do {
        cout << "\n1. Add Pipe" << endl;
        cout << "2. Add Station" << endl;
        cout << "3. View All Objects" << endl;
        cout << "4. Edit Pipe" << endl;
        cout << "5. Edit Station" << endl;
        cout << "6. Save" << endl;
        cout << "7. Load" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";

        cin >> choice;
        clearInput();

        switch (choice) {
        case 1:
            inputPipe(myPipe);
            break;
        case 2:
            inputStation(myStation);
            break;
        case 3:
            cout << "\n=== VIEWING ALL OBJECTS ===" << endl;
            showPipe(myPipe);
            showStation(myStation);
            cout << "=============================" << endl;
            waitForEnter();
            break;
        case 4:
            editPipe(myPipe);
            break;
        case 5:
            editStation(myStation);
            break;
        case 6:
            saveToFile(myPipe, myStation);
            break;
        case 7:
            loadFromFile(myPipe, myStation);
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Wrong choice!" << endl;
            waitForEnter();
            break;
        }

    } while (choice != 0);

    return 0;
}