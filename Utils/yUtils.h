﻿/*
	author : PengYao
	time   : 2016/3/23
	version: 1.0
	ext    : myself utils lib
	e-mail : yasin1151@outlook.com
 */

#ifndef _YASIN_UTILS_H_
#define _YASIN_UTILS_H_

#include <string>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <random>
//using namespace std;

/*
class yUtils
{
public:

	static int getRandom(int _begin, int _end);
};
*/

namespace yUtils
{
	const int MAX_INT_NUM = 16;
	const int MY_MAX_BYTE = 256;


	/*
	*	@brief : 将一个数转换成string
	*	@param : _value --- 需要转换的数
	*			 floatSaveDigits --- 需要保存的小数位数,默认为0
	*/
	template <typename T>
	std::string toStr(T _value, int floatSaveDigits = 0)
	{
		if (0 > floatSaveDigits)
		{
			return "";
		}

		char szFormat[MAX_INT_NUM] = {"%d"};
		char szBuf[MY_MAX_BYTE] = {};
		if (floatSaveDigits)
		{
			sprintf(szFormat, szFormat, floatSaveDigits);
			strcpy(szBuf, "%0.");
			strcat(szBuf, szFormat);
			strcat(szBuf, "lf");
			strcpy(szFormat, szBuf);
			sprintf(szBuf, szFormat, _value);
		}
		else
		{
			sprintf(szBuf, szFormat, _value);
		}

		return szBuf;
	}

	/*
		@brief : 判断两个浮点型是否相等
	*/

	inline bool IsEqualF(float lhs, float rhs)
	{
		if (lhs - rhs < 1e-6 && lhs - rhs >= -1e-6)
		{
			return true;
		}
		return false;
	}

	/*
		@brief : 判断两个double是否相等
	*/
	inline bool IsEqualLF(double lhs, double rhs)
	{
		if (lhs - rhs < 1e-15 && lhs - rhs >= -1e-15)
		{
			return true;
		}
		return false;
	}

	/*
		@brief : 获取两个点的角度
	*/
#ifdef __COCOS2D_H__

	/*
		@brief : 角度转弧度
	*/
	static float Angle2Radian(float angle)
	{
		return angle * std::_Pi / 180;
	}

	/*
		@brief : 弧度转角度
	*/
	static float Radian2Angle(float radian)
	{
		return radian * 180 / std::_Pi;
	}

	/*
	@brief : 获取两个点之间的弧度
	*/
	static float GetRadian(const cocos2d::Vec2& point1, const cocos2d::Vec2& point2)
	{
		float xDis = point1.x - point2.x;

		float yDis = point1.y - point2.y;

		float bevelEdge = sqrt(pow(xDis, 2) + pow(yDis, 2));

		float radian = acos(xDis / bevelEdge);

		//如果在第四象限，则为负数
		if (point1.y < point2.y)
		{
			radian = -radian;
		}

		return radian;
	}


	/*
		@brief : 获取两个点之间的角度
	*/
	static float GetAngle(const cocos2d::Vec2& point1, const cocos2d::Vec2& point2)
	{
		return Angle2Radian(GetRadian(point1, point2));
	}


	/*
		@brief : 将vs的gbk编码转换成utf-8编码，用于log
	*/
	static std::string GBK2UTF(const std::string& str)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		std::wstring wszBuf = [=]()
		{
			//将string装换成wstring
			setlocale(LC_ALL, "chs");
			const char* szSource = str.c_str();
			size_t uSize = str.size() + 1;
			wchar_t* wszDest = new wchar_t[uSize];
			wmemset(wszDest, 0, uSize);
			mbstowcs(wszDest, szSource, uSize);
			std::wstring result = wszDest;
			delete[] wszDest;
			setlocale(LC_ALL, "C");
			return result;
		}();

		int iAsciSize = WideCharToMultiByte(CP_UTF8, 0, wszBuf.c_str(), wszBuf.size(), NULL, 0, NULL, NULL);
		if (ERROR_NO_UNICODE_TRANSLATION == iAsciSize || 0 == iAsciSize)
		{
			return std::string();
		}

		char* szRetStr = new char[iAsciSize];
		int iConveRet = WideCharToMultiByte(CP_UTF8, 0, wszBuf.c_str(), wszBuf.size(), szRetStr, iAsciSize, NULL, NULL);
		if (iConveRet != iAsciSize)
		{
			return std::string();
		}

		std::string szBuf = "";
		szBuf.append(szRetStr, iAsciSize);

		delete[] szRetStr;
		return szBuf;
#else
		return str;
#endif
	}

#endif
}


#endif	// end _YASIN_UTILS_H_