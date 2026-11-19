 /*
    Author: Gloria Silva
    Date: 11/09/2026
    Lab Purpose: In this lab I will implement Huffman coding in C++ to compress and decompress text files. Then, I will construct a Huffman tree, generate Huffman codes, encode a text file into a compressed binary format, and then decode it back to its original form. Lastly, I will compare the file sizes before and after compression.
    A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/


#include <iostream>
#include <string>
#include <print>
#include <fstream>
#include <unordered_map>
#include <vector>
//I chose not to use using namespace std because I was getting errors


//creating the structure for my node
struct Node{
    char ch;
    int freq;
    Node *left, *right; 
};


//function prototypes
Node* newNode(char ch, int freq);
void deleteTree(Node *node);
bool compare(Node* a, Node* b);
Node* buildHuffmanTree(std::unordered_map<char, int>& freqMap);
void generateHuffmanCodes(Node* root, std::string code, std::unordered_map<char, std::string>& huffmanCode);
std::string encodeText(std::string text, std::unordered_map<char, std::string>& huffmanCode);
std::string decodeText(std::string encodedText, Node* root);



int main(){

    //creating the filename variable asking the user for the filename
    std::string filename;
    std::cout << "\nEnter text file name: ";
    std::cin >> filename;

    
    // Read input file
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cout << "Error opening file.\n";
        return 1;
    }
    
    //creating text and character variables
    std::string text;
    char ch;
    //read characters from a file one by one until the end of the file is reached
    while (inputFile.get(ch)) {
        text += ch; // Append each character to the string
    }
    inputFile.close();
    
    //storing the character-frequency mapping in an un-ordered map
    std::unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++; // Increment the frequency of each character in freqMap
    }
    
    
    std::cout << "\nHuffman Codes:\n";
    
    //made the root node variable call the tree function so that I can use root in the next function
    Node* root = buildHuffmanTree(freqMap);
    // This should be placed in the main function after building the Huffman tree.
    std::unordered_map<char, std::string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    //this is how I output the Huffman code for each character in the terminal
    for(auto pair : huffmanCode){
        std::cout << pair.first << " : "<< pair.second << "\n";
    }

    
    //writing the encoded text to the new file
    std::ofstream encodedFile;
    encodedFile.open("compressed.bin");
    
    if (!encodedFile) {
        std::cerr << "Error: Unable to open compressed.txt for writing!" << std::endl;
        return 1;
    }
    
    //defining my variable in order to write and output the encoded text
    std::string encodedText = encodeText(text, huffmanCode);
    encodedFile << encodedText;  // Write encoded text
    encodedFile.close();
    
    //outputting the encoded text
    std::cout << "\nEncoded Text (first 100 bits): " << encodedText.substr(0, 100) << "...\n";


    //defining the decodedtext string and setting it to the function so we can write and use it later on
    std::string decodedText = decodeText(encodedText, root);
    std::ofstream decodedFile;
    decodedFile.open("decompressed.bin");
        
    if (!decodedFile) {
        std::cerr << "Error: Unable to open compressed.txt for writing!" << std::endl;
        return 1;
    }
    
    //writing to the file
    decodedFile << decodedText;  // Write decoded text
    decodedFile.close();
    decodeText(encodedText, root);



    //terminal outputs for original, compressed, and decompressed file sizes
    std::cout << "\nOriginal file size: " << text.size() << " bytes\n";

    std::cout << "\nCompressed file size: " << encodedText.size() / 8 << " bytes (approx)";
    std::cout << "\nCompressed output saved to 'compressed.bin'\n";

    std::cout << "\nDecompressed file size: " << decodedText.size() << " bytes";
    std::cout << "\nDecompressed output saved to 'decompressed.txt'\n";
    std::cout << "\nDeleting nodes: ";
    deleteTree(root);
    std::cout << "\n";











}


//new node function which creates a dynamic node
Node* newNode(char ch, int freq){
    Node *temp = new Node;
    temp->ch = ch;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}


// Function to delete the entire tree
void deleteTree(Node *node) {
    if (node == NULL) {
        return;
    }
// Recursively delete left, middle, and right children
    deleteTree(node->left);
    //deleteTree(node->middle);
    deleteTree(node->right);
// Delete the current node
    if(node->left == nullptr && node->right == nullptr){ //this is so that the deleting nodes are printed as shown in the example
        std::cout << node->ch << " ";
    }    
    delete node;
}


// Comparison Function to sort nodes based on frequency
bool compare(Node* a, Node* b) {
    return a->freq < b->freq;  // Sort in ascending order of frequency
}
        
// Build Huffman Tree with vector
Node* buildHuffmanTree(std::unordered_map<char, int>& freqMap) {
    std::vector<Node*> nodes;  // Store nodes in a vector
// Step 1: Convert frequency map into nodes
    for (auto pair: freqMap) {
        char character = pair.first;   // Get the character (e.g., 'a')
        int frequency = pair.second;   // Get the frequency (e.g., 15)
    //Create a node using newNode function with character and its frequency
        Node* tempNode = newNode(character, frequency);
    // Use push_back to add the newly created node to the nodes vector.
        nodes.push_back(tempNode);
    }
// Step 2: Sort nodes by frequency
// This loop continues merging nodes until only one node remains, which becomes the root of the Huffman Tree.
    while (nodes.size() > 1) {
        sort(nodes.begin(), nodes.end(), compare);  //sort the nodes in ascending order of frequency 
    // Take two smallest frequency nodes
        Node* left = nodes[0];  //Hint: The node at index 0 has the smallest frequency.
        Node* right = nodes[1]; //Hint: The node at index 1 has the second smallest frequency.
    // Create a new node combining both
    // '\0' is the most common placeholder for internal nodes.
        Node* merged = newNode('\0', left->freq + right->freq); //Hint: The frequency of the merged node is the sum of left and right nodes' frequencies.
        merged->left = left;
        merged->right = right;
    // Remove the first two nodes from the list
        nodes.erase(nodes.begin(), nodes.begin() + 2);
        nodes.push_back(merged);//Hint: push_back() adds the merged node to the end of the nodes vector.
    }
// Ensure the vector is not empty before accessing index 0
    if (nodes.empty()) return nullptr;
        return nodes[0];  // The last remaining node is the root
}


//this function creates the huffman codes
void generateHuffmanCodes(Node* root, std::string code, std::unordered_map<char, std::string>& huffmanCode) {
    if (root == nullptr) return; // Base case: Stop recursion if tree is empty
    //// If the node is a leaf node (contains a character)
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCode[root->ch] = code; // Store Huffman code for this character
        return;
    }
    //If the node has a left child, assigns 0 for a left branch
    generateHuffmanCodes(root->left, code + "0", huffmanCode);
    //If the node has a right child, assigns 1 for a right branch
    generateHuffmanCodes(root->right, code + "1", huffmanCode);
}


// Encode the text using Huffman Codes
std::string encodeText(std::string text, std::unordered_map<char, std::string>& huffmanCode) {
    std::string encodedText;
    for (char ch : text) {
        encodedText += huffmanCode[ch];  //Append the Huffman code of each character to the encoded text.
    }
    return encodedText;
}
    

// Decode Huffman encoded text
std::string decodeText(std::string encodedText, Node* root) {
    std::string decodedText;
    Node* current = root; //Start at the root of the Huffman tree
    //Loop through each bit in encodedText
    for (char bit : encodedText) {
    // If the bit is '0', move to the left child; if the bit is '1', move to the right child.
        current = (bit == '0') ? current = current->left : current = current->right; //Hint: Use the left child when the bit is '0' and the right child when the bit is '1'.
        // Check if we reach a leaf node (character node)
        if (current->left == nullptr && current->right == nullptr) {  
            decodedText += current->ch; // Append the decoded character to the result
            current = root;  // Reset to the root for the next character
        }
    }
    return decodedText; // Return the fully decoded string
}
      