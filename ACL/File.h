#ifndef _File_H
#define _File_H
#include "CommonHeader.h"

//R:100, W:010, O:111, RW:110
class File{
private:
	string fileName;
	//string filePath;
	void initalizeFileUserList(string fileName);
	void updateFileUserListLog();
public:
	string tempUserRight;
	map<string, string> usernameAndRight;
	explicit File();
	explicit File(string fileName);
	explicit File(const File &otherFile);
	void setFileName(string fileName);
	string getFileName();
	const File& operator= (const File &otherUser);
	bool searchAFileUser(string otherUsername);
	bool deleteAFileUser(string otherUsername);
	string displayAFileUser(string otherUsername);
	void displayAllFileUser();

	//void setFilePath(string filePath);
	//string getFilePath();
	~File();
};
#endif