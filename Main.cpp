#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <vector>

using namespace std;

//function to get the process list
vector<PROCESSENTRY32> GetProcesses() {
    //initializing vector to store all the processes
    vector<PROCESSENTRY32> processes;
    //handle to the snapshot of the processes
    HANDLE hProcessSnap;
    //structure to store the process information
    PROCESSENTRY32 pe32;

    //creating the snapshot of the processes
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    //checking to see if the snapshot was made successfully
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        //outputting error message if the snapshot was not made successfully
        cout << "CreateToolhelp32Snapshot (of processes) failed" << endl;
        return processes;
    }

    //declaring size of the structure
    pe32.dwSize = sizeof(PROCESSENTRY32);

    //if the first process is not found, output error message and return
    if (!Process32First(hProcessSnap, &pe32)) {
        cout << "Process32First failed" << endl;
        CloseHandle(hProcessSnap);
        return processes;
    }

    //Adding processes to the vector one by one until all processes are added
    do {
        processes.push_back(pe32);
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return processes;
}

void PopulateListBox(HWND hListBox, const vector <PROCESSENTRY32>& processes) {
    //looping through the processes and adding them to the list box
    for (int i = 0; i < processes.size(); i++) {
        //adding the process name to the list box
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)processes[i].szExeFile);
    }
}

int main() {
    vector<PROCESSENTRY32> processes = GetProcesses();

}


