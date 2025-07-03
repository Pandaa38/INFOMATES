/*
 * Metodología de la Programación: Kmer2
 * Curso 2023/2024
 */

/** 
 * @file Profile.cpp
 * @author Juan Reche Aguilar
 * 
 * Created on 29 January 2023, 11:00
 */


#include "Profile.h"
#include <fstream>

const std::string Profile::MAGIC_STRING_T="MP-KMER-T-1.0";

Profile::Profile():_profileId("unknown"),_size(0){
    
    this -> allocate(INITIAL_CAPACITY);
}

Profile::Profile(int size) : _profileId("unknown"), _size(size){
    
    if(size < 0)
        throw std::out_of_range("Profile(int): invalid size for a profile");
    
    this -> allocate(size);
}

Profile::Profile(const Profile& orig){
    
    this -> copy(orig);
}

Profile::~Profile(){
    this -> dellocate();
}

Profile& Profile::operator=(const Profile& orig){
    
    if(&orig != this){
        this ->dellocate();
        this ->copy(orig);
    }
    
    return *this;
}

const std::string& Profile::getProfileId() const{
    
    return _profileId;
}

void Profile::setProfileId(const std::string& id){
    
    _profileId = id;
}

const KmerFreq& Profile::at(int index) const{
    
    if(index < 0 || index >= _size)
        throw std::out_of_range("const at(int): Invalid position");
    
    return _vectorKmerFreq[index];
}

KmerFreq& Profile::at(int index){
    
    if(index < 0 || index >= _size)
        throw std::out_of_range("at(int): Invalid position");
    
    return _vectorKmerFreq[index];
}

int Profile::getSize() const{
    
    return _size;
}

int Profile::getCapacity() const{
    
    return _capacity;
}

double Profile::getDistance(const Profile& otherProfile) const{
    
    int size_this = _size, size_other = otherProfile.getSize();
    
    if(size_this == 0 || size_other == 0)
        throw std::invalid_argument(std::string("getDistance(const Profile& ") +
                            "otherProfile): the profile is empty");
    
    double dist = 0.0;
        
    for (int i = 0; i < size_this; i++){
                
        int rank = otherProfile.findKmer(at(i).getKmer());
        if (rank == -1) // It is not found in otherProfile
            rank = size_other;
        
        dist += abs(i - rank);
    }
    
    dist /= (size_this * size_other);
    
    return dist;
}

int Profile::findKmer(const Kmer& kmer, int initialPos, int finalPos) const{
    
    bool found = false;
    
    while(!found && initialPos <= finalPos){
        
        if(this->at(initialPos).getKmer().toString() == kmer.toString()) 
            found = true;
        else
            initialPos ++;
    }
    
    if(!found) initialPos = -1;
    
    return initialPos;
}

int Profile::findKmer(const Kmer& kmer) const{
    
    return findKmer(kmer, 0, _size - 1);
}

std::string Profile::toString() const{
    
    std::string kmer_str;
    //kmer_str = MAGIC_STRING_T + "\n";
    kmer_str += _profileId + "\n" + std::to_string(_size) + "\n";
    
    for(int i = 0; i < _size; i++){
        
        kmer_str += _vectorKmerFreq[i].toString();
        kmer_str += "\n";
    }
    
    return kmer_str;
}

void Profile::SwapElements(int first, int second){
    
    if(first > _size || second > _size || first < 0 || second < 0)
        throw std::out_of_range (std::string("SwapElements: first or second ") +
                           "are positions out of the range of the given array");
    
    KmerFreq intermediate;
    intermediate = _vectorKmerFreq[first];
    
    _vectorKmerFreq[first] = _vectorKmerFreq[second];
    
    _vectorKmerFreq[second] = intermediate;
    
}

void Profile::quickSort(int first, int last){ 
    
    const int SelctionTheBest = 10;
    
    bool mayselection = (first - last) <= SelctionTheBest;
    
    if(mayselection){
        selectionSort();
    }
    else{
        
        int pos_pivote;

        if (first < last) {

            pos_pivote = split(first, last);

            quickSort (first, pos_pivote - 1); // Ordena primera mitad
            quickSort (pos_pivote + 1, last); // Ordena segunda mitad
        }
    }
}

int Profile::split(int first, int last){
    
    int left, right;
    KmerFreq value_pivote = _vectorKmerFreq[first];
    
    left = first + 1; // left go foward
    right = last; // dcha go back
    
    while (left <= right){
        while (left <= right && isBiggerEqual(value_pivote,_vectorKmerFreq[right]))
            left++;
        
        while (left <= right && isBiggerEqual(_vectorKmerFreq[right],value_pivote))
            right--;
        
        if (left < right) {
            
            SwapElements(left, right);
            
            right--;
            left++;
        }
    }
    
    SwapElements(first, right);
        
    return right;
}

void Profile::selectionSort(){
    
    for (int left = 0 ; left < _size ; left++) {
        
        KmerFreq max = _vectorKmerFreq[left]; 
        int pos_max = left;
        
        for (int i = left + 1; i < _size ; i++){
            
            if(isBigger(_vectorKmerFreq[i],max)){
                max = _vectorKmerFreq[i];
                pos_max = i;
            }
            
        }

        SwapElements(left, pos_max);
    }
}

//Hacer sobrecarga(si hay tiempo)
bool Profile::isBigger(const KmerFreq& large, const KmerFreq& small) const{
    
    bool bigger = false;
    
    if(small.getFrequency() < large.getFrequency())
        bigger = true;
    else if(small.getFrequency() == large.getFrequency()){
        
        if(small.getKmer().toString() > large.getKmer().toString())
            bigger = true;
    }
    return bigger;
}

bool Profile::isBiggerEqual(const KmerFreq& large, const KmerFreq& small) const{
    
    bool bigger_equal = isBigger(large,small);
    
    if(!bigger_equal){
        
        if(large.getFrequency() == small.getFrequency())
            bigger_equal = true;
        
    }
    return bigger_equal;
}

void Profile::sort(){
    
    quickSort(0, _size-1);
}

void Profile::save(const char fileName[]) const{

    std::ofstream outFile;
    outFile.open(fileName);
    
    if (!outFile) {
        throw std::ios_base::failure("save: Error opening output file");
    }
    outFile << MAGIC_STRING_T << std::endl;
    outFile << toString();
    
    outFile.close();
    
    if (!outFile) {
        throw std::ios_base::failure("save: Error writting to output file");
    }
}

void Profile::load(const char fileName[]){
   
    dellocate();
    
    std::ifstream inFile;
    inFile.open(fileName);
    
    if (!inFile){
        throw std::ios_base::failure("load: Error opening input file");
    }
    
    std::string magic_str;
    inFile >> magic_str;
    inFile.ignore();
    
    if(magic_str != MAGIC_STRING_T){
        inFile.close();
        throw std::invalid_argument(std::string("load: An invalid magic string")
                                        + ("is found in the given file"));
    }
    
    std::getline(inFile, _profileId);
        
    if(!inFile){
        inFile.close();
        throw std::ios_base::failure("load: Error reading from input file: id");
    }
    
    int size;
    inFile >> size;
        
    if(!inFile){
        inFile.close();
        throw std::ios_base::failure("load: Error reading from input file: size");
    }
    if(_size < 0){
        inFile.close();
        throw std::out_of_range(std::string("load: The number of kmers in ")+
                ("the given file exceeds the maximun capacity or is negative"));
    }
    
    int freq;
    std::string nucleotide;
    KmerFreq next_kmerfreq;
    
    for(int i = 0; i < size; i++){
        
        inFile >> nucleotide;
        if(!inFile){
            inFile.close();
            throw std::ios_base::failure("load: Error reading from input file: nucleotide");
        }
        
        inFile >> freq;
        if(!inFile){
            inFile.close();
            throw std::ios_base::failure("load: Error reading from input file: freq");
        }
        
        next_kmerfreq.setKmer(Kmer(nucleotide));
        next_kmerfreq.setFrequency(freq);
        
        append(next_kmerfreq);
    }
    
    inFile.close();
    
    if(!inFile)
        throw std::ios_base::failure("load: Error reading from input file");
}

void Profile::append(const KmerFreq& kmerFreq){
    
    int index = findKmer(kmerFreq.getKmer());
    
    if(index != -1){
        
        int freq = _vectorKmerFreq[index].getFrequency()
                                                    + kmerFreq.getFrequency();
        _vectorKmerFreq[index].setFrequency(freq);
    }
    else{
        
        if(_size >= _capacity)
            this -> rellocate();
    
        _vectorKmerFreq[_size] = kmerFreq;
        _size++;
    }
}

void Profile::normalize(const std::string& validNucleotides){
    
    //Normalize each Kmer
    Kmer normalized;
    for(int i = 0; i < _size; i++){
        
        normalized = _vectorKmerFreq[i].getKmer();
        normalized.normalize(validNucleotides);
        _vectorKmerFreq[i].setKmer(normalized);
    }
    
    int i = 1;
    // Loop to traverse the kmers in array from position 1 to position nElements-1
    while(i < _size){
        
        // index = Position of array[i].getKmer() in the subarray that begins
        //         at position 0 and ends at position i-1
        int index = findKmer(_vectorKmerFreq[i].getKmer(), 0, i-1);
        
        // If array[i].getKmer() was found in the the subarray from 0 to i-1 
        if(index != -1){
            
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
        throw std::out_of_range( std::string("deletePos: pos is not in the")
                                       + "range from 0 to nElements-1");
    
    
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

//Private Methods
void Profile::allocate(int nElements){
    
    if(nElements < 0)
        throw std::invalid_argument("allocate: nElements <= 0");
    
    _vectorKmerFreq = new KmerFreq[nElements];
    _capacity = nElements;
}

void Profile::dellocate(){
    
    delete [] _vectorKmerFreq;
    _vectorKmerFreq = nullptr;
    
    _size = 0;
    _capacity = 0;
}

void Profile::rellocate(int increase){
    
    KmerFreq* temp = new KmerFreq [_capacity + increase];
    
    /*
    for(int i = 0; i < _size; i++){
        temp[i] = _vectorKmerFreq[i];
    }
    */
    
    copy_kmer(_vectorKmerFreq, temp, _size);
    
    delete [] _vectorKmerFreq;
    _vectorKmerFreq = temp;
    _capacity += increase;
}

void Profile::copy(const Profile &otherProfile){
    
    _profileId = otherProfile.getProfileId();
    _size = otherProfile.getSize();
    _capacity = otherProfile.getCapacity();
    
    this -> allocate(_capacity);
    
    copy_kmer(otherProfile._vectorKmerFreq, _vectorKmerFreq, _size);
    
    /*
    for(int i = 0; i < _size; i++){
        
        _vectorKmerFreq[i] = otherProfile.at(i);
    }
    */
}

