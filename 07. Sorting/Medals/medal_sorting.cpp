#include <algorithm> //Includes vector and sort
#include <fstream> 
#include <iomanip> //Input/Output 
#include <iostream>

struct Country{
    std::string name;
    int gold;
    int silver;
    int bronze;
};

void read_file(const std::string& file_name, std::vector<Country>& data){
    std::ifstream file(file_name);
    
    if(file.fail()) {
        std::cerr << "Unable to open file: " << file_name << "\n";
        std::exit(1);
    }
    while(not file.eof()){
        Country c;
        file >> c.name;
        file >> c.gold;
        file >> c.silver;
        file >> c.bronze;
        data.push_back(c);
        
    }
    file.close();
}

//return true is a shoul be befores b
bool compare_countries(const Country& a, const Country& b){
    if(a.gold != b.gold){
        return a.gold > b.gold;
    }
    if(a.silver != b.silver){
        return a.silver > b.silver;
    }
    if(a.bronze != b.bronze){
        return a.bronze > b.bronze;
    }
    return a.name < b.name;
}

void print_table(const std::vector<Country>& data){
    for(Country c : data){
        std::cout 
        << std::setw(13) << std::left << c.name << " " 
        << std::setw(4) << c.gold << std::right << " " 
        << std::setw(4) << c.silver << std::right << " " 
        << std::setw(4) << c.bronze << std::right << std::endl;
    }
}


int main(int argc, char* argv[]){
    if(argc != 2){
        std::cerr << "Please specify the name of the input file.\n";
        std::exit(1);
    }
    std::string file_name = argv[1];
    std::vector<Country> data;
    data.reserve(20);
    
    read_file(file_name, data);
    std::sort(data.begin(), data.end(),compare_countries);
    print_table(data);

    return 0;
}