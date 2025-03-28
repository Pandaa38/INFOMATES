/*
 * Metodología de la Programación: Kmer5
 * Curso 2023/2024
 */

/** 
 * @file KmerCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 22 December 2023, 10:00
 */

#include <random>
#include <fstream>
#include "KmerCounter.h"

using namespace std;

/**
 * DEFAULT_VALID_NUCLEOTIDES is a c-string that contains the set of characters
 * that will be considered as valid nucleotides. 

 * The constructor of the class KmerCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const KmerCounter::DEFAULT_VALID_NUCLEOTIDES="ACGT";

KmerCounter::KmerCounter(int k, std::string validNucleotides)
: _k(k), _validNucleotides(validNucleotides), 
  _allNucleotides(Kmer::MISSING_NUCLEOTIDE + validNucleotides)
{
    
    int nrow = getNumRows();
    int ncol = getNumCols();
   
    allocate(nrow, ncol);
    initFrequencies();    
} 

KmerCounter::KmerCounter(const KmerCounter& orig){
    copy(orig);
}

KmerCounter::~KmerCounter(){
    dellocate();
}

int KmerCounter::getNumNucleotides() const{
    return _allNucleotides.length();
}

int KmerCounter::getK() const{
    return _k;
}

int KmerCounter::getNumKmers() const{
    return pow(_k, _allNucleotides.length());
}

int KmerCounter::getNumberActiveKmers() const{
    
    int nak = 0;
    
    for(int i = 0; i < getNumRows(); i++){
        for(int j = 0; j < getNumCols(); j++){
            if((*this)(i,j) > 0)
                nak++;
        }
    }
    return nak;
}

std::string KmerCounter::toString() const{
    string outputString = _allNucleotides + " " + to_string(_k) + "\n";
    
    for(int row=0; row<this->getNumRows(); row++){
        for(int col=0; col<this->getNumCols(); col++){
            outputString += to_string((*this)(row,col)) + " ";
        }
        outputString += "\n";
    }
    
    return outputString;
}

void KmerCounter::increaseFrequency(const Kmer& kmer, int frequency){
    
    if(kmer.thereIsInvalidNucleotide(_allNucleotides))
        throw std::invalid_argument("increaseFrequency: invalid kmer");

    int row = -1, col = -1;
    getRowColumn(kmer, row, col);
    
    _frequency[row][col] += frequency;
}

KmerCounter& KmerCounter::operator=(const KmerCounter& orig){
    
    if(&orig != this){
        this->copy(orig);
    }    
    return *this;
}

KmerCounter& KmerCounter::operator+=(const KmerCounter& kc){
    
    if(this->getK() != kc.getK() || _validNucleotides != kc._validNucleotides){
        throw std::invalid_argument(std::string("operator+=: the given") + 
              ("argument has a different set of nucleotides or a different K"));
    }
    
    for (int i = 0; i < getNumRows(); i++){
        for(int j = 0; j < getNumCols(); j++){
            
            (*this)(i,j) += kc(i,j);            
        }
    }
    
    return *this;
}

void KmerCounter::calculateFrequencies(const char* fileName){
    
    std::ifstream inFile;
    inFile.open(fileName);
    
    if(!inFile)
        throw std::ios_base::failure(std::string("calculateFrequencies: ")
                                        + "filename cannot be opened");
    
    this->initFrequencies();
    
    std::string genome;
    int total_used;
    
    inFile >> genome;
    total_used = genome.length() - _k  + 1;
    
    Kmer *kmerArray = new Kmer [total_used];
    
    for(int i = 0; i < total_used; i++){
        
        kmerArray[i] = Kmer(genome.substr(i, _k));
        kmerArray[i].normalize(_validNucleotides);
        
        increaseFrequency(kmerArray[i]);
    }
    
    delete [] kmerArray;
    inFile.close();
}

Profile KmerCounter::toProfile(){
    
    const int nActive = getNumberActiveKmers();
    Profile profile(nActive);
    
    bool finished = false;
    int nAdded = 0;
    
    for(int i = 0; i < getNumRows() && !finished; i++){
        for(int j = 0; j < getNumCols() && !finished; j++){
            
            if( (*this)(i,j) > 0){
                profile.at(nAdded).setFrequency((*this)(i,j));
                profile.at(nAdded).setKmer(this->getKmer(i,j));
                
                nAdded++;
                finished = nAdded >= nActive;
            }
        }
    }

    return profile;
}

void KmerCounter::allocate(int nrow, int ncol){
    
    //array 1D con array apuntado a pos
    _frequency = new int* [nrow];
    _frequency[0] = new int [nrow * ncol];
    
    for(int i = 1; i < nrow; ++i){
        _frequency[i] = _frequency[i-1]+ncol;        
    }
    
//    _frequency = new int* [nrow];
//    for(int i=0; i < nrow; ++i){
//        _frequency[i] = new int [ncol];
//    }
}

void KmerCounter::dellocate(){
    
    if (_frequency != nullptr) {
        delete[] _frequency[0];
        delete[] _frequency;
        _frequency = nullptr;
    }
    
//    for(int i = 0; i < getNumRows(); ++i){
//        delete [] _frequency[i];
//    }
//    delete [] _frequency;
    
}

void KmerCounter::copy(const KmerCounter& other){
    
    if (_frequency != nullptr) {
        dellocate();
    }
    _k = other._k;
    _validNucleotides = other._validNucleotides;
    _allNucleotides = other._allNucleotides;
    
    allocate(other.getNumRows(),other.getNumCols());
    
    for(int i = 0; i < getNumRows(); i++){
        for(int j = 0; j < getNumCols(); j++){
            (*this)(i,j) = other(i,j);
        }
    }
}

int KmerCounter::getNumRows() const{
    int rp = ( _k + 1)/2;

    return pow(_allNucleotides.length(),rp);
}

int KmerCounter::getNumCols() const{
    int lp = _k - ( _k + 1)/2;

    return pow(_allNucleotides.length(),lp);
}

int KmerCounter::getIndex(const std::string& kmer) const{
    int index = 0;
    int base = 1;

    for (size_t i = 0; i < kmer.size(); i++) {
        size_t pos = _allNucleotides.find(kmer[kmer.size()-i-1]);
        if (pos == string::npos)
            return -1;
        index += pos * base;
        base *= _allNucleotides.size();
    }
    return index;
}

string KmerCounter::getInvertedIndex(int index, int nCharacters) const {
    string result(nCharacters, Kmer::MISSING_NUCLEOTIDE);

    for (int i = result.size(); i > 0; i--) {
        result[i - 1] = _allNucleotides[index % _allNucleotides.size()];
        index = index / _allNucleotides.size();
    }
    return result;
}

void KmerCounter::getRowColumn(const Kmer& kmer, int& row, int& column) const{
    
    int rp = ( _k + 1)/2;
    
    row = this->getIndex(kmer.toString().substr(0,rp));
    column = this->getIndex(kmer.toString().substr(rp));
}

Kmer KmerCounter::getKmer(int row, int column) const{
    
    if(row < 0 || column < 0 || row >= getNumRows() || column >= getNumCols()){
        throw std::invalid_argument(std::string("getKmer: the given row or") +
                ("column are out of the correct bounds"));
    }
    
    int rp = ( _k + 1)/2;
    int lp = _k - ( _k + 1)/2;
    
    std::string genome = getInvertedIndex(row, rp)+getInvertedIndex(column, lp);
    
    Kmer kmer(genome);
    
    return kmer;
}

void KmerCounter::initFrequencies(){
        
    for(int i = 0; i < getNumRows(); i++){
        for(int j = 0; j < getNumCols(); j++){
            (*this)(i,j) = 0;
        }
    }    
}

const int& KmerCounter::operator()(int row, int column) const{
    return _frequency[row][column];
}
int& KmerCounter::operator()(int row, int column){
    return _frequency[row][column];
}