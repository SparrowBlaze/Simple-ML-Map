#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

/*
 *  A Very Basic Natural Language Processing Model
 *
 *  Pairing words together, and remembering that they've been seen before.
 *
 */

void cleanToken(std::string &str) {
    
//    std::string finalStr = "";
//
//    for (int i = 0; i < str.size(); i++) {
//        if (isalpha(str.at(i))) {
//            finalStr.push_back(str.at(i));
//        }
//    }
//
//    str = finalStr;
    
    while (!str.empty() && (isspace(str.at(0)) || ispunct(str.at(0)))) {
        str.erase(str.begin());
    }
    
    while (!str.empty() && (isspace(str.at(str.size()-1)) || ispunct(str.at(str.size()-1)))) {
        str.erase(str.begin() + str.size() - 1);
    }
}

int main() {
    std::string docName = "";
    
    std::cout << "Enter the name of a text file: ";
    std::cin  >> docName;
    
    // 1. Read the document into a set of strings and print them to a file.
    std::string setOutputFilename = docName + "_set.txt";
    
    // Open an input file
    std::ifstream inFS;
    inFS.open(docName + ".txt");
    
    if (!inFS.is_open()) {
        std::cout << "Couldn't open " << docName << ".txt for reading." << std::endl;
        return 1;
    }
    
    
    // Read into a string set
    std::set<std::string> stringSet;
    
    while (!inFS.eof()) {
        std::string newString = "";
        inFS >> newString;
        cleanToken(newString);
        stringSet.insert(newString);
    }
    
    inFS.close();
    
    // Output to file
    std::ofstream outFS;
    outFS.open(setOutputFilename);
    
    if (!outFS.is_open()) {
        std::cout << "Couldn't open " << setOutputFilename << " for writing." << std::endl;
        return 1;
    }
    
    for (std::set<std::string>::iterator it = stringSet.begin(); it != stringSet.end(); it++) {
        outFS << *it << std::endl;
//        std::cout << *it << std::endl;
    }
    std::cout << std::endl << stringSet.size() << " elements in set for " << docName << ".txt" << std::endl;
    
    outFS.close();
    std::cout << "Set written to " << setOutputFilename << std::endl;
    
    
    
    
    // 2. Read the document into a vector of strings and print them to a file.
    
    // Open an input file
    inFS.open(docName + ".txt");
    
    if (!inFS.is_open()) {
        std::cout << "Couldn't open " << docName << ".txt for reading." << std::endl;
        return 1;
    }
    
    // Read into string set
    std::vector<std::string> stringVector;
    
    while (!inFS.eof()) {
        std::string newString = "";
        inFS >> newString;
        cleanToken(newString);
        stringVector.push_back(newString);
    }
    
    inFS.close();
    
    // Output to file
    std::string vectorOutputFilename = docName + "_vector.txt";
    outFS.open(vectorOutputFilename);
    
    if (!outFS.is_open()) {
        std::cout << "Couldn't open " << vectorOutputFilename << " for writing." << std::endl;
        return 1;
    }
    
    for (std::vector<std::string>::iterator it = stringVector.begin(); it != stringVector.end(); it++) {
        outFS << *it << std::endl;
//        std::cout << *it << std::endl;
    }
    std::cout << std::endl << stringVector.size() << " elements in vector for " << docName << ".txt" << std::endl;
    
    outFS.close();
    std::cout << "Vector written to " << vectorOutputFilename << std::endl;
    
    
    
    
    // 3. Create a map from a string (the key) to a string (the value).
    std::map<std::string, std::string> wordMap;
    std::string last = "";
    
    for (std::vector<std::string>::iterator it = stringVector.begin(); it != stringVector.end(); it++) {
        wordMap[last] = *it;
        last = *it;
    }
    
    // Print it to a file
    std::string mapOutputFilename = docName + "_1_1.txt";
    outFS.open(mapOutputFilename);
    
    if (!outFS.is_open()) {
        std::cout << "Couldn't open " << mapOutputFilename << " for writing." << std::endl;
        return 1;
    }
    
    for (std::map<std::string, std::string>::iterator it = wordMap.begin(); it != wordMap.end(); it++) {
        outFS << it->first << ", " << it->second << std::endl;
    }
    
    outFS.close();
    std::cout << "Map written to " << mapOutputFilename << std::endl;
    
    
    
    
    // 4. Generate text from this map.
    std::map<std::string, std::string>::iterator it = wordMap.begin();
    std::string state = it->first;
    
    for (int i = 0; i < 100; i++) {
//        std::cout << wordMap[state] << " ";
        state = wordMap[state];
    }
//    std::cout << std::endl;
    
    
    
    
    // 5. Generate text from a map that pairs strings (keys) to a vector of strings (values).
    std::map<std::string, std::vector<std::string>> newMap;
    state = "";
    
    for (std::vector<std::string>::iterator it = stringVector.begin(); it != stringVector.end(); it++) {
        newMap[state].push_back(*it);
        state = *it;
    }
    
    // Get the sixth element, to check we got this right.
    std::map<std::string, std::vector<std::string>>::iterator mit = newMap.begin();
    for (int i = 0; i < 5 && mit != newMap.end(); i++) {
        mit++;
    }
    
    if (mit == newMap.end()) {
        std::cout << "Something went wrong. The map had fewer than six entries." << std::endl;
        return 1;
    }
    
    std::vector<std::string> sextoElemento = mit->second;
    for (unsigned int i = 0; i < sextoElemento.size(); i++) {
        std::string value = sextoElemento.at(i);
//        std::cout << value;
        if (i + 1 < sextoElemento.size()) {
//            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
    // 6. Generate text from a map composed of a list of strings as keys and vectors of strings as values.
    // Make it random
    srand(static_cast<unsigned int>(time(NULL)));
    
    state = "";
    for (int i = 0; i < 100; i++) {
        int index = rand() % newMap[state].size();
        std::cout << newMap[state].at(index) << " ";
        state = newMap[state].at(index);
    }
    
    std::cout << std::endl;
    
    // 7. Explore different texts and methods, and observe when the algorithm produces interesting
    //      things. Have a little fun. Discuss what you did in your Canvas Submission.
    
    
    
    return 0;
}
