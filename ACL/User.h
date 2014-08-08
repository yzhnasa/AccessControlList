#ifndef User_H
#define User_H
#include "CommonHeader.h"
#include "File.h"
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20
//#define ESC 0x1b
//const char ESC = 27;

class User{
private:
	string username;
	string password;
	File newFile;
	string rightLevel;//"s" is super user, "a" is average user.
public:
	explicit User();
	explicit User(string username, string password, string rightLevel);
	User(const User &otherUser);
	void setUsername(string username);
	string getUsername();
	void setPassword(string password);
	string getPassword();
	void setRightLevel(string rightLevel);
	string getRightLevel();
	File& creatFile(string fileName);
	bool setOtherUserRight(string otherUsername);
	const User& operator=(const User &otherUser);
	~User();
};

#endif