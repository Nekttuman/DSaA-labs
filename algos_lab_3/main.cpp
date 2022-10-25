#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>


const std::string pref = "../input_texts/";
const std::string DECR_FILE_PATH = pref + "decrypted_text.txt";
const std::string SOURCE_PATH = pref + "source.txt";
const std::string ENCR_FILE_PATH = pref + "encrypted_text.txt";
const std::string SOURCE_CODING_TABLE_PATH = pref + "source_table.txt";
const std::string FREQ_TABLE_PATH = pref + "freq_table.txt";


class {
    std::vector<char> source_alphabet;
    std::map<char, char> encr_table;

    void get_source_alph() {
        std::fstream in(SOURCE_PATH, std::ios_base::in);
        if (!in.is_open()) {
            std::cout << "Files not open";
            return;
        }

        for (char symbol = ' '; !in.eof();) {
            in >> std::noskipws >> symbol;
            if (std::find(source_alphabet.begin(), source_alphabet.end(), symbol) == source_alphabet.end()
                && symbol != '\0' && symbol != -1 && symbol != '\n')
                source_alphabet.push_back(symbol);
        }

        std::sort(source_alphabet.begin(), source_alphabet.end());
        in.close();

        for (auto i: source_alphabet)
            std::cout<<i<<" ";
    }

    void set_encr_table(short mode = 1) {
        unsigned int alp_size = source_alphabet.size();
        for (int i = 0; i < alp_size; ++i) {
            encr_table.insert(std::pair<char, char>(source_alphabet[i], source_alphabet[alp_size - i - 1]));
        }
        encr_table.insert(std::pair<char, char>('\n', '\n'));
    }

    void encrypt_source_text() {
        std::fstream out(ENCR_FILE_PATH, std::ios_base::out);
        std::fstream in(SOURCE_PATH, std::ios_base::in);
        std::noskipws(in);
        for (char symbol = ' '; !in.eof();) {
            in >> symbol;
            out << encr_table[symbol];
        }

        out.close();
        in.close();
    }

    void fwrite_encr_table() {
        std::fstream file(SOURCE_CODING_TABLE_PATH, std::ios_base::out);
        for (auto item: encr_table)
            file << item.first << " : " << item.second << "\n";
    }

public:
    void operator()(short encr_mode = 1) {
        get_source_alph();
        set_encr_table(encr_mode);
        encrypt_source_text();
        fwrite_encr_table();
    }
} make_encryption;

class {
    std::map<char, int> freq_table;
    std::map<char, int> standard_freq_table;
    std::map<char,char> decode_table;


    void frequency_count(){
        std::fstream in(ENCR_FILE_PATH, std::ios_base::in);

        for (char ch = -1; !in.eof(); in>>std::noskipws>>ch){
            if (ch != -1)
                ++freq_table[ch];
        }
        in.close();

        for(auto s: freq_table)
            std::cout<<s.first<<" : "<<s.second<<'\n';
    }

    void get_standard_freq_table(){
        std::fstream in(FREQ_TABLE_PATH, std::ios_base::in);

        char ch;
        int freq;
        while (!in.eof()){
            in>> ch>>freq;
            standard_freq_table.insert(std::pair<char, int>(ch, freq));
        }
        standard_freq_table.insert(std::pair<char, int> (' ', 200000));

    }

    void create_decode_table(){
        auto _freq_table = freq_table;
        auto _standard_freq_table = standard_freq_table;

        unsigned int s_freq_t_len = standard_freq_table.size();
        for (int i = 0; i<s_freq_t_len; ++i){
            auto s_mx = std::max_element(_standard_freq_table.begin(), _standard_freq_table.end(),[] (const std::pair<char, int> & p1, const std::pair<char, int> & p2) {
                return p1.second < p2.second;
            });
            auto mx = std::max_element(_freq_table.begin(), _freq_table.end(), [] (const std::pair<char, int> & p1, const std::pair<char, int> & p2) {
                return p1.second < p2.second;
            });
            decode_table.insert(std::pair<char,char>(mx->first, s_mx->first));


            //std::cout<<mx->first<<" : "<< s_mx->first<<"\n";

            _freq_table.erase(mx);
            _standard_freq_table.erase(s_mx);
        }
        decode_table.insert(std::pair<char,char>('\n','\n'));
    }

    void try_decode(){
        std::fstream in(ENCR_FILE_PATH, std::ios_base::in);
        std::fstream out(DECR_FILE_PATH, std::ios_base::out);


        for (char ch = ' '; !in.eof(); in>>std::noskipws>>ch){
            out<<decode_table[ch];
        }

        in.close();
        out.close();
    }
public:
    void operator ()(){
            frequency_count();
            get_standard_freq_table();
            create_decode_table();
            try_decode();
    }
} decryption;

int main() {
    make_encryption();
    decryption();
    return 0;
}
