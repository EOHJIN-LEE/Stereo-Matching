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


	//이미지 로드
	cv::Mat leftimage = cv::imread("im_left_test.png");

	cv::Mat rightimage = cv::imread("im_right_test.png");



	cv::Mat leftgray;

	cv::Mat rightgray;

	cv::Mat leftresult = cv::Mat::zeros(375, 450, CV_8UC1);

	cv::Mat lefteeee = cv::Mat::zeros(375, 450, CV_8UC1); //왼쪽을 중심으로 표기해줄곳



	cv::Mat widelefteeee = cv::Mat::zeros(393, 468, CV_8UC1); //왼쪽을 중심으로 표기해줄곳          393, 468    마스크 1919일때
	//39일때 

	cv::cvtColor(leftimage, leftgray, cv::COLOR_BGR2GRAY); //그레이 스케일로

	cv::cvtColor(rightimage, rightgray, cv::COLOR_BGR2GRAY); //그레이 스케일로



	cv::medianBlur(leftgray, leftgray, 3); //5

	cv::medianBlur(rightgray, rightgray, 3); //5

	//sharpen(leftgray, leftgray);
	//sharpen(rightgray, rightgray);

	cv::equalizeHist(leftgray, leftgray);
	cv::equalizeHist(rightgray, rightgray);

	imgSharpening(leftgray, 10);
	imgSharpening(rightgray, 10);
	//메디안 필터 적용


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

	// widegray에 큰 이미지로 복사가 되었음. 39만큼 더 늘어났음(경계값 처리를 위해)


	leftwidegray.copyTo(leftfimage);

	rightwidegray.copyTo(rightfimage);

	rightwidegray.copyTo(rightfimage2);





	///////////////////////////////////////////////////// 디스크립터 /////////////////////////////////////////////////////

	cv::Mat des = cv::Mat::zeros(19, 19, CV_8UC1); //디스크립터
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
	cv::Point savepoint[361]; //256-> 32 i-> 16으로   361(마스크 19*19)
	/*
	for (int i = 0; i < 256; i++)
	{
		//첫번째 점
		randomreturn(&x1, &y1);
		//printf("x1 : %d, y1 : %d  \n\n", x1, y1);

		///////////////////////
		while (x1 == 39 && y1 == 39) //중앙일때는 randomreturn 중앙이 아닐때까지 반복
		{

			randomreturn(&x1, &y1);

		}
		////////////////////////



		//두번째 점
		randomreturn(&x2, &y2);

		////////////////////////
		while (x2 == 39 && y2 == 39) //중앙일때는 randomreturn 중앙이 아닐때까지 반복
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

		start_point = cv::Point(x1 - 39, y1 - 39);
		//printf("start_point x : %d, y : %d\n", start_point.x, start_point.y);
		end_point = cv::Point(x2 - 39, y2 - 39);
		//printf("end_point x : %d, y : %d\n", end_point.x, end_point.y);

		//printf("i : %d, i*2 : %d, i*2 + 1 : \n", i, i*2, i*2 + 1);
		savepoint[2 * i] = cv::Point(x1 - 39, y1 - 39);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2].x, savepoint[i*2].y);
		savepoint[2 * i + 1] = cv::Point(x2 - 39, y2 - 39);
		//printf("save_point x : %d, y : %d\n", savepoint[i*2+1].x, savepoint[i*2+1].y);

	}// 0,1 짝 2,3 짝 3,4 짝 이렇게 이루어짐
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
for (int r = 0; r < 375; r++) //그래도 계산할때는 r+에서부터 시작하기 때문   leftimage.rows
{//375
	printf("%d 번째 열 작업중입니다. \n", r);

	//중요한건 이 열이 돌아다니면서 비교
	for (int c = 0; c < leftimage.cols; c++) //마찬가지로 계산할때 c
	{
		int whatisbest[450];// col이 450이기 때문. 여기에 차이의 제곱값의 합을 비교해준다.


		for (int i = 0; i < 450; i++)
		{
			whatisbest[i] = 110000000;
		}


		//printf("\n현재 계산하고 있는 좌표 r : %d c : %d \n", r, c);
		cv::Point kingpoint[361];
		for (int i = 0; i < 361; i++) /// 256개의 savepoint
		{
			//printf("savepoint의 위치들 x : %d,y : %d \n", savepoint[i].x, savepoint[i].y);
			kingpoint[i] = cv::Point(c + 9, r + 9) + savepoint[i];

			//printf("kingpoint의 위치들 x : %d,y : %d \n", kingpoint[i].x, kingpoint[i].y);
		}//비교할 점을 골랐음 그점은 kingpoint에 저장






		//printf("kingpoint완료\n");

		for (int rightGo = 0; rightGo < leftimage.cols; rightGo++) // leftimage.col에서 c까지로 변환 왜냐하면 어차피 왼쪽부터 검사하기 때문
		{


			cv::Point matchpoint[361];
			int temp = 0;
			for (int i1 = 0; i1 < 361; i1++)
			{



				matchpoint[i1] = cv::Point(rightGo + 9, r + 9) + savepoint[i1];

				//printf("matchpoint의 위치들 x : %d,y : %d \n", matchpoint[i1].x, matchpoint[i1].y);

				int k = leftfimage.at<uchar>(kingpoint[i1].y, kingpoint[i1].x) - rightfimage.at<uchar>((matchpoint[i1]).y, matchpoint[i1].x);

				temp = temp + k * k;


				/*
				if (rightGo < c)
				{
					temp = (temp / 2);
				}

				*/
				//printf("%d 번째 점에서의 temp : %d \n", temp);

			}

			//printf("temp 계산 %d\n", temp); //이상한 부분


			if (rightGo < c)
			{
				temp = (temp / 2);
			} //왼쪽에있다면 매칭이 정확하다는 것을 도와줌


			whatisbest[rightGo] = temp;    //차이값을 저장


			//printf("222222\n"); //이상한 부분
			//printf("비교중인 좌표 rightgo = %d, c = %d\n ",rightGo,c); //정상
			//**해당 (킹포인트 - 비교포인트)^2를 일시적으로 temp 값에 저장해주고 해당 temp를 whatisbest[rightGo]에 저장해준다. 그러면 whatisbest에는 몇번째 픽셀에서의 계산값들이 저장되어있음


		}
		//cv::circle(rightfimage2, cv::Point((getMinInt(whatisbest, 450)), r), 5, (0, 0, 255), -1);

		//printf("c에서 매칭되는 거리차는 %d\n", (getMinInt(whatisbest, 450) - c));

				if ((abs((getMinInt(whatisbest, 450)) - c) * 4) > 220)
			{
					leftresult.at<uchar>(r, c) = 220;
			}
				else
				{
					leftresult.at<uchar>(r, c) = (abs((getMinInt(whatisbest, 450)) - c) * 4);
				}
			
			//widelefteeee.at<uchar>(r + 39, c + 39) = (abs(getMinInt(whatisbest, 450)) - c) * 4;
			
			
			
			
			//그다음엔 해당 계산값들중 무엇이 가장 작은지를 찾아내야함.
			//그리고 가장 작은 계산 값의 픽셀의 위치가 현재 c와의 차이가 나는 것을 계산하고 이만큼 이동했다를 알려줘야함.


			//계산이 다 끝나면 해당 raw에서의 차이값 *4를 해줌.

		}
	}

	
	cv::medianBlur(leftresult, leftresult, 3);

	//imgSharpening(leftresult, 3);

	cv::medianBlur(leftresult, leftresult, 3);

	cv::namedWindow("Result");
	

	//des 출력
	cv::imshow("Result", leftimageROI);
	cv::imshow("widegray", leftfimage);
	cv::imshow("matching result", rightfimage2);
	cv::imshow("descriptor", des);
	cv::imshow("reo", leftresult);
	cv::imwrite("Result.jpg", leftresult);




	cv::waitKey(0);

	return 0;
}


//x1과 y1의 값을 랜덤으로 중복되게 해서 준다.
void randomreturn(int *x1, int *y1)
{
	int count = 0; // 1이면 1찾기, 2이면 2찾기
	int num = 0;

	for (int i = 0; i < 2; i++) //x1,x2,y1,y2 네번 찾아야하기 때문에 포문 4번
	{ //39 39은 처음 시작점
		count++;
		num = rand() % 100;

		//1%의 확률

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
		//2%의 확률
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
		//5%의 확률
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
		//7%의 확률
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
		//8%의 확률
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

		//10%의 확률(가운데 예외처리 필요X 아직 x축이기 때문에)
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

		//8%의 확률
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
		//7%의 확률
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
		//5%의 확률
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
		//2%의 확률
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
		//1%의 확률
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


void imgSharpening(cv::Mat& img, float sigma)

{

	cv::Mat tmp;

	cv::GaussianBlur(img, tmp, cv::Size(0, 0), sigma);

	cv::addWeighted(img, 1.5, tmp, -0.5, 0, img);

}



