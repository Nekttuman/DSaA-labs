#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

#include "Algo.h"

int main() {


    std::cout << """1. HA\n"
                 "2. RLE\n"
                 "3. LZ78\n"
                 "4. BWT\n"
                 "5. MTF\n"
                 "6. AC\n"
                 "7. PPM\n"
                 "\ncode: """;
    int num;
    std::cin >> num;
    std::cout << "use tmp result or clear dataset? (0/1)  ";
    int ans;
    std::cin >> ans;

    std::string path = ans ? "../enwik8.txt" : "../tmpres.txt";


    std::fstream enwik(path, std::ios_base::in);
    if (!enwik.is_open()){
        std::cout<<"file not opened";
        throw;
    }

    ////////////////////////////

    float dataset_size_koef = 1;

    ////////////////////////////


    enwik.seekg(0, std::ios::end);
    size_t size = enwik.tellg() * (ans ? dataset_size_koef : 1);
    std::string buffer(size, ' ');
    enwik.seekg(0);
    enwik.read(&buffer[0], size);


    std::fstream tmpResFile("../tmpres.txt", std::ios_base::out);
    if (!tmpResFile.is_open()){
        std::cout<<"file not opened";
        throw;
    }
    std::string tmpRes;

    auto start = std::chrono::high_resolution_clock::now();
    switch (num) {
        case 1: {
            tmpRes = Algo::HA_Compress(buffer);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "1. HA time: " << duration.count() << "\n";
            break;
        }
        case 2: {

            tmpRes = Algo::RLE_Compress(buffer);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "2. RLE time: " << duration.count() << "\n";
            break;
        }
        case 3: {

            tmpRes = Algo::LZ78_Compress(buffer);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "3. LZ78 time: " << duration.count() << "\n";
            break;
        }
        case 4: {

            tmpRes = Algo::BWT_Compress(buffer);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "4. BWT time: " << duration.count() << "\n";

            break;
        }
        case 5: {

            tmpRes = Algo::MTF_Compress(buffer);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "5. MFT time: " << duration.count() << "\n";

            break;
        }
        case 6: {

            tmpRes = Algo::AC_Compress(buffer);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "6. AC time: " << duration.count() << "\n";
            break;
        }
        case 7: {

            tmpRes = Algo::ppm_encode(buffer);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "7. ppm time: " << duration.count() << "\n";

            break;
        }
    }

    tmpResFile<<tmpRes;

    return 0;
}
