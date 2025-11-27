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

    bool operator==(const Word& other) const{ 
        return text == other.text && line == other.line && column == other.column; 
    } 
    
    // bool operator<(const Word& other) const{ 
    //     // if(line != other.line){ 
    //     // return line < other.line; 
    //     // } 
    //     // if(column != other.column){ 
    //     // return column < other.column; 
    //     // } 
    //     // return text < other.text; 
    //     // } 
    //     if(!(text != other.text)){ 
    //         return text < other.text; 
    //     } 
    //     if(line != other.line){ 
    //         return line < other.line; 
    //     } 
    //     return column < other.column; 
    // } 
}; 

// class MyHashFunction{ 
// public: 
// std::size_t operator()(const word& w) const{ 
// return (std::hash<std::string>()(w.text)) ^ (std::hash<int>()(w.line)) ^ (std::hash<int>()(w.column)); 
// } 
// }; 
//Read words function 
bool read_words(const std::string input_file_name,std::vector<Word>& words) { 
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
    if(token.empty()){ 
        return ""; 
    } 
    std::string upperToken; 
    for(char c : token){ 
        upperToken += toupper(c); 
    } 
    std::string soundex = ""; 
    soundex += upperToken[0]; 
    std::unordered_map<std::string, std::string> dictionary = { 
        {"BFPV", "1"}, 
        {"CGJKQSXZ", "2"}, 
        {"DT", "3"}, 
        {"L", "4"}, 
        {"MN", "5"}, 
        {"R", "6"}, 
        {"AEIOUHWY", "."} 
    }; 
    
    for(size_t i = 1; i < upperToken.size(); i++){ 
        char c = upperToken[i]; 
        std::string code = " "; 
        
        for(auto& key : dictionary){ 
            if(key.first.find(c) != std::string::npos){ 
                code = key.second; 
                break; 
            } 
        } 
        
        if(!code.empty() && code != "."){ 
            if(code != std::string(1, soundex.back())){ 
                soundex += code; 
            } 
        } 
    } 
    if(soundex.size() > 7){ 
        soundex = soundex.substr(0,7); 
    } else{ 
        soundex.append(7 - soundex.size(), '0'); 
    } 
    return soundex; 
} 

//Function that creates a dictionary with same soundex words 
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

//Function to return all the words with the same soundex 
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
        return suggestions; 
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
                if(unrecognized_words.find(w)== unrecognized_words.end()){ 
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

    std::cout << "Aqui empiezan las demás pruebas" << std::endl;
    std::cout << soundexGenerator("Arrum") << std::endl; 
    std::cout << soundexGenerator("aroma") << std::endl; 
}

    