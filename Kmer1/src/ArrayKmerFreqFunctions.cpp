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

void ReadArrayKmerFreq(KmerFreq& array[], int dim, int& nElements){
    
    std::cin >> nElements;
    
    for(int i = 0; i < nElements && i < dim; i++){
        std::cin >> array[i].setKmer();
        std::cin >> array[i].setFrequency();
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
    
    
    Kmer intermediate_Kmer() = array[first].getKmer();
    int intermediate_int = array[first].getFrequency();
    
    array[first].setKmer(array[second].getKmer());
    array[first].setFrequency(array[second].getFrequency());
    
    array[second].setKmer(intermediate_Kmer);
    array[second].setFrequency(intermediate_int);
}

void NormalizeArrayKmerFreq(KmerFreq array[], int nElements, 
                            std::string validNucleotides){ 
    
    // Loop to traverse and normalize each one of the kmers in array
          // Normalize kmer i
    
    
    // Loop to traverse the kmers in array from position 1 to position nElements-1
          // index = Position of array[i].getKmer() in the subarray that begins
          //         at position 0 and ends at position i-1
          // If array[i].getKmer() was found in the the subarray from 0 to i-1 
               // Accumulate the frequencies of the kmers at positions 
               //    index and i in the kmer at position index
               // Delete from the array, the kmer at position i 
}

