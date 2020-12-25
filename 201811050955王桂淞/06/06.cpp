#include<iostream>
using namespace std;
class vehicle
{
public:
	vehicle();
	vehicle(int n1, int n2);
	void vehicle_make(int n1, int n2);//用户传参定义
	~vehicle() {};
	virtual  void vehicle_print()
	{
		cout << "vehicle车轮数是" << wheels << endl;
		cout << "vehicle重量为" << weight << endl;
	}
private:
	int wheels;
	int weight;	
};
vehicle::vehicle() {
	this->wheels = 0;
	this->weight = 0;
}
vehicle::vehicle(int n1,int n2)
{
	this->wheels = n1;
	this->weight = n2;
}
void   vehicle::vehicle_make(int n1, int n2)
{
	wheels = n1;
	weight = n2;
}
class car :private vehicle
{
public:
	car()
	{
		wheels = 0;
		weight = 0;
		passenger_load = 0;
	}
	car(int n1, int n2, int n3) :wheels(n1), weight(n2), passenger_load(n3)
	{
	}
	void car_print()
	{
		cout << "car车轮数是" << this->wheels << endl;
		cout << "car重量为" << this->weight << endl;
		cout << "car载人重量是" << this->passenger_load << endl;
	}
	~car() {};
private:
	int wheels;
	int weight;
	int passenger_load;
};
class truck :private vehicle
{
public:
	truck()
	{
		wheels = 0;
		weight = 0;
		passenger_load = 0;
		payload=0;
	}
	void truck_make(int n1, int n2, int n3, int n4);
	virtual void vehicle_print()
	{
		cout << "truck车轮数是" << this->wheels << endl;
		cout << "truck重量为" << this->weight << endl;
		cout << "truck载人重量是" << this->passenger_load << endl;
		cout << "truck载重数是" << this->payload << endl;
	}
private:
	int wheels;
	int weight;
	int passenger_load;
	int payload;


};
void truck::truck_make(int n1, int n2, int n3, int n4)
{
	this->wheels = n1;
	this->weight = n2;
	this->passenger_load=n3;
	this->payload=n4;
}
int main()
{
	
	int a1=5, a2=10;
	int b1 = 15, b2 = 20, b3 = 30;
	int c1 = 25, c2 = 30, c3 = 40,c4=50;
	vehicle A(a1,a2);
	car B(b1,b2,b3);
	truck C;
	C.truck_make(c1, c2, c3, c4);
	A.vehicle_print();
	B.car_print();
	C.vehicle_print();
}