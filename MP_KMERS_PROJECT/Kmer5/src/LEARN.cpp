/*
 * Metodología de la Programación: Kmer5
 * Curso 2023/2024
 */

/** 
 * @file LEARN.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 22 December 2023, 10:00
 */

#include <iostream>
#include <cstring>
#include "KmerCounter.h"

using namespace std;
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "ERROR in LEARN parameters" << endl;
    outputStream << "Run with the following parameters:" << endl;
    outputStream << "LEARN [-t|-b] [-k kValue] [-n nucleotidesSet] [-p profileId] [-o outputFilename] <file1.dna> [<file2.dna> <file3.dna> .... ]" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-k kValue: number of nucleotides in a kmer (5 by default)" << endl;
    outputStream << "-n nucleotidesSet: set of possible nucleotides in a kmer (ACGT by default). " 
                 << "Note that the characters should be provided in uppercase" << endl;
    outputStream << "-p profileId: profile identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.prf by default)" << endl;
    outputStream << "<file1.dna> <file2.dna> <file3.dna> ....: names of the input files (at least one is mandatory)" << endl;
    outputStream << endl;
    outputStream << "This program learns a profile model from a set of "<< 
            "input DNA files <file1.dna> <file2.dna> <file3.dna> ...." << endl;
    outputStream << endl;
}

/**
 * This program learns a Profile model from a set of input DNA files (file1.dna,
 * file2.dna, ...). The learned Profile object is then zipped (kmers with any 
 * missing nucleotide or with frequency equals to zero will be removed) 
 * and ordered by frequency and saved in 
 * the file outputFilename (or output.prf if the output file is not provided).
 * 
 * Running sintax:
 * > LEARN [-t|-b] [-k kValue] [-n nucleotidesSet] [-p profileId] [-o outputFilename] <file1.dna> [<file2.dna> <file3.dna> ....]
 * 
 * Running example:
 * > LEARN -k 2 -p bug -o /tmp/unknownACGT.prf ../Genomes/unknownACGT.dna
 * 
 * > cat /tmp/unknownACGT.prf
MP-KMER-T-1.0
bug
7
GG 2
AC 1
AG 1
AT 1
CC 1
GA 1
TA 1
 * 
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char *argv[]) {  
    // Process the main() arguments
    if(argc < 3){
        showEnglishHelp(cerr);
        return 1;
    }
    //DEFAULT
    /*
     * -t (text)
     * id unknow
     * k = 5 (ya en el constructor)
     * nucleotidesSet = ACGT
     * salida = output.prf
     */
    
    int kValue = 5;
    char mode = 't';
    std::string nucleotidesSet;
    std::string id;
    std::string output = "output.prf";
    
    int pos = 1;
    bool fin = false;
    
    while ((pos < argc) && (!fin)) {
        if (argv[pos][0] == '-') {
            if (strlen(argv[pos]) == 2) { // Se necesita una letra
                //MODE
                if (argv[pos][1] == 't') {
                    // Modo texto. 
                    pos++;
                } else if (argv[pos][1] == 'b') {
                    mode = 'b';
                    pos++;
                }
                // K VALUE
                else if (argv[pos][1] == 'k' && (pos + 1 < argc)) {
                    kValue = atoi(argv[pos+1]);
                    pos+=2;
                }
                //PROFILE ID
                else if (argv[pos][1] == 'p' && (pos + 1 < argc)) {
                    id = argv[pos+1];
                    pos+=2;
                }
                // VALID NUCLEOTIDES
                else if (argv[pos][1] == 'n' && (pos + 1 < argc)) {
                    nucleotidesSet = argv[pos+1];
                    pos+=2;
                }
                // OUTPUT
                else if (argv[pos][1] == 'o' && (pos + 1 < argc)) {
                    output = argv[pos+1];
                    pos+=2;
                }
                else{
                    showEnglishHelp(cerr);
                    return 1;
                }
                    
            }//strlen(argv[pos]) == 2
            else {
                // Error, se ha puesto solo ‘-’
                showEnglishHelp(cerr);
                return 1;
            }

        }//argv[pos][0] == '-'
        // Aquí comienza lista de ficheros de entrada.
        //if(pos + 1 <= argc){
        //    showEnglishHelp(cerr);
        //    return 1;
        //}
        else 
            fin = true;
        
    }
        
    // Loop to calculate the kmer frecuencies of the input genome files using 
    // a KmerCounter object
    KmerCounter kmerCounter(kValue);
    KmerCounter tmp(kValue);
    
    if(!nucleotidesSet.empty()){
        kmerCounter = KmerCounter(kValue,nucleotidesSet);
        tmp = KmerCounter(kValue,nucleotidesSet);
    }
    
    for(int i = pos;i < argc; i++){
        
        tmp.calculateFrequencies(argv[i]);
        kmerCounter += tmp;
    }
    
    
    // Obtain a Profile object from the KmerCounter object
    Profile profile = kmerCounter.toProfile();
    if(!id.empty())
        profile.setProfileId(id);
    
    // Zip the Profile object
    profile.zip(true);
    
    // Sort the Profile object
    profile.sort();
    
    // Save the Profile object in the output file
    profile.save(output.c_str());
     
    
    /*
     * ERROR CON ESCRIBIR EN BINARIO
    Profile l1;
    Profile l2;
    l1.setProfileId("Test1");
    KmerFreq kmf;
    for (int i = 0; i < 10; i++) {
        Kmer kmer(i + 1);
        kmf.setKmer(kmer);
        kmf.setFrequency(10 - i);
        l1.append(kmf);
        kmer.at(0) = 'A';
        kmf.setKmer(kmer);
        kmf.setFrequency(10 - i);
        l1.append(kmf);
    }
    l1.sort();
    
    const char* fileName = "tests/output/testb_save.bgr";
    l1.save(fileName, 'b');
    
    l2.load(fileName);
    bool iguales = true;
    iguales = l1.toString() == l2.toString();
    cout << boolalpha << iguales;
    */     
}