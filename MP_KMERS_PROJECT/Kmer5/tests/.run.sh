touch tests//.timeout
CMD="valgrind --leak-check=full /home/juan/Documentos/MyProgram/MP_KMERS_PROJECT/Kmer5/./dist/LEARN/GNU-Linux/LEARN  -p 'homo sapiens' -o tests/output/human_chr6.prf ../Genomes/human_chr6_s60000_l500000.dna 1> tests//.out16 2>&1"
eval $CMD
rm tests//.timeout
