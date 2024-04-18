/*
 * Metodología de la Programación: Kmer3
 * Curso 2023/2024
 */

/**
 * @file main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
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
    outputStream << "ERROR in Kmer3 parameters" << endl;
    outputStream << "Run with the following parameters:" << endl;
    outputStream << "kmer3 [-t min|max] <file1.prf> <file2.prf> [ ... <filen.prf>]" << endl;
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
 * > kmer3 [-t min|max] <file1.prf> <file2.prf> [  ... <filen.prf>] 
 * 
 * Running example:
 * > kmer3 ../Genomes/human1.prf ../Genomes/worm1.prf ../Genomes/mouse1.prf 
Distance to ../Genomes/worm1.prf: 0.330618
Distance to ../Genomes/mouse1.prf: 0.224901
Nearest profile file: ../Genomes/mouse1.prf
Identifier of the nearest profile: mus musculus
 * 
 * Running example:
 * > kmer3 -t max ../Genomes/human1.prf ../Genomes/worm1.prf ../Genomes/mouse1.prf 
Distance to ../Genomes/worm1.prf: 0.330618
Distance to ../Genomes/mouse1.prf: 0.224901
Farthest profile file: ../Genomes/worm1.prf
Identifier of the farthest profile: worm
 */
int main(int argc, char* argv[]) {
    
    //preguntar si string o bool
    std::string mode = "min"; //Default
    int pos_base = 1;
    
    // Process the main() arguments
     if(argc < 3){
        showEnglishHelp(cerr);
        return 1;
    }
    
    //mejorar para test 3 (pone -f)
    if(argv[1][0] == '-'){
        if(argv[1][1] == 't'){
            if((string)argv[2] != "min" && (string)argv[2] != "max" ){
                showEnglishHelp(cerr);
                return 1;
            }
            else{
                mode = (string)argv[2];
                pos_base = 3;
            }
        }
        else{
            showEnglishHelp(cerr);
            return 1;
        }
    }
    
    
    // Allocate a dynamic array of Profiles
    int num_candidates = argc - pos_base -1;
    Profile *candidates;
    candidates = new Profile [num_candidates];
    
    // Load the input Profiles
    Profile base;
    base.load(argv[pos_base]);
    base.sort();
    
    for(int i = 0; i < num_candidates; i++){
        
        candidates[i].load(argv[pos_base+1 + i]);
        candidates[i].sort();

    }
    
    // Calculate and print the distance from the first Profile to the rest
    double distance_mode = base.getDistance(candidates[0]);
    double distance;
    int index = 0;
    
    for(int i = 0; i < num_candidates; i++){
        
        distance = base.getDistance(candidates[i]);
        cout << "Distance to "<<argv[pos_base+1 + i]<< ": "<< distance <<endl;
        
        
        if(mode == "max" && distance > distance_mode){
             distance_mode = distance;
             index = i;
        }
        else if(mode == "min" && distance < distance_mode){
            distance_mode = distance;
            index = i;
        }
    }
    
    //preguntar si es mejor hacer array y luego coger el primero
    // Print name of the file and identifier that takes min|max distance to the first one
    if(mode == "min"){
        cout << "Nearest profile file: " << (string)argv[pos_base+1+index]
             << endl;
        cout << "Identifier of the nearest profile: " 
             << candidates[index].getProfileId() << endl;
    }
    else{
        cout << "Farthest profile file: " << (string)argv[pos_base+1+index] 
             << endl;
        cout << "Identifier of the farthest profile: " 
             << candidates[index].getProfileId() << endl;
    }
    
    // Deallocate the dynamic array of Profile
    delete [] candidates;
    
    return 0;
}
