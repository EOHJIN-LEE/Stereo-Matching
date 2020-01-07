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
void imgSharpening(cv::Mat& img, float sigma);

int desresult[128][640 * 800]; //[0~255]

int main()
{


	//�̹��� �ε�
	cv::Mat leftimage = cv::imread("im_left_test.png");

	cv::Mat rightimage = cv::imread("im_right_test.png");



	cv::Mat leftgray;

	cv::Mat rightgray;

	cv::Mat leftresult = cv::Mat::zeros(375, 450, CV_8UC1);

	cv::Mat lefteeee = cv::Mat::zeros(375, 450, CV_8UC1); //������ �߽����� ǥ�����ٰ�



	cv::Mat widelefteeee = cv::Mat::zeros(393, 468, CV_8UC1); //������ �߽����� ǥ�����ٰ�          393, 468    ����ũ 1919�϶�
	//39�϶� 

	cv::cvtColor(leftimage, leftgray, cv::COLOR_BGR2GRAY); //�׷��� �����Ϸ�

	cv::cvtColor(rightimage, rightgray, cv::COLOR_BGR2GRAY); //�׷��� �����Ϸ�



	cv::medianBlur(leftgray, leftgray, 3); //5

	cv::medianBlur(rightgray, rightgray, 3); //5

	//sharpen(leftgray, leftgray);
	//sharpen(rightgray, rightgray);

	cv::equalizeHist(leftgray, leftgray);
	cv::equalizeHist(rightgray, rightgray);

	imgSharpening(leftgray, 10);
	imgSharpening(rightgray, 10);
	//�޵�� ���� ����


	cv::Mat leftwidegray = cv::Mat::zeros(393, 468, CV_8UC1);

	cv::Mat rightwidegray = cv::Mat::zeros(393, 468, CV_8UC1);



	cv::Mat leftimageROI(leftwidegray, cv::Rect(9, 9, leftgray.cols, leftgray.rows));

	cv::Mat rightimageROI(rightwidegray, cv::Rect(9, 9, rightgray.cols, rightgray.rows));



	cv::Mat leftfimage = cv::Mat::zeros(393, 468, CV_8UC1);

	cv::Mat rightfimage = cv::Mat::zeros(393, 468, CV_8UC1);

	cv::Mat rightfimage2 = cv::Mat::zeros(393, 468, CV_8UC1);

	leftgray.copyTo(leftimageROI);

	rightgray.copyTo(rightimageROI);

	const int width = leftimage.cols;
	const int height = leftimage.rows;

	// widegray�� ū �̹����� ���簡 �Ǿ���. 39��ŭ �� �þ��(��谪 ó���� ����)


	leftwidegray.copyTo(leftfimage);

	rightwidegray.copyTo(rightfimage);

	rightwidegray.copyTo(rightfimage2);





	///////////////////////////////////////////////////// ��ũ���� /////////////////////////////////////////////////////

	cv::Mat des = cv::Mat::zeros(19, 19, CV_8UC1); //��ũ����
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
	cv::Point savepoint[361]; //256-> 32 i-> 16����   361(����ũ 19*19)
	/*
	for (int i = 0; i < 256; i++)
	{
		//ù��° ��
		randomreturn(&x1, &y1);
		//printf("x1 : %d, y1 : %d  \n\n", x1, y1);

		///////////////////////
		while (x1 == 39 && y1 == 39) //�߾��϶��� randomreturn �߾��� �ƴҶ����� �ݺ�
		{

			randomreturn(&x1, &y1);

		}
		////////////////////////



		//�ι�° ��
		randomreturn(&x2, &y2);

		////////////////////////
		while (x2 == 39 && y2 == 39) //�߾��϶��� randomreturn �߾��� �ƴҶ����� �ݺ�
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

		start_point = cv::Point(x1 - 39, y1 - 39);
		//printf("start_point x : %d, y : %d\n", start_point.x, start_point.y);
		end_point = cv::Point(x2 - 39, y2 - 39);
		//printf("end_point x : %d, y : %d\n", end_point.x, end_point.y);

		//printf("i : %d, i*2 : %d, i*2 + 1 : \n", i, i*2, i*2 + 1);
		savepoint[2 * i] = cv::Point(x1 - 39, y1 - 39);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2].x, savepoint[i*2].y);
		savepoint[2 * i + 1] = cv::Point(x2 - 39, y2 - 39);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2+1].x, savepoint[i*2+1].y);

	}// 0,1 ¦ 2,3 ¦ 3,4 ¦ �̷��� �̷����
	*/
	     //361
	int k = 0;
	int w = 0;

	for (int i = -9; i < 10; i++)
	{
		
		for (int j = -9; j < 10; j++)
		{
			
			savepoint[k*19 + w] = cv::Point(j, i);
			
			
			w++;
		}
		
		
		k++;
	}
	
	
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
for (int r = 0; r < 375; r++) //�׷��� ����Ҷ��� r+�������� �����ϱ� ����   leftimage.rows
{//375
	printf("%d ��° �� �۾����Դϴ�. \n", r);

	//�߿��Ѱ� �� ���� ���ƴٴϸ鼭 ��
	for (int c = 0; c < leftimage.cols; c++) //���������� ����Ҷ� c
	{
		int whatisbest[450];// col�� 450�̱� ����. ���⿡ ������ �������� ���� �����ش�.


		for (int i = 0; i < 450; i++)
		{
			whatisbest[i] = 110000000;
		}


		//printf("\n���� ����ϰ� �ִ� ��ǥ r : %d c : %d \n", r, c);
		cv::Point kingpoint[361];
		for (int i = 0; i < 361; i++) /// 256���� savepoint
		{
			//printf("savepoint�� ��ġ�� x : %d,y : %d \n", savepoint[i].x, savepoint[i].y);
			kingpoint[i] = cv::Point(c + 9, r + 9) + savepoint[i];

			//printf("kingpoint�� ��ġ�� x : %d,y : %d \n", kingpoint[i].x, kingpoint[i].y);
		}//���� ���� ����� ������ kingpoint�� ����






		//printf("kingpoint�Ϸ�\n");

		for (int rightGo = 0; rightGo < leftimage.cols; rightGo++) // leftimage.col���� c������ ��ȯ �ֳ��ϸ� ������ ���ʺ��� �˻��ϱ� ����
		{


			cv::Point matchpoint[361];
			int temp = 0;
			for (int i1 = 0; i1 < 361; i1++)
			{



				matchpoint[i1] = cv::Point(rightGo + 9, r + 9) + savepoint[i1];

				//printf("matchpoint�� ��ġ�� x : %d,y : %d \n", matchpoint[i1].x, matchpoint[i1].y);

				int k = leftfimage.at<uchar>(kingpoint[i1].y, kingpoint[i1].x) - rightfimage.at<uchar>((matchpoint[i1]).y, matchpoint[i1].x);

				temp = temp + k * k;


				/*
				if (rightGo < c)
				{
					temp = (temp / 2);
				}

				*/
				//printf("%d ��° �������� temp : %d \n", temp);

			}

			//printf("temp ��� %d\n", temp); //�̻��� �κ�


			if (rightGo < c)
			{
				temp = (temp / 2);
			} //���ʿ��ִٸ� ��Ī�� ��Ȯ�ϴٴ� ���� ������


			whatisbest[rightGo] = temp;    //���̰��� ����


			//printf("222222\n"); //�̻��� �κ�
			//printf("������ ��ǥ rightgo = %d, c = %d\n ",rightGo,c); //����
			//**�ش� (ŷ����Ʈ - ������Ʈ)^2�� �Ͻ������� temp ���� �������ְ� �ش� temp�� whatisbest[rightGo]�� �������ش�. �׷��� whatisbest���� ���° �ȼ������� ��갪���� ����Ǿ�����


		}
		//cv::circle(rightfimage2, cv::Point((getMinInt(whatisbest, 450)), r), 5, (0, 0, 255), -1);

		//printf("c���� ��Ī�Ǵ� �Ÿ����� %d\n", (getMinInt(whatisbest, 450) - c));

				if ((abs((getMinInt(whatisbest, 450)) - c) * 4) > 220)
			{
					leftresult.at<uchar>(r, c) = 220;
			}
				else
				{
					leftresult.at<uchar>(r, c) = (abs((getMinInt(whatisbest, 450)) - c) * 4);
				}
			
			//widelefteeee.at<uchar>(r + 39, c + 39) = (abs(getMinInt(whatisbest, 450)) - c) * 4;
			
			
			
			
			//�״����� �ش� ��갪���� ������ ���� �������� ã�Ƴ�����.
			//�׸��� ���� ���� ��� ���� �ȼ��� ��ġ�� ���� c���� ���̰� ���� ���� ����ϰ� �̸�ŭ �̵��ߴٸ� �˷������.


			//����� �� ������ �ش� raw������ ���̰� *4�� ����.

		}
	}

	
	cv::medianBlur(leftresult, leftresult, 3);

	//imgSharpening(leftresult, 3);

	cv::medianBlur(leftresult, leftresult, 3);

	cv::namedWindow("Result");
	

	//des ���
	cv::imshow("Result", leftimageROI);
	cv::imshow("widegray", leftfimage);
	cv::imshow("matching result", rightfimage2);
	cv::imshow("descriptor", des);
	cv::imshow("reo", leftresult);
	cv::imwrite("Result.jpg", leftresult);




	cv::waitKey(0);

	return 0;
}


//x1�� y1�� ���� �������� �ߺ��ǰ� �ؼ� �ش�.
void randomreturn(int *x1, int *y1)
{
	int count = 0; // 1�̸� 1ã��, 2�̸� 2ã��
	int num = 0;

	for (int i = 0; i < 2; i++) //x1,x2,y1,y2 �׹� ã�ƾ��ϱ� ������ ���� 4��
	{ //39 39�� ó�� ������
		count++;
		num = rand() % 100;

		//1%�� Ȯ��

		if (num == 0)
		{


			if (count == 1)
			{
				*x1 = rand() % 3; //0, 1 , 2

			}
			else if (count == 2)
			{
				*y1 = rand() % 3;


			}

		}

		else if (num == 1)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 1 * 3; // 3, 4, 5
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 1 * 3;

			}

		}
		else if (num == 2)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 2 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 2 * 3;

			}

		}

		else if (num == 3)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 3 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 3 * 3;

			}
		}
		//2%�� Ȯ��
		else if (num >= 4 && num <= 5)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 4 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 4 * 3;

			}
		}
		else if (num >= 6 && num <= 7)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 5 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 5 * 3;
			}
		}
		else if (num >= 8 && num <= 9)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 6 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 6 * 3;
			}
		}
		else if (num >= 10 && num <= 11)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 7 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 7 * 3;
			}
		}
		//5%�� Ȯ��
		else if (num >= 12 && num <= 16)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 8 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 8 * 3;
			}
		}
		else if (num >= 17 && num <= 21)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 9 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 9 * 3;
			}
		}
		//7%�� Ȯ��
		else if (num >= 22 && num <= 28)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 10 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 10 * 3;
			}
		}
		//8%�� Ȯ��
		else if (num >= 29 && num <= 36)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 11 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 11 * 3;
			}
		}
		else if (num >= 37 && num <= 44)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 12 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 12 * 3;
			}
		}

		//10%�� Ȯ��(��� ����ó�� �ʿ�X ���� x���̱� ������)
		else if (num >= 45 && num <= 54)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 13 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 13 * 3;
			}
		}

		//8%�� Ȯ��
		else if (num >= 55 && num <= 62)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 14 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 14 * 3;
			}
		}
		else if (num >= 63 && num <= 70)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 15 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 15 * 3;
			}
		}
		//7%�� Ȯ��
		else if (num >= 71 && num <= 77)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 16 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 16 * 3;
			}
		}
		//5%�� Ȯ��
		else if (num >= 78 && num <= 82)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 17 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 17 * 3;
			}
		}
		else if (num >= 83 && num <= 87)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 18 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 18 * 3;
			}
		}
		//2%�� Ȯ��
		else if (num >= 88 && num <= 89)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 19 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 19 * 3;
			}
		}
		else if (num >= 90 && num <= 91)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 20 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 20 * 3;
			}
		}
		else if (num >= 92 && num <= 93)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 21 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 21 * 3;
			}
		}
		else if (num >= 94 && num <= 95)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 22 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 22 * 3;
			}
		}
		//1%�� Ȯ��
		else if (num == 96)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 23 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 23 * 3;
			}
		}
		else if (num == 97)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 24 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 24 * 3;
			}
		}
		else if (num == 98)
		{
			if (count == 1)
			{
				*x1 = rand() % 3 + 25 * 3;
			}
			else if (count == 2)
			{
				*y1 = rand() % 3 + 25 * 3;
			}
		}
		else if (num == 99)
		{
			if (count == 1)
			{
				*x1 = 26 * 3;

				//*x1 = rand() % 3 + 26 * 3;
			}
			else if (count == 2)
			{
				*y1 = 26 * 3;
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


void imgSharpening(cv::Mat& img, float sigma)

{

	cv::Mat tmp;

	cv::GaussianBlur(img, tmp, cv::Size(0, 0), sigma);

	cv::addWeighted(img, 1.5, tmp, -0.5, 0, img);

}



