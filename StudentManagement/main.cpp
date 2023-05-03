#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<list>
#include<ctime>
<<<<<<< HEAD
#include <fstream>
#include <iostream>
#include <sstream>
=======
#include "tabulate/table.hpp"
>>>>>>> master

using namespace tabulate;
using namespace std;

//forward declarations
class Student;
class User;

class User
{
private:
<<<<<<< HEAD
    string account;//Î¨Ò»±êÊ¶
    string password;
    short role;//Ñ§Éú0£¬ÀÏÊ¦1
public:
    //constructors
    User() {};
    User(string account, string password, short role)
        :account(account), password(password), role(role) {};
    User(User& user)
        :account(user.account), password(user.password), role(user.role) {};
    //getters and setters
    string getAccount() { return account; }
    string getPassword() { return password; }
    short getRole() { return role; }
    void setAccount(string account) { this->account = account; }
    void setPassword(string password) { this->password = password; }
    void setRole(short role) { this->role = role; }
    //methods
    bool login();
    //ºÍUserÏà¹ØµÄ
    bool addOneUser(User user);//Ôö¼ÓÒ»¸öÓÃ»§£¬ÐèÒª¼ìÑéaccountµÄÎ¨Ò»ÐÔ
    bool deleteOneUser(string account);//É¾³ýÒ»¸öÓÃ»§
    bool showOneUser(string account);//²é¿´Ò»¸öÓÃ»§ÐÅÏ¢
    bool showAllUser();//²é¿´ËùÓÐÓÃ»§ÐÅÏ¢
    bool updateOneUser(User user);//ÐÞ¸ÄÓÃ»§ÐÅÏ¢

    //ºÍStudentÏà¹ØµÄ
    // ¹«¹²È¨ÏÞ
    bool updateOneStudent(Student student);//Ñ§ÉúÖ»ÄÜÐÞ¸Ä×Ô¼ºµÄµç»°ºÍÉúÈÕ£¬ÀÏÊ¦¿ÉÒÔÈÎÒâÐÞ¸Ä
    //Ñ§ÉúµÄÈ¨ÏÞ
    bool showOneStudent(string id);//Ñ§ÉúÖ»ÄÜ²é¿´×Ô¼ºµÄÑ§ÉúÐÅÏ¢
    //ÀÏÊ¦µÄÈ¨ÏÞ
    bool showAllStudent();//ÀÏÊ¦¿ÉÒÔ²é¿´ËùÓÐÑ§ÉúÐÅÏ¢
    bool addOneStudent(Student student);//ÀÏÊ¦¿ÉÒÔÔö¼ÓÒ»¸öÑ§Éú
    bool deleteOneStudent(string id);//ÀÏÊ¦¿ÉÒÔÉ¾³ýÒ»¸öÑ§Éú
    bool signUp();//Ö»ÓÐÓµÓÐ¹ÜÀíÔ±ÕËºÅºÍÃÜÂëµÄÀÏÊ¦¿ÉÒÔ×¢²áÐÂÀÏÊ¦
=======
	string account;//Î¨Ò»ï¿½ï¿½Ê¶
	string password;
	short role;//Ñ§ï¿½ï¿½0ï¿½ï¿½ï¿½ï¿½Ê¦1
public:
	//constructors
	User() {};
	User(string account, string password, short role)
		:account(account), password(password), role(role) {};
	User(User& user)
		:account(user.account), password(user.password), role(user.role) {};
	//getters and setters
	string getAccount() { return account; }
	string getPassword() { return password; }
	short getRole() { return role; }
	void setAccount(string account) { this->account = account; }
	void setPassword(string password) { this->password = password; }
	void setRole(short role) { this->role = role; }
	//methods
	bool login(User user);
	//ï¿½ï¿½Userï¿½ï¿½Øµï¿½
	bool addOneUser(User user);//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½Ã»ï¿½ï¿½ï¿½ï¿½ï¿½Òªï¿½ï¿½ï¿½ï¿½accountï¿½ï¿½Î¨Ò»ï¿½ï¿½
	bool deleteOneUser(string account);//É¾ï¿½ï¿½Ò»ï¿½ï¿½ï¿½Ã»ï¿½
	bool showOneUser(string account);//ï¿½é¿´Ò»ï¿½ï¿½ï¿½Ã»ï¿½ï¿½ï¿½Ï¢
	bool showAllUser();//ï¿½é¿´ï¿½ï¿½ï¿½ï¿½ï¿½Ã»ï¿½ï¿½ï¿½Ï¢
	bool updateOneUser(User user);//ï¿½Þ¸ï¿½ï¿½Ã»ï¿½ï¿½ï¿½Ï¢

	//ï¿½ï¿½Studentï¿½ï¿½Øµï¿½
	// ï¿½ï¿½ï¿½ï¿½È¨ï¿½ï¿½
	bool updateOneStudent(Student student);//Ñ§ï¿½ï¿½Ö»ï¿½ï¿½ï¿½Þ¸ï¿½ï¿½Ô¼ï¿½ï¿½Äµç»°ï¿½ï¿½ï¿½ï¿½ï¿½Õ£ï¿½ï¿½ï¿½Ê¦ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Þ¸ï¿½
	//Ñ§ï¿½ï¿½ï¿½ï¿½È¨ï¿½ï¿½
	bool showOneStudent(string id);//Ñ§ï¿½ï¿½Ö»ï¿½Ü²é¿´ï¿½Ô¼ï¿½ï¿½ï¿½Ñ§ï¿½ï¿½ï¿½ï¿½Ï¢
	//ï¿½ï¿½Ê¦ï¿½ï¿½È¨ï¿½ï¿½
	bool showAllStudent();//ï¿½ï¿½Ê¦ï¿½ï¿½ï¿½Ô²é¿´ï¿½ï¿½ï¿½ï¿½Ñ§ï¿½ï¿½ï¿½ï¿½Ï¢
	bool addOneStudent(Student student);//ï¿½ï¿½Ê¦ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½Ñ§ï¿½ï¿½
	bool deleteOneStudent(string id);//ï¿½ï¿½Ê¦ï¿½ï¿½ï¿½ï¿½É¾ï¿½ï¿½Ò»ï¿½ï¿½Ñ§ï¿½ï¿½
	list<Student> loadStudent();//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ñ§ï¿½ï¿½
	bool signUp(User user);//Ö»ï¿½ï¿½Óµï¿½Ð¹ï¿½ï¿½ï¿½Ô±ï¿½ËºÅºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¦ï¿½ï¿½ï¿½ï¿½×¢ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¦
>>>>>>> master
};

class Student
{
private:
    string id;
    string name;
    string identityId;
    string sex;
    string phone;
    string birthday;
    short age;
public:
<<<<<<< HEAD
    //construtors
    Student() {};
    inline Student(string id, string name, string identityId, string sex, string birthday)
        :id(id), name(name), identityId(identityId), sex(sex), birthday(birthday) {
        //¼ÆËãÄêÁä²¢¸³Öµ
        int birthYear = atoi(birthday.substr(0, 4).c_str());
        int birthMonth = atoi(birthday.substr(5, 2).c_str());
        time_t now;
        time(&now);
        tm* nowTime = localtime(&now);
        int nowYear = 1900 + nowTime->tm_year;
        int nowMonth = 1 + nowTime->tm_mon;
        age = nowYear - birthYear;
        if (nowMonth < birthMonth) {
            age--;
        }
    };
    Student(const Student& student)//ÕâÀïµÃÊÇ³£ÒýÓÃ£¬²»È»»á±¨´í
        :id(student.id), name(student.name), identityId(student.identityId), sex(student.sex), phone(student.phone), birthday(student.birthday), age(student.age) {};
    //getters and setters
    string getStudentString()
    {
        return id + " " + name + " " + sex + +" " + phone + " " + birthday + " " + to_string(age);
    }
    string getId() { return id; }
    string getName() { return name; }
    string getSex() { return sex; }
    string getPhone() { return phone; }
    string getBirthday() { return birthday; }
    short getAge() { return age; }
    string getIdentityId() { return identityId; }
    void setId(string id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setSex(string sex) { this->sex = sex; }
    void setPhone(string phone) { this->phone = phone; }
    void setBirthday(string birthday) { this->birthday = birthday; }
    void setAge(short age) { this->age = age; }
    //methods
=======
	//construtors
	Student() {};
	inline Student(string id, string name, string identityId, string sex, string birthday)
		:id(id), name(name), identityId(identityId), sex(sex), birthday(birthday) {
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ä²¢ï¿½ï¿½Öµ
		int birthYear = atoi(birthday.substr(0, 4).c_str());
		int birthMonth = atoi(birthday.substr(5, 2).c_str());
		time_t now;
		time(&now);
		tm* nowTime = localtime(&now);
		int nowYear = 1900 + nowTime->tm_year;
		int nowMonth = 1 + nowTime->tm_mon;
		age = nowYear - birthYear;
		if (nowMonth < birthMonth) {
			age--;
		}
	};
	Student(Student& student)
		:id(student.id), name(student.name), identityId(student.identityId), sex(student.sex), phone(student.phone), birthday(student.birthday), age(student.age) {};
	//getters and setters
	string getId() { return id; }
	string getName() { return name; }
	string getSex() { return sex; }
	string getPhone() { return phone; }
	string getBirthday() { return birthday; }
	short getAge() { return age; }
	void setId(string id) { this->id = id; }
	void setName(string name) { this->name = name; }
	void setSex(string sex) { this->sex = sex; }
	void setPhone(string phone) { this->phone = phone; }
	void setBirthday(string birthday) { this->birthday = birthday; }
	void setAge(short age) { this->age = age; }
	//methods
>>>>>>> master
};

class FileUtil
{
public:
<<<<<<< HEAD
    static list<Student> loadStudent();//¼ÓÔØËùÓÐÑ§Éú
    static list<User> loadUser();//¼ÓÔØËùÓÐÓÃ»§
    static bool saveAllUser(list<User> users);//±£´æËùÓÐÓÃ»§£¬²ÉÓÃ¸²¸ÇµÄ·½Ê½ÊµÏÖ£¬·½±ãÐÞ¸Ä¡¢É¾³ý²Ù×÷µÄÊµÏÖ
    static bool saveAllStudent(list<Student> students);//±£´æËùÓÐÑ§Éú£¬²ÉÓÃ¸²¸ÇµÄ·½Ê½ÊµÏÖ£¬·½±ãÐÞ¸Ä¡¢É¾³ý²Ù×÷µÄÊµÏÖ
=======
	static list<Student> loadStudent();//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ñ§ï¿½ï¿½
	static list<User> loadUser();//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ã»ï¿½
	static bool saveAllUser(list<User> users);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ã»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ã¸ï¿½ï¿½ÇµÄ·ï¿½Ê½Êµï¿½Ö£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Þ¸Ä¡ï¿½É¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Êµï¿½ï¿½
	static bool saveAllStudent(list<Student> students);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ñ§ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ã¸ï¿½ï¿½ÇµÄ·ï¿½Ê½Êµï¿½Ö£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Þ¸Ä¡ï¿½É¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Êµï¿½ï¿½
	static list<User> loadAllUser();//loadUser()ï¿½ï¿½Êµï¿½ï¿½
	static list<Student> loadAllStudent();//loadStudent()ï¿½ï¿½Êµï¿½ï¿½
};

class Panel
{
public:
	void login();//ï¿½ï¿½Â¼ï¿½ï¿½ï¿½
>>>>>>> master
};

//global variables
list<Student> shown_students;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½Ñ§ï¿½ï¿½ï¿½Ð±ï¿½
User now_user;//ï¿½ï¿½Ç°ï¿½ï¿½Â¼ï¿½ï¿½ï¿½Ã»ï¿½

list<Student> FileUtil::loadStudent() {
    list<Student> students;
    ifstream infile("D:\\code\\student\\student.txt");
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return students;
    }
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string id, name, identityId, sex, phone, birthday, ageStr;
        short age;
        getline(iss, id, ',');
        getline(iss, name, ',');
        getline(iss, identityId, ',');
        getline(iss, sex, ',');
        getline(iss, phone, ',');
        getline(iss, birthday, ',');
        getline(iss, ageStr, ',');
        age = stoi(ageStr);
        Student student(id, name, identityId, sex, birthday);
        student.setPhone(phone);
        student.setAge(age);
        students.push_back(student);
    }
    infile.close();
    return students;
}

// ¶¨Òå saveAllStudent º¯Êý
bool FileUtil::saveAllStudent(list<Student> students) {
    ofstream outfile("D:\\code\\student\\student.txt");
    if (!outfile) {
        cerr << "Error opening file!" << endl;
        return false;
    }
    for (auto& student : students) {
        outfile << student.getId() << ','
            << student.getName() << ','
            << student.getIdentityId() << ','
            << student.getSex() << ','
            << student.getPhone() << ','
            << student.getBirthday() << ','
            << student.getAge() << endl;
    }
    outfile.close();
    return true;
}


int main() {
<<<<<<< HEAD
    Student student("202100810120", "ÓÚ¾¸âø", "510105200203280019", "ÄÐ", "2002-06");
    cout << student.getAge() << " " << student.getBirthday() << endl;
    FileUtil file;
    shown_students = FileUtil::loadStudent();
    for (auto it = shown_students.begin(); it != shown_students.end(); it++) {
        cout << it->getStudentString() << endl;
    }
    FileUtil::saveAllStudent(shown_students);

    return 0;
=======
	Student student("202100810120", "ï¿½Ú¾ï¿½ï¿½ï¿½", "510105200203280019", "ï¿½ï¿½", "2002-06");
	cout << student.getAge() << endl;

	Table hellogithub; // ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ hellogithub ï¿½ï¿½ Table ï¿½ï¿½ï¿½ï¿½

	hellogithub.add_row({ "HelloGitHub","HelloMotherfucker~" });
	hellogithub.add_row({ "hellogithub.com" });
	hellogithub[1][0].format()
		.font_style({ FontStyle::underline });
	hellogithub.add_row({ "github.com/521xueweihan/HelloGitHub" });
	hellogithub[2][0].format()
		.font_style({ FontStyle::underline })
		.font_background_color(Color::red)
		.font_style({ FontStyle::bold });
	hellogithub.add_row({ "xueweihan NB!!!" });

	cout << hellogithub << endl;

	system("pause");

	return 0;
>>>>>>> master
}