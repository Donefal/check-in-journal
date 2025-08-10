#include <iostream>
#include <fstream>

class fileManager{
    private:
        const std::string DATA_FILE = "data.txt";
};

enum topCriteria {NEWEST, OLDEST};
enum returnStatus {OK, ERROR, NOT_FOUND};

/* ------------------------------------------------------------------------------------------------------------------- */

void sendHelp(){
    std::cout << std::endl;
    std::cout << "List of {command}" << std::endl;
    std::cout << "HELP - list of command" << std::endl;
    std::cout << "ADD - start add entry menu" << std::endl;
    std::cout << "SEARCH {keyword} - search the keyword in all entry" << std::endl;
    std::cout << "SHOW - show every entry" << std::endl;
    std::cout << "SHOW TOP {num} - show top {num} newest entry" << std::endl;
    std::cout << "SHOW TOP {num} OLDEST - show top {num} oldest entry" << std::endl;
    std::cout << std::endl;
    std::cout << "For usage: ./journal {command}" << std::endl;
    std::cout << std::endl;

    return;
}

void addEntry(fileManager &fm){
    std::string entry;

    std::cout << "ADD Entries" << std::endl;
    std::getline(std::cin, entry, '\n');

    std::cout << entry << std::endl;

    return;
}


returnStatus searchEntry(fileManager &fm, std::string keyword){

    return OK;
}


returnStatus showEntry(fileManager &fm, topCriteria criteria, std::string top_str){
    // TODO: TRY and CATCH stoi top_str

    return OK;
    return ERROR;
}


// argc = argument count
// argv = argument values
int main(int argc, char* argv[]){
    fileManager fm;

    if(argc < 2){
        std::cout << "Usage: ./journal {command}" << std::endl;
        std::cout << "(./journal HELP) for the list of command" << std::endl;

    } else {
        std::string command = argv[1];

        if(command == "HELP"){
            sendHelp();

        } else if (command == "ADD"){
            addEntry(fm);

        } else if (command == "SEARCH"){
            if(argc < 3){
                std::cout << "Missing keyword" << std::endl;
                return 1;
            } else if (argc == 3){
                std::string keyword = argv[2];
                
                return searchEntry(fm, keyword);
            } else {
                std::cout << "Keyword should only be 1 (one) word";
                return 1;
            }

        } else if (command == "SHOW"){
            topCriteria criteria = NEWEST;
            std::string top_str = "-1";

            // Basic ./journal SHOW
            if(argc < 3){
                std::cout << "Showing All Entry" << std::endl;
                showEntry(fm, criteria, top_str);
            } 
            
            // ./journal SHOW {NEWEST/OLDEST}
            if(argc >= 3){
                std::string flag = argv[2];

                if(flag == "NEWEST"){
                    criteria = NEWEST;
                } else if (flag == "OLDEST"){
                    criteria = OLDEST;
                } else {
                    std::cout << flag << " is not a valid command" << std::endl;
                    return 1;
                }
            }

            // ./journal SHOW {NEWEST/OLDEST} TOP {NUM}
            if(argc >= 4){
                std::string flag = argv[3];

                if(flag != "TOP"){
                    std::cout << flag << " is not a valid command (1)" << std::endl;
                    return 1;
                }

                if(argc < 5){
                    std::cout << "Please include the amount after TOP (see HELP for more info)" << std::endl;
                    return 1;
                } else {
                    top_str = argv[4];
                }
            }

            return showEntry(fm, criteria, top_str);
        } else {
            std::cout << command << " is not a valid command" << std::endl;
            return 1;
        }
    }
    
    return 0;
}