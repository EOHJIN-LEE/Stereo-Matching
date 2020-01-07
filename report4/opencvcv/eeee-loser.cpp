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


	//이미지 로드
	cv::Mat leftimage = cv::imread("im_left_test.png");

	cv::Mat rightimage = cv::imread("im_right_test.png");



	cv::Mat leftgray;

	cv::Mat rightgray;



	cv::Mat lefteeee = cv::Mat::zeros(375, 450, CV_8UC1); //왼쪽을 중심으로 표기해줄곳

	cv::Mat widelefteeee = cv::Mat::zeros(509, 584, CV_8UC1); //왼쪽을 중심으로 표기해줄곳


	cv::cvtColor(leftimage, leftgray, cv::COLOR_BGR2GRAY); //그레이 스케일로

	cv::cvtColor(rightimage, rightgray, cv::COLOR_BGR2GRAY); //그레이 스케일로



	cv::medianBlur(leftgray, leftgray, 3);

	cv::medianBlur(rightgray, rightgray, 3);

	//메디안 필터 적용


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

	// widegray에 큰 이미지로 복사가 되었음. 13만큼 더 늘어났음(경계값 처리를 위해)


	leftwidegray.copyTo(leftfimage);

	rightwidegray.copyTo(rightfimage);

	rightwidegray.copyTo(rightfimage2);





	///////////////////////////////////////////////////// 디스크립터 /////////////////////////////////////////////////////

	cv::Mat des = cv::Mat::zeros(135, 135, CV_8UC1); //디스크립터
	//라인 패턴을 생성하는 부분(중앙에 가깝게 랜덤으로)

	srand(time(NULL));
	int num = rand() % 100;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int x1x2equal = 0;// 0이면 같지 않은거 1이면 같은거(구분)
	int count = 0; // 1이면 1찾기, 2이면 2찾기
	int county = 0; // 1이면 1찾기, 2이면 2찾기

	//x1,x2찾기
	cv::Point savepoint[145]; //256-> 32 i-> 16으로 64+ 81 = 145 + 60 = 205
	
							  
							  /*
	for (int i = 0; i < 60; i++) //64->60개로 바꿔봄
	{
		//첫번째 점
		randomreturn(&x1, &y1);
		//printf("x1 : %d, y1 : %d  \n\n", x1, y1);

		///////////////////////
		while (x1 == 13 && y1 == 13) //중앙일때는 randomreturn 중앙이 아닐때까지 반복
		{

			randomreturn(&x1, &y1);

		}
		////////////////////////



		//두번째 점
		randomreturn(&x2, &y2);

		////////////////////////
		while (x2 == 13 && y2 == 13) //중앙일때는 randomreturn 중앙이 아닐때까지 반복
		{

			randomreturn(&x2, &y2);

		}
		///////////////////////

		while (x1 == x2 && y1 == y2)
		{

			randomreturn(&x2, &y2);

		}

		cv::Point start_point(x1, y1);		//line의 시작점 

		cv::Point end_point(x2, y2);	//line의 끝점	

		// 파랑색 선으로 그리기. BGR순서
		cv::circle(des, start_point, 0.1, (0, 0, 255), -1); //스타트 포인트의 점들
		cv::circle(des, end_point, 0.1, (0, 255, 0), -1); //엔드 포인트의 점들
		//이제 위 함수안에다가 최종 2차vector(x,y) 배열저장 해야함 홀수는 x1 짝수는 x2

		start_point = cv::Point(x1 - 13, y1 - 13);
		//printf("start_point x : %d, y : %d\n", start_point.x, start_point.y);
		end_point = cv::Point(x2 - 13, y2 - 13);
		//printf("end_point x : %d, y : %d\n", end_point.x, end_point.y);
		


		//printf("i : %d, i*2 : %d, i*2 + 1 : \n", i, i*2, i*2 + 1);
		//savepoint[2 * i] = cv::Point(x1 - 13, y1 - 13);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2].x, savepoint[i*2].y);
		//savepoint[2 * i + 1] = cv::Point(x2 - 13, y2 - 13);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2+1].x, savepoint[i*2+1].y);

	}// 0,1 짝 2,3 짝 3,4 짝 이렇게 이루어짐
	*/


	int k = 0; //몇번째인가

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			cv::circle(des, cv::Point(j, i) , 0.1, (0, 0, 255), -1);

			savepoint[4 * i + j] = cv::Point(j - 67, i - 67);
			
		}
	}
	// 왼쪽 위 사각형

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cv::circle(des, cv::Point(j + 130, i), 0.1, (0, 0, 255), -1);

			savepoint[4 * i + j + 16] = cv::Point((j - 67) + 130, i - 67); //9를 더해주는 이유는 *위치이동*
			
		}
	}
	// 오른쪽 위 사각형

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			cv::circle(des, cv::Point(j, i + 130), 0.1, (0, 0, 255), -1);

			//des표시용

			savepoint[4 * i + j + 32] = cv::Point((j - 67), (i - 67) + 130); //9를 더해주는 이유는 *위치이동*
			
		}
	}
	// 왼쪽 아래 사각형

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			cv::circle(des, cv::Point(j + 130, i + 130), 0.1, (0, 0, 255), -1);

			//des표시용
			savepoint[5 * i + j + 48] = cv::Point((j - 67) + 130, (i - 67) + 130); //9를 더해주는 이유는 *위치이동*
			
		}
	}
	//오른쪽 아래 사각형
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
		
			cv::circle(des, cv::Point(j + 63, i + 63), 0.1, (0, 0, 255), -1);

			savepoint[5 * i + j + 64] = cv::Point((j - 67) + 63, (i - 67) + 63);
			
		}
	}

	

	// 가운데 사각형 5 by 5
	


	//여기까지가 descriptor 생성


	//************************* 스타트 포인트와 엔드 포인트를 따로 구별할 필요는 없음 ****************************

	//////////////////////////////////////////////////디스크립터 끝///////////////////////////////////////////////////////////////



	 // -일때도 재대로 승수가 작동 printf("\n\n\n pow %d   %d",pow1(-5,2), int(-4));




	///////////////////////******************************************************************************************시작*********************************************************////////
	/////////////////////////////////////////////////첫번째 영상의 디스크립터의 점들과 두번째 영상의 디스크립터의 점들을 빼어서 가장 작은 차이를 보이는 점이 어디있는지 확인하기////////////

	//int nn[8] = { 1, 2, -1,5,-10,-7,2,5 };

	//printf("가장 작은 배열은 여기에 : %d",getMinInt(nn, 8)); //정상체크 완료

	//cv::Point initialpoint(500, 0);

	//cv::circle(leftimageROI, initialpoint, 200, (0, 0, 255), -1); //스타트 포인트의 점들
	// 검증완료 첫번째가 x 두번째가 y








	

	
	
	//첫번째 영상들의 중앙점(r,c)가 해당 열(col)을 돌아다니며 비교한다.//
	for (int r = 200; r < 220; r++) //그래도 계산할때는 r+13을 해줘야함 13,13에서부터 시작하기 때문   leftimage.rows
	{


		//중요한건 이 열이 돌아다니면서 비교
		for (int c = 0; c < leftimage.cols; c++) //마찬가지로 계산할때 c+13
		{
			//printf("\n현재 계산하고 있는 좌표 r : %d c : %d \n", r, c);
			cv::Point kingpoint[145];
			for (int i = 0; i < 145; i++) /// 256개의 savepoint
			{
				//printf("savepoint의 위치들 x : %d,y : %d \n", savepoint[i].x, savepoint[i].y);
				kingpoint[i] = cv::Point(c + 67, r + 67) + savepoint[i];

				//printf("kingpoint의 위치들 x : %d,y : %d \n", kingpoint[i].x, kingpoint[i].y);
			}//비교할 점을 골랐음 그점은 kingpoint에 저장


			int whatisbest[450];// col이 450이기 때문. 여기에 차이의 제곱값의 합을 비교해준다.

			for (int i = 0; i < 450; i++)
			{
				whatisbest[i] = 110000000;
			}

			//printf("kingpoint완료\n");

			for (int rightGo = 0; rightGo < leftimage.cols; rightGo++)
			{
				cv::Point matchpoint[145];
				int temp = 0;
				for (int i1 = 0; i1 < 145; i1++)
				{

					matchpoint[i1] = cv::Point(rightGo + 67, r + 67) + savepoint[i1];

					//printf("matchpoint의 위치들 x : %d,y : %d \n", matchpoint[i1].x, matchpoint[i1].y);


					temp = temp + pow1((leftfimage.at<uchar>(kingpoint[i1].y, kingpoint[i1].x) - rightfimage.at<uchar>((matchpoint[i1]).y, matchpoint[i1].x)), 2);

					//printf("%d 번째 점에서의 temp : %d \n", temp);

				}

				//printf("temp 계산 %d\n", temp); //이상한 부분


				whatisbest[rightGo] = temp;    //차이값을 저장

				//printf("비교중인 좌표 rightgo = %d, c = %d\n ",rightGo,c); 정상
				//**해당 (킹포인트 - 비교포인트)^2를 일시적으로 temp 값에 저장해주고 해당 temp를 whatisbest[rightGo]에 저장해준다. 그러면 whatisbest에는 몇번째 픽셀에서의 계산값들이 저장되어있음


			}
			cv::circle(rightfimage2, cv::Point((getMinInt(whatisbest, 450)), r), 5, (0, 0, 255), -1);

			//printf("c에서 매칭되는 거리차는 %d\n", (getMinInt(whatisbest, 450) - c));
			widelefteeee.at<uchar>(r + 67, c + 67) = (abs(getMinInt(whatisbest, 450)) - c) * 4;

			//그다음엔 해당 계산값들중 무엇이 가장 작은지를 찾아내야함.
			//그리고 가장 작은 계산 값의 픽셀의 위치가 현재 c와의 차이가 나는 것을 계산하고 이만큼 이동했다를 알려줘야함.


			//계산이 다 끝나면 해당 raw에서의 차이값 *4를 해줌.

		}
	}
	
	




	
	///////////////////////////////////





	






	cv::namedWindow("Result");


	//des 출력
	cv::imshow("Result", leftimageROI);
	cv::imshow("widegray", leftfimage);
	cv::imshow("matching result", rightfimage2);
	cv::imshow("descriptor", des);
	cv::imshow("reo", widelefteeee);
	cv::imwrite("Result.jpg", widelefteeee);




	cv::waitKey(0);

	return 0;
}


//x1과 y1의 값을 랜덤으로 중복되게 해서 준다.
void randomreturn(int *x1, int *y1)
{
	int count = 0; // 1이면 1찾기, 2이면 2찾기
	int num = 0;

	for (int i = 0; i < 2; i++) //x1,x2,y1,y2 네번 찾아야하기 때문에 포문 4번
	{ //13 13은 처음 시작점
		count++;
		num = rand() % 100;

		//1%의 확률

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
		//2%의 확률
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
		//5%의 확률
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
		//7%의 확률
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
		//8%의 확률
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

		//10%의 확률(가운데 예외처리 필요X 아직 x축이기 때문에)
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

		//8%의 확률
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
		//7%의 확률
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
		//5%의 확률
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
		//2%의 확률
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
		//1%의 확률
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
//인트의 승을 구해준다.
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