#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void getplayercoordinateforview(float x, float y) { //������� ��� ���������� ��������� ������


	view.setCenter(x + 100, y); //������ �� �������, ��������� ��� ���������� ������. +100 - �������� ������ �� ���� ������. �����������������
	return view;

}