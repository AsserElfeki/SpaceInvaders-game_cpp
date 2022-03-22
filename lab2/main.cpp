#include <iostream>
#include <regex>
#include <fstream>

void log (std::string msg)  {
    std::cout << msg << std::endl;
}

/*
Tasks to perform:
1. Find URL address inside the text provided. (using regex)
2. Check whether password provided by the user is valid. Valid means:
-at least 8 characters
-at least 1 capital letter
-at least 1 lower letter
-at least 1 number
3. Modify the validation in such a way that the password contains at least 1 special character.
4. Find all special characters inside the password. (!"$%&'()+,-./:;=#@?[\]^_`{|}~*)
5. Display all special characters found and their positions in the password.
6. From list provided output all valid email addresses.
7. Write only valid emails into a file.
8. In all email addresses which end with ".ru" replace it by ".pl".
In tasks 1 and 6 perform loading the content from the file.
*/

int main()
{
    std::ifstream inFile;
    inFile.open("task_1.txt");
    if (!inFile) {
        std::cerr << "Cannot open a file\n";
        return -1;
    }
    else {
        std::cout << "Text file for task_1 was open successfully\n";

        std::string line, Text;
        while (getline(inFile, line))
        {Text += line + '\n';}

        std::regex URL_pattern ("([^ ]https*\\W+\\w+\\.?\\/?\\S+)");
        std::sregex_iterator currentMatch (Text.begin(), Text.end(), URL_pattern);
        std::sregex_iterator lastMatch;

        log ("########## Task 1: ##########");
        while (currentMatch != lastMatch) {
            std::cout << "Match found: " << currentMatch->str() << "\n";
            currentMatch ++;
        }
    log(" ");

        log ("########## Task 2 & 3: ##########");
        std::string password;
        std::regex upper_case_expression{ "[A-Z]+" };
        std::regex lower_case_expression{ "[a-z]+" };
        std::regex number_expression{ "[0-9]+" };
        std::regex special_char_expression{"([^ a-zA-Z0-9]+)"};

        bool done = false;
        bool upper_case = false;
        bool lower_case = false;
        bool number_case = false;
        bool special_char = false;

        do{
            log ("enter your password:");
            std::cin >> password;

            if (password.length() <= 8 )
            {
                log("password should be at least 8 characters");
            }

            else
            {
                upper_case = std::regex_search(password, upper_case_expression);
                lower_case = std::regex_search(password, lower_case_expression);
                number_case = std::regex_search(password, number_expression);
                special_char = std::regex_search(password, special_char_expression);

                if (!upper_case || !lower_case || !number_case || !special_char)
                {
                    log("password is invalid");
                }

                else
                done = true;
            }
        } while (!done);

        log(" ");

        log ("########## Task 4: ##########");
        std::sregex_iterator currentMatch_pswrd (password.begin(), password.end(), special_char_expression);
        std::sregex_iterator lastMatch_pswrd;

        while (currentMatch_pswrd != lastMatch_pswrd) {
            std::cout << "special character: [ " << currentMatch_pswrd->str() << " ] was found at position: " << currentMatch_pswrd->position() << "\n";
            currentMatch_pswrd ++;
        }
        log(" ");
    inFile.close();
    }

    std::ofstream oFile;
    oFile.open("output.txt");
    inFile.open("task_6.txt");
    if (!inFile){
        log("emails file cannot be open");
        return -1;
    }
    else {
        log("emails file opened successfully");
        std::string line_ , emails;
        while (getline(inFile, line_)){
            emails += line_ + '\n';
        }
        std::regex valid_email_pattern ("([a-zA-Z0-9.-_]+@[a-zA-Z-]+\\.[a-zA-Z]+.?[a-zA-Z]?)");
        std::sregex_iterator currentMatch_email (emails.begin(), emails.end(), valid_email_pattern);
        std::sregex_iterator lastMatch_email;

        log ("########## Task 6 & 7: ##########");
        while (currentMatch_email != lastMatch_email) {
            std::cout << "valid email address found: " << currentMatch_email->str() << "\n";
            oFile << "valid email address found: " << currentMatch_email->str() << "\n";
            currentMatch_email ++;
        }

        log ("########## Task 8: ##########");
        currentMatch_email = {emails.begin(), emails.end(), valid_email_pattern};
        while (currentMatch_email != lastMatch_email) {
            std::cout << "Corrected email address : " << std::regex_replace(currentMatch_email->str(), std::regex(".ru$"), ".pl") << "\n";
            oFile << "Corrected email address : " << std::regex_replace(currentMatch_email->str(), std::regex(".ru$"), ".pl") << "\n";
            currentMatch_email ++;

        }

        inFile.close();
        oFile.close();
    }

    return 0;
}
