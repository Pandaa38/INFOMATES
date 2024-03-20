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
    if(nElements > dim) nElements = dim;
    
    for(int i = 0; i < nElements; i++){
        
        int freq;
        std::string nucleotide;
        
        std::cin >> nucleotide;
        std::cin >> freq;
        
        array[i].setKmer(Kmer(nucleotide));
        array[i].setFrequency(freq);
    }
}

void PrintArrayKmerFreq(const KmerFreq array[], int nElements){
    
    if(nElements > 0) std::cout << nElements << std::endl;
    
    for(int i = 0; i < nElements; i++){
        std::cout << array[i].toString() << std::endl;
        
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
    
    bool found = false;
    
    while(initialPos <= finalPos && !found){
        
        if(array[initialPos].getKmer().toString() == kmer.toString())
            found = true;
        
        else initialPos++;
    }
    
    if(!found) initialPos = -1;
    
    return initialPos;
}

// Use selection sort
void SortArrayKmerFreq(KmerFreq array[], int nElements){
    
    for (int left = 0 ; left < nElements ; left++) {
        
        KmerFreq max = array[left]; 
        int pos_max = left;
        
        for (int i = left + 1; i < nElements ; i++){
            if (array[i].getFrequency() > max.getFrequency()){
                max = array[i];
                pos_max = i;
            }
            
            else if (array[i].getFrequency() == max.getFrequency()){
                if(array[i].getKmer().toString() < max.getKmer().toString()){
                    max = array[i];
                    pos_max = i;
                }
            }
        }

        SwapElementsArrayKmerFreq(array, nElements, left, pos_max);
    }
}


void NormalizeArrayKmerFreq(KmerFreq array[], int& nElements, 
                            const std::string& validNucleotides){ 
    
    // Loop to traverse and normalize each one of the kmers in array
          // Normalize kmer i
    Kmer normalized;
    for(int i = 0; i < nElements; i++){
        
        normalized = array[i].getKmer();
        normalized.normalize(validNucleotides);
        array[i].setKmer(normalized);
    }
    
    int i = 1;
    
    // Loop to traverse the kmers in array from position 1 to position nElements-1
    while(i < nElements){
        
        // index = Position of array[i].getKmer() in the subarray that begins
        //         at position 0 and ends at position i-1
        int index = FindKmerInArrayKmerFreq(array, array[i].getKmer(), 0, i-1);
        
        // If array[i].getKmer() was found in the the subarray from 0 to i-1 
        if(index != -1){
            
            // Accumulate the frequencies of the kmers at positions 
            //    index and i in the kmer at position index
            int freq = array[i].getFrequency() + array[index].getFrequency();
            array[index].setFrequency(freq);
            
            // Delete from the array, the kmer at position i
            DeletePosArrayKmerFreq(array, nElements, i);
        }
        
        else i++;
    }

}

void DeletePosArrayKmerFreq(KmerFreq array[], int& nElements, int pos){
    
    if(pos < 0 || pos >= nElements)
        throw std::out_of_range( std::string( "pos is not in the range")
                                       + "from 0 to nElements-1");
    
    
    for(int i = pos; i < nElements - 1; i++)
        SwapElementsArrayKmerFreq(array, nElements, i, i+1);
    
    nElements--;
}

void ZipArrayKmerFreq(KmerFreq array[], int& nElements, 
                       bool deleteMissing, int lowerBound){
    
    /* esto funciona siempre
    int i = 0;
    if(deleteMissing){
        
        while(i < nElements){
            
            Kmer Kmer_delete = array[i].getKmer();
            
            if(Kmer_delete.ThereIsMissingNucleotide()){
                DeletePosArrayKmerFreq(array, nElements, i);
            }
            
            else i++;
        }
       
    }
    
    i = 0;
    while(i < nElements){
         
        if(array[i].getFrequency() <= lowerBound){
            DeletePosArrayKmerFreq(array, nElements, i);
            i--;
        }
        else i++;
    }
     */
    
    int i = 0;
    
    while(i < nElements){
        
        if(array[i].getFrequency() <= lowerBound){
            DeletePosArrayKmerFreq(array, nElements, i);
        }
        else if(deleteMissing){
            
            Kmer Kmer_delete = array[i].getKmer();
            
            if(Kmer_delete.ThereIsMissingNucleotide()){
                DeletePosArrayKmerFreq(array, nElements, i);
            }
            else i++;
        }
        else i++;
    }
}
