/*
 * Metodología de la Programación: Kmer4
 * Curso 2023/2024
 */

/**
 * @file main.cpp
 * @author Juan Reche Aguilar
 *
 * Created on 16 November 2023, 14:15
 */

#include <iostream>
#include "Profile.h"

using namespace std;


/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "ERROR in Kmer4 parameters" << endl;
    outputStream << "Run with the following parameters:" << endl;
    outputStream << "kmer4 [-t min|max] <file1.prf> <file2.prf> [ ... <filen.prf>]" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t min | -t max: search for minimun distances or maximum distances (-t min by default)" << endl;
    outputStream << "<file1.prf>: source profile file for computing distances" << endl;
    outputStream << "<file2.prf> [ ... <filen.prf>]: target profile files for computing distances" << endl;  
    outputStream << endl;
    outputStream << "This program computes the distance from profile <file1.prf> to the rest" << endl;
    outputStream << endl;
}

/**
 * This program reads an undefined number of Profile objects from the set of 
 * files passed as parameters to main(). All the Profiles object, except the 
 * first one, must be stored in a dynamic array of Profile objects. Then, 
 * for each Profile in the dynamic array, this program prints to the 
 * standard output the name of the file of that Profile and the distance from 
 * the first Profile to the current Profile. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Profile with the minimum|maximum  distance to the Profile 
 * of the first file and its profile identifier.
 * 
 * At least, two Profile files are required to run this program.
 * 
 * This program assumes that the profile files are already normalized and 
 * sorted by frequency. This is not checked in this program. Unexpected results
 * will be obtained if those conditions are not met.
 * 
 * Running sintax:
 * > kmer4 [-t min|max] <file1.prf> <file2.prf> [  ... <filen.prf>] 
 * 
 * Running example:
 * > kmer4 ../Genomes/human1.prf ../Genomes/worm1.prf ../Genomes/mouse1.prf 
Distance to ../Genomes/worm1.prf: 0.330618
Distance to ../Genomes/mouse1.prf: 0.224901
Nearest profile file: ../Genomes/mouse1.prf
Identifier of the nearest profile: mus musculus
 * 
 * Running example:
 * > kmer4 -t max ../Genomes/human1.prf ../Genomes/worm1.prf ../Genomes/mouse1.prf 
Distance to ../Genomes/worm1.prf: 0.330618
Distance to ../Genomes/mouse1.prf: 0.224901
Farthest profile file: ../Genomes/worm1.prf
Identifier of the farthest profile: worm
 */

bool min_mode(double n1, double n2){
    return n1 <= n2;
}
bool max_mode(double n1, double n2){
    return n1 >= n2;
}

int pos_min_max(const double* distances, int size,
                bool (*compare)(double n1, double n2) )
{
    int pos = 0;
    
    for(int i = 1; i < size; i++){
        
        if(compare(distances[i],distances[pos]))
            pos = i;
    }
    
    return pos;
}

int main(int argc, char* argv[]) {
        
    // Process the main() arguments
     if(argc < 3){
        showEnglishHelp(cerr);
        return 1;
    }
     
    bool min = true; //Default
    int pos_base = 1;
    
    if(argv[1][0] == '-'){
        
        if(argv[1][1] == 't'){
            
            pos_base = 3;
            
            if(argc - pos_base < 2){
                showEnglishHelp(cerr);
                return 1;
            }
            
            if((string)argv[2] == "max"){
                min = false;
            }
            else if((string)argv[2] != "max" && (string)argv[2] != "min"){
                showEnglishHelp(cerr);
                return 1;
            }
        }//if(argv[1][1] == 't')
        else{
            showEnglishHelp(cerr);
            return 1;
        }
    }//if(argv[1][0] == '-')
    
    
    // Allocate a dynamic array of Profiles
    int num_candidates = argc - pos_base -1;
    
    Profile *candidates = new Profile [num_candidates];
    double *distances = new double [num_candidates];
    
    // Load the input Profiles
    Profile base;
    base.load(argv[pos_base]);
    
    for(int i = 0; i < num_candidates; i++){
        
        candidates[i].load(argv[pos_base+1 + i]);
    }
    
    // Calculate and print the distance from the first Profile to the rest
    for(int i = 0; i < num_candidates; i++){
        
        distances[i] = base.getDistance(candidates[i]);
        cout << "Distance to " << argv[pos_base+1 + i] << ": " 
             << distances[i] << endl;
    }
    
    int index=pos_min_max(distances, num_candidates, min ? min_mode : max_mode);
  
    cout << (min ? "Nearest" : "Farthest") << " profile file: " 
         << (string)argv[pos_base+1+index] << endl;
    cout << "Identifier of the " << (min ? "nearest" : "farthest")<< " profile: " 
         << candidates[index].getProfileId() << endl;
    
    // Deallocate the dynamic array of Profile
    delete [] candidates;
    delete [] distances;
    
    candidates = nullptr; //no se si necesario
    distances = nullptr;    
    
    return 0;
}