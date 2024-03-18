/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file ArrayKmerFreqFunctions.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 27 October 2023, 12:00
 */


#include "ArrayKmerFreqFunctions.h"

void ReadArrayKmerFreq(KmerFreq array[], int dim, int& nElements){
    
    std::cin >> nElements;
    
    for(int i = 0; i < nElements && i < dim; i++){
        
        int freq;
        std::string nucleotide;
        
        std::cin >> nucleotide;
        std::cin >> freq;
        
        array[i].setKmer(Kmer(nucleotide));
        array[i].setFrequency(freq);
    }
}

void PrintArrayKmerFreq(const KmerFreq array[], int nElements){
    
    for(int i = 0; i < nElements; i++){
        std::cout << array[i].getKmer().toString() << " " 
                  << array[i].getFrequency() << std::endl;
        
    }
}

void SwapElementsArrayKmerFreq(KmerFreq array[], int nElements, int first,
                               int second){
    
    if(first > nElements || second > nElements)
        throw std::out_of_range (std::string("first or second are positions") +
                                 "out of the range of the given array");
    
    KmerFreq intermediate_Kmer;
    intermediate_Kmer = array[first];
    
    array[first] = array[second];
    
    array[second] = intermediate_Kmer;
    
}

int FindKmerInArrayKmerFreq(const KmerFreq array[], const Kmer& kmer,
        int initialPos, int finalPos){
    
    bool finded = false;
    int pos = initialPos + 1;
    
    while(pos < finalPos && !finded){
        
        if(kmer.toString() == array[pos].getKmer().toString()) 
            finded = true;
        
        pos++;
    }
    
    if(finded == false) pos = -1;
    
    return pos;
}


void SortArrayKmerFreq(KmerFreq array[], int nElements){
    
    for (int izda = 0 ; izda < nElements ; izda++) {
        
        KmerFreq minimo = array[izda]; 
        int pos_min = izda; 
        
        for (int i = izda + 1; i < nElements ; i++)
            if (array[i].getFrequency() < minimo.getFrequency()){ 
            minimo = array[i];
            pos_min = i;
        }

        SwapElementsArrayKmerFreq(array, nElements, izda, pos_min);
    }
}


void NormalizeArrayKmerFreq(KmerFreq array[], int& nElements, 
                            const std::string& validNucleotides){ 
    
    // Loop to traverse and normalize each one of the kmers in array
          // Normalize kmer i
    for(int i = 0; i < nElements; i++){
        
        Kmer normalized = array[i].getKmer();
        normalized.normalize(validNucleotides);
        array[i].setKmer(normalized);
    }
    
    
    // Loop to traverse the kmers in array from position 1 to position nElements-1
    for(int i = 0; i < nElements; i++){
        // index = Position of array[i].getKmer() in the subarray that begins
          //         at position 0 and ends at position i-1
        
        int index = FindKmerInArrayKmerFreq(array, array[i].getKmer(), i, nElements);
        
        // If array[i].getKmer() was found in the the subarray from 0 to i-1 
        if(index != -1) {
            // Accumulate the frequencies of the kmers at positions 
            //    index and i in the kmer at position index
            int freq = array[i].getFrequency() + array[index].getFrequency();
             array[i].setFrequency(freq);
             
             // Delete from the array, the kmer at position i
             DeletePosArrayKmerFreq(array, nElements, i);
        } 
    }
}

void DeletePosArrayKmerFreq(KmerFreq array[], int& nElements, int pos){
    
    if(pos < 0 || pos > nElements - 1)
        throw std::out_of_range( std::string( "pos is not in the range")
                                       + "from 0 to nElements-1");
    
    
    int tope = nElements-1;
    
    for(int i = pos ; i < tope ; i++)
        array[i] = array[i+1];
    
    nElements -= 1;
}

void ZipArrayKmerFreq(KmerFreq array[], int& nElements, 
                       bool deleteMissing, int lowerBound){
    
    for(int i = 0; i < nElements; i++){
        
        if(deleteMissing){
            Kmer miss = array[i].getKmer();
            if(miss.ThereIsMissingNucleotide())
                DeletePosArrayKmerFreq(array, nElements, i);            
        }
        
        if(array[i].getFrequency() <  lowerBound)
            DeletePosArrayKmerFreq(array, nElements, i);
        
    }
    
}
