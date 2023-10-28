#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int keywordThreshold(string keyword_file, string keyword_threshold[][2]) {
    ifstream file(keyword_file);
    if (file.fail()) {
        cout<<"Failed to open keyword file"<<endl;
        return 0;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                keyword_threshold[count][0] = line.substr(0, i);
                keyword_threshold[count][1] = line.substr(i + 1, line.length() - i + 1);
                //line.length() - i + 1
            }        
        }
        count++;
    }
    return count;
}

bool countFilter(string email_file, string keyword_threshold[][2], int keyword_count[], int keyword_size) {
    ifstream file(email_file);
    string word;

    if (file.fail()) {
        cout<<"Failed to open email file"<<endl;
        return false;
    }

    while (file >> word) {
        //WHAT DOES THIS EVEN MEAN?! internet search for next 3 lines
        for (size_t i = 0; i < word.length(); i++) {
            if (ispunct(word[i])) {
                word.erase(i--, 1);
            }
        }
        // word = regex_replace(word, regex("[^a-zA-Z']+"), "");
        for (int i = 0; i < keyword_size; i++) {
            if (word == keyword_threshold[i][0]) {
                keyword_count[i]++;
            }
        }
    }
    
    return true;
}


bool checkSpam(int keyword_count[], string keyword_threshold[][2], int keyword_size) {
    for (int i = 0; i < keyword_size; i++) {
        if (keyword_count[i] < stoi(keyword_threshold[i][1])) {
            // cout << "Not spam because " << keyword_threshold[i][0] << " appears " << keyword_count[i] << " times, which is less than the threshold of " << keyword_threshold[i][1] << endl;
            return false;
        }
    }

    // cout << "Spam detected!" << endl;
    return true;
}

int main() {
    string email_file = "email_spam.txt";
    string keyword_file = "keywords_1.txt";
    string keyword_threshold[10][2];
    int keyword_count[10] = {0,0,0,0,0,0,0,0,0,0};
    int keyword_size = 0;
    bool read_email_file, spam_email;
    keyword_size = keywordThreshold(keyword_file, keyword_threshold);
    if(!keyword_size) {
        return 0;
    }
    read_email_file = countFilter(email_file, keyword_threshold, keyword_count, keyword_size);
    if(!read_email_file) {
        return 0;
    }
    spam_email = checkSpam(keyword_count, keyword_threshold, keyword_size);
    if(spam_email) {
        cout << "It's a spam email!!" << endl;
    }
    else {
        cout << "It's not a spam email!!" << endl;
    }
}
