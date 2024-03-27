/*
 * Metodología de la Programación: Kmer2
 * Curso 2023/2024
 */

/** 
 * @file Profile.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */


#include "Profile.h"
#include <fstream>
#include <iostream>

const std::string Profile::MAGIC_STRING_T="MP-KMER-T-1.0";

/*
 private:
    static const int DIM_VECTOR_KMER_FREQ = 2000; ///< The capacity of the array _vectorKmerFreq
    static const std::string MAGIC_STRING_T; ///< A const string with the magic string for text files

    std::string _profileId; ///< profile identifier
    KmerFreq _vectorKmerFreq[DIM_VECTOR_KMER_FREQ]; ///< array of KmerFreq
    int _size; ///< Number of used elements in _vectorKmerFreq
};
 */

Profile::Profile(){
    
    _profileId = "unknown";
    _vectorKmerFreq[DIM_VECTOR_KMER_FREQ];
}

Profile::Profile(int size){
    
    //throw
    
    Profile();
    _size = size;
}

std::string Profile::getProfileId() const{
    
    return _profileId;
}

void Profile::setProfileId(const std::string& id){
    
    _profileId = id;
}

const KmerFreq& Profile::at(int index) const{
    
    //throw
    
    return _vectorKmerFreq[index];
}

KmerFreq& Profile::at(int index){
    
    //throw
    
    return _vectorKmerFreq[index];
}

int Profile::getSize() const{
    
    return _size;
}

int Profile::getCapacity() const{
    
    return DIM_VECTOR_KMER_FREQ;
}

int Profile::findKmer(const Kmer& kmer, int initialPos, int finalPos) const{
    
    bool found;
    
    while(!found && initialPos <= finalPos){
        
        if(_vectorKmerFreq[initialPos] == kmer) 
            found = true;
        else
            initialPos ++;
    }
    
    if(!found) initialPos = std::string::npos;
    
    return initialPos;
}

int Profile::findKmer(const Kmer& kmer) const{
    
    return findKmer(kmer, 0, _size - 1);
}

std::string Profile::toString(){
    
    std::string kmer_str;
    
    kmer_str = _profileId + "\n" + std::to_string(_size) + "\n";
    
    for(int i = 0; i < _size; i++){
        
        kmer_str += _vectorKmerFreq[i].toString();
    }
    
    return kmer_str;
}


void Profile::SwapElements(int first, int second){
    
    //mirar si tmb son negativos
    if(first > _size || second > _size)
        throw std::out_of_range (std::string("first or second are positions") +
                                 "out of the range of the given array");
    
    KmerFreq intermediate;
    intermediate = _vectorKmerFreq[first];
    
    _vectorKmerFreq[first] = _vectorKmerFreq[second];
    
    _vectorKmerFreq[second] = intermediate;
    
}

void Profile::sort(){
    
    for (int left = 0 ; left < _size ; left++) {
        
        KmerFreq max = _vectorKmerFreq[left]; 
        int pos_max = left;
        
        for (int i = left + 1; i < _size ; i++){
            
            if (_vectorKmerFreq[i].getFrequency() > max.getFrequency()){
                max = _vectorKmerFreq[i];
                pos_max = i;
            }
            
            else if (_vectorKmerFreq[i].getFrequency() == max.getFrequency()){
                if(_vectorKmerFreq[i].getKmer().toString()
                        < max.getKmer().toString()){
                    
                    max = _vectorKmerFreq[i];
                    pos_max = i;
                }
            }
        }

        SwapElements(left, pos_max);
    }
}

void Profile::save(const char& fileName[]) const{
       
    std::ofstream outFile;
    
    outFile.open(fileName);
    if (!outFile) {
        throw std::ios_base::failure("Error opening output file");
    }
    outFile << MAGIC_STRING_T << std::endl;
    outFile << toString();

    if (!outFile) {
        throw std::ios_base::failure("Error writting to output file");
    }
}

void Profile::load(char fileName[]){
    
    std::ifstream inFile;
    
    inFile.open(fileName);
    if (!inFile) {
        throw std::ios_base::failure("Error opening input file");
    }
    
    std::string magic_str;
    inFile >> magic_str;
    if(magic_str != MAGIC_STRING_T)
        throw std::invalid_argument("An invalid magic string is" + 
                                    "found in the given file");
    
    std::getline(inFile, _profileId);
    inFile.ignore("\n");
    
    inFile >> _size;
    if(_size > DIM_VECTOR_KMER_FREQ)
        throw std::out_of_range("The number of kmers in the given file" +
                                "exceeds the maximun capacity");
    
    int freq;
    std::string nucleotide;
    
    for(int i = 0; i < _size; i++){
        
        inFile >> nucleotide;
        inFile >> freq;
        
        _vectorKmerFreq[i].setKmer(Kmer(nucleotide));
        _vectorKmerFreq[i].setFrequency(freq);
    }
    
    if (!inFile)
        throw std::ios_base::failure("Error reading from input file");
    
    inFile.close();
}

void Profile::append(KmerFreq kmerFreq){
    
    if(_size == DIM_VECTOR_KMER_FREQ)
        throw std::out_of_range("The array is full");
    
    int index = findKmer(kmerFreq.getKmer());
    if(index != -1){
        int freq = _vectorKmerFreq[index].getFrequency() 
                   + kmerFreq.getFrequency();
        _vectorKmerFreq[index].setFrequency(freq);
    }
    else{
        _vectorKmerFreq[_size] = kmerFreq;
        _size++;
    }
}

void Profile::normalize(const std::string& validNucleotides){
    
    //Normalize each Kmer
    for(int i = 0; i < _size; i++){
        
        _vectorKmerFreq[i].getKmer().normalize(validNucleotides);
    }
    
    int i = 1;
    
    // Loop to traverse the kmers in array from position 1 to position nElements-1
    while(i < _size){
        
        // index = Position of array[i].getKmer() in the subarray that begins
        //         at position 0 and ends at position i-1
        int index = findKmer(_vectorKmerFreq[i], 0, i-1);
        
        // If array[i].getKmer() was found in the the subarray from 0 to i-1 
        if(index != std::string::npos){
            
            // Accumulate the frequencies of the kmers at positions 
            //    index and i in the kmer at position index
            int freq = _vectorKmerFreq[i].getFrequency() 
                       + _vectorKmerFreq[index].getFrequency();
            _vectorKmerFreq[index].setFrequency(freq);
            
            // Delete from the array, the kmer at position i
            deletePos(i);
        }
        
        else i++;
    }
}

void Profile::deletePos(int pos){
    
    if(pos < 0 || pos >= _size)
        throw std::out_of_range( std::string( "pos is not in the range")
                                       + "from 0 to nElements-1");
    
    
    for(int i = pos; i < _size - 1; i++)
        _vectorKmerFreq[i] = _vectorKmerFreq[i + 1];
    
    _size--;
}

void Profile::zip(bool deleteMissing, int lowerBound){
    
    int i = 0;
    
    while(i < _size){
        
        if(_vectorKmerFreq[i].getFrequency() <= lowerBound){
            deletePos(i);
        }
        else if(deleteMissing){
            
            Kmer Kmer_delete = _vectorKmerFreq[i].getKmer();
            
            if(Kmer_delete.ThereIsMissingNucleotide()){
                deletePos(i);
            }
            else i++;
        }
        else i++;
    }
}

void Profile::join(const Profile& profile){
    
    for(int i = 0; i < profile.getSize(); i++){
        append(profile.at(i));
    }
}