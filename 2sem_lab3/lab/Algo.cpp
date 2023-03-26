#include "Algo.h"

namespace Algo {
    string RLE_Compress(const string &input) {
        string result;

        for (size_t i = 0; i < input.length(); ++i) {
            int count = 1;
            while (i < input.length() - 1 && input[i] == input[i + 1]) {
                ++count;
                ++i;
            }
            result += to_string(count) + input[i];
        }

        return result;
    }

    string LZ78_Compress(const string &input) {
        unordered_map<string, int> dictionary;
        string result;
        string current;

//        int i = 0;
        for (char c: input) {
            string next = current + c;
            if (dictionary.find(next) != dictionary.end()) {
                current = next;
            } else {
                result += to_string(dictionary[current]) + c;
                dictionary[next] = dictionary.size();
                current = "";
            }
//            std::cout<<i++<<" ";
        }

        if (!current.empty()) {
            result += to_string(dictionary[current]);
        }

        return result;
    }

    string BWT_Compress(const string &input) {
        vector<string> rotations;
        rotations.reserve(input.length());
        string bwt;

        for (size_t i = 0; i < input.length(); ++i) {
            rotations.push_back(input.substr(i) + input.substr(0, i));
        }

        sort(rotations.begin(), rotations.end());

        for (const auto &rotation: rotations) {
            bwt += rotation.back();
        }

        return bwt;
    }

    string MTF_Compress(const string &input_str) {
        string compressed_str;
        list<char> dictionary;
        for (int i = 0; i < 256; i++) {
            dictionary.push_back(char(i));
        }
        for (char ch: input_str) {
            auto it = find(dictionary.begin(), dictionary.end(), ch);
            int idx = distance(dictionary.begin(), it);
            compressed_str += to_string(idx) + ",";
            dictionary.erase(it);
            dictionary.push_front(ch);
        }
        compressed_str.pop_back();
        return compressed_str;
    }

    struct Node {
        char c;
        int freq;
        Node *left;
        Node *right;

        Node(char c, int freq, Node *left = nullptr, Node *right = nullptr)
                : c(c), freq(freq), left(left), right(right) {}
    };

    struct CompareNodes {
        bool operator()(Node *a, Node *b) {
            return a->freq > b->freq;
        }
    };

    void encode(Node *root, const string &str, unordered_map<char, string> &huffmanCode) {
        if (root == nullptr) {
            return;
        }
        if (!root->left && !root->right) {
            huffmanCode[root->c] = str;
        }
        encode(root->left, str + "0", huffmanCode);
        encode(root->right, str + "1", huffmanCode);
    }

    string buildHuffmanTree(const string &text, unordered_map<char, int> &freq) {
        priority_queue<Node *, vector<Node *>, CompareNodes> pq;
        for (auto &pair: freq) {
            pq.push(new Node({pair.first, pair.second, nullptr, nullptr}));
        }
        while (pq.size() != 1) {
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();
            int sum = left->freq + right->freq;
            pq.push(new Node({'\0', sum, left, right}));
        }
        unordered_map<char, string> huffmanCode;
        encode(pq.top(), "", huffmanCode);

        string encoded = "";
        for (char ch: text) {
            encoded += huffmanCode[ch];
        }

        std::string codeTableString;
        for (const auto &pair: huffmanCode) {
            codeTableString += pair.first;
            codeTableString += pair.second;
        }

        return codeTableString + encoded;
    }

    string HA_Compress(const string &text) {
        unordered_map<char, int> freq;
        for (char ch: text) {
            freq[ch]++;
        }
        return buildHuffmanTree(text, freq);
    }

    string AC_Compress(const string &text) {
        long double low = 0;
        long double high = 1;

        long double range = 1;
        int num_chars = 256;

        vector<long double> probabilities(num_chars, 0);
        for (char c: text) {
            probabilities[c] += (long double) 1 / (long double) text.length();
        }
        for (int i = 1; i < num_chars; i++) {
            probabilities[i] += probabilities[i - 1];
        }

        for (char c: text) {
            low = low + probabilities[c - 1] * range;
            high = low + (probabilities[c] - probabilities[c - 1]) * range;
            range = high - low;
        }

        return to_string((low + high) / 2);
    }

    string ppm_encode(const string &input) {
        map<string, int> freq;
        string output = "";

        for (int i = 0; i < input.length(); i++) {
            string context = "";
            int max_order = min(i, 5);
            for (int j = 1; j <= max_order; j++) {
                context = input.substr(i - j, j);
                if (freq.count(context)) {
                    break;
                }
            }

            if (freq.count(context)) {
                char best_char = 0;
                int best_freq = 0;
                for (char c = 0; c < 128 && c > 0; c = c + 1) {
                    string symbol = context + c;
                    if (freq.count(symbol) && freq[symbol] > best_freq) {
                        best_char = c;
                        best_freq = freq[symbol];
                    }
                }
                output += best_char;
                freq[context + best_char]++;
            } else {
                output += input[i];
                freq[string(1, input[i])]++;
            }
        }

        return output;
    }
}