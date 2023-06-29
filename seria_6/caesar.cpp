#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

std::string Caesar(int n, const std::string& str){

    std::string new_string = "";
    
    for (char c : str){

        if(c >= 'A' and c <= 'Z'){
            if(n >= 0){
                if(c + n <= 'Z'){
                    new_string += c + n;
                }
                else{
                    new_string += c + n - 26;
                }
            }
            else{
                if(c + n >= 'A'){
                    new_string += c + n;
                }
                else{
                    new_string += c + n + 26;
                }
            }
        }
        else if(c >= 'a' and c <= 'z'){
            if(n>=0){
                if(c + n <= 'z'){
                    new_string += c + n;
                }
                else{
                    new_string += c + n - 26;
                }
            }
            else{
                if(c + n >= 'a'){
                    new_string += c+ n;
                }
                else{
                    new_string += c + n + 26;
                }
            }
        }
        else{
            new_string += c;
        }

    }
        
    return new_string;
}


int main(int argc, char *argv[]){

    std::string operation;
    int n;
    std::string file_name;
    std::string file_to_save;

    std::istringstream(argv[1]) >> operation;
    std::istringstream(argv[2]) >> n;
    std::istringstream(argv[3]) >> file_name;
    std::istringstream(argv[4]) >> file_to_save;


   std::ifstream input_file(file_name);
   std::ofstream output_file(file_to_save);

    if (operation == "-e") {  // Encryption

        if (input_file.is_open() && output_file.is_open()) {
            std::string line;
            while (std::getline(input_file, line)) {
                 std::string encrypted_line = Caesar(n, line);  // Encrypt the line
                output_file << encrypted_line << std::endl;  // Write the encrypted line to the output file
                }
                input_file.close();  // Close the input file
                output_file.close();  // Close the output file
                std::cout << "Encryption complete." << std::endl;
            } else {
                std::cout << "Failed to open the file." << std::endl;
            }
    } else if (operation == "-d") {  // Decryption
        if (input_file.is_open() && output_file.is_open()) {
            std::string line;
            while (std::getline(input_file, line)) {
                 std::string decrypted_line = Caesar(-n, line);  // decrypt the line
                output_file << decrypted_line << std::endl;  // Write the decrypted line to the output file
                }
                input_file.close();  // Close the input file
                output_file.close();  // Close the output file
                std::cout << "Decryption complete." << std::endl;
            } else {
                std::cout << "Failed to open the file." << std::endl;
            }
    }
    return 0;
}