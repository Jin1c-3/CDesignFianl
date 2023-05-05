#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<list>
#include<ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <conio.h>
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
	inline string toString() const {
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
	inline string toString() const
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
	static void loading();//通用加载页面
	static void menu();//主界面
	static void login();//登陆的可视化界面
	static void signUp();//注册教师的可视化界面
	static void error();//通用错误页面
	static void studentOperation(list<Student> students);//显示学生信息，同时包括更新、删除、增加的功能
	static void studentOperation(Student student);//显示单个学生信息，同时包括更新电话的功能
	static void userOperation(list<User> users);//显示用户信息，同时包括更新、删除、增加的功能。只有拥有管理员账号密码的老师可以进入
	static void showStudent(list<Student> students);//只负责显示学生信息的表格，其他一概不管
	static void showStudent(Student student);//只负责显示单个学生信息的表格，其他一概不管
	static void showUser(list<User> users);//只负责显示用户信息的表格，其他一概不管
};

//global variables
list<Student> allStudengs;//所有学生
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
		getline(iss, ageStr, '\n');
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
	ifstream infile("user.txt");
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
	ofstream outfile("user.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& user : users) {
		outfile << user.toString() << endl;
	}
	outfile.close();
	return true;
}

void Panel::showStudent(list<Student>students) {
	Table table;
	table.add_row({ "学号","姓名","身份证号","性别","电话","生日","年龄" });
	for (auto student : students) {
		table.add_row({ student.getId(),student.getName(),student.getIdentityId(),student.getSex(),student.getPhone(),student.getBirthday(),to_string(student.getAge()) });
	}
	//第一行的属性值
	table[0].format()
		.font_style({ FontStyle::bold })
		.font_style({ FontStyle::underline })
		.font_background_color(Color::green)
		.font_color(Color::blue);
	//遍历所有行
	for (auto& roe : table) {
		roe.format().font_align(FontAlign::center);
	}
	//表格边框设置
	table.format()
		.multi_byte_characters(true)
		// Font styling
		.font_style({ FontStyle::bold, FontStyle::dark })
		.font_align(FontAlign::center)
		.font_color(Color::red)
		.font_background_color(Color::yellow)
		// Corners
		.corner_top_left("x")
		.corner_top_right("x")
		.corner_bottom_left("x")
		.corner_bottom_right("x")
		.corner_top_left_color(Color::cyan)
		.corner_top_right_color(Color::yellow)
		.corner_bottom_left_color(Color::green)
		.corner_bottom_right_color(Color::red)
		// Borders
		.border_top("*")
		.border_bottom("*")
		.border_left("*")
		.border_right("*")
		.border_left_color(Color::yellow)
		.border_right_color(Color::green)
		.border_top_color(Color::cyan)
		.border_bottom_color(Color::red);
	cout << table << endl;
}

void Panel::showStudent(Student student) {
	list<Student>temp = { student };
	showStudent(temp);
}

void Panel::showUser(list<User> users) {
	Table table;
	table.add_row({ "账号","密码","权限" });
	for (auto user : users) {
		table.add_row({ user.getAccount(),user.getPassword(),to_string(user.getRole()) });
	}
	//第一行的属性值
	table[0].format()
		.font_style({ FontStyle::bold })
		.font_style({ FontStyle::underline })
		.font_background_color(Color::green)
		.font_color(Color::blue);
	//遍历所有行
	for (auto& roe : table) {
		roe.format().font_align(FontAlign::center);
	}
	//遍历第三列的所有单元格
	for (auto& col_cell : table.column(2)) {
		if (col_cell.get_text() == "1") {
			col_cell.format().font_background_color(Color::red);
		}
	}
	//表格边框设置
	table.format()
		.multi_byte_characters(true)
		// Font styling
		.font_style({ FontStyle::bold, FontStyle::dark })
		.font_align(FontAlign::center)
		.font_color(Color::red)
		.font_background_color(Color::yellow)
		// Corners
		.corner_top_left("x")
		.corner_top_right("x")
		.corner_bottom_left("x")
		.corner_bottom_right("x")
		.corner_top_left_color(Color::cyan)
		.corner_top_right_color(Color::yellow)
		.corner_bottom_left_color(Color::green)
		.corner_bottom_right_color(Color::red)
		// Borders
		.border_top("*")
		.border_bottom("*")
		.border_left("*")
		.border_right("*")
		.border_left_color(Color::yellow)
		.border_right_color(Color::green)
		.border_top_color(Color::cyan)
		.border_bottom_color(Color::red);
	cout << table << endl;
}

bool User::login()
{
	string account, password;
	cout << "请输入账号：";
	cin >> account;
	cout << "请输入密码：";
	cin >> password;
	for (auto& user : allUser) {
		if (user.getAccount() == account && user.getPassword() == password) {
			this->account = account;
			this->password = password;
			this->role = user.getRole();
			return true;
		}
	}
	return false;
}

bool User::addOneUser(User user)//增加一个用户，需要检验account的唯一性
{
	for (auto& u : allUser) {
		if (u.getAccount() == user.getAccount()) {
			cout << "账号已存在" << endl;
			return false;
		}
	}
	allUser.push_back(user);
	return true;
}

bool User::deleteOneUser(string account) {
    for (auto it = allUser.begin(); it != allUser.end(); ++it) {
        if (it->getAccount() == account) {
            allUser.erase(it);
            return true;
        }
    }
    cout << "账号不存在" << endl;
    return false;
}


//查看一个用户信息
bool User::showOneUser(string account) 
{
    for (auto& user : allUser) 
	{
        if (user.getAccount() == account)
		{ 
			list<User> tempList;
			tempList.push_back(user);
			Panel::showUser(tempList);
			return true;
		}
    }
    cout << "账号不存在" << endl;
    return false;
}

bool User::showAllUser()//查看所有用户信息
{
	Panel::showUser(allUser);
	return true;
}

//修改用户密码
bool User::updateOneUser(User user) {
    for (auto& u : allUser) {
        if (u.getAccount() == user.getAccount()) {
            // 要求用户输入原密码
            string old_password;
            cout << "请输入原密码：";
            // 将输入的字符替换为'*'
            char ch;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!old_password.empty()) {
                        old_password.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    old_password.push_back(ch);
                    cout << "*";
                }
            }
            cout << endl;
            if (old_password != u.getPassword()) {
                cout << "密码错误" << endl;
                return false;
            }
            // 要求用户输入新密码
            string new_password;
            cout << "请输入新密码：";
            // 将输入的字符替换为'*'
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!new_password.empty()) {
                        new_password.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    new_password.push_back(ch);
                    cout << "*";
                }
            }
            cout << endl;
            u.setPassword(new_password);
            return true;
        }
    }
    cout << "账号不存在" << endl;
    return false;
}

int main() {

	/*测试表格
	Panel::showStudent(shown_students = FileUtil::loadAllStudent());
	FileUtil::saveAllStudent(shown_students);

	Panel::showUser(allUser = FileUtil::loadAllUser());
	FileUtil::saveAllUser(allUser);*/


	/*测试登录
	allUser = FileUtil::loadAllUser();
	User user1;
	if (user1.login())
		cout << "登录成功" << endl;
	else cout << "账号或密码错误" << endl;*/
	
	/*测试添加账户
	allUser = FileUtil::loadAllUser();
	User testUser1("20210080000", "00000000", 1); 
	if (now_user.addOneUser(testUser1))
		cout << "成功添加" << endl;
	User testUser2("20210080000", "00000000", 1);
	if (now_user.addOneUser(testUser2))
		cout << "成功添加" << endl;*/

	/*测试删除账号
	allUser = FileUtil::loadAllUser();
	if (now_user.deleteOneUser("202100810120"))
		cout << "成功删除" << endl;
	now_user.deleteOneUser("202100810120");*/

	/*测试显示单个用户信息
	allUser = FileUtil::loadAllUser();
	now_user.showOneUser("202100810120");
	now_user.showOneUser("20210081020");*/

	/*显示所有用户信息
	allUser = FileUtil::loadAllUser();
	now_user.showAllUser();*/

	/*修改密码
    allUser = FileUtil::loadAllUser();
    User user;
    user.setAccount("202100800000");
    user.updateOneUser(user);
	Panel::showUser(allUser);*/

	system("pause");
	return 0;
}