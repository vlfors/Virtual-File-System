/*
 TreeFiles.h ������� ������ ��� ���������� ����������� �������� �������
*/
#pragma once
#ifndef TREEFILES_H
#define TREEFILES_H
#include <iostream>
#include <string>
#include <vector>
typedef std::vector<std::string> tLOCK;

class Catalog
{
   public:
	  std::string name_f;
	  //char *name_f;
      char type_f;
	  tLOCK locks;


};



// Template definition
//����������� �������
template<class CItem> class fTree
{
public:
   // Tree Item properties
	//�������� ���� ������
   CItem item;
   
   // Children items
   //�������� ����
   std::vector<fTree> children;
   //int add(fTree path ,fTree ch);

};
typedef fTree<Catalog> tTree;
typedef std::vector<tTree> tVECTREE;
#endif