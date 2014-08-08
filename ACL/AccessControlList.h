#ifndef AccessControlList_H
#define AccessControlList_H
#include "CommonHeader.h"
//#include <windows.h>
#include "File.h"
#include "User.h"



class AccessControlList{
private:
	void initalizeAccessControlList();//Initialize from log file.
	void updateFileListLogFile();
	bool deleteFromAcccessControlList(string fileName);
public:
	File *filePointer;
	vector<File> fileList;//Public can be directly add new file in it.
	explicit AccessControlList();
	bool searchFile(string fileName);
	bool readFile(User &user, File &file);
	bool writeFile(User &user, File &file);
	bool deleteFlie(User &user, File &file);
	void dispalyAUserInformation(User &user, string otherUsername);
	bool setUserRightForAFile(User &user, File &file, string otherUsername);
	bool deleteAUserFromAllFile(User &user, string otherUsername);
	~AccessControlList();
};

#endif