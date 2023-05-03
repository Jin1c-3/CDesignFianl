#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<list>
#include<ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include "tabulate/table.hpp"

using namespace tabulate;
using namespace std;

//forward declarations
class Student;
class User;

class User
{
private:
	string account;//唯一标识
	string password;
	short role;//学生0，老师1
public:
	//constructors
	User() {};
	User(string account, string password, short role)
		:account(account), password(password), role(role) {};
	User(const User& user)//定义为常拷贝
		:account(user.account), password(user.password), role(user.role) {};
	//getters and setters
	string getAccount() { return account; }
	string getPassword() { return password; }
	string getUser() const {
		return account + "," + password + "," + to_string(role);
	}
	short getRole() { return role; }
	void setAccount(string account) { this->account = account; }
	void setPassword(string password) { this->password = password; }
	void setRole(short role) { this->role = role; }
	//methods
	bool login();
	//和User相关的
	bool addOneUser(User user);//增加一个用户，需要检验account的唯一性
	bool deleteOneUser(string account);//删除一个用户
	bool showOneUser(string account);//查看一个用户信息
	bool showAllUser();//查看所有用户信息
	bool updateOneUser(User user);//修改用户信息

	//和Student相关的
	// 公共权限
	bool updateOneStudent(Student student);//学生只能修改自己的电话和生日，老师可以任意修改
	//学生的权限
	bool showOneStudent(string id);//学生只能查看自己的学生信息
	//老师的权限
	bool showAllStudent();//老师可以查看所有学生信息
	bool addOneStudent(Student student);//老师可以增加一个学生
	bool deleteOneStudent(string id);//老师可以删除一个学生
	bool signUp();//只有拥有管理员账号和密码的老师可以注册新老师
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
	//construtors
	Student() {};
	inline Student(string id, string name, string identityId, string sex, string phone, string birthday)
		:id(id), name(name), identityId(identityId), sex(sex), phone(phone), birthday(birthday) {
		//计算年龄并赋值
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
	Student(const Student& student)//这里得是常引用，不然会报错
		:id(student.id), name(student.name), identityId(student.identityId), sex(student.sex), phone(student.phone), birthday(student.birthday), age(student.age) {};
	//getters and setters
	inline string toString()
	{
		return id + "," + name + "," + identityId + "," + sex + "," + phone + "," + birthday + "," + to_string(age);
	}
	inline vector<string> toVectorString() {
		vector <string> v;
		v.push_back(id);
		v.push_back(name);
		v.push_back(identityId);
		v.push_back(sex);
		v.push_back(phone);
		v.push_back(birthday);
		v.push_back(to_string(age));
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
};

class FileUtil
{
public:
	static list<Student> loadAllStudent();//加载所有学生
	static list<User> loadAllUser();//加载所有用户
	static bool saveAllUser(list<User> users);//保存所有用户，采用覆盖的方式实现，方便修改、删除操作的实现
	static bool saveAllStudent(list<Student> students);//保存所有学生，采用覆盖的方式实现，方便修改、删除操作的实现
};

class Panel
{
public:
	void loading();//通用加载页面
	void menu();//主界面
	void login();//登陆的可视化界面
	void signUp();//注册教师的可视化界面
	void error();//通用错误页面
	void studentOperation(list<Student> students);//显示学生信息，同时包括更新、删除、增加的功能
	void studentOperation(Student student);//显示单个学生信息，同时包括更新电话的功能
	void userOperation(list<User> users);//显示用户信息，同时包括更新、删除、增加的功能。只有拥有管理员账号密码的老师可以进入
};

//global variables
list<Student> shown_students;//正在显示的学生列表
list<User> allUser;//所有用户
User now_user;//当前登录的用户

list<Student> FileUtil::loadAllStudent() {
	list<Student> students;
	ifstream infile("student.txt");
	if (!infile) {
		cerr << "Error opening file!" << endl;
		return students;
	}
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string id, name, identityId, sex, phone, birthday, ageStr;
		getline(iss, id, ',');
		getline(iss, name, ',');
		getline(iss, identityId, ',');
		getline(iss, sex, ',');
		getline(iss, phone, ',');
		getline(iss, birthday, ',');
		getline(iss, ageStr, ',');
		Student student(id, name, identityId, sex, phone, birthday);
		students.push_back(student);
	}
	infile.close();
	return students;
}

// 定义 saveAllStudent 函数
bool FileUtil::saveAllStudent(list<Student> students) {
	ofstream outfile("student.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& student : students) {
		outfile << student.toString() << endl;
	}
	outfile.close();
	return true;
}

// 加载所有用户
list<User> FileUtil::loadAllUser() {
	list<User> users;
	ifstream infile("E:\\code\\StudentManagement\\user.txt");
	if (!infile) {
		cerr << "Error opening file!" << endl;
		return users;
	}
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string account, password, roleStr;
		getline(iss, account, ',');
		getline(iss, password, ',');
		getline(iss, roleStr, ',');
		short role = stoi(roleStr);
		User user(account, password, role);
		users.push_back(user);
	}
	infile.close();
	return users;
}

// 保存所有用户，采用覆盖的方式实现，方便修改、删除操作的实现
bool FileUtil::saveAllUser(list<User> users) {
	ofstream outfile("E:\\code\\StudentManagement\\user.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& user : users) {
		outfile << user.getUser() << endl;
	}
	outfile.close();
	return true;
}

int main() {
	Student yujingyi("202100810120", "于静怡", "123456789012345678", "女", "12345678901", "2000-01");
	cout << yujingyi.toString() << endl;

	Table studentTableTest; // 创建一个叫做 hellogithub 的 Table 对象
	studentTableTest.add_row({ "学号","姓名","身份证号","性别","电话","生日","年龄" });

	shown_students = FileUtil::loadAllStudent();
	for (auto student : shown_students) {
		studentTableTest.add_row({ student.getId(),student.getName(),student.getIdentityId(),student.getSex(),student.getPhone(),student.getBirthday(),to_string(student.getAge()) });
	}
	cout << studentTableTest << endl;
	FileUtil::saveAllStudent(shown_students);

	allUser = FileUtil::loadAllUser();
	for (auto user : allUser) {
		cout << user.getUser() << endl;
	}
	FileUtil::saveAllUser(allUser);

	system("pause");
	return 0;
}