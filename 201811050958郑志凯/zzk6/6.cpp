#include<iostream>
#include <math.h>
using namespace std;

class vehicle
{
protected:
	int wheels;
	int weight;
public:
	vehicle(int wh, int we)
	{
		wheels = wh;
		weight = we;
	}
	void disp()
	{
		cout << "wheels = " << wheels << ", weight = " << weight << endl;
	}
};
class car : private vehicle
{
	int passenger_load;
public:
	car(int wh, int we, int pa) : vehicle(wh, we)
	{
		passenger_load = pa;
	}
	void disp()
	{
		vehicle::disp();
		cout << "passenger_load = " << passenger_load << endl;
	}
};
class truck : private vehicle
{
	int passenger_load;
	int payload;
public:
	truck(int wh, int we, int pa, int pay) : vehicle(wh, we)
	{
		passenger_load = pa;
		payload = pay;
	}
	void disp()
	{
		vehicle::disp();
		cout << "passenger_load = " << passenger_load << ", payload = " << payload << endl;
	}
};

void main()
{
	int wh·v, we·v, wh·c, we·c, pa·c, wh·t, we·t, pa·t, pay·t;
	cout << "请输入vehicle的wheel和weight：" << endl;
	cin >> wh·v >> we·v;
	cout << "请输入car的wheel、weight和passenger_load：" << endl;
	cin >> wh·c >> we·c >> pa·c;
	cout << "请输入car的wheel、weight、passenger_load和payload：" << endl;
	cin >> wh·t >> we·t >> pa·t >> pay·t;
	cout << "\n" << endl;

	cout << "vehicle：" << endl;
	vehicle v(wh·v, we·v);
	v.disp();
	cout << "\n" << endl;

	cout << "car：" << endl;
	car c(wh·c, we·c, pa·c);
	c.disp();
	cout << "\n" << endl;

	cout << "truck：" << endl;
	truck t(wh·t, we·t, pa·t, pay·t);
	t.disp();
	cout << "\n" << endl;
}