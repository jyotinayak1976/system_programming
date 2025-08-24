#include <iostream>
#include <string>

const int TABLE_SIZE = 10;

struct Node {
	std::string key;
	std::string value;
	Node* next;
	Node(std::string k, std::string v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
	private:
		Node* table[TABLE_SIZE];

		int hashFunction(const std::string& key) {
			unsigned long hash = 0;
			for (char c : key) {
				hash += c;
			}

			return hash % TABLE_SIZE;
		}
	public:
		HashTable() {
			for (int i=0;i<TABLE_SIZE ; i++) {
				table[i] = nullptr;
			}
		}

		void insert(const std::string& key, const std::string& value) {
			int index = hashFunction(key);
			Node* head = table[index];

			for (Node* curr = head; curr != nullptr ; curr = curr->next){
				if (curr->key == key){
				       curr->value = value;
				       return;
				}
			}

			Node* newNode = new Node(key,value);
			newNode->next = head;
			table[index] = newNode;
		}

		std::string get(const std::string& key) {
			int index = hashFunction(key);
			for (Node* curr = table[index]; curr != nullptr; curr = curr->next){
				if (curr->key == key){
					return curr->value;
				}
			}
			return "key not found";
		}

		void remove(const std::string& key) {
			int index = hashFunction(key);
			Node* curr = table[index];

			Node* prev = nullptr;

			while (curr != nullptr) {
				if (curr->key == key) {
					if (prev) {
						prev->next = curr->next;
					} else {
						table[index] = curr->next;
					}
					delete curr;
					return;
				}
				prev = curr;
				curr = curr->next;
			}
		}

		void display() {
 		       for (int i = 0; i < TABLE_SIZE; i++) {
            			std::cout << i << ": ";
            			Node* curr = table[i];
            			while (curr != nullptr) {
                			std::cout << "[" << curr->key << " -> " << curr->value << "] ";
                			curr = curr->next;
            			}
            			std::cout << "\n";
        		}
    		}
};

int main() {
    HashTable ht;

    ht.insert("name", "Jyoti");
    ht.insert("city", "Bhubaneswar");
    ht.insert("language", "Odia");

    std::cout << "city: " << ht.get("city") << "\n";
    std::cout << "language: " << ht.get("language") << "\n";

    ht.insert("city", "Paris"); // Update
    std::cout << "city (updated): " << ht.get("city") << "\n";

    ht.remove("language");
    std::cout << "language after removal: " << ht.get("language") << "\n";

    std::cout << "\nFull table:\n";
    ht.display();

    return 0;
}





			       

