#pragma once
struct Calculator {
	int open, close, low, high;
	Calculator(int o, int c, int l, int h) :open(o), close(c), low(l), high(h) {};

	int candleBodySize();
	int candleTopShadowSize();
	int candleBottomShadowSize();
};