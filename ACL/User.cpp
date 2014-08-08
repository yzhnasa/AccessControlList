#include "User.h"

User::User(){
	username.clear();
	password.clear();
}
User::User(string username, string password, string rightLevel){
	this->username = username;
	this->password = password;
	this->rightLevel = rightLevel;
}

void User::setUsername(string username){
	this->username = username;
}
string User::getUsername(){
	return username;
}

void User::setPassword(string password){
	this->password = password;
}

string User::getPassword(){
	return password;
}
void User::setRightLevel(string rightLevel){
	this->rightLevel = rightLevel;
}

string User::getRightLevel(){
	return rightLevel;
}

File &User::creatFile(string fileName){
	string fileNameLog = fileName + "Log.txt";
	newFile.setFileName(fileName);
	fileName = fileName + ".txt";
	fstream outFile(fileName, ios::out);
	fstream outLogFile(fileNameLog, ios::out);
	if (!outLogFile){
		cout << "Create file fail." << endl;
		exit(1);
	}
	cout << "Create log file success." << endl;
	outLogFile << this->username << endl;
	outLogFile << "111" << endl;
	outLogFile.close();
	// searching filename for avoid same name.
	newFile.usernameAndRight[username] = "111";
	if (!outFile){
		cout << "Create file failed." << endl;
		exit(1);
	}
	cout << "Create success." << endl;
	cout << "Now you can input your information, if you want to stop please press #." << endl;
	char inputChar;
	cin.get(inputChar);
	while (inputChar != '#'){
		cin.get(inputChar);
		if (inputChar != '#')
			outFile.put(inputChar);
	}
	outFile.close();
	return newFile;
}

User::User(const User &otherUser){
	if (this != &otherUser){
		username = otherUser.username;
		password = otherUser.password;
		rightLevel = otherUser.rightLevel;
	}
}

const User &User::operator=(const User &otherUser){
	if (this != &otherUser){
		username = otherUser.username;
		password = otherUser.password;
		rightLevel = otherUser.rightLevel;
	}
	return *this;
}

User::~User(){
	//
}