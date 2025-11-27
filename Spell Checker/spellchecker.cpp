// #include <fstream>
// #include <regex>
// #include <vector>
// #include <iostream>
// #include <unordered_map>
// #include <unordered_set>
// #include <vector>
// #include <cctype>
// #include <string>
// #include <fstream>


// struct word {
//     std::string text;
//     int line;
//     int column;
// };

// bool read_words(const std::string input_file_name,std::vector<word>& words)
// {
//     std::ifstream input_file(input_file_name);
//     if (input_file.fail()) {
//         return false;
//     }
//     std::regex reg_exp("[a-zA-Z]+");
//     std::smatch match;
//     std::string text;
//     int line = 0;
//     int column = 0;
//     while (std::getline(input_file, text)) {
//         ++line;
//         column = 1;
//         while (std::regex_search(text, match, reg_exp)) {
//             column += match.position();
//             words.push_back({match.str(), line, column});
//             column += match.length();
//             text = match.suffix().str();
//         }
//     }
//     return true;
// }

// //soundex generator function
// std::string soundex_generator(const std::string& token){
//     if(token.empty()){
//         return "";
//     }

//     //Convert the word to upper case for uniformity
//     std::string upperToken;
//     for(char c : token){
//         upperToken += toupper(c);
//     }

//     std::string soundex = "";

//     //Retain the First Letter
//     soundex += upperToken[0];

//     //Create a dictionary which maps letters to respective soundex codes. Vowels and 'H', 'W' and 'Y' will be represented by '.'
//     std::unordered_map<std::string, std::string> dictionary = {
//         {"BFPV", "1"},
//         {"CGJKQSXZ", "2"},
//         {"DT", "3"},
//         {"L", "4"},
//         {"MN", "5"},
//         {"R", "6"},
//         {"AEIOUHWY", "."}
//         };

//     //Encode as per the dictionary
//     for(size_t i = 1; i < upperToken.size(); i++){
//         char ch = upperToken[i];
//         std::string code = " ";

//         for(auto& pair : dictionary){
//             if(pair.first.find(ch) != std::string::npos){
//                 code = pair.second;
//                 break;
//             }
//         }

//         if(!code.empty() && code != "."){
//             if(code != std::string(1, soundex.back())){
//                 soundex += code;
//             }
//         }
//     }

//     if(soundex.size() > 7){
//         soundex = soundex.substr(0, 7);
//     } else{
//         soundex.append(7 - soundex.size(), '0');
//     }
//     return soundex;
// }

// //Read file and create a dictionary with simlar soundex words
// bool buildSoundexDictionary(const std::string& fileName, std::unordered_map<std::string, std::vector<std::string>>& s_dictionary){
//     std::ifstream file(fileName);
//     if(file.fail()) {
//         std::cerr << "Unable to open file: " << fileName << "\n";
//         return false;
//     }

//     std::string word;
//     while(file >> word){
//         std::string code = soundex_generator(word);
//         s_dictionary[code].push_back(word);
//     }
//     return true;
// }

// std::unordered_set<std::string> loadDictionary(const std::string& dictionary_File){
//     std::unordered_set<std::string> dictionary;
//     std::ifstream file(dictionary_File);
//     if(file.fail()){
//         std::cerr << "Unable to open dictionary: " << dictionary_File;
//         return dictionary;
//     }

//     std::string word;
//     while(file >> word){
//         for(auto& w : word){
//             w = tolower(w);
//             dictionary.insert(word);
//         }
//     }
//     return dictionary;
// }

// std::string suggest_words(const std::string& word, const std::unordered_map<std::string, std::vector<std::string>> s_dictionary){
//     std::string code = soundex_generator(word);
//     auto it = s_dictionary.find(code);
//     if(it != s_dictionary.end()){
//         std::string suggestions = "Suggested words for " + word + ": ";
//         for(const auto& w : it -> second){
//             suggestions += w + " ";
//         }
//         return suggestions;
//     }
//     return "No suggestions for " + word + ".";
// }

// //driver code
// int main(){
//     // std::unordered_map<std::string, std::vector<std::string>> dictionary;
//     // if(!buildSoundexDictionary("words.txt", dictionary)){
//     //     return 1; // falla al abrir
//     // }

//     // // Print some examples
//     // for(const auto& [code, words] : dictionary){
//     //     std::cout << code << ": ";

//     //     int count = 0;
//     //     for(const auto& w : words){
//     //         if(count >= 10){
//     //             break;
//     //         }
//     //         if(count == 0){
//     //             std::cout << w;
//     //         } 
//     //         std::cout << ", " << w;
//     //         count++;
//     //     }
//     //     std::cout << std::endl;
//     // }

//     // //Read words
//     // std::string file_name = "tooinkle.txt";
//     // std::vector<word> words;

//     // if (read_words(file_name, words)) {
//     //     for (word w : words) {
//     //         std::cout << w.text << "  (line " << w.line
//     //             << ", column " << w.column << ")\n";
//     //     }
//     // } else {
//     //     std::cout << "Unable to read file: "
//     //         << file_name << "\n";
//     // }

//     // std::cout << soundex_generator("Bangalore") << std::endl;
//     // std::cout << soundex_generator("GeeksforGeeks") << std::endl;

//     std::cout << "-------------------------------------------------" << std::endl;
//     auto dict = loadDictionary("words.txt");

//     // 2. Construir diccionario Soundex
//     std::unordered_map<std::string, std::vector<std::string>> s_dictionary;
//     buildSoundexDictionary("words.txt", s_dictionary);

//     // 3. Leer archivo de prueba
//     std::vector<word> words;
//     if(!read_words("tooinkle.txt", words)){
//         std::cerr << "Error leyendo tooinkle.txt\n";
//         return 1;
//     }

//     // 4. Validar cada palabra
//     for(const auto& w : words){
//         std::string lowerWord = w.text;
//         for(auto& c : lowerWord) c = tolower(c);

//         if(dict.find(lowerWord) == dict.end()){
//             // No está en el diccionario exacto → usar Soundex
//             std::cout << "Palabra no reconocida: " << w.text
//                       << " (linea " << w.line << ", columna " << w.column << ")\n";
//             std::cout << suggest_words(w.text, s_dictionary) << "\n";
//         }
//     }
//     return 0;
// }


#include <fstream>
#include <regex>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cctype>
#include <string>
#include <fstream>
#include <set>


struct Word {
    std::string text;
    int line;
    int column;

    bool operator==(const Word& w) const{
        return text == w.text && line == w.line && column == w.column;
    }

    bool operator<(const Word& w) const{
        if(!(text != w.text)){
            return text < w.text;
        }
        if(line != w.line){
            return line < w.line;
        }
       return column < w.column;
    }
};


class MyHashFunction{
    public: 
        size_t operator()(const Word& w) const{
            return (std::hash<std::string>()(w.text)) ^ (std::hash<int>()(w.line)) ^ (std::hash<int>()(w.column));
        }
};

//Read words function
bool read_words(const std::string input_file_name,std::vector<Word>& words)
{
    std::ifstream input_file(input_file_name);
    if (input_file.fail()) {
        return false;
    }
    std::regex reg_exp("[a-zA-Z]+");
    std::smatch match;
    std::string text;
    int line = 0;
    int column = 0;
    while (std::getline(input_file, text)) {
        ++line;
        column = 1;
        while (std::regex_search(text, match, reg_exp)) {
            column += match.position();
            words.push_back({match.str(), line, column});
            column += match.length();
            text = match.suffix().str();
        }
    }
    return true;
}

//Soundex generator function
std::string soundexGenerator(const std::string& token){
    std::string uppertoken = "";
    for(char c : token){
        uppertoken += toupper(c);
    }

    std::string soundex = "";

    soundex += token[0];

    std::unordered_map<std::string, std::string> dictionary{
        {"BFPV","1"}, 
        {"CGJKQSXZ", "2"},       
        {"DT", "3"},
        {"L", "4"}, 
        {"MN", "5"}, 
        {"R", "6"},
        {"AEIOUHWY", "."}
    };

    for(int i = 1; i < uppertoken.size(); i++){
        char c = uppertoken[i];
        std::string code = "";
        for(auto& key : dictionary){
            if(key.first.find(c) != std::string::npos){
                code = key.second;
                if(code != "."){
                    soundex += code;
                }
            }
        }
    }
    const size_t max_length = 7;
    if(soundex.size() > max_length){
        soundex = soundex.substr(0, max_length);
    } else{
        while(soundex.length() < max_length){
            soundex += "0";
        }
    }
    return soundex;
}

bool buildSoundexDictionary(const std::string fileName, std::unordered_map<std::string, std::vector<std::string>>& soundex_dictionary, std::unordered_set<std::string>& words_dictionary){
    std::ifstream file(fileName);
    if(file.fail()){
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return false;
    }
    
    std::regex reg_exp("[a-zA-Z]+");
    std::smatch match;
    std::string text;
    
    while(std::getline(file, text)){
        while(std::regex_search(text, match, reg_exp)){
            std::string word = match.str();
            std::string code = soundexGenerator(word);
            soundex_dictionary[code].push_back(word);
            words_dictionary.insert(word);
            text = match.suffix().str();
        }      
    }
    file.close();
    return true;
}

std::string suggest_words(const std::string& word, const std::unordered_map<std::string, std::vector<std::string>> soundex_dictionary){
    std::string soundex = soundexGenerator(word);
    auto word_in = soundex_dictionary.find(soundex);
    if(word_in != soundex_dictionary.end()){
        std::string suggestions = "Suggestions: ";
        bool first = true;
        std::cout << suggestions;
        for(const std::string& suggested_word : word_in -> second){
            if(!first){
                std::cout << ", ";
            }
            std::cout << suggested_word;
            first = false;
        }
        return "";
    }
    return "No suggestions";
}

bool identify_unrecognized_words(const std::string& fileName, const std::unordered_set<std::string>& word_dictionary, const std::unordered_map<std::string, std::vector<std::string>>& soundex_dictionary){
    std::set<Word> unrecognized_words;

    std::ifstream file(fileName);
    if(file.fail()){
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return false;
    }

    std::regex reg_exp("[a-zA-Z]+");
    std::smatch match;
    std::string text;
    int line = 0;
    int column = 0;

    while(std::getline(file, text)){
        ++line;
        column = 1;
        while(std::regex_search(text, match, reg_exp)){
            std::string word = match.str();
            std::string lower;
            column += match.position();

            for(char c : word){
                lower += tolower(c); 
            }
            if(word_dictionary.find(lower) == word_dictionary.end()){
                Word w{lower, line, column};
                if(unrecognized_words.find(w) == unrecognized_words.end()){
                    unrecognized_words.insert(w);
                }
            }
            column += match.length();
            text = match.suffix().str();
        }
    }
    for(const auto& w : unrecognized_words){
        std::cout << std::endl;
        std::cout << "Unrecognized word: " << "\"" << w.text << "\"" << ". First found at line " << w.line << ", column " << w.column << "." << std::endl;
        std::cout << suggest_words(w.text,soundex_dictionary) << std::endl;

    }
    return true;
}


void print_dictionary(const std::unordered_map<std::string, std::vector<std::string>> dictionary_name){
    for(const auto& data : dictionary_name){
        std::cout << data.first << ":";
        bool first = true;
        for(const auto& word : data.second){
            if(!first){
                std::cout << ", ";
            }
            std::cout << word;
            first = false;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Please specify the name of the input file.\n";
        std::exit(1);
    }

    std::string file_name = argv[1];
    std::unordered_map<std::string, std::vector<std::string>> soundex_dictionary;
    std::unordered_set<std::string> word_dictionary;

    std::cout << buildSoundexDictionary("words.txt",soundex_dictionary, word_dictionary) << std::endl;
    // print_dictionary(soundex_dictionary);
    // std::cout << soundexGenerator("Bangalore") << std::endl;
    // std::cout << soundexGenerator("GeeksforGeeks") << std::endl;
    std::cout << identify_unrecognized_words(file_name,word_dictionary,soundex_dictionary) << std::endl;
    std::cout << soundexGenerator("Arrum") << std::endl;
    std::cout << soundexGenerator("Aarn") << std::endl;
}
