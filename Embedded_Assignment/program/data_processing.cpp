#include "definitions.h"
#include <string.h>
#include <fstream>
#include <iostream>


using namespace std;

// Load data from text file
void load_data(bool table[N_TILES_H][N_TILES_W], string& name_file) {
    ifstream data_flux("data/" + name_file + ".txt");
    char a;

    if(data_flux)
    {
        int i = 0, j = 0;
        do {
            data_flux.get(a);
            if (a == '0') {
                table[i][j] =  false;
                j += 1;
            }
            else if (a == '1') {
                table[i][j] =  true;
                j += 1;
            }
            else if (a == '\n') {
                i += 1;
                j = 0;
            }
            else{
                cout << "ERROR: Failed to read the file." << endl;
            return;
            }
        } while ((i <= N_TILES_H) && (j <= N_TILES_W));
    }
    else
    {
    cout << "ERROR: Impossible to open the file." << endl;
    }
    return;
}

// Save grid to text file
void save_data(bool table[N_TILES_H][N_TILES_W], string& name_file) {
    ofstream data_flux("data/" + name_file + ".txt");
    if(data_flux) //On teste si tout est OK
    {
        int i, j;
        for (i=0; i < N_TILES_H; i++) {
            for (j=0; j < N_TILES_W; j++) {
                data_flux << table[i][j];
            }
            data_flux << endl;
        }
    }
    else
    {
    cout << "ERROR: Impossible to open the file." << endl;
    }
}
