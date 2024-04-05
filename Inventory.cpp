#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct product{
    string name;
    int quantity;
    int max_quantity;
    double price;
    string manufacturer;
    string search_tags[10];
    int num_tags;
    float rating;
}; 

void load(string fname, product products[], int &num){
    ifstream file;
    file.open(fname);
    if(!file.is_open()){
        cout << "Error: Unable to open file." << endl;
        return;
    }

    num = 0;
    string line;
    while (getline(file, line)){
        product merch;

        merch.name = line;
        file >> merch.quantity >> merch.max_quantity >> merch.price;
        file.ignore();
        getline(file, merch.manufacturer);

        string tags;
        getline(file, tags);
        istringstream tagStream(tags);

        merch.num_tags = 0;
        int i = 0;
        while ((i < 10) && (tagStream >> merch.search_tags[i])){
            merch.num_tags += 1;
            i++;
        }

        file >> merch.rating;
        file.ignore();

        products[num] = merch;
        num++;      

    }
    file.close();
}

void save(string fname, product products[], int num){
    ofstream file;
    file.open(fname);
    if(!file.is_open()){
        cout << "Error: unable to open" << endl;
        return;
    }

    for (int i = 0; i < num; ++i){
        file << products[i].name << endl;
        file << products[i].quantity << endl;
        file << products[i].max_quantity << endl;
        file << products[i].price << endl;
        file << products[i].manufacturer << endl;
        for (int j = 0; j < products[i].num_tags; ++j){
            file << products[i].search_tags[j] << " ";
        }
        file << endl;
        file << products[i].rating << endl;
    }

    file.close();
}

void list_all_products(product products[], int num){
    for(int i = 0; i < num; ++i){
        cout << products[i].name << endl;
        cout << "Quantity: " << products[i].quantity << endl;
        cout << "Max Quantity: " << products[i].max_quantity << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Manufacturer: " << products[i].manufacturer << endl;
        
        cout << "Search Tags: ";
        for(int j = 0; j < products[i].num_tags; ++j){
            cout << products[i].search_tags[j];
            if(j < products[i].num_tags - 1){
                cout << ", ";
            }
        }
        cout << endl;
        cout << "Rating: " << products[i].rating << endl;
        cout << "---" << endl;

    }
}

void sort_products_by_price(product products[], int num, bool ascending){
    for(int i = 0; i < num -1; ++i){
        for(int j = 0; j < num - 1; ++j){
            if((ascending && products[j].price > products[j + 1].price)
            || (!ascending && products[j].price < products[j + 1].price)){

                product hold = products[j];
                products[j] = products[j + 1];
                products[j + 1] = hold;
            }
        }
    }
}

void list_all_products_restocking(product products[], int num){
    for(int i = 0; i < num; ++i){
        if(products[i].quantity == 0){
            cout << products[i].name << endl;
            cout << "Quantity: " << products[i].quantity << endl;
            cout << "Max Quantity: " << products[i].max_quantity << endl;
            cout << "Price: " << products[i].price << endl;
            cout << "Manufacturer: " << products[i].manufacturer << endl;
            
            cout << "Search Tags: ";
            for(int j = 0; j < products[i].num_tags; ++j){
                cout << products[i].search_tags[j];
                if(j < products[i].num_tags - 1){
                    cout << ", ";
                }
            }
            cout << endl;
            cout << "Rating: " << products[i].rating;
            cout << endl;
        }
    }
}

void list_all_products_manufacturer(product products[], int num, string manufacturer){
    for(int i = 0; i < num; ++i){
        if(products[i].manufacturer == manufacturer){
            cout << products[i].name << endl;
            cout << "Quantity: " << products[i].quantity << endl;
            cout << "Max Quantity: " << products[i].max_quantity << endl;
            cout << "Price: " << products[i].price << endl;
            cout << "Manufacturer: " << products[i].manufacturer << endl;
            
            cout << "Search Tags: ";
            for(int j = 0; j < products[i].num_tags; ++j){
                cout << products[i].search_tags[j];
                if(j < products[i].num_tags - 1){
                    cout << ", ";
                }
            }
            cout << endl;
            cout << "Rating: " << products[i].rating << endl;
            cout << "---" << endl;
        }
    }
}
   
bool restock_product(product products[], int num, string name, int amount){
    for(int i = 0; i < num; ++i){
        if(products[i].name == name){
            if((products[i].max_quantity) >= (products[i].quantity + amount)){
                products[i].quantity += amount;
                return true;
            }
            else{
                cout << "Error: Product is already fully stocked!" << endl;
                return false;
            }
        }
    }
}

bool sell_product(product products[], int num, string name, int amount){
    for(int i = 0; i < num; ++i){
        if(products[i].name == name){
            if((products[i].quantity - amount) < 0){
                cout << "Error: Not enough stock!" << endl;
                return false;
            }
            else{
                products[i].quantity -= amount;
                return true;
            }
        }
        else{
                cout << "Error: Product not Found!\n";
                return false;
        }
    }
}

bool adjust_product_price(product products[], int num, string name, float new_price){
    if (new_price <= 0){
        cout << "Error: Invalid price!" << endl;
        return false;
        }

    for(int i = 0; i < num; ++i){
        if(products[i].name == name){
            products[i].price = new_price;
            return true;
            }
        }
    cout << "Error: Product not Found!\n";
    return false;
}

bool set_product_tags(product products[], int num, string name, string tags[], int num_tags){
    for(int i=0; i < num; ++i){
        if(products[i].name == name){
            if(num_tags > 10){
            cout << "Error: Too many tags!" << endl;
            return false;
            }
            else{
                for(int j = 0; j < num_tags; ++j){
                    products[i].search_tags[j] = tags[j];
                }
                products[i].num_tags = num_tags;
                    return true;
                    }
                }     
        else{
                cout << "Error: Product not Found!\n";
                return false;
        }
    }
}

int main(){
    product products[10];
    int num = 0;
    int input = 1;
    while (input != 4){
        cout << "-----" << endl;
        cout << "Inventory Management System" << endl;
        cout << "1. File Operations" << endl;
        cout << "2. List Products" << endl;
        cout << "3. Product Operations" << endl;
        cout << "4. Exit" << endl;
        cout << "-----" << endl;

        cout << "Enter your choice: " << endl;
        cin >> input;

        if(input == 1){
            cout << "1. Load Products" << endl;
            cout << "2. Save Products" << endl;
            cout << "Enter your choice: ";
            
            int input2;
            cin >> input2;
            cin.ignore();

            if(input2 == 1){
                cout << "Enter file name to load: ";
                string fileName;
                cin >> fileName;
                cin.ignore();
                load(fileName, products, num);
        }
            else if(input2 == 2){
                cout << "Enter file name to save: " << endl;
                string fileName;
                cin >> fileName;
                cin.ignore();
                save(fileName, products, num);
            }
            else{
                cout << "Invalid choice" << endl;
            }
        }
        else if(input == 2){
            cout << "1. List All Products" << endl;
            cout << "2. List Products Sorted by Price" << endl;
            cout << "3. List Products by Manufacturer" << endl;
            cout << "4. List Products Needing Restocking" << endl;
            cout << "Enter your choice: " << endl;

            int input2;
            cin >> input2;
            cin.ignore();

            if(input2 == 1){
                list_all_products(products, num);
        }
            else if(input2 == 2){
                int ascending;
                cout << "Ascending order? (1 for Yes, 0 for No): " << endl;
                cin >> ascending;
                cin.ignore();
                    if (ascending == 1){
                        sort_products_by_price(products, num, true);
                    }
                    else{
                        sort_products_by_price(products, num, false);
                    }
        }
            else if(input2 == 3){
                cout << "Enter manufacturer name: ";
                string manufacturer;
                getline(cin, manufacturer);
                list_all_products_manufacturer(products, num, manufacturer);
        }
            else if(input2 == 4){
                 list_all_products_restocking(products, num);
            }
        }
        else if(input == 3){
            cout << "1. Restock a Product" << endl;
            cout << "2. Sell a Product" << endl;
            cout << "3. Adjust Product Price" << endl;
            cout << "4. Set Product Tags" << endl;
            cout << "Enter your choice: ";
        
            int input2;
            cin >> input2;
            
            if(input2 == 1){
                string restockName;
                int restock;
                cout << "Enter product name to restock: ";
                cin.ignore();
                getline(cin, restockName);  //****
                cout << "Enter amount to restock: ";
                cin >> restock;
                restock_product(products, num, restockName, restock);
            }
            else if(input2 == 2){
                string sellName;
                int sell;
                cout << "Enter product name to sell: ";
                cin.ignore();
                getline(cin, sellName);
                cout << "Enter amount to sell: ";
                cin >> sell;
                sell_product(products, num, sellName, sell);
            }
            else if (input2 == 3){
                string newName;
                float newPrice;
                cout << "Enter product name for price adjustment: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter new price: ";
                cin >> newPrice;
                adjust_product_price(products, num, newName, newPrice);
            }
            else if (input2 == 4){
                string productName;
                int nTags;
                string tags[10];
                cout << "Enter product name to set tags: " << endl;
                cin >> productName;
                cout << "Enter number of tags: " << endl;
                cin >> nTags;
                cout << "Enter tags separated by spaces: " << endl;
                for (int i = 0; i < nTags; ++i){
                    cin >> tags[i];
                }
                set_product_tags(products, num, productName, tags, nTags);
                

            }
            else{
                cout << "Invalid choice" << endl;
            }
        }
        else if(input == 4){
            break;
        }
        else{
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}