#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;
const int MAX_CARS = 600;
//struct
struct carType{
  enum {MAX_CHARACTERS = 50};
  char name[MAX_CHARACTERS];
  double mpg;
  int cylinders;
  double displacement;
  double horsepower;
  double weight;
  double acceleration;
  int model;
  char origin[MAX_CHARACTERS];
  bool validEntry;
  carType();
};
//default constructor
carType::carType(){
  for(int index = 0; index < carType::MAX_CHARACTERS; ++index){
    name[index] = '\0';
    origin[index] = '\0';
  }
  mpg = 0;
  cylinders = 0;
  displacement = 0;
  horsepower = 0;
  weight = 0;
  acceleration = 0;
  model = 0;
  validEntry = 0;
}

//compares 2 character arrays; returns true if they are the same, false if they are different
bool compareCharArray(char cArray1[], char cArray2[]){
  for(int index = 0; index < carType::MAX_CHARACTERS; ++index){
    if (cArray1[index] != cArray2[index]){
      return false;
    }
  }
  return true;
}

//reads the information for a car in the file
carType readCar(ifstream &infile){
  carType car;
  infile.get(car.name, carType::MAX_CHARACTERS, ';');
  infile.ignore(999, ';');
  infile >> car.mpg;
  infile.ignore(999, ';');
  infile >> car.cylinders;
  infile.ignore(999, ';');
  infile >> car.displacement;
  infile.ignore(999, ';');
  infile >> car.horsepower;
  infile.ignore(999, ';');
  infile >> car.weight;
  infile.ignore(999, ';');
  infile >> car.acceleration;
  infile.ignore(999, ';');
  infile >> car.model;
  infile.ignore(999, ';');
  infile.get(car.origin, carType::MAX_CHARACTERS, '\n');
  car.validEntry = !infile.eof();

  return car;
}

//initially extracts all the car information from the file
int readCarData(carType carList[]){
  ifstream filein("cars.txt");

  int carNum = 0;
    while(filein.peek() != EOF && carNum < MAX_CARS) {
      carList[carNum] = readCar(filein);
      carNum++;
    }
    --carNum;
    return carNum;
}

//prints the car index; if an origin is specified, it only prints cars with that origin
void printCars(carType carList[], int carNum, char origin[]) {
  for(int index = 0; index < carNum; ++index){
    if(carList[index].validEntry != 0 && (compareCharArray(carList[index].origin, origin) || origin[0] == '\0') ){
      cout << "Index " << index << ":  " << carList[index].name << ";" << carList[index].mpg << ";" << carList[index].cylinders << ";" << carList[index].displacement << ";" << carList[index].horsepower << ";" << carList[index].weight << ";" << carList[index].acceleration << ";" << carList[index].model << ";" << carList[index].origin << endl;
    }
    else if(carList[index].validEntry == 0) {
      cout << endl;
    }
  }
}

//invalidates the car that is specified by the user
void removeCar(int carNum, carType carList[]){
  //should give an option to quit
  int input = 0;
  do{
    cout << "Enter the index of the car to remove: ";
    cin >> input;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(carList[input].validEntry != 1 || !(input < carNum && input >= 0)){
      cout << "\n\tThat car index is not valid.\n" << endl;
    }
    else{
      carList[input].validEntry = 0;
      break;
    }
  }while(true);
}

//adds a car to the index if there is space available (the max size actually being the number of cars in the initial index)
void addCar(int carNum, carType carList[]){
  int slot = 0;
  bool space = 0;
  int intInput = 0;
  double doubleInput = 0;
  char charInput;
  carType newCar;
  for(int index = 0; index < carNum; ++index){
    if(carList[index].validEntry != 1){
      slot = index;
      space = 1;
      break;
    }
  }
  if(space == 0){
    cout << "\tThe car database is full, you cannot add another car.\n" << endl;
    return;
  }

  //name
  cout << "Enter the name of the new car: ";
  cin >> charInput;
  cin.getline(newCar.name, carType::MAX_CHARACTERS - 1);
  for(int index = carType::MAX_CHARACTERS - 1; index > 0; --index){
    newCar.name[index] = toupper(newCar.name[index - 1]);
  }
  newCar.name[0] = toupper(charInput);
  //mpg
  do{
    cout << "Enter the miles per gallon of the new car: ";
    cin >> doubleInput;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(!(doubleInput < 1000 && doubleInput >= 0)){
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      newCar.mpg = doubleInput;
      break;
    }
  }while(true);
  //cylinders
  do{
    cout << "Enter the number of cylinders in the new car: ";
    cin >> intInput;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(!(intInput < 50 && intInput >= 0)){
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      newCar.cylinders = intInput;
      break;
    }
  }while(true);
  //displacement
  do{
    cout << "Enter the displacement of the new car: ";
    cin >> doubleInput;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(!(doubleInput < 1000 && doubleInput >= 0)){
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      newCar.displacement = doubleInput;
      break;
    }
  }while(true);
  //horsepower
  do{
    cout << "Enter the horsepower of the new car: ";
    cin >> doubleInput;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(!(doubleInput < 1000 && doubleInput >= 0)){
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      newCar.horsepower = doubleInput;
      break;
    }
  }while(true);
  //weight
  do{
    cout << "Enter the weight of the new car: ";
    cin >> doubleInput;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(!(doubleInput < 10000 && doubleInput >= 0)){
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      newCar.weight = doubleInput;
      break;
    }
  }while(true);
  //acceleration
  do{
    cout << "Enter the acceleration of the new car: ";
    cin >> doubleInput;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(!(doubleInput < 10000 && doubleInput >= 0)){
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      newCar.acceleration = doubleInput;
      break;
    }
  }while(true);
  //model
  do{
    cout << "Enter the model of the new car: ";
    cin >> intInput;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(!(intInput < 100 && intInput >= 0)){
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      newCar.model = intInput;
      break;
    }
  }while(true);
  //origin
  cout << "Enter the geographic origin of the new car: ";
  cin >> charInput;
  cin.getline(newCar.origin, carType::MAX_CHARACTERS - 1);
  for(int index = carType::MAX_CHARACTERS - 1; index > 0; --index){
    newCar.origin[index] = newCar.origin[index - 1];
  }
  newCar.origin[0] = charInput;

  newCar.validEntry = 1;
  carList[slot] = newCar;

  cout << carList[slot].name << " has been added to Index #" << slot << endl;
  return;
}

//displays the menu, with choices for the user to select, and giving an option to quit
int displayMenu(char origin[]){
  int option = 0;
  char charInput;
  cout << "\n\t1. Display Car List" << endl << "\t2. Remove a Car from the List" << endl << "\t3. Add a Car to the List" << endl << "\t4. Display Cars by Origin" << endl << "\t5. Quit\n" << endl;

  while(true){
    cout << "Enter your option: ";
    cin >> option;
      if(!cin){
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "\n\tInvalid input data.\n" << endl;
      }
      else if(!(option <= 5 && option >= 1)){
        cout << "\n\tInvalid input data.\n" << endl;
      }
      else{
        if(option == 4){
          cout << "Enter the origin to search for: ";
          cin >> charInput;
          cin.getline(origin, carType::MAX_CHARACTERS - 1);
          for(int index = carType::MAX_CHARACTERS - 1; index > 0; --index){
            origin[index] = origin[index - 1];
          }
          origin[0] = charInput;
        }
        break;
      }
  }
  return option;
}

//welcome message plays at the start of program
void welcomeMessage(){
  cout << "Welcome to the car index. Here you can add cars to the index, remove cars, and search the index." << endl;
}

//quit message that plays at the end of program
void quitMessage(){
  cout << "Exiting car index." << endl;
}

int main() {
  int carNum = 0;
  char origin[carType::MAX_CHARACTERS] = {'\0'};
  int option = 0;
  carType carList[MAX_CARS];
  carNum = readCarData(carList);
  welcomeMessage();
  while(true){
    for(int index = 0; index < carType::MAX_CHARACTERS; ++index){
      origin[index] = '\0';
    }
    option = displayMenu(origin);
    if(option == 1 || option == 4){
      printCars(carList, carNum, origin);
    }
    else if(option == 2){
      removeCar(carNum, carList);
    }
    else if(option == 3){
      addCar(carNum, carList);
    }
    else{
      quitMessage();
      return 0;
    }
  }
}