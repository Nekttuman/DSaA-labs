#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>

const std::string pref = "D://repos/Algosee/algos_lab_3/input_texts/";
const std::string DECR_FILE_PATH = pref + "decrypted_text.txt";
const std::string SOURCE_PATH = pref + "source.txt";
const std::string ENCR_FILE_PATH = pref + "encrypted_text.txt";


void make_encryption(){
    std::fstream in;
    in.open(SOURCE_PATH, std::ios_base::in);
    std::fstream out(ENCR_FILE_PATH,std::ios_base::out);

    std::map<char, char> encr_table;
    std::vector<char> source_alphabet;

    for (char symbol = ' '; !in.eof();){
        //in >> symbol;
        symbol = in.get();
        if (std::find(source_alphabet.begin(), source_alphabet.end(), symbol) == source_alphabet.end())
            source_alphabet.push_back(symbol);
    }
    std::sort(source_alphabet.begin(), source_alphabet.end());

    unsigned int alp_size = source_alphabet.size();
    for (int i = 0; i < alp_size; ++i) {
        encr_table.insert(std::pair<char, char>(source_alphabet[i],source_alphabet[alp_size-i]));
    }

    in.close();
    in.open(SOURCE_PATH, std::ios_base::in);

    for (char symbol = ' '; !in.eof();) {
        in >> symbol;
        out << encr_table[symbol];
    }



    out.close();
}



int main() {
    make_encryption();
    return 0;
}
