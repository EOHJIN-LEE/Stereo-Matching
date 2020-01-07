#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include<time.h>

void randomreturn(int *x1, int *y1);
int pow1(int x, int y);
int getMinInt(int* n, int size);


int desresult[128][640 * 800]; //[0~255]

int main()
{


	//�̹��� �ε�
	cv::Mat leftimage = cv::imread("im_left_test.png");

	cv::Mat rightimage = cv::imread("im_right_test.png");



	cv::Mat leftgray;

	cv::Mat rightgray;



	cv::Mat lefteeee = cv::Mat::zeros(375, 450, CV_8UC1); //������ �߽����� ǥ�����ٰ�

	cv::Mat widelefteeee = cv::Mat::zeros(509, 584, CV_8UC1); //������ �߽����� ǥ�����ٰ�


	cv::cvtColor(leftimage, leftgray, cv::COLOR_BGR2GRAY); //�׷��� �����Ϸ�

	cv::cvtColor(rightimage, rightgray, cv::COLOR_BGR2GRAY); //�׷��� �����Ϸ�



	cv::medianBlur(leftgray, leftgray, 3);

	cv::medianBlur(rightgray, rightgray, 3);

	//�޵�� ���� ����


	cv::Mat leftwidegray = cv::Mat::zeros(509, 584, CV_8UC1);

	cv::Mat rightwidegray = cv::Mat::zeros(509, 584, CV_8UC1);



	cv::Mat leftimageROI(leftwidegray, cv::Rect(67, 67, leftgray.cols, leftgray.rows));

	cv::Mat rightimageROI(rightwidegray, cv::Rect(67, 67, rightgray.cols, rightgray.rows));



	cv::Mat leftfimage = cv::Mat::zeros(509, 584, CV_8UC1);

	cv::Mat rightfimage = cv::Mat::zeros(509, 584, CV_8UC1);

	cv::Mat rightfimage2 = cv::Mat::zeros(509, 584, CV_8UC1);

	leftgray.copyTo(leftimageROI);

	rightgray.copyTo(rightimageROI);

	const int width = leftimage.cols;
	const int height = leftimage.rows;

	// widegray�� ū �̹����� ���簡 �Ǿ���. 13��ŭ �� �þ��(��谪 ó���� ����)


	leftwidegray.copyTo(leftfimage);

	rightwidegray.copyTo(rightfimage);

	rightwidegray.copyTo(rightfimage2);





	///////////////////////////////////////////////////// ��ũ���� /////////////////////////////////////////////////////

	cv::Mat des = cv::Mat::zeros(135, 135, CV_8UC1); //��ũ����
	//���� ������ �����ϴ� �κ�(�߾ӿ� ������ ��������)

	srand(time(NULL));
	int num = rand() % 100;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int x1x2equal = 0;// 0�̸� ���� ������ 1�̸� ������(����)
	int count = 0; // 1�̸� 1ã��, 2�̸� 2ã��
	int county = 0; // 1�̸� 1ã��, 2�̸� 2ã��

	//x1,x2ã��
	cv::Point savepoint[145]; //256-> 32 i-> 16���� 64+ 81 = 145 + 60 = 205
	
							  
							  /*
	for (int i = 0; i < 60; i++) //64->60���� �ٲ㺽
	{
		//ù��° ��
		randomreturn(&x1, &y1);
		//printf("x1 : %d, y1 : %d  \n\n", x1, y1);

		///////////////////////
		while (x1 == 13 && y1 == 13) //�߾��϶��� randomreturn �߾��� �ƴҶ����� �ݺ�
		{

			randomreturn(&x1, &y1);

		}
		////////////////////////



		//�ι�° ��
		randomreturn(&x2, &y2);

		////////////////////////
		while (x2 == 13 && y2 == 13) //�߾��϶��� randomreturn �߾��� �ƴҶ����� �ݺ�
		{

			randomreturn(&x2, &y2);

		}
		///////////////////////

		while (x1 == x2 && y1 == y2)
		{

			randomreturn(&x2, &y2);

		}

		cv::Point start_point(x1, y1);		//line�� ������ 

		cv::Point end_point(x2, y2);	//line�� ����	

		// �Ķ��� ������ �׸���. BGR����
		cv::circle(des, start_point, 0.1, (0, 0, 255), -1); //��ŸƮ ����Ʈ�� ����
		cv::circle(des, end_point, 0.1, (0, 255, 0), -1); //���� ����Ʈ�� ����
		//���� �� �Լ��ȿ��ٰ� ���� 2��vector(x,y) �迭���� �ؾ��� Ȧ���� x1 ¦���� x2

		start_point = cv::Point(x1 - 13, y1 - 13);
		//printf("start_point x : %d, y : %d\n", start_point.x, start_point.y);
		end_point = cv::Point(x2 - 13, y2 - 13);
		//printf("end_point x : %d, y : %d\n", end_point.x, end_point.y);
		


		//printf("i : %d, i*2 : %d, i*2 + 1 : \n", i, i*2, i*2 + 1);
		//savepoint[2 * i] = cv::Point(x1 - 13, y1 - 13);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2].x, savepoint[i*2].y);
		//savepoint[2 * i + 1] = cv::Point(x2 - 13, y2 - 13);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2+1].x, savepoint[i*2+1].y);

	}// 0,1 ¦ 2,3 ¦ 3,4 ¦ �̷��� �̷����
	*/


	int k = 0; //���°�ΰ�

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			cv::circle(des, cv::Point(j, i) , 0.1, (0, 0, 255), -1);

			savepoint[4 * i + j] = cv::Point(j - 67, i - 67);
			
		}
	}
	// ���� �� �簢��

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cv::circle(des, cv::Point(j + 130, i), 0.1, (0, 0, 255), -1);

			savepoint[4 * i + j + 16] = cv::Point((j - 67) + 130, i - 67); //9�� �����ִ� ������ *��ġ�̵�*
			
		}
	}
	// ������ �� �簢��

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			cv::circle(des, cv::Point(j, i + 130), 0.1, (0, 0, 255), -1);

			//desǥ�ÿ�

			savepoint[4 * i + j + 32] = cv::Point((j - 67), (i - 67) + 130); //9�� �����ִ� ������ *��ġ�̵�*
			
		}
	}
	// ���� �Ʒ� �簢��

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			cv::circle(des, cv::Point(j + 130, i + 130), 0.1, (0, 0, 255), -1);

			//desǥ�ÿ�
			savepoint[5 * i + j + 48] = cv::Point((j - 67) + 130, (i - 67) + 130); //9�� �����ִ� ������ *��ġ�̵�*
			
		}
	}
	//������ �Ʒ� �簢��
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
		
			cv::circle(des, cv::Point(j + 63, i + 63), 0.1, (0, 0, 255), -1);

			savepoint[5 * i + j + 64] = cv::Point((j - 67) + 63, (i - 67) + 63);
			
		}
	}

	

	// ��� �簢�� 5 by 5
	


	//��������� descriptor ����


	//************************* ��ŸƮ ����Ʈ�� ���� ����Ʈ�� ���� ������ �ʿ�� ���� ****************************

	//////////////////////////////////////////////////��ũ���� ��///////////////////////////////////////////////////////////////



	 // -�϶��� ���� �¼��� �۵� printf("\n\n\n pow %d   %d",pow1(-5,2), int(-4));




	///////////////////////******************************************************************************************����*********************************************************////////
	/////////////////////////////////////////////////ù��° ������ ��ũ������ ����� �ι�° ������ ��ũ������ ������ ��� ���� ���� ���̸� ���̴� ���� ����ִ��� Ȯ���ϱ�////////////

	//int nn[8] = { 1, 2, -1,5,-10,-7,2,5 };

	//printf("���� ���� �迭�� ���⿡ : %d",getMinInt(nn, 8)); //����üũ �Ϸ�

	//cv::Point initialpoint(500, 0);

	//cv::circle(leftimageROI, initialpoint, 200, (0, 0, 255), -1); //��ŸƮ ����Ʈ�� ����
	// �����Ϸ� ù��°�� x �ι�°�� y








	

	
	
	//ù��° ������� �߾���(r,c)�� �ش� ��(col)�� ���ƴٴϸ� ���Ѵ�.//
	for (int r = 200; r < 220; r++) //�׷��� ����Ҷ��� r+13�� ������� 13,13�������� �����ϱ� ����   leftimage.rows
	{


		//�߿��Ѱ� �� ���� ���ƴٴϸ鼭 ��
		for (int c = 0; c < leftimage.cols; c++) //���������� ����Ҷ� c+13
		{
			//printf("\n���� ����ϰ� �ִ� ��ǥ r : %d c : %d \n", r, c);
			cv::Point kingpoint[145];
			for (int i = 0; i < 145; i++) /// 256���� savepoint
			{
				//printf("savepoint�� ��ġ�� x : %d,y : %d \n", savepoint[i].x, savepoint[i].y);
				kingpoint[i] = cv::Point(c + 67, r + 67) + savepoint[i];

				//printf("kingpoint�� ��ġ�� x : %d,y : %d \n", kingpoint[i].x, kingpoint[i].y);
			}//���� ���� ����� ������ kingpoint�� ����


			int whatisbest[450];// col�� 450�̱� ����. ���⿡ ������ �������� ���� �����ش�.

			for (int i = 0; i < 450; i++)
			{
				whatisbest[i] = 110000000;
			}

			//printf("kingpoint�Ϸ�\n");

			for (int rightGo = 0; rightGo < leftimage.cols; rightGo++)
			{
				cv::Point matchpoint[145];
				int temp = 0;
				for (int i1 = 0; i1 < 145; i1++)
				{

					matchpoint[i1] = cv::Point(rightGo + 67, r + 67) + savepoint[i1];

					//printf("matchpoint�� ��ġ�� x : %d,y : %d \n", matchpoint[i1].x, matchpoint[i1].y);


					temp = temp + pow1((leftfimage.at<uchar>(kingpoint[i1].y, kingpoint[i1].x) - rightfimage.at<uchar>((matchpoint[i1]).y, matchpoint[i1].x)), 2);

					//printf("%d ��° �������� temp : %d \n", temp);

				}

				//printf("temp ��� %d\n", temp); //�̻��� �κ�


				whatisbest[rightGo] = temp;    //���̰��� ����

				//printf("������ ��ǥ rightgo = %d, c = %d\n ",rightGo,c); ����
				//**�ش� (ŷ����Ʈ - ������Ʈ)^2�� �Ͻ������� temp ���� �������ְ� �ش� temp�� whatisbest[rightGo]�� �������ش�. �׷��� whatisbest���� ���° �ȼ������� ��갪���� ����Ǿ�����


			}
			cv::circle(rightfimage2, cv::Point((getMinInt(whatisbest, 450)), r), 5, (0, 0, 255), -1);

			//printf("c���� ��Ī�Ǵ� �Ÿ����� %d\n", (getMinInt(whatisbest, 450) - c));
			widelefteeee.at<uchar>(r + 67, c + 67) = (abs(getMinInt(whatisbest, 450)) - c) * 4;

			//�״����� �ش� ��갪���� ������ ���� �������� ã�Ƴ�����.
			//�׸��� ���� ���� ��� ���� �ȼ��� ��ġ�� ���� c���� ���̰� ���� ���� ����ϰ� �̸�ŭ �̵��ߴٸ� �˷������.


			//����� �� ������ �ش� raw������ ���̰� *4�� ����.

		}
	}
	
	




	
	///////////////////////////////////





	






	cv::namedWindow("Result");


	//des ���
	cv::imshow("Result", leftimageROI);
	cv::imshow("widegray", leftfimage);
	cv::imshow("matching result", rightfimage2);
	cv::imshow("descriptor", des);
	cv::imshow("reo", widelefteeee);
	cv::imwrite("Result.jpg", widelefteeee);




	cv::waitKey(0);

	return 0;
}


//x1�� y1�� ���� �������� �ߺ��ǰ� �ؼ� �ش�.
void randomreturn(int *x1, int *y1)
{
	int count = 0; // 1�̸� 1ã��, 2�̸� 2ã��
	int num = 0;

	for (int i = 0; i < 2; i++) //x1,x2,y1,y2 �׹� ã�ƾ��ϱ� ������ ���� 4��
	{ //13 13�� ó�� ������
		count++;
		num = rand() % 100;

		//1%�� Ȯ��

		if (num == 0)
		{


			if (count == 1)
			{
				*x1 = 0;

			}
			else if (count == 2)
			{
				*y1 = 0;


			}

		}

		else if (num == 1)
		{
			if (count == 1)
			{
				*x1 = 1;
			}
			else if (count == 2)
			{
				*y1 = 1;

			}

		}
		else if (num == 2)
		{
			if (count == 1)
			{
				*x1 = 2;
			}
			else if (count == 2)
			{
				*y1 = 2;

			}

		}

		else if (num == 3)
		{
			if (count == 1)
			{
				*x1 = 3;
			}
			else if (count == 2)
			{
				*y1 = 3;

			}
		}
		//2%�� Ȯ��
		else if (num >= 4 && num <= 5)
		{
			if (count == 1)
			{
				*x1 = 4;
			}
			else if (count == 2)
			{
				*y1 = 4;

			}
		}
		else if (num >= 6 && num <= 7)
		{
			if (count == 1)
			{
				*x1 = 5;
			}
			else if (count == 2)
			{
				*y1 = 5;
			}
		}
		else if (num >= 8 && num <= 9)
		{
			if (count == 1)
			{
				*x1 = 6;
			}
			else if (count == 2)
			{
				*y1 = 6;
			}
		}
		else if (num >= 10 && num <= 11)
		{
			if (count == 1)
			{
				*x1 = 7;
			}
			else if (count == 2)
			{
				*y1 = 7;
			}
		}
		//5%�� Ȯ��
		else if (num >= 12 && num <= 16)
		{
			if (count == 1)
			{
				*x1 = 8;
			}
			else if (count == 2)
			{
				*y1 = 8;
			}
		}
		else if (num >= 17 && num <= 21)
		{
			if (count == 1)
			{
				*x1 = 9;
			}
			else if (count == 2)
			{
				*y1 = 9;
			}
		}
		//7%�� Ȯ��
		else if (num >= 22 && num <= 28)
		{
			if (count == 1)
			{
				*x1 = 10;
			}
			else if (count == 2)
			{
				*y1 = 10;
			}
		}
		//8%�� Ȯ��
		else if (num >= 29 && num <= 36)
		{
			if (count == 1)
			{
				*x1 = 11;
			}
			else if (count == 2)
			{
				*y1 = 11;
			}
		}
		else if (num >= 37 && num <= 44)
		{
			if (count == 1)
			{
				*x1 = 12;
			}
			else if (count == 2)
			{
				*y1 = 12;
			}
		}

		//10%�� Ȯ��(��� ����ó�� �ʿ�X ���� x���̱� ������)
		else if (num >= 45 && num <= 54)
		{
			if (count == 1)
			{
				*x1 = 13;
			}
			else if (count == 2)
			{
				*y1 = 13;
			}
		}

		//8%�� Ȯ��
		else if (num >= 55 && num <= 62)
		{
			if (count == 1)
			{
				*x1 = 14;
			}
			else if (count == 2)
			{
				*y1 = 14;
			}
		}
		else if (num >= 63 && num <= 70)
		{
			if (count == 1)
			{
				*x1 = 15;
			}
			else if (count == 2)
			{
				*y1 = 15;
			}
		}
		//7%�� Ȯ��
		else if (num >= 71 && num <= 77)
		{
			if (count == 1)
			{
				*x1 = 16;
			}
			else if (count == 2)
			{
				*y1 = 16;
			}
		}
		//5%�� Ȯ��
		else if (num >= 78 && num <= 82)
		{
			if (count == 1)
			{
				*x1 = 17;
			}
			else if (count == 2)
			{
				*y1 = 17;
			}
		}
		else if (num >= 83 && num <= 87)
		{
			if (count == 1)
			{
				*x1 = 18;
			}
			else if (count == 2)
			{
				*y1 = 18;
			}
		}
		//2%�� Ȯ��
		else if (num >= 88 && num <= 89)
		{
			if (count == 1)
			{
				*x1 = 19;
			}
			else if (count == 2)
			{
				*y1 = 19;
			}
		}
		else if (num >= 90 && num <= 91)
		{
			if (count == 1)
			{
				*x1 = 20;
			}
			else if (count == 2)
			{
				*y1 = 20;
			}
		}
		else if (num >= 92 && num <= 93)
		{
			if (count == 1)
			{
				*x1 = 21;
			}
			else if (count == 2)
			{
				*y1 = 21;
			}
		}
		else if (num >= 94 && num <= 95)
		{
			if (count == 1)
			{
				*x1 = 22;
			}
			else if (count == 2)
			{
				*y1 = 22;
			}
		}
		//1%�� Ȯ��
		else if (num == 96)
		{
			if (count == 1)
			{
				*x1 = 23;
			}
			else if (count == 2)
			{
				*y1 = 23;
			}
		}
		else if (num == 97)
		{
			if (count == 1)
			{
				*x1 = 24;
			}
			else if (count == 2)
			{
				*y1 = 24;
			}
		}
		else if (num == 98)
		{
			if (count == 1)
			{
				*x1 = 25;
			}
			else if (count == 2)
			{
				*y1 = 25;
			}
		}
		else if (num == 99)
		{
			if (count == 1)
			{
				*x1 = 26;
			}
			else if (count == 2)
			{
				*y1 = 26;
			}
		}



	}


	//*x1 = 4;
	//*y1 = 3;
}
//��Ʈ�� ���� �����ش�.
int pow1(int x, int y)
{
	int i;
	int ret_val;
	if (y == 0)
	{
		return 1;
	}
	ret_val = x;

	for (i = 0; i < y - 1; i++)
	{
		ret_val = ret_val * x;
	}
	return ret_val;
}


int getMinInt(int* n, int size) {
	int min = n[0];
	int num = 0;
	int result = 0;
	for (int i = 1; i < size; i++)
	{
		num++;
		if (n[i] < min && n[i] > 0)
		{
			min = n[i];
			result = num;
		}
	}


	return result;
}