/*
 TreeFiles.h Описаны классы для построения виртуальной файловой системы
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
//Определение шаблона
template<class CItem> class fTree
{
public:
   // Tree Item properties
	//Свойства узла дерева
   CItem item;
   
   // Children items
   //дочерние узлы
   std::vector<fTree> children;
   //int add(fTree path ,fTree ch);

};
typedef fTree<Catalog> tTree;
typedef std::vector<tTree> tVECTREE;
#endif