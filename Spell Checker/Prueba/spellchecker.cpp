/*----------------------------------------------------------
 * Project: Spell Checker
 *
 * Date: 03-Dec-2025
 * Authors:
 *           A01803172 Giancarlo Moreno
 *           A01277159 Leonardo González
 *           A01748498 Emiliano Díaz
 *----------------------------------------------------------*/

#include <fstream> 
#include <regex> 
#include <vector> 
#include <iostream> 
#include <unordered_map> 
#include <unordered_set> 
#include <vector> 
#include <cctype> 
#include <set>
#include <chrono>

struct Word { 
    std::string text; 
    int line; 
    int column; 

    bool operator<(const Word& other) const{ 
        if(!(text != other.text)){ 
            return text < other.text; 
        } 
        if(line != other.line){ 
            return line < other.line; 
        } 
        return column < other.column; 
    } 
}; 
    
//Soundex generator function 
std::string soundexGenerator(const std::string& token){
    std::string uppertoken = "";
    for(char c : token){
        uppertoken += toupper(c);
    }

    std::string soundex = "";
    soundex += token[0];

    std::unordered_map<std::string, std::string> dictionary{
        {"BFPV", "1"},
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

//Function that creates a dictionary with words that have the same soundex in the words.txt 
void buildSoundexDictionary(const std::string fileName, std::unordered_map<std::string, std::vector<std::string>>& soundex_dictionary, std::unordered_set<std::string>& words_dictionary){ 
    soundex_dictionary.reserve(9000);
    words_dictionary.reserve(50000);
    std::ifstream file(fileName); 
    if(file.fail()){ 
        std::cerr << "Unable to open file: " << fileName << std::endl; 
        return; 
    } 
    std::regex reg_exp("[a-zA-Z]+"); 
    std::smatch match; 
    std::string text; 
    while(std::getline(file, text)){ 
        while(std::regex_search(text, match, reg_exp)){ 
            std::string word = match.str(); 
            std::string lower;
            for(char c : word){
                lower += tolower(c);
            }
            std::string code = soundexGenerator(lower); 
            soundex_dictionary[code].push_back(lower); 
            words_dictionary.insert(lower); 
            text = match.suffix().str(); 
        } 
    } 
    file.close(); 
    return; 
} 

//Function to join all the words with the same soundex 
std::string suggest_words(const std::string& word, const std::unordered_map<std::string, std::vector<std::string>> soundex_dictionary){ 
    std::string soundex = soundexGenerator(word); 
    auto found_soundex = soundex_dictionary.find(soundex); 
    if(found_soundex != soundex_dictionary.end()){ 
        std::string suggestions = "Suggestions: "; 
        bool first = true;  
        for(const std::string& suggested_word : found_soundex -> second){ 
            if(!first){ 
                suggestions += ", "; 
            } 
            suggestions += suggested_word; 
            first = false; 
        } 
        return suggestions; 
    } 
    return "No suggestions."; 
} 

//Function to create a set of the unrecognized words of the .txt
void identify_unrecognized_words(const std::string& fileName, const std::unordered_set<std::string>& word_dictionary, const std::unordered_map<std::string, std::vector<std::string>>& soundex_dictionary){ 
    std::set<std::string> first_unrecognized_words; 
    std::vector<Word> unrecognized_words;
    std::ifstream file(fileName); 
    if(file.fail()){ 
        std::cerr << "Unable to open file: " << fileName << std::endl; 
        return; 
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
                if(first_unrecognized_words.insert(lower).second){
                    unrecognized_words.push_back({lower, line, column}); 
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
    return; 
}

//Auxiliary function to print the words in a dictionary 
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
    
    //Creating the soundex dictionary of every word in the words.txt
    auto start = std::chrono::high_resolution_clock::now();
    buildSoundexDictionary("words.txt",soundex_dictionary, word_dictionary); 

    //---------- Extra functions to verify the correct functionality of the functions ----------/
    // std::cout << "Here is the space for the extra tests" << std::endl;
    // print_dictionary(soundex_dictionary);
    // std::cout << soundexGenerator("Arrum") << std::endl; 
    // std::cout << soundexGenerator("aroma") << std::endl;  
    // std::cout << soundexGenerator("Bangalore") << std::endl; 
    // std::cout << soundexGenerator("GeeksforGeeks") << std::endl; 

    //Identify the unrecognized words of the given .txt
    
    identify_unrecognized_words(file_name,word_dictionary,soundex_dictionary);
    std::cout << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double total_time = duration.count() / 1'000'000.0;
    std::cout << "Total time: " << total_time << std::endl;
    return 0;
}

    