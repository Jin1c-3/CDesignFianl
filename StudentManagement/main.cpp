#include<iostream>
#include<string>
#include<list>
#include<ctime>

using namespace std;

//global variables
list<Student> shown_students;//正在显示的学生列表
User now_user;//当前登录的用户

class User
{
private:
	string account;//唯一标识
	string password;
	short role;//学生0，老师1,管理员3
public:
	//constructors
	User() {};
	User(string account, string password, short role) :account(account), password(password), role(role) {};
	//getters and setters
	string getAccount() { return account; }
	string getPassword() { return password; }
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
	list<User> loadUser();//加载所有用户
	//和Student相关的
	// 公共权限
	bool updateOneStudent(Student student);//学生只能修改自己的电话和生日，老师可以任意修改
	//学生的权限
	bool showOneStudent(string id);//学生只能查看自己的学生信息
	//老师的权限
	bool showAllStudent();//老师可以查看所有学生信息
	bool addOneStudent(Student student);//老师可以增加一个学生
	bool deleteOneStudent(string id);//老师可以删除一个学生
	list<Student> loadStudent();//加载所有学生
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
	inline Student(string id, string name, string identityId, string sex, string birthday)
		:id(id), name(name), identityId(identityId), sex(sex), birthday(birthday) {
		//计算年龄并赋值
		int birthYear = atoi(birthday.substr(0, 4).c_str());
		int birthMonth = atoi(birthday.substr(4, 2).c_str());
		time_t now;
		time(&now);
		tm* nowTime = localtime(&now);
		int nowYear = 1990 + nowTime->tm_year;
		int nowMonth = 1 + nowTime->tm_mon;
		age = nowYear - birthYear;
		if (nowMonth < birthMonth) {
			age--;
		}
	};
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
};

class FileUtil
{
public:
	static bool saveAllUser(list<User> users);//保存所有用户，采用覆盖的方式实现，方便修改、删除操作的实现
	static bool saveAllStudent(list<Student> students);//保存所有学生，采用覆盖的方式实现，方便修改、删除操作的实现
};