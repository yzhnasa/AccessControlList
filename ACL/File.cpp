#include "File.h"

using namespace std;

File::File(){
	usernameAndRight.clear();
}

File::File(string fileName){
	usernameAndRight.clear();
	this->fileName = fileName;
	initalizeFileUserList(fileName);
}

File::File(const File &otherFile){
	if (this != &otherFile){
		this->fileName = otherFile.fileName;
		this->usernameAndRight = otherFile.usernameAndRight;
	}
}

const File &File::operator=(const File &otherFile){
	if (this != &otherFile){
		this->fileName = otherFile.fileName;
		this->usernameAndRight = otherFile.usernameAndRight;
	}
	return *this;
}

void File::initalizeFileUserList(string fileName){
	string fileNameLog = fileName + "Log.txt";
	fstream inputFile(fileNameLog, ios::in);
	if (inputFile.good()){
		string username;
		string right;
		while (!inputFile.eof()){
			getline(inputFile, username);
			if (username.empty())break;
			getline(inputFile, right);
			usernameAndRight[username] = right;
		}
	}
	inputFile.close();
}

void File::setFileName(string fileName){
	this->fileName = fileName;
}

string File::getFileName(){
	return fileName;
}

bool File::searchAFileUser(string otherUsername){
	map<string, string>::iterator itrMap = usernameAndRight.find(otherUsername);
	if (itrMap == usernameAndRight.end()){
		return false;
	}
	tempUserRight = (*itrMap).second;
	return true;
}

bool File::deleteAFileUser(string otherUsername){
	if (searchAFileUser(otherUsername)){
		usernameAndRight.erase(otherUsername);
		return true;
	}
	return false;
}

string  File::displayAFileUser(string otherUsername){
	return tempUserRight;
}

void File::displayAllFileUser(){
	if (!usernameAndRight.empty()){
		map<string, string>::iterator itrMap;
		for (itrMap = usernameAndRight.begin(); itrMap != usernameAndRight.end(); itrMap++){
			cout << "Username: " << (*itrMap).first << endl;
			cout << "Right: " << (*itrMap).second << endl;
			cout << endl;
		}
	}
	else{
		cout << "This file only can be read by superuser." << endl;
	}
}

void File::updateFileUserListLog(){
	string fileNameLog = fileName + "Log.txt";
	fstream outLogFile(fileNameLog, ios::out);
	if (!outLogFile){
		cout << "Create file fail." << endl;
		//exit(1);
		return;
	}
	map<string, string>::iterator itrMap;
	for (itrMap = usernameAndRight.begin(); itrMap != usernameAndRight.end(); itrMap++){
		outLogFile << (*itrMap).first << endl;
		outLogFile << (*itrMap).second << endl;
	}
	outLogFile.close();
}

File::~File(){
	updateFileUserListLog();
}