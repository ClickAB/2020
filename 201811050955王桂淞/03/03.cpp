#include<iostream>
using namespace std;
typedef struct score {
	int chinese, math, english;
	int sum, number;
}student;
int sort(student stu[],int n)
{
	int maxindex;
	student temp;
	for (int i = 0; i < n-1; i++)//选择排序
	{
		maxindex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (stu[j].sum > stu[maxindex].sum) {
				maxindex = j;
			}
			if (stu[j].sum == stu[maxindex].sum)
			{
				if (stu[j].chinese > stu[maxindex].chinese)
				{
					maxindex = j;
				}
				if (stu[j].number < stu[maxindex].number)
				{
					maxindex = j;
				}
			}
		}
		temp = stu[i];
		stu[i] = stu[maxindex];
		stu[maxindex] = temp;
	}
	return 0;

}
int main()
{
	int n;//参加评选的学生人数
	cin >> n;
	student stu[100];
	for (int i = 0; i < n; i++)
	{
		cin >> stu[i].chinese >> stu[i].math >> stu[i].english;
		stu[i].number = i+1;
		stu[i].sum = stu[i].chinese + stu[i].math + stu[i].english;
	}
	sort(stu, n);
	for (int i = 0; i < 5; i++)
	{
		cout << stu[i].number <<" "<< stu[i].sum << endl;
	}
}