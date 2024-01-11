#pragma once
struct Candle{
	const int MAX_SIZE;
	char* top_shadow = new char[MAX_SIZE];
	char* body = new char[MAX_SIZE];
	char* bottom_shadow = new char[MAX_SIZE];

	Candle(int maxSize) : MAX_SIZE(maxSize) {};
	void setTopShadow();
	void setBody();
	void setBottomShadow();
};