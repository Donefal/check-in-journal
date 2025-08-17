#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>

enum topCriteria {NEWEST, OLDEST};
enum returnStatus {OK, ERROR, NOT_FOUND};

class fileManager{
    private:
        const std::string DATA_FILE = "data.txt";
        std::vector<std::string> entries;
    public:
        returnStatus readFile(){
            std::ifstream file(DATA_FILE);
            std::string line;

            if(!file.is_open()){
                std::cerr << "Failed to open save file" << std::endl;
                return ERROR;
            }

            while(std::getline(file, line, '\n')){
                entries.push_back(line);
            }

            file.close();
            return OK;
        }

        returnStatus saveFile(){
            std::ofstream file(DATA_FILE);
            
            if(!file.is_open()){
                std::cerr << "Failed to open save file" << std::endl;
                return ERROR;
            }

            for(std::string entry : entries){
                file << entry << std::endl;
            }

            file.close();
            return OK;
        }

        returnStatus resetFile(){
            std::ofstream file(DATA_FILE);

            if(!file.is_open()){
                std::cerr << "Failed to open save file" << std::endl;
                return ERROR;
            }

            file << "";
            file.close();
            return OK;
        }

        void append(const std::string &entry){
            entries.push_back(entry);
        }

        void pop(){
            entries.pop_back();
        }

        std::vector<std::string>& getEntries(){
            return entries;
        }

        // Constructor & Destructor
        fileManager(){
            readFile();
        }
        
        ~fileManager(){};        
};


/* ------------------------------------------------------------------------------------------------------------------- */



void sendHelp(){
    std::cout << std::endl;
    std::cout << "List of {command}" << std::endl;
    std::cout << "HELP - list of command" << std::endl;
    std::cout << "ADD - start add entry menu" << std::endl;
    std::cout << "SEARCH {keyword} - search the keyword in all entry" << std::endl;
    std::cout << "SHOW - show every entry" << std::endl;
    std::cout << "SHOW TOP {num} - show top {num} newest entry" << std::endl;
    std::cout << "SHOW TOP {num} NEWEST - same as SHOW TOP {num}" << std::endl;
    std::cout << "SHOW TOP {num} OLDEST - show top {num} oldest entry" << std::endl;
    std::cout << "POP - delete the last entry program" << std::endl;
    std::cout << "RESET - delete every entry on the program" << std::endl;
    std::cout << std::endl;
    std::cout << "For usage: ./journal {command}" << std::endl;
    std::cout << std::endl;

    return;
}

void addEntry(fileManager &fm){
    std::string entry;
    std::stringstream entryString;

    std::cout << "Write Entry: " << std::endl;
    std::getline(std::cin, entry, '\n');

    // Handling time
    auto time = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::localtime(&tt);
    entryString << "[" << std::put_time(&tm, "%Y-%m-%d") << "] " << entry;

    fm.append(entryString.str());
    fm.saveFile();

    return;
}

returnStatus searchEntry(fileManager &fm, std::string keyword){
    std::vector<std::string> entries = fm.getEntries();
    std::vector<std::string> validEntries;

    for(std::string entry : entries){
        if(entry.find(keyword) != std::string::npos){
            validEntries.push_back(entry);
        }
    }

    for(std::string entry : validEntries){
        std::cout << entry << std::endl;
    }
    
    return OK;
}

returnStatus showEntry(fileManager &fm, topCriteria criteria, std::string top_str){
    int top_int;

    try{
        top_int = std::stoi(top_str);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return ERROR;
    }
    
    std::vector<std::string> entries = fm.getEntries();
    int len = entries.size();
    if(top_int == -1) top_int = len;

    switch (criteria){
        case OLDEST:
            for(int i = 0; i < len && i < top_int; i++){
                std::cout << entries[i] << std::endl;
            }
            break;
        case NEWEST:
        {
            int count = 0;
            for(int i = len - 1; i >= 0 && count < top_int; i--){
                std::cout << entries[i] << std::endl;
                count++;
            }
            break; 
        }
        default:
            break;
    }
    
    return OK;
}

void resetEntry(fileManager &fm){
    char choice;
    std::cout << "Are you sure? (y): ";
    std::cin >> choice;

    if (choice == 'y'){
        fm.resetFile();
        std::cout << "File reset succesful" << std::endl;
    }

    return;
}

void popEntry(fileManager &fm){
    fm.pop();
    fm.saveFile();
}

// argc = argument count
// argv = argument values
int main(int argc, char* argv[]){
    fileManager fm;

    if(argc < 2){
        std::cout << "Usage: ./journal {command} or use (./journal HELP) for the list of command" << std::endl;

    } else {
        std::string command = argv[1];

        if(command == "HELP"){
            sendHelp();

        } else if (command == "ADD"){
            addEntry(fm);

        } else if (command == "SEARCH"){
            if(argc < 3){
                std::cerr << "Missing keyword" << std::endl;
                return 1;
            } else if (argc == 3){
                std::string keyword = argv[2];
                
                return searchEntry(fm, keyword);
            } else {
                std::cerr << "Keyword should only be 1 (one) word";
                return 1;
            }

        } else if (command == "SHOW"){
            topCriteria criteria = NEWEST;
            std::string top_str = "-1";

            // Basic ./journal SHOW
            if(argc < 3){
                showEntry(fm, criteria, top_str);
                return 0;
            } 
            
            // ./journal SHOW {NEWEST/OLDEST}
            if(argc >= 3){
                std::string flag = argv[2];

                if(flag == "NEWEST"){
                    criteria = NEWEST;
                } else if (flag == "OLDEST"){
                    criteria = OLDEST;
                } else {
                    std::cerr << flag << " is not a valid command" << std::endl;
                    return 1;
                }
            }

            // ./journal SHOW {NEWEST/OLDEST} TOP {NUM}
            if(argc >= 4){
                std::string flag = argv[3];

                if(flag != "TOP"){
                    std::cerr << flag << " is not a valid command" << std::endl;
                    return 1;
                }

                if(argc < 5){
                    std::cerr << "Please include the amount after TOP (see HELP for more info)" << std::endl;
                    return 1;
                } else {
                    top_str = argv[4];

                    if(top_str == "-1"){
                        top_str = "0";
                    }
                }
            }

            return showEntry(fm, criteria, top_str);
        } else if(command == "RESET") {
            resetEntry(fm);

        } else if (command == "POP"){
            popEntry(fm);

        }else {
            std::cerr << command << " is not a valid command" << std::endl;
            return 1;
        }
    }
    
    return 0;
}