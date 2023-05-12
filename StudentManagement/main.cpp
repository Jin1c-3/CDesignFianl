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
	bool showMyself();//学生可以查看自己的信息

	//老师的权限
	bool showOneStudent(string id);//老师可以查看一个学生信息
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
private:
	static Table getStdOuterFrame();
	static Table getStdInnerFrame();
	inline static void pause(string message="系统温馨提示：输入任意键以继续...") {
		cout << message << endl;
		string input_temp;
		getchar();
		getline(cin, input_temp);
	};
public:
	static void loading(string) ;//通用加载页面
	static void menu();//主界面
	static bool login();//登陆的可视化界面
	static void signUp();//注册教师的可视化界面
	static void error(string);//通用错误页面
	static void success(string);//通用成功页面
	static void studentOperation(list<Student> students);//显示学生信息，同时包括更新、删除、增加的功能
	static void studentOperation(Student student);//显示单个学生信息，同时包括更新电话的功能
	static void userOperation(list<User> users);//显示用户信息，同时包括更新、删除、增加的功能。只有拥有管理员账号密码的老师可以进入
	static void showStudent(list<Student> students);//只负责显示学生信息的表格，其他一概不管
	static void showStudent(Student student);//只负责显示单个学生信息的表格，其他一概不管
	static void showUser(list<User> users);//只负责显示用户信息的表格，其他一概不管
};

//global variables
list<Student> allStudengs;//所有学生
list<Student> shownStudents;//正在显示的学生列表
list<User> allUser;//所有用户
User nowUser;//当前登录的用户

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
	for (auto& row : table) {
		row.format().font_align(FontAlign::center);
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

void Panel::loading(string message="正在加载中>>>>>>") {
	for (int i = 0; i < 16; i++) {
		system("cls");

		Table outer_frame = Panel::getStdOuterFrame();
		Table inner_frame = Panel::getStdInnerFrame();
		inner_frame
			.format()
			.width(50);
		inner_frame.add_row({ message })
			.format()
			.font_color(Color::red);

		string loading_strip = "OOO";
		for (int j = 0; j < i; j++) {
			loading_strip += "OOO";
		}
		inner_frame.add_row({ loading_strip })
			.format()
			.font_align(FontAlign::left);

		outer_frame.add_row({ inner_frame });
		cout << outer_frame << endl;

		Sleep(100);
	}
	Sleep(200);

	system("cls");
}

void Panel::error(string message = "发生错误！") {
	system("cls");

	Table outer_frame = Panel::getStdOuterFrame();
	outer_frame
		.format()
		.font_color(Color::red);
	outer_frame.add_row({ message });
	cout << outer_frame << endl;

	Panel::pause();

	system("cls");
}

void Panel::success(string message = "操作成功！") {
	system("cls");

	Table outer_frame = Panel::getStdOuterFrame();
	outer_frame
		.format()
		.font_color(Color::green);
	outer_frame.add_row({ message });
	cout << outer_frame << endl;

	Panel::pause();

	system("cls");
}

Table Panel::getStdOuterFrame() {
	Table mainTable;
	mainTable.add_row({ "学生信息管理系统" });
	mainTable[0][0]
		.format()
		.font_align(FontAlign::center)
		.font_style({ FontStyle::bold })
		.font_background_color(Color::green)
		.font_color(Color::grey);
	return mainTable;
}

Table Panel::getStdInnerFrame() {
	Table table;
	table
		.format()
		.font_align(FontAlign::center);
	return table;
}

bool Panel::login() {
	Table outer_frame = Panel::getStdOuterFrame();

	string account, password;
	system("cls");
	cout << "请输入您的账号：" << endl;
	cin >> account;

	system("cls");
	Table account_frame = Panel::getStdInnerFrame();
	account_frame.add_row({ "账号：" + account })
		.format()
		.width(50)
		.font_align(FontAlign::left)
		.font_color(Color::yellow);
	outer_frame.add_row({ account_frame });
	cout << outer_frame << endl;

	cout<< "请输入您的密码：" << endl;
	char ch = _getch();
	while (ch != '\r') {
		if (ch == 8) {
			if (!password.empty()) {
				password.pop_back();
				cout << "\b \b";
			}
		}
		else {
			password.push_back(ch);
			cout << '*';
		}
		ch = _getch();
	}

	system("cls");
	account_frame.add_row({ "密码：" + password })
		.format()
		.font_color(Color::yellow);
	outer_frame =Panel::getStdOuterFrame();
	outer_frame.add_row({ account_frame });
	cout << outer_frame << endl;

	Panel::pause();

	nowUser.setAccount(account);
	nowUser.setPassword(password);

	Panel::loading("正在登陆中...");

	if (nowUser.login()) {
		Panel::success("恭喜您成功登录！");
		return true;
	}
	else {
		Panel::error("请检查用户名或密码！");
		return false;
	}
}

bool User::login()
{
	for (auto& user : FileUtil::loadAllUser()) {
		if (user.getAccount() == account && user.getPassword() == password) {
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

bool User::updateOneStudent(Student student)//学生只能修改自己的电话和生日，老师可以任意修改
// 检验nowUser的role，如果是0说明是学生，只能修改自己的电话和生日，如果是1说明是老师可以修改任意学生任意信息，
{
	if (nowUser.getRole() == 0) {
		// 如果是学生，只能修改自己的电话和生日
		for (auto& s : allStudengs) {
			if (s.getId() == student.getId()) {
				if (s.getId() != nowUser.getAccount()) {
					cout << "您只能修改自己的信息" << endl;
					return false;
				}
				s.setPhone(student.getPhone());
				s.setBirthday(student.getBirthday());
				cout << "修改成功" << endl;
				return true;
			}
		}
		cout << "学号不存在" << endl;
		return false;
	}
	else if (nowUser.getRole() == 1) {
		// 如果是老师，可以修改任意学生任意信息
		for (auto& s : allStudengs) {
			if (s.getId() == student.getId()) {
				s.setName(student.getName());
				s.setSex(student.getSex());
				s.setPhone(student.getPhone());
				s.setBirthday(student.getBirthday());
				s.setAge(student.getAge());
				cout << "修改成功" << endl;
				return true;
			}
		}
		cout << "学号不存在" << endl;
		return false;
	}
	else {
		// 如果是其他用户，无权修改
		cout << "您无权修改" << endl;
		return false;
	}
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

bool User::showMyself()//在学生表中检索now_user账号，如果检索到显示改学生信息
{
	for (auto& student : allStudengs) {
		if (student.getId() == nowUser.getAccount()) {
			list<Student> tempList;
			tempList.push_back(student);
			Panel::showStudent(tempList);
			return true;
		}
	}
	cout << "无当前用户信息" << endl;
	return false;
}


bool User::showOneStudent(string id)//老师可以查看一个学生信息
{
	for (auto& student : allStudengs) {
		if (student.getId() == id) {
			list<Student> tempList;
			tempList.push_back(student);
			Panel::showStudent(tempList);
			return true;
		}
	}
	cout << "学号不存在" << endl;
	return false;
}

bool User::showAllStudent()//老师可以查看所有学生信息
{
	Panel::showStudent(allStudengs);
	return true;
}

bool User::addOneStudent(Student student)//老师可以增加一个学生
{
	for (auto& s : allStudengs) {
		if (s.getId() == student.getId()) {
			cout << "学号已存在" << endl;
			return false;
		}
	}
	allStudengs.push_back(student);
	return true;
}

bool User::deleteOneStudent(string id)//老师可以删除一个学生
{
	for (auto it = allStudengs.begin(); it != allStudengs.end(); ++it) {
		if (it->getId() == id) {
			allStudengs.erase(it);
			return true;
		}
	}
	cout << "学号不存在" << endl;
	return false;
}

//输入指定管理员账号（admin）和密码(admin)，之后可以注册新老师
bool User::signUp() {
	// 输入管理员账号和密码
	string admin_account = "admin";
	string admin_password = "admin";
	string input_account, input_password;
	cout << "请输入管理员账号： ";
	cin >> input_account;

	cout << "请输入管理员密码： ";
	input_password = "";
	char ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') { // 如果是回退键
			if (!input_password.empty()) {
				input_password.pop_back();
				cout << "\b \b";
			}
		}
		else {
			input_password.push_back(ch);
			cout << "*";
		}
	}
	cout << endl;

	// 判断输入的账号和密码是否正确
	if (admin_account == input_account && admin_password == input_password) {
		// 输入新老师的账号和密码
		string new_account, new_password;
		cout << "请输入新的教师账号： ";
		cin >> new_account;

		cout << "请输入新的教师密码： ";
		new_password = "";
		while ((ch = _getch()) != '\r') {
			if (ch == '\b') { // 如果是回退键
				if (!new_password.empty()) {
					new_password.pop_back();
					cout << "\b \b";
				}
			}
			else {
				new_password.push_back(ch);
				cout << "*";
			}
		}
		cout << endl;

		// 检查是否存在相同的账号
		for (auto& u : allUser) {
			if (u.getAccount() == new_account) {
				cout << "账号已存在" << endl;
				return false;
			}
		}
		// 添加新老师
		User new_teacher(new_account, new_password, 1);
		allUser.push_back(new_teacher);
		FileUtil::saveAllUser(allUser);
		cout << "新老师已添加" << endl;
		return true;
	}
	else {
		cout << "管理员账号或密码错误" << endl;
		return false;
	}
}

int main() {

	/*测试表格
	Panel::showStudent(shown_students = FileUtil::loadAllStudent());
	FileUtil::saveAllStudent(shown_students);

	Panel::showUser(allUser = FileUtil::loadAllUser());
	FileUtil::saveAllUser(allUser);*/


	//测试登录
	/*allUser = FileUtil::loadAllUser();
	User user1;
	if (user1.login())
		cout << "登录成功" << endl;*/
	
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
	
	/*学生显示自己信息
	allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	allStudengs = FileUtil::loadAllStudent();
	Panel::showStudent(allStudengs);
	nowUser.login();
	nowUser.showMyself();*/

	/*老师查看一个学生信息
	allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.showOneStudent("202100810120");*/
	
	//老师查看所有学生信息
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.showAllStudent();*/

	//老师添加一个学生
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	Student student("2021008101112", "静京", "123456789012345633", "男", "12345678802", "2000-03");
	nowUser.addOneStudent(student);
	nowUser.addOneStudent(student);*/
	
	//老师删除一个学生
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	if(nowUser.deleteOneStudent("202100810120"))
		cout <<  "成功删除" << endl;
	nowUser.deleteOneStudent("2021008101112");*/
	
	//老师注册新老师
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.signUp();*/
	
	//学生修改自己信息
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.login();
	Student student("202100810120", "静京", "123456789012345633", "男", "12345678802", "2000-03");
	nowUser.updateOneStudent(student);*/
	
	Panel::login();

	system("pause");
	return 0;
}